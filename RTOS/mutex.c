
#include "config.h"
#include "stdlib.h"
#include "serial.h"


#define	TaskStkLengh	50			//Define the Task0 stack length 

 
OS_STK	TaskStk0 [TaskStkLengh];		//Define the Task0 stack 
OS_STK	TaskStk1 [TaskStkLengh];		//Define the Task1 stack 
OS_STK	TaskStk2 [TaskStkLengh];	

OS_EVENT *mutex;

void 	Task0(void *pdata);			//Task0 
void 	Task1(void *pdata);			//Task1 
void 	Task2(void *pdata);			//Task1 

int main (void)
{
	uint8 err;
	IO0DIR = 0x00FF0000;
	init_serial ();
	TargetInit ();
	OSInit ();	
	mutex = OSMutexCreate(1,&err);																									
	OSTaskCreate (Task0,(void *)0, &TaskStk0[TaskStkLengh - 1], 3);	
	OSTaskCreate (Task1,(void *)0, &TaskStk1[TaskStkLengh - 1], 4);
	OSTaskCreate (Task2,(void *)0, &TaskStk2[TaskStkLengh - 1], 5);	
	OSStart();
														
}
/*********************************************************************************************************
**                            Task0 
********************************************************************************************************/

void Task0	(void *pdata)
{
	int n;
	uint8 err;
		
	while (1)
	{
		printf("Task0 waiting for Mutex \n");
	  OSMutexPend(mutex, 0, &err);  /* Acquire Mutex */
		printf("Acquire Mutex by Task0 \n");		
		IO0CLR = 0xFF < 16;
		for (n = 0; n < 10; n++) 
			{
			IO0SET = n <<16; 			/* Display value n */
	    OSTimeDly(20);				/* Wait */
			IO0CLR = n <<16;			/* Turn off LEDs */
			OSTimeDly(20);				/* Wait */
			}
	  OSMutexPost(mutex);		/* Release semaphore */
		printf("Release Mutex by Task0\n");
    OSTimeDly(500);
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
	  printf("Task1 waiting for Mutex \n");
		OSMutexPend(mutex, 0, &err);  /* Acquire semaphore */
		printf("Acquire Mutex by Task1 \n");	
		IO0CLR = 0xFF < 16;			
	  for (n = 0; n < 10; n++) 
			{
			IO0SET = 0xFF << 16; 	/* Turn on LED */
	    OSTimeDly(20);				/* Wait */
			IO0CLR = 0xFF << 16;	/* Turn off LEDs */
			OSTimeDly(20);				/* Wait */
			}
		OSMutexPost(mutex);		/* Release semaphore */
		printf("Release mutex by Task1\n");
		OSTimeDly(200);
  }

}   

/*********************************************************************************************************
**                            Task1 
********************************************************************************************************/

void Task2	(void *pdata)
{
	int n, a;
	uint8 err;
	while(1)
  {
	  printf("Task2 waiting for Mutex \n");
		OSMutexPend(mutex, 0, &err);  /* Acquire semaphore */
		printf("Acquire Mutex by Task2 \n");	
		IO0CLR = 0xFF < 16;	
		a = 0x01;						//Initial Value	
	  for (n = 0; n < 8; n++) 
			{
			IO0SET = a << 16; 	/* Turn on LED */
	    OSTimeDly(20);				/* Wait */
			IO0CLR = a << 16;	/* Turn off LEDs */
			OSTimeDly(20);				/* Wait */
			a = a << 1;		
			}
		OSMutexPost(mutex);		/* Release semaphore */
		printf("Release mutex by Task2\n");
		//OSTimeDly(40);
  }

}   
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
