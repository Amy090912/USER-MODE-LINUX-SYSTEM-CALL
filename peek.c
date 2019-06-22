// peek



#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>

char *peek_ptr;
static char peek_buffer[9];
static int peek_buffer_size = 0;

static int open_sesame_peek(struct inode* inode_pointer, struct file* file_pointer) {
  
  printk(KERN_INFO "Opened_peek!");
  return 0;
}

static int bye_sesame_peek(struct inode* inode_pointer, struct file* file_pointer) {
  printk(KERN_INFO "Closed_peek");
  return 0;
}

static ssize_t pillage_sesame_peek(struct file *file, char *data, size_t length, loff_t *offset_in_file){

  if(peek_buffer_size == 8)
  {
    int cp = copy_to_user(data,peek_ptr,1);
    printk(KERN_INFO "peek value: %s\n", peek_ptr);
    return cp;
  
  }
  
  else
  {
    printk(KERN_INFO "not equal to 8");
  }
}


static ssize_t restock_sesame_peek(struct file *file, const char *data, size_t length, loff_t *offset_in_file){

  if((peek_buffer_size + length) < 8)
  {
    int cp = copy_from_user((&peek_buffer)+peek_buffer_size, data, length);
    peek_buffer_size = peek_buffer_size + length;
    return cp;
  }

  else if((peek_buffer_size + length) == 8)
  {
    int cp2 = copy_from_user((&peek_buffer)+peek_buffer_size, data, length);
    memcpy(&peek_ptr, peek_buffer,8);
    printk(KERN_INFO "peek pointer: %lx\n", peek_ptr);
    peek_buffer_size = peek_buffer_size + length;
    return cp2;
  }

  else 
{
  memset(peek_buffer, 0, 8);
  peek_buffer_size = 0;
  printk(KERN_INFO "larger than 8");
}
    
}





static struct device* device_data_peek;
static struct class* class_stuff_peek;

static struct file_operations file_ops_peek =
{
   .open = open_sesame_peek,
   .release = bye_sesame_peek,
   .read = pillage_sesame_peek,
   .write = restock_sesame_peek,
};

static int __init hi_peek(void) {

   int major = register_chrdev(0, "Hello peek", &file_ops_peek);   
   class_stuff_peek = class_create(THIS_MODULE, "hello class peek");
   device_data_peek = device_create(class_stuff_peek, NULL, MKDEV(major, 0), NULL,
			       "peek");
  
  printk(KERN_INFO "HI!\n");
  return 0;
}

static void __exit bye_peek(void) {
  printk(KERN_INFO "BYE!\n");
}

module_init(hi_peek);
module_exit(bye_peek);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("RL");
MODULE_DESCRIPTION("A sample driver that just says hello!");
