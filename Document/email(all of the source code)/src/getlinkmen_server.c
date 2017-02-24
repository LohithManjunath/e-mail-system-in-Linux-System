#include"head.h"
#include"server.h"
#include"database.h"

void makefriends(char* bufname,MSG msg)
{
	char* zErrMsg = 0;//debug
	sqlite3 *db = NULL; 
	char** azResult;
	int nrow=0,ncolumn=0,i,f;
	sqlite3_open("../bin/try.db", &db);//打开数据库
	//char bufname[500];
	//memset(bufname, 0, sizeof(bufname));

	sprintf(sql, "SELECT friend FROM linkman_table WHERE uname='%s'", client_name[msg.client_num]);
	//sprintf(sql, "SELECT friend FROM linkman_table WHERE uname='%s'", client_name);
	printf("%s\n",sql);

	sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
	printf("zErrMsg=%s\n",zErrMsg);
	printf("nrow=%d, ncolumn=%d\n",nrow,ncolumn);
	for(i=1; i<((nrow+1)*ncolumn); i++)
	{
		printf("azResult[%d]=%s\n",i,azResult[i]);		
		strcat(bufname,azResult[i]);
		strcat(bufname,";");
	}
	
	printf("%s\n",bufname);

	sqlite3_close (db);        //关闭数据库
	return 0;
}





void getlinkmen_fun(MSG msg,int temp_sock_descriptor)
{

	printf("welcome to the getlinkmen_fun.\n");
	char linkmen[200];

	memset(linkmen,0,sizeof(linkmen));

	makefriends(linkmen,msg);

	

	if(send(temp_sock_descriptor, linkmen, 200, 0)==-1)	//send
	{
		perror("can not send linkmen\n");
		close(temp_sock_descriptor);
		exit(1);
	}
	
	printf("linkmen list had send to the client!\n");
	return ;
	
}
