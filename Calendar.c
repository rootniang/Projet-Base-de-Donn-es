#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <libpq-fe.h>
#include "Calendar.h"


void Calendar_Window(GtkWidget* Widget , gpointer p)
{
   GtkWidget* Calendar = NULL ;
   //GtkWidget* button = NULL ;
   GtkWidget* Windows = NULL ;
   GtkWidget* vbox = NULL ;
   Windows = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
   Calendar = gtk_calendar_new() ;
   vbox = gtk_vbox_new(0,20) ;
   gtk_box_pack_start(GTK_BOX(vbox), Calendar,0,0,0) ;
   gtk_container_add(GTK_CONTAINER(Windows), vbox) ;
   gtk_container_set_border_width(GTK_CONTAINER(Windows), 100) ;
   gtk_window_set_position(GTK_WINDOW(Windows), GTK_WIN_POS_CENTER) ;
   g_signal_connect(G_OBJECT(Windows), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
   g_signal_connect(G_OBJECT(Calendar), "day-selected-double-click", G_CALLBACK(Events), NULL);
   //g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(Terminer), &i);
   gtk_widget_show_all(Windows) ;
   gtk_main();

}

void Events(GtkCalendar* c, gpointer p)
{
   GtkWidget* label = NULL ;
   GtkWidget* button = NULL ;
   GtkWidget* Textarea = NULL ;
   GtkWidget* Windows = NULL ;
   GtkWidget* vbox = NULL ;
   gchar* text = NULL ;

   Windows = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
   label = gtk_label_new(NULL) ;
   Textarea = gtk_text_view_new() ;
   gtk_widget_set_size_request(Textarea,20,150) ;
   text = g_locale_to_utf8("<i><big><b>Evenements</b></big></i>", -1, NULL, NULL, NULL);
   gtk_label_set_markup(GTK_LABEL(label), text) ;
   g_free(text) ;
   gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER) ;
   button = gtk_button_new_with_mnemonic("Enregistrer") ;
   vbox = gtk_vbox_new(0,20) ;
   gtk_box_pack_start(GTK_BOX(vbox), label,0,0,0) ;
   gtk_box_pack_start(GTK_BOX(vbox), Textarea,0,0,0) ;
   gtk_box_pack_start(GTK_BOX(vbox), button,0,0,0) ;
   gtk_container_add(GTK_CONTAINER(Windows), vbox) ;
   gtk_container_set_border_width(GTK_CONTAINER(Windows), 100) ;
   gtk_window_set_position(GTK_WINDOW(Windows), GTK_WIN_POS_CENTER) ;
   g_signal_connect(G_OBJECT(Windows), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
   g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(Enregistrer), Textarea);
   //g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(Terminer), &i);
   gtk_widget_show_all(Windows) ;
   gtk_main();
}

void Enregistrer(GtkWidget* w , gpointer p)
{
	GtkTextBuffer* text_buffer = NULL ;
	GtkTextIter start, end ;
	text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(p)) ;
	gtk_text_buffer_get_start_iter(text_buffer,&start) ;
	gtk_text_buffer_get_end_iter(text_buffer,&end) ;
	gchar* buf = gtk_text_buffer_get_text(text_buffer,&start,&end, 0) ;
	printf("%s\n", buf) ;
	g_free(buf) ;
}
