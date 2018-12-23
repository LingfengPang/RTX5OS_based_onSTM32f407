/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/
 
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include "stm32f4xx_hal.h" //包含32HAL库
#ifdef RTE_Compiler_EventRecorder
#include "EventRecorder.h"
#include "led.h"
#endif

//GPIO初始化

/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/


//线程1
void led1(){
	
	while(1){HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_6);
	osDelay(500);
	HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_6);
	osDelay(500);}
}
//线程2
void led2(){
	
	while(1)
		{HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_7);
	osDelay(300);
	HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_7);
	osDelay(300);}
}
void app_main (void *argument) {
 
  // ...放置各种初始化程序和线程函数
	MX_GPIO_Init();
	osThreadNew(led1,NULL,NULL);
	osThreadNew(led2,NULL,NULL);
	 
  for (;;) {
		
  }
}
 
int main (void) {
 
  // System Initialization
  SystemCoreClockUpdate();
#ifdef RTE_Compiler_EventRecorder
  // Initialize and start Event Recorder
  EventRecorderInitialize(EventRecordError, 1U);
#endif
  // ...
 
  osKernelInitialize();                 // Initialize CMSIS-RTOS
  osThreadNew(app_main, NULL, NULL);    // Create application main thread
  osKernelStart();                      // Start thread execution
  for (;;) {}
}
