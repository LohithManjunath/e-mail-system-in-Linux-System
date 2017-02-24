#include"head.h"
#include"client.h"
#include<gtk/gtk.h>
GtkWidget *window2;
GtkWidget *entry1;
GtkWidget *entry2;
int sd;
int rc;
int res;
void get_User(GtkWidget *widget,gpointer data)
{
	
	char flag='l';
	rc=send(sd, &flag,sizeof(flag), 0);		//send
	g_print("9\n");
	gchar user_space[20];
	gchar paw_space[20];
	gchar* user=user_space;
	gchar* paw=paw_space;
	int kill=0;
	GtkWidget *dialog;
	gchar *message;
	message="登陆成功";
	GtkMessageType type=GTK_MESSAGE_INFO;
	
	strcpy(user,gtk_entry_get_text(GTK_ENTRY(entry1)));
	strcpy(paw,gtk_entry_get_text(GTK_ENTRY(entry2)));

	rc=send(sd, user, 20, 0);
	g_print("8\n");						//send
	if(rc<0)
	{
	    message="cannot send data";
		kill=1;
	    close(sd);
	}
	g_print("paw=%s\n",paw);
	rc=send(sd, paw, 20, 0);
	g_print("rc=%d\n", rc);
	g_print("paw=%s\n",paw);
	g_print("7\n");						//send
	if(rc<0)
	{
	    message="cannot send data";
		kill=1;
	    close(sd);
	}
	
	if(recv(sd, &flag, sizeof(flag), 0)==-1)
	{
		message="can not receive flag";
		kill=1;
		close(sd);
	}
	else if(flag == 'a')
	{
		message="密码错误！";
	}
	else if(flag == 'b')
	{
		message="没有此用户！请注册~";
		
	}
	else if(flag == 'c')
	{
		gtk_widget_destroy(window2);

		//gtk_main_quit();
		//pthread_exit("ok!");
		return 0;					//login successful 0
	}
	gtk_entry_set_text(GTK_ENTRY(entry1),"");
	gtk_entry_set_text(GTK_ENTRY(entry2),"");
	dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,type,GTK_BUTTONS_OK,message,NULL);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	if(kill==1)
	{
		exit(1);
	}
}


void create_User(GtkWidget *widget,gpointer data)
{
	char flag;
	flag='r';
	int kill=0;
	GtkWidget *dialog;
	gchar *message;
	message="登陆成功";
	GtkMessageType type=GTK_MESSAGE_INFO;

	rc=send(sd, &flag, sizeof(flag), 0);		//send
	if(rc<0)
	{
	    message="cannot send data";
		kill=1;
	    close(sd);
	}
	printf("in login_pthread had send flag='r' to the server.\n");
	if(kill==1)
	{
		dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,type,GTK_BUTTONS_OK,message,NULL);
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		exit(1);
	}
	

	gtk_widget_destroy(window2);
	//gtk_main_quit();
	
	//pthread_exit("regiter!");
	return 1;								//register is 1
	
}

//void *loginpthread(void *arg)
int loginpthread(int *arg)
{


	GtkWidget *table1;

	GtkWidget *button1;
	GtkWidget *button2;

	GtkWidget *label1;
	GtkWidget *label2;
	printf("welcome to the login_ptread_client\n");
	printf("[%s, %s, %d]\n", __FILE__, __FUNCTION__, __LINE__);

	//sd = *((int *)arg);
	sd = *(arg);

	window2 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window2),"Login");
	gtk_window_set_position( GTK_WINDOW(window2),GTK_WIN_POS_CENTER_ALWAYS );
 	//g_signal_connect (G_OBJECT (window2), "destroy",G_CALLBACK (gtk_main_quit), NULL);
	//g_signal_connect_swapped (G_OBJECT (window2), "delete_event",G_CALLBACK (gtk_widget_destroy),window2);
	table1 = gtk_table_new (4,2,FALSE);
	printf("welcome to the login_ptread_client\n");
	entry1 = gtk_entry_new_with_max_length(50);
	entry2 = gtk_entry_new_with_max_length(50);
	gtk_entry_set_visibility (GTK_ENTRY (entry2),0);

	button1 = gtk_button_new_with_label("注册");
	button2 = gtk_button_new_with_label("登陆");

	label1 = gtk_label_new("邮箱");
	label2 = gtk_label_new("密码");
printf("[%s, %s, %d]\n", __FILE__, __FUNCTION__, __LINE__);
	gtk_container_add(GTK_CONTAINER(window2),table1);

	gtk_table_attach(GTK_TABLE(table1),label1,0,1,0,1,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(table1),entry1,1,2,0,1,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(table1),label2,0,1,1,2,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(table1),entry2,1,2,1,2,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach_defaults(GTK_TABLE(table1),button2,0,2,2,3);
	gtk_table_attach_defaults(GTK_TABLE(table1),button1,0,2,3,4);
	g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(create_User),window2);
	g_signal_connect(G_OBJECT(button2),"clicked",G_CALLBACK(get_User),window2);
//

	gtk_widget_show_all(window2);
printf("[%s, %s, %d]\n", __FILE__, __FUNCTION__, __LINE__);
	printf("welcome to the login_ptread_client\n");
	printf("wwwwwwwwwwelcome to the login_ptread_client\n");
//	pthread_exit("regiter!");
}
