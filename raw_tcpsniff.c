#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <linux/if_ether.h>

// Dumps raw memory in hex byte and printable split format
void dump(const unsigned char *data_buffer, const unsigned int length) {
   unsigned char byte;
   unsigned int i, j;
   
   for(i=0; i < length; i++) {
      byte = data_buffer[i];
      printf("%02x ", data_buffer[i]);  // Display byte in hex.
      if(((i%16)==15) || (i==length-1)) {
         for(j=0; j < 15-(i%16); j++)
            printf("   ");
         printf("| ");
         for(j=(i-(i%16)); j <= i; j++) {  // Display printable bytes from line.
            byte = data_buffer[j];
            if((byte > 31) && (byte < 127)) // Outside printable char range
               printf("%c", byte);
            else
               printf(".");
         }
         printf("\n"); // End of the dump line (each line is 16 bytes)
      } // End if
   } // End for
}


int main(void)
{
    int i, recv_length, sockfd;
    u_char buffer[9000];
    
    if((sockfd = socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL))) == -1) // IPPROTO_ICMP IPPROTO_TCP IPPROTO_UDP // SOCK_RAW SOCK_STREAM // AF_PACKET,SOCK_RAW,htons(ETH_P_ALL) / PF_INET, SOCK_RAW, IPPROTO_TCP
        printf("Fatal error in socket!");

    for(i = 0; i < 100000; i++)
    {
        recv_length = recv(sockfd, buffer, 8000, 0);
        printf("Got a %d byte packet\n", recv_length);
        dump(buffer, recv_length);
    }

}
