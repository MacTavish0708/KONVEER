#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_adc.h"
#include "misc.h"
#include "stdio.h"



void SetSysClockTo72(void) {
    ErrorStatus HSEStartUpStatus;
    RCC_DeInit();
    RCC_HSEConfig( RCC_HSE_ON);
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
    if (HSEStartUpStatus == SUCCESS){
        RCC_HCLKConfig( RCC_SYSCLK_Div1);
        RCC_PCLK2Config( RCC_HCLK_Div1);
        RCC_PCLK1Config( RCC_HCLK_Div2);
        RCC_PLLConfig(0x00010000, RCC_PLLMul_9);
        RCC_PLLCmd( ENABLE);
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){}
        RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK);
        while (RCC_GetSYSCLKSource() != 0x08){}
    }
    else{
    	while (1){}
    }
}



//init_all//////////////////////////////////////////////////////////////////////////////////////////////////
GPIO_InitTypeDef port;
ADC_InitTypeDef adc;
uint16_t counter;
int gruz0=0;
int tiktak=0;
int led0=0;
int i, t=0;
int adc_value;
int e=0 ,d=0 ,s=0;
int stopmot;

void init_all() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

    //button_for_led//////////////////////////////////////////////////////////////////////////////////////////////////
    GPIO_StructInit(&port);
    port.GPIO_Mode = GPIO_Mode_IPU;
    port.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    port.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &port);

    //button_for_motor//////////////////////////////////////////////////////////////////////////////////////////////////
    GPIO_StructInit(&port);
    port.GPIO_Mode = GPIO_Mode_IPU;
    port.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    port.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &port);

	//led//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    port.GPIO_Mode = GPIO_Mode_Out_PP;
    port.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    port.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &port);

    port.GPIO_Mode = GPIO_Mode_Out_PP;
    port.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0 | GPIO_Pin_3 |  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
    port.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &port);

    //ADC//////////////////////////////////////////////////////////////////////////////////////////////////
    port.GPIO_Mode  = GPIO_Mode_AIN;
    port.GPIO_Pin   = GPIO_Pin_0;
    GPIO_Init(GPIOA, &port);

    RCC_ADCCLKConfig (RCC_PCLK2_Div6);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    adc.ADC_Mode = ADC_Mode_Independent;
    adc.ADC_ScanConvMode = DISABLE;
    adc.ADC_ContinuousConvMode = ENABLE;
    adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    adc.ADC_DataAlign = ADC_DataAlign_Right;
    adc.ADC_NbrOfChannel = 0;

    ADC_RegularChannelConfig(ADC1,ADC_Channel_0, 1,ADC_SampleTime_28Cycles5);
    ADC_Init ( ADC1, &adc);

    ADC_Cmd (ADC1,ENABLE);

    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));

    ADC_Cmd (ADC1,ENABLE);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}



//LED//////////////////////////////////////////////////////////////////////////////////////////////////
void e0() {
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
}
void e1() {
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
}
void e2() {
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
}
void e3() {
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
}
void e4() {
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
}
void e5() {
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
}
void e6() {
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
}
void e7() {
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
}
void e8() {
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
}
void e9() {
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void d0() {
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
	GPIO_SetBits(GPIOB, GPIO_Pin_6);
	GPIO_SetBits(GPIOB, GPIO_Pin_1);
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	GPIO_SetBits(GPIOB, GPIO_Pin_3);
	GPIO_SetBits(GPIOB, GPIO_Pin_4);
}
void d1() {
	GPIO_SetBits(GPIOB, GPIO_Pin_3);
	GPIO_SetBits(GPIOB, GPIO_Pin_4);
}
void d2() {
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
	GPIO_SetBits(GPIOB, GPIO_Pin_4);
	GPIO_SetBits(GPIOB, GPIO_Pin_7);
	GPIO_SetBits(GPIOB, GPIO_Pin_1);
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
}
void d3() {
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
	GPIO_SetBits(GPIOB, GPIO_Pin_4);
	GPIO_SetBits(GPIOB, GPIO_Pin_7);
	GPIO_SetBits(GPIOB, GPIO_Pin_3);
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
}
void d4() {
	GPIO_SetBits(GPIOB, GPIO_Pin_6);
	GPIO_SetBits(GPIOB, GPIO_Pin_4);
	GPIO_SetBits(GPIOB, GPIO_Pin_7);
	GPIO_SetBits(GPIOB, GPIO_Pin_3);
}
void d5() {
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
	GPIO_SetBits(GPIOB, GPIO_Pin_6);
	GPIO_SetBits(GPIOB, GPIO_Pin_7);
	GPIO_SetBits(GPIOB, GPIO_Pin_3);
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
}
void d6() {
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
	GPIO_SetBits(GPIOB, GPIO_Pin_6);
	GPIO_SetBits(GPIOB, GPIO_Pin_7);
	GPIO_SetBits(GPIOB, GPIO_Pin_1);
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	GPIO_SetBits(GPIOB, GPIO_Pin_3);
}
void d7() {
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
	GPIO_SetBits(GPIOB, GPIO_Pin_4);
	GPIO_SetBits(GPIOB, GPIO_Pin_3);
}
void d8() {
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
	GPIO_SetBits(GPIOB, GPIO_Pin_6);
	GPIO_SetBits(GPIOB, GPIO_Pin_7);
	GPIO_SetBits(GPIOB, GPIO_Pin_1);
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	GPIO_SetBits(GPIOB, GPIO_Pin_3);
	GPIO_SetBits(GPIOB, GPIO_Pin_4);
}
void d9() {
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
	GPIO_SetBits(GPIOB, GPIO_Pin_6);
	GPIO_SetBits(GPIOB, GPIO_Pin_7);
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	GPIO_SetBits(GPIOB, GPIO_Pin_3);
	GPIO_SetBits(GPIOB, GPIO_Pin_4);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void s0() {
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_8);
	GPIO_SetBits(GPIOB, GPIO_Pin_9);
	GPIO_SetBits(GPIOB, GPIO_Pin_10);
	GPIO_SetBits(GPIOB, GPIO_Pin_11);
}
void s1() {
	GPIO_SetBits(GPIOB, GPIO_Pin_10);
	GPIO_SetBits(GPIOB, GPIO_Pin_11);
}
void s2() {
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_SetBits(GPIOB, GPIO_Pin_11);
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_8);
	GPIO_SetBits(GPIOB, GPIO_Pin_9);
}
void s3() {
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_SetBits(GPIOB, GPIO_Pin_11);
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_10);
	GPIO_SetBits(GPIOB, GPIO_Pin_9);
}
void s4() {
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_11);
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_10);
}
void s5() {
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_10);
	GPIO_SetBits(GPIOB, GPIO_Pin_9);
}
void s6() {
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_8);
	GPIO_SetBits(GPIOB, GPIO_Pin_9);
	GPIO_SetBits(GPIOB, GPIO_Pin_10);
}
void s7() {
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_SetBits(GPIOB, GPIO_Pin_11);
	GPIO_SetBits(GPIOB, GPIO_Pin_10);
}
void s08() {
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_8);
	GPIO_SetBits(GPIOB, GPIO_Pin_9);
	GPIO_SetBits(GPIOB, GPIO_Pin_10);
	GPIO_SetBits(GPIOB, GPIO_Pin_11);
}
void s9() {
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_9);
	GPIO_SetBits(GPIOB, GPIO_Pin_10);
	GPIO_SetBits(GPIOB, GPIO_Pin_11);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void off_led(){
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	GPIO_ResetBits(GPIOA, GPIO_Pin_6);
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	GPIO_ResetBits(GPIOB, GPIO_Pin_3);
	GPIO_ResetBits(GPIOB, GPIO_Pin_4);
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	GPIO_ResetBits(GPIOB, GPIO_Pin_8);
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);
	GPIO_ResetBits(GPIOB, GPIO_Pin_10);
	GPIO_ResetBits(GPIOB, GPIO_Pin_11);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
}
void led_print(int led){
	s = led / 100;
	d = (led / 10) % 10;
	e = led % 10;

	switch(e) {
	case(0): e0(); break;
	case(1): e1(); break;
	case(2): e2(); break;
	case(3): e3(); break;
	case(4): e4(); break;
	case(5): e5(); break;
	case(6): e6(); break;
	case(7): e7(); break;
	case(8): e8(); break;
	case(9): e9(); break;
	}

	switch(d) {
	case(0): d0();break;
	case(1): d1();break;
	case(2): d2();break;
	case(3): d3();break;
	case(4): d4();break;
	case(5): d5();break;
	case(6): d6();break;
	case(7): d7();break;
	case(8): d8();break;
	case(9): d9();break;
	}

	switch(s) {
	case(0): s0();break;
	case(1): s1();break;
	case(2): s2();break;
	case(3): s3();break;
	case(4): s4();break;
	case(5): s5();break;
	case(6): s6();break;
	case(7): s7();break;
	case(8): s08();break;
	case(9): s9();break;
	}
}



int fotodiod(int gruz){
	if (adc_value>3590){
		if (t==0){
			t=1;
			gruz--;
			off_led();
		}
	}
	else t=0;
	return gruz;
}



//fun_button//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int fun_but(int led1){
	if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_15) == 0){
		for(i=0;i<0x100000;i++);
		led1++;
   		off_led();
		for(i=0;i<0x100000;i++);
	}

	if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14) == 0){
	if(led1!=0) {
		for(i=0;i<0x100000;i++);
		led1--;
   		off_led();
		for(i=0;i<0x100000;i++);
	}
	}
	return led1;
}



void blink() {
	off_led();
	for(i=0;i<0x100000;i++);
	led_print(led0);
	for(i=0;i<0x100000;i++);
	off_led();
	for(i=0;i<0x100000;i++);
	led_print(led0);
	for(i=0;i<0x100000;i++);
	off_led();
	for(i=0;i<0x100000;i++);
	led_print(led0);
	for(i=0;i<0x100000;i++);
}


static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_GPIOA_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}



void start_eng() {
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
		while ( HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) != GPIO_PIN_SET );
	}
}



void stop_eng() {
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9) == 0){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
		while ( HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) != GPIO_PIN_SET );
		stopmot=1;
	}
}



int main(void) {
    SetSysClockTo72();
    __enable_irq();
    init_all();

    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    while (1) {
    	counter++;
    	if(counter == 15000) {
    		adc_value = ADC_GetConversionValue(ADC1);
    		switch (tiktak) {
    		case 0:
    			led0=fun_but(led0);
    			led_print(led0);
    			if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 0){
    				tiktak=1;
    				blink();
    			}
    			break;

    		case 1:
    			start_eng(); //fun_puska_mot
    			led0 = fotodiod(led0);
    			led_print(led0);
    			stop_eng(); //fun_ost
    			if ((led0==0)&&(stopmot==1)){
    				blink();
    				tiktak=0;
    			}
    			break;

    		}
    	}
    }
}

