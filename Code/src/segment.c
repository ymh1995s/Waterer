#include "stm32f10x.h"

/* 4digit segment�� �ڸ����� ���� �� ��ȣ ���� */
#define SEG_dig_4        	GPIO_Pin_4
#define SEG_dig_3        	GPIO_Pin_5
#define SEG_dig_2        	GPIO_Pin_6
#define SEG_dig_1        	GPIO_Pin_7

/* 4digit segment�� ���ڰ�(0~9)�� ���� �� ��ȣ ���� */
#define A_                  GPIO_Pin_0
#define B_                  GPIO_Pin_1
#define C_                  GPIO_Pin_2
#define D_                  GPIO_Pin_3



/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/* 4digit segment�� ��� ���� ���� ������ �Լ� */
void GPIO_4digit_segment_0(void)
{
    // 0 ���
    GPIO_ResetBits(GPIOC, A_ | B_ | C_ | D_);
}

void GPIO_4digit_segment_1(void)
{
    // 1 ���
    GPIO_SetBits(GPIOC, A_);
    GPIO_ResetBits(GPIOC, B_ | C_ | D_);
}

void GPIO_4digit_segment_2(void)
{
    // 2 ���
    GPIO_SetBits(GPIOC,  B_);
    GPIO_ResetBits(GPIOC, A_ | C_ | D_);
}
void GPIO_4digit_segment_3(void)
{
    // 3 ���
    GPIO_SetBits(GPIOC, A_ | B_);
    GPIO_ResetBits(GPIOC, C_ | D_);
}
void GPIO_4digit_segment_4(void)
{
    // 4 ���
    GPIO_SetBits(GPIOC, C_);
    GPIO_ResetBits(GPIOC, A_| B_ | D_);
}

void GPIO_4digit_segment_5(void)
{
    // 5 ���
    GPIO_SetBits(GPIOC, A_ | C_);
    GPIO_ResetBits(GPIOC, B_ | D_);
}

void GPIO_4digit_segment_6(void)
{
    // 6 ���
    GPIO_SetBits(GPIOC, B_ | C_);
    GPIO_ResetBits(GPIOC, A_ | D_);
}

void GPIO_4digit_segment_7(void)
{
    // 7 ���
    GPIO_SetBits(GPIOC, A_ | B_ | C_);
    GPIO_ResetBits(GPIOC, D_);
}

void GPIO_4digit_segment_8(void)
{
    // 8 ���
    GPIO_SetBits(GPIOC, D_);
    GPIO_ResetBits(GPIOC, A_ |B_ | C_);
}

void GPIO_4digit_segment_9(void)
{
    // 9 ���
    GPIO_SetBits(GPIOC, A_ | D_);
    GPIO_ResetBits(GPIOC, B_ | C_);
}


/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/* 4digit�� �ڸ����� �����ϴ� �Լ� */
void GPIO_4digit_segment_DIG_1(void)
{
    GPIO_ResetBits(GPIOC, SEG_dig_2 | SEG_dig_3 | SEG_dig_4);       // �ѱ�
    GPIO_SetBits(GPIOC, SEG_dig_1);                                 // ����
}

void GPIO_4digit_segment_DIG_2(void)
{
    GPIO_ResetBits(GPIOC, SEG_dig_1 | SEG_dig_3 | SEG_dig_4);       // �ѱ�
    GPIO_SetBits(GPIOC, SEG_dig_2);                                 // ����
}

void GPIO_4digit_segment_DIG_3(void)
{
    GPIO_ResetBits(GPIOC, SEG_dig_1 | SEG_dig_2 | SEG_dig_4);       // �ѱ�
    GPIO_SetBits(GPIOC, SEG_dig_3);                                 // ����
}

void GPIO_4digit_segment_DIG_4(void)
{
    GPIO_ResetBits(GPIOC, SEG_dig_1 | SEG_dig_2 | SEG_dig_3);       // �ѱ�
    GPIO_SetBits(GPIOC, SEG_dig_4);                                 // ����
}