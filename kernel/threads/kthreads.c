/*
 * kthreads.c
 *
 *  Created on: Apr 23, 2015
 *      Author: mwkurian
 */

#include "kthread.h"
#include <global_defs.h>
#include "klibc.h"
#include "scheduler.h"

// kthread_handle* kthread_create(kthread_callback_handler cb_handler)
// {
// 	kthread_handle * kthread = kmalloc(sizeof(kthread_handle));
// 	kthread->cb_handler = cb_handler;
// 	return kthread;
// }

kthread_handle* kthread_create()
{
    vm_use_kernel_vas();
    kthread_handle * kthread = kmalloc(sizeof(kthread_handle));
    kthread->parent_pid = get_process_pid();
    return kthread;
}

uint32_t kthread_start(kthread_handle * kthread)
{
	sched_task * task = sched_create_task_from_kthread(kthread, 10);
	sched_add_task(task);

    return kthread->parent_pid;
}

void kthread_save_state(kthread_handle* kthread)
{
    asm("MOV %0, r0":"=r"(kthread->R0)::);
    asm("MOV %0, r1":"=r"(kthread->R1)::);
    asm("MOV %0, r2":"=r"(kthread->R2)::);
    asm("MOV %0, r3":"=r"(kthread->R3)::);
    asm("MOV %0, r4":"=r"(kthread->R4)::);
    asm("MOV %0, r5":"=r"(kthread->R5)::);
    asm("MOV %0, r6":"=r"(kthread->R6)::);
    asm("MOV %0, r7":"=r"(kthread->R7)::);
    asm("MOV %0, r8":"=r"(kthread->R8)::);
    asm("MOV %0, r9":"=r"(kthread->R9)::);
    asm("MOV %0, r10":"=r"(kthread->R10)::);
    asm("MOV %0, r11":"=r"(kthread->R11)::);
    asm("MOV %0, r12":"=r"(kthread->R12)::);
    asm("MOV %0, r13":"=r"(kthread->R13)::);
    asm("MOV %0, r14":"=r"(kthread->R14)::);
    asm("MOV %0, r15":"=r"(kthread->R15)::);
}


void kthread_load_state(kthread_handle* kthread)
{
    asm("MOV r0, %0"::"r"(kthread->R0):);
    asm("MOV r1, %0"::"r"(kthread->R1):);
    asm("MOV r2, %0"::"r"(kthread->R2):);
    asm("MOV r3, %0"::"r"(kthread->R3):);
    asm("MOV r4, %0"::"r"(kthread->R4):);
    asm("MOV r5, %0"::"r"(kthread->R5):);
    asm("MOV r6, %0"::"r"(kthread->R6):);
    asm("MOV r7, %0"::"r"(kthread->R7):);
    asm("MOV r8, %0"::"r"(kthread->R8):);
    asm("MOV r9, %0"::"r"(kthread->R9):);
    asm("MOV r10, %0"::"r"(kthread->R10):);
    asm("MOV r10, %0"::"r"(kthread->R10):);
    asm("MOV r12, %0"::"r"(kthread->R12):);

    asm("MOV r13, %0"::"r"(kthread->R13):);

    asm("MOV r14, %0"::"r"(kthread->R14):);

    asm("MOV r15, %0"::"r"(kthread->R15):);
}



