#include"head.h"
#include"server.h"
#include"database.h"

int sendmail(struct message_type tmp)
{
	printf("welcome to the send_server_database!\n");
	//点击发送按钮时
	char* zErrMsg = 0;//debug
	sqlite3 *db = NULL; 
	char** azResult;
	int nrow,ncolumn,i,f,flag;
	int pp;
	sqlite3_open("../bin/try.db", &db);//打开数据库
	
//////////////////////////////////////////////////////////////////
	int n,j,k,len;
	char Result[100][100];
	len = strlen(tmp.receiver);
	for(n=0,k=0; k<len; n++)
	{
		for(j=0; tmp.receiver[k]!=';'; j++,k++)
		{
			Result[n][j] = tmp.receiver[k];
		}
		Result[n][j++] = '\0';
		k++;
	}
///////////////////////////////////////////////////////////////////
		
		
	strcpy(sql, "SELECT uname FROM user_table");
	sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
			
	for(j=0; j<n; j++)
	{
		for(i=1,f=0; i<((nrow+1)*ncolumn); i++)
		{
			if(strcmp(azResult[i],Result[j]) == 0)
			{
				f = 1;	
				break;
			}
		}
		if( !f )
		{
			return 1;
		}
	}	
	
	
	for(i=0; i<n; i++)	
	{
		count++;//!!
		gettime(&tmp.mtime);
	
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		

		sprintf(sql, "SELECT friend,ltime FROM linkman_table WHERE uname='%s'", tmp.sender);		
		sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);

		for(pp=2,flag=0; pp<(nrow+1)*ncolumn; pp+=2)
		{
			if(strcmp(azResult[pp],Result[i]) == 0)
			{
				if((azResult[pp+1],tmp.mtime) < 0)
				{
					sprintf(sql, "UPDATE linkman_table SET ltime='%s' WHERE (uname='%s' AND friend='%s')", tmp.mtime, tmp.sender, Result[i]);
					sqlite3_exec(db, sql, 0, 0, &zErrMsg);
				}
				flag=1;			
				break;				
			}
			
		}
		if(!flag)
		{
			sprintf(sql, "INSERT INTO linkman_table VALUES('%s','%s','%s')", tmp.sender, Result[i], tmp.mtime);
			sqlite3_exec(db, sql, 0, 0, &zErrMsg);
		}
	



		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		sprintf(sql, "SELECT friend,ltime FROM linkman_table WHERE uname='%s'", Result[i]);		
		sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);

		for(pp=2,flag=0; pp<(nrow+1)*ncolumn; pp+=2)
		{
			if(strcmp(azResult[pp],tmp.sender) == 0)
			{
				if((azResult[pp+1],tmp.mtime) < 0)
				{
					sprintf(sql, "UPDATE linkman_table SET ltime='%s' WHERE (uname='%s' AND friend='%s')", tmp.mtime, Result[i], tmp.sender);
					sqlite3_exec(db, sql, 0, 0, &zErrMsg);
				}
				flag=1;			
				break;				
			}
			
		}
		if(!flag)
		{
			sprintf(sql, "INSERT INTO linkman_table VALUES('%s','%s','%s')", Result[i], tmp.sender, tmp.mtime);
			sqlite3_exec(db, sql, 0, 0, &zErrMsg);
		}

		


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
		
		sprintf(sql, "INSERT INTO message_table VALUES('%d', '%s', '%s', 2)", count, tmp.mtitle, tmp.mtext);
		sqlite3_exec(db, sql, 0, 0, &zErrMsg);//insert message

		
		sprintf(sql, "INSERT INTO sendbox_table VALUES('%d','%s','%s','%s','%s')", count, tmp.sender, tmp.mtitle, tmp.mtime, Result[i]);
		sqlite3_exec(db, sql, 0, 0, &zErrMsg);

		sprintf(sql, "INSERT INTO receivebox_table VALUES('%d','%s','%s','%s','%s','n')", count, Result[i], tmp.mtitle, tmp.mtime, tmp.sender);
		printf("%s\n",sql);//debug
		sqlite3_exec(db, sql, 0, 0, &zErrMsg);		
	}


	
	/*查询用户名是否在活跃状态*/
	
	sqlite3_close (db);        //关闭数据库
	return 0;
}







void send_fun(MSG msg,int temp_sock_descriptor)
{

	printf("welcome to the send_server_function!\n");
	struct message_type tmp;
	
	strcpy(tmp.sender,client_name[msg.client_num]);

	printf("client_name[%d] is %s\n",msg.client_num,tmp.sender);

	strcpy(tmp.receiver,msg.receiver);
	printf("tmp.receiver is %s\n",tmp.receiver);
	strcpy(tmp.mtitle,msg.mtitle);
	printf("tmp.mtitle is %s\n",tmp.mtitle);
	strcpy(tmp.mtext,msg.mtext);
	printf("tmp.mtext is %s\n",tmp.mtext);
	
	int x;
	char flag;
	x = sendmail(tmp);	
	
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
	printf("send_fun flag = %c\n",flag);

	return ;
}









