#include "succeed.h"
//extern char boxkind[20];
int i = 0;
gboolean set(gpointer data){
	if(i < 20)
	{
		i++;
		g_print("i = %d\n",i);
		return TRUE;
	}
	else {
		g_print("quit");
		gtk_widget_destroy((GtkWidget *)data);
		//insert_list_text(boxkind);
		g_print("quit");
		return FALSE;
	}
}

void create_succeed_window( int data)
{
	GtkWidget* window;
	GtkWidget* label;

	window = gtk_window_new(GTK_WINDOW_POPUP);
	gtk_window_set_title(GTK_WINDOW(window), "SUCCEED");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window), 20);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_widget_destroy), NULL);

	if (data == 1){	
		i = 0;
		label = gtk_label_new("send succeed!");	
		gtk_container_add(GTK_CONTAINER(window), label);
		g_timeout_add(100,set,window);
	}

	gtk_widget_show_all(window);

	gtk_widget_show(window);
}
