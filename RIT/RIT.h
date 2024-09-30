/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           RIT.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_RIT, funct_RIT, IRQ_RIT .c files
** Correlated files:    lib_RIT.c, funct_RIT.c, IRQ_RIT.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#ifndef __RIT_H
#define __RIT_H
#include "../Touchpanel/Touchpanel.h"

/* init_RIT.c */
extern uint32_t init_RIT( uint32_t RITInterval );
extern void enable_RIT( void );
extern void disable_RIT( void );
extern void reset_RIT( void );
/* IRQ_RIT.c */
extern void RIT_IRQHandler (void);

void Turno(Player player);
void StartGame(int turno);
void DrawAround(Player player,uint16_t Color);
void DrawWallPlayer(int turno,int i,int j);
void MoveWall(int i_old,int j_old,int ti_new,int j_new);
void TurnWall(int i_old,int j_old,int ti_new,int j_new);
void CheckWinner(int turno);
void UpdateValour(int turno);
void save_info(Move move);
#endif /* end __RIT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
