#include"head.h"
#include"server.h"
#include"database.h"

int savemail(struct message_type tmp)
{
	//点击保存按钮时
	sqlite3 *db = NULL; 	
	char* zErrMsg = 0;//debug
	sqlite3_open("try.db", &db);//打开数据库

	count++;//
	sprintf(sql, "INSERT INTO message_table VALUES('%d', '%s', '%s', '1')", count, tmp.mtitle, tmp.mtext);
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);//insert message_table

	gettime(&tmp.mtime);
	
	sprintf(sql, "INSERT INTO draftbox_table VALUES('%d','%s','%s','%s')", count, tmp.sender, tmp.mtitle, tmp.mtime);
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);//insert draftbox_table

	sqlite3_close (db);        //关闭数据库
	return 0;
}

void save_fun(MSG msg,int temp_sock_descriptor)
{
	printf("welcome to the save_server_function!\n");
	struct message_type tmp;
	
	strcpy(tmp.sender,client_name[msg.client_num]);			//sender

	printf("client_name[%d] is %s\n",msg.client_num,tmp.sender);

	strcpy(tmp.mtitle,msg.mtitle);			//title
	printf("tmp.mtitle is %s\n",tmp.mtitle);
	strcpy(tmp.mtext,msg.mtext);			//text
	printf("tmp.mtext is %s\n",tmp.mtext);
	
	int x;
	char flag;

	x = savemail(tmp);
	
	if(x == 0)
	{
		flag = 'y';
		if(send(temp_sock_descriptor, &flag, 1, 0)==-1)	//send
		{
			perror("can not send flag\n");
			close(temp_sock_descriptor);
			exit(1);
		}
	}
	else
	{
		flag = 'n';
		printf("The receiver has not been found\n");
		if(send(temp_sock_descriptor, &flag, 1, 0)==-1)	//send
		{
			perror("can not send flag\n");
			close(temp_sock_descriptor);
			exit(1);
		}
	}
	printf("save_fun flag = %c\n",flag);
	
	return ;
}
