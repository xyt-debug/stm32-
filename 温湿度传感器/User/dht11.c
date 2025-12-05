#include "dht11.h"
#include "Delay.h"

// 连接到 DHT11 的 GPIO
#define DHT11_GPIO_PORT      GPIOA
#define DHT11_GPIO_CLK       RCC_APB2Periph_GPIOA
#define DHT11_GPIO_PIN       GPIO_Pin_3

// 设置 GPIO 为输出
static void DHT11_Mode_Out(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = DHT11_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStruct);
}

// 设置 GPIO 为输入
static void DHT11_Mode_In(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = DHT11_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStruct);
}

// 写引脚
static void DHT11_Out(uint8_t level)
{
    GPIO_WriteBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN, (BitAction)level);
}

// 读引脚
static uint8_t DHT11_In(void)
{
    return GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN);
}



// 初始化 GPIO
void DHT11_Init(void)
{
    RCC_APB2PeriphClockCmd(DHT11_GPIO_CLK, ENABLE);
    DHT11_Mode_Out();
    DHT11_Out(1); // 默认拉高
}

// 读取 1 bit
static uint8_t DHT11_ReadBit(void)
{
    while (DHT11_In() == 0);     // 等待低电平结束
    Delay_us(40);                // 延时 40us

    uint8_t bit = 0;
    if (DHT11_In() == 1)
        bit = 1;

    while (DHT11_In() == 1);     // 等待高电平结束
    return bit;
}

// 读取 1 字节
static uint8_t DHT11_ReadByte(void)
{
    uint8_t data = 0;

    for (uint8_t i = 0; i < 8; i++)
    {
        while (DHT11_In() == 0);  // 等待开始
        Delay_us(40);

        data <<= 1;
        if (DHT11_In()) data |= 1;

        while (DHT11_In() == 1);  // 等待高电平结束
    }

    return data;
}

// 读取完整 40bit 数据
uint8_t DHT11_ReadData(DHT11_Data_TypeDef* DHT11_Data)
{
    uint8_t humi_int, humi_dec, temp_int, temp_dec, checksum;

    // MCU 发送起始信号
    DHT11_Mode_Out();
    DHT11_Out(0);
    Delay_ms(18);        // 拉低至少 18ms（主机信号）
    DHT11_Out(1);
    Delay_us(30);
    DHT11_Mode_In();

    // DHT11 响应信号
    if (DHT11_In() == 0)
    {
        while (DHT11_In() == 0);
        while (DHT11_In() == 1);

        // 读取 5 字节
        humi_int  = DHT11_ReadByte();
        humi_dec  = DHT11_ReadByte();
        temp_int  = DHT11_ReadByte();
        temp_dec  = DHT11_ReadByte();
        checksum  = DHT11_ReadByte();

        DHT11_Data->humidity_int = humi_int;
        DHT11_Data->humidity_dec = humi_dec;
        DHT11_Data->temp_int = temp_int;
        DHT11_Data->temp_dec = temp_dec;
        DHT11_Data->checksum = checksum;

        if (checksum == (humi_int + humi_dec + temp_int + temp_dec))
            return 1;        // OK
        else
            return 0;        // 校验错误
    }
    else
    {
        return 0;            // 无响应
    }
}
