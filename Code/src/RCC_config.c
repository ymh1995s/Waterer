#include "stm32f10x.h"
#include "SPI_define.h"
/*
    RCC ������ ���õ� �ڵ���� �Լ�ȭ�Ͽ� ��Ÿ�� c����
*/

void RCC_Configuration(void)
{


    // TIM2 clock enable 
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    // GPIOA ENABLE
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // GPIOB ENABLE
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    /* Enable AFIO clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    /* Enable USART1 clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /* Enable USART3 clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);


    // SPI clocks
    RCC_APB2PeriphClockCmd(SPIy_CLK, ENABLE);	//SPI1
    RCC_APB1PeriphClockCmd(SPIz_CLK, ENABLE);	//SPI2
}