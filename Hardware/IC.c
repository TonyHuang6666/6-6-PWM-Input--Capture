#include "stm32f10x.h"
//配置输入捕获单元
void IC_Init(void)
{
    //开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    //2.配置GPIO
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //3.配置时基单元

    TIM_InternalClockConfig(TIM3);//内部时钟。漏了！！！！！！！！！！

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;//定义结构体变量
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 0xffff;//设置自动重装载寄存器的值,一般设为最大值65535
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72-1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
    //4.配置输入捕获单元
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//不分频，每次都捕获
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    //5.选择从模式的触发源
    TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
    //6.选择触发后执行的操作
    TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
    //7.开启定时器
    TIM_Cmd(TIM3, ENABLE);//开启定时器。漏了！！！！！！！！！！
}

uint16_t Get_Frequency(void)
{
    return 1000000/TIM_GetCapture1(TIM3);
}
