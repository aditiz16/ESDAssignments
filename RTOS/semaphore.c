
#include "config.h"
#include "stdlib.h"
#include "serial.h"


#define	TaskStkLengh	100			//Define the Task0 stack length 

 
OS_STK	TaskStk [TaskStkLengh];		//Define the Task0 stack 
OS_STK	TaskStk1 [TaskStkLengh];		//Define the Task1 stack 

OS_EVENT *printsem;

void 	Task0(void *pdata);			//Task0 
void 	Task1(void *pdata);			//Task1 

int main (void)
{
	
	IO0DIR = 0x00FF0000;
	init_serial ();
	TargetInit ();
	OSInit ();	
	printsem = OSSemCreate(1);																									
	OSTaskCreate (Task0,(void *)0, &TaskStk[TaskStkLengh - 1], 2);	
	OSTaskCreate (Task1,(void *)0, &TaskStk1[TaskStkLengh - 1], 3);		
	OSStart();
	return 0;															
}
/*********************************************************************************************************
**                            Task0 
********************************************************************************************************/

void Task0	(void *pdata)
{
	int n;
	uint8 err;
//	pdata = pdata;		
	while (1)
	{
		printf("Task0 waiting for semaphore \n");
	  OSSemPend(printsem, 0, &err);  /* Acquire semaphore */
		printf("Acquire Sem by Task0 \n");		
			IO0CLR = 0xFF < 16;
			for (n = 0; n < 10; n++) 
		{
			IO0SET = n <<16; 				/* Turn on LED */
	    OSTimeDly(20);				/* Wait */
			IO0CLR = n <<16;				/* Turn off LEDs */
			OSTimeDly(20);				/* Wait */
		}
	   OSSemPost(printsem);		/* Release semaphore */
		 printf("Release Sem by Task0\n");
     OSTimeDly(20);
	}
}
/*********************************************************************************************************
**                            Task1 
********************************************************************************************************/

		void Task1	(void *pdata)
{
	int n;
	uint8 err;
	while(1)
   	{
	     printf("Task1 waiting for semaphore\n");
		OSSemPend(printsem, 0, &err);  /* Acquire semaphore */
		 printf("Acquire Sem by Task1 \n");	
			IO0CLR = 0xFF < 16;			
	   for (n = 0; n < 10; n++) 
		{
			IO0SET = 0xFF << 16; 				/* Turn on LED */
	    OSTimeDly(20);				/* Wait */
			IO0CLR = 0xFF << 16;				/* Turn off LEDs */
			OSTimeDly(20);				/* Wait */
		}
	       OSSemPost(printsem);		/* Release semaphore */
		   printf("Release Sem by Task1\n");

   	}

}   
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
