/*
 * bsp.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Ritesh.S
 */
#include <stdint.h>

#include "bsp.h"
#include "rtos.h"

#define LED_RED GPIO_PIN_0
#define LED_GREEN GPIO_PIN_5


static uint32_t volatile tickCtr;

void Systick_Handler(void)
{
	OS_tick();

	__disable_irq();
	OS_shed();
	__enable_irq();
}

void BSP_init(void)
{
	/*To be written later*/
}

void BSP_ledRedOn(void)
{
	HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
}

void BSP_ledGreenOn(void)
{
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
}

void BSP_ledRedOff(void)
{
	HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
}

void BSP_ledGreenOff(void)
{
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
}

void OS_onStartup(void)
{
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / BSP_TICKS_PER_SEC);

	NVIC_SetPriority(SysTick_IRQn, 0U);
}


void OS_onIdle(void)
{
	__WFI();
}

void Q_onAssert(char const *module, int loc)
{
	void(module);
	void(loc);
	NVIC_SystemReset();
}
