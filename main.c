

/*
 * This Program need Root or Administrator Permission
 */

#include <stdio.h>
#include <pcap.h>
#include <unistd.h>

struct data_form {
    unsigned char one;
    unsigned char two;
    unsigned char three;
    unsigned char four;
};

void print_bpf_u_int32(bpf_u_int32 data){
    struct data_form *ptr=(struct data_form*)&data;

    printf("%d.%d.%d.%d\n", ptr->one, ptr->two, ptr->three, ptr->four);
}

int main(int argc, char **argv) {

    // Only Root User
    if(0 != getuid()) {
        printf("Need Root Permission\n");
        return 1;
    }

    char error_buf[PCAP_ERRBUF_SIZE];
    char *device_name = "wlan0";  // 패킷을 가져올 인터페이스 이름. 무선 인터넷 NIC

    bpf_u_int32 subnet_mask;
    bpf_u_int32 network_addr;


    // int	pcap_lookupnet(const char *, bpf_u_int32 *, bpf_u_int32 *, char *);
    // Fail return -1
    /*
     * ip_addr = 108736
     * subnet_mask = 16777215
     */
    pcap_lookupnet(
            device_name,
            &network_addr,
            &subnet_mask,
            error_buf
    );

    print_bpf_u_int32(network_addr);
    print_bpf_u_int32(subnet_mask);


    pcap_t *device_handler;  // pcap_t *pcap_open_live(const char *, int, int, int, char *);

    // Open device_handler for packet capture
    // pcap_open_live(device_handler, snaplen, PROMISCUOUS, 1000, ebuf);
    device_handler = pcap_open_live(
            device_name,
            100,
            1,  // Open with Promiscuous mode
            0,  // Non-Delay
            error_buf
    );


    printf("Break Point");

}