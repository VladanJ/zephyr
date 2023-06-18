#ifndef OWN_THREAD_H_INCLUDED
#define OWN_THREAD_H_INCLUDED


#include <zephyr/kernel.h>



namespace std
{

#define STACKSIZE 2000

K_THREAD_STACK_DEFINE(coop_stack, STACKSIZE);


  class thread {
  public:
    struct k_thread _thread;

    thread(void (*func)(), void* arg) {

	    k_thread_create(&_thread, coop_stack, STACKSIZE,
	    (k_thread_entry_t) func,
	    NULL, NULL, NULL, K_PRIO_COOP(7), 0, K_NO_WAIT);
  }

  ~thread() {
    k_thread_join(&_thread, K_NO_WAIT);
  }

  private:
    
 };
}

#endif
