#include"mail_win.h"
#include "color.h"
#include "text_view.h"
#include "font.h"
#include "jjy_text_view.h"
#include "gettext.h"
extern int total;
extern char name[20];
char *_number;
#include "login.h"

extern GtkWidget* entry_usrname;
extern int count_unread;
//extern char boxkind[20] = {0};
typedef struct e_rec
{
	char topic[50];
	char kind[10];//
	char sender[20];
	char reciever[200];
	char time[20];
	char textnum[20];
	char info[50];//numid
}E_rec;

extern E_rec pioe[200]; //part information of email 
extern char bigbuf[4096];
extern char text_add[2048];
extern char add_name[200];
GtkListStore* list_store;
GtkTreeIter list_iter;
GtkTreeModel* model;
GtkTreeModel* tree_model;
GtkWidget* text;
GtkTreeSelection* list_select;
GdkColor text_color;
GtkWidget *entry_srch;
int max_mail;
extern GtkWidget *view;
extern GtkTextBuffer *text_buffer;
int list_last = -1;
int isMulChoice = 0;
GtkWidget *entry_from;
GtkWidget *entry_to;
GtkWidget *entry_subject;
GtkWidget *entry_attachment;

enum ListCols
{
	LIST_CHECKED,
	LIST_READ,
	LIST_NUM,
	LIST_NAME,
	LIST_MESSAGE,
	LIST_DATE,
	LIST_COLOR,
	LIST_CNT
};

enum TreeCols
{
	TREE_NAME,
	TREE_CNT
};

void test_button_clicked(GtkWidget *button,gpointer data)
{	
	g_print("yes is clicked\n");
}

static GtkItemFactoryEntry menu_items[] = { 
	{ "/_File",         NULL,         NULL, 0, "<Branch>" },
	{ "/File/_New",     "<control>N", new_mail, 0, NULL },
	{ "/File/sep1",     NULL,         NULL, 0, "<Separator>" },
	{ "/File/Quit",     "<control>Q", gtk_main_quit, 0, NULL },
	{ "/_Edit",      NULL,         NULL, 0, "<Branch>" },
	{ "/Edit/Color",  "F1",         area_event, 0, NULL },
	{ "/Edit/Font",  "F2",        on_font_show, 0, NULL },
	{ "/_Help",         NULL,         NULL, 0, "<Branch>" },
	{ "/_Help/About",   "F3",         create_about, 0, NULL },
};

char* entry_topic;
char* topic;
char* res;
void on_button_search(GtkWidget *button,gpointer data)
{
	int flag;
	GtkTreeIter iter;
	gboolean valid;

	printf("on_button_search\n");

	entry_topic = (char *)gtk_entry_get_text(GTK_ENTRY(entry_srch));
	valid = gtk_tree_model_get_iter_first (model, &iter);

	if(!(strcmp(entry_topic, "") == 0))
	{
		while(valid)
		{
			printf("while\n");
			flag = 0;
			res = NULL;

			gtk_tree_model_get (model, &iter, LIST_MESSAGE, &topic, -1);		
			res = strstr(topic,entry_topic);

			if(res != NULL)		
				flag = 1;
			else flag = 0;

			if(flag == 1)
			{
				gtk_list_store_set(GTK_LIST_STORE(list_store), &iter, LIST_COLOR, "blue", -1);
				valid = gtk_tree_model_iter_next (model, &iter);
			}
			else
			{
				gtk_list_store_set(GTK_LIST_STORE(list_store), &iter, LIST_COLOR, "black", -1);
				valid = gtk_tree_model_iter_next (model, &iter);
			}
		}
	}
}

void get_main_menu(GtkWidget *window, GtkWidget **menubar)
{
	GtkItemFactory *item_factory;
	GtkAccelGroup *accel_group;

	gint nmenu_items = sizeof (menu_items) / sizeof (menu_items[0]);
	accel_group = gtk_accel_group_new ();
	item_factory = gtk_item_factory_new (GTK_TYPE_MENU_BAR, "<main>", accel_group);
	gtk_item_factory_create_items (item_factory, nmenu_items, menu_items, NULL);
	gtk_window_add_accel_group (GTK_WINDOW (window), accel_group);

	if (menubar)  
		*menubar = gtk_item_factory_get_widget (item_factory, "<main>");
}

void select_deleted(GtkWidget* button,gpointer data)
{
	isMulChoice = 1;
	toggle_button_callback(NULL, NULL);
}

void on_button_ok(GtkWidget* button,gpointer data)
{
	isMulChoice = 0;
	g_print("delete start\n");
	GtkTreeIter iter;
	gboolean valid;
	
	valid = gtk_tree_model_get_iter_first (model, &iter);
	
	gint row_count = 1;

	while(valid)
	{
		char *num;
		char *str_data1;
		char *str_data2;
		char *str_data3;
     		gboolean   int_data;

		gtk_tree_model_get (model, &iter, 
			LIST_CHECKED, &int_data,
			LIST_NUM, &num,
			LIST_NAME,&str_data1,
			LIST_MESSAGE,&str_data2,
			LIST_DATE, &str_data3,-1);
		
		if (int_data == 1 && row_count != max_mail)
		{
			g_print("row = %d\n",row_count);
			g_print("max_mail = %d\n",max_mail);
			g_print ("Row %d: (%d,%s, %s, %s, %s)\n", row_count, int_data, num, str_data1, str_data2, str_data3);
			
			if((int)data == 1)//undel
			{
				g_print("num is %d\n",(int)*num - 48);
				char task[10]="retn";
				changemail(pioe[atoi(num)-1].info ,task,pioe[atoi(num)-1].kind);
				gtk_list_store_remove (GTK_LIST_STORE(list_store), &iter);
				gtk_text_buffer_set_text((GtkTextBuffer*)text_buffer, "", 0);
				insert_text((GtkTextBuffer *)text_buffer, -1);
				max_mail--;
				break;
			}
			else//del
			{
				char task[10]="dele";
				changemail(pioe[atoi(num)-1].info ,task,pioe[atoi(num)-1].kind);			

				gtk_list_store_remove (GTK_LIST_STORE(list_store), &iter);
                                /*char reorder[10]={0};
                                if(strcmp(pioe[atoi(num)-1].kind,"recr")==0||strcmp(pioe[atoi(num)-1].kind,"recu")==0) 
                                strcpy(reorder,"recv");
                                if(strcmp(pioe[atoi(num)-1].kind,"send")==0) 
                                strcpy(reorder,"send");
                                if(strcmp(pioe[atoi(num)-1].kind,"draf")==0) 
                                strcpy(reorder,"draf");
                                if(strcmp(pioe[atoi(num)-1].kind,"trad")==0||strcmp(pioe[atoi(num)-1].kind,"trau")==0||strcmp(pioe[atoi(num)-1].kind,"tras")==0||
                              strcmp(pioe[atoi(num)-1].kind,"trar")==0) 
				strcpy(reorder,"tras");
				hostpage(reorder);*/
				gtk_text_buffer_set_text((GtkTextBuffer*)text_buffer, "", 0);

				insert_text((GtkTextBuffer *)text_buffer, -1);
				max_mail--;
				break;
			}			
			g_free (num);
      			g_free (str_data1);
			g_free (str_data2);
			g_free (str_data3);
			
			
		}
		else if (int_data == 1 && row_count == max_mail)
		{
			g_print("row = %d\n",row_count); 
			g_print("max_mail = %d\n",max_mail);
			g_print ("Row %d: (%d,%s, %s, %s, %s)\n", row_count, int_data, num, str_data1, str_data2, str_data3);

			printf("name=%s\nnum=%s\n",name,num);
			
			if((int)data == 1)//undel
			{
				g_print("num is %d\n",(int)*num - 48);
				char task[10]="retn";
				changemail(pioe[atoi(num)-1].info ,task,pioe[atoi(num)-1].kind);
				gtk_list_store_remove (GTK_LIST_STORE(list_store), &iter);
				gtk_text_buffer_set_text((GtkTextBuffer*)text_buffer, "", 0);
				insert_text((GtkTextBuffer *)text_buffer, -1);
				max_mail--;
				break;


			}
			else
			{
				char task[10]="dele";
				changemail(pioe[atoi(num)-1].info ,task,pioe[atoi(num)-1].kind);				

				gtk_list_store_remove (GTK_LIST_STORE(list_store), &iter);
				gtk_text_buffer_set_text((GtkTextBuffer*)text_buffer, "", 0);
				insert_text((GtkTextBuffer *)text_buffer, -1);
				max_mail--;
				break;
			}
			g_free (num);
      			g_free (str_data1);
			g_free (str_data2);
			g_free (str_data3);                        			
			
		}
		else
		{
			row_count ++;
			valid = gtk_tree_model_iter_next (model, &iter);
		}
	}
}


void on_button_select (GtkWidget *button,gpointer data)
{
	GtkTreeIter iter;
	gboolean valid;
	
	valid = gtk_tree_model_get_iter_first (model, &iter);
	
	gint row_count = 1;

	while(valid)
	{
		g_print("valid is %d\n",valid);
		gchar *str_data1;
		gchar *str_data2;
		gchar *str_data3;
     		gboolean   int_data;

		gtk_tree_model_get (model, &iter, 
		LIST_CHECKED, &int_data,
		LIST_NAME,&str_data1,
		LIST_MESSAGE,&str_data2,
		LIST_DATE, &str_data3,-1);

		g_print("row = %d\n",row_count);
		g_print("max_mail = %d\n",max_mail);
		g_print ("Row %d: (%d,%s, %s, %s)\n", row_count, int_data, str_data1, str_data2, str_data3);

		g_free (str_data1);
		g_free (str_data2);
		g_free (str_data3);	

		row_count ++;
		max_mail = max_mail > row_count ? max_mail : row_count ;
		
		if((int)data == 1)
			gtk_list_store_set (GTK_LIST_STORE(list_store), &iter, 0, 1, -1);
		else if((int)data == 2)
			gtk_list_store_set (GTK_LIST_STORE(list_store), &iter, 0, 0, -1);

		valid = gtk_tree_model_iter_next (model, &iter);
	}	
	g_print("select all\n");	
	max_mail --;
}

void insert_text(GtkTextBuffer* buffer, int num)
{   
	GtkTextIter iter;
	gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0); 
   
	if(num < 0)
	{
		gtk_text_buffer_insert(buffer, &iter, "", -1);
		gtk_entry_set_text(GTK_ENTRY(entry_from) ,"");
		gtk_entry_set_text(GTK_ENTRY(entry_to) ,"");
		gtk_entry_set_text(GTK_ENTRY(entry_subject) ,"");
		gtk_entry_set_text(GTK_ENTRY(entry_attachment) ,"");
	}
	else
	{
        //printf("hehehehe\n");
	
        int text_id;
        text_id=num-49;
	 
	gettext(pioe[text_id].textnum); 
       //get text font,color   
	char prit[4096] = {0};
        int i=0,j=0;
        char text_style[50]={0};
        char getred[15]={0};
        char getgreen[15]={0};
	char getblue[15]={0};
	char * from=(char*)malloc(50);//database
	char * to=(char*)malloc(50);;//database
	char * subject=(char*)malloc(50);;//database
        for(i=0;i<strlen(bigbuf);i++)
        { 
          if(bigbuf[i]!=';')
             text_style[i]=bigbuf[i];
          else
          {text_style[i]='\0';j=i;break;}
        }
      printf("text=%s\n",text_style);
	int k=0;
        
        for(i=j+1;i<strlen(bigbuf);i++)
        { 
	 
          if(bigbuf[i]!=';')
	  {
             getred[k++]=bigbuf[i];
	  }
          else
          {
		getred[k]='\0';j=i;break;}
        }
        k=0;
        for(i=j+1;i<strlen(bigbuf);i++)
        { 
          if(bigbuf[i]!=';')
             getgreen[k++]=bigbuf[i];
          else
          {getgreen[k]='\0';j=i;break;}
        }
        k=0;
	for(i=j+1;i<strlen(bigbuf);i++)
        { 
          if(bigbuf[i]!='#')
             getblue[k++]=bigbuf[i];
          else
          {getblue[k]='\0';j=i;break;}
        }
        text_color.red =atoi(getred);
	text_color.green =atoi(getgreen);
	text_color.blue =atoi(getblue);
        char outtext[5000]={0};
        strcpy(outtext,&bigbuf[j+1]);
	printf("color : %d %d %d\n", text_color.red, text_color.green, text_color.blue);
       
    //chao song,mi song
        int p,q;
        char showname[100]={0};
         
        for(p=0;p<strlen(pioe[text_id].reciever);p++) 
        {
         if(pioe[text_id].reciever[p]=='#')
          break;
        }
        p++;
        char tempname[50]={0};
        q=0;
        int onlyflag=0;
        for(;p<strlen(pioe[text_id].reciever);p++) 
        {
         if(pioe[text_id].reciever[p]==';')
         {
          tempname[q]='\0';
          if(strcmp(name,tempname)==0)
          {
          q=0;
          for(p=0;p<strlen(pioe[text_id].reciever);p++)
          {
          if(pioe[text_id].reciever[p]=='#')continue;
          showname[q++]=pioe[text_id].reciever[p];
          }
          onlyflag=1;
          break;
          }
         else q=0;
         }
         else tempname[q++]=pioe[text_id].reciever[p];        
        }
       printf("text_id=%d\n",text_id);
        q=0;   
        printf("pioe=%s\n",pioe[text_id].reciever);
        if(onlyflag==0)
        {
       for(p=0;pioe[text_id].reciever[p]!='#';p++)
        {
        showname[q++]=pioe[text_id].reciever[p];
        }
        showname[q]='\0';
        }
        strcpy(from,pioe[text_id].sender);
        strcpy(to,showname);
	strcpy(subject,pioe[text_id].topic);
	sprintf(prit, "%s",outtext);
	
	
		gtk_text_buffer_insert(buffer, &iter, prit, -1);
		gtk_widget_modify_text(view, GTK_STATE_NORMAL, &text_color); 
		gtk_entry_set_text(GTK_ENTRY(entry_from) ,from);
		gtk_entry_set_text(GTK_ENTRY(entry_to) ,to);
		gtk_entry_set_text(GTK_ENTRY(entry_subject) ,subject);
		gtk_entry_set_text(GTK_ENTRY(entry_attachment) ,add_name);
		printf("add_name: %s\n", add_name);
		char *text_font = (char*)malloc(50);
       
	       	strcpy(text_font,text_style);
		PangoFontDescription* chosen_font;	
		chosen_font = pango_font_description_from_string(text_font);
		gtk_widget_modify_font (view,chosen_font);
		free(text_font);
	free(from);
	free(subject);
        free(to);
	int length=strlen(text_add);
	printf("lenth = %d\n",length);
	if (length != 0)
	{
	FILE * fp = fopen(add_name,"wb+");
    	if(NULL == fp )
	{
        	printf("File:\t%s Can Not Open To Write\n", add_name);
        	exit(1);
	}
	int write_length;
	write_length = fwrite(text_add,sizeof(char),length,fp);
	printf("write_length = %d",write_length);
	printf("%s\n",text_add);
        if (write_length<length)
        {
            	printf("File:\t%s Write Failed\n", add_name);
        }    
	fflush(fp);
 	close(fp);
	}
	}
	
}
void toggle_button_callback (GtkWidget* widget,  gpointer data)
{
	GtkTreeIter iter;
	gboolean valid;
      
	valid = gtk_tree_model_get_iter_first (model, &iter);
	gint row_count = 0;
	while(valid)
	{
		char* read;
		gchar *str_data1;
		gchar *str_data2;
		gchar *str_data3;
     		gboolean   int_data;
		
		row_count ++;
		max_mail = max_mail > row_count ? max_mail : row_count ;
	      
		if (gtk_tree_selection_iter_is_selected(GTK_TREE_SELECTION(list_select), &iter))
		{
			gtk_tree_model_get (model, &iter, 
				LIST_CHECKED, &int_data,
				LIST_READ, &read,
				LIST_NUM,&_number,
				LIST_NAME,&str_data1,
				LIST_MESSAGE,&str_data2,
				LIST_DATE, &str_data3,
                        	  -1);

			g_print ("Row %d: (%d, %s, %s, %s, %s, %s)\n", row_count, int_data, read, _number, str_data1, str_data2, str_data3);

			int flag;
			if(int_data == 1)
				flag = 0;
			else
				flag = 1;

			gtk_list_store_set (GTK_LIST_STORE(list_store), &iter, 0, flag, LIST_READ,GTK_STOCK_APPLY ,-1);
			gtk_text_buffer_set_text((GtkTextBuffer*)text_buffer, "", 0);

			insert_text((GtkTextBuffer *)text_buffer, (int)*_number);
                        char task[10]="read";
                        if(strcmp(pioe[atoi(_number)-1].kind,"recu")==0)
			changemail(pioe[atoi(_number)-1].info ,task,pioe[atoi(_number)-1].kind);

      			g_free (str_data1);
			g_free (str_data2);
			g_free (str_data3);

			if(!isMulChoice)
			{
				if(list_last != -1)
				{
					gtk_tree_model_get_iter_first (model, &iter);
					int j;
					for(j=1; j< list_last; j++)
						gtk_tree_model_iter_next (model, &iter);
					gtk_list_store_set (GTK_LIST_STORE(list_store), &iter, 0, 0, -1);
				}
				list_last = row_count;
		
				break;
			}
		}
		valid = gtk_tree_model_iter_next (model, &iter);
          
	}
	
}




void insert_list_text(char* str)
{
	//database
	int i;
        char task[10]={0};
        if(strcmp(str,"Receive Box")==0) 
        strcpy(task,"recv");
        if(strcmp(str,"Send Box")==0) 
        strcpy(task,"send");
        if(strcmp(str,"Draft Box")==0) 
        strcpy(task,"draf");
        if(strcmp(str,"Trash Box")==0) 
        strcpy(task,"tras");
	
	//
	//strcpy(boxkind, task);
        hostpage(task);
        printf("shifouyidu=%s\n",pioe[0].kind);
	for(i=0; i<total; i++)
	{
		char *num=(char *)malloc(20);
		char *read=(char*)malloc(10);
		char  *name=(char *)malloc(20);
		char  *subject=(char *)malloc(50);
		char  *data=(char *)malloc(20);
		sprintf(num,"%d",i+1);
		strcpy(read,pioe[i].kind);//
		strcpy(name,pioe[i].sender);//
		strcpy (subject,pioe[i].topic);//
		strcpy(data,pioe[i].time);//

		num = g_strdup_printf("%s", num); 
		name = g_strdup_printf("%s", name);
		subject = g_strdup_printf("%s", subject);
		data = g_strdup_printf("%s", data);

		gtk_list_store_append(GTK_LIST_STORE(list_store), &list_iter);

		if((strcmp(read, "recu")==0))
			gtk_list_store_set(GTK_LIST_STORE(list_store), &list_iter, 
						LIST_CHECKED, FALSE,
						LIST_READ,GTK_STOCK_ABOUT,
						LIST_NUM, num,
						LIST_NAME, name, 
						LIST_MESSAGE, subject, 
						LIST_DATE, data, 
						-1);
		else
			gtk_list_store_set(GTK_LIST_STORE(list_store), &list_iter, 
						LIST_CHECKED, FALSE,
						LIST_READ,GTK_STOCK_APPLY,
						LIST_NUM, num,
						LIST_NAME, name, 
						LIST_MESSAGE, subject, 
						LIST_DATE, data, 
						-1);
		free(num);
		free(name);
		free(subject);
		free(data);
                free(read);
	}
}

GtkWidget* create_list()
{
	GtkWidget* scrolled_window;
	GtkWidget* tree_view;
	GtkCellRenderer* cell;
	GtkTreeViewColumn* column;

	//scrolled window
	scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_size_request (GTK_WIDGET (scrolled_window), 700, 300);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	
	//list store & tree view
	list_store = gtk_list_store_new(LIST_CNT, G_TYPE_BOOLEAN, G_TYPE_STRING,  G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	tree_view = gtk_tree_view_new();
	
	//pack
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW (scrolled_window), tree_view);
	gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(list_store));
	g_object_unref(list_store);

	insert_list_text("Receive Box");

	//set column
	cell = gtk_cell_renderer_toggle_new ();
	column = gtk_tree_view_column_new_with_attributes ("", cell, "active", LIST_CHECKED, NULL);	
	gtk_tree_view_append_column (GTK_TREE_VIEW (tree_view), GTK_TREE_VIEW_COLUMN (column));
	
	cell = gtk_cell_renderer_pixbuf_new ();
	column = gtk_tree_view_column_new_with_attributes ("", cell, "stock-id", LIST_READ, NULL);	
	gtk_tree_view_append_column (GTK_TREE_VIEW (tree_view), GTK_TREE_VIEW_COLUMN (column));

	cell = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes ("Num", cell, "text", LIST_NUM, NULL);
	gtk_tree_view_column_add_attribute(column, cell, "foreground", LIST_COLOR);
	gtk_tree_view_append_column (GTK_TREE_VIEW (tree_view), GTK_TREE_VIEW_COLUMN (column));
	column = gtk_tree_view_column_new_with_attributes ("Name", cell, "text", LIST_NAME, NULL);
	gtk_tree_view_column_add_attribute(column, cell, "foreground", LIST_COLOR);
	gtk_tree_view_append_column (GTK_TREE_VIEW (tree_view), GTK_TREE_VIEW_COLUMN (column));
	column = gtk_tree_view_column_new_with_attributes ("Subject", cell, "text", LIST_MESSAGE, NULL);
	gtk_tree_view_column_add_attribute(column, cell, "foreground", LIST_COLOR);
	gtk_tree_view_append_column (GTK_TREE_VIEW (tree_view), GTK_TREE_VIEW_COLUMN (column));
	column = gtk_tree_view_column_new_with_attributes ("Date", cell, "text", LIST_DATE, NULL);
	gtk_tree_view_column_add_attribute(column, cell, "foreground", LIST_COLOR);
  	gtk_tree_view_append_column (GTK_TREE_VIEW (tree_view), GTK_TREE_VIEW_COLUMN (column));

	//set selectpioe[num].sender
	list_select = gtk_tree_view_get_selection(GTK_TREE_VIEW (tree_view));
	gtk_tree_selection_set_mode(GTK_TREE_SELECTION(list_select), GTK_SELECTION_SINGLE);
	model=gtk_tree_view_get_model(GTK_TREE_VIEW(tree_view));
	g_signal_connect(G_OBJECT(list_select), "changed", G_CALLBACK(toggle_button_callback), NULL);

	return scrolled_window;
}

void on_tree_clicked(GtkTreeSelection* select, gpointer data)
{
	GtkTreeIter iter;  
//	GtkTreeModel* model;  
	char* str;  
  
	if(gtk_tree_selection_get_selected(select, &tree_model, &iter))  
	{  
		gtk_tree_model_get(tree_model, &iter, TREE_NAME, &str, -1);  
		printf("%s\n", str);
		gtk_list_store_clear(list_store);
		insert_list_text(str);
		gtk_text_buffer_set_text((GtkTextBuffer*)text_buffer, "", 0);
		insert_text((GtkTextBuffer *)text_buffer, -1);
		g_free(str);  
	}  
}

GtkWidget* create_tree()
{
	GtkWidget *scrolled_window;
	GtkWidget* tree;
	GtkTreeIter iter;
	GtkTreeStore* tree_store;
	GtkCellRenderer* renderer;
	GtkTreeViewColumn* column;
	GtkTreeSelection* select;

	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_widget_set_size_request (GTK_WIDGET (scrolled_window), 300, 500);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	tree_store = gtk_tree_store_new(TREE_CNT, G_TYPE_STRING);

	gtk_tree_store_append(GTK_TREE_STORE(tree_store), &iter, NULL);
	gtk_tree_store_set(GTK_TREE_STORE(tree_store), &iter, TREE_NAME, "Receive Box", -1);

	gtk_tree_store_append(GTK_TREE_STORE(tree_store), &iter, NULL);
	gtk_tree_store_set(GTK_TREE_STORE(tree_store), &iter, TREE_NAME, "Send Box", -1);

	gtk_tree_store_append(GTK_TREE_STORE(tree_store), &iter, NULL);
	gtk_tree_store_set(GTK_TREE_STORE(tree_store), &iter, TREE_NAME, "Draft Box", -1);

	gtk_tree_store_append(GTK_TREE_STORE(tree_store), &iter, NULL);
	gtk_tree_store_set(GTK_TREE_STORE(tree_store), &iter, TREE_NAME, "Trash Box", -1);

	tree = gtk_tree_view_new_with_model(GTK_TREE_MODEL(tree_store));

	g_object_unref(tree_store);
	
	renderer = gtk_cell_renderer_text_new();
	column  = gtk_tree_view_column_new_with_attributes("", renderer, "text", TREE_NAME, NULL);
	gtk_tree_view_append_column((GtkTreeView *)tree, (GtkTreeViewColumn *)column);
	gtk_tree_view_expand_all((GtkTreeView *)tree);

	gtk_container_add(GTK_CONTAINER(scrolled_window), GTK_WIDGET(tree));
	
	//set select
	select = gtk_tree_view_get_selection(GTK_TREE_VIEW (tree));
	gtk_tree_selection_set_mode(GTK_TREE_SELECTION(select), GTK_SELECTION_SINGLE);
	tree_model=gtk_tree_view_get_model(GTK_TREE_VIEW(tree));
	g_signal_connect(G_OBJECT(select), "changed", G_CALLBACK(on_tree_clicked), NULL);

	gtk_widget_show_all (scrolled_window);

	return scrolled_window;
}

GtkWidget* create_toolbar()
{
	GtkWidget* toolbar;
	toolbar = gtk_toolbar_new();
	gtk_toolbar_set_icon_size(GTK_TOOLBAR(toolbar),GTK_ICON_SIZE_DND);
	
	GtkWidget *iconw = gtk_image_new_from_file ("./res/1.png"); 
	GtkWidget *button_new = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), "new",  "新建", "Private", iconw,  GTK_SIGNAL_FUNC (new_mail),  (gpointer)1);
  	gtk_toolbar_append_space (GTK_TOOLBAR (toolbar)); 

	iconw = gtk_image_new_from_file ("./res/2.png"); 
	GtkWidget * button_reply = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), "reply",  "回复", "Private", iconw,  GTK_SIGNAL_FUNC (new_mail),  (gpointer)2);
  	gtk_toolbar_append_space (GTK_TOOLBAR (toolbar)); 

	iconw = gtk_image_new_from_file ("./res/3.png"); 
	GtkWidget * button_resend = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), "resend",  "转发", "Private", iconw,  GTK_SIGNAL_FUNC (new_mail),  (gpointer)3);
  	gtk_toolbar_append_space (GTK_TOOLBAR (toolbar)); 

	iconw = gtk_image_new_from_file ("./res/4.png"); 
	GtkWidget * button_sel_del = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), "sel_del",  "选择删除", "Private", iconw,  GTK_SIGNAL_FUNC (select_deleted),  model);
  	gtk_toolbar_append_space (GTK_TOOLBAR (toolbar)); 

	iconw = gtk_image_new_from_file ("./res/5.png"); 
	GtkWidget * button_undel = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), "undel",  "撤销删除", "Private", iconw,  GTK_SIGNAL_FUNC (on_button_ok),  (gpointer)1);
  	gtk_toolbar_append_space (GTK_TOOLBAR (toolbar)); 

/*	iconw = gtk_image_new_from_file ("./res/7.png"); 
	GtkWidget * button_sel_all = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), "sel_all",  "全选", "Private", iconw,  GTK_SIGNAL_FUNC (on_button_select),  (gpointer)1);
 	gtk_toolbar_append_space (GTK_TOOLBAR (toolbar)); */ 

	iconw = gtk_image_new_from_file ("./res/6.png"); 
	GtkWidget * button_sel_none = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), "sel_none",  "反选", "Private", iconw,  GTK_SIGNAL_FUNC (on_button_select),  (gpointer)2);
  	gtk_toolbar_append_space (GTK_TOOLBAR (toolbar)); 

	iconw = gtk_image_new_from_file ("./res/8.png"); 
	GtkWidget * button_del = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), "delete",  "确定删除", "Private", iconw, GTK_SIGNAL_FUNC(on_button_ok),  (gpointer)2);
  	gtk_toolbar_append_space (GTK_TOOLBAR (toolbar)); 
	gtk_toolbar_set_style(GTK_TOOLBAR(toolbar),GTK_TOOLBAR_ICONS);

	return toolbar;
}
GtkWidget* create_button(char *filename,char *title)
{
	GtkWidget* box;
	GtkWidget* image;
	GtkWidget* button;
	image=gtk_image_new_from_file(filename);   //11.JPG 和12.JPG这两张图片是放在button文件夹里的

	box=gtk_vbox_new(FALSE,0);
//	gtk_container_set_border_width(GTK_CONTAINER(box),5);

	gtk_box_pack_start(GTK_BOX(box),image,FALSE,FALSE,0);

	gtk_widget_show(image);

	button=gtk_button_new();
	gtk_container_add(GTK_CONTAINER(button),box);
	gtk_widget_show(box);
	return button;
}
void create_mail_window(gpointer* data)
{
	GtkWidget* window;
	GtkWidget* box_main;
	GtkWidget* box_toolbar;
	GtkWidget* toolbar;
	GtkWidget* box_parent;
	GtkWidget* box_from;
	GtkWidget* box_text;
	GtkWidget* box_attachment;
	GtkWidget* box1;
	GtkWidget* box2;
	GtkWidget* entry_search;
	GtkWidget* button_search;
	GtkWidget* button_reply;
	GtkWidget* button_resend;
	GtkWidget* button_del;
	GtkWidget* vpaned;
	GtkWidget* tree;
	GtkWidget* list;
	GtkWidget* iconw;
	GtkWidget* menubar;
	GtkWidget* label;
	GtkWidget *menubox;
	//set window
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Mail");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_set_name (window, "first_win");

	text_color.red = 0;
	text_color.green = 0;
	text_color.blue = 0;

	//set box_main
	box_main = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (window), box_main);

	//set menu
  	menubox = gtk_hbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (box_main), menubox);

	get_main_menu (window, &menubar);
	gtk_container_add (GTK_CONTAINER (menubox), menubar);

	GtkWidget *usrlabel1 = gtk_label_new(",welcome to use the wanted mail!!!        ");	
	PangoFontDescription *font_desc = pango_font_description_from_string("Sans");
	pango_font_description_set_size (font_desc, 15 * PANGO_SCALE);
	gtk_widget_modify_font (usrlabel1, font_desc);
	gtk_box_pack_end(GTK_BOX(menubox),usrlabel1,FALSE,TRUE,0);
	
	const gchar *usrname = gtk_entry_get_text(GTK_ENTRY(entry_usrname));
	GtkWidget * usrlabel = gtk_label_new(usrname);
	gtk_label_set_selectable (GTK_LABEL(usrlabel), TRUE);
	gtk_widget_modify_font (usrlabel, font_desc);
	gtk_box_pack_end(GTK_BOX(menubox),usrlabel,FALSE,TRUE,0);

	//set toolbar
  	box_toolbar = gtk_hbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (box_main), box_toolbar);

	toolbar = create_toolbar();
	gtk_box_pack_start(GTK_BOX(box_toolbar),toolbar,FALSE,TRUE,0);

	GtkWidget *label_srch = gtk_label_new("Subject : ");
	entry_srch = gtk_entry_new();
	GtkWidget *button = create_button("./res/9.png","search");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_button_search), NULL);
	g_signal_connect(G_OBJECT(entry_srch), "activate", G_CALLBACK(on_button_search), NULL);

	gtk_box_pack_end(GTK_BOX(box_toolbar),button,FALSE,TRUE,0);
	gtk_box_pack_end(GTK_BOX(box_toolbar),entry_srch,FALSE,TRUE,0);
	gtk_box_pack_end(GTK_BOX(box_toolbar),label_srch,FALSE,TRUE,0);

	box_from = gtk_hbox_new (FALSE, 0);

	//set from to subject entry
	
	label = gtk_label_new("From : ");
	entry_from = gtk_entry_new();
//	gtk_entry_set_text(entry_from ,from);
	gtk_editable_set_editable(GTK_EDITABLE(entry_from),GTK_TOGGLE_BUTTON(window)->active);
	gtk_box_pack_start (GTK_BOX (box_from), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (box_from), entry_from, TRUE, TRUE, 0);

	label = gtk_label_new("To : ");
	entry_to = gtk_entry_new();
//	gtk_entry_set_text(entry_to,to);
	gtk_editable_set_editable(GTK_EDITABLE(entry_from),GTK_TOGGLE_BUTTON(window)->active);
	gtk_box_pack_start (GTK_BOX (box_from), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (box_from), entry_to, TRUE, TRUE, 0);

	label = gtk_label_new("Subject : ");
	entry_subject = gtk_entry_new();
//	gtk_entry_set_text(entry_subject ,subject);
	gtk_editable_set_editable(GTK_EDITABLE(entry_from),GTK_TOGGLE_BUTTON(window)->active);
	gtk_box_pack_start (GTK_BOX (box_from), label, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (box_from), entry_subject, TRUE, TRUE, 0);

	box_attachment = gtk_hbox_new(FALSE, 0);

	label = gtk_label_new("Attachment : ");
	entry_attachment = gtk_entry_new();
	gtk_editable_set_editable(GTK_EDITABLE(entry_attachment),GTK_TOGGLE_BUTTON(window)->active);
	gtk_box_pack_start (GTK_BOX (box_attachment), label, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (box_attachment), entry_attachment, FALSE, TRUE, 0);

	box_text = gtk_vbox_new(FALSE, 10);
	gtk_box_pack_start (GTK_BOX (box_text), box_from, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (box_text), box_attachment, FALSE, TRUE, 0);

	//set box parent
	box_parent = gtk_hbox_new (FALSE, 10);
	gtk_box_pack_start (GTK_BOX (box_main), box_parent, TRUE, TRUE, 0);

	box1 = gtk_vbox_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX (box_parent), box1, FALSE, TRUE, 0);

	box2 = gtk_vbox_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX (box_parent), box2, TRUE, TRUE, 0);

	//set tree
	tree = create_tree();
	gtk_box_pack_start (GTK_BOX (box1), tree, TRUE, TRUE, 0);	

	//set list
	vpaned = gtk_vpaned_new();
	gtk_box_pack_start (GTK_BOX (box2), vpaned, TRUE, TRUE, 0);

	list = create_list();
	gtk_paned_add1(GTK_PANED(vpaned), list);

	//set text view
	text = jjy_create_text(700, 240);
	gtk_box_pack_start (GTK_BOX (box_text), text, TRUE, TRUE, 0);
	gtk_paned_add2(GTK_PANED(vpaned), box_text);

	//show mail window
	gtk_widget_show_all(window);
	if (count_unread > 0)
	create_error_window( 8);
	//destroy log in window
	gtk_widget_destroy((GtkWidget*)data);

	gtk_main();
}


