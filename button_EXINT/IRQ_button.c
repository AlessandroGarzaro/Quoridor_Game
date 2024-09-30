#include "button.h"
#include "lpc17xx.h"
#include "../GLCD/GLCD.h"
#include "../timer/timer.h"

extern int int0;
extern int key1; 
extern int key2;

extern int turno;
extern int EndGame;
extern  int IntCount;


void EINT0_IRQHandler (void)	  	/* INT0														 */
{		
	NVIC_DisableIRQ(EINT0_IRQn);							/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 20);     /* GPIO pin selection */
	int0=1;
	IntCount=25;
	enable_timer(0);
	turno=1;
	
	GUI_Text(30,300, (unsigned char*) "                    ",0x0000,White);
	EndGame=0;
	LPC_SC->EXTINT &= (1 << 0);   
	

}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	NVIC_DisableIRQ(EINT1_IRQn);							/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
	key1=1;
	LPC_SC->EXTINT &= (1 << 1); 
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{	
	NVIC_DisableIRQ(EINT2_IRQn);							/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 24);     /* GPIO pin selection */
	key2=1;
  LPC_SC->EXTINT &= (1 << 2);     					/* clear pending interrupt         */    
}


