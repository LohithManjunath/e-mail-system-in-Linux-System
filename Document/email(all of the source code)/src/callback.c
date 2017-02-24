#include"head.h"
#include"window.h"
#include"callback.h"
#include"gv.h"
#include<gtk/gtk.h>


void on_button_clicked_welcom(GtkWidget *button,gpointer data)
{
	gtk_widget_hide_all(window_welcom);
	window_login = new_login_window();
	gtk_widget_show_all(window_login);
}

void login_get_User(GtkWidget *button,gpointer data)
{
	int rc;
	char flag;
	MSG bag;//
	gchar user_space[50];
	gchar paw_space[50];
	gchar* user=user_space;
	gchar* paw=paw_space;
	int kill=0;
	GtkWidget *dialog;
	gchar mess[100];
	gchar *message = mess;
	message="登陆成功";
	GtkMessageType type=GTK_MESSAGE_INFO;
	strcpy(user,gtk_entry_get_text(GTK_ENTRY(entry_login_user)));
	strcpy(paw,gtk_entry_get_text(GTK_ENTRY(entry_login_psw)));
	if(strlen(user)==0||strlen(paw)==0)
	{
		message="输入不能为空";
		printf("ga\n");
		dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,type,GTK_BUTTONS_OK,message,NULL);
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		goto login;
	}
	bag.num=0;
	strcpy(bag.uname,user);			
	strcpy(bag.upsw,paw);

	
	bzero(buff,sizeof(buff));
	memcpy(buff,&bag,sizeof(bag));

	do_connect();							//connect
	int x;
    	if( (x = send(socket_descriptor, buff, sizeof(bag), 0))==-1)		//send
   	{
        	perror("can not send message\n");
        	exit(1);
    	}
	printf("the client send %d words\n",x);
	
			
	if((x=recv(socket_descriptor, &flag, sizeof(flag), 0))==-1)		//receive
	{
		message="can not receive flag";
		kill=1;
	}


	if(flag == 'a')
	{
		message="密码错误！";
	}
	else if(flag == 'b')
	{
		message="没有此用户！请注册~";
		
	}
	else if(flag == 'c')
	{
		if((x=recv(socket_descriptor, &client_num, sizeof(client_num), 0))==-1)		//receive
		{
			message="can not receive client_num";
			kill=1;
		}
		bag.num=21;
		bag.client_num = client_num;
		bzero(buff,sizeof(buff));
		memcpy(buff,&bag,sizeof(bag));

		do_connect();							//connect
		char email_num[10];
    		if( (x = send(socket_descriptor, buff, sizeof(bag), 0))==-1)		//send
   		{
      	 	 	perror("can not send message\n");
      	  		exit(1);
    		}

	
			memset(email_num,0,sizeof(email_num));

		if(recv(socket_descriptor, email_num, 10, 0)==-1)		//receive
		{
			message="can not receive email_num";
			kill=1;
		}

		//sprintf(message,"登陆成功\n 你有%s封未读邮件",email_num);
	
		gchar b[100];
		b[0] = '\0';
		message=strcat(b,"登陆成功\n 你有");
		printf("%s\n",b);
		message=strcat(b,email_num);
		printf("%s\n",b);
		message=strcat(b,"封未读邮件");
		printf("%s\n",b);

		gtk_widget_hide_all(window_login);
		window_main = new_main_window();
		gchar l[20];
		l[0] = '\0';
		strcat(l,"未读邮件: ");
		strcat(l,email_num);
		gtk_label_set_text(main_label,l);
		window_send = new_send_window();
		gtk_widget_show_all(window_main);

		dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,type,GTK_BUTTONS_OK,message,NULL);
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		goto login;
	}
	gtk_entry_set_text(GTK_ENTRY(entry_login_user),"");
	gtk_entry_set_text(GTK_ENTRY(entry_login_psw),"");
	dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,type,GTK_BUTTONS_OK,message,NULL);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
login:
	close(socket_descriptor);					//close
	if(kill==1)
	{
		exit(1);
	}
}

void recover_item(GtkWidget * widget, gpointer selection)
{

	GtkListStore *store;

	GtkTreeModel *model;

	GtkTreeIter iter;

	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

	if (gtk_tree_model_get_iter_first(model, &iter) == FALSE)

        return;
	
	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter)) {
	
		do_connect();				//connect

		bzero(buff,sizeof(buff));
		M.num = 10;
		memcpy(buff,&M,sizeof(M));	
	
		int x ;	
		if((x = send(socket_descriptor, buff, sizeof(M), 0))==-1)		//send
    		{
        		perror("can not send message\n");
       		 	exit(1);
  		}
		printf("in the send_send function the client send %d words\n",x);

		
		close(socket_descriptor);				//close

		
		gtk_list_store_remove(store, &iter);
	}
}





void login_create_User(GtkWidget *button,gpointer data)
{
	gtk_widget_hide_all(window_login);
	window_register = new_register_window();
	gtk_widget_show_all(window_register);
	
}

void login_change_psw(GtkWidget *button,gpointer data )
{
	gtk_widget_hide_all(window_login);
	window_change_psw = new_change_psw_window();
	gtk_widget_show_all(window_change_psw);
}

void change_psw_ok(GtkWidget *widget,gpointer   data )
{
	int rc;
	char flag;
	MSG bag;//
	gchar psw_re_space[50];
	gchar psw_new_space[50];
	gchar psw_user_space[50];
	gchar psw_new2_space[50];
	gchar* psw_re=psw_re_space;
	gchar* psw_new=psw_new_space;
	gchar* psw_user=psw_user_space;
	gchar* psw_new2=psw_new2_space;
	int kill=0;
	GtkWidget *dialog;
	gchar *message;
	message="修改成功";
	GtkMessageType type=GTK_MESSAGE_INFO;
	strcpy(psw_re,gtk_entry_get_text(GTK_ENTRY(entry_change_psw_re)));
	strcpy(psw_new,gtk_entry_get_text(GTK_ENTRY(entry_change_psw_new)));
	strcpy(psw_user,gtk_entry_get_text(GTK_ENTRY(entry_change_psw_user)));
	strcpy(psw_new2,gtk_entry_get_text(GTK_ENTRY(entry_change_psw_new2)));

	if(strlen(psw_re)==0||strlen(psw_new)==0||strlen(psw_user)==0)
	{
		message="输入不能为空";
		goto change;
	}
	else if(strlen(psw_new)<6||strlen(psw_new)>16)
	{
		message="密码请输入6~16个字符!";
		goto change;
	}
	else if(strcmp(psw_new,psw_re)==0)
	{
		message="与原密码一致！";
		goto change;
	}
	else if(strcmp(psw_new,psw_new2)!=0)
	{
		message="两次输入密码不一致！";
		goto change;
	}
	bag.num=4;
	strcpy(bag.uname,psw_user);		
	strcpy(bag.upsw,psw_re);
	strcpy(bag.utel,psw_new);	
	printf("the bag.uname is %s\nthe bag.upsw is %s\nthe bag.utel is %s\n",bag.uname,bag.upsw, bag.utel);
	
	bzero(buff,sizeof(buff));
	memcpy(buff,&bag,sizeof(bag));

	do_connect();							//connect
	int x;
    	if( (x = send(socket_descriptor, buff, sizeof(bag), 0))==-1)		//send
   	{
        	perror("can not send message\n");
        	exit(1);
    	}
	printf("the client send %d words\n",x);
	
			
	if(recv(socket_descriptor, &flag, sizeof(flag), 0)==-1)		//receive
	{
		message="can not receive flag";
		kill=1;
	}

	close(socket_descriptor);					//close
	if(flag == 'n')
	{
		message="账户或密码错误！";
	}
	else if(flag == 'y')
	{
		gtk_widget_hide_all(window_change_psw);
		gtk_widget_show_all(window_login);
		goto change;
	}
	
change:
	dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,type,GTK_BUTTONS_OK,message,NULL);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);

	gtk_entry_set_text(GTK_ENTRY(entry_change_psw_user),"");
	gtk_entry_set_text(GTK_ENTRY(entry_change_psw_re),"");
	gtk_entry_set_text(GTK_ENTRY(entry_change_psw_new),"");
	gtk_entry_set_text(GTK_ENTRY(entry_change_psw_new2),"");
	if(kill==1)
	{
		exit(1);
	}
}

void change_psw_return(GtkWidget *widget,gpointer   data )
{
	gtk_widget_hide_all(window_change_psw);
	gtk_widget_show_all(window_login);
}

void Clean( GtkWidget *widget,gpointer   data)
{
	gtk_entry_set_text(GTK_ENTRY(entry_reg_user),(""));
	gtk_entry_set_text(GTK_ENTRY(entry_reg_psw),(""));
	gtk_entry_set_text(GTK_ENTRY(entry_reg_psw2),(""));
	gtk_entry_set_text(GTK_ENTRY(entry_reg_tel),(""));
}

void Reg( GtkWidget *widget,gpointer   data)
{
	GtkWidget *dialog;
	MSG bag;//
	int kill=0;
	int pass=0;
	int i;
	char flag;
	gchar user[U_MSG];
	gchar pdw[U_MSG];
	gchar tel[U_MSG];
	gchar *message;
	message="注册成功！";
	GtkMessageType type=GTK_MESSAGE_INFO;
//tel
	strcpy(tel,gtk_entry_get_text(GTK_ENTRY(entry_reg_tel)));
	if(strlen(tel)>11)
	{
		message="电话号码太长！";
	}
	else
	{
		++pass;
		
	}
//pdw
	strcpy(pdw,gtk_entry_get_text(GTK_ENTRY(entry_reg_psw)));
	if(strlen(pdw)==0)
	{
		message="请输入密码！";
	}
	else if(strlen(pdw)<6||strlen(pdw)>16)
	{
		message="密码请输入6~16个字符!";
	}
	else if(strcmp(gtk_entry_get_text(GTK_ENTRY(entry_reg_psw)),gtk_entry_get_text(GTK_ENTRY(entry_reg_psw2)))!=0)
	{
		message="两次输入密码不一致！";g_print("1");
	}
	else
	{
		++pass;
		
	}	
	
//user
	strcpy(user,gtk_entry_get_text(GTK_ENTRY(entry_reg_user)));
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
				
				}
				else
				{
					message="邮箱名包含非法字符！";
				}
			}
			pass-=strlen(user)-1;
			
		}
		else
		{
			message="邮箱名请以字母开头！";
		}
	}

	if(pass==3)
	{
		bag.num=1;
		strcpy(bag.uname,user);	
		strcpy(bag.upsw,pdw);
		strcpy(bag.utel,tel);
		bzero(buff,sizeof(buff));
		memcpy(buff,&bag,sizeof(bag));
		do_connect();							//connect
	
   	 	if(send(socket_descriptor, buff, sizeof(bag), 0)==-1)		//send
	   	{
        		perror("can not send message\n");
        		exit(1);
    		}
		
				
		if(recv(socket_descriptor, &flag, sizeof(flag), 0)==-1)		//receive
		{
			message="can not receive flag";
			kill=1;
		}

		close(socket_descriptor);					//close
		if(flag == 'y')
		{
			gtk_widget_hide_all(window_register);
			gtk_widget_show_all(window_login);
			dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,type,GTK_BUTTONS_OK,message,NULL);
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
			goto rend;
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
rend:
	if(kill==1) 
	{
		exit(1);
	}

}

void reg_Clean( GtkWidget *widget,gpointer   data)
{
	gtk_entry_set_text(GTK_ENTRY(entry_reg_user),(""));
	gtk_entry_set_text(GTK_ENTRY(entry_reg_psw),(""));
	gtk_entry_set_text(GTK_ENTRY(entry_reg_psw2),(""));
	gtk_entry_set_text(GTK_ENTRY(entry_reg_tel),(""));
}



void on_button_clicked(GtkButton* button,gpointer data)
{
	g_print("nidianle%s\n",(gchar*)data);
}

void on_edit_cut_activate(GtkButton* button,gpointer data )
{
	gtk_text_buffer_cut_clipboard(buffer,clipboard,TRUE);
}

void on_edit_copy_activate(GtkButton* button,gpointer data )
{
	gtk_text_buffer_copy_clipboard(buffer,clipboard);
}

void on_edit_paste_activate(GtkButton* button,gpointer data )
{
	gtk_text_buffer_paste_clipboard(buffer,clipboard,NULL,TRUE);
}

void send_creat_new_file(GtkButton* button,gpointer data)
{
	GtkTextIter start, end;        /*定义迭代器起点终点 */
        gtk_text_buffer_get_bounds (GTK_TEXT_BUFFER (buffer), &start, &end);
	MSG MES;
	gchar title_anrry[30],text_anrry[1000];
	gchar *tit = title_anrry;
	gchar *tex = text_anrry;
	tit = (gchar *)gtk_entry_get_text (GTK_ENTRY ( entry_name ));
	tex = gtk_text_buffer_get_text (GTK_TEXT_BUFFER (buffer),&start,&end,TRUE);
	strcpy(MES.mtitle,tit);
	strcpy(MES.mtext,tex);
	MES.num = 3;                   //save
	MES.client_num=client_num;
	do_connect();				//connect

	bzero(buff,sizeof(buff));
	memcpy(buff,&MES,sizeof(MES));	
	if(send(socket_descriptor, buff, sizeof(MES), 0)==-1)		//send
    	{
        	perror("can not send message\n");
        	exit(1);
  	}
	char flag;
	if(recv(socket_descriptor,&flag,sizeof(flag),0) < 0)		//receive
	{
		perror("the client can not receive the flag from the server!\n");
		exit(1);
	}
	close(socket_descriptor);				//close
	GtkWidget * dialog;
	gchar * message;
	GtkMessageType type = GTK_MESSAGE_INFO;
	if(flag == 'y'||flag == 'Y')
		message = "保存成功";
	else
		message = "保存失败";	
	dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,type,GTK_BUTTONS_OK,message,NULL);
	gtk_dialog_run(GTK_DIALOG(dialog));	
	gtk_widget_destroy(dialog);
	gtk_text_buffer_set_text(buffer,"",0);
	gtk_entry_set_text (GTK_ENTRY ( entry_name ), "请键入邮件主题");
}

void send_save_mail(GtkButton* button,gpointer data )
{
	GtkTextIter start, end;        /*定义迭代器起点终点 */
        gtk_text_buffer_get_bounds (GTK_TEXT_BUFFER (buffer), &start, &end);
	MSG MES;
	gchar title_anrry[30],text_anrry[1000];
	gchar *tit = title_anrry;
	gchar *tex = text_anrry;
	tit = (gchar *)gtk_entry_get_text (GTK_ENTRY ( entry_name ));
	tex = gtk_text_buffer_get_text (GTK_TEXT_BUFFER (buffer),&start,&end,TRUE);
	strcpy(MES.mtitle,tit);
	strcpy(MES.mtext,tex);
	MES.num = 3;                            //save
	MES.client_num=client_num;
	do_connect();				//connect

	bzero(buff,sizeof(buff));
	memcpy(buff,&MES,sizeof(MES));	
	if(send(socket_descriptor, buff, sizeof(MES), 0)==-1)		//send
    	{
        	perror("can not send message\n");
        	exit(1);
  	}
	char flag;
	if(recv(socket_descriptor,&flag,sizeof(flag),0) < 0)		//receive
	{
		perror("the client can not receive the flag from the server!\n");
		exit(1);
	}
	close(socket_descriptor);				//close
	GtkWidget * dialog;
	gchar * message;
	GtkMessageType type = GTK_MESSAGE_INFO;
	if(flag == 'y'||flag == 'Y')
		message = "保存成功";
	else
		message = "保存失败";
	dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL |GTK_DIALOG_DESTROY_WITH_PARENT,type,GTK_BUTTONS_OK,message,NULL);
	gtk_dialog_run(GTK_DIALOG(dialog));	
	gtk_widget_destroy(dialog);
}

void send_file_ok_sel( GtkWidget *w,GtkFileSelection *fs )
{
    g_print ("%s\n", gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs)));
}

void send_attach_button(GtkWidget *widget,gpointer data)
{
	GtkWidget *filew;
	filew = gtk_file_selection_new ("添加附件");
	g_signal_connect (G_OBJECT (filew), "destroy",G_CALLBACK (gtk_widget_destroy), NULL);
	g_signal_connect (G_OBJECT (GTK_FILE_SELECTION (filew)->ok_button),"clicked", G_CALLBACK (send_file_ok_sel), filew);
	g_signal_connect_swapped (G_OBJECT (GTK_FILE_SELECTION (filew)->cancel_button),"clicked", G_CALLBACK (gtk_widget_destroy), filew);
	gtk_file_selection_set_filename (GTK_FILE_SELECTION(filew), "penguin.png");
	gtk_widget_show (filew);
}

void send_send_button(GtkWidget *widget,gpointer data)
{


	GtkTextIter start, end;        /*定义迭代器起点终点 */
        gtk_text_buffer_get_bounds (GTK_TEXT_BUFFER (buffer), &start, &end);

	MSG MES;
	
	gchar recipient_anrry[200],title_anrry[30],text_anrry[1000],copy_anrry[50],secret_anrry[50];
	
	gchar *rec = recipient_anrry;
	gchar *tit = title_anrry;
	gchar *tex = text_anrry;
	gchar *cop = copy_anrry;
	gchar *sec = secret_anrry;
	gchar tar[200],tar1[1000];	
	gchar *target = tar;
	gchar *target1 = tar1;
	*target = '\0';
	*target1 = '\0';
	rec = (gchar *)gtk_entry_get_text (GTK_ENTRY ( entry_rec ));
	tit = (gchar *)gtk_entry_get_text (GTK_ENTRY ( entry_name ));
	cop = (gchar *)gtk_entry_get_text (GTK_ENTRY ( entry_copy ));
	sec = (gchar *)gtk_entry_get_text (GTK_ENTRY ( entry_secret ));

	tex = gtk_text_buffer_get_text (GTK_TEXT_BUFFER (buffer),&start,&end,TRUE);
	strcpy(target,rec);
	gint len = strlen(target);
	if(*(target+len-1)!=';')
	{
		*(target+len) = ';';
		*(target+len+1) = '\0';
	}
	strcat(target,cop);
	len = strlen(target);
	if(*(target+len-1)!=';')
	{
		*(target+len) = ';';
		*(target+len+1) = '\0';
	}
	strcat(target,sec);
	len = strlen(target);
	if(*(target+len-1)!=';')
	{
		*(target+len) = ';';
		*(target+len+1) = '\0';
	}
	
	strcpy(target1,tex);
	if(*cop != '/0')
	{
		strcat(target1,"\n\n");
		strcat(target1,"Make a copy for:");
		strcat(target1,cop);
	}
	strcpy(MES.receiver,target);                                                                ////////////////////////
	strcpy(MES.mtitle,tit);
	strcpy(MES.mtext,target1);
	MES.num = 2;                               //send
	MES.client_num=client_num;
	do_connect();				//connect

	bzero(buff,sizeof(buff));
	memcpy(buff,&MES,sizeof(MES));	
	
	int x ;	
	if((x = send(socket_descriptor, buff, sizeof(MES), 0))==-1)		//send
    	{
        	perror("can not send message\n");
        	exit(1);
  	}
	printf("in the send_send function the client send %d words\n",x);

	char flag;
	if(recv(socket_descriptor,&flag,sizeof(flag),0) < 0)		//receive
	{
		perror("the client can not receive the flag from the server!\n");
		exit(1);
	}
	close(socket_descriptor);				//close
	
	GtkWidget * dialog;
	gchar * message;
	GtkMessageType type = GTK_MESSAGE_INFO;
	if(flag == 'y'||flag == 'Y')
		message = "发送成功";
	else
		message = "发送失败";	
	dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,type,GTK_BUTTONS_OK,message,NULL);
	gtk_dialog_run(GTK_DIALOG(dialog));	
	gtk_widget_destroy(dialog);
		

}

void send_color_changed_cb( GtkWidget *widget,GtkColorSelection *colorsel )
{/* 颜色改变信号的处理函数 */
  GdkColor ncolor;
  gtk_color_selection_get_current_color (colorsel, &ncolor);
  //gtk_widget_modify_bg (drawingarea, GTK_STATE_NORMAL, &ncolor);       
}

gint send_area_event( GtkWidget *widget, GtkWidget *view_text )
{/* 绘图区事件处理函数 */
	GtkWidget *colorseldlg = NULL;
	gint handled = FALSE;
	gint response;
	GtkColorSelection *colorsel;
	/* 检查是否接收到一个鼠标按键按下事件 */  
	handled = TRUE;
	/* 创建颜色选择对话框 */
	if (colorseldlg == NULL)
	colorseldlg = gtk_color_selection_dialog_new ("改变文字颜色");
	/* 获取颜色选择构件 */
	colorsel = GTK_COLOR_SELECTION (GTK_COLOR_SELECTION_DIALOG (colorseldlg)->colorsel);
	gtk_color_selection_set_previous_color (colorsel, &color);
	gtk_color_selection_set_current_color (colorsel, &color);
	gtk_color_selection_set_has_palette (colorsel, TRUE);
	/* 为 "color_changed" 信号设置回调函数，将用户数据设置为颜色选择构件 */
	g_signal_connect (G_OBJECT (colorsel), "color_changed",G_CALLBACK (send_color_changed_cb), (gpointer)colorsel);
	/* 显示对话框 */
	response = gtk_dialog_run (GTK_DIALOG (colorseldlg));
	if (response == GTK_RESPONSE_OK)
	{
		gtk_color_selection_get_current_color (colorsel, &color);	
		gtk_widget_modify_text(view_text, GTK_STATE_NORMAL, &color);  
	}
	else 
        	gtk_widget_modify_text(view_text, GTK_STATE_NORMAL, &color);
	gtk_widget_destroy (colorseldlg);
	return handled;
}

void send_toggle_button_callback (GtkWidget *widget, GtkWidget* entry_rec)
{
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget))) 
	{/* 如果运行到这里，开关按钮是按下的 */
		gchar entry_text_anrry[500];
		gchar res_anrry[500];
		gchar target_anrry[500];
		target_anrry[0] = '\0';
		gchar* entry_text = entry_text_anrry;
		gchar* res = res_anrry;
		gchar* target = target_anrry;
		entry_text = (gchar *)gtk_entry_get_text (GTK_ENTRY (entry_select));
		res = (gchar *)gtk_button_get_label( (GtkButton *)widget );
		if( *(entry_text) != '\0' )
		{
			int i = strlen(entry_text);		
			if( *(entry_text+i-1) != ';' )
			{	*(entry_text + i ) = ';';
				*(entry_text + i + 1) = '\0';		
			}
		}
		strcpy(target,entry_text);
		strcat(target,res);
		strcat(target,";");
		gtk_entry_set_text(GTK_ENTRY(entry_select), target );
		gtk_toggle_button_set_active( widget,FALSE );
	} 
	/*else 
	{/* 如果运行到这里，开关按钮是弹起的 */
		/*gchar entry_text_anrry[500],res_anrry[50],target_anrry[500];
		gchar* entry_text = entry_text_anrry,*res = res_anrry,*target = target_anrry;
		g_print("1");
		entry_text = (gchar *)gtk_entry_get_text (GTK_ENTRY (entry_select));
		res = (gchar *)gtk_button_get_label( (GtkButton *)widget );
		gchar* flag_start,*flag_end;
		flag_start = strstr(entry_text,res);
		flag_end = flag_start;
		while(*flag_end != ';')
		{
			flag_end++;
		}
		flag_end++;
		int i=0;
		while(entry_text != flag_start)
		{
			target_anrry[i++] = *entry_text;
			entry_text++;
		}
		while(*flag_end != '\0')
		{
			target_anrry[i++] = *flag_end;
			flag_end++;	
		}
		target_anrry[i] = '\0';
		gtk_entry_set_text(GTK_ENTRY(entry_select), target );
	}*/
}

int send_CHECK_REF(GtkWidget *scroll_window,GtkWidget * *mail)
{
	gint i;
	MSG MES;
	GtkWidget *check_button;
	GtkWidget *box;
	gint n,j,k,len;
	gchar rec[200];
	gchar Result[100][100];
	///////////////////
	MES.num = 9;                               //send
	MES.client_num=client_num;
	do_connect();				//connect

	bzero(buff,sizeof(buff));
	memcpy(buff,&MES,sizeof(MES));	
	
	int x ;	
	if((x = send(socket_descriptor, buff, sizeof(MES), 0))==-1)		//send
    	{
        	perror("can not send message\n");
        	exit(1);
  	}
	printf("in the send_CHECK_REF function the client send %d words\n",x);
	if(recv(socket_descriptor,rec,200,0) < 0)		//receive
	{
		perror("the client can not receive the flag from the server!\n");
		exit(1);
	}
	close(socket_descriptor);				//close
	////////////////////
	len = strlen(rec);
	for(n=0,k=0; k<len; n++)
	{
		for(j=0;rec[k]!=';';j++,k++)
		{
			Result[n][j] = rec[k];
		}
		Result[n][j++] = '\0';
		k++;
	}
	box = gtk_vbox_new(FALSE,0);
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scroll_window), box);
	for(i=0;i<n;i++)
	{
		check_button = gtk_check_button_new_with_label (Result[i]);
		mail[i] = check_button;
		gtk_box_pack_start (GTK_BOX (box), check_button, FALSE, FALSE, 0);
		gtk_widget_show (check_button);
	}
	gtk_widget_show (box);
	return i;
}

void send_font_select_ok(GtkWidget *button,GtkFontSelectionDialog *fs)
{//选择字体

	gchar *s = gtk_font_selection_dialog_get_font_name(fs);
	gtk_widget_destroy(GTK_WIDGET(fs));
	desc_info = pango_font_description_from_string(s);
	gtk_widget_modify_font(view_text,desc_info);
	g_free(s);
}

void send_changefont(GtkWidget *button,GtkWidget *view_text)
{//选择字体
	GtkWidget* dialog;
	GtkWidget* f[2];
	GtkWidget* *a = f;
	*a = view_text;
	*(a+1) = dialog;
	dialog = gtk_font_selection_dialog_new("请选择一种字体:");
	gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
	gtk_signal_connect(GTK_OBJECT(dialog),"destroy",GTK_SIGNAL_FUNC(gtk_widget_destroy),&dialog);
	gtk_signal_connect(GTK_OBJECT(GTK_FONT_SELECTION_DIALOG(dialog)->ok_button),"clicked",GTK_SIGNAL_FUNC(send_font_select_ok),GTK_FONT_SELECTION_DIALOG(dialog));
	gtk_signal_connect_object(GTK_OBJECT(GTK_FONT_SELECTION_DIALOG(dialog)->cancel_button),"clicked",GTK_SIGNAL_FUNC(gtk_widget_destroy),GTK_OBJECT(dialog));
	gtk_widget_show(dialog);
}

void callback_fasong( GtkWidget *widget,gpointer   data )
{
   	gtk_widget_hide_all(window_main);
	gtk_entry_set_text (GTK_ENTRY (entry_name), M.mtitle );
	gtk_entry_set_text (GTK_ENTRY (entry_rec),"" );
	gtk_entry_set_text (GTK_ENTRY (entry_copy), "");
	gtk_entry_set_text (GTK_ENTRY (entry_secret), ""); 
	gtk_text_buffer_set_text(buffer,M.mtext,-1);
	gtk_widget_show_all(window_send);
}
void callback_jieshou( GtkWidget *widget,gpointer   data )
{
	GtkTreeIter iter;
	GtkTreeModel *model;
	GtkListStore *store;
	char* value;
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
	MSG weidu;
	weidu.num=21;
	weidu.client_num = client_num;
	bzero(buff,sizeof(buff));
	memcpy(buff,&weidu,sizeof(weidu));
	do_connect();							//connect
	char email_num[10];
	if( send(socket_descriptor, buff, sizeof(weidu), 0)==-1)		//send
	{
		perror("can not send message\n");
		exit(1);
	}
	
	memset(email_num,0,sizeof(email_num));
	if(recv(socket_descriptor, email_num, 10, 0)==-1)		//receive
	{
		perror("can not receive email_num\n");
	}
	gchar l[20];
	l[0] = '\0';
	strcat(l,"未读邮件: ");
	strcat(l,email_num);
	gtk_label_set_text(main_label,l);
   	M.num = 5;			
	gtk_list_store_clear(store);
	MAILBOX rcvmb;
	MSG sndmsg;
	sndmsg.num = 11;
	getmailbox(sndmsg, client_num, &rcvmb);
	printf("%d\n", rcvmb.mailnum);
	int i;
	for (i = 0; i < rcvmb.mailnum; i++)
	{
		gchar *s1 = rcvmb.sender[i];
		gchar *s2 = rcvmb.title[i];
		gchar *s3 = rcvmb.time[i];
		int *s4 = rcvmb.no[i];
		gchar *s5 = rcvmb.rmstat[i];
		gchar *s6 = "lixingxing";
		add_to_list(list, s1,s2,s3,s4,s5,s6);
	}
	g_free(value);
}

void callback_sort( GtkWidget *widget,gpointer   data )/////////create
{
	char s_ob[50];
	strcpy(s_ob,gtk_entry_get_text(GTK_ENTRY(data)));
    	printf ("sort - %s was pressed\n", s_ob);
	char* value;
	GtkTreeIter iter;
	GtkTreeModel *model;
	GtkListStore *store;
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));

	gtk_list_store_clear(store);
	
	MAILBOX rcvmb;
	MSG sndmsg;

	switch (lxxlzyqdsdsb)            //switch (Delete_flag)  sndmsg.num =
	{
		case 1:
			sndmsg.num = 11;
			break;
		case 2:
			sndmsg.num = 16;
			break;
		case 3:
			sndmsg.num = 17;
			break;
		case 4:
			sndmsg.num = 13;
			break;
		case 5:
			sndmsg.num = 14;
			break;
		case 6:
			sndmsg.num = 15;
			break;
	}

	strcpy(sndmsg.sortkey, s_ob);

	getmailbox(sndmsg, client_num, &rcvmb);
	printf("%d\n", rcvmb.mailnum);
	int i;
	for (i = 0; i < rcvmb.mailnum; i++)
	{
		gchar *s1;

		if ((lxxlzyqdsdsb == 1) || (lxxlzyqdsdsb == 2) || (lxxlzyqdsdsb == 3))
			s1 = &rcvmb.sender[i];
		else if (lxxlzyqdsdsb == 4)
			s1 = &rcvmb.receiver[i];
		else if (lxxlzyqdsdsb == 5)
			s1 = "";
		else if (lxxlzyqdsdsb == 6)
		{
			if (strcmp(rcvmb.database_flag[i], "r")) {s1 = &rcvmb.receiver[i];printf("receiver %s\n",rcvmb.receiver[i]);}
			else if (strcmp(rcvmb.database_flag[i], "s")) s1 = &rcvmb.sender[i];
			else if (strcmp(rcvmb.database_flag[i], "d")) s1 = "";
		}
		gchar *s2 = rcvmb.title[i];
		gchar *s3 = rcvmb.time[i];
		gint *s4 = rcvmb.no[i];
		gchar *s5 = rcvmb.rmstat[i];
		gchar *s6 = rcvmb.database_flag[i];
	
		if ((lxxlzyqdsdsb != 1) && (lxxlzyqdsdsb != 2) && (lxxlzyqdsdsb != 3)) s5 = "y";

		add_to_list(list, s1,s2,s3,s4,s5,s6);
	}
		
}


void callback_xinjian( GtkWidget *widget,gpointer   data )
{
	gtk_widget_hide_all(window_main);
	gtk_entry_set_text (GTK_ENTRY (entry_name), "请键入邮件主题");
	gtk_entry_set_text (GTK_ENTRY (entry_rec), "");
	gtk_entry_set_text (GTK_ENTRY (entry_copy), "");
	gtk_entry_set_text (GTK_ENTRY (entry_secret), "");    
	gtk_text_buffer_set_text(buffer,"",0);
	gtk_widget_show_all(window_send);
}


void callback_huifu( GtkWidget *widget,gpointer   data )
{
    	gtk_widget_hide_all(window_main);
	gchar tit[100];
	gchar * ti = tit;
	*ti = '\0'; 
	strcat(ti,"RC:");
	strcat(ti,M.mtitle);
	gtk_entry_set_text (GTK_ENTRY (entry_name),ti );
	gtk_entry_set_text (GTK_ENTRY (entry_rec), M.sender );
	gtk_entry_set_text (GTK_ENTRY (entry_copy), "");
	gtk_entry_set_text (GTK_ENTRY (entry_secret), "");  
	gtk_text_buffer_set_text(buffer,"",0);
	gtk_widget_show_all(window_send);
}

void callback_zhuanfa( GtkWidget *widget,gpointer   data )
{
   	gtk_widget_hide_all(window_main);
	gchar tit[100];
	gchar * ti = tit;
	*ti = '\0';
	strcat(ti,M.mtitle);
	strcat(ti,"转发自:");
	strcat(ti,M.sender);
	g_print("%s",M.sender);
	gtk_entry_set_text (GTK_ENTRY (entry_name),ti );
	gtk_entry_set_text (GTK_ENTRY (entry_rec),"" );
	gtk_entry_set_text (GTK_ENTRY (entry_copy), "");
	gtk_entry_set_text (GTK_ENTRY (entry_secret), "");       
	gtk_text_buffer_set_text(buffer,M.mtext,-1);
	g_print("%s",M.mtext);
	gtk_widget_show_all(window_send);
}
void add_to_list(GtkWidget * list, const gchar * str,const gchar * str1,const gchar * str2,const gint * str3,const gchar * str4,const gchar * str5)
{///////////////////////////////////right tree

	GtkListStore *store;

	GtkTreeIter iter;

	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));


	gtk_list_store_append(store, &iter);

	gtk_list_store_set(store, &iter,LIST_TWO, str,LIST_THREE, str1,LIST_FOUR, str2,LIST_FIVE,str3,LIST_SIX,str4,LIST_SEVEN,str5, -1);

}

void on_changed(GtkWidget* widget,gpointer statusbar)
{
	GtkTreeIter iter;
	GtkTreeModel *model;
	GtkListStore *store;
	char* value;
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
	if(gtk_tree_selection_get_selected(GTK_TREE_SELECTION(widget),&model,&iter))
	{
		gtk_tree_model_get(model,&iter,COLUMN,&value,-1);
		g_printf("%s\n",value);

		MSG sndmsg;

		if(strcmp(value,"Menu")==0)
		{	
			gtk_list_store_clear(store);
		}
		else if(strcmp(value,"收件箱")==0)
		{	
			MSG weidu;
			weidu.num=21;
			weidu.client_num = client_num;
			bzero(buff,sizeof(buff));
			memcpy(buff,&weidu,sizeof(weidu));
			do_connect();							//connect
			char email_num[10];
			if( send(socket_descriptor, buff, sizeof(weidu), 0)==-1)		//send
			{
				perror("can not send message\n");
				exit(1);
			}
	
			memset(email_num,0,sizeof(email_num));
			if(recv(socket_descriptor, email_num, 10, 0)==-1)		//receive
			{
				perror("can not receive email_num");
		
			}
			gchar l[20];
			l[0] = '\0';
			strcat(l,"未读邮件: ");
			strcat(l,email_num);
			gtk_label_set_text(main_label,l);
			M.num = 5;	
			lxxlzyqdsdsb = 1;		
			gtk_list_store_clear(store);
			MAILBOX rcvmb;

			sndmsg.num = 11;
			strcpy(sndmsg.sortkey, "lixingxing");

			getmailbox(sndmsg, client_num, &rcvmb);
			printf("%d\n", rcvmb.mailnum);
			int i;
			for (i = 0; i < rcvmb.mailnum; i++)
			{
				gchar *s1 = rcvmb.sender[i];
				gchar *s2 = rcvmb.title[i];
				gchar *s3 = rcvmb.time[i];
				gint *s4 = rcvmb.no[i];
				gchar *s5 = rcvmb.rmstat[i];
				gchar *s6 = "lixingxing";
	
				add_to_list(list, s1,s2,s3,s4,s5,s6);
			}
		}
		else if(strcmp(value,"已读")==0)
		{	
			M.num = 5;
			lxxlzyqdsdsb = 2;
			gtk_list_store_clear(store);
			MAILBOX rcvmb;

			sndmsg.num = 16;
			strcpy(sndmsg.sortkey, "lixingxing");

			getmailbox(sndmsg, client_num, &rcvmb);
			printf("%d\n", rcvmb.mailnum);
			int i;
			for (i = 0; i < rcvmb.mailnum; i++)
			{
				gchar *s1 = rcvmb.sender[i];
				gchar *s2 = rcvmb.title[i];
				gchar *s3 = rcvmb.time[i];
				gint *s4 = rcvmb.no[i];
				gchar *s5 = rcvmb.rmstat[i];
				gchar *s6 = "lixingxing";

				add_to_list(list, s1,s2,s3,s4,s5,s6);
			}
		}
		else if(strcmp(value,"未读")==0)
		{	
			MSG weidu;
			weidu.num=21;
			weidu.client_num = client_num;
			bzero(buff,sizeof(buff));
			memcpy(buff,&weidu,sizeof(weidu));
			do_connect();							//connect
			char email_num[10];
			if( send(socket_descriptor, buff, sizeof(weidu), 0)==-1)		//send
			{
				perror("can not send message\n");
				exit(1);
			}
	
			memset(email_num,0,sizeof(email_num));
			if(recv(socket_descriptor, email_num, 10, 0)==-1)		//receive
			{
				perror("can not receive email_num");
		
			}
			gchar l[20];
			l[0] = '\0';
			strcat(l,"未读邮件: ");
			strcat(l,email_num);
			gtk_label_set_text(main_label,l);
			M.num = 5;	
			lxxlzyqdsdsb = 3;
			gtk_list_store_clear(store);
			MAILBOX rcvmb;

			sndmsg.num = 17;
			strcpy(sndmsg.sortkey, "lixingxing");

			getmailbox(sndmsg, client_num, &rcvmb);
			printf("%d\n", rcvmb.mailnum);
			int i;
			for (i = 0; i < rcvmb.mailnum; i++)
			{
				gchar *s1 = rcvmb.sender[i];
				gchar *s2 = rcvmb.title[i];
				gchar *s3 = rcvmb.time[i];
				gint *s4 = rcvmb.no[i];
				gchar *s5 = rcvmb.rmstat[i];
				gchar *s6 = "lixingxing";
	
				add_to_list(list, s1,s2,s3,s4,s5,s6);
			}
		}
		else if(strcmp(value,"已发邮件")==0)
		{	
			M.num = 7;
			lxxlzyqdsdsb = 4;				
			gtk_list_store_clear(store);
			MAILBOX rcvmb;

			sndmsg.num = 13;
			strcpy(sndmsg.sortkey, "lixingxing");

			getmailbox(sndmsg, client_num, &rcvmb);
			printf("%d\n", rcvmb.mailnum);
			int i;
			for (i = 0; i < rcvmb.mailnum; i++)
			{
				gchar *s1 = rcvmb.receiver[i];
				gchar *s2 = rcvmb.title[i];
				gchar *s3 = rcvmb.time[i];
				gint *s4 = rcvmb.no[i];
				gchar *s5 = "n";
				gchar *s6 = "lixingxing";
	
				add_to_list(list, s1,s2,s3,s4,s5,s6);
			}
		}
		else if(strcmp(value,"草稿")==0)
		{	
			M.num = 8;	
			lxxlzyqdsdsb = 5;
			gtk_list_store_clear(store);
			MAILBOX rcvmb;

			sndmsg.num = 14;
			strcpy(sndmsg.sortkey, "lixingxing");

			getmailbox(sndmsg, client_num, &rcvmb);
			printf("%d\n", rcvmb.mailnum);
			int i;
			for (i = 0; i < rcvmb.mailnum; i++)
			{
				gchar *s1 = "";
				gchar *s2 = rcvmb.title[i];
				gchar *s3 = rcvmb.time[i];
				gint *s4 = rcvmb.no[i];
				gchar *s5 = "n";
				gchar *s6 = "lixingxing";
	
				add_to_list(list, s1,s2,s3,s4,s5,s6);
			}
		}
		else if(strcmp(value,"垃圾箱")==0)
		{	
			M.num = 6;
			lxxlzyqdsdsb = 6;
			gtk_list_store_clear(store);
			MAILBOX rcvmb;

			sndmsg.num = 15;
			strcpy(sndmsg.sortkey, "lixingxing");

			getmailbox(sndmsg, client_num, &rcvmb);
			printf("%d\n", rcvmb.mailnum);
			int i;
			for (i = 0; i < rcvmb.mailnum; i++)
			{
				gchar *s1 = rcvmb.receiver[i];
				gchar *s2 = rcvmb.title[i];
				gchar *s3 = rcvmb.time[i];
				gint *s4 = rcvmb.no[i];
				gchar *s5 = "n";
				gchar *s6 = rcvmb.database_flag[i];
			
	
				add_to_list(list, s1,s2,s3,s4,s5,s6);
			}
		}
		
		//gtk_list_store_clear(store);
		g_free(value);
	}	
}


void Ton_changed(GtkWidget * widget, gpointer label)
{
	GtkTreeIter iter;
	GtkTreeModel *model;
	char *value;
	char *vsender;
	char *vtime;
	int *vID;
	char *vstat;
	char *flag;
	wchar_t *vtitle;
	wchar_t *wtext = "223454353@mm.com";
	
	printf("Ton_changed!!\n");
	
	GtkTextBuffer *buffer_text;
	buffer_text = gtk_text_view_get_buffer (GTK_TEXT_VIEW (main_textview));

	
	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(widget), &model, &iter)) {
		//gtk_tree_model_get(model, &iter, LIST_FIVE, &value, -1);
		gtk_tree_model_get(model, &iter, LIST_TWO, &vsender, -1);
		gtk_tree_model_get(model, &iter, LIST_THREE, &vtitle, -1);
		gtk_tree_model_get(model, &iter, LIST_FOUR, &vtime, -1);
		gtk_tree_model_get(model, &iter, LIST_FIVE, &vID, -1);
		gtk_tree_model_get(model, &iter, LIST_SIX, &vstat, -1);
		gtk_tree_model_get(model, &iter, LIST_SEVEN, &flag, -1);
		strcpy(M.sender,vsender);
		strcpy(M.mtitle,vtitle);
		strcpy(M.mtime,vtime);
		M.database_flag=*flag;

		printf("receiver:%s\n",M.receiver);
		printf("mtitle:%s\n",M.mtitle);
		printf("mtime:%s\n",M.mtime);
		M.no = vID;
		printf("id:%d\n",vID);
		printf("vstat:%s\n",vstat);


		MSG rcvm;
		if ((lxxlzyqdsdsb == 1) || (lxxlzyqdsdsb == 3))
			getmsg(121, M.no, vstat, &rcvm);
		else 
			getmsg(122, M.no, vstat, &rcvm);
		printf("%s\n",rcvm.mtext);
		wtext = &rcvm.mtext;

		strcpy(M.mtext,wtext);

		gtk_text_buffer_set_text((GtkTextBuffer*)buffer_text, wtext, -1);
		//g_free(value);
	}
	MSG weidu;
	weidu.num=21;
	weidu.client_num = client_num;
	bzero(buff,sizeof(buff));
	memcpy(buff,&weidu,sizeof(weidu));
	do_connect();							//connect
	char email_num[10];
	if( send(socket_descriptor, buff, sizeof(weidu), 0)==-1)		//send
	{
		perror("can not send message\n");
		exit(1);
	}
	
	memset(email_num,0,sizeof(email_num));
	if(recv(socket_descriptor, email_num, 10, 0)==-1)		//receive
	{
		perror("can not receive email_num");
	}
	gchar l[20];
	l[0] = '\0';
	strcat(l,"未读邮件: ");
	strcat(l,email_num);
	gtk_label_set_text(main_label,l);
}




void remove_item(GtkWidget * widget, gpointer selection)
{

	GtkListStore *store;

	GtkTreeModel *model;

	GtkTreeIter iter;

	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

	if (gtk_tree_model_get_iter_first(model, &iter) == FALSE)

        return;
	
	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter)) {
	
		do_connect();				//connect

		bzero(buff,sizeof(buff));
		memcpy(buff,&M,sizeof(M));	
	
		int x ;	
		if((x = send(socket_descriptor, buff, sizeof(M), 0))==-1)		//send
    		{
        		perror("can not send message\n");
       		 	exit(1);
  		}
		printf("in the send_send function the client send %d words\n",x);

		
		close(socket_descriptor);				//close

		
		gtk_list_store_remove(store, &iter);
	}
}


void send_button_rec(GtkWidget * widget, gpointer data)
{
	gtk_editable_set_editable( entry_rec,TRUE );
	gtk_editable_set_editable( entry_copy,FALSE );
	gtk_editable_set_editable( entry_secret,FALSE );
 	entry_select = entry_rec;
}

void send_button_copy(GtkWidget * widget, gpointer data)
{
	gtk_editable_set_editable( entry_rec,FALSE );
	gtk_editable_set_editable( entry_copy,TRUE );
	gtk_editable_set_editable( entry_secret,FALSE );
 	entry_select = entry_copy;
}
 
void send_button_secret(GtkWidget * widget, gpointer data)
{
	gtk_editable_set_editable( entry_rec,FALSE );
	gtk_editable_set_editable( entry_copy,FALSE );
	gtk_editable_set_editable( entry_secret,TRUE );
 	entry_select = entry_secret;
}


void send_return(GtkWidget * widget, gpointer selection)
{
	/*GtkTextIter start, end;     
        gtk_text_buffer_get_bounds (GTK_TEXT_BUFFER (buffer), &start, &end);
	MSG MES;
	gchar title_anrry[30],text_anrry[1000];
	gchar *tit = title_anrry;
	gchar *tex = text_anrry;
	tit = (gchar *)gtk_entry_get_text (GTK_ENTRY ( entry_name ));
	tex = gtk_text_buffer_get_text (GTK_TEXT_BUFFER (buffer),&start,&end,TRUE);
	strcpy(MES.mtitle,tit);
	strcpy(MES.mtext,tex);
	MES.num = 3;

	do_connect();				//connect

	bzero(buff,sizeof(buff));
	memcpy(buff,&MES,sizeof(MES));	
	if(send(socket_descriptor, buff, sizeof(MES), 0)==-1)		//send
    	{
        	perror("can not send message\n");
        	exit(1);
  	}
	char flag;
	if(recv(socket_descriptor,&flag,sizeof(flag),0) < 0)		//receive
	{
		perror("the client can not receive the flag from the server!\n");
		exit(1);
	}
	close(socket_descriptor);				//close
	GtkWidget * dialog;
	gchar * message;
	GtkMessageType type = GTK_MESSAGE_INFO;
	if(flag == 'y'||flag == 'Y')
		message = "保存成功";
	else
		message = "保存失败";
	dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL |GTK_DIALOG_DESTROY_WITH_PARENT,type,GTK_BUTTONS_OK,message,NULL);
	gtk_dialog_run(GTK_DIALOG(dialog));	
	gtk_widget_destroy(dialog);
	*/
	gtk_widget_hide_all(window_send);
	gtk_widget_show_all(window_main);
}
