/*  
 *  Hello_Kernel_Module.c
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */

#include <linux/fs.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>

#include <linux/kthread.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

static struct task_struct *kthread;

struct file* phcamLive_Filp = NULL;
struct file* phwebCamOutfile_Filp = NULL;
char data[640*480];
mm_segment_t old_fs;

static int readVideo(void *data)
{
   size_t amountRead = 0;
   while (!kthread_should_stop()) {
      printk(KERN_ALERT "Opened webCamOutfile !!.\n");
      old_fs=get_fs();
      set_fs(KERNEL_DS);
      amountRead = phcamLive_Filp->f_op->read(phcamLive_Filp, data, 2, &phcamLive_Filp->f_pos);
      set_fs(old_fs);
        
      if (amountRead)
         printk(KERN_ALERT "Read %lli bytes from /dev/video0", phcamLive_Filp->f_pos);
         
      schedule();
    }
    return 0;
}

int init_module(void)
{
   phcamLive_Filp = filp_open("/dev/video0", O_RDWR | O_LARGEFILE, 0);
   if (phcamLive_Filp == NULL)
   {
      printk(KERN_ALERT "filp_open error, failed to open webCam resource !!.\n");
   }else{
      printk(KERN_ALERT "Opened webCam resource !!.\n");
      phwebCamOutfile_Filp=filp_open("/home/rich/Videos/webCamOutfile", O_RDWR | O_LARGEFILE, 0);
      if (phwebCamOutfile_Filp == NULL){
         printk(KERN_ALERT "filp_open error, failed to open webCamOutfile !!.\n");
      }else{
         kthread = kthread_create(readVideo, NULL, "mykthread");
         wake_up_process(kthread);
      }
      filp_close(phcamLive_Filp,NULL);
   }
  
   return 0;
}

void cleanup_module(void)
{
    /* Waits for thread to return. */
    kthread_stop(kthread);
}

