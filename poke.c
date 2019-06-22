//poke
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>

 
static char poke_buffer[9];
static int poke_buffer_size = 0;
char* poke_ptr;

static int open_sesame_poke(struct inode* inode_pointer, struct file* file_pointer) {
  
  printk(KERN_INFO "Opened_poke!");
  return 0;
}

static int bye_sesame_poke(struct inode* inode_pointer, struct file* file_pointer) {
  printk(KERN_INFO "Closed_poke");
  return 0;
}

/*
static ssize_t pillage_sesame_poke(struct file *file, char *data, size_t length, loff_t *offset_in_file){
  
  return 0;
  
}
*/


static ssize_t restock_sesame_poke(struct file *file, const char *data, size_t length, loff_t *offset_in_file){

printk(KERN_INFO "poke opened ");

if((poke_buffer_size + length) <9)
{
  int cp = copy_from_user((&poke_buffer)+poke_buffer_size, data, length); 
  poke_buffer_size = poke_buffer_size + length;
}

else if((poke_buffer_size + length) ==9)
{
  int cp2 = copy_from_user((&poke_buffer)+poke_buffer_size, data, length);
  memcpy(&poke_ptr, poke_buffer,8);
  *poke_ptr = poke_buffer[8];
  //printk(KERN_INFO "poke_ptr: %lx\n", poke_ptr);
  //printk(KERN_INFO "poke_value: %s\n", poke_ptr);
  poke_buffer_size = 0;
  memset(poke_buffer, 0, 9);
}

else 
{
  memset(poke_buffer, 0, 9);
  poke_buffer_size = 0;
  printk(KERN_INFO "larger than 9 ");
}


  return 0;
}





static struct device* device_data_poke;
static struct class* class_stuff_poke;

static struct file_operations file_ops_poke =
{
   .open = open_sesame_poke,
   .release = bye_sesame_poke,
   //.read = pillage_sesame_poke,
   .write = restock_sesame_poke,
};

static int __init hi_poke(void) {

   int major = register_chrdev(0, "Hello poke", &file_ops_poke);   
   class_stuff_poke = class_create(THIS_MODULE, "hello class poke");
   device_data_poke = device_create(class_stuff_poke, NULL, MKDEV(major, 0), NULL,
			       "poke");
  
  printk(KERN_INFO "HI!\n");
  return 0;
}

static void __exit bye_poke(void) {
  printk(KERN_INFO "BYE!\n");
}

module_init(hi_poke);
module_exit(bye_poke);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("RL");
MODULE_DESCRIPTION("A sample driver that just says hello!");
