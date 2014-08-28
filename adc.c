#include "stm32f4xx_adc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
//#include "led.h"
//#include "stm32f4_discovery.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_dac.h"




void adc_configure(void)
{
	ADC_InitTypeDef ADC_init_structure; //Structure for adc confguration
	GPIO_InitTypeDef GPIO_initStructre; //Structure for analog input pin
	//Clock configuration
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3,ENABLE);//The ADC1 is connected the APB2 peripheral bus thus we will use its clock source
	RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOFEN,ENABLE);//Clock for the ADC port!! Do not forget about this one ;)
	//Analog pin configuration
	GPIO_StructInit(&GPIO_initStructre);
	GPIO_initStructre.GPIO_Pin = GPIO_Pin_10;//The channel 10 is connected to PC0
	GPIO_initStructre.GPIO_Mode = GPIO_Mode_AN; //The PF10 pin is configured in analog mode
	GPIO_initStructre.GPIO_PuPd = GPIO_PuPd_NOPULL; //We don't need any pull up or pull down
	GPIO_Init(GPIOF,&GPIO_initStructre);//Affecting the port with the initialization structure configuration
	//ADC structure configuration
	ADC_DeInit();
	ADC_init_structure.ADC_DataAlign = ADC_DataAlign_Right;//data converted will be shifted to right
	ADC_init_structure.ADC_Resolution = ADC_Resolution_12b;//Input voltage is converted into a 12bit number giving a maximum value of 4096
	ADC_init_structure.ADC_ContinuousConvMode = ENABLE; //the conversion is continuous, the input data is converted more than once
	ADC_init_structure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;// conversion is synchronous with TIM1 and CC1 (actually I'm not sure about this one :/)
	ADC_init_structure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//no trigger for conversion
	ADC_init_structure.ADC_NbrOfConversion = 1;//I think this one is clear :p
	ADC_init_structure.ADC_ScanConvMode = DISABLE;//The scan is configured in one channel
	ADC_Init(ADC3,&ADC_init_structure);//Initialize ADC with the previous configuration
	//Enable ADC conversion
	ADC_Cmd(ADC3,ENABLE);
	//Select the channel to be read from
	//ADC_RegularChannelConfig(ADC3,ADC_Channel_10,1,ADC_SampleTime_144Cycles);
	ADC_RegularChannelConfig(ADC3,ADC_Channel_8,1,ADC_SampleTime_144Cycles);
}

int adc_convert(void)
{
	ADC_SoftwareStartConv(ADC3);//Start the conversion
	while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC));//Processing the conversion
	return ADC_GetConversionValue(ADC3); //Return the converted data
}




