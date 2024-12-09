// SPDX-License-Identifier: UNLICENSED
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include "hello1.h"

MODULE_AUTHOR("Bohdan Krokhun <krokhun.bohdan@lll.kpi.ua>");
MODULE_DESCRIPTION("Hello1 module of lab5");
MODULE_LICENSE("Dual BSD/GPL");

struct event_list {
	struct list_head list;
	ktime_t start_time;
	ktime_t end_time;
};

static LIST_HEAD(event_list_head);

static int __init hello1_init(void) {
	pr_info("Hello, world from hello1!\n");
	return 0;
}

void print_hello(void) {
	struct event_list *event = kmalloc(sizeof(*event), GFP_KERNEL);

	if (!event) {
		pr_err("Failed to allocate memory for the event.\n");
		return;
	}

	event->start_time = ktime_get();
	pr_info("Hello, world!\n");
	event->end_time = ktime_get();

	list_add_tail(&event->list, &event_list_head);
}
EXPORT_SYMBOL(print_hello);

static void __exit hello1_exit(void) {
	struct event_list *event;
	struct list_head *pos, *tmp;

	list_for_each_safe(pos, tmp, &event_list_head) {
		event = list_entry(pos, struct event_list, list);
		pr_info("Print time: %lld ns\n", 
			(ktime_to_ns(event->end_time) - ktime_to_ns(event->start_time)));
		list_del(pos);
		kfree(event);
	}

	pr_info("Goodbye, world from hello1!\n");
}

module_init(hello1_init);
module_exit(hello1_exit);
