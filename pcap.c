#include <stdio.h>
#include <pcap.h>
#include<time.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include<netinet/tcp.h>   //Provides declarations for tcp header
#include <netinet/if_ether.h> /* includes net/ethernet.h */

//defines for the packet type code in an ETHERNET header
#define ETHER_TYPE_IP (0x0800)
#define ETHER_TYPE_8021Q (0x8100)
#define ETHER_TYPE_ARP (0x0806)
#define IP_HL(ip)               (((ip)->ip_hl) & 0x0f)

//------------------------------------------------------------------- 
int main(int argc, char **argv) 
{ 
unsigned int pkt_counter=0;  
struct ether_header *eptr;
struct pcap_pkthdr hdr;
struct arphdr * arp;
u_char *ptr;
int i;
  
  struct pcap_pkthdr header; // The header that pcap gives us 
  const u_char *packet; // The actual packet 
  int fnum;
  
  if (argc != 2) { 
    fprintf(stderr, "Usage: %s [input pcaps]\n", argv[0]); 
    exit(1); 
  }  		
    pcap_t *handle; 
    char errbuf[PCAP_ERRBUF_SIZE]; 
    handle = pcap_open_offline(argv[1], errbuf);   

    // ethernet header
            eptr = (struct ether_header *) packet; 
	    if (handle == NULL) { 
	      fprintf(stderr,"Couldn't open pcap file %s: %s\n", argv[fnum], errbuf); 
	      return(2); 
	    } 
	 
 while (packet = pcap_next(handle,&header))
 { 
		      
	 u_char *pkt_ptr = (u_char *)packet; 
		      

		      int ether_type = ((int)(pkt_ptr[12]) << 8) | (int)pkt_ptr[13]; 
		      int ether_offset = 0; 
	 
			
			printf("\nRecieved at ..... %s",ctime((const time_t*)&hdr.ts.tv_sec));
			printf("Ethernet address length is %d\n",ETHER_HDR_LEN);



	      if (ether_type == ETHER_TYPE_IP) 
		{ether_offset = 14; 
		printf("Ethernet type hex:%x dec:%d is an IP packet\n",
		ntohs(eptr->ether_type),
		ntohs(eptr->ether_type));
		}
	     
	      else if(ether_type == ETHER_TYPE_ARP)
	 	printf("Ethernet type hex:%x dec:%d is an ARP packet\n",ntohs(eptr->ether_type),ntohs(eptr->ether_type));
		 
	// printing details from ethernet header

		ptr = eptr->ether_dhost;
		i = ETHER_ADDR_LEN;
		printf("Destination Address: ");
		do{
		printf("%s%x",(i == ETHER_ADDR_LEN) ? " " : ":",*ptr++);
		}while(--i>0);
		printf("\t");

		ptr = eptr->ether_shost;
		i = ETHER_ADDR_LEN;
		printf(" Source Address: ");
		do{
		printf("%s%x",(i == ETHER_ADDR_LEN) ? " " : ":",*ptr++);
		}while(--i>0);
		printf("\n");



// IP packet
	 if (ether_type == ETHER_TYPE_IP)
      {
	 //parse the IP header 
	      pkt_ptr += ether_offset;  
	      struct ip *ip_hdr = (struct ip *)pkt_ptr;  
	      int size_ip= IP_HL(ip_hdr)*4;
	      int packet_length = ntohs(ip_hdr->ip_len); 
	      printf("packet length %d:\n",packet_length);
	      printf("Internet Protocol version 4: From: %s\t", inet_ntoa(ip_hdr->ip_src));
	      printf(" To: %s\n", inet_ntoa(ip_hdr->ip_dst));
	
	/* determine protocol */
	 switch(ip_hdr->ip_p) {
	  case IPPROTO_TCP:
	   printf("Protocol: TCP\n");
	   break;
	  case IPPROTO_UDP:
	   printf("Protocol: UDP\n");
	   break;
	  case IPPROTO_ICMP:
	   printf("Protocol: ICMP\n");
	   break;
	  case IPPROTO_IP:
	   printf("Protocol: IP\n");
	   break;
	  default:
	   printf("Protocol: unknown\n");
	   break;
	 }
	      


	//parse tcp header
		pkt_ptr += size_ip; 
		struct tcphdr *tcp_hdr;
		tcp_hdr = (struct tcphdr*)pkt_ptr;
	 printf("TCP header: Src port: %d\t", ntohs(tcp_hdr->th_sport));
	 printf(" Dst port: %d\n", ntohs(tcp_hdr->th_dport));
	  
	}


//ARP packet

if(ether_type == ETHER_TYPE_ARP)
{

arp=(struct arphdr *)(pkt_ptr+ sizeof(struct ether_header));

if (1==htons(arp->ar_op))
	printf("ARP Opcode: ARP Request\n");
else
	printf("ARP Opcode: ARP Reply\n");


}
	      pkt_counter++;  
	 
	    }  
 
    pcap_close(handle);  
 
 
  printf("Processed %d packets ", pkt_counter);
  return 0; 
} 

/*   snippet of output
avanti@localhost l3]$ ./final arp-storm.pcap

Recieved at ..... Thu Jan  1 05:30:00 1970
Ethernet address length is 14
Ethernet type hex:5424 dec:21540 is an ARP packet
Destination Address:  49:89:c3:66:f:1a	 Source Address:  5c:24:30:66:f:1a
ARP Opcode: ARP Request

Recieved at ..... Thu Jan  1 05:30:00 1970
Ethernet address length is 14
Ethernet type hex:5424 dec:21540 is an ARP packet
Destination Address:  49:89:c3:66:f:1a	 Source Address:  5c:24:30:66:f:1a
ARP Opcode: ARP Request

Processed 622 packets
[avanti@localhost l3]$ ./final bgp.pcap

Recieved at ..... Thu Jan  1 05:30:00 1970
Ethernet address length is 14
Ethernet type hex:5424 dec:21540 is an IP packet
Destination Address:  49:89:c3:66:f:1a	 Source Address:  5c:24:30:66:f:1a
packet length 59:
Internet Protocol version 4: From: 192.168.0.33	 To: 192.168.0.15
Protocol: TCP
TCP header: Src port: 179	 Dst port: 2124

Recieved at ..... Thu Jan  1 05:30:00 1970
Ethernet address length is 14
Ethernet type hex:5424 dec:21540 is an IP packet
Destination Address:  49:89:c3:66:f:1a	 Source Address:  5c:24:30:66:f:1a
packet length 40:
Internet Protocol version 4: From: 192.168.0.15	 To: 192.168.0.33
Protocol: TCP
TCP header: Src port: 2124	 Dst port: 179
Processed 20 packets */
