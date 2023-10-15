#include "stm32f10x.h"
#include "SPI_define.h"     // SPI1, SPI2를 쉽게 사용할 수 있도록 정의한 부분

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

void USART1_Configuration(); //Printf에 사용
void USART3_Configuration();

void GPIO_4digit_segment_0(void);   //c언어처럼 함수를 미리 선언을 합니다. 구현은 해당 c파일에
void GPIO_4digit_segment_1(void);   //역할은 GPIO_4digit_segment_0이면 0을 fnd에 출력하겠다. 구현은 segment.c파일에
void GPIO_4digit_segment_DIG_1(void);   //GPIO_4digit_segment_0~9의 함수를 써주기 전, 출력을 해줄 자릿수를 정하는 함수
void GPIO_4digit_segment_DIG_2(void);   //ex) 첫번째 자리에 숫자를 출력하고 싶으면 그 전에
void GPIO_4digit_segment_DIG_3(void);   //GPIO_4digit_segment_DIG_1()함수를 먼저 사용하여 자리수를 지정해 줘야한다.
void GPIO_4digit_segment_DIG_4(void);
void delay_m(void);


int main(void)
{

    delay_test();
    delay_test();
    delay_test();

int count=0;  //보드 1 SEG

int ok=0; //보드 1 
int Receive_data = 0; //보드2 ==OK


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //Port C를 Enable하는 것.
    // RCC->APB2ENR |= RCC_APB2Periph_GPIOC;                //Port C를 Enable하는 것.

    SystemInit();//RCC 초기화

    TIM_Configuration();
    NVIC_Configuration();
    RCC_Configuration();                // RCC 셋팅을 불러오는 함수
    GPIO_Configuration();               // GPIO 셋팅을 불러오는 함수

    USART1_Configuration();
    USART3_Configuration();

    //USART1_Init();

    int m=0;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_TypeDef * GPIOx=GPIOC;
    GPIO_InitTypeDef       GPIO_InitStructure= {0,}; //PIO 함수의 객체(A) 선언

    GPIO_InitStructure.GPIO_Pin      = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6 ;         // 객체 A를 9번 핀으로 선언
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;      // 최대 스피드를 50MHz
    GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_Out_PP;      // In/Out 모드 선택

    GPIO_Init(GPIOA, &GPIO_InitStructure);            // Port B에 객체 A의 셋팅값 입력
    GPIO_ResetBits(GPIOA, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6);            //6번핀이 부저, 4,5번이 led 끈상태로 시작
    


    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;    // 외부 Segment의 GPIO 핀 번호
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_PP;

    GPIO_Init(GPIOC, &GPIO_InitStructure);
    //위 코드는 내장 세그먼트 출력 코드, 우리는 내장이 고장났으므로 해당없음





    // 아래 코드는 4digit segment를 키는 코드. (아래 함수들은 stm32 제공 라이브러리 함수를 기반으로 새롭게 만든 함수로 segment.c에서 해석 가능)
    GPIO_4digit_segment_0();            // 4digit segment의 출력 숫자(0~9)을 결정
    GPIO_4digit_segment_DIG_4();        // 4digit segment의 자릿수에 전원 인가를 결정(총 4자리.)
    delay_m();                          // delay 함수

//여기서부터 임민혁이직접 작성한 코드

        CCR1_Val = m_speed[m];


while(1)//현재  fnd의 출력자리는 4번째라고 4줄위에 써져있음
    {
    
         
        
        
        while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);     // 1. TXE는 Tx Empty. 즉 USART_FLAG_TXE는 USART3 Rx쪽의 Tmp 저장장소가 비었는지, 안비워졌는지 확인하는 곳. 비워져야 데이터를 받아 전송할 수 있다.
        
        if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == (uint8_t)Bit_SET)    //ok버튼
                                                                        //버튼을 눌렀을 때 해당하는 코드를 작성하면 됩니다.
            {
                count=count+1;      //카운트변수에 따라 세그먼트 값 변경
                delay_m_button();   //버튼을 짧게 누르면 여러번 입력이 되므로 약간 긴 딜레이 *2
                delay_m_button();   //그렇다면 딜레이 시간을 조정하려면 delay.c파일을 손보면 되겠죠?
            }
    
        if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == (uint8_t)Bit_SET)    //A의 0번핀이 내장버튼이다.
        {            
            ok=ok+1;
            delay_m_button();   //버튼을 짧게 누르면 여러번 입력이 되므로 약간 긴 딜레이 *2
            delay_m_button();   //그렇다면 딜레이 시간을 조정하려면 delay.c파일을 손보면 되겠죠?
        }

        
        USART_SendData(USART3, ok);                                // 2. Send_data값(Data)를 USART3의 Tmp에 넣는다.

        while (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);    // 3. RXNE는 RX Not Empty로, USART3 Rx의 Tmp 공간에 값이 들어왔는지 확인한다.
        Receive_data = USART_ReceiveData(USART3);                         // 4. USART3 Rx의 Tmp공간에 값이 들어왔으면, 해당 값을 변수(Receive_data)로 받아 통신을 완료시킨다.

        printf("Received data is %d =ok\n", Receive_data);
        printf("ok data is %d\n", ok);
        printf("count data is %d\n", count);
    

        if(count==1)
            {
                GPIO_4digit_segment_DIG_3();        // 첫번째 자리를 지정해주고
                GPIO_4digit_segment_5();            //첫번째 자리에 0을 출력해주겠다
                                                    //원래 segment.c에 정의되있는건 0~4까지 더 높은 숫자를 띄우려면
                                                    //segment.c를 손보면 됩니다. ppt에 바꾸는법 나와있어요
                delay_count();
            
                GPIO_4digit_segment_DIG_4();        // 두번쨰 자리를 지정
                GPIO_4digit_segment_0();            // 두번쨰 자리에 1을 출력해주겠다. 
                                                    // 이러면 와일문을 돌면서 1, 0이 반복 출력되면서 잔상효과로 세그먼트에 값 출력
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
                GPIO_SetBits(GPIOA, GPIO_Pin_4);            //6번핀이 부저, 4,5번이 led 끈상태로 시작
                GPIO_4digit_segment_DIG_4();       
                GPIO_4digit_segment_0();
                delay_count();
                count=0;
            }
        
        if(Receive_data!=0||ok!=0)
       {
            GPIO_ResetBits(GPIOA, GPIO_Pin_4);            //6번핀이 부저, 4,5번이 led 끈상태로 시작
            GPIO_SetBits(GPIOA, GPIO_Pin_5);            //6번핀이 부저, 4,5번이 led 끈상태로 시작
         int m = 0;
         int n = 0;
         int number=6;
     while(number--)
    {
        //printf는 Token2Shell에서 확인 가능. 다음 시간에 설명할 예정.
        printf("-----------------------------\n");


        CCR1_Val = m_speed[m];
        printf("CCR1_Val : %d\n", m_speed[m]);

        // 아래 두 줄은 PWM에서 출력 채널을 선택하여 Pulse값을 입력하는 것과
        TIM_OCInitStructure_PWM.TIM_Pulse = CCR1_Val;
        TIM_OC1Init(TIM4, &TIM_OCInitStructure_PWM);

       
       // 모터 회전 방향 전환
      if(n%2 ==0)
          {
        GPIO_ResetBits(GPIOB, GPIO_Pin_12);     // 정방향
        TIM_OCInitStructure_PWM.TIM_Pulse = CCR1_Val;
        TIM_OC1Init(TIM4, &TIM_OCInitStructure_PWM);
           delay_m1();
        }
    
        if(n%2 ==1){
       GPIO_SetBits(GPIOB, GPIO_Pin_12);     // 역방향
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
        if(n%2 == 0) // 정방향
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
            
            GPIO_ResetBits(GPIOA, GPIO_Pin_5);            //6번핀이 부저, 4,5번이 led 끈상태로 시작
            
            Receive_data=0;
            ok=0;
            }
}
}