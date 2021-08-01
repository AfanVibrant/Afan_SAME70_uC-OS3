/****************************************************************************
 * Afan SAME70 uC/OS-III rtos_start.c
 * Author : Afan Vibrant (AfanVibrant@outlook.com)
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#include <atmel_start.h>
#include <peripheral_clk_config.h>

#include "rtos_config.h"

#include "rtos.h"
#include "rtos_start.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const char *led_task_name = "led task";
static OS_TCB  led_task_tcb;
static CPU_STK led_task_stk[LEDRUN_THREAD_STKSZ/4];

/****************************************************************************
 * Public Functions Prototypes
 ****************************************************************************/

/****************************************************************************
 * Private Functions Prototypes
 ****************************************************************************/

static void led_thread_entry(void *parameter);

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static void display_task_info(void)
{
#if (OS_CFG_DBG_EN > 0u)
  OS_TCB  *ptcb;
  OS_ERR  err;

  CPU_SR_ALLOC();

  CPU_CRITICAL_ENTER();
  ptcb = OSTaskDbgListPtr;
  CPU_CRITICAL_EXIT();

  printf("==================================================\r\n");
  printf("  Prio     Used    Free    Per      Task      Usage\r\n");
  While(ptcb != (OS_TCB *)0) {
    printf("   %2d    %5d    %5d    %02d%%     %s     % /%\r\n",
      ptcb->Prio,
      ptcb->StkUsed,
      ptcb->StkFree,
      (ptcb->StkUsed * 100) / (ptcb->StkUsed + ptcb->StkFree),
      ptcb->NamePtr,
      ptcb->CPUUsage);

    CPU_CRITICAL_ENTER();
    p_tcb = p_tcb -> DbgNextPtr; //指向下一个任务的TCB
    CPU_CRITICAL_EXIT();
  }
#endif
}

/****************************************************************************
 * Name: led_thread_entry
 *
 * Description:
 *   Task for LED.
 *
 * Input Parameters:
 *   NONE.
 *
 * Returned Value:
 *   None.
 *
 ****************************************************************************/

static void led_thread_entry(void *parameter)
{
  OS_ERR err;

  (void)parameter;

#if (OS_TASK_STAT_EN > 0)
  OSStatInit();               /* Call this function in a task */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
  CPU_IntDisMeasMaxCurReset();
#endif

  while (1)
  {
    printf("led task run\r\n");
    display_task_info();
    rtos_task_delay_ms(500);
  }
}

/*
 * Example
 */
void uCos3_V308X_start(void)
{
  OS_ERR err;
  
  printf("uCos3 with LWIP demo run on SAME70Q21\r\n");

  Mem_Init();     /* Initialize Memory Management Module  */
  Math_Init();    /* Initialize Mathematical Module       */

  OS_CPU_SysTickInitFreq(CONF_CPU_FREQUENCY);   /* Initialize uC/OS-II periodic timer (SysTick).*/

  OSInit(&err);   /* Initialize uC/OS-II.                  */
  CPU_Init();     /* Initialize CPU */

  OSTaskCreate(&led_task_tcb, (CPU_CHAR *)led_task_name,
               led_thread_entry, NULL,
               (rtos_thread_t)LEDRUN_THREAD_PRIO,
               (CPU_STK *)led_task_stk,
               (CPU_STK_SIZE)(LEDRUN_THREAD_STKSZ/4/10),
               (CPU_STK_SIZE)(LEDRUN_THREAD_STKSZ/4),
               (OS_MSG_QTY  )16,
               (OS_TICK     )0,
                NULL,
               (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
               &err);
  if(OS_ERR_NONE == err) {
  }
  else {
    printf("%s task with priority-%d create fail\r\n", led_task_name, LEDRUN_THREAD_PRIO);
  }

  OSTimeSet(0, &err);

  /* Start multitasking (i.e. give control to uC/OS-III) */
  
  OSStart(&err);
}
