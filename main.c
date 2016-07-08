/*
 * 기한: 7월 15일 23:59 까지
 * 이메일: bob@gilgil.net
 * 제목 양식: [bob5] 네트워크과제1_이름
 * 네트워크 라이브러리 pcap 을 이용해 패킷을 캡쳐한 뒤 ethernet, ip, tcp 헤더에서 source mac, ip, port 와 destination mac, ip, port 추출해서 출력.
 */

/*
 * Good Info:
 * https://wiki.kldp.org/KoreanDoc/html/Libpcap-KLDP/function.html --> pcap 함수에 대한 한글설명
 * http://www.tcpdump.org/pcap.html --> 영문자료. pcap 함수에 대해 자세히 나와있음
 * http://mindnet.tistory.com/entry/%EB%84%A4%ED%8A%B8%EC%9B%8C%ED%81%AC-%EC%89%BD%EA%B2%8C-%EC%9D%B4%ED%95%B4%ED%95%98%EA%B8%B0-18%ED%8E%B8-IP-Header-IP%ED%97%A4%EB%8D%94-%EA%B5%AC%EC%A1%B0
   --> 패킷 헤더 자료
 */

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


    pcap_t *device;  // pcap_t *pcap_open_live(const char *, int, int, int, char *);

    // pcap_open_live(device, snaplen, PROMISCUOUS, 1000, ebuf);
    device = pcap_open_live(
            device_name,
            100,
            1,  // Open with Promiscuous mode
            0,  // Non-Delay
            error_buf
    );


    printf("Break Point");

}