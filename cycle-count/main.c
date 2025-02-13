#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hardirq.h>
#include <linux/preempt.h>
#include <linux/sched.h>

void fib(int n, int prev1, int prev2) {
    // Base Case: when n gets less than 3
    if (n < 3) {
        return;
    }
    
    int curr = prev1 + prev2;
    printk(KERN_INFO "%d ", curr);
  
    return fib(n - 1, prev2, curr);
}

// Function that handles the first two terms and calls the recursive function
void printFib(volatile int n) {
    // When the number of terms is less than 1
    if (n < 1) {
        printk(KERN_INFO "Invalid number of terms\n");
    }
    // When the number of terms is 1
    else if (n == 1) {
        printk(KERN_INFO "%d ", 0);
    }
    // When the number of terms is 2
    else if (n == 2) {
        printk(KERN_INFO "%d %d", 0, 1);
    }
    // When number of terms greater than 2
    else {
        printk(KERN_INFO "%d %d ", 0, 1);
        fib(n, 0, 1);
    }
    return;
}

static int __init hello_start(void) {
    unsigned long flags;
    uint64_t start, end;
    unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;

    printk(KERN_INFO "Loading test module...\n");
    preempt_disable();              /*we disable preemption on our CPU*/
    raw_local_irq_save(flags);      /*we disable hard interrupts on our CPU*/


    /*at this stage we exclusively own the CPU*/
    asm volatile (
        "RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low));

    printFib(9);

    asm volatile (
        "RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (cycles_high1), "=r" (cycles_low1));
    
    raw_local_irq_restore(flags);


                                    /*we enable hard interrupts on our CPU*/
    preempt_enable();               /*we enable preemption*/
    start = ( ((uint64_t)cycles_high << 32) | cycles_low );
    end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
    printk(KERN_INFO "\n function execution time is %llu clock cycles", (end - start));
    
    return 0;
}

static void __exit hello_end(void) {
    printk(KERN_INFO "\n");
}

module_init(hello_start);

module_exit(hello_end);

MODULE_LICENSE("GPL");