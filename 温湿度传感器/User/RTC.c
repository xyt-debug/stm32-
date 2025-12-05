#include "stm32f10x.h"                  // Device header


void RTC_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);

    if (BKP_ReadBackupRegister(BKP_DR1) != 0x5050) // 第一次上电
    {
        RCC_BackupResetCmd(ENABLE);
        RCC_BackupResetCmd(DISABLE);

        RCC_LSEConfig(RCC_LSE_ON);   // 启动外部32.768kHz晶振
        while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);

        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
        RCC_RTCCLKCmd(ENABLE);

        RTC_WaitForSynchro();
        RTC_WaitForLastTask();

        RTC_SetPrescaler(32767);     // 1秒中断
        RTC_WaitForLastTask();

        //=====================================================
        //⭐ 这里设置一次真实时间（你要填写你当前的真实时间）
        //=====================================================
        uint32_t init_time = 20*3600 + 15*60 + 0;  // 例如 14:30:00
        RTC_SetCounter(init_time);
        RTC_WaitForLastTask();
				
        //=====================================================

        BKP_WriteBackupRegister(BKP_DR1, 0x5050); // 标记已经初始化
    }
    else
    {
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
        RCC_RTCCLKCmd(ENABLE);

        RTC_WaitForSynchro();
        RTC_WaitForLastTask();
    }
}


void RTC_GetTime(uint32_t *hour, uint32_t *min, uint32_t *sec)
{
    uint32_t time = RTC_GetCounter();

    *hour = time / 3600 % 24;
    *min  = time % 3600 / 60;
    *sec  = time % 60;
}

