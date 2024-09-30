/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               TouchPanel.h
** Descriptions:            The TouchPanel application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

#ifndef _TOUCHPANEL_H_
#define _TOUCHPANEL_H_

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"

/* Private typedef -----------------------------------------------------------*/
typedef	struct POINT 
{
   uint16_t x;
   uint16_t y;
}Coordinate;
typedef	struct CASELLA 
{
   uint16_t x;
   uint16_t y;
	 uint16_t muro; // 1 verticale 2 orizzontale
	 uint16_t muro_pos;
   uint16_t player;
}Map;
typedef	struct PLAYER 
{
   uint16_t x;
   uint16_t y;
	 uint8_t wall;
	uint16_t x_TabWall;
	uint16_t y_TabWall;
	uint16_t colour;
	uint16_t x_ind;
	uint16_t y_ind;
}Player;




typedef struct Matrix 
{						
long double An,  
            Bn,     
            Cn,   
            Dn,    
            En,    
            Fn,     
            Divider ;
} Matrix ;

typedef struct GAME_INFORMATION
{
 uint32_t info;
} Information_Game;

typedef struct move{
    unsigned int playerID : 8;           // 8 bits for Player ID
    unsigned int playerMoveOrWall : 4;   // 4 bits for Player Move or Wall Placement
    unsigned int wallOrientation : 4;    // 4 bits for Wall Orientation
    unsigned int y : 8;                  // 8 bits for Y coordinate
    unsigned int x : 8;                  // 8 bits for X coordinate
} Move;



/* Private variables ---------------------------------------------------------*/
extern Coordinate ScreenSample[3];
extern Coordinate ScreenSampleMatrix[4];

extern Coordinate DisplaySample[3];

extern Coordinate DisplaySampleTabs[3];
extern Map   DisplayMap[13][13];
extern Information_Game Info_Game[100];
extern Matrix 		matrix ;
extern Coordinate display ;
extern Player Player_One;
extern Player Player_Two;
extern Player players[3];

#define	CHX 	        0x90 	/* 通道Y+的选择控制字 */	
#define	CHY 	        0xd0	/* 通道X+的选择控制字 */

#define SSPSR_RNE       2
#define SSPSR_BSY       4

/* bit-frequency = PCLK / CPSR */
#define SPI_SPEED_4MHz    18 	  /* 4MHz */
#define SPI_SPEED_2MHz    36 	  /* 2MHz */
#define	SPI_SPEED_1MHz	  72	  /* 1MHz */
#define	SPI_SPEED_500kHz  144	  /* 500kHz */
#define SPI_SPEED_400kHz  180	  /* 400kHz */


#define TP_CS(a)	if (a)	\
					LPC_GPIO0->FIOSET = (1<<6);\
					else		\
					LPC_GPIO0->FIOCLR = (1<<6)

#define TP_INT_IN   ( LPC_GPIO2->FIOPIN & (1<<13) ) 

/* Private function prototypes -----------------------------------------------*/				
void TP_Init(void);	
Coordinate *Read_Ads7846(void);
void TouchPanel_Calibrate(void);
void DrawMatrix(void);
void DrawCross(uint16_t Xpos,uint16_t Ypos);
void DrawBoard(uint16_t Xpos,uint16_t Ypos);
void DrawTab(uint16_t Xpos,uint16_t Ypos);
void DrawPlayer(uint16_t Xpos,uint16_t Ypos,uint16_t colour);
void DrawWall(uint16_t Xpos,uint16_t Ypos,int orientamento);
void DeleteWall(uint16_t Xpos,uint16_t Ypos,int orientamento);
void TP_DrawPoint(uint16_t Xpos,uint16_t Ypos);
void DrawSquare(uint16_t Xpos,uint16_t Ypos,uint16_t colour);
uint8_t setCalibrationMatrix( Coordinate * displayPtr,Coordinate * screenPtr,Matrix * matrixPtr);
uint8_t getDisplayPoint(Coordinate * displayPtr,Coordinate * screenPtr,Matrix * matrixPtr );

#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/


