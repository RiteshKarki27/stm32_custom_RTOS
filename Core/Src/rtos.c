/*
 * rtos.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Ritesh.S
 */

#include <stdint.h>

#include "rtos.h"
#include "qassert.h"

Q_DEFINE_THIS_FILE

OSThread * volatile OS_Current;
OSThread * volatile OS_Next;

OSThread *OS_thread[32+1];
uint8_t OS_threadNum;
uint8_t OS_currentIdx;
uint32_t OS_readySet;

OSThread idleThread;

void main_idleThread(void)
{
	while(1){
		OS_onIdle();
	}
}

void OS_init(void * stk, uint32_t stkSize)
{
	NVIC_setPriority(-2U, 0xFF);

	OSThread_start(&idleThread, &main_idleThread, stk, stkSize);
}

void OS_delay(uint32_t ticks)
{
	__enable_irq();

	Q_REQUIRE(OS_current != OS_Thread[0]);

	OS_current->timeout = ticks;

}
