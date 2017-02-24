#include"head.h"
#include"server.h"
#include"database.h"

int recovermail(int mno,char flag)
{
	//从回收站中恢复邮件
	char* zErrMsg = 0;//debug
	sqlite3* db = NULL; 
	sqlite3_open("../bin/try.db", &db);//打开数据库
	int i;
	char** azResult;		
	int nrow,ncolumn;
	
	sprintf(sql, "SELECT * FROM recyclebin_table WHERE(no='%d' AND flag='%c')", mno, flag);
	sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);		
	printf("nrow=%d, ncolumn=%d\n",nrow,ncolumn);
	
	sprintf(sql, "DELETE FROM recyclebin_table WHERE(no='%d' AND flag='%c')", mno, flag);
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	for(i=0; i<(nrow+1)*ncolumn; i++)
	{
		printf("azResult[%d] = %s\n",i,azResult[i]);
	}
	if(flag == 's')
	{
		sprintf(sql, "INSERT INTO sendbox_table VALUES('%s','%s','%s','%s','%s')", azResult[7],azResult[8],azResult[11],azResult[12],azResult[10]);
		printf("recover from sendbox: %s\n",sql);		
		sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	}
	else if(flag == 'r')
	{
		sprintf(sql, "INSERT INTO receivebox_table VALUES('%s','%s','%s','%s','%s','y')", azResult[7],azResult[8],azResult[11],azResult[12],azResult[9]);
		printf("recover from receivebox: %s\n",sql);
		sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	}	
	else //flag == 'd'
	{
		sprintf(sql, "INSERT INTO draftbox_table VALUES('%s','%s','%s','%s')", azResult[7],azResult[8],azResult[11],azResult[12]);
		printf("recover from draftbox: %s\n",sql);
		sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	}
	
	sqlite3_close (db);        //关闭数据库
	return 0;	
}




void recover_fun(MSG msg,int temp_sock_descriptor)
{
	printf("welcome to the recover_function.\nthe msg.no is %d.\nthe msg.database_flag = %c.\n",msg.no,msg.database_flag);
	recovermail(msg.no,msg.database_flag);
	return ;
}

