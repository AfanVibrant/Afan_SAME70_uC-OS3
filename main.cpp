/****************************************************************************
 * Afan SAME70 uC/OS-III main.cpp
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

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "rtos_start.h"

#ifdef __cplusplus
}
#endif /* __cplusplus */

int main(void)
{
  /* Initializes MCU, drivers and middleware */
  atmel_start_init();

  /* Disable the watchdog */
  WDT->WDT_MR = WDT_MR_WDDIS;

  SCB_EnableICache();

  printf("Start running uC/OS-III on Microchip SAME70\r\n");
  uCos3_V308X_start();
  
  /* Replace with your application code */
  while (1) 
  {
  }
}
