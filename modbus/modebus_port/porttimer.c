/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: porttimer.c,v 1.1 2006/08/22 21:35:13 wolti Exp $
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"
 
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "tim.h"


 
/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBPortTimersInit( USHORT usTim1Timerout50us )
{
  // Set the Auto-Reload Register (ARR)
  // usTim1Timerout50us is the count value calculated by FreeMODBUS based on the baud rate, representing the 3.5 character time (as a multiple of 50μs).
  // Note: Ensure that the Timer Prescaler in CubeMX is configured so that the counter frequency is 20kHz (i.e., 50us/tick).
  // If the Prescaler in CubeMX differs, you need to modify the CubeMX configuration to match the 50us base.
  __HAL_TIM_SET_AUTORELOAD(&htim7, usTim1Timerout50us - 1);
    
  return TRUE;
}
 
 
void
vMBPortTimersEnable(  )
{
  /* 1. Clear the current counter value to restart timing from zero */
    __HAL_TIM_SET_COUNTER(&htim7, 0);
    
    /* 2. Clear any pending update interrupt flags to prevent immediate interrupt entry */
    __HAL_TIM_CLEAR_FLAG(&htim7, TIM_FLAG_UPDATE);
    
    /* 3. Start the timer interrupt */
    HAL_TIM_Base_Start_IT(&htim7);
}
 
void
vMBPortTimersDisable(  )
{
  /* Disable any pending timers. */
  HAL_TIM_Base_Stop_IT(&htim7);
}
 
/* Create an ISR which is called whenever the timer has expired. This function
* must then call pxMBPortCBTimerExpired( ) to notify the protocol stack that
* the timer has expired.
*/ 
static void prvvTIMERExpiredISR( void )
{
( void )pxMBPortCBTimerExpired(  );
}

void TIM7_DAC_IRQHandler(void)
{
	if(__HAL_TIM_GET_FLAG(&htim7,TIM_FLAG_UPDATE))
	{
		//Clear the update flag
		__HAL_TIM_CLEAR_FLAG(&htim7,TIM_FLAG_UPDATE);
		//Notify Modbus that 3.5 character times have elapsed
		prvvTIMERExpiredISR();
	}
}

