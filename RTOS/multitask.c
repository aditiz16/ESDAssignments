
#include "config.h"
#include "stdlib.h"
#include "serial.h"
#include "LCD.h"

/*Hardware Connections 
****Serial Communication****
Connect a DB9 cable between PC and UART0.
	COMPORT Settings
	Baudrate:-9600
	Databits:-8
	Parity:-None
	Stopbits:1

**** LCD Connections *****
LCD Data - P1.23  - P1.16
LCD_RS - P0.8
LCD_RW - P0.9
LCD_EN - P0.10
**** LED Connections *****
LED - P0.23 - P0.16 */

#define	TaskStkLengh	100			//Define the Task0 stack length 

 
OS_STK	TaskStk0 [TaskStkLengh];		//Define the Task0 stack 
OS_STK	TaskStk1 [TaskStkLengh];		//Define the Task1 stack 
OS_STK	TaskStk2 [TaskStkLengh];		//Define the Task2 stack 

void 	Task0(void *pdata);			//Task0 
void 	Task1(void *pdata);			//Task1 
void 	Task2(void *pdata);			//Task2 

int main (void)
{
	
	
	TargetInit ();
	OSInit ();	
   																								
	OSTaskCreate (Task0,(void *)0, &TaskStk0[TaskStkLengh - 1], 1);	
	OSTaskCreate (Task1,(void *)0, &TaskStk1[TaskStkLengh - 1], 2);	
	OSTaskCreate (Task2,(void *)0, &TaskStk2[TaskStkLengh - 1], 3);	
	
	OSStart();
	return 0;															
}
/*********************************************************************************************************
**                            Task0 
********************************************************************************************************/

void Task0	(void *pdata)
{
	IO0DIR |= 0xFF << 16;  //P0.23 - P0.16 --LED
	while(1)
  {
		IO0SET =0xFF << 16;		/* Turn on LED */
    OSTimeDly(200);   		   	/* Wait */
		IO0CLR = 0xFF << 16;  		/* Turn off LEDs */
    OSTimeDly(200);      		/* Wait */
 	}
}
/*********************************************************************************************************
**                            Task1 
********************************************************************************************************/

void Task1	(void *pdata)
{
	int i;
	unsigned char flag = 0;
	 lcd_init();		//LCD Task
     lcd_cmd (0x38);
	  lcd_cmd (0x0c);
	  lcd_cmd (0x06);
	  lcd_cmd (0x01);
		
		while (1)
		{
		if(!flag)
		{
			lcd_cmd (0x01);
			lcd_display_str ("LCD_TASK",8);
		  flag = 1;
		  OSTimeDly(100);
		}
		else 
			{
			lcd_cmd (0x01);
			lcd_display_str ("Smart Logic",11);
		  flag = 0;
		  OSTimeDly(100);
			}
		}
}
 
/*********************************************************************************************************
**                            Task2 
********************************************************************************************************/

void Task2 (void *data)
{
	unsigned char flag = 0;
	init_serial ();
  while (1)
	{
		if(!flag)
			{
			printf ("\nSmarttt Logic");
		  flag = 1;
		  OSTimeDly(100);
			}
		else 
			{
			printf ("\nUART Task");
		  flag = 0;
		  OSTimeDly(100);
			}
	}
}



/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
