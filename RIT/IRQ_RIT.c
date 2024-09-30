/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../RIT/RIT.h"
#include "../button_EXINT/button.h"
#include "../GLCD/GLCD.h"
#include "../Touchpanel/Touchpanel.h"
#include "../timer/timer.h"

volatile int key2=0;
volatile int key1=0;
volatile int int0=0;

volatile enum MODE{
    MOVE,
	  WALL
}mode;
volatile int EndGame=0;
volatile int turno=0;
volatile int i_wall=7, j_wall=7;


extern Player players[3];
extern Move move;
/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
volatile int IntCount;
volatile int Cambia;

void RIT_IRQHandler (void)
{					
	static int select=0,D=0,U=0,L=0,R=0;		//joystick
	
	
	static int moved = 0, new_wall=0;
	static int i_new,j_new;
	static int i_newWall,j_newWall;
	static Move move;
	static uint32_t move_info;
	Player playing=players[turno];
	
	
	int i,j;
	//if(moved==0){
		
	i=playing.x_ind; // mi salvo indice x player in gioco
	j=playing.y_ind; // mi salvo indice y player in gioco
		
	//}
 	if(new_wall==0){
		i_newWall=i_wall;
		j_newWall=j_wall;
		new_wall=1;
	}
	/*	if(IntCount<=0 && EndGame==0){
	
				if(turno==1)
					turno=2;
			
				else
					turno=1;
				IntCount=25;
				StartGame(turno);
	
	}*/
	if(key2 > 1){ 
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){	/* KEY2 pressed */		
			switch(key2){
				case 2:
					if(mode == WALL){
					
						//TODO: Rotate Wall
						j_newWall=j_newWall;
						i_newWall=i_newWall;
						new_wall=1;
						TurnWall(i_newWall,j_newWall,i_newWall,j_newWall);
						
						
						
						reset_RIT();
					}
						
					break;
				default:
					break;
			}
			key2++;
		}
		else {	/* button released */
			//disable_RIT();
			reset_RIT();
			key2=0;			
			NVIC_EnableIRQ(EINT2_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
		}
	}
	else {
		if(key2 == 1)
			key2++;
	}
	
	/* Button management - KEY1 */
	if(key1 >= 1){ 
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){	/* KEY1 pressed */	
			switch(mode){
				case MOVE: 
						if(players[turno].wall>0){
						mode = WALL;
						DrawAround(playing,White);			
						DrawWallPlayer(turno,i_wall,j_wall);
						moved=0;
						}
						reset_RIT();
						
						//mostra muro al centro
				break;
					
				case WALL:
					
						mode = MOVE;
						//rimuovi il muro		
					reset_RIT();
					break;
				default:
					break;
			}
			key1++;
		}
		else {	/* button released */
			key1=0;	
			//disable_RIT();
			reset_RIT();
			NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
		}
		
	//------------------------------------------------------------/
	
		
		/* INT0 pressed */			
	}else	if(int0 >= 1){
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){				
			
						
						mode=MOVE;
						StartGame(turno);
					
						reset_RIT();
		}
		else {	/* button released */
			int0=0;			
			NVIC_EnableIRQ(EINT0_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
		}
		if (int0 == 1)
			int0++;
		
		
		/* ------------------------------------------*/
	}else if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
		
		/* Joytick Select pressed */
		
		select++;
		
		if(select>=1){			// pressione di 50ms
			
			
			if(mode == MOVE && moved == 1){
				
				players[turno].x_ind=i_new;
				players[turno].y_ind=j_new;
				if(turno!=0)
				DrawAround(playing,White);
				DrawSquare(DisplayMap[i][j].x,DisplayMap[i][j].y,White);
				
				
				i=players[turno].x_ind; // mi salvo indice x player in gioco
				j=players[turno].y_ind;	
				select=0;
				moved=0;
				DrawPlayer(DisplayMap[i][j].x,DisplayMap[i][j].y,playing.colour);
				new_wall=0;
				CheckWinner(turno);
				
				
				//salvo info in 32 bit
				
				if(turno==1)
					move.playerID=0;
				else if(turno==2)
					move.playerID=1;
				
				move.wallOrientation=0;
				move.playerMoveOrWall=0;
				move.x=DisplayMap[i][j].x;
				move.y=DisplayMap[i][j].y;
				
				save_info(move);		
				
				
				//conferma posizione
					
			}else if(mode == WALL){
				
				// salvo il muro
				if(DisplayMap[i_newWall][j_newWall].muro_pos==0){
						DisplayMap[i_newWall][j_newWall].muro_pos=1;
					
						if(DisplayMap[i_newWall][j_newWall].muro==1){
								DisplayMap[i_newWall][j_newWall+1].muro_pos=1;
								DisplayMap[i_newWall][j_newWall-1].muro_pos=1;
								move.wallOrientation=0;
							
						}else if(DisplayMap[i_newWall][j_newWall].muro==2){
								DisplayMap[i_newWall+1][j_newWall].muro_pos=1;
								DisplayMap[i_newWall-1][j_newWall].muro_pos=1;
								move.wallOrientation=1;

						}
						DrawWallPlayer(turno,i_newWall,j_newWall);
						select=0;
						moved=0;
						mode = MOVE;
						new_wall=0;
						UpdateValour(turno);
						
						
						
				if(turno==1)
					move.playerID=0;
				else if (turno==2)
					move.playerID=1;
				
				
				move.playerMoveOrWall=1;
				move.x=DisplayMap[i][j].x;
				move.y=DisplayMap[i][j].y;
				
				save_info(move);		
						
						
				}
				
			 //conferma muro		
		}
		if(turno==1)
					turno=2;
		
				
				else
					turno=1;
				IntCount=25;
				StartGame(turno);
	}
			//	Down / Sud
	}else if((LPC_GPIO1->FIOPIN & (1<<26)) == 0 && L==0 && R==0 && U==0){	//se il pin indicante la direzione ? attivo e  								
		D++;																																	// non sono attivi gli altri pin di direzione
		if(D>=1 && j+2>=0 && j_newWall<11){
				switch(mode){
					case MOVE:
						
						DrawAround(playing,Yellow);
						DrawSquare(DisplayMap[i][j].x,DisplayMap[i][j].y,Yellow);
					 // aggiorno posizione player
						
						if(DisplayMap[i][j+1].muro_pos==0){
						if(moved==0){
							j_new=j+2;
							i_new=i;
							moved=1;
						}				
						select=0;
						DrawPlayer(DisplayMap[i][j].x,DisplayMap[i][j+2].y,playing.colour);
					}
						if(i_new==playing.x_ind && j_new==playing.y_ind)
								moved=0;
						
						break;
			case WALL:
							
						
							j_newWall=j_newWall+2;
							i_newWall=i_newWall;
							new_wall=1;
							
						
						MoveWall(i_newWall,j_newWall-2,i_newWall,j_newWall);
						if(i_newWall==i_wall && j_newWall==j_wall)
								new_wall=0;
						
						
					
						break;
				
				}
		}
				//Left / Ovest
	}else if((LPC_GPIO1->FIOPIN & (1<<27)) == 0 && R==0 && D==0 && U==0){													
		L++;
		if(L==1){
			
			
			switch(mode){
					case MOVE:
						
					
						
						DrawAround(playing,Yellow);
						DrawSquare(DisplayMap[i][j].x,DisplayMap[i][j].y,Yellow);
					
						if(moved==0){
							j_new=j;
							i_new=i-2;
							moved=1;
						}		
						DrawPlayer(DisplayMap[i-2][j].x,DisplayMap[i][j].y,playing.colour);
						select=0;
						
						if(i_new==playing.x_ind && j_new==playing.y_ind)
								moved=0;
						break;
			
				
					case WALL:
							
						//if(new_wall==0){
							j_newWall=j_newWall;
							i_newWall=i_newWall-2;
							new_wall=1;
							
						//}	
						MoveWall(i_newWall+2,j_newWall,i_newWall,j_newWall);
						if(i_newWall==i_wall && j_newWall==j_wall)
								new_wall=0;
						
					
						break;
				}

		}
	// Right / Est
	}else if((LPC_GPIO1->FIOPIN & (1<<28)) == 0 && L==0 && U==0 && D==0){													
		R++;
		if(R==1){
			
			
			switch(mode){
					case MOVE:
						DrawAround(playing,Yellow);
						DrawSquare(DisplayMap[i][j].x,DisplayMap[i][j].y,Yellow);
					
						
						if(moved==0){
							j_new=j;
							i_new=i+2;
							moved=1;
						}		
						
						DrawPlayer(DisplayMap[i+2][j].x,DisplayMap[i][j].y,playing.colour);
						select=0;
						if(i_new==i_wall && j_new==i_wall)
								moved=0;
						break;
			
				
					case WALL:
							
						//if(new_wall==0){
							j_newWall=j_newWall;
							i_newWall=i_newWall+2;
							new_wall=1;
							
						//}	
						MoveWall(i_newWall-2,j_newWall,i_newWall,j_newWall);
						if(i_newWall==i_wall && j_newWall==j_wall)
								new_wall=0;
						
					
						break;
				}

	// UP / Nord
			}
	}else if((LPC_GPIO1->FIOPIN & (1<<29)) == 0 && L==0 && R==0 && U==0){														
		U++;
 		if(U==1 && j>=0 && j_newWall>1){
			switch(mode){
					case MOVE:
						DrawAround(playing,Yellow);
						DrawSquare(DisplayMap[i][j].x,DisplayMap[i][j].y,Yellow);
					
						
						if(moved==0){
							j_new=j-2;
							i_new=i;
							moved=1;
						}		
						DrawPlayer(DisplayMap[i][j].x,DisplayMap[i][j-2].y,playing.colour);
						select=0;
						
						if(i_new==playing.x_ind && j_new==playing.y_ind)
								moved=0;
						break;
			
				
					case WALL:

							j_newWall=j_newWall-2;
							i_newWall=i_newWall;
							new_wall=1;
							
						//}	
						MoveWall(i_newWall,j_newWall+2,i_newWall,j_newWall);
						if(i_newWall==i_wall && j_newWall==j_wall)
								new_wall=0;
						break;
				}
		}
	
	}else{
		select=0;
		U=D=L=R=0;
	}

	
	
	
	
  return;
}




/******************************************************************************
** Function name:		StartGame
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


void StartGame(turno){
	
		/*	GUI_Text(30,300, (unsigned char*) "      Inizia        ",0x0000,White);*/
			//GUI_Wall(40,260, players[1].wall,0x0000,White);
			//GUI_Wall(200,260, players[2].wall,0x0000,White);
			
	
			switch(turno){
				case 0:
					break;
					
				case 1:
					Turno(players[turno]);
					//turno=2;
				break;
								
				case 2:
					Turno(players[turno]);
					//turno=1;
				break;
					
			//}
}
}

/******************************************************************************
** Function name:		Turno
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


void Turno(Player player){
		//possibili movimenti
		// devo controllare di ognuno che non abbiano barriere 
	  // e siano dentro le barriere
		//uint16_t i,j,k;
	//int EndRound=1;
	init_timer(1,0x0B1780);							// 1min 0x2CB41780
	if(turno!=0 && EndGame==0 ){
	DrawAround(player,Yellow);
	}
}


void UpdateValour(int turno){
		char nWall[5] = "";
		players[turno].wall=players[turno].wall-1;
	if(players[turno].wall==0){
		GUI_Text(30,300, (unsigned char*) "  No walls available, move the token ",0x0000,White);
		GUI_Text(30,300, (unsigned char*) "                                     ",0x0000,White);
	}
		
			sprintf(nWall,"%4d",players[turno].wall);
	if (turno==1){
			GUI_Text(40,260,(unsigned char*)"   ", 0x0000, White);
			GUI_Text(40,260, (uint8_t *) nWall, 0x0000, White);
	}else if(turno==2){
			
		  GUI_Text(200,260,(unsigned char*)"   ", 0x0000, White);
			GUI_Text(200,260, (uint8_t *) nWall, 0x0000, White);
	}
	
}


/******************************************************************************
**                            End Of File
******************************************************************************/
