#include"head.h"
#include"database.h"
#include"server.h"

int recycle_receive(int mno)
{
	//从收件箱删除邮件
	//从receivebox_table中删除，插入到recyclebin_table中
	char* zErrMsg = 0;//debug
	sqlite3* db = NULL; 
	sqlite3_open("../bin/try.db", &db);//打开数据库
	int i;
	char** azResult;		
	int nrow,ncolumn;
	
	sprintf(sql, "SELECT * FROM receivebox_table WHERE no='%d'", mno);
	printf("%s\n",sql);//debug
	sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
	/*
	printf("more details:nrow=%d ncolumn=%d\n",nrow,ncolumn);
	for(i=0; i<((nrow+1)*ncolumn); i++)
	{
		printf("azResult[%d]=%s\n",i,azResult[i]);
	}
	*/
	sprintf(sql, "INSERT INTO recyclebin_table VALUES('%d','%s','%s','%s','%s','%s','r')", mno ,azResult[7],azResult[10],azResult[7],azResult[8],azResult[9]);
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	

	sprintf(sql, "DELETE FROM receivebox_table WHERE no='%d'", mno);
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);//delete
	
	sqlite3_close (db);        //关闭数据库
	return 0;
}


int deletemail(int mno,char flag)
{
	//在回收站中点击彻底删除按钮
	//使message_table中flag--，为0则删除，删除recyclebin中信息	
	char* zErrMsg = 0;//debug
	sqlite3* db = NULL; 
	sqlite3_open("../bin/try.db", &db);//打开数据库
	int i;
	char** azResult;		
	int nrow,ncolumn;
	

	sprintf(sql, "update message_table set flag=flag-1 where no=%d",mno);
	//printf("%s\n",sql);
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);//update message_table
	//printf("error : %s\n",zErrMsg);

	sprintf(sql, "SELECT flag FROM message_table WHERE no=%d", mno);
	printf("%s\n",sql);
	sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
	printf("azResult[1] = %d\n",atoi(azResult[1]));
	if(atoi(azResult[1]) == 0)
	{
		sprintf(sql, "DELETE FROM message_table WHERE no='%d'", mno);
		sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	}	

	sprintf(sql, "DELETE FROM recyclebin_table WHERE (no='%d' AND uname='%s' AND flag='%c')", mno, client_name, flag);
	printf("%s\n",sql);	
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);//delete from recyclebin_table
	printf("error : %s\n",zErrMsg);
	sqlite3_close (db);        //关闭数据库
	return 0;
}


int recycle_send(int mno)
{
	//从发件箱删除邮件
	//从sendbox_table中删除，插入到recyclebin_table中
	char* zErrMsg = 0;//debug
	sqlite3* db = NULL; 
	sqlite3_open("try.db", &db);//打开数据库
	int i;
	char** azResult;		
	int nrow,ncolumn;
	
	sprintf(sql, "SELECT * FROM sendbox_table WHERE no='%d'", mno);
	printf("%s\n",sql);//debug
	sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);

	/*
	printf("more details:nrow=%d ncolumn=%d\n",nrow,ncolumn);
	for(i=0; i<((nrow+1)*ncolumn); i++)
	{
		printf("azResult[%d]=%s\n",i,azResult[i]);
	}
	*/
	sprintf(sql, "INSERT INTO recyclebin_table VALUES('%d','%s','%s','%s','%s','%s','s')", mno ,azResult[6],azResult[6],azResult[9],azResult[7],azResult[8]);
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	

	sprintf(sql, "DELETE FROM sendbox_table WHERE no='%d'", mno);
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);//delete
	
	sqlite3_close (db);        //关闭数据库
	return 0;
}


int recycle_draft(int mno)
{
	//从草稿箱删除邮件
	//从draftbox_table中删除，插入到recyclebin_table中
	char* zErrMsg = 0;//debug
	sqlite3* db = NULL; 
	sqlite3_open("try.db", &db);//打开数据库
	int i;
	char** azResult;		
	int nrow,ncolumn;
	
	sprintf(sql, "SELECT * FROM draftbox_table WHERE no='%d'", mno);
	//printf("%s\n",sql);//debug
	sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);

	printf("more details:nrow=%d ncolumn=%d\n",nrow,ncolumn);
	for(i=0; i<((nrow+1)*ncolumn); i++)
	{
		printf("azResult[%d]=%s\n",i,azResult[i]);
	}
	
	sprintf(sql, "INSERT INTO recyclebin_table VALUES('%d','%s','%s','%s','%s','%s','d')", mno ,azResult[5],azResult[5],NULL,azResult[6],azResult[7]);
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	

	sprintf(sql, "DELETE FROM draftbox_table WHERE no='%d'", mno);
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);//delete
	
	sqlite3_close (db);        //关闭数据库
	return 0;
}





void delete_recEbox_fun(MSG msg,int temp_sock_descriptor)		///////////RecEbox
{
	recycle_receive(msg.no);
	return ;
}


void delete_recYbox_fun(MSG msg,int temp_sock_descriptor)		//////////RecYbox
{
	deletemail(msg.no,msg.database_flag);
	return ;
}

void delete_send_fun(MSG msg,int temp_sock_descriptor)			//////////Sendbox
{
	recycle_send(msg.no);
	return ;
}

void delete_draft_fun(MSG msg,int temp_sock_descriptor)			//////////Draftbox
{
	recycle_draft(msg.no);
	return ;
}	
