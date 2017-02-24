#include"head.h"
#include"window.h"
#include"callback.h"
#include"gv.h"
#include<gtk/gtk.h>

GtkWidget * new_welcom_window()
{
	GtkWidget *window;
	char* title="点击进入";
	GtkWidget *box;
	GtkWidget *box_out;

	GtkWidget *image;
	GtkWidget* label;
	GtkWidget* button;
	window=gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect_swapped (G_OBJECT (window), "delete_event",G_CALLBACK (gtk_widget_destroy),window);
	gtk_window_set_title (GTK_WINDOW (window), "欢迎使用么么邮");
	gtk_window_set_position( GTK_WINDOW(window),GTK_WIN_POS_CENTER_ALWAYS );
	box=gtk_vbox_new(FALSE,2);
	image=gtk_image_new_from_file("/home/neuedu/mywork/gtk/workwork/hehe");
	label=gtk_label_new(title);
	//gtk_container_set_border_width(GTK_CONTAINER(box),5);
	gtk_box_pack_start(GTK_BOX(box),image,FALSE,FALSE,3);
   	gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,3);
	button=gtk_button_new();
	gtk_container_add(GTK_CONTAINER(button),box);
	box_out=gtk_hbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),box_out);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(on_button_clicked_welcom),NULL);
	gtk_box_pack_start(GTK_BOX(box_out),button,FALSE,FALSE,5);

	return window;
}

GtkWidget * new_login_window()
{
	GtkWidget *window;

	GtkWidget *table1;

	GtkWidget *button1;
	GtkWidget *button2;
	GtkWidget *button3;

	GtkWidget *label1;
	GtkWidget *label2;


	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect_swapped (G_OBJECT (window), "delete_event",G_CALLBACK (gtk_widget_destroy),window);
	gtk_window_set_title(GTK_WINDOW(window),"登录");
	gtk_window_set_position( GTK_WINDOW(window),GTK_WIN_POS_CENTER_ALWAYS );
	table1 = gtk_table_new (5,2,FALSE);
	entry_login_user = gtk_entry_new_with_max_length(50);
	entry_login_psw = gtk_entry_new_with_max_length(50);
	gtk_entry_set_visibility (GTK_ENTRY (entry_login_psw),0);

	button1 = gtk_button_new_with_label("注册");
	button2 = gtk_button_new_with_label("登陆");
	button3 = gtk_button_new_with_label("修改密码");

	label1 = gtk_label_new("邮箱");
	label2 = gtk_label_new("密码");
	gtk_container_add(GTK_CONTAINER(window),table1);

	gtk_table_attach(GTK_TABLE(table1),label1,0,1,0,1,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(table1),entry_login_user,1,2,0,1,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(table1),label2,0,1,1,2,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(table1),entry_login_psw,1,2,1,2,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach_defaults(GTK_TABLE(table1),button2,0,2,2,3);
	gtk_table_attach_defaults(GTK_TABLE(table1),button1,0,2,3,4);
	gtk_table_attach_defaults(GTK_TABLE(table1),button3,0,2,4,5);
	g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(login_create_User),window);
	g_signal_connect(G_OBJECT(button2),"clicked",G_CALLBACK(login_get_User),window);
	g_signal_connect(G_OBJECT(button3),"clicked",G_CALLBACK(login_change_psw),window);

	return window;
}

GtkWidget * new_change_psw_window()
{
	GtkWidget *window;

	GtkWidget *table1;

	GtkWidget *button1;
	GtkWidget *button2;

	GtkWidget *label1;
	GtkWidget *label2;
	GtkWidget *label3;
	GtkWidget *label4;



	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect_swapped (G_OBJECT (window), "delete_event",G_CALLBACK (gtk_widget_destroy),window);
	gtk_window_set_title(GTK_WINDOW(window),"修改密码");
	gtk_window_set_position( GTK_WINDOW(window),GTK_WIN_POS_CENTER_ALWAYS );
	table1 = gtk_table_new (6,2,FALSE);

	entry_change_psw_user = gtk_entry_new_with_max_length(50);
	entry_change_psw_re = gtk_entry_new_with_max_length(50);
	entry_change_psw_new = gtk_entry_new_with_max_length(50);
	entry_change_psw_new2 = gtk_entry_new_with_max_length(50);

	gtk_entry_set_visibility (GTK_ENTRY (entry_change_psw_re),0);
	gtk_entry_set_visibility (GTK_ENTRY (entry_change_psw_new),0);
	gtk_entry_set_visibility (GTK_ENTRY (entry_change_psw_new2),0);

	button1 = gtk_button_new_with_label("确定");
	button2 = gtk_button_new_with_label("返回");

	label1 = gtk_label_new("用户名");
	label2 = gtk_label_new("原密码");
	label3 = gtk_label_new("新密码");
	label4 = gtk_label_new("确认新密码");

	gtk_container_add(GTK_CONTAINER(window),table1);

	gtk_table_attach(GTK_TABLE(table1),label1,0,1,0,1,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(table1),entry_change_psw_user,1,2,0,1,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(table1),label2,0,1,1,2,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(table1),entry_change_psw_re,1,2,1,2,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(table1),label3,0,1,2,3,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(table1),entry_change_psw_new,1,2,2,3,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(table1),label4,0,1,3,4,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(table1),entry_change_psw_new2,1,2,3,4,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach_defaults(GTK_TABLE(table1),button1,0,2,4,5);
	gtk_table_attach_defaults(GTK_TABLE(table1),button2,0,2,5,6);
	g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(change_psw_ok),window);
	g_signal_connect(G_OBJECT(button2),"clicked",G_CALLBACK(change_psw_return),window);

	return window;
}

GtkWidget * new_register_window()
{

	GtkWidget *window;
	g_print("welcome to the register_pthread_client\n");
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
 	g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect_swapped (G_OBJECT (window), "delete_event",G_CALLBACK (gtk_widget_destroy),window);

	table1 = gtk_table_new (6,4,FALSE);
	frame=gtk_frame_new("欢迎注册 么么邮 免费邮箱"); 
	gtk_window_set_position( GTK_WINDOW(window),GTK_WIN_POS_CENTER_ALWAYS );

	gtk_container_add(GTK_CONTAINER(window),frame);/*将框架构件加入窗体*/

	gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_OUT);

	entry_reg_user = gtk_entry_new();
	entry_reg_psw = gtk_entry_new();
	entry_reg_psw2 = gtk_entry_new();
	entry_reg_tel = gtk_entry_new();

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
	gtk_table_attach(GTK_TABLE(table1),entry_reg_user,1,2,1,2,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);
	gtk_table_attach(GTK_TABLE(table1),label3,2,4,1,2,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);

	gtk_table_attach(GTK_TABLE(table1),label4,0,1,2,3,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);
	gtk_table_attach(GTK_TABLE(table1),entry_reg_psw,1,2,2,3,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);
	gtk_table_attach(GTK_TABLE(table1),label5,2,4,2,3,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);

	gtk_table_attach(GTK_TABLE(table1),label6,0,1,3,4,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);
	gtk_table_attach(GTK_TABLE(table1),entry_reg_psw2,1,2,3,4,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);
	gtk_table_attach(GTK_TABLE(table1),label7,2,4,3,4,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);

	gtk_table_attach(GTK_TABLE(table1),label8,0,1,4,5,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);
	gtk_table_attach(GTK_TABLE(table1),entry_reg_tel,1,2,4,5,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);
	gtk_table_attach(GTK_TABLE(table1),label9,2,4,4,5,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,5);


	gtk_table_attach(GTK_TABLE(table1),button1,0,2,5,6,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(table1),button2,2,4,5,6,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);

	g_signal_connect (G_OBJECT (button2), "clicked",G_CALLBACK (reg_Clean), NULL);
	g_signal_connect (G_OBJECT (button1), "clicked",G_CALLBACK (Reg), NULL);
	gtk_entry_set_visibility (GTK_ENTRY (entry_reg_psw),0);
	gtk_entry_set_visibility (GTK_ENTRY (entry_reg_psw2),0);
	return window;
}

gint settime(gpointer data)
{
	time_t times;
	times=time(NULL);
	gtk_label_set_text(GTK_LABEL((GtkWidget*)data),ctime(&times));
}

GtkWidget * new_main_window()
{


	GtkWidget *window; 

	GtkWidget *box;
	GtkWidget *button;
	GtkWidget *separator;
	GtkWidget *table;

	GtkWidget *entry;
	GtkWidget *entry1;

	GtkWidget *box1;
	GtkWidget *box2;
	GtkWidget *box3;
	GtkWidget *box4;

	GtkWidget *table1;
	GtkWidget *table2;
	GtkWidget *table3;
	GtkWidget *table4;

	GtkWidget *button1;
	GtkWidget *button2;

	GtkWidget *label1;
	GtkWidget *label2;
	
	GtkWidget *frame;
	GtkWidget *view_text;
	GtkWidget *scrolled_window_text,*scrolled_window_select;

	GtkListStore *store;
	GtkTreeSelection *selection;
	GtkCellRenderer *renderer;
	
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL); 
	g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect_swapped (G_OBJECT (window), "delete_event",G_CALLBACK (gtk_widget_destroy),window);
	gtk_window_set_title(GTK_WINDOW(window),"么么邮邮箱，让你邮得么么哒");
	gtk_window_set_position( GTK_WINDOW(window),GTK_WIN_POS_CENTER_ALWAYS );
	gtk_widget_set_size_request (GTK_WIDGET(window),800,600);


	table = gtk_table_new (4,4,FALSE);
	gtk_container_add (GTK_CONTAINER (window), table);

//////////////////////Frame
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);

 	frame = gtk_frame_new (NULL);
	gtk_container_add (GTK_CONTAINER (window), frame);

	gtk_frame_set_label_align (GTK_FRAME (frame), 1.0, 0.0);

	gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_ETCHED_OUT);
  	gtk_table_attach_defaults(GTK_TABLE(table),frame,0,4,2,4);
	gtk_widget_show (frame);
	
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);

 	frame = gtk_frame_new (NULL);
	gtk_container_add (GTK_CONTAINER (window), frame);

	gtk_frame_set_label_align (GTK_FRAME (frame), 1.0, 0.0);
	gtk_table_attach_defaults(GTK_TABLE(table),frame,0,4,3,4);
	gtk_widget_show (frame);

	gtk_container_set_border_width (GTK_CONTAINER (window), 10);

 	frame = gtk_frame_new (NULL);
	gtk_container_add (GTK_CONTAINER (window), frame);

	gtk_frame_set_label_align (GTK_FRAME (frame), 1.0, 0.0);
	gtk_table_attach_defaults(GTK_TABLE(table),frame,0,1,2,4);
	gtk_widget_show (frame);

///////////////////Manu
	label1 = gtk_label_new("Menu");
	gtk_table_attach(GTK_TABLE(table),label1,0,1,2,3,GTK_FILL,GTK_FILL,0,5);
	label2 = gtk_label_new("weidu");
	gint s =g_timeout_add(1000,settime,label2);
	gtk_table_attach(GTK_TABLE(table),label2,3,4,1,2,GTK_FILL,GTK_FILL,0,5);
	main_label = gtk_label_new("weijieyoujian:(3)");
	gtk_table_attach(GTK_TABLE(table),main_label,2,3,1,2,GTK_FILL,GTK_FILL,0,5);

/////////////////////Sort
	table1 = gtk_table_new (1,3,FALSE);
	gtk_table_attach(GTK_TABLE(table),table1,2,4,2,3,(GtkAttachOptions)(0),(GtkAttachOptions)(0),0,5);
	label1 = gtk_label_new("搜索");
	gtk_table_attach(GTK_TABLE(table1),label1,0,1,0,1,GTK_FILL,GTK_EXPAND,0,5);
	entry1 = gtk_entry_new_with_max_length(50);
	gtk_table_attach(GTK_TABLE(table1),entry1,1,2,0,1,GTK_EXPAND,GTK_FILL,0,5);
	button = gtk_button_new_with_label("搜索");
	g_signal_connect (G_OBJECT (button), "clicked",G_CALLBACK(callback_sort), entry1);///////jia
	gtk_table_attach(GTK_TABLE(table1),button,2,3,0,1,GTK_FILL,GTK_FILL,0,5);
/////////////////////////////button
	box = gtk_hbox_new (FALSE, 0);

	gtk_table_attach(GTK_TABLE(table),box,0,2,1,2,GTK_FILL,GTK_FILL,0,5);

	button = gtk_button_new_with_label ("新建");  
	g_signal_connect (G_OBJECT (button), "clicked",G_CALLBACK (callback_xinjian), "button 1");
	gtk_box_pack_start (GTK_BOX(box), button, FALSE, FALSE, 0);
	gtk_widget_show (button);
	
	separator = gtk_vseparator_new ();
        gtk_box_pack_start (GTK_BOX (box), separator, FALSE, TRUE, 5);
        gtk_widget_show (separator);

	button = gtk_button_new_with_label ("发送");
	g_signal_connect (G_OBJECT (button), "clicked",G_CALLBACK(callback_fasong), "button 2");
	gtk_box_pack_start(GTK_BOX (box), button, FALSE, FALSE, 0);
	gtk_widget_show (button);
	
	button = gtk_button_new_with_label ("接收");
	g_signal_connect (G_OBJECT (button), "clicked",G_CALLBACK(callback_jieshou), "button 2");
	gtk_box_pack_start(GTK_BOX (box), button, FALSE, FALSE, 0);
	gtk_widget_show (button);

	separator = gtk_vseparator_new ();
        gtk_box_pack_start (GTK_BOX (box), separator, FALSE, TRUE, 5);
        gtk_widget_show (separator);

	button = gtk_button_new_with_label ("回复");
	g_signal_connect (G_OBJECT (button), "clicked",G_CALLBACK(callback_huifu), "button 2");
	gtk_box_pack_start(GTK_BOX (box), button, FALSE, FALSE, 0);
	gtk_widget_show (button);

	button = gtk_button_new_with_label ("转发");
	g_signal_connect (G_OBJECT (button), "clicked",G_CALLBACK(callback_zhuanfa), "button 2");
	gtk_box_pack_start(GTK_BOX (box), button, FALSE, FALSE, 0);
	gtk_widget_show (button);

	separator = gtk_vseparator_new ();
        gtk_box_pack_start (GTK_BOX (box), separator, FALSE, TRUE, 5);
        gtk_widget_show (separator);

	//gtk_table_attach(GTK_TABLE(table),box,1,3,3,4,GTK_FILL|GTK_EXPAND,GTK_FILL|GTK_EXPAND,10,5);

//////////////////////////Tree view right
	box1 = gtk_vbox_new (FALSE, 0);
	gtk_table_attach(GTK_TABLE(table),box1,1,4,3,4,GTK_FILL|GTK_EXPAND,GTK_FILL|GTK_EXPAND,10,5);
	scrolled_window_select = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window_select),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_box_pack_start (GTK_BOX(box1), scrolled_window_select, FALSE, FALSE, 10);
	gtk_widget_set_size_request (GTK_WIDGET(scrolled_window_select),500,200);
	
	list = gtk_tree_view_new();
	
	GtkTreeViewColumn *column;
	GtkTreeViewColumn *column1;
	GtkTreeViewColumn *column2;
	GtkTreeViewColumn *column3;
	GtkTreeViewColumn *column4;
	GtkTreeViewColumn *column5;
	GtkTreeViewColumn *column6;

	//renderer = gtk_cell_renderer_toggle_new();
	//column = gtk_tree_view_column_new_with_attributes("选择",renderer,"actived",LIST_ONE,NULL);
	

	renderer = gtk_cell_renderer_text_new();

	column1 = gtk_tree_view_column_new_with_attributes ("姓名",renderer,"text", LIST_TWO,NULL);
	
	column2 = gtk_tree_view_column_new_with_attributes ("主题",renderer,"text", LIST_THREE,NULL);

	column3 = gtk_tree_view_column_new_with_attributes ("日期",renderer,"text", LIST_FOUR,NULL);
	
	column4 = gtk_tree_view_column_new_with_attributes ("ID",renderer,"text", LIST_FIVE,NULL);

	column5 = gtk_tree_view_column_new_with_attributes ("stat",renderer,"text", LIST_SIX,NULL);
	
	column6 = gtk_tree_view_column_new_with_attributes ("database_flag",renderer,"text", LIST_SEVEN,NULL);
	
	 

   	//gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column1);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column2);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column3);
	//gtk_tree_view_append_column(GTK_TREE_VIEW(list), column4);
	//gtk_tree_view_append_column(GTK_TREE_VIEW(list), column6);


	store = gtk_list_store_new(R_COLUMNS, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING);////////xiugai

	gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));
	

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));
	g_signal_connect(selection, "changed", G_CALLBACK(Ton_changed), label1);
	
	button = gtk_button_new_with_label ("删除");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(remove_item), selection);
	gtk_box_pack_start(GTK_BOX (box), button, FALSE, FALSE, 0);
	gtk_widget_show (button);

	button = gtk_button_new_with_label ("恢复");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(recover_item), selection);
	gtk_box_pack_start(GTK_BOX (box), button, FALSE, FALSE, 0);
	gtk_widget_show (button);

	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window_select),list);
/////////////////////////
////////////////////Tool for text
	
	clipboard=gtk_clipboard_get(GDK_NONE);
	
//////////////////////////////////////Tree_view_left
	GtkTreeSelection *selection1;
	GtkWidget* view1;
	GtkTreeViewColumn *col;

	GtkCellRenderer *renderer_left;

	view1=gtk_tree_view_new();

	col=gtk_tree_view_column_new();

	gtk_tree_view_column_set_title(col,"MeMeEmail");

	gtk_tree_view_append_column(GTK_TREE_VIEW(view1),col);

	renderer_left=gtk_cell_renderer_text_new();

	gtk_tree_view_column_pack_start(col,renderer_left,TRUE);

	gtk_tree_view_column_add_attribute(col,renderer_left,"text",COLUMN);
	

	GtkTreeStore* treestore;
	GtkTreeIter toplevel,child,child2;
	

	treestore=gtk_tree_store_new(N_COLUMNS,G_TYPE_STRING);

	gtk_tree_store_append(treestore,&toplevel,NULL);
	gtk_tree_store_set(treestore,&toplevel,COLUMN,"Menu",-1);

	gtk_tree_store_append(treestore,&child,&toplevel);
	gtk_tree_store_set(treestore,&child,COLUMN,"收件箱",-1);

	gtk_tree_store_append(treestore,&child2,&child);
	gtk_tree_store_set(treestore,&child2,COLUMN,"已读",-1);

	gtk_tree_store_append(treestore,&child2,&child);
	gtk_tree_store_set(treestore,&child2,COLUMN,"未读",-1);

	gtk_tree_store_append(treestore,&child,&toplevel);
	gtk_tree_store_set(treestore,&child,COLUMN,"已发邮件",-1);

	gtk_tree_store_append(treestore,&child,&toplevel);
	gtk_tree_store_set(treestore,&child,COLUMN,"草稿",-1);

	gtk_tree_store_append(treestore,&child,&toplevel);
	gtk_tree_store_set(treestore,&child,COLUMN,"垃圾箱",-1);


	gtk_tree_view_set_model(GTK_TREE_VIEW(view1), GTK_TREE_MODEL(treestore));

	//gtk_tree_view_set_model(GTK_TREE_VIEW(view1),model);
	gtk_tree_view_expand_all(view1);
	selection1 = gtk_tree_view_get_selection(GTK_TREE_VIEW(view1));
	g_signal_connect(selection1, "changed", G_CALLBACK(on_changed),NULL);
	gtk_table_attach(GTK_TABLE(table),view1,0,1,3,4,GTK_FILL,GTK_FILL,10,15);
//////////////////////////////////text
	GtkTextBuffer *buffer_text;
	PangoFontDescription *font;
	
	main_textview = gtk_text_view_new ();
	
	buffer_text=gtk_text_view_get_buffer(GTK_TEXT_VIEW(main_textview));
	
	font = pango_font_description_from_string ("Monospace Bold 10");
	gtk_widget_modify_font (main_textview, font);
	
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(main_textview),GTK_WRAP_CHAR);
	gtk_text_view_set_indent (GTK_TEXT_VIEW(main_textview), 25);
	gtk_text_view_set_justification (GTK_TEXT_VIEW (main_textview), GTK_JUSTIFY_LEFT);
	gtk_text_view_set_editable (GTK_TEXT_VIEW (main_textview), TRUE);
	gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (main_textview), TRUE);
	gtk_text_view_set_pixels_above_lines (GTK_TEXT_VIEW (main_textview), 5);
	gtk_text_view_set_pixels_below_lines (GTK_TEXT_VIEW (main_textview), 5);
        gtk_text_view_set_pixels_inside_wrap (GTK_TEXT_VIEW (main_textview), 5);
	gtk_text_view_set_left_margin (GTK_TEXT_VIEW (main_textview), 10);
	gtk_text_view_set_right_margin (GTK_TEXT_VIEW (main_textview), 10);
	buffer_text = gtk_text_view_get_buffer (GTK_TEXT_VIEW (main_textview));

	gchar *cc = "Welecome@meme.com!!\n";
	gtk_text_buffer_set_text (buffer_text, cc, -1);
	scrolled_window_text = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window_text),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start (GTK_BOX(box1), scrolled_window_text,TRUE,TRUE, 10);
	
	gtk_container_add (GTK_CONTAINER (scrolled_window_text), main_textview);
	gtk_widget_set_size_request (GTK_WIDGET(scrolled_window_text),500,220);
//////////////////////////////////////////////
	/*GtkWidget *window; 

	GtkWidget *box;
	GtkWidget *button;
	GtkWidget *separator;
	GtkWidget *table;

	GtkWidget *entry;
	GtkWidget *entry1;

	GtkWidget *box1;
	GtkWidget *box2;
	GtkWidget *box3;
	GtkWidget *box4;

	GtkWidget *table1;
	GtkWidget *table2;
	GtkWidget *table3;
	GtkWidget *table4;

	GtkWidget *button1;
	GtkWidget *button2;

	GtkWidget *label1;
	GtkWidget *label2;
	GtkWidget *frame;
	GtkWidget *view_text;
	GtkWidget *scrolled_window_text,*scrolled_window_select;

	GtkListStore *store;
	GtkTreeSelection *selection;

	GtkCellRenderer *renderer;

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL); 
	gtk_window_set_title(GTK_WINDOW(window),"么么邮邮箱，让你邮得么么哒");
	gtk_widget_set_size_request (GTK_WIDGET(window),800,600);
	g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect_swapped (G_OBJECT (window), "delete_event",G_CALLBACK (gtk_widget_destroy), window);

	table = gtk_table_new (4,3,FALSE);
	gtk_container_add (GTK_CONTAINER (window), table);

//////////////////////Frame
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);

 	frame = gtk_frame_new (NULL);
	gtk_container_add (GTK_CONTAINER (window), frame);

	gtk_frame_set_label_align (GTK_FRAME (frame), 1.0, 0.0);

	gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_ETCHED_OUT);
  	gtk_table_attach_defaults(GTK_TABLE(table),frame,0,3,2,4);
	gtk_widget_show (frame);
	
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);

 	frame = gtk_frame_new (NULL);
	gtk_container_add (GTK_CONTAINER (window), frame);

	gtk_frame_set_label_align (GTK_FRAME (frame), 1.0, 0.0);
	gtk_table_attach_defaults(GTK_TABLE(table),frame,0,3,3,4);
	gtk_widget_show (frame);

	gtk_container_set_border_width (GTK_CONTAINER (window), 10);

 	frame = gtk_frame_new (NULL);
	gtk_container_add (GTK_CONTAINER (window), frame);

	gtk_frame_set_label_align (GTK_FRAME (frame), 1.0, 0.0);
	gtk_table_attach_defaults(GTK_TABLE(table),frame,0,1,2,4);
	gtk_widget_show (frame);

///////////////////Manu
	label1 = gtk_label_new("Manu");
	gtk_table_attach(GTK_TABLE(table),label1,0,1,2,3,GTK_FILL,GTK_FILL,0,5);

/////////////////////Sort
	table1 = gtk_table_new (1,3,FALSE);
	gtk_table_attach(GTK_TABLE(table),table1,1,3,2,3,(GtkAttachOptions)(0),(GtkAttachOptions)(0),0,5);
	label1 = gtk_label_new("Sort");
	gtk_table_attach(GTK_TABLE(table1),label1,0,1,0,1,GTK_FILL,GTK_EXPAND,0,5);
	entry1 = gtk_entry_new_with_max_length(50);
	gtk_table_attach(GTK_TABLE(table1),entry1,1,2,0,1,GTK_EXPAND,GTK_FILL,0,5);
	button = gtk_button_new_with_label("Sort");
	g_signal_connect (G_OBJECT (button), "clicked",G_CALLBACK(callback_sort), entry1);///////jia
	gtk_table_attach(GTK_TABLE(table1),button,2,3,0,1,GTK_FILL,GTK_FILL,0,5);
/////////////////////////////button
	box = gtk_hbox_new (FALSE, 0);

	gtk_table_attach(GTK_TABLE(table),box,0,1,1,2,GTK_FILL,GTK_FILL,0,5);

	button = gtk_button_new_with_label ("新建");  
	g_signal_connect (G_OBJECT (button), "clicked",G_CALLBACK (callback_xinjian), "button 1");
	gtk_box_pack_start (GTK_BOX(box), button, FALSE, FALSE, 0);
	gtk_widget_show (button);
	
	separator = gtk_vseparator_new ();
        gtk_box_pack_start (GTK_BOX (box), separator, FALSE, TRUE, 5);
        gtk_widget_show (separator);

	button = gtk_button_new_with_label ("发送");
	g_signal_connect (G_OBJECT (button), "clicked",G_CALLBACK(callback_fasong), "button 2");
	gtk_box_pack_start(GTK_BOX (box), button, FALSE, FALSE, 0);
	gtk_widget_show (button);
	
	button = gtk_button_new_with_label ("接收");
	g_signal_connect (G_OBJECT (button), "clicked",G_CALLBACK(callback_jieshou), "button 2");
	gtk_box_pack_start(GTK_BOX (box), button, FALSE, FALSE, 0);
	gtk_widget_show (button);

	separator = gtk_vseparator_new ();
        gtk_box_pack_start (GTK_BOX (box), separator, FALSE, TRUE, 5);
        gtk_widget_show (separator);

	button = gtk_button_new_with_label ("回复");
	g_signal_connect (G_OBJECT (button), "clicked",G_CALLBACK(callback_huifu), "button 2");
	gtk_box_pack_start(GTK_BOX (box), button, FALSE, FALSE, 0);
	gtk_widget_show (button);

	button = gtk_button_new_with_label ("转发");
	g_signal_connect (G_OBJECT (button), "clicked",G_CALLBACK(callback_zhuanfa), "button 2");
	gtk_box_pack_start(GTK_BOX (box), button, FALSE, FALSE, 0);
	gtk_widget_show (button);

	separator = gtk_vseparator_new ();
        gtk_box_pack_start (GTK_BOX (box), separator, FALSE, TRUE, 5);
        gtk_widget_show (separator);

	gtk_table_attach(GTK_TABLE(table),box,1,3,3,4,GTK_FILL|GTK_EXPAND,GTK_FILL|GTK_EXPAND,10,5);

//////////////////////////Tree view right
	box1 = gtk_vbox_new (FALSE, 0);
	gtk_table_attach(GTK_TABLE(table),box1,1,3,3,4,GTK_FILL|GTK_EXPAND,GTK_FILL|GTK_EXPAND,10,5);
	scrolled_window_select = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window_select),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_box_pack_start (GTK_BOX(box1), scrolled_window_select, FALSE, FALSE, 10);
	gtk_widget_set_size_request (GTK_WIDGET(scrolled_window_select),500,200);
	
	list = gtk_tree_view_new();
	
	GtkTreeViewColumn *column;
	GtkTreeViewColumn *column1;
	GtkTreeViewColumn *column2;
	GtkTreeViewColumn *column3;
	GtkTreeViewColumn *column4;

	//renderer = gtk_cell_renderer_toggle_new();
	//column = gtk_tree_view_column_new_with_attributes("选择",renderer,"actived",LIST_ONE,NULL);

	renderer = gtk_cell_renderer_text_new();

	column1 = gtk_tree_view_column_new_with_attributes ("发件人/收件人",renderer,"text", LIST_TWO,NULL);
	column2 = gtk_tree_view_column_new_with_attributes ("主题",renderer,"text", LIST_THREE,NULL);

	column3 = gtk_tree_view_column_new_with_attributes ("日期",renderer,"text", LIST_FOUR,NULL);
	
	column4 = gtk_tree_view_column_new_with_attributes ("ID",renderer,"text", LIST_FIVE,NULL);
	
	 

   	//gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column1);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column2);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column3);
	//gtk_tree_view_append_column(GTK_TREE_VIEW(list), column4);


	store = gtk_list_store_new(R_COLUMNS, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT);////////xiugai

	gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));
	
	

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));
	g_signal_connect(selection, "changed", G_CALLBACK(Ton_changed), label1);
	
	button = gtk_button_new_with_label ("  删除  ");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(remove_item), selection);
	gtk_box_pack_start(GTK_BOX (box), button, FALSE, FALSE, 0);
	gtk_widget_show (button);

	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window_select),list);
/////////////////////////
////////////////////Tool for text
	main_textview = gtk_text_view_new ();
	box2=gtk_vbox_new(FALSE,0);
	GtkTextBuffer *buffer_text;
	buffer_text=gtk_text_view_get_buffer(GTK_TEXT_VIEW(main_textview));
	gtk_widget_set_size_request (GTK_WIDGET(box2),200,30);
	gtk_box_pack_start (GTK_BOX(box1), box2, FALSE, FALSE, 0);
//////////////////////////////////////Tree_view_left
	GtkTreeSelection *selection1;
	GtkWidget* view1;
	GtkTreeViewColumn *col;

	GtkCellRenderer *renderer_left;

	view1=gtk_tree_view_new();

	col=gtk_tree_view_column_new();

	gtk_tree_view_column_set_title(col,"MeMeEmail");

	gtk_tree_view_append_column(GTK_TREE_VIEW(view1),col);

	renderer_left=gtk_cell_renderer_text_new();

	gtk_tree_view_column_pack_start(col,renderer_left,TRUE);

	gtk_tree_view_column_add_attribute(col,renderer_left,"text",COLUMN);
	

	GtkTreeStore* treestore;
	GtkTreeIter toplevel,child;
	

	treestore=gtk_tree_store_new(N_COLUMNS,G_TYPE_STRING);

	gtk_tree_store_append(treestore,&toplevel,NULL);
	gtk_tree_store_set(treestore,&toplevel,COLUMN,"Menu",-1);

	gtk_tree_store_append(treestore,&child,&toplevel);
	gtk_tree_store_set(treestore,&child,COLUMN,"收件箱",-1);

	gtk_tree_store_append(treestore,&child,&toplevel);
	gtk_tree_store_set(treestore,&child,COLUMN,"已发邮件",-1);

	gtk_tree_store_append(treestore,&child,&toplevel);
	gtk_tree_store_set(treestore,&child,COLUMN,"草稿",-1);

	gtk_tree_store_append(treestore,&child,&toplevel);
	gtk_tree_store_set(treestore,&child,COLUMN,"垃圾箱",-1);


	gtk_tree_view_set_model(GTK_TREE_VIEW(view1), GTK_TREE_MODEL(treestore));

	//gtk_tree_view_set_model(GTK_TREE_VIEW(view1),model);

	selection1 = gtk_tree_view_get_selection(GTK_TREE_VIEW(view1));
	g_signal_connect(selection1, "changed", G_CALLBACK(on_changed),NULL);
	gtk_table_attach(GTK_TABLE(table),view1,0,1,3,4,GTK_FILL,GTK_FILL,10,15);
//////////////////////////////////text
	
	PangoFontDescription *font;
	

	
	font = pango_font_description_from_string ("Monospace Bold 10");
	gtk_widget_modify_font (main_textview, font);
	
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(main_textview),GTK_WRAP_CHAR);
	gtk_text_view_set_indent (GTK_TEXT_VIEW(main_textview), 25);
	gtk_text_view_set_justification (GTK_TEXT_VIEW (main_textview), GTK_JUSTIFY_LEFT);
	gtk_text_view_set_editable (GTK_TEXT_VIEW (main_textview), TRUE);
	gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (main_textview), TRUE);
	gtk_text_view_set_pixels_above_lines (GTK_TEXT_VIEW (main_textview), 5);
	gtk_text_view_set_pixels_below_lines (GTK_TEXT_VIEW (main_textview), 5);
        gtk_text_view_set_pixels_inside_wrap (GTK_TEXT_VIEW (main_textview), 5);
	gtk_text_view_set_left_margin (GTK_TEXT_VIEW (main_textview), 10);
	gtk_text_view_set_right_margin (GTK_TEXT_VIEW (main_textview), 10);
	buffer_text = gtk_text_view_get_buffer (GTK_TEXT_VIEW (main_textview));

	gchar *cc = "WELECOME@meme.com\n";
	gtk_text_buffer_set_text (buffer_text, cc, -1);
	scrolled_window_text = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window_text),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start (GTK_BOX(box1), scrolled_window_text,TRUE,TRUE, 10);
	
	gtk_container_add (GTK_CONTAINER (scrolled_window_text), main_textview);
	gtk_widget_set_size_request (GTK_WIDGET(scrolled_window_text),500,220);
//////////////////////////////////////////////


	
	*/
	return window;
}

GtkWidget * new_send_window()
{
	
	GtkWidget *window;
	GtkWidget *table;
	GtkWidget *button,*button_attach,*button_color,*button_font,*button_return;
	GtkWidget* toolbar;
	GtkWidget *label1,*label2,*label3,*label4;
	GtkWidget *button_rec,*button_copy,*button_secret;	
	GtkWidget *scrolled_window_text,*scrolled_window_select;
	GtkWidget *filew;
	//窗口编辑
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request (GTK_WIDGET (window), 800, 600);
	gtk_window_set_title (GTK_WINDOW (window), "编写邮件");
	gtk_window_set_position( GTK_WINDOW(window),GTK_WIN_POS_CENTER_ALWAYS );
	//销毁窗口
	g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect_swapped (G_OBJECT (window), "delete_event",G_CALLBACK (gtk_widget_destroy), window);		
	//table creat
	table = gtk_table_new (10, 10, FALSE);
	gtk_container_add (GTK_CONTAINER (window), table);
	//label1 creat
	label1 = gtk_label_new ("收件人:");
	gtk_table_attach (GTK_TABLE (table), label1, 0, 1, 0, 1,GTK_FILL,GTK_FILL,0,5);
	//entry_rec creat
	entry_rec = gtk_entry_new ();
	gtk_entry_set_max_length (GTK_ENTRY (entry_rec), 500);
	gtk_table_attach (GTK_TABLE (table), entry_rec, 1, 8, 0, 1,GTK_FILL|GTK_EXPAND,GTK_FILL,10,5);
	//button_rec creat
	button_rec = gtk_button_new_with_label ("编辑收件人");
	gtk_table_attach (GTK_TABLE (table), button_rec, 8, 9, 0, 1,GTK_FILL|GTK_EXPAND,GTK_FILL,10,10);
	g_signal_connect (G_OBJECT (button_rec), "clicked",G_CALLBACK ( send_button_rec ), NULL );
	//label3 creat
	label3 = gtk_label_new ("抄 送：");
 	gtk_table_attach (GTK_TABLE (table), label3, 0, 1, 1, 2,GTK_FILL,GTK_FILL,0,5);
	//entry_copy
	entry_copy = gtk_entry_new ();
	gtk_entry_set_max_length (GTK_ENTRY (entry_copy), 500);
	gtk_table_attach (GTK_TABLE (table), entry_copy, 1, 8, 1, 2,GTK_FILL|GTK_EXPAND,GTK_FILL,10,5);
	//button_copy
	button_copy = gtk_button_new_with_label ("编辑抄送人");
	gtk_table_attach (GTK_TABLE (table), button_copy, 8, 9, 1, 2,GTK_FILL|GTK_EXPAND,GTK_FILL,10,10);
	g_signal_connect (G_OBJECT (button_copy), "clicked",G_CALLBACK ( send_button_copy ), NULL );
	//label4 creat
	label4 = gtk_label_new ("密 送：");
 	gtk_table_attach (GTK_TABLE (table), label4, 0, 1, 2, 3,GTK_FILL,GTK_FILL,0,5);
	//entry_secret
	entry_secret = gtk_entry_new ();
	gtk_entry_set_max_length (GTK_ENTRY (entry_secret), 500);
	gtk_table_attach (GTK_TABLE (table), entry_secret, 1, 8, 2, 3,GTK_FILL|GTK_EXPAND,GTK_FILL,10,5);
	//button_secret
	button_secret = gtk_button_new_with_label ("编辑密送人");
	gtk_table_attach (GTK_TABLE (table), button_secret, 8, 9, 2, 3,GTK_FILL|GTK_EXPAND,GTK_FILL,10,10);
	g_signal_connect (G_OBJECT (button_secret), "clicked",G_CALLBACK ( send_button_secret ), NULL );
	//label2 creat
	label2 = gtk_label_new ("主 题:");	
	gtk_table_attach (GTK_TABLE (table), label2, 0, 1, 3, 4,GTK_FILL,GTK_FILL,0,5);
	//entry_name creat
	entry_name = gtk_entry_new ();
	gtk_entry_set_max_length (GTK_ENTRY (entry_name), 50);
	gtk_entry_set_text (GTK_ENTRY (entry_name), "请键入邮件主题");
	gtk_table_attach (GTK_TABLE (table), entry_name, 1, 9, 3, 4,GTK_FILL|GTK_EXPAND,GTK_FILL,10,5);
	//scroll_text
   	scrolled_window_text = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window_text),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_table_attach (GTK_TABLE (table), scrolled_window_text, 0, 9, 5, 10,GTK_FILL|GTK_EXPAND,GTK_FILL|GTK_EXPAND,10,5);
	//view_text creat
	view_text = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scrolled_window_text), view_text);
	//tool bar
	buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(view_text));
	clipboard=gtk_clipboard_get(GDK_NONE);
	toolbar=gtk_toolbar_new();
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_NEW,"新建一个文件","新建",GTK_SIGNAL_FUNC(send_creat_new_file),  NULL  ,-1);//waiting
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_SAVE,"保存当前文件","保存",GTK_SIGNAL_FUNC(send_save_mail),NULL,-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_CUT,"剪切","剪切",GTK_SIGNAL_FUNC(on_edit_cut_activate),view_text,-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_COPY,"复制","复制",GTK_SIGNAL_FUNC(on_edit_copy_activate),view_text,-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(toolbar),GTK_STOCK_PASTE,"粘贴","粘贴",GTK_SIGNAL_FUNC(on_edit_paste_activate),view_text,-1);
	gtk_toolbar_set_style(GTK_TOOLBAR(toolbar),GTK_TOOLBAR_ICONS);
	gtk_table_attach (GTK_TABLE (table), toolbar, 0, 5, 4, 5,GTK_FILL,GTK_SHRINK,0,5);
	//scroll_select
	scrolled_window_select = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window_select),GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
	gtk_table_attach (GTK_TABLE (table), scrolled_window_select, 9, 10, 5, 10,GTK_FILL|GTK_EXPAND,GTK_FILL|GTK_EXPAND,10,5);
	//check button
	GtkWidget * mail[100];
	int linkman_num,flag;
	linkman_num = send_CHECK_REF(scrolled_window_select,mail);
		//check connect
	for(flag=0;flag<linkman_num;flag++)
	{
		g_signal_connect (G_OBJECT (mail[flag]), "toggled",G_CALLBACK (send_toggle_button_callback), entry_rec);
	}
	//button_attach
	button_attach = gtk_button_new_with_label ("添加附件");
	gtk_table_attach (GTK_TABLE (table), button_attach, 7, 8, 4, 5,GTK_FILL|GTK_EXPAND,GTK_FILL,10,10);
	g_signal_connect (G_OBJECT (button_attach), "clicked",G_CALLBACK ( send_attach_button ), NULL);
	//button_color
	button_color = gtk_button_new_with_label ("编辑颜色");
	gtk_table_attach (GTK_TABLE (table), button_color, 5, 6, 4, 5,GTK_FILL|GTK_EXPAND,GTK_FILL,10,10);
	g_signal_connect (G_OBJECT (button_color), "clicked",G_CALLBACK ( send_area_event ), view_text );
	//button_font
	button_font = gtk_button_new_with_label ("编辑字体");
	gtk_table_attach (GTK_TABLE (table), button_font, 6, 7, 4, 5,GTK_FILL|GTK_EXPAND,GTK_FILL,10,10);
	g_signal_connect(G_OBJECT(button_font),"clicked",G_CALLBACK(send_changefont),view_text);
	//button_return 
	button_return = gtk_button_new_with_label ("返回");
	gtk_table_attach (GTK_TABLE (table), button_return, 9, 10, 1, 2,GTK_FILL|GTK_EXPAND,GTK_FILL,10,5);
	g_signal_connect(G_OBJECT(button_return),"clicked",G_CALLBACK(send_return),NULL);
	//send button
	button = gtk_button_new_with_label ("发 送");
	gtk_table_attach (GTK_TABLE (table), button, 9, 10, 0, 1,GTK_FILL|GTK_EXPAND,GTK_FILL,10,5);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK( send_send_button ),NULL);
	gtk_editable_set_editable( entry_rec,TRUE );
	gtk_editable_set_editable( entry_copy,FALSE );
	gtk_editable_set_editable( entry_secret,FALSE );
	entry_select = entry_rec;
	//show 
	return window;
}
