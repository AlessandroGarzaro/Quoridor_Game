
/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../RIT/RIT.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern  int IntCount;
extern int turno;
extern int EndGame;

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER0_IRQHandler (void)
{
	static int clear = 0;
	char time_in_char[5] = "";
	int i,j;
	
	i=players[turno].x_ind;
	j=players[turno].y_ind;
	
	
	IntCount--;
	sprintf(time_in_char,"%4d",IntCount);					
						/* 1 seconds = 200 times * 500 us*/
	GUI_Text(120, 260, (uint8_t *) time_in_char, Black, White);		
		if(IntCount<=0 && EndGame==0){
			
			DrawAround(players[turno],White);
			DrawSquare(DisplayMap[i][j].x,DisplayMap[i][j].y,White);
			DrawPlayer(DisplayMap[i][j].x,DisplayMap[i][j].y,players[turno].colour);
				if(turno==1)
					turno=2;
			
				else
					turno=1;
				IntCount=25;
				
				StartGame(turno);
	
	}
		
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}




/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER_IRQHandler (void)
{	
	
	static int clear = 0;
	char time_in_char[5] = "";
	
	
	IntCount--;
	sprintf(time_in_char,"%4d",IntCount);					
						/* 1 seconds = 200 times * 500 us*/
	GUI_Text(120, 260, (uint8_t *) time_in_char, Black, White);		
	if(IntCount==0){
		IntCount=25;
		
	} 
		
					
	
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}
/******************************************************************************
**                            End Of File
******************************************************************************/
