#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/types.h>

#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>

#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>


#define PREFIX "[SIMPLE_NETFILTER_MODULE]"
MODULE_LICENSE("GPL");


unsigned int packet_filter(unsigned int hooknum, struct sk_buff *skb, const struct net_device *in, 
                           const struct net_device *out, int (*okfn)(struct sk_buff *)) {
    
    struct iphdr *iph;
    struct tcphdr *tcph;
    struct udphdr *udph;

    if(skb == NULL)
            return NF_ACCEPT;

    iph = ip_hdr(skb);

    if(iph == NULL)
            return NF_ACCEPT;
    
    // 172.16.0.0
    u32 start_addr = 0xac100000; 
    // 172.16.255.255
    u32 end_addr = 0xac10ffff;

    u32 saddr = iph->saddr;
    
    if((saddr >= start_addr) && (saddr <= end_addr)) {
        printk(PREFIX "In range");
    }
    
    printk(PREFIX " %s. protocol is [%d].\n", __func__, iph->protocol);
    printk(PREFIX " %s. source addr is [%pI4].\n", __func__, &iph->saddr);
    printk(PREFIX " %s. dest addr is [%pI4].\n", __func__, &iph->daddr);
    
    return NF_DROP;

}

static struct nf_hook_ops nfho = {
	.hook = (nf_hookfn *)packet_filter, // hook function
    .pf = NFPROTO_INET, // process network packets at ip layer
    .hooknum = NF_INET_PRE_ROUTING, // preroute chain
    .priority = NF_IP_PRI_FIRST, // highest priority
};


static int __init proc_init(void) {
	
    printk(KERN_INFO "Enabling module PROC.ko\n");
    // netfilter func to register hook :)
    nf_register_net_hook(&init_net, &nfho);

	return 0;
}

static void __exit proc_exit(void) {
    nf_unregister_net_hook(&init_net, &nfho);
	printk(KERN_INFO "Exiting PROC.ko\n");
}

module_init(proc_init);
module_exit(proc_exit);
