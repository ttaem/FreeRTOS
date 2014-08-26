#include "stm32f4xx.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#include "FreeRTOS.h"
#include "task.h"
 
#include "serial.h"

void Delay(uint32_t nCount)
{
     __IO uint32_t i;   //__IO mean volatile
      for(i=0; nCount > i; i++);
}
 
void led1_task(void *p)
{
  vTaskDelay(100);
  while(1) {
    GPIO_SetBits(GPIOG, GPIO_Pin_6);  //Delay(1000000); 
    vTaskDelay(1000);
   GPIO_ResetBits(GPIOG, GPIO_Pin_6);  //Delay(1000000);
    vTaskDelay(1000);
  }
}

void led2_task(void *p)
{
  vTaskDelay(200);
  while(1) {
    GPIO_SetBits(GPIOG, GPIO_Pin_7);  //Delay(5000000); 
    vTaskDelay(1000);
    GPIO_ResetBits(GPIOG, GPIO_Pin_7);  //Delay(5000000);
    vTaskDelay(1000);
  }
}

void led3_task(void *p)
{
  vTaskDelay(300);
  while(1) {
    GPIO_SetBits(GPIOG, GPIO_Pin_10);  //Delay(5000000); 
    vTaskDelay(1000);
    GPIO_ResetBits(GPIOG, GPIO_Pin_10);  //Delay(5000000);
    vTaskDelay(1000);
  }
}

void led4_task(void *p)
{
  vTaskDelay(400);
  while(1) {
    GPIO_SetBits(GPIOG, GPIO_Pin_12);  //Delay(5000000); 
    vTaskDelay(1000);
    GPIO_ResetBits(GPIOG, GPIO_Pin_12);  //Delay(5000000);
    vTaskDelay(1000);
    
    vSerialPutString(0, "zzz", 3);
  }
}
 
void main(void)
{
	char str[4] = "zzz";

  
    GPIO_InitTypeDef GPIO_InitStructure;    //structure
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);    
 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_10|GPIO_Pin_12;  //Pin_Enable
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
    
    xSerialPortInitMinimal(9600, 10);
    
  //xTaskCreate(led1_task, (signed char *)"led1_task", 128, 0, tskIDLE_PRIORITY+1, 0);
  //xTaskCreate(led2_task, (signed char *)"led2_task", 128, 0, tskIDLE_PRIORITY+2, 0);
  //xTaskCreate(led3_task, (signed char *)"led3_task", 128, 0, tskIDLE_PRIORITY+3, 0);
  //xTaskCreate(led4_task, (signed char *)"led4_task", 128, 0, tskIDLE_PRIORITY+4, 0);
    
   //vSerialPutString(0, str, 3);
   
  vTaskStartScheduler();
}
  




 
   
