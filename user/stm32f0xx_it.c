/**
  ******************************************************************************
  * @file    IO_Toggle/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-March-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "main.h"
/** @addtogroup STM32F0_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup IO_Toggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void){    
		if(sysTickCountDown > 0) sysTickCountDown --;
		if(sysTickCountDownForEncoder > 0) sysTickCountDownForEncoder--;    
}

void EXTI4_15_IRQHandler(void) {
    //按下
    if(EXTI_GetITStatus(EXTI_Line4) != RESET) {
        EXTI_ClearITPendingBit(EXTI_Line4);
        position1Confirm = TRUE;
        while (!EncoderKey()) {
            delayInMilliSecondsForEncoder(10);
        }
    }

    //顺时针拧
    if((EXTI_GetITStatus(EXTI_Line5) != RESET) && (EXTI_GetITStatus(EXTI_Line6) == RESET)) {
        EXTI_ClearITPendingBit(EXTI_Line5);
        position1 ++;
        while (!EncoderA() || !EncoderB()) {
            delayInMilliSecondsForEncoder(10);
        }
        EXTI_ClearITPendingBit(EXTI_Line6);
    }

    //逆时针拧
    if((EXTI_GetITStatus(EXTI_Line5) == RESET) && (EXTI_GetITStatus(EXTI_Line6) != RESET)) {
        EXTI_ClearITPendingBit(EXTI_Line6);
        position1--;
        while (!EncoderA() || !EncoderB()) {
            delayInMilliSecondsForEncoder(10);
        }
        EXTI_ClearITPendingBit(EXTI_Line5);
    }
}


/*

*/
void USART1_IRQHandler(void)
{		
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
