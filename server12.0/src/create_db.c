#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"


 void db_table_create(sqlite3 *db, char* db_sql_create)
{
	
	char *zErrMsg = 0;
	sqlite3_exec(db, db_sql_create, 0, 0, &zErrMsg);
	if (zErrMsg == NULL)	
	{		
		printf("create table successfully!\n");
	}	
	else
	{	
		printf("zErrMsg = %s\n", zErrMsg);
	}
	
}


int main(int argc, char* argv[])
{		
	sqlite3 *db = NULL;
	int rc;
	rc = sqlite3_open("db.db", &db);
	if (rc)
	{
		printf(stderr, "can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("create database db.db sucessfully!\n");
	}
	
	db_table_create(db, "CREATE TABLE user_info(\
	user_name  VARCHAR(20) PRIMARY KEY,\
	user_psd   VARCHAR(20),\
	user_phone VARCHAR(20));");
	printf("table 1: user_info!\n");
	
	db_table_create(db, "CREATE TABLE mail_text(\
	text_num   INTEGER PRIMARY KEY,\
	text_text  VARCHAR(2048),\
	text_info  VARCHAR(200),\
	add_name   VARCHAR(200),\
	text_add   VARCHAR(2048));");
	printf("table 2: mail_text!\n");
	sqlite3_close(db);
	return 0;
}
