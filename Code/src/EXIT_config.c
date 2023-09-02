#include "stm32f10x.h"
/*
    EXIT ������ ���õ� �ڵ���� �Լ�ȭ�Ͽ� ��Ÿ�� c����
*/

void EXTI_configuration()
{
    EXTI_InitTypeDef EXTI_InitStructure_KEY;

    /* Configure gpio as input : Button Left-WKUP */
    /* Connect EXTI Line to gpio pin */
    GPIO_EXTILineConfig(GPIOA, GPIO_Pin_0);

    /* Configure EXTI Line to generate an interrupt */
    EXTI_InitStructure_KEY.EXTI_Line    = EXTI_Line0;
    EXTI_InitStructure_KEY.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure_KEY.EXTI_Trigger = EXTI_Trigger_Rising_Falling ;
    EXTI_InitStructure_KEY.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure_KEY);

    /* Configure gpio as input : Button Right-USER */
    /* Connect EXTI Line to gpio pin */
    GPIO_EXTILineConfig(GPIOA, GPIO_Pin_1);

    /* Configure EXTI Line to generate an interrupt */  
    EXTI_InitStructure_KEY.EXTI_Line    = EXTI_Line1;
    EXTI_InitStructure_KEY.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure_KEY.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure_KEY.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure_KEY);
}