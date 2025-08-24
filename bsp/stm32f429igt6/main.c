#include "board.h"
#include "rtthread.h"

#if defined(RT_USER_MAIN) && defined(RT_USING_HEAP)

// 从内部SRAM里面分配一部分静态内存来作为rtt的堆空间，这里配置为4KB 
#define RT_HEAP_SIZE 4096
static uint32_t rt_heap[RT_HEAP_SIZE];
RT_WEAK void *rt_heap_begin_get(void)
{
    return rt_heap;
}

RT_WEAK void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}

#endif

// TCB
static rt_thread_t led1_thread;
static rt_thread_t led4_thread;

// thread function
static void led1_thread_entry(void *param) {
		while (1) {
		LED1_ON;
		rt_thread_delay(500);		// delay for 500 ticks
		LED1_OFF;
		rt_thread_delay(500);
		rt_kprintf("led1 blink %dms\n\r", 500);
	}
}

static void led4_thread_entry(void *param) {
		while (1) {
		LED4_ON;
		rt_thread_delay(100);		// delay for 100 ticks
		LED4_OFF;
		rt_thread_delay(100);
		rt_kprintf("\tled4 blink %dms\n\r", 100);
	}
}



/* create static thread. static thread is store in code segment
 *
 */
int main(void)
{
    /* create led1 app thread dynamicly */
	led1_thread = rt_thread_create(
			"led1",									// thread name
			led1_thread_entry,						// thread function
			RT_NULL,								// params of thread function
			512,									// stack size
			3,										// thread priority
			20);									// time slice of thread. (ticks)
	
	/* start thread */
	if (led1_thread != RT_NULL)
		rt_thread_startup(led1_thread);
	else
		return -1;

	led4_thread = rt_thread_create(
			"led4",									// thread name
			led4_thread_entry,						// thread function
			RT_NULL,								// params of thread function
			512,									// stack size
			4,										// thread priority
			20);									// time slice of thread. (ticks)
	
	/* start thread */
	if (led4_thread != RT_NULL)
		rt_thread_startup(led4_thread);
	else
		return -1;

}


