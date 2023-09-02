#include "stm32f10x.h"

/* for문으로 제작한 딜레이 함수 */
static void delay_int_count(volatile unsigned int nTime)
{
    for(; nTime>0; nTime--);
}
void delay_m(void)
{
    delay_int_count(30000/*6*/);
}
void delay_count(void)
{
    delay_int_count(10000/*6*/);
}

void delay_m_button(void)
{
    delay_int_count(806596/*6*/);
}
void delay_m_common(void)
{
    delay_int_count(806596/*6*/);
}

void delay_motor_speed(void)//90도 돌기
{
    delay_int_count(800000/*6*/);
}
void delay_test(void)
{
    delay_int_count(1206596/*6*/);

}

void delay_m_beep(void)
{
    delay_int_count(10000/*6*/);

}
void delay_m1(void)
{
    delay_int_count(247000/*6*/);
}
void delay_m2(void)
{
    delay_int_count(256000/*6*/);
}
void delay_m3(void)
{
    delay_int_count(66660000/*6*/);     // 150ml
}