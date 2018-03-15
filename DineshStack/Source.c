#include <stdio.h>
#include <stdlib.h>

void reverse(char ar[], int n)
{
    char c;
    int i = 0;
    for ( i = 0; i <= n ; i++){
        c = ar[i];
        ar[i] = ar[n];
        ar[n] = c;
        n--;}

}


int main(void){

	int sizeOfStack,i,iUserChoice;
	char *str;
	char cPush,cPop;

    printf("Enter the amount of character to be input :");

	scanf("%d", &sizeOfStack);

	str = (char*)realloc(NULL, sizeof(char)*sizeOfStack);
	
	for(i =0;i<sizeOfStack;i++)
	{
		printf("\rEnter the character to be pushed : ");
		scanf(" %c", &str[i]);
	}

	//add end char to tail 
	str[sizeOfStack]='\0';

	
	// reverse array  
	reverse(str,sizeOfStack-1);

	
	//printf("the final array is :%s\n", str);


	while(1)
	{
		printf( "1.Push an element on the stack\n"
  		"2.Pop an element from the stack\n"
		"3.Display the top element\n"
		"4.Display all stack element\n"
		"5.Display size of the stack\n"
		"6.Display the final stack and its reversed version\n"
		"7.quit\n"
		);


		printf("Enter your choice :");
		scanf(" %d", &iUserChoice);

		switch (iUserChoice) {
			case 1:	
				printf("\rEnter the element to be pushed : ");
				scanf(" %c", &cPush);

				// re allocate array size
				str = (char*)realloc(str, sizeof(char)*(sizeOfStack+1));
				 
				for(i=sizeOfStack+1;i>0;i--)
			        str[i]=str[i-1];
				str[0]=cPush;
				str[sizeOfStack+1]='\0';

				sizeOfStack=sizeOfStack+1;


				//printf("the final array is :%s\n", str);


				break;

			case 2:	
				printf("\rpop element is : ");
				scanf(" %c", &cPop);
				for(i=0;i<sizeOfStack;i++)
			        str[i]=str[i+1];
		
				sizeOfStack=sizeOfStack-1;

				//printf("the final array is :%s\n", str);

				break;

			case 3: 
				printf("\relement at the top is:%c",str[0]);
				printf("\n");
				break;

			case 4: 
				printf("\rstack is:\n");
				for(i=0;i<sizeOfStack;i++)
				{
					printf("%c     ",str[i]);
				}
				printf("\n");

				break;
			case 5:
				printf("\rsize of stack is:%d",sizeOfStack);
				printf("\n");
				break;

			case 6:
				printf("\rthe initial stack is:\n");
				for(i=0;i<sizeOfStack;i++)
				{
					printf("%c     ",str[i]);
				}
				printf("\n");


				printf("\rthe final stack is:\n");
				for(i=sizeOfStack-1;i>=0;i--)
				{
					printf("%c     ",str[i]);
				}
				printf("\n");
				break;

			case 7:	
				exit(0);

		}

	}
    return 0;
}