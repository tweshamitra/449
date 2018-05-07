/*
 * /dev/rps skeleton code
 *
 *
 */

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/random.h>
#include <asm/uaccess.h>

/*
 * rps_read is the function called when a process calls read() on
 * /dev/rps.  It writes count bytes to the buffer passed in the
 * read() call.
 */

//global variable to hold the mode
char mode = 0;

//helper function that returns a byte
unsigned char get_random_byte(int max, int min){	
	unsigned char c;
	get_random_bytes(&c, 1);
	return c%max + min;
	
}

/*  This is the function called when someone does a read() call.
 *  The function will write count number bytes to the buffer passed in
 *  with the use of copy_to_user(). It will decide which bytes to write
 *  based on the current mode. 
 */
static ssize_t rps_read(struct file * file, char * buf,
			  size_t count, loff_t *ppos)
{        
	int i;
	char x; 
	switch(mode){
		case 0:
			for(i = 0; i < count; i++){
				x = get_random_byte(3,1);
				copy_to_user(buf+i, &x, 1);		
			}
			break;
		case 1:
			for(i = 0; i < count; i++){
				copy_to_user(buf+i, &mode, 1);
			}
			break;
		case 2:
			for(i = 0; i <count; i ++){
				copy_to_user(buf+i, &mode, 1);	
			}
			break;
		case 3:	
			for(i = 0; i <count; i++){
				copy_to_user(buf+i, &mode, 1);
			}
			break;
	}		
	return count;
}

/*
 * rps_write is the function called when a process calls write() on
 * /dev/rps.  It reads count bytes from the buffer passed in the
 * write() call through the use of copy_from_user. In this case,  
 * rps_ctrl is writing a single byte which is stored as mode in this 
 * program. We just want the last byte of the buffer which is why 
 * we need to do use count-1;
 */

static ssize_t rps_write(struct file * file, const char * buf,
			  size_t count, loff_t *ppos)
{
       //printk(KERN_ERR "write(file, 0x%p, %d, %lld)\n", buf, count, *ppos);
	copy_from_user(&mode, &buf[count-1], 1);
	return count;
}

/*
 * Now we have two file operations: read, write
 */

static const struct file_operations rps_fops = {
	.owner		= THIS_MODULE,
	.read		= rps_read,
        .write          = rps_write,
};

static struct miscdevice rps_dev = {
	/*
	 * We don't care what minor number we end up with, so tell the
	 * kernel to just pick one.
	 */
	MISC_DYNAMIC_MINOR,
	/*
	 * Name ourselves /dev/hello.
	 */
	"rps",
	/*
	 * What functions to call when a program performs file
	 * operations on the device.
	 */
	&rps_fops
};

static int __init
rps_init(void)
{
	int ret;

	/*
	 * Create the "rps" device in the /sys/class/misc directory.
	 * Udev will automatically create the /dev/rps device using
	 * the default rules.
	 */
	ret = misc_register(&rps_dev);
	if (ret)
                printk(KERN_ERR "Unable to register \"Hello, world!\" misc device\n");
        else {
                printk(KERN_ERR "Registered device under <MAJOR , MINOR><%d %d>\n" , 10, rps_dev.minor);
                printk(KERN_ERR "Create device file using: mknod /dev/rps c %d %d\n", 10, rps_dev.minor);
        }

	return ret;
}

module_init(rps_init);

static void __exit
rps_exit(void)
{
	misc_deregister(&rps_dev);
}

module_exit(rps_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Twesha Mitra <twm17@pitt.edu>");
MODULE_DESCRIPTION("/dev/rps skeleton code");
MODULE_VERSION("dev");
