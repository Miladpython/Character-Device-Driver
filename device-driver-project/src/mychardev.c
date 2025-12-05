#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>

#define DEVICE_NAME "mychardev"

static char kernel_buffer[256] = "Hello from kernel!";
static int dev_major = 0;
static struct cdev my_cdev;

/* open() */
static int my_open(struct inode *inode, struct file *file)
{
    pr_info("mychardev: device opened\n");
    return 0;
}

/* read() */
static ssize_t my_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
    return simple_read_from_buffer(buf, count, ppos, kernel_buffer, strlen(kernel_buffer));
}

/* write() */
static ssize_t my_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    if (count > sizeof(kernel_buffer))
        count = sizeof(kernel_buffer);

    if (copy_from_user(kernel_buffer, buf, count))
        return -EFAULT;

    pr_info("mychardev: received from user: %s\n", kernel_buffer);
    return count;
}

/* release() */
static int my_release(struct inode *inode, struct file *file)
{
    pr_info("mychardev: device closed\n");
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .read = my_read,
    .write = my_write,
    .release = my_release,
};

static int __init my_init(void)
{
    int ret;
    dev_t dev;

    ret = alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME);
    if (ret < 0)
        return ret;

    dev_major = MAJOR(dev);

    cdev_init(&my_cdev, &fops);
    cdev_add(&my_cdev, dev, 1);

    pr_info("mychardev: registered with major %d\n", dev_major);
    return 0;
}

static void __exit my_exit(void)
{
    cdev_del(&my_cdev);
    unregister_chrdev_region(MKDEV(dev_major, 0), 1);
    pr_info("mychardev: unregistered\n");
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);

