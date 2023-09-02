#include "stm32f10x.h"

void RCC_Configuration(void) {
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//TIM2�� ENABLE,, TIM1�� APB2(~72MHz)�̰� ������ APB1(~36MHz)�̴�.
}							//���� TIM2,3,4��� ENABLE�Ϸ���
							//RCC_APB1...(RCC_APB1Periph_TIM2 | .. _TIM3 | .. _TIM4, ENALBE); �� �ϸ� ��.

void NVIC_Configuration(void){

//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//�̰� �Ʒ� TIM���� �켱���� ���� �� ����Ѵ�.
								//�Ʒ��� �켱������ 0 �ϳ��̹Ƿ� �Ƚᵵ �ǳ�
								//�켱������ 2������ ..Group_1, 4������ ...Group_2, ... Group_4���� �ִ�.)

NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;			//TIM2�� ���Ƿ� TIM2�� ����.
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//�켱���� 0
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//����켱���� 0
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//TIM2�� ä���� ENABLE��Ŵ
NVIC_Init(&NVIC_InitStructure);
}

void TIM2_IRQHandler(void)
{
if(TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET){	//(�Ƚᵵ��)�̰� �ǽ����־���. ���ͷ�Ʈ �÷��� Ŭ����
						//�̰ɾ��� �ҵ��κ� TIM_IT_Update�� TIM_IT_CC1�� �ٲ����.

TIM_ClearITpendingBit(TIM2, TIM_IT_Update);	//ClearITpendingBit�� pending bit�� clear�ϱ����� ���.
						//TIM_IT_Update�� UIF(Update Interrupt Flag)�� 1�� �ٲپ��ִ� ����.
GPIO_SetBits(GPIOA, GPIO_Pin_4);		//��ɾ���, �̰� �׳� �ܺ� LED Ű�°�.
}
}

void TIM_Configuration(void)
{

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;			//�Ʒ� ���� ����ü �θ��°� ����

TIM_TimeBaseStructure.TIM_Period = 0x4AF;			//Ÿ�̸��� ī���Ͱ� 0x4AF(1199)�� �� ������ �ٽ� 0���� ���ư�.
								//Ÿ�̸��� �ֱ� ������. (0, 1, 2, 3, ..., 1198, 1199, 0, 1, 2, ...)
								//�ֱ� ����(���� �ֱ⸦ 0x4AF�ֱ�� 1�ֱ�� ���°� (�Ʒ����� 72MHz(1�ʿ� 72M�ֱ�)�� 1200Hz��(1�ʿ� 1200�ֱ�). ���� 1200�ֱ⸦ 1�ֱ�� ���� 1�ֱ⿡ 1�ʵǵ��� ����.)
								//������ �ֱ⸦ (TIMx_ARR�� ����; Auto-reload register). Counter�� ���� �ڵ����� �缳���� �� �� ������ ����.
								//1�ʸ� ī��Ʈ�Ϸ��� �� ���� 1200�̿����Ѵ�.
								//�׷���0x4AF�� 1199�̴�. ������ 0�� �� ������ ī��Ʈ�� �����ϹǷ�, 0~1199�� 1200����,

TIM_TimeBaseStructure.TIM_Prescaler = 0xEA5F;			//���������Ϸ� ����(TIMx_PSC�� ����, ��16bit�� 72,000�� ���� ����.(�ִ� �� 65,000))
								//���� 72MHz(1�ʿ� 72M�ֱ�)�� 60,000(0xEA5F + 0x1)�� ���� 1200Hz(1�ʿ� 1200�ֱ�)�� �ٲٴ� ��.
								//�⺻(CK_INT)72Mhz --> CK_PSC�� ������(=CK_PSC�� 72Mhz)
								//TIMx_PSC�� ��(1199 = 0xEA5F)�� +1�� ���(1200)�� CK_PSC(72Mhz)���� ������ �� ���� CK_CNT�� ���޵�(1��)
								//���� ����� 1200�� �ȴ�.
								//���; ���� CK_INT(72Mhz)�� CK_PSC�� ������ ���� CK_PSC�� 72MHz
								//���2; CK_PSC(72Mhz)�� �Էµ� PSC��(0XEA5F+0x1 = 60,000)�� ������
								//���3; ��, 72MHz(CK_PSC)�� 60,000�� ������ 1200Hz(=CK_CNT)�� ���°�.

TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//=0x0	//CKD : Clock division, digital filter� ���Ǵ� sampling Ŭ���� ���Ǵ� tDTS�� ���ϱ� ���� �κ�
								//CK_INT(72Mhz)�������� ���ϰ� ��.
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//=0	//ī��Ʈ�� +�� ����, -�� ���� ����
TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;		//�̰� TIM1, TIM8������ ��. �ƹ��ų��־��
TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);			//�� ������ TIM2�� ����
}