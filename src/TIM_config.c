#include "stm32f10x.h"

// 1Clock�� �ֱ� = (prescaler + 1) / 72MHz
// 1Clock�� ���ļ� = 1 / 1Clock�� �ֱ�
// n�� : 1�� = x clock : 1 clock
// x clock = n * 1Clock�� ���ļ�

TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure_PWM;
TIM_OCInitTypeDef           TIM_OCInitStructure_PWM;

void TIM_Configuration(void)
{
    // Time base configuration 
    // �Է��� 72,000,000MHz�̴�. Prescaler(59999+1)�� ������ 1200�� �ȴ�. ��, 1�ʿ� 1200���� ��ȣ�� ���� 1200Hz�� �ȴ�.
    // �̶� ��ȣ�� �ֱ⸦ 1200 ��ȣ�� ����ָ� 1�ʿ� 1�� Ÿ�̸� ��ȣ�� �ްԵǰԲ� ������ �����ϹǷ� �ֱ⸦ 1200���� ����ش�.(1199 + 1)
    // �̸� �� ���� ���� ������ TIM_Prescaler�� 16��Ʈ�� ũ���̱� ������ 65535 �̻��� ���� ���� �� ���⿡ Prescaler, Period�� �������� ������ ����Ѵ�.
    TIM_TimeBaseStructure.TIM_Period = 1199;                      // 0~1799 �̹Ƿ� 1800
    TIM_TimeBaseStructure.TIM_Prescaler = 0xEA5F;                 // 0~59999 �̹Ƿ� 60000 (0xEA5F = 59999)

    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;       // ���� ���������� �ʿ� ���� �κ�. tDTS�� ���ϱ� ���� �κ��̴�.
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   // ������ �����ϴ� �κ��� counter�� �����ϴ� �������� ����, �����ϴ� �������� ������ ���ϴ� �κ�.
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;         // Advanced-control timer�� TIM1, TIM8�� �ƴѰ�쿡�� �ʿ䰡 ����.
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.TIM_Period = 0x0707;                    // 0~1799 �̹Ƿ� 1800 (0x0707 = 1799)
    TIM_TimeBaseStructure.TIM_Prescaler = 59999;                  // 0~59999 �̹Ƿ� 60000

    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;       // ���� ���������� �ʿ� ���� �κ�. tDTS�� ���ϱ� ���� �κ��̴�.
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   // ������ �����ϴ� �κ��� counter�� �����ϴ� �������� ����, �����ϴ� �������� ������ ���ϴ� �κ�.
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;         // Advanced-control timer�� TIM1, TIM8�� �ƴѰ�쿡�� �ʿ䰡 ����.
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  
    // TIM2 enable counter 
    TIM_Cmd(TIM2, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
  
    // �ش� �ڵ�� ���� ���������� ��� ����.
    TIM_PrescalerConfig(TIM2, 0xEA5F, TIM_PSCReloadMode_Immediate);
    TIM_PrescalerConfig(TIM3, 0xEA5F, TIM_PSCReloadMode_Immediate);

    // Clear TIM update pending flag
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);

    // TIM IT enable 
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);










    // PWM //   // PWM //   // PWM //   // PWM //
    // PWM //   // PWM //   // PWM //   // PWM //
    // PWM //   // PWM //   // PWM //   // PWM //
    // PWM //   // PWM //   // PWM //   // PWM //
    // PWM //   // PWM //   // PWM //   // PWM //
    
    
    // ���⼭ TIM4�� PWM ��ȣ�� �����ϴ� Ÿ�̸ӷ� ����
    // 72Mhz �Է¿��� �ֱ� 720���� ������ 1,000Hz�� �ȴ�.
    // ���⼭ Prescaler�� 100�̸� 10Hz�� �ȴ�.
    TIM_TimeBaseStructure_PWM.TIM_Period = 719;     // 72Mhz �Է¿��� �ֱ� 720���� ������ 1,000Hz�� �ȴ�.
    TIM_TimeBaseStructure_PWM.TIM_Prescaler = 99;   //   ���⼭ Prescaler�� 100�̸� 10Hz�� �ȴ�.
    TIM_TimeBaseStructure_PWM.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure_PWM.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure_PWM);


    
    // PWM1 Mode configuration: Channel1 
    TIM_OCInitStructure_PWM.TIM_OCMode = TIM_OCMode_PWM1;   //CCMR��������(Capture/compare mode register)
                                                            //TIMx_CCRM1, TIMx_CCRM2 �� ������ �ִ�.
                                                            //CCMR1�� ä��1,2(CH1,CH2. �� OC1Init, OC2Init)���. CCMR2�� ä��3,4(CH3,CH4. �� OC3Init, OC4Init)����̴�.
                                                            //���� OC�� Output Channel, IC�� Input Channel�� ������, TIM_OCMode�� �⺻������ Output.

    TIM_OCInitStructure_PWM.TIM_OutputState = TIM_OutputState_Enable;	//CCER��������(Capture/compare enable register)
                                                                        //�� �״�� output�� enable����.

    TIM_OCInitStructure_PWM.TIM_Pulse = 0;//CCR1_Val;		//CCR�� ĸ��/�� ��������
                                                            //Channel���� �ٸ��� ������ CCRx_Val�� ����.(CCR����)
                                                            //����Ǵ� ���� TIMx_CCRx�� ����.

    TIM_OCInitStructure_PWM.TIM_OCPolarity = TIM_OCPolarity_High;	//CCER��������(Captuer/compare enable register) ����
    TIM_OC1Init(TIM4, &TIM_OCInitStructure_PWM);			        //TIM4�� ���� ������ OC?�� ����
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);


    TIM_OCInitStructure_PWM.TIM_OutputState = TIM_OutputState_Enable;	//�Ʒ��� ���� ����
    TIM_OCInitStructure_PWM.TIM_Pulse = 0;//CCR2_Val;
    TIM_OC2Init(TIM4, &TIM_OCInitStructure_PWM);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

    // TIM4 enable counter 
    TIM_Cmd(TIM4, ENABLE);
}
