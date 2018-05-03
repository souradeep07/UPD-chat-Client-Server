#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>


int main()
{
	int i=0;
	int sock;
	unsigned int rcvlen;
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;
	char buffer[64];
	char buff[64];
	int recv_count=0,sent_count=0;

	if((sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP))<0)
	{
		printf("Error Creating Socket\n");
		exit(1);
	}
	else{printf("Socket CReated\n");}

	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(9852);
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);

	if(bind(sock,(struct sockaddr *)&serveraddr,sizeof(serveraddr))<0)
		printf("Binding Fauiled\n"),exit(1);
	else
		printf("Binding Successful\n");
	
	rcvlen=sizeof(clientaddr);

	while(1){
		
		if((recv_count=recvfrom(sock,buffer,64,0,(struct sockaddr *)&clientaddr,&rcvlen))<0)
			printf("Coundn't Receive\n");
		else	
			printf("%d Bytes Received\n",recv_count);
		
		printf("Received From Client: %s\n",buffer);
		
		printf("Enter text to send: ");
		scanf ("%[^\n]%*c", buff);

		if((sent_count=sendto(sock,buff,strlen(buff),0,(struct sockaddr *)&clientaddr,sizeof(serveraddr)))<0)			
			printf("Coundn't Send\n");
		else	
			printf("%d Bytes sent\n",sent_count);
	}
}
