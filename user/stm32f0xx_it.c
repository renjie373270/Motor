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

void WWDG_IRQHandler(void){}
void PVD_IRQHandler(void){}
void RTC_IRQHandler(void){}
void FLASH_IRQHandler(void){}
void RCC_IRQHandler(void){}
void EXTI0_1_IRQHandler(void){}
void EXTI2_3_IRQHandler(void){}

//433MHz÷–∂œ
void EXTI4_15_IRQHandler(void){

    if(EXTI_GetITStatus(EXTI_Line12) != RESET) {
        EXTI_ClearITPendingBit(EXTI_Line12);
        rf_receive_data();
    }
}
void TS_IRQHandler(void){}
void DMA1_Channel1_IRQHandler(void){}
void DMA1_Channel2_3_IRQHandler(void){}
void DMA1_Channel4_5_IRQHandler(void){}
void ADC1_COMP_IRQHandler(void){}
void TIM1_BRK_UP_TRG_COM_IRQHandler(void){}
void TIM1_CC_IRQHandler(void){}
void TIM2_IRQHandler(void){}
void TIM3_IRQHandler(void){}
void TIM6_DAC_IRQHandler(void){}
void TIM14_IRQHandler(void){}
void TIM15_IRQHandler(void){}
void TIM16_IRQHandler(void){}
void TIM17_IRQHandler(void){}
void I2C1_IRQHandler(void){}
void I2C2_IRQHandler(void){}
void SPI1_IRQHandler(void){}
void SPI2_IRQHandler(void){}
void USART1_IRQHandler(void){}
void USART2_IRQHandler(void){}
void CEC_IRQHandler(void){}
	