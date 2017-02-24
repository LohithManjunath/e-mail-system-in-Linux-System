#include"head.h"
#include"database.h"
#include"server.h"

/*
typedef struct msg
{
	int num;
	int no;
	int client_num;	
	char database_flag;
	char uname[18];
	char upsw[18];
	char utel[12];
	char sender[18];
	char receiver[18];
	char mtime[30];
	char mtitle[30];
	char mtext[1000];
}MSG;
*/
int port = 7777;

client_num = 0;

int main(int argc, char* argv[])
{
	int sd, rc, n, cliLen;
	struct sockaddr_in servAddr;
	int size_of_addr;

	struct sockaddr_in pin;
	int temp_sock_descriptor;

    
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if(sd<0)
	{
		printf("%s: cannot open socket \n", argv[0]);
		exit(1);
	}
	bzero(&servAddr, sizeof(servAddr));

	servAddr.sin_family=AF_INET;
	servAddr.sin_addr.s_addr=INADDR_ANY;
	servAddr.sin_port=htons(port);

//bind socket
	rc=bind(sd, (struct sockaddr*)&servAddr, sizeof(servAddr));
	if(rc < 0)
	{
		printf("%s: cannot bind port number %d \n", argv[0], port);
		exit(1);
	}
//listen
	if(listen(sd, 20) == -1)
	{
		perror("listen1");
		exit(1);
	}
	printf("waiting for accepting!\n");




//main progress
    while(1)
    {
	MSG msg;	//received message

//accept send and receive by the "temp_sock_descriptor"  
	bzero(&pin, sizeof(pin));
	size_of_addr = 1;
	temp_sock_descriptor = accept(sd, (struct sockaddr*)&pin, &size_of_addr);
        if(temp_sock_descriptor == -1)
        {
            perror("accept!");
            exit(1);
        }
	printf("connecting!\n");
//
//receive struct msg	
	int buffer_lenth;			//receive struct;
	bzero(buffer,sizeof(buffer));
	
	if((buffer_lenth = recv(temp_sock_descriptor,buffer,sizeof(buffer),0)) <0)
	{
		perror("recv()!");
		exit(1);
	}
	buffer[buffer_lenth] = '\0';
	printf("recv %d words.\n",buffer_lenth);
	printf("buffer is %s\n",buffer);
	
	memcpy(&msg,buffer,sizeof(msg));
	
	printf("the received msg.num = %d\n",msg.num);
//	
	switch(msg.num)
	{
		case 0:	//login
		{
			login_fun(msg,temp_sock_descriptor);
			break;
		}
		case 1: //register
		{
			register_fun(msg,temp_sock_descriptor);
			break;
		}
		case 2://send email
		{
			send_fun(msg,temp_sock_descriptor);
			break;
		}
		case 3://save email
		{
			save_fun(msg,temp_sock_descriptor);
			break;
		}
		case 4://change_password
		{
			change_password_fun(msg,temp_sock_descriptor);
			break;
		}
		case 5://delete email in receive box
		{
			delete_recEbox_fun(msg,temp_sock_descriptor);
			break;
		}
		case 6://delete email in recycle box
		{
			delete_recYbox_fun(msg,temp_sock_descriptor);
			break;
		}
		case 7://delete email in send box
		{
			delete_send_fun(msg,temp_sock_descriptor);
			break;
		}
		case 8://delete email in draft box
		{
			delete_draft_fun(msg,temp_sock_descriptor);
			break;
		}
		case 9://getlinkmen
		{
			getlinkmen_fun(msg,temp_sock_descriptor);
			break;
		}
		case 10://recover the email
		{
			recover_fun(msg,temp_sock_descriptor);
			break;
		}

		case 11://open receivebox
		{
			openrcvb_fun(msg,temp_sock_descriptor);
			break;		
		}
	 	case 121://open mail in receivebox
		{
			openrcvm_fun(msg,temp_sock_descriptor);
			break;
		}
		case 122://open mail in other boxes
		{
			openrcvm_fun(msg,temp_sock_descriptor);
			break;
		}
		case 13://open sendbox
		{
			opensndb_fun(msg,temp_sock_descriptor);
			break;
		}
		case 14://open draftbox
		{
			opendrtfb_fun(msg,temp_sock_descriptor);
			break;
		}
		case 15://open recyclebinbox
		{
			openrbb_fun(msg,temp_sock_descriptor);
			break;
		}
		case 16://open ydmailbox
		{
			openydmb_fun(msg,temp_sock_descriptor);
			break;
		}
		case 17://open wdmailbox
		{
			openwdmb_fun(msg,temp_sock_descriptor);
			break;
		}
		case 21://note function
		{
			note_fun(msg,temp_sock_descriptor);
			break;
		}


		default:
		{
			exit(1);
		}
	}
    }
    return 0;
}
