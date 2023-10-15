#include "stm32f10x.h"
#include "SPI_define.h"     // SPI1, SPI2�� ���� ����� �� �ֵ��� ������ �κ�

#include <stdio.h>

TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
TIM_OCInitTypeDef           TIM_OCInitStructure_PWM;

uint16_t CCR1_Val = 0;
uint16_t CCR2_Val = 0;
uint16_t CCR3_Val = 0;
uint16_t CCR4_Val = 0;




int m_speed[6] = {10, 10, 10, 10, 10, 10};

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void TIM_Configuration(void);

void USART1_Configuration(); //Printf�� ���
void USART3_Configuration();

void GPIO_4digit_segment_0(void);   //c���ó�� �Լ��� �̸� ������ �մϴ�. ������ �ش� c���Ͽ�
void GPIO_4digit_segment_1(void);   //������ GPIO_4digit_segment_0�̸� 0�� fnd�� ����ϰڴ�. ������ segment.c���Ͽ�
void GPIO_4digit_segment_DIG_1(void);   //GPIO_4digit_segment_0~9�� �Լ��� ���ֱ� ��, ����� ���� �ڸ����� ���ϴ� �Լ�
void GPIO_4digit_segment_DIG_2(void);   //ex) ù��° �ڸ��� ���ڸ� ����ϰ� ������ �� ����
void GPIO_4digit_segment_DIG_3(void);   //GPIO_4digit_segment_DIG_1()�Լ��� ���� ����Ͽ� �ڸ����� ������ ����Ѵ�.
void GPIO_4digit_segment_DIG_4(void);
void delay_m(void);


int main(void)
{

    delay_test();
    delay_test();
    delay_test();

int count=0;  //���� 1 SEG

int ok=0; //���� 1 
int Receive_data = 0; //����2 ==OK


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //Port C�� Enable�ϴ� ��.
    // RCC->APB2ENR |= RCC_APB2Periph_GPIOC;                //Port C�� Enable�ϴ� ��.

    SystemInit();//RCC �ʱ�ȭ

    TIM_Configuration();
    NVIC_Configuration();
    RCC_Configuration();                // RCC ������ �ҷ����� �Լ�
    GPIO_Configuration();               // GPIO ������ �ҷ����� �Լ�

    USART1_Configuration();
    USART3_Configuration();

    //USART1_Init();

    int m=0;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_TypeDef * GPIOx=GPIOC;
    GPIO_InitTypeDef       GPIO_InitStructure= {0,}; //PIO �Լ��� ��ü(A) ����

    GPIO_InitStructure.GPIO_Pin      = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6 ;         // ��ü A�� 9�� ������ ����
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;      // �ִ� ���ǵ带 50MHz
    GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_Out_PP;      // In/Out ��� ����

    GPIO_Init(GPIOA, &GPIO_InitStructure);            // Port B�� ��ü A�� ���ð� �Է�
    GPIO_ResetBits(GPIOA, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6);            //6������ ����, 4,5���� led �����·� ����
    


    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;    // �ܺ� Segment�� GPIO �� ��ȣ
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_PP;

    GPIO_Init(GPIOC, &GPIO_InitStructure);
    //�� �ڵ�� ���� ���׸�Ʈ ��� �ڵ�, �츮�� ������ ���峵���Ƿ� �ش����





    // �Ʒ� �ڵ�� 4digit segment�� Ű�� �ڵ�. (�Ʒ� �Լ����� stm32 ���� ���̺귯�� �Լ��� ������� ���Ӱ� ���� �Լ��� segment.c���� �ؼ� ����)
    GPIO_4digit_segment_0();            // 4digit segment�� ��� ����(0~9)�� ����
    GPIO_4digit_segment_DIG_4();        // 4digit segment�� �ڸ����� ���� �ΰ��� ����(�� 4�ڸ�.)
    delay_m();                          // delay �Լ�

//���⼭���� �ӹ��������� �ۼ��� �ڵ�

        CCR1_Val = m_speed[m];


while(1)//����  fnd�� ����ڸ��� 4��°��� 4������ ��������
    {
    
         
        
        
        while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);     // 1. TXE�� Tx Empty. �� USART_FLAG_TXE�� USART3 Rx���� Tmp ������Ұ� �������, �Ⱥ�������� Ȯ���ϴ� ��. ������� �����͸� �޾� ������ �� �ִ�.
        
        if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == (uint8_t)Bit_SET)    //ok��ư
                                                                        //��ư�� ������ �� �ش��ϴ� �ڵ带 �ۼ��ϸ� �˴ϴ�.
            {
                count=count+1;      //ī��Ʈ������ ���� ���׸�Ʈ �� ����
                delay_m_button();   //��ư�� ª�� ������ ������ �Է��� �ǹǷ� �ణ �� ������ *2
                delay_m_button();   //�׷��ٸ� ������ �ð��� �����Ϸ��� delay.c������ �պ��� �ǰ���?
            }
    
        if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == (uint8_t)Bit_SET)    //A�� 0������ �����ư�̴�.
        {            
            ok=ok+1;
            delay_m_button();   //��ư�� ª�� ������ ������ �Է��� �ǹǷ� �ణ �� ������ *2
            delay_m_button();   //�׷��ٸ� ������ �ð��� �����Ϸ��� delay.c������ �պ��� �ǰ���?
        }

        
        USART_SendData(USART3, ok);                                // 2. Send_data��(Data)�� USART3�� Tmp�� �ִ´�.

        while (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);    // 3. RXNE�� RX Not Empty��, USART3 Rx�� Tmp ������ ���� ���Դ��� Ȯ���Ѵ�.
        Receive_data = USART_ReceiveData(USART3);                         // 4. USART3 Rx�� Tmp������ ���� ��������, �ش� ���� ����(Receive_data)�� �޾� ����� �Ϸ��Ų��.

        printf("Received data is %d =ok\n", Receive_data);
        printf("ok data is %d\n", ok);
        printf("count data is %d\n", count);
    

        if(count==1)
            {
                GPIO_4digit_segment_DIG_3();        // ù��° �ڸ��� �������ְ�
                GPIO_4digit_segment_5();            //ù��° �ڸ��� 0�� ������ְڴ�
                                                    //���� segment.c�� ���ǵ��ִ°� 0~4���� �� ���� ���ڸ� ������
                                                    //segment.c�� �պ��� �˴ϴ�. ppt�� �ٲٴ¹� �����־��
                delay_count();
            
                GPIO_4digit_segment_DIG_4();        // �ι��� �ڸ��� ����
                GPIO_4digit_segment_0();            // �ι��� �ڸ��� 1�� ������ְڴ�. 
                                                    // �̷��� ���Ϲ��� ���鼭 1, 0�� �ݺ� ��µǸ鼭 �ܻ�ȿ���� ���׸�Ʈ�� �� ���
                delay_count();
            }
        
         else if(count==2)
            {
                GPIO_4digit_segment_DIG_2();        
                GPIO_4digit_segment_1();
                delay_count();
            
                GPIO_4digit_segment_DIG_3();        
                GPIO_4digit_segment_0();
                delay_count();
            
                GPIO_4digit_segment_DIG_4();        
                GPIO_4digit_segment_0();
                delay_count();
            }
        
        else if(count==3)
            {
                GPIO_4digit_segment_DIG_2();       
                GPIO_4digit_segment_1();
                delay_count();
            
                GPIO_4digit_segment_DIG_3();       
                GPIO_4digit_segment_5();
                delay_count();
            
                GPIO_4digit_segment_DIG_4();       
                GPIO_4digit_segment_0();
                delay_count();
            }
         
        else if(count==4)
            {
                GPIO_4digit_segment_DIG_2();       
                GPIO_4digit_segment_2();
                delay_count();
            
                GPIO_4digit_segment_DIG_3();       
                GPIO_4digit_segment_0();
                delay_count();
            
                GPIO_4digit_segment_DIG_4();       
                GPIO_4digit_segment_0();
                delay_count();
            }
         
        else if(count==5)
            {
                GPIO_4digit_segment_DIG_2();       
                GPIO_4digit_segment_2();
                delay_count();
            
                GPIO_4digit_segment_DIG_3();       
                GPIO_4digit_segment_5();
                delay_count();
            
                GPIO_4digit_segment_DIG_4();       
                GPIO_4digit_segment_0();
                delay_count();
            }
        
        else if(count==6)
            {
                GPIO_4digit_segment_DIG_2();       
                GPIO_4digit_segment_3();
                delay_count();
            
                GPIO_4digit_segment_DIG_3();       
                GPIO_4digit_segment_0();
                delay_count();
            
                GPIO_4digit_segment_DIG_4();       
                GPIO_4digit_segment_0();
                delay_count();
            }
        else if(count==7)
            {
                GPIO_4digit_segment_DIG_2();       
                GPIO_4digit_segment_3();
                delay_count();
            
                GPIO_4digit_segment_DIG_3();       
                GPIO_4digit_segment_5();
                delay_count();
            
                GPIO_4digit_segment_DIG_4();       
                GPIO_4digit_segment_0();
                delay_count();
            }
        else if(count==8)
            {
                GPIO_4digit_segment_DIG_2();       
                GPIO_4digit_segment_4();
                delay_count();
            
                GPIO_4digit_segment_DIG_3();       
                GPIO_4digit_segment_0();
                delay_count();
            
                GPIO_4digit_segment_DIG_4();       
                GPIO_4digit_segment_0();
                delay_count();
            }
        else if(count==9)
            {
                GPIO_4digit_segment_DIG_2();       
                GPIO_4digit_segment_4();
                delay_count();
            
                GPIO_4digit_segment_DIG_3();       
                GPIO_4digit_segment_5();
                delay_count();
            
                GPIO_4digit_segment_DIG_4();       
                GPIO_4digit_segment_0();
                delay_count();
            }
        else if(count==10)
            {
                GPIO_4digit_segment_DIG_2();       
                GPIO_4digit_segment_5();
                delay_count();
            
                GPIO_4digit_segment_DIG_3();       
                GPIO_4digit_segment_0();
                delay_count();
            
                GPIO_4digit_segment_DIG_4();       
                GPIO_4digit_segment_0();
                delay_count();
            }
        
        
        else
            {
                GPIO_SetBits(GPIOA, GPIO_Pin_4);            //6������ ����, 4,5���� led �����·� ����
                GPIO_4digit_segment_DIG_4();       
                GPIO_4digit_segment_0();
                delay_count();
                count=0;
            }
        
        if(Receive_data!=0||ok!=0)
       {
            GPIO_ResetBits(GPIOA, GPIO_Pin_4);            //6������ ����, 4,5���� led �����·� ����
            GPIO_SetBits(GPIOA, GPIO_Pin_5);            //6������ ����, 4,5���� led �����·� ����
         int m = 0;
         int n = 0;
         int number=6;
     while(number--)
    {
        //printf�� Token2Shell���� Ȯ�� ����. ���� �ð��� ������ ����.
        printf("-----------------------------\n");


        CCR1_Val = m_speed[m];
        printf("CCR1_Val : %d\n", m_speed[m]);

        // �Ʒ� �� ���� PWM���� ��� ä���� �����Ͽ� Pulse���� �Է��ϴ� �Ͱ�
        TIM_OCInitStructure_PWM.TIM_Pulse = CCR1_Val;
        TIM_OC1Init(TIM4, &TIM_OCInitStructure_PWM);

       
       // ���� ȸ�� ���� ��ȯ
      if(n%2 ==0)
          {
        GPIO_ResetBits(GPIOB, GPIO_Pin_12);     // ������
        TIM_OCInitStructure_PWM.TIM_Pulse = CCR1_Val;
        TIM_OC1Init(TIM4, &TIM_OCInitStructure_PWM);
           delay_m1();
        }
    
        if(n%2 ==1){
       GPIO_SetBits(GPIOB, GPIO_Pin_12);     // ������
         TIM_OCInitStructure_PWM.TIM_Pulse = CCR1_Val;
        TIM_OC1Init(TIM4, &TIM_OCInitStructure_PWM);
        delay_m2();
    }
        
        m++;

        if(m==3)
        {
      if(count==1)
       {
         CCR1_Val = 0 ;
        TIM_OCInitStructure_PWM.TIM_Pulse = CCR1_Val;
        TIM_OC1Init(TIM4, &TIM_OCInitStructure_PWM);
        if(n%2 == 0) // ������
            delay_m3();
       }
   
      if(count==2)
       {
         CCR1_Val = 0 ;
        TIM_OCInitStructure_PWM.TIM_Pulse = CCR1_Val;
        TIM_OC1Init(TIM4, &TIM_OCInitStructure_PWM);
       if(n%2 == 0){
         delay_m3();
         delay_m3();
       }
       }
   
      if(count==3)
       {
         CCR1_Val = 0 ;
        TIM_OCInitStructure_PWM.TIM_Pulse = CCR1_Val;
        TIM_OC1Init(TIM4, &TIM_OCInitStructure_PWM);
       if(n%2 == 0){
            delay_m3();
            delay_m3();
            delay_m3();
       }
       }
   
      if(count==4)
       {
         CCR1_Val = 0 ;
        TIM_OCInitStructure_PWM.TIM_Pulse = CCR1_Val;
        TIM_OC1Init(TIM4, &TIM_OCInitStructure_PWM);
       if(n%2 == 0){
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
       }
       }
   
      if(count==5)
       {
         CCR1_Val = 0 ;
        TIM_OCInitStructure_PWM.TIM_Pulse = CCR1_Val;
        TIM_OC1Init(TIM4, &TIM_OCInitStructure_PWM);
       if(n%2 == 0){
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
       }
       }
   
      if(count==6)
       {
         CCR1_Val = 0 ;
        TIM_OCInitStructure_PWM.TIM_Pulse = CCR1_Val;
        TIM_OC1Init(TIM4, &TIM_OCInitStructure_PWM);
       if(n%2 == 0){
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
       }
       }
   
      if(count==7)
       {
         CCR1_Val = 0 ;
        TIM_OCInitStructure_PWM.TIM_Pulse = CCR1_Val;
        TIM_OC1Init(TIM4, &TIM_OCInitStructure_PWM);
       if(n%2 == 0){
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
       }
       }
   
      if(count==8)
       {
         CCR1_Val = 0 ;
        TIM_OCInitStructure_PWM.TIM_Pulse = CCR1_Val;
        TIM_OC1Init(TIM4, &TIM_OCInitStructure_PWM);
       if(n%2 == 0){
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
       }
       }
   
      if(count==9)
       {
         CCR1_Val = 0 ;
        TIM_OCInitStructure_PWM.TIM_Pulse = CCR1_Val;
        TIM_OC1Init(TIM4, &TIM_OCInitStructure_PWM);
       if(n%2 == 0){
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
            delay_m3();
       }
       }
   
           m=0;
           if(n==0)
              n = 1;
           else if(n==1)
              n = 0;
        }   // end of if
    
      }     // end of while

      } // end of ok if
  
    if(Receive_data!=0||ok!=0)
            {
            GPIO_SetBits(GPIOA, GPIO_Pin_6);

            delay_m_button();   
            delay_m_button();   
            delay_m_button();   
            delay_m_button();   
            delay_m_button();
            delay_m_button();
            delay_m_button();
            delay_m_button();
            delay_m_button();            
            GPIO_ResetBits(GPIOA, GPIO_Pin_6);
            
            GPIO_ResetBits(GPIOA, GPIO_Pin_5);            //6������ ����, 4,5���� led �����·� ����
            
            Receive_data=0;
            ok=0;
            }
}
}