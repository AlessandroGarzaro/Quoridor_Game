#include "lpc17xx.h"
#include "RIT.h"
#include "../RIT/RIT.h"
#include "../button_EXINT/button.h"
#include "../GLCD/GLCD.h"
#include "../Touchpanel/Touchpanel.h"
#include "../timer/timer.h"

extern int EndGame;



void DrawAround(Player player,uint16_t Color){
	
	uint16_t i,j;
	
	i=player.x_ind;
	j=player.y_ind;

		if( i<13 && (j-2)<13 && (i)>=0 && (j-2)>=0 && DisplayMap[i][j-1].muro_pos==0 )
				DrawSquare(DisplayMap[i][j].x,DisplayMap[i][j-2].y,Color);
	
	// guardo quello  a destra
	if( (i+2)<13 && (j)<13 && (i+2)>=0 && (j)>=0 && DisplayMap[i+1][j].muro_pos==0 )
			  DrawSquare(DisplayMap[i+2][j].x,DisplayMap[i][j].y,Color);
	
	// guardo quello  a sinistra
	if( (i-2)<13 && (j)<13 && (i-2)>=0 && (j)>=0 && DisplayMap[i-1][j].muro_pos==0 )
			DrawSquare(DisplayMap[i-2][j].x,DisplayMap[i][j].y,Color);
	
	// guardo quello  sotto
	if( (i)<13 && (j+2)<13 && (i)>=0 && (j+2)>=0 && DisplayMap[i][j+1].muro_pos==0 )  
				DrawSquare(DisplayMap[i][j].x,DisplayMap[i][j+2].y,Color);

}

void DrawWallPlayer(turno,i,j){
			
			uint16_t x=DisplayMap[i][j].x;
			uint16_t y=DisplayMap[i][j].y;
	
			DrawWall(x,y,DisplayMap[i][j].muro);

}
void TurnWall(i_old,j_old,i_new,j_new){
			
				//old
			uint16_t x_old=DisplayMap[i_old][j_old].x,x;
			uint16_t y_old=DisplayMap[i_old][j_old].y,y;
			
			uint16_t orient_old=DisplayMap[i_old][j_old].muro,orient_new;
	
			DeleteWall(x_old,y_old,orient_old);
	
			if(orient_old==1){
				DisplayMap[i_new][j_new].muro=2;
			}else if(orient_old==2){
				DisplayMap[i_new][j_new].muro=1;
			}
			orient_new=DisplayMap[i_new][j_new].muro;

			//new
			x=DisplayMap[i_new][j_new].x;
			y=DisplayMap[i_new][j_new].y;
		
			
		
			
			DrawWall(x,y,DisplayMap[i_new][j_new].muro);


}

void MoveWall(i_old,j_old,i_new,j_new){
			//new
			uint16_t x=DisplayMap[i_new][j_new].x;
			uint16_t y=DisplayMap[i_new][j_new].y;
			//old
			uint16_t x_old=DisplayMap[i_old][j_old].x;
			uint16_t y_old=DisplayMap[i_old][j_old].y;
			
			uint16_t orient_old=DisplayMap[i_old][j_old].muro;
			uint16_t orient_new=DisplayMap[i_new][j_new].muro;
			
			if(DisplayMap[i_old][j_old].muro_pos==0){
			DeleteWall(x_old,y_old,orient_old);
			}
			DrawWall(x,y,DisplayMap[i_new][j_new].muro);
			

}
void CheckWinner(turno){

			if(players[turno].y_ind==0 && turno==2){
						
				LCD_Clear(White);
				GUI_Text(30,300, (unsigned char*) " Ha vinto il PLAYER 1  ",0x0000,White);
				EndGame=1;
				turno=0;
				reset_RIT();
				disable_RIT();
			
				StartGame(turno);
			}else if(players[turno].y_ind==12 && turno==1){
				turno=0;
				LCD_Clear(White);
				GUI_Text(30,300, (unsigned char*) " Ha vinto il PLAYER 2  ",0x0000,White);
				EndGame=1;
				turno=0;
				reset_RIT();
				disable_RIT();
				StartGame(turno);
		 	}

}

uint32_t encode_move(Move move) {
    uint32_t encodedMove = 0;
    encodedMove |= (move.playerID << 24);
    encodedMove |= (move.playerMoveOrWall << 20);
    encodedMove |= (move.wallOrientation << 16);
    encodedMove |= (move.y << 8);
    encodedMove |= move.x;
    return encodedMove;
}

void save_info(Move move){
	
	encode_move(move);
	

}






