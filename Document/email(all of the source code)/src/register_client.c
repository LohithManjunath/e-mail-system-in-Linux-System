#include"head.h"
#include"client.h"
#include<gtk/gtk.h>

GtkWidget *entry1;
GtkWidget *entry2;
GtkWidget *entry3;
GtkWidget *entry4;
GtkWidget *window;
int rc;
int sd;
char flag;
void Clean( GtkWidget *widget,gpointer   data)
{
	gtk_entry_set_text(GTK_ENTRY(entry1),(""));
	gtk_entry_set_text(GTK_ENTRY(entry2),(""));
	gtk_entry_set_text(GTK_ENTRY(entry3),(""));
	gtk_entry_set_text(GTK_ENTRY(entry4),(""));
}

void Reg( GtkWidget *widget,gpointer   data)
{
	GtkWidget *dialog;
	int kill=0;
	int pass=0;
	int i;
	gchar user[U_MSG];
	gchar pdw[U_MSG];
	gchar tel[U_MSG];
	gchar *message;
	message="注册成功！";
	GtkMessageType type=GTK_MESSAGE_INFO;
//tel
	strcpy(tel,gtk_entry_get_text(GTK_ENTRY(entry4)));
	if(strlen(tel)>11)
	{
		message="电话号码太长！";
	}
	else
	{
		++pass;
		printf("pass=%d\n",pass);
	}
//pdw
	strcpy(pdw,gtk_entry_get_text(GTK_ENTRY(entry2)));
	if(strlen(pdw)==0)
	{
		message="请输入密码！";
	}
	else if(strlen(pdw)<6||strlen(pdw)>16)
	{
		message="密码请输入6~16个字符!";
	}
	else if(strcmp(gtk_entry_get_text(GTK_ENTRY(entry2)),gtk_entry_get_text(GTK_ENTRY(entry3)))!=0)
	{
		message="两次输入密码不一致！";
	}
	else
	{
		++pass;
		printf("pass=%d\n",pass);
	}	
	
//user
	strcpy(user,gtk_entry_get_text(GTK_ENTRY(entry1)));
	if(strlen(user)==0)
	{
		message="请输入邮箱名！";
	}
	else if(strlen(user)<6||strlen(user)>16)
	{
		message="邮箱名请输入6~16个字符!";
	}
	else if(strlen(user))
	{
		if((user[0]>=65&&user[0]<=90)||(user[0]>=97&&user[0]<=122))
		{
			for(i=0;i<strlen(user);++i)
			{
				if((user[i]>=65&&user[i]<=90)||(user[i]>=97&&user[i]<=122)||(user[i]>=48&&user[i]<=57)||user[i]==95)
				{
					++pass;
					printf("pass=%d\n",pass);
				}
				else
				{
					message="邮箱名包含非法字符！";
				}
			}
			pass-=strlen(user)-1;
			printf("pass=%d\n",pass);
		}
		else
		{
			message="邮箱名请以字母开头！";
		}
	}
	printf("pass=%d\n",pass);
	if(pass==3)
	{
		rc=send(sd, user, 20, 0);	//send
		printf("rc1=%d\n",rc);
		if(rc<0)
		{
			kill=1;
		}
		rc=send(sd, pdw, 18, 0);	//send
		printf("rc2=%d\n",rc);
		if(rc<0)
		{
			kill=1;
		}
		rc=send(sd, tel, 12, 0);	//send
		printf("rc3=%d\n",rc);
		if(rc<0)
		{
			kill=1;
		}	
	
		if(recv(sd, &flag, sizeof(flag), 0)==-1)
		{
			message="can not receive flag";
			kill=1;
			close(sd);
		}
		else if(flag == 'y')
		{
			gtk_widget_destroy(window);
			//pthread_exit("ok!");
			return 0;						//register successful!
			message="注册成功！！";
		}
		else if(flag == 'n')
		{
			message="用户名已经占用！";
		}
	}
	g_print("kill=%d\n",kill);
	if(kill==1)
	{
		message="cannot send data";
	    	close(sd);
	}
	dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,type,GTK_BUTTONS_OK,message,NULL);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	if(flag=='y')
	{
		
	}
	if(kill==1) 
	{
		exit(1);
	}
	
}

//void *register_thread(void *arg)
int register_thread(int *arg)
{
	g_print("welcome to the register_pthread_client\n");
	sd = *((int *)arg);



	GtkWidget *table1;
	
	GtkWidget *button1;
	GtkWidget *button2;

	GtkWidget *label2;
	GtkWidget *label3;
	GtkWidget *label4;
	GtkWidget *label5;
	GtkWidget *label6;
	GtkWidget *label7;
	GtkWidget *label8;
	GtkWidget *label9;

	GtkWidget *frame;

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request (GTK_WIDGET (window),605,210);
 	//g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect_swapped (G_OBJECT (window), "delete_event",G_CALLBACK (gtk_widget_destroy),window);

	table1 = gtk_table_new (6,4,FALSE);
	frame=gtk_frame_new("欢迎注册 么么邮 免费邮箱"); 

	gtk_container_add(GTK_CONTAINER(window),frame);/*将框架构件加入窗体*/

	gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_OUT);

	entry1 = gtk_entry_new();
	entry2 = gtk_entry_new();
	entry3 = gtk_entry_new();
	entry4 = gtk_entry_new();

	button1 = gtk_button_new_with_label("提交");
	gtk_widget_set_size_request (button1,250, 30);
	button2 = gtk_button_new_with_label("重置");
	gtk_widget_set_size_request (button2,250, 30);

	label2 = gtk_label_new("*邮件地址");
	label3 = gtk_label_new("6~16个字符，包括字母、数字、下划线，以字母开头");
	label4 = gtk_label_new("* 密码");
	label5 = gtk_label_new("6~16个字符，包括字母、数字、特殊字符，区分大小写");
	label6 = gtk_label_new("*确认密码");
	label7 = gtk_label_new("请再次确认密码");
	label8 = gtk_label_new("手机号码");
	label9 = gtk_label_new("密码遗忘或被窃是可以通过手机短信找回密码头");

	gtk_container_add(GTK_CONTAINER(frame),table1);


	gtk_table_attach(GTK_TABLE(table1),label2,0,1,1,2,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);
	gtk_table_attach(GTK_TABLE(table1),entry1,1,2,1,2,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);
	gtk_table_attach(GTK_TABLE(table1),label3,2,4,1,2,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);

	gtk_table_attach(GTK_TABLE(table1),label4,0,1,2,3,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);
	gtk_table_attach(GTK_TABLE(table1),entry2,1,2,2,3,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);
	gtk_table_attach(GTK_TABLE(table1),label5,2,4,2,3,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);

	gtk_table_attach(GTK_TABLE(table1),label6,0,1,3,4,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);
	gtk_table_attach(GTK_TABLE(table1),entry3,1,2,3,4,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);
	gtk_table_attach(GTK_TABLE(table1),label7,2,4,3,4,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);

	gtk_table_attach(GTK_TABLE(table1),label8,0,1,4,5,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);
	gtk_table_attach(GTK_TABLE(table1),entry4,1,2,4,5,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);
	gtk_table_attach(GTK_TABLE(table1),label9,2,4,4,5,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);


	gtk_table_attach(GTK_TABLE(table1),button1,0,2,5,6,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(table1),button2,2,4,5,6,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);

	g_signal_connect (G_OBJECT (button2), "clicked",G_CALLBACK (Clean), NULL);
	g_signal_connect (G_OBJECT (button1), "clicked",G_CALLBACK (Reg), NULL);
	gtk_entry_set_visibility (GTK_ENTRY (entry2),0);
	gtk_entry_set_visibility (GTK_ENTRY (entry3),0);
		



	gtk_widget_show_all(window);
}
