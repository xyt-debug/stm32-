#include "stm32f10x.h"                  // Device header
#include "Delay.h"


void Seg_Init(void)
{
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOA, &GPIO_Initstructure);
	
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;		//用于扫描点亮两个数码管的GND引脚
	GPIO_Init( GPIOB, &GPIO_Initstructure);
}


void Seg_Set(uint8_t Number1, uint8_t Number2)
{
	
		//显示第一位
		GPIO_ResetBits(GPIOB , GPIO_Pin_0);
		GPIO_SetBits(GPIOB, GPIO_Pin_1);
		switch (Number1)		//用switch语句来选择显示什么数字。
		{							
			case 0:
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);
				GPIO_ResetBits(GPIOA, GPIO_Pin_6);
				break;
			}
			case 1:
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
				GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
				break;
			}
			case 2:
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6);
				GPIO_ResetBits(GPIOA, GPIO_Pin_5 | GPIO_Pin_2);
				break;
			}
			case 3:
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6);
				GPIO_ResetBits(GPIOA, GPIO_Pin_5 | GPIO_Pin_4);
				break;
			}
			case 4:
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_5 | GPIO_Pin_6);
				GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_4);
				break;
			}
			case 5:
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6);
				GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_4);
				break;
			}
			case 6:
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
				break;
			}			
			case 7:
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
				GPIO_ResetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
				break;
			}	
			case 8:
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
				break;
			}	
			case 9:
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6);
				GPIO_ResetBits(GPIOA, GPIO_Pin_4);
				break;
			}	
		}
		Delay_ms(1);
		
		//显示第二位
		GPIO_SetBits(GPIOB , GPIO_Pin_0);
    GPIO_ResetBits(GPIOB, GPIO_Pin_1);
		switch (Number2)		//用switch语句来选择显示什么数字。
		{							
			case 0:
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);
				GPIO_ResetBits(GPIOA, GPIO_Pin_6);
				break;
			}
			case 1:
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
				GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
				break;
			}
			case 2:
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6);
				GPIO_ResetBits(GPIOA, GPIO_Pin_5 | GPIO_Pin_2);
				break;
			}
			case 3:
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6);
				GPIO_ResetBits(GPIOA, GPIO_Pin_5 | GPIO_Pin_4);
				break;
			}
			case 4:
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_5 | GPIO_Pin_6);
				GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_4);
				break;
			}
			case 5:
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6);
				GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_4);
				break;
			}
			case 6:
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
				break;
			}			
			case 7:
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
				GPIO_ResetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
				break;
			}	
			case 8:
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
				break;
			}	
			case 9:
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6);
				GPIO_ResetBits(GPIOA, GPIO_Pin_4);
				break;
			}	
		}
		Delay_ms(1);  
	
	
}


