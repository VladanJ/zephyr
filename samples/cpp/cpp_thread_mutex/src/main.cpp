/*
 * Copyright (c) 2015-2016 Wind River Systems, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file C++ Synchronization demo.  Uses basic C++ functionality.
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/arch/cpu.h>
#include <zephyr/sys/printk.h>
#include <mutex.h>
#include <thread.h>

/* specify delay between greetings (in ms); compute equivalent in ticks */
#define SLEEPTIME  500
#define STACKSIZE 2000

K_THREAD_STACK_DEFINE(coop_stack, STACKSIZE);


std::mutex mut_main;
std::mutex mut_coop;

void coop_thread_entry(void)
{
	struct k_timer timer;

	k_timer_init(&timer, NULL, NULL);

	while (1) {
		/* wait for main thread to let us have a turn */
		

		/* say "hello" */
		printk("%s: Hello World!\n", __FUNCTION__);

		//sem_coop.wait();
		mut_coop.lock();

		/* wait a while, then let main thread have a turn */
		k_timer_start(&timer, K_MSEC(SLEEPTIME), K_NO_WAIT);
		k_timer_status_sync(&timer);
		//sem_main.give();
		printk("%s: Hello World2!\n", __FUNCTION__);
		mut_main.unlock();
	}
}

int main(void)
{
	struct k_timer timer;

	
    std::thread t1(coop_thread_entry, NULL);
			
	k_timer_init(&timer, NULL, NULL);

	while (1) {
		/* say "hello" */
		printk("%s: Hello World!\n", __FUNCTION__);

		/* wait a while, then let coop thread have a turn */
		k_timer_start(&timer, K_MSEC(SLEEPTIME), K_NO_WAIT);
		k_timer_status_sync(&timer);
		//sem_coop.give();
		mut_coop.unlock();

		/* Wait for coop thread to let us have a turn */
		//sem_main.wait();
		printk("%s: Hello World2!\n", __FUNCTION__);
		mut_main.lock();
	}

	return 0;
}
