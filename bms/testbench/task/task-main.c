/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * Memory Functions
 *
 * Copied from FADS ROM, Dan Malek (dmalek@jlc.net)
 */

#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>

#include "FreeRTOS.h"
#include "task.h"

struct task_para {
  uint32_t XPID;
};

void vApplicationIdleHook(void) {
  //vCoRoutineSchedule();

  //volatile size_t xFreeStackSpace;

  //xFreeStackSpace = xPortGetFreeHeapSize();

  //printf("free heap size %x\n",xFreeStackSpace);
}

static void simple_task(void *pvParameters) {
  struct task_para para;
  para.XPID = *(uint32_t*)pvParameters;
  int running_times = 0;
  for (;;) {
    running_times++;
    printf("xpid %d task running %d times \r\n", para.XPID, running_times);
    vTaskDelay(1000 * para.XPID);
    //taskYIELD();
  }
}


int task_main(int argc, char *argv[]) {
  const char * task_name[4] = {"task1", "task2", "task3", "task4"};
  static TaskHandle_t simple_task_handler[4] = {0};
  struct task_para test_para[4] = {0};
  for(int i = 0; i<4; i++){
    test_para[i].XPID = i+1;
  }

  for(int i = 0; i<4; i++){
    int priority = tskIDLE_PRIORITY + 2;
    if(i<2){
      priority = tskIDLE_PRIORITY + 1;
    }

    printf("create xpid %d task, priority %d\n", test_para[i].XPID, priority);

    if (xTaskCreate(simple_task, task_name[i], configMINIMAL_STACK_SIZE + 10,
                    &test_para[i].XPID, priority,
                    &simple_task_handler[i]) != pdPASS) {
      printf("task %d create fail\n", test_para[i].XPID);
      while (1);
    }
  }
  printf("xTaskResumeAll...\n");
	xTaskResumeAll();
  printf("vTaskStartScheduler...\n");
  vTaskStartScheduler();
  printf("scheduler...\n");
  for (;;);
  return 0;

}

void task_init(void) { register_testbench("task", task_main, NULL); }

testbench_init(task_init);


