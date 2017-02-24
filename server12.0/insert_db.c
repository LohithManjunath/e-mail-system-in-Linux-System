#include "insert_db.h"
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <string.h>
void db_insert(char* name, char* psd, char* phone, char* rtnresult)
{       
      
	sqlite3 *db = NULL;
	int rc;
	char *zErrMsg = 0;
	char db_sql_insert[500] = {0};

	rc = sqlite3_open("db.db", &db);
      
	if (rc)    
	{
		printf("open failed!\n");
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("open success!\n");	
	}
	char order[25] = {0};
	//printf("psd == %s\n", psd);
	//sprintf(order,"cgpd%s",psd);
	//printf("order :%s\n",order);
	if (strcmp(phone,"changepsd") == 0)
	{
		
		
		sprintf(db_sql_insert, "UPDATE \"user_info\" set user_psd='%s' where user_name ='%s'",psd,name);
		printf("%s\n",db_sql_insert);
		sqlite3_exec (db, db_sql_insert, 0, 0, &zErrMsg);	
		if (zErrMsg == NULL)
		{	strcpy(rtnresult,"change successful");
			printf("rtnlt:%s", rtnresult);
		}
		else
		printf("%s\n",zErrMsg);
	}	
	else
	{
		sprintf(db_sql_insert, "INSERT INTO \"user_info\" VALUES(\
		'%s','%s','%s');", name, psd, phone);
		sqlite3_exec (db, db_sql_insert, 0, 0, &zErrMsg);
		if (zErrMsg != NULL)
		{
			if (strcmp(zErrMsg,"column user_name is not unique") == 0)
			strcpy(rtnresult, "user_name was used!");
			else
			strcpy(rtnresult, zErrMsg);
		}
		else 
		{
		
			printf("insert data: %s, %s, %s \n",name, psd, phone);
			char create_table_sql[500] = {0};
			char table_name[50] = {0};
			sprintf(table_name, "table_%s", name);
			printf("%s\n", table_name);
			sprintf(create_table_sql, "CREATE TABLE %s (\
			mail_num  INTEGER    PRIMARY KEY,\
			mail_name VARCHAR(50),\
			mail_kind VARCHAR(10),\
			mail_send VARCHAR(20),\
			mail_rece VARCHAR(200),\
			mail_time VARCHAR(25),\
			text_num  VARCHAR(20),\
			mail_info VARCHAR(200));",table_name);
			sqlite3_exec(db, create_table_sql, 0, 0, &zErrMsg);
			if (zErrMsg == NULL)
			{
				strcpy(rtnresult, "insert success!");
				printf("insert success!\n");
			}
			else
			{
			strcpy(rtnresult, zErrMsg);
			printf("%s\n", zErrMsg);
			}
		}
	}
	sqlite3_close(db);
}

