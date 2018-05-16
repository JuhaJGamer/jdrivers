#define MODULE
#define __KERNEL__

#include <linux/module.h>
#include <linux/config.h>

#include <linux/netdevice.h>

int dwlg520_open (struct net_device *dev) { //Open device 
    printk("dwl+g520 open call\n"); //Info
    netif_start_queue(dev); //Allow transmit - Allow upper layers to call hard_start_xmit
    return 0; //0 - Success
}

int dwlg520_release (struct net_device *dev) { //Release device
    printk("dwl+520 release call\n"); //Info
    netif_stop_queue(dev); //Disable transmit - See dwlg520_open(struct net_device)
    return 0;//Return
}

static int dwlg520_xmit (sk_buff *skb, struct net_device *dev) { //Start upper level transmission
    printk("dwl+g520 xmit call\n") //Info
    dev_kfree_skb(skb);
    return 0;
}

int dwlg520_init(struct net_device dev*) { //Initialize device 
    dev->open = dwlg520_open; //Set open routine
    dev->release = dwlg520_release; //Set release routine;
    dev->hard_start_xmit = dwlg520_xmit; //Set xmit routine;
    printk("DWL+G520 initialized\n"); //Info
    return 0;
}

struct net_device dwlg520 = {init:dwlg520_init}; //Declare device

int dwlg520_init_module (void) { //Initialize module
    int result;

    strcpy(dwlg520.name,"dwlg+520"); //Set card name
    if((result = register_netdev(&dwlg520))) { //Register network device
        printk("Error initializing card DWL+G520.\n"); //In case of failure, report and return
        return result;
    }
    return 0; //Return 0 on success
}

void dwlg520_cleanup (void) //Cleanup module
{
    printk("<0> Cleaning up the Module...\n"); //Info
    unregister_netdev(&dwlg520); //Unregister network device (wil lreturn 1 if not registered)
    return 0; //Return 0
}

module_init(dwlg520_init); //Set module init
module_exit(swlg520_cleanup); //Set module exit
