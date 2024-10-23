#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>  /* copy_from_user */


#include "drv_probe.h"

struct class *g_cls = NULL;
struct cdev g_cdev;
dev_t g_dev = 0;


static int device_open(struct inode *inode, struct file *file)
{   
    printk(KERN_INFO "Device opened\n");
    return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Device closed\n");
    return 0;
}

static ssize_t device_read(struct file *file, char __user *buffer, size_t length, loff_t *offset)
{
    char *message = "Hello from the kernel!";
    int message_length = strlen(message);
    int bytes_read = 0;

    if (*offset >= message_length)
        return 0;

    if (*offset + length > message_length)
        length = message_length - *offset;

    if (copy_to_user(buffer, message + *offset, length))
        return -EFAULT;

    *offset += length;
    bytes_read = length;

    return bytes_read;
}

static struct file_operations fops = {
    .open = device_open,
    .release = device_release,
    .read = device_read,
};

static int __init char_dev_init(void)
{
    int result;

    dev_t dev;
    struct cdev *cdev = &g_cdev;
    struct class *cls;
    struct device *device;

    // 分配设备号
    result = alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME);
    if (result < 0) {
        printk(KERN_ALERT "Failed to allocate character device region\n");
        goto FAILED_0;
    }

    // 初始化字符设备并添加到内核
    cdev_init(cdev, &fops);
    cdev->owner = THIS_MODULE;
    result = cdev_add(cdev, dev, 1);
    if (result < 0) {
        printk(KERN_ALERT "Failed to add character device\n");
        goto FAILED_1;
    }

    // 创建类
    cls = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(cls))
    {
        printk(KERN_ALERT "Failed to create class\n");
        goto FAILED_2;
    }

    // 创建设备文件
    device = device_create(cls, NULL, dev, NULL, DEVICE_NAME);
    if (IS_ERR(device))
    {
        printk(KERN_ALERT "Failed to create class\n");
        goto FAILED_3;
    }

    g_dev = dev;
    g_cls = cls;
    
    printk(KERN_INFO "Character device registered\n");
    return 0;

FAILED_3:
    class_destroy(cls);
FAILED_2:
    cdev_del(cdev);
FAILED_1:
    unregister_chrdev_region(dev, 1);
FAILED_0:
    return -1;
}

static void __exit char_dev_exit(void)
{
    device_destroy(g_cls,g_dev);
    class_destroy(g_cls);
    cdev_del(&g_cdev);
    unregister_chrdev_region(g_dev, 1);
    printk(KERN_INFO "Character device unregistered\n");
}

module_init(char_dev_init);
module_exit(char_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple character device driver");
