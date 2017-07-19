#include<windows.h>
#include<stdio.h>
#include <process.h>
#include <iostream>


long lNumber = 10;
HANDLE m_hWriteComplete[2];
HANDLE ghMutex; 


unsigned __stdcall WorkThread(LPVOID lparam)
{
	DWORD dwWaitResult; 

	for(int i=0;i<10000;++i)
	{
		//std::cout<<"1111111111"<<std::endl;
		dwWaitResult = WaitForSingleObject( 
            ghMutex,    // handle to mutex
            INFINITE);  // no time-out interval

		switch (dwWaitResult) 
        {
            // The thread got ownership of the mutex
            case WAIT_OBJECT_0: 
                __try { 
                    // TODO: Write to the database
                    //printf("Thread %d writing to database...\n", 
                    //        GetCurrentThreadId());

                    lNumber=lNumber+3;
					lNumber=lNumber+5;
                } 

                __finally { 
                    // Release ownership of the mutex object
                    if (! ReleaseMutex(ghMutex)) 
                    { 
                        // Handle error.
                    } 
                } 
                break; 

            // The thread got ownership of an abandoned mutex
            // The database is in an indeterminate state
            case WAIT_ABANDONED: 
                return FALSE; 
        }

	}
	
	SetEvent(m_hWriteComplete[0]);
	return 0;
}

unsigned __stdcall WorkThread001(LPVOID lparam)
{
	DWORD dwWaitResult; 

	for(int i=0;i<10000;++i)
	{
		//std::cout<<"2222222222"<<std::endl;

		dwWaitResult = WaitForSingleObject( 
            ghMutex,    // handle to mutex
            INFINITE);  // no time-out interval

		switch (dwWaitResult) 
        {
            // The thread got ownership of the mutex
            case WAIT_OBJECT_0: 
                __try { 
                    // TODO: Write to the database
                    //printf("Thread %d writing to database...\n", 
                    //        GetCurrentThreadId());

                    lNumber=lNumber-3;
					lNumber=lNumber-5;
                } 

                __finally { 
                    // Release ownership of the mutex object
                    if (! ReleaseMutex(ghMutex)) 
                    { 
                        // Handle error.
                    } 
                } 
                break; 

            // The thread got ownership of an abandoned mutex
            // The database is in an indeterminate state
            case WAIT_ABANDONED: 
                return FALSE; 
        }
	}

	
	SetEvent(m_hWriteComplete[1]);
	return 0;
}


void HowToWaitForTwoThreadFinish()
{
	HANDLE hWorker;
	UINT  nThreadID,nThreadID_01;
	DWORD dwEvent;
	
	
	for (int i = 0; i < 2; i++) 
    { 
	
			m_hWriteComplete[i]= CreateEvent(NULL,   //SECURITY_ATTRIBUTES
								  TRUE,   //If this parameter is TRUE, the function creates a manual-reset event object
								  FALSE,  //If this parameter is TRUE, the initial state of the event object is signaled; otherwise, it is nonsignaled
								  NULL);  //The name of the event object

			if (m_hWriteComplete[i] == NULL) 
			{ 
				printf("CreateEvent error: %d\n", GetLastError() ); 
				ExitProcess(0); 
			} 

	}



	hWorker = (HANDLE)_beginthreadex(NULL,					// Security
									0,					// Stack size - use default
									WorkThread,     		// Thread fn entry point
									(void*) NULL,			// Param for thread
									0,						// Init flag
									&nThreadID);			// Thread address	

	hWorker = (HANDLE)_beginthreadex(NULL,					// Security
									0,					// Stack size - use default
									WorkThread001,     		// Thread fn entry point
									(void*) NULL,			// Param for thread
									0,						// Init flag
									&nThreadID_01);			// Thread address	


	 //   while(true)
		//{
			dwEvent = WaitForMultipleObjects( 
			2,           // number of objects in array
			m_hWriteComplete,     // array of objects
			TRUE,       // wait for any object
			INFINITE);       // five-second wait

	std::cout<<"final number is "<<lNumber<<std::endl;
	getchar();


}

void main()
{
	ghMutex = CreateMutex( 
						NULL,              // default security attributes
						FALSE,             // initially not owned
						NULL);             // unnamed mutex

	if (ghMutex == NULL) 
    {
        printf("CreateMutex error: %d\n", GetLastError());
        return ;
    }

	HowToWaitForTwoThreadFinish();


}


