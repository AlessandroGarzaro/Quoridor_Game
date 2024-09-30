/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               TouchPanel.c
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

/* Includes ------------------------------------------------------------------*/
#include "../GLCD/GLCD.h"
#include "../TouchPanel/TouchPanel.h"
#define MAX 3
//#include "../joystick/joystick.h"

/* Private variables ---------------------------------------------------------*/
Matrix 			matrix ;
Coordinate  display ;

/* Display Sample */	
Coordinate ScreenSample[3];

Coordinate ScreenSampleMatrix[4];
/* LCD Sample */
Coordinate DisplaySample[3] = {{ 45,  45},
															 { 45, 270},
                               {190, 190}} ;

Coordinate DisplaySampleTabs[3] = {{ 40,  260},
															 { 120, 260},
                               {200, 260}} ;

Player Player_Tmp ={0,0,0,0,0,0,0,0};															 
Player Player_One ={118,16,8,40,260,0x001F,6,0};
Player Player_Two ={118,220,8,200,260,0xF81F,6,12};
Information_Game Info_Game[100];

Player players[MAX]={{0,0,0,0,0,0,0,0},{118,16,8,40,260,0x001F,6,0},{118,220,8,200,260,0xF81F,6,12}};

												

Map   DisplayMap[13][13]={						
																			{{ 16,  16,0,0,0},
																			{ 16,  33,2,0,0},//M
																			{ 16,  50,0,0,0},
																			{ 16,  67,2,0,0},//M
																			{ 16,  84,0,0,0},
																			{ 16,  101,2,0,0},//M
																			{ 16, 118,0,0,0},
																			{ 16,  135,2,0,0},//M
																			{ 16, 152,0,0,0},
																			{ 16,  169,2,0,0},//M
																			{ 16, 186,0,0,0},
																			{ 16,  16,2,0,0},//M
																			{ 16, 220,0,0,0}
																			},//M
																			{
																				{ 33,  16,1,0,0},//M
																				{ 33,  33,1,0,0},//M
																				{ 33,  50,1,0,0},//M
																				{ 33,  67,1,0,0},//M
																				{ 33,  84,1,0,0},//M
																				{ 33,  101,1,0,0},//M
																				{ 33,  118,1,0,0},//M
																				{ 33,  135,1,0,0},//M
																				{ 33,  152,1,0,0},//M
																				{ 33,  169,1,0,0},//M
																				{ 33,  186,1,0,0},//M
																				{ 33,  203,1,0,0},//M
																				{ 33,  220,1,0,0},//M
																			},
																			{
																			{ 50,  16,0,0,0},
																			{ 16,  33,0,0,0},//M
																			{ 50,  50,0,0,0},
																			{ 16,  67,0,0,0},//M
																			{ 50,  84,0,0,0},
																			{ 16,  101,0,0,0},//M
																			{ 50, 118,0,0,1},
																			{ 16,  135,0,0,0},//M
																			{ 50, 152,0,0,0},
																			{ 16,  169,0,0,0},//M
																			{ 50, 186,0,0,0},
																			{ 16,  203,0,0,0},//M
																			{ 50, 220,0,0,1}
																			},
																			{
																				{ 67,  16,1,0,0},//M
																				{ 67,  33,1,0,0},//M
																				{ 67,  50,1,0,0},//M
																				{ 67,  67,1,0,0},//M
																				{ 67,  84,1,0,0},//M
																				{ 67,  101,1,0,0},//M
																				{ 67,  118,1,0,0},//M
																				{ 67,  135,1,0,0},//M
																				{ 67,  152,1,0,0},//M
																				{ 67,  169,1,0,0},//M
																				{ 67,  186,1,0,0},//M
																				{ 67,  203,1,0,0},//M
																				{ 67,  220,1,0,0},//M
																				
																			},
																			{
																			{ 84,  16,0,0,0},
																			{ 16,  33,2,0,0},//M
																			{ 84,  50,0,0,0},
																			{ 16,  67,2,0,0},//M
																			{ 84,  84,0,0,0},
																			{ 16,  101,2,0,0},//M
																			{ 84, 118,0,0,0},
																			{ 16,  135,2,0,0},//M
																			{ 84, 152,0,0,0},
																			{ 16,  169,2,0,0},//M
																			{ 84, 186,0,0,0},
																			{ 16,  203,2,0,0},//M
																			{ 84, 220,0,0,0}
																			},
																			{
																				{101, 16,1,0,0},//M
																				{101, 33,1,0,0},//M	
																				{101, 50,1,0,0},//M	
																				{101, 67,1,0,0},//M	
																				{101, 84,1,0,0},//M	
																				{101, 101,1,0,0},//M	
																				{101, 118,1,0,0},//M	
																				{101, 135,1,0,0},//M	
																				{101, 152,1,0,0},//M	
																				{101, 169,1,0,0},//M	
																				{101, 186,1,0,0},//M	
																				{101, 203,1,0,0},//M	
																				{101, 220,1,0,0},//M	
																			},
																		
																			{
																			{118,  16,0,0,0},
																			{ 16,  33,2,0,0},//M
																			{118,  50,0,0,0},
																			{ 16,  67,2,0,0},//M
																			{118,  84,0,0,0},
																			{ 16,  101,2,0,0},//M
																			{118, 118,0,0,0},
																			{ 16,  135,2,0,0},//M
																			{118, 152,0,0,0},
																			{ 16,  169,2,0,0},//M
																			{118, 186,0,0,0},
																			{ 16,  203,2,0,0},//M
																			{118, 220,0,0,0}
																			},
																				{
																				{ 135,  16,1,0,0},//M
																				{ 135,  33,1,0,0},//M
																				{ 135,  50,1,0,0},//M
																				{ 135,  67,1,0,0},//M
																				{ 135,  84,1,0,0},//M
																				{ 135,  101,1,0,0},//M
																				{ 135,  118,1,0,0},//M
																				{ 135,  135,1,0,0},//M
																				{ 135,  152,1,0,0},//M
																				{ 135,  169,1,0,0},//M
																				{ 135,  186,1,0,0},//M
																				{ 135,  203,1,0,0},//M
																				{ 135,  220,1,0,0},//M
																			},
																		
																			{
																			{152,  16,0,0,0},
																			{ 16,  33,2,0,0},//M
																			{152,  50,0,0,0},
																			{ 16,  67,2,0,0},//M
																			{152,  84,0,0,0},
																			{ 16,  101,2,0,0},//M
																			{152, 118,0,0,0},
																			{ 16,  135,2,0,0},//M
																			{152, 152,0,0,0},
																			{ 16,  169,2,0,0},//M
																			{152, 186,0,0,0},
																			{ 16,  203,2,0,0},//M
																			{152, 220,0,0,0}
																			},
																				{
																				{ 169,  16,1,0,0},//M
																				{ 169,  33,1,0,0},//M
																				{ 169,  50,1,0,0},//M
																				{ 169,  67,1,0,0},//M
																				{ 169,  84,1,0,0},//M
																				{ 169,  101,1,0,0},//M
																				{ 169,  118,1,0,0},//M
																				{ 169,  135,1,0,0},//M
																				{ 169,  152,1,0,0},//M
																				{ 169,  169,1,0,0},//M
																				{ 169,  186,1,0,0},//M
																				{ 169,  203,1,0,0},//M
																				{ 169,  220,1,0,0},//M
																				
																			},
																			{
																			{186,  16,0,0,0},
																			{ 16,  33,2,0,0},//M
																			{186,  50,0,0,0},
																			{ 16,  67,2,0,0},//M
																			{186,  84,0,0,0},
																			{ 16,  101,2,0,0},//M
																			{186, 118,0,0,0},
																			{ 16,  135,2,0,0},//M
																			{186, 152,0,0,0},
																			{ 16,  169,2,0,0},//M
																			{186, 186,0,0,0},
																			{ 16,  203,2,0,0},//M
																			{186, 220,0,0,0}
																		  },
																				{
																				{ 203,  16,1,0,0},//M
																				{ 203,  33,1,0,0},//M
																				{ 203,  50,1,0,0},//M
																				{ 203,  67,1,0,0},//M
																				{ 203,  84,1,0,0},//M
																				{ 203,  101,1,0,0},//M
																				{ 203,  118,1,0,0},//M
																				{ 203,  135,1,0,0},//M
																				{ 203,  152,1,0,0},//M
																				{ 203,  169,1,0,0},//M
																				{ 203,  186,1,0,0},//M
																				{ 203,  203,1,0,0},//M
																				{ 203,  220,1,0,0},//M
																				
																			},
																			{
																			{220,  16,0,0,0},
																			{ 16,  33,2,0,0},//M
																			{220,  50,0,0,0},
																			{ 16,  67,2,0,0},//M
																			{220,  84,0,0,0},
																			{ 16,  101,2,0,0},//M
																			{220, 118,0,0,0},
																			{ 16,  135,2,0,0},//M
																			{220, 152,0,0,0},
																			{ 16,  169,2,0,0},//M
																			{220, 186,0,0,0},
																			{ 16,  203,2,0,0},//M
																			{220, 220,0,0,0},
																		}
																		};																			
                               											 

/* Private define ------------------------------------------------------------*/
#define THRESHOLD 2  


/*******************************************************************************
* Function Name  : LPC17xx_SPI_SetSpeed
* Description    : Set clock speed to desired value
* Input          : - speed: speed
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void LPC17xx_SPI_SetSpeed (uint8_t speed)
{
	speed &= 0xFE;
	if ( speed < 2  ) {
		speed = 2 ;
	}
	LPC_SSP1->CPSR = speed;
}

/*******************************************************************************
* Function Name  : ADS7843_SPI_Init
* Description    : ADS7843 SPI 初始化
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void ADS7843_SPI_Init(void) 
{ 
	volatile uint32_t dummy;

	/* Initialize and enable the SSP1 Interface module. */
	LPC_SC->PCONP |= (1 << 10);          /* Enable power to SSPI1 block  */

	/* P0.7 SCK, P0.8 MISO, P0.9 MOSI are SSP pins. */
	LPC_PINCON->PINSEL0 &= ~((3UL<<14) | (3UL<<16) | (3UL<<18)) ; /* P0.7,P0.8,P0.9 cleared */
	LPC_PINCON->PINSEL0 |=  (2UL<<14) | (2UL<<16) | (2UL<<18);    /* P0.7 SCK1,P0.8 MISO1,P0.9 MOSI1 */

	/* PCLK_SSP1=CCLK */
	LPC_SC->PCLKSEL0 &= ~(3<<20);               /* PCLKSP0 = CCLK/4 (18MHz) */
	LPC_SC->PCLKSEL0 |=  (1<<20);               /* PCLKSP0 = CCLK   (72MHz) */

	LPC_SSP1->CR0  = 0x0007;                    /* 8Bit, CPOL=0, CPHA=0         */
	LPC_SSP1->CR1  = 0x0002;                    /* SSP1 enable, master          */

	LPC17xx_SPI_SetSpeed ( SPI_SPEED_500kHz );

	/* wait for busy gone */
	while( LPC_SSP1->SR & ( 1 << SSPSR_BSY ) );

	/* drain SPI RX FIFO */
	while( LPC_SSP1->SR & ( 1 << SSPSR_RNE ) )
	{
		dummy = LPC_SSP1->DR;
	}
} 

/*******************************************************************************
* Function Name  : TP_Init
* Description    : ADS7843端口初始化
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void TP_Init(void) 
{ 
  LPC_GPIO0->FIODIR |=  (1<<6);   /* P0.6 CS is output */
  LPC_GPIO2->FIODIR |=  (0<<13);  /* P2.13 TP_INT is input */
  TP_CS(1); 
  ADS7843_SPI_Init(); 
} 

/*******************************************************************************
* Function Name  : DelayUS
* Description    : 延时1us
* Input          : - cnt: 延时值
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void DelayUS(uint32_t cnt)
{
  uint32_t i;
  for(i = 0;i<cnt;i++)
  {
     uint8_t us = 12; /* 设置值为12，大约延1微秒 */    
     while (us--)     /* 延1微秒	*/
     {
       ;   
     }
  }
}


/*******************************************************************************
* Function Name  : WR_CMD
* Description    : 向 ADS7843写数据
* Input          : - cmd: 传输的数据
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static uint8_t WR_CMD (uint8_t cmd)  
{ 
  uint8_t byte_r;

  while (LPC_SSP1->SR & (1 << SSPSR_BSY) ); 	     /* Wait for transfer to finish */
  LPC_SSP1->DR = cmd;
  while (LPC_SSP1->SR & (1 << SSPSR_BSY) ); 	     /* Wait for transfer to finish */
  while( !( LPC_SSP1->SR & ( 1 << SSPSR_RNE ) ) ); /* Wait until Rx FIFO not empty */
  byte_r = LPC_SSP1->DR;

  return byte_r;                                     /* Return received value */
} 



/*******************************************************************************
* Function Name  : RD_AD
* Description    : 读取ADC值
* Input          : None
* Output         : None
* Return         : ADS7843返回二字节数据
* Attention		 : None
*******************************************************************************/
static int RD_AD(void)  
{ 
  unsigned short buf,temp; 

  temp = WR_CMD(0x00);
  buf = temp<<8; 
  DelayUS(1); 
  temp = WR_CMD(0x00);;
  buf |= temp; 
  buf>>=4; 
  buf&=0xfff; 
  return buf; 
} 


/*******************************************************************************
* Function Name  : Read_X
* Description    : 读取ADS7843通道X+的ADC值 
* Input          : None
* Output         : None
* Return         : ADS7843返回通道X+的ADC值
* Attention		 : None
*******************************************************************************/
int Read_X(void)  
{  
  int i; 
  TP_CS(0); 
  DelayUS(1); 
  WR_CMD(CHX); 
  DelayUS(1); 
  i=RD_AD(); 
  TP_CS(1); 
  return i;    
} 

/*******************************************************************************
* Function Name  : Read_Y
* Description    : 读取ADS7843通道Y+的ADC值
* Input          : None
* Output         : None
* Return         : ADS7843返回通道Y+的ADC值
* Attention		 : None
*******************************************************************************/
int Read_Y(void)  
{  
  int i; 
  TP_CS(0); 
  DelayUS(1); 
  WR_CMD(CHY); 
  DelayUS(1); 
  i=RD_AD(); 
  TP_CS(1); 
  return i;     
} 


/*******************************************************************************
* Function Name  : TP_GetAdXY
* Description    : 读取ADS7843 通道X+ 通道Y+的ADC值
* Input          : None
* Output         : None
* Return         : ADS7843返回 通道X+ 通道Y+的ADC值 
* Attention		 : None
*******************************************************************************/
void TP_GetAdXY(int *x,int *y)  
{ 
  int adx,ady; 
  adx=Read_X(); 
  DelayUS(1); 
  ady=Read_Y(); 
  *x=adx; 
  *y=ady; 
} 

/*******************************************************************************
* Function Name  : TP_DrawPoint
* Description    : 在指定座标画点
* Input          : - Xpos: Row Coordinate
*                  - Ypos: Line Coordinate 
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void TP_DrawPoint(uint16_t Xpos,uint16_t Ypos)
{
  LCD_SetPoint(Xpos,Ypos,White);  
}	

/*******************************************************************************
* Function Name  : DrawCross
* Description    : 在指定座标画十字准星
* Input          : - Xpos: Row Coordinate
*                  - Ypos: Line Coordinate 
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void DrawCross(uint16_t Xpos,uint16_t Ypos)
{
  LCD_DrawLine(Xpos-15,Ypos,Xpos-2,Ypos,0xffff);
  LCD_DrawLine(Xpos+2,Ypos,Xpos+15,Ypos,0xffff);
  LCD_DrawLine(Xpos,Ypos-15,Xpos,Ypos-2,0xffff);
  LCD_DrawLine(Xpos,Ypos+2,Xpos,Ypos+15,0xffff);
  
  LCD_DrawLine(Xpos-15,Ypos+15,Xpos-7,Ypos+15,RGB565CONVERT(184,158,131));
  LCD_DrawLine(Xpos-15,Ypos+7,Xpos-15,Ypos+15,RGB565CONVERT(184,158,131));

  LCD_DrawLine(Xpos-15,Ypos-15,Xpos-7,Ypos-15,RGB565CONVERT(184,158,131));
  LCD_DrawLine(Xpos-15,Ypos-7,Xpos-15,Ypos-15,RGB565CONVERT(184,158,131));

  LCD_DrawLine(Xpos+7,Ypos+15,Xpos+15,Ypos+15,RGB565CONVERT(184,158,131));
  LCD_DrawLine(Xpos+15,Ypos+7,Xpos+15,Ypos+15,RGB565CONVERT(184,158,131));

  LCD_DrawLine(Xpos+7,Ypos-15,Xpos+15,Ypos-15,RGB565CONVERT(184,158,131));
  LCD_DrawLine(Xpos+15,Ypos-15,Xpos+15,Ypos-7,RGB565CONVERT(184,158,131));	  	
}
/*******************************************************************************
* Function Name  : DrawBoard
* Description    : 在指定座标画十字准星
* Input          : - Xpos: Row Coordinate
*                  - Ypos: Line Coordinate 
* Output         : None
* Return         : None
* Attention		 : None
Black
************/
void DrawBoard(uint16_t Xpos,uint16_t Ypos)
{
	// disegno i vari quadrati
	LCD_DrawLine(Xpos-15,Ypos+15,Xpos,Ypos+15,0x0000);
  LCD_DrawLine(Xpos-15,Ypos,Xpos-15,Ypos+15,0x0000);

  LCD_DrawLine(Xpos-15,Ypos-15,Xpos,Ypos-15,0x0000);
  LCD_DrawLine(Xpos-15,Ypos,Xpos-15,Ypos-15,0x0000);

  LCD_DrawLine(Xpos,Ypos+15,Xpos+15,Ypos+15,0x0000);
  LCD_DrawLine(Xpos+15,Ypos,Xpos+15,Ypos+15,0x0000);

  LCD_DrawLine(Xpos,Ypos-15,Xpos+15,Ypos-15,0x0000);
  LCD_DrawLine(Xpos+15,Ypos-15,Xpos+15,Ypos,0x0000);
	
	//Coordinate DisplaySampleTabs[3] = {{ 40,  260},
			//														 { 120, 260},
          //                 			    {200, 260}} ;
}

void DrawTab(uint16_t Xpos,uint16_t Ypos)
{
	// disegno i vari quadrati
	LCD_DrawLine(Xpos-35,Ypos+35,Xpos,Ypos+35,0x0000);
  LCD_DrawLine(Xpos-35,Ypos,Xpos-35,Ypos+35,0x0000);

  LCD_DrawLine(Xpos-35,Ypos-15,Xpos,Ypos-15,0x0000);
  LCD_DrawLine(Xpos-35,Ypos,Xpos-35,Ypos-15,0x0000);

  LCD_DrawLine(Xpos,Ypos-15,Xpos+35,Ypos-15,0x0000);
  LCD_DrawLine(Xpos+35,Ypos,Xpos+35,Ypos-15,0x0000);

  LCD_DrawLine(Xpos,Ypos+35,Xpos+35,Ypos+35,0x0000);
  LCD_DrawLine(Xpos+35,Ypos+35,Xpos+35,Ypos,0x0000);
	
	GUI_Text(30,300, (unsigned char*) "Click to start game",0xffff,Black); 
}

/*******************************************************************************
* Function Name  : DrawWall
* Description    : 在指定座标画十字准星
* Input          : - Xpos: Row Coordinate
*                  - Ypos: Line Coordinate 
* Output         : None
* Return         : None
* Attention		 : None
Black
************/
void DrawWall(uint16_t Xpos,uint16_t Ypos,int orientamento){

		
		//int i,j;
	  
		if(orientamento==1){
			LCD_DrawLine( Xpos, Ypos-24, Xpos, Ypos+24 ,Red);
		}else if(orientamento==2){
		
			LCD_DrawLine( Xpos-24, Ypos, Xpos+24, Ypos ,Red);
		
		}

}

/*******************************************************************************
* Function Name  : DeleteWall
* Description    : 在指定座标画十字准星
* Input          : - Xpos: Row Coordinate
*                  - Ypos: Line Coordinate 
* Output         : None
* Return         : None
* Attention		 : None
Black
************/

void DeleteWall(uint16_t Xpos,uint16_t Ypos,int orientamento){

		
		//int i,j;
	  
		if(orientamento==1){
			LCD_DrawLine( Xpos, Ypos-24, Xpos, Ypos+24 ,White);
		}else if(orientamento==2){
		
			LCD_DrawLine( Xpos-24, Ypos, Xpos+24, Ypos ,White);
		
		}

}



/*******************************************************************************
* Function Name  : DrawCross
* Description    : 在指定座标画十字准星
* Input          : - Xpos: Row Coordinate
*                  - Ypos: Line Coordinate 
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void DeleteCross(uint16_t Xpos,uint16_t Ypos)
{
  LCD_DrawLine(Xpos-15,Ypos,Xpos-2,Ypos,0x0000);
  LCD_DrawLine(Xpos+2,Ypos,Xpos+15,Ypos,0x0000);
  LCD_DrawLine(Xpos,Ypos-15,Xpos,Ypos-2,0x0000);
  LCD_DrawLine(Xpos,Ypos+2,Xpos,Ypos+15,0x0000);
  
  LCD_DrawLine(Xpos-15,Ypos+15,Xpos-7,Ypos+15,RGB565CONVERT(0,0,0));
  LCD_DrawLine(Xpos-15,Ypos+7,Xpos-15,Ypos+15,RGB565CONVERT(0,0,0));

  LCD_DrawLine(Xpos-15,Ypos-15,Xpos-7,Ypos-15,RGB565CONVERT(0,0,0));
  LCD_DrawLine(Xpos-15,Ypos-7,Xpos-15,Ypos-15,RGB565CONVERT(0,0,0));

  LCD_DrawLine(Xpos+7,Ypos+15,Xpos+15,Ypos+15,RGB565CONVERT(0,0,0));
  LCD_DrawLine(Xpos+15,Ypos+7,Xpos+15,Ypos+15,RGB565CONVERT(0,0,0));

  LCD_DrawLine(Xpos+7,Ypos-15,Xpos+15,Ypos-15,RGB565CONVERT(0,0,0));
  LCD_DrawLine(Xpos+15,Ypos-15,Xpos+15,Ypos-7,RGB565CONVERT(0,0,0));	  	
}

/*******************************************************************************
* Function Name  : Draw_Player
* Description    : 得到滤波之后的X Y
* Input          : None
* Output         : None
* Return         : Coordinate结构体地址
* Attention		 : None
*******************************************************************************/
void DrawPlayer(uint16_t Xpos,uint16_t Ypos,uint16_t colour)
{
  LCD_DrawLine(Xpos-15,Ypos,Xpos-2,Ypos,colour);
  LCD_DrawLine(Xpos+2,Ypos,Xpos+15,Ypos,colour);
  LCD_DrawLine(Xpos,Ypos-15,Xpos,Ypos-2,colour);
  LCD_DrawLine(Xpos,Ypos+2,Xpos,Ypos+15,colour);
  
  LCD_DrawLine(Xpos-15,Ypos+15,Xpos-7,Ypos+15,colour);
  LCD_DrawLine(Xpos-15,Ypos+7,Xpos-15,Ypos+15,colour);

  LCD_DrawLine(Xpos-15,Ypos-15,Xpos-7,Ypos-15,colour);
  LCD_DrawLine(Xpos-15,Ypos-7,Xpos-15,Ypos-15,colour);

  LCD_DrawLine(Xpos+7,Ypos+15,Xpos+15,Ypos+15,colour);
  LCD_DrawLine(Xpos+15,Ypos+7,Xpos+15,Ypos+15,colour);

  LCD_DrawLine(Xpos+7,Ypos-15,Xpos+15,Ypos-15,colour);
  LCD_DrawLine(Xpos+15,Ypos-15,Xpos+15,Ypos-7,colour);	  	
}






/*******************************************************************************
* Function Name  : Read_Ads7846
* Description    : 得到滤波之后的X Y
* Input          : None
* Output         : None
* Return         : Coordinate结构体地址
* Attention		 : None
*******************************************************************************/
Coordinate *Read_Ads7846(void)
{
  static Coordinate  screen;
  int m0,m1,m2,TP_X[1],TP_Y[1],temp[3];
  uint8_t count=0;
  int buffer[2][9]={{0},{0}}; 
  
	do{		   
    TP_GetAdXY(TP_X,TP_Y);  
		buffer[0][count]=TP_X[0];  
		buffer[1][count]=TP_Y[0];
		count++; 
	}while(!TP_INT_IN&& count<9);  
  
	if(count==9){  
		temp[0]=(buffer[0][0]+buffer[0][1]+buffer[0][2])/3;
		temp[1]=(buffer[0][3]+buffer[0][4]+buffer[0][5])/3;
		temp[2]=(buffer[0][6]+buffer[0][7]+buffer[0][8])/3;
		m0=temp[0]-temp[1];
		m1=temp[1]-temp[2];
		m2=temp[2]-temp[0];
		m0=m0>0?m0:(-m0);
    m1=m1>0?m1:(-m1);
		m2=m2>0?m2:(-m2);
		if( m0>THRESHOLD  &&  m1>THRESHOLD  &&  m2>THRESHOLD ) return 0;
		if(m0<m1)
		{
			if(m2<m0) 
				screen.x=(temp[0]+temp[2])/2;
			else 
				screen.x=(temp[0]+temp[1])/2;	
		}
		else if(m2<m1) 
			screen.x=(temp[0]+temp[2])/2;
		else 
			screen.x=(temp[1]+temp[2])/2;

    temp[0]=(buffer[1][0]+buffer[1][1]+buffer[1][2])/3;
		temp[1]=(buffer[1][3]+buffer[1][4]+buffer[1][5])/3;
		temp[2]=(buffer[1][6]+buffer[1][7]+buffer[1][8])/3;
	
		m0=temp[0]-temp[1];
		m1=temp[1]-temp[2];
		m2=temp[2]-temp[0];
		m0=m0>0?m0:(-m0);
		m1=m1>0?m1:(-m1);
		m2=m2>0?m2:(-m2);
		if(m0>THRESHOLD&&m1>THRESHOLD&&m2>THRESHOLD) return 0;

		if(m0<m1)
		{
			if(m2<m0) 
				screen.y=(temp[0]+temp[2])/2;
			else 
				screen.y=(temp[0]+temp[1])/2;	
			}
		else if(m2<m1) 
			 screen.y=(temp[0]+temp[2])/2;
		else
			 screen.y=(temp[1]+temp[2])/2;

		return &screen;
	}  
  return 0; 
}
	 
/*******************************************************************************
* Function Name  : setCalibrationMatrix
* Description    : computation of K A B C D E F
* Input          : None
* Output         : None
* Return         : 
* Attention		 : None
*******************************************************************************/
uint8_t setCalibrationMatrix( Coordinate * displayPtr,
                          Coordinate * screenPtr,
                          Matrix * matrixPtr)
{

  uint8_t retTHRESHOLD = 0 ;
  
  matrixPtr->Divider = ((screenPtr[0].x - screenPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) - 
                       ((screenPtr[1].x - screenPtr[2].x) * (screenPtr[0].y - screenPtr[2].y)) ;
  if( matrixPtr->Divider == 0 )
  {
    retTHRESHOLD = 1;
  }
  else
  {
    matrixPtr->An = ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) - 
                    ((displayPtr[1].x - displayPtr[2].x) * (screenPtr[0].y - screenPtr[2].y)) ;
	  matrixPtr->Bn = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].x - displayPtr[2].x)) - 
                    ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].x - screenPtr[2].x)) ;
    matrixPtr->Cn = (screenPtr[2].x * displayPtr[1].x - screenPtr[1].x * displayPtr[2].x) * screenPtr[0].y +
                    (screenPtr[0].x * displayPtr[2].x - screenPtr[2].x * displayPtr[0].x) * screenPtr[1].y +
                    (screenPtr[1].x * displayPtr[0].x - screenPtr[0].x * displayPtr[1].x) * screenPtr[2].y ;
    matrixPtr->Dn = ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].y - screenPtr[2].y)) - 
                    ((displayPtr[1].y - displayPtr[2].y) * (screenPtr[0].y - screenPtr[2].y)) ;
    matrixPtr->En = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].y - displayPtr[2].y)) - 
                    ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].x - screenPtr[2].x)) ;
    matrixPtr->Fn = (screenPtr[2].x * displayPtr[1].y - screenPtr[1].x * displayPtr[2].y) * screenPtr[0].y +
                    (screenPtr[0].x * displayPtr[2].y - screenPtr[2].x * displayPtr[0].y) * screenPtr[1].y +
                    (screenPtr[1].x * displayPtr[0].y - screenPtr[0].x * displayPtr[1].y) * screenPtr[2].y ;
  }
  return( retTHRESHOLD ) ;
}

/*******************************************************************************
* Function Name  : getDisplayPoint
* Description    : using K A B C D E F 
* Input          : None
* Output         : None
* Return         : 返回1表示成功 0失败
* Attention		 : None
*******************************************************************************/
uint8_t getDisplayPoint(Coordinate * displayPtr,
                     Coordinate * screenPtr,
                     Matrix * matrixPtr )
{
  uint8_t retTHRESHOLD = 1 ;

	if ( screenPtr != 0){
		if( matrixPtr->Divider != 0 )
		{
			/* XD = AX+BY+C */        
			displayPtr->x = ( (matrixPtr->An * screenPtr->x) + 
												(matrixPtr->Bn * screenPtr->y) + 
												 matrixPtr->Cn 
											) / matrixPtr->Divider ;
		/* YD = DX+EY+F */        
			displayPtr->y = ( (matrixPtr->Dn * screenPtr->x) + 
												(matrixPtr->En * screenPtr->y) + 
												 matrixPtr->Fn 
											) / matrixPtr->Divider ;
		}
		else
		{
			retTHRESHOLD = 0;
		}
	}
	else{
		retTHRESHOLD = 0;
	}
  return(retTHRESHOLD);
} 




/*******************************************************************************
* Function Name  : TouchPanel_Calibrate
* Description    : 校准触摸屏
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/


/*******************************************************************************
* Function Name  : DrawSquare
* Description    : 校准触摸屏
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/

void DrawSquare(uint16_t Xpos,uint16_t Ypos,uint16_t colour){
		
		int i,j;
	  
		for(i=-14;i<15;i++){
			for(j=-14;j<15;j++){
				LCD_SetPoint(Xpos+i,Ypos+j,colour); 
			}
		}
	/*for(i=-15, ;i<15;i++){
			for(j=-15;i<15;j++){
				LCD_SetPoint(Xpos+i,Ypos+j,colour); 
			}
		}*/

}

/*******************************************************************************
* Function Name  : DrawMatrix
* Description    : 校准触摸屏
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/

void DrawMatrix(void){

	uint8_t i,j;
//  Coordinate * Ptr;
	char nWall[5] = "";
	
	LCD_Clear(White);
	
  for(i=0;i<13;i+=2)
  {
		for(j=0;j<13;j+=2){
			
   #ifndef SIMULATOR
	 DelayUS(1000 * 5);
	 #endif	
   DrawBoard(DisplayMap[i][j].x,DisplayMap[i][j].y);
   
   /*do
   {
   Ptr = Read_Ads7846();
   }
   while( Ptr == (void*)0 );
   ScreenSampleMatrix[i].x = Ptr->x; ScreenSampleMatrix[i].y = Ptr->y;
  */
		}
	}
	for(i=0;i<3;i++){
	
		DrawTab(DisplaySampleTabs[i].x,DisplaySampleTabs[i].y);
		 
	}
	GUI_Text(40,240, (unsigned char*) "WALL",0x0000,White);
	GUI_Text(120,240, (unsigned char*) "TIME",0x0000,White);
	GUI_Text(200,240, (unsigned char*) "WALL",0x0000,White);
	GUI_Text(30,300, (unsigned char*) "      Inizia        ",0x0000,White);
	GUI_Text(30,300, (unsigned char*) "                    ",0x0000,White);
	GUI_Text(30,300, (unsigned char*) "     Click INT0     ",0x0000,White);		
		
	
			sprintf(nWall,"%4d",players[1].wall);
			GUI_Text(40,260, (uint8_t *) nWall, 0x0000, White);
			GUI_Text(200,260, (uint8_t *) nWall, 0x0000, White);
	
	DrawPlayer(Player_One.x,Player_One.y,Player_One.colour);
	DrawPlayer(Player_Two.x,Player_Two.y,Player_Two.colour);

}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
