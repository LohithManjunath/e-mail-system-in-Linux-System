#include"head.h"
#include"server.h"
#include"database.h"

int showmessage(char username[18])
{
	//登陆成功时调用，返回值为收到的新邮件数目
	int sqlite_callback(void* tmp,int argc,char** argv,char** col)
	{
		*((int*)tmp) = atoi(argv[0]);
		return 0;
	}
	sqlite3 *db = NULL;
	char* zErrMsg = 0;//debug
	int cnt=0;
	sqlite3_open("try.db", &db);//打开数据库
	
	sprintf(sql, "SELECT count(*) FROM receivebox_table WHERE (uname='%s' AND rmstat='n')", username);
	sqlite3_exec(db, sql, sqlite_callback, &cnt, &zErrMsg);

	printf("cnt=%d\n",cnt);
	return cnt;
}	






void note_fun(MSG msg,int temp_sock_descriptor)
{
	printf("welcome to the note_fun.\n");
	int email_num;
	printf("client_name[msg.client_num]= %s \n",client_name[msg.client_num]);
	email_num =showmessage(client_name[msg.client_num]);
	printf("client_name[msg.client_num]= %s \n",client_name[msg.client_num]);
	char flag[10];
	char *x;
	//int lenth;
	memset(flag,0,sizeof(flag));
	//x = itoa(email_num,flag,10); 
	printf("!!%d\n",email_num);
	sprintf(flag+strlen(flag), "%d", email_num);
	printf("heheheheheh%d\n", email_num);
	//sprintf(flag+strlen)
	printf("the flag = %s\nthe email_num = %d\n",flag,email_num);
		if(send(temp_sock_descriptor, flag, 10, 0)==-1)	//send
		{
			perror("can not send email_num\n");
			close(temp_sock_descriptor);
			exit(1);
		}


	return ;
}
