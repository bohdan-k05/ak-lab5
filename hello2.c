// SPDX-License-Identifier: UNLICENSED
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include "hello1.h"

MODULE_AUTHOR("Bohdan Krokhun <krokhun.bohdan@lll.kpi.ua>");
MODULE_DESCRIPTION("Hello2 module of lab 5");
MODULE_LICENSE("Dual BSD/GPL");

extern void print_hello(void);

static unsigned int num = 1; // Default value
module_param(num, uint, S_IRUGO);
MODULE_PARM_DESC(num, "Number of times \"Hello, world!\" will be printed");

int i;

static int __init hello2_init(void) {
	if (num == 0 || (num >= 5 && num <= 10)) {
		pr_warn("Parameter is 0 or is in 5 to 10 range.\n");
	}
	
	if (num > 10) {
		pr_err("Parameter should be less than 10.\n");
		return -EINVAL;
	}
	
	for (i = 0; i < num; i++) {
		print_hello();
	}
	
	return 0;
}

static void __exit hello2_exit(void) {
	pr_info("Goodbye, world from hello2!\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
