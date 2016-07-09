

/*
 * This Program need Root or Administrator Permission
 */

#include <stdio.h>
#include <pcap.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

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

void packet_processer(u_char * , const struct pcap_pkthdr *, const u_char *);

int main(int argc, char **argv) {
    int i;

    // Only Root User
    if(0 != getuid()) {
        printf("Need Root Permission\n");
        return 1;
    }

    char error_buf[PCAP_ERRBUF_SIZE];


    bpf_u_int32 subnet_mask;
    bpf_u_int32 network_addr;


    pcap_if_t *alldevs;

    // int pcap_findalldevs(pcap_if_t **alldevsp, char *errbuf);
    int res = pcap_findalldevs(&alldevs, error_buf);

    if (res == -1) {
        printf("Error findalldevs:\n%s\n", error_buf);
        return 1;
    }


    // 패킷을 가져올 인터페이스 이름. 무선 인터넷 NIC
    char device_name[10];
    strcpy(device_name, alldevs[0].name);

    // Check device name
    printf("Device: %s\n", alldevs[0].name);

    // Free all list
    pcap_freealldevs(alldevs);

    // int	pcap_lookupnet(const char *, bpf_u_int32 *, bpf_u_int32 *, char *);
    // Fail return -1
    /*
     * ip_addr = 108736
     * subnet_mask = 16777215
     */
    if(-1 == pcap_lookupnet(
            device_name,
            &network_addr,
            &subnet_mask,
            error_buf
    )) {
        // if Fail
        printf("lookupnet fail\n%s\n", error_buf);
        return 1;
    }

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

    struct bpf_program compiled_filter;

    // Compile Filter String to bpf_program struct
    // TCP Packet
    // int pcap_compile(pcap_t *, struct bpf_program *, const char *, int, bpf_u_int32);
    pcap_compile(
            device_handler,
            &compiled_filter,
            "tcp",
            0, // no optimize
            network_addr
    );

    // Set Filter
    if(-1 == pcap_setfilter(
            device_handler,
            &compiled_filter
    )) {
        printf("Fail setfiler");
        return 1;
    }


    pcap_loop(
            device_handler,
            -1,
            packet_processer,
            0 // Userdata just 0
    );

}

void packet_processer(u_char *param , const struct pcap_pkthdr *header, const u_char *pkt_data){
    time_t time;
    struct tm *local_time;
    char time_str[16];

    time = header->ts.tv_sec;

    // Edit string for print pretty
    local_time = localtime(&time);
    strftime(time_str, sizeof(time_str), "%H:%M:%S", local_time);

    printf("%s,%.6d len:%d\n", time_str, (int)header->ts.tv_usec, header->len);




}