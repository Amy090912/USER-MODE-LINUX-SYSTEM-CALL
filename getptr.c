//get pointer

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>

char buffer[1024];

static int open_sesame(struct inode* inode_pointer, struct file* file_pointer) {
  printk(KERN_INFO "Opened_getp!");
  return 0;
}

static int bye_sesame(struct inode* inode_pointer, struct file* file_pointer) {
  printk(KERN_INFO "Closed_getp");
  return 0;
}

static ssize_t pillage_sesame(struct file *file, char *data, size_t length, loff_t *offset_in_file){
  long ptr = buffer;
  int pcopyied=copy_to_user(data,&ptr, 8);
  printk(KERN_INFO "getptr pointer: %lx\n", ptr);
  return pcopyied;
}


/*
static ssize_t restock_sesame(struct file *file, const char *data, size_t length, loff_t *offset_in_file){
  return 0;
}
*/



static struct device* device_data;
static struct class* class_stuff;

static struct file_operations file_ops =
{
   .open = open_sesame,
   .release = bye_sesame,
   .read = pillage_sesame,
   //.write = restock_sesame,
};

static int __init hi(void) {

   int major = register_chrdev(0, "Hello", &file_ops);   
   class_stuff = class_create(THIS_MODULE, "hello class");
   device_data = device_create(class_stuff, NULL, MKDEV(major, 0), NULL,
			       "getptr");
  
  printk(KERN_INFO "HI!\n");
  return 0;
}

static void __exit bye(void) {
  printk(KERN_INFO "BYE!\n");
}

module_init(hi);
module_exit(bye);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("RL");
MODULE_DESCRIPTION("A sample driver that just says hello!");
