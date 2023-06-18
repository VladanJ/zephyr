#ifndef OWN_MUTEX_H_INCLUDED
#define OWN_MUTEX_H_INCLUDED

//#include "ipc-log.h"


#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/arch/cpu.h>
#include <zephyr/sys/printk.h>

namespace std
{
class mutex
  {
  public:
    struct k_sem _sema_internal;

    mutex()
    {
      k_sem_init(&_sema_internal, 0, K_SEM_MAX_LIMIT);
    }

    ~mutex()
    {
    }

    void lock()
    {
      printk("%s: Before!\n", __FUNCTION__);
      k_sem_take(&_sema_internal, K_FOREVER);
      printk("%s: After!\n", __FUNCTION__);
    }

    void unlock()
    {
      printk("%s: Before!\n", __FUNCTION__);
      k_sem_give(&_sema_internal);
      printk("%s: After!\n", __FUNCTION__);
    }

  private:

  };
}

#endif
