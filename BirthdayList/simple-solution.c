#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

struct birthday{
	char *name;
	int month;
	int day;
	int year;
	struct list_head list;
};

/**
 * The following defines and initializes a list_head object named birthday_list
 */
static LIST_HEAD(birthday_list);

/*
*struct has to be initiated outside rather than inside source code. Make will
not execute with constant errors. Ubuntu 18v!
*/
struct birthday *people,*people1,*people2,*people3,*people4;
struct birthday *ptr1;
struct birthday *ptr1, *next;

//itrate through the list and keepipng track of reference
void delete_Oldest(struct list_head *birthday_list){
        //delete the oldest within linked list
        int cal_year = 0;
        int list_info = 0;
        int itrated_list = 0;
	
        list_for_each_entry(ptr1, birthday_list, list){
                if((2020 - ptr1->year) > cal_year){
                cal_year = (2020 - ptr1->year);
                itrated_list = list_info;
                }
        list_info = list_info + 1;
        }

        list_info = 0;
        list_for_each_entry_safe(ptr1, next, birthday_list, list){
                if(list_info == itrated_list){
                list_del(&ptr1->list);
                kfree(ptr1);
                }
        list_info = list_info + 1;
        }
}

int simple_init(void)
{
       /*
	*The kernal uses the loglevel to decide whether to print the message to the console.
	*printk "different loglevels.(Kern_Info = Some information).
	*/
	printk(KERN_INFO "Loading Module\n");

	people = kmalloc(sizeof(*people),GFP_KERNEL);
	people->name = "Kwame";
	people->month = 9;
	people->day = 19;
	people->year = 1992;
	INIT_LIST_HEAD(&people->list);
	//add a new node
	list_add_tail(&people->list, &birthday_list);

	people1 = kmalloc(sizeof(*people1),GFP_KERNEL);
	people1->name = "Kofi";
	people1->month = 5;
        people1->day = 8;
        people1->year = 1993;
        INIT_LIST_HEAD(&people1->list);
        list_add_tail(&people1->list, &birthday_list);

	people2 = kmalloc(sizeof(*people2),GFP_KERNEL);
	people2->name = "Ethan";
	people2->month = 1;
        people2->day = 21;
        people2->year = 1994;
        INIT_LIST_HEAD(&people2->list);
        list_add_tail(&people2->list, &birthday_list);

	people3 = kmalloc(sizeof(*people3),GFP_KERNEL);
	people3->name = "Neon";
	people3->month = 4;
        people3->day = 25;
        people3->year = 1991;
        INIT_LIST_HEAD(&people3->list);
        list_add_tail(&people3->list, &birthday_list);

	people4 = kmalloc(sizeof(*people4),GFP_KERNEL);
	people4->name = "Fernando";
	people4->month = 12;
        people4->day = 19;
        people4->year = 1995;
        INIT_LIST_HEAD(&people4->list);
        list_add_tail(&people4->list, &birthday_list);


        //all 5 birthday displayed
        list_for_each_entry(ptr1, &birthday_list, list){
                printk(KERN_INFO "Birthday: Name %s Month %d Day %d Year %d\n",
                ptr1->name, ptr1->month, ptr1->day, ptr1->year);
	}
	
	//calling method to be run in simple_init when sudo command is run.
	//delete must be at the top or errors for data structure being called before hands.
	delete_Oldest(&birthday_list);
	return 0;
}


void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");

	list_for_each_entry_safe(ptr1, next, &birthday_list, list){
		printk(KERN_INFO "Removing %s %d %d %d\n",
		ptr1->name, ptr1->month, ptr1->day, ptr1->year);
		
		list_del(&ptr1->list);
                kfree(ptr1);
	}
	printk(KERN_INFO "Free memory...\n");
}


module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel Data Structures");
MODULE_AUTHOR("SGG");
