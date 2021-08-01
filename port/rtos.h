/****************************************************************************
 * Afan SAME70 uC/OS-III port/rtos.h
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

#ifndef PORT_RTOS_H
#define PORT_RTOS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include  <cpu.h>
#include  <lib_math.h>
#include  <lib_mem.h>
#include  <os.h>

#include  <os_cfg_app.h>

#include <stdbool.h>
#include <compiler.h>

#include "rtos_config.h"

#define rtos_irq_enter()          CPU_SR_ALLOC(); \
                                  CPU_CRITICAL_ENTER(); \
                                  OSIntEnter(); \
                                  CPU_CRITICAL_EXIT();

#define rtos_irq_exit()           OSIntExit();

#define rtos_enter_critical()     CPU_SR_ALLOC(); \
                                  CPU_CRITICAL_ENTER()
#define rtos_exit_critical()      CPU_CRITICAL_EXIT()

typedef OS_SEM                    rtos_sem_t;
typedef OS_MUTEX                  rtos_mutex_t;
typedef OS_Q                      rtos_mbox_t;
typedef OS_PRIO                   rtos_thread_t;
typedef OS_TMR                   *rtos_timer_t;
typedef unsigned int              rtos_prot_t;

#define RTOS_TICK_PER_SECOND      OS_CFG_TICK_RATE_HZ
#define RTOS_USEC_PER_TICK        (1000000/RTOS_TICK_PER_SECOND)

#define rtos_task_delay(n)        OS_ERR err; \
                                  OSTimeDly(n, OS_OPT_TIME_DLY, &err)
#define rtos_task_delay_ms(n)     rtos_task_delay(1000*n/RTOS_USEC_PER_TICK)
#define rtos_task_delay_us(n)     uint32_t tick = (n > RTOS_USEC_PER_TICK) ? \
                                                  (n + 1)/RTOS_USEC_PER_TICK : 1; \
                                  rtos_task_delay(tick)

#define RTOS_MBOX_NULL            (rtos_mbox_t *)0
#define RTOS_SEM_NULL             (rtos_sem_t  *)0

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PORT_RTOS_H */
