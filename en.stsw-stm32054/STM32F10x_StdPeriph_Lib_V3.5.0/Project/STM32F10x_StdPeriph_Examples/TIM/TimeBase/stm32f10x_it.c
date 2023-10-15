/**
  ******************************************************************************
  * @file    TIM/TimeBase/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include <stdio.h>
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup TIM_TimeBase
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t capture = 0;
extern __IO uint16_t CCR1_Val;
extern __IO uint16_t CCR2_Val;
extern __IO uint16_t CCR3_Val;
extern __IO uint16_t CCR4_Val;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
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
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles TIM2 global interrupt request.
  * @param  None
  * @retval None
  */
int count = 0;
void TIM2_IRQHandler(void)
{
    //if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)//TIM_IT_Update) != RESET)
    //    {
            TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
            count++;
            if(count%2 == 1)
                {
                    GPIO_SetBits(GPIOB, GPIO_Pin_9);
                }
            else
                {
                    GPIO_ResetBits(GPIOB, GPIO_Pin_9);
                }
     //   }
}

int count_2 = 0;
void TIM3_IRQHandler(void)
{
    //if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)//TIM_IT_Update) != RESET)
    //    {
            TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
            count_2++;
            if(count_2%2 == 1)
                {
                    GPIO_SetBits(GPIOB, GPIO_Pin_5);
                    GPIO_SetBits(GPIOB, GPIO_Pin_8);
                }
            else
                {
                    GPIO_ResetBits(GPIOB, GPIO_Pin_5);
                    GPIO_ResetBits(GPIOB, GPIO_Pin_8);
                }
     //   }
}
/*
void TIM4_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)//TIM_IT_Update) != RESET)
        {
            TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

        }
}
*/

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles External line 0 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    // PB8�� �����ϴ� �ڵ�.
    GPIOB->ODR ^= GPIO_Pin_5;       // ^ �����ڴ� | �� �ٸ��� �� ��Ʈ�� 0�̰� �ٸ� ��Ʈ�� 1�� ��쿡�� 1. �������� 0
    printf("EXTI0_IRQHandler\n");
    /* Clear the  EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}

/*
    �ش� ��ġ�� EXTI1�� IRQHandler�Լ��� �ۼ��ϼ���.
    �ش� �ڵ�� �� EXTI0_IRQHandler() �Լ��� �����Ͻø� �˴ϴ�.

    // ��Ʈ
    void EXTI???????????_IRQHandler(void)
    {  
        if(EXTI_GetITStatus(EXTI_Line???????) != RESET)
        {
            // �ڵ� �ۼ�
            EXTI_ClearITPendingBit(EXTI_Line???????);
        }
    }
*/

/**
  * @brief  This function handles External lines 9 to 5 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{
#if defined (STM32F10X_HD_VL) || defined (STM32F10X_HD) || defined (STM32F10X_XL)
  if(EXTI_GetITStatus(EXTI_Line8) != RESET)
  {
    /* Toggle LED2 */
     //STM_EVAL_LEDToggle(LED2);

    /* Clear the  EXTI line 8 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line8);
  }
#else
  if(EXTI_GetITStatus(EXTI_Line9) != RESET)
  {
    /* Toggle LED2 */
     //STM_EVAL_LEDToggle(LED2);

    /* Clear the  EXTI line 9 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line9);
  }
#endif
}
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

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
