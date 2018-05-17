#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>

int main(argc,argv)
   int   argc;
   char *argv[];
{
   struct sockaddr_in addr;
   struct hostent *host;

   host = gethostbyname(argv[1]);
   if( host != NULL ){
      addr.sin_addr =  *(struct in_addr *)(host->h_addr_list[0]);
      printf("ip=%x\n", addr.sin_addr);
      //printf("ip(c)=[%s]\n",inet_ntoa(addr.sin_addr));
   }
}
