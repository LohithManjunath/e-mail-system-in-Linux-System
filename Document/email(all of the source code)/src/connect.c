#include"client.h"
#include"head.h"
#include"gv.h"
void do_connect(void)
{
	printf("welcome to the do_connect!\n");    
	
	port = 7777;
	bzero(&pin, sizeof(pin));
	pin.sin_family=AF_INET;
	pin.sin_addr.s_addr = inet_addr("10.10.28.157");	//address
	pin.sin_port=htons(port);
//socked
	if((socket_descriptor=socket(AF_INET, SOCK_STREAM, 0))==-1)
    	{
		perror("error opening socket\n");
		exit(1);
	}
//connect
	if(connect(socket_descriptor, (void*)&pin, sizeof(pin))==-1)
	{   
		perror("can not connecting to server\n");
		exit(1);
	}
	else
	{
		printf("connect the server successfully!\n");
		return ;
	}	
}
