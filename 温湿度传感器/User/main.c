//#include "stm32f10x.h"

//// 初始化 USART1
//void UART1_Init(void)
//{
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

//    GPIO_InitTypeDef GPIO_InitStructure;

//    // TX (PA9) - 复用推挽输出
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);

//    // RX (PA10) - 上拉输入
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);

//    USART_InitTypeDef USART_InitStructure;
//    USART_InitStructure.USART_BaudRate = 115200;
//    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//    USART_InitStructure.USART_StopBits = USART_StopBits_1;
//    USART_InitStructure.USART_Parity = USART_Parity_No;
//    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

//    USART_Init(USART1, &USART_InitStructure);
//    USART_Cmd(USART1, ENABLE);
//}

//// 发送一个字符
//void UART1_SendChar(char c)
//{
//    USART_SendData(USART1, c);
//    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
//}

//// 发送字符串
//void UART1_SendString(char* str)
//{
//    while (*str)
//    {
//        UART1_SendChar(*str++);
//    }
//}

//// 接收一个字符（阻塞）
//char UART1_ReceiveChar(void)
//{
//    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
//    return USART_ReceiveData(USART1);
//}

//int main(void)
//{
//    SystemInit();
//    UART1_Init();

//    UART1_SendString("STM32 UART Test\r\n");

//    while (1)
//    {
//        char c = UART1_ReceiveChar();  // 阻塞接收
//        UART1_SendChar(c);             // 回显接收到的字符
//    }
//}


#include "stm32f10x.h"  // Device header
#include "LED.h"
#include "Delay.h"
#include "Key.h"
#include "OLED.h"
#include "uart.h"
#include "dht11.h"
#include "stdlib.h"
#include "string.h"
#include "RTC.h"
  
int T_Max = 23;   // 默认温度最大阈值
int H_Max = 70;   // 默认湿度最大阈值
uint32_t hour, min, sec;

int main(void)
{
	SystemInit();
	uart_init();
	DHT11_Init();
	OLED_Init();
	LED_Init();
  RTC_Init();
	

  OLED_ShowString(2, 1, "Temp:      C");   // 预留温度位
  OLED_ShowString(3, 1, "Humi:      %");   // 预留湿度位	
	
	OLED_ShowString(4, 1, "Tmax:");//温度阈值
  OLED_ShowNum(4, 6, T_Max, 2);

  OLED_ShowString(4, 10, "Hmax:");//湿度阈值
  OLED_ShowNum(4, 15, H_Max, 2);
	
	DHT11_Data_TypeDef dht;
	
	
	while (1)
	{//解析串口指令，设定温湿度阈值
	
		if (Serial_RxFlag)
   {
    Serial_RxFlag = 0;

    if (strncmp(Serial_RxPacket, "SET:TMAX=", 9) == 0)
    {
        T_Max = atoi(&Serial_RxPacket[9]);
        OLED_ShowNum(4, 6, T_Max, 2);
        Serial_Printf("TMAX SET TO %d\r\n", T_Max);
    }
    else if (strncmp(Serial_RxPacket, "SET:HMAX=", 9) == 0)
    {
        H_Max = atoi(&Serial_RxPacket[9]);
        OLED_ShowNum(4, 15, H_Max, 2);
        Serial_Printf("HMAX SET TO %d\r\n", H_Max);
    }
   }

		
		
	 if (DHT11_ReadData(&dht))
        {
            // OLED 显示温度
            OLED_ShowNum(2, 7, dht.temp_int, 2);
            OLED_ShowNum(2, 10, dht.temp_dec, 1);
            OLED_ShowString(2, 9, ".");
					
            // OLED 显示湿度
            OLED_ShowNum(3, 7, dht.humidity_int, 2);
            OLED_ShowNum(3, 10, dht.humidity_dec, 1);
					  OLED_ShowString(3, 9, ".");

            // 串口输出方便调试
            Serial_Printf("Temp=%d.%dC  Humi=%d.%d%%\r\n",
                          dht.temp_int, dht.temp_dec,
                          dht.humidity_int, dht.humidity_dec);
        
				
				    // 温度报警
            if (dht.temp_int > T_Max)
                GPIO_SetBits(GPIOA, GPIO_Pin_0);
            else
                GPIO_ResetBits(GPIOA, GPIO_Pin_0);

            // 湿度报警
            if (dht.humidity_int > H_Max)
                GPIO_SetBits(GPIOA, GPIO_Pin_2);
            else
                GPIO_ResetBits(GPIOA, GPIO_Pin_2);
        }
				
       else
        {
            OLED_ShowString(2, 1, "DHT11 ERROR");
            Serial_SendString("DHT11 Read Error!\r\n");
        }

        Delay_ms(1000); // DHT11 最快1秒读1次
	
		// 读取并显示RTC时间
    RTC_GetTime(&hour, &min, &sec);
		OLED_ShowNum(1, 1, hour, 2);
		OLED_ShowString(1, 3, ":");
		OLED_ShowNum(1, 4, min, 2);
		OLED_ShowString(1, 6, ":");
		OLED_ShowNum(1, 7, sec, 2);
	}
}

	

