#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <libpq-fe.h>
#include <string.h>
#include "Calendar.h"

void Quit(GtkWidget* W , gpointer data)
{
  gtk_widget_destroy(data) ;
}

void Calendar_Window(GtkWidget* Widget , gpointer p)
{
   GtkWidget* Calendar = NULL ;
   GtkWidget* button = NULL ;
   GtkWidget* Windows = NULL ;
   GtkWidget* vbox = NULL ;
   Windows = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
   Calendar = gtk_calendar_new() ;
   button = gtk_button_new_with_mnemonic("Quitter") ;
   vbox = gtk_vbox_new(0,20) ;
   gtk_box_pack_start(GTK_BOX(vbox), Calendar,0,0,0) ;
   gtk_box_pack_start(GTK_BOX(vbox), button,0,0,0) ;
   gtk_container_add(GTK_CONTAINER(Windows), vbox) ;
   gtk_container_set_border_width(GTK_CONTAINER(Windows), 100) ;
   gtk_window_set_position(GTK_WINDOW(Windows), GTK_WIN_POS_CENTER) ;
   //g_signal_connect(G_OBJECT(Windows), "delete-event", G_CALLBACK(Quit), GTK_WIDGET(Windows));
   g_signal_connect(G_OBJECT(Calendar), "day-selected-double-click", G_CALLBACK(Events), Calendar);
   g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(Quit), Windows);
   gtk_widget_show_all(Windows) ;
   gtk_main();

}

void Events(GtkCalendar* c, gpointer p)
{
   GtkWidget* label = NULL ;
   GtkWidget* label1 = NULL ;
   GtkWidget* button = NULL ;
   GtkWidget* button1 = NULL ;
   GtkWidget* Windows = NULL ;
   GtkWidget* box1 = NULL ;
   GtkWidget* box2 = NULL ;
   GtkWidget* box3 = NULL ;
   GtkWidget* Gbox = NULL ;
   GtkWidget* Gbox1 = NULL ;
   gchar* text = NULL ;
   gchar* text1 = NULL ;
   guint jours;
   guint mois;
   guint annee;
   int i ;
   PGconn     *conn;
   PGresult   *res;
   const char *values[1];
   GtkTextIter iter ;
   GtkTextBuffer* text_buffer = NULL ;

   conn = PQsetdbLogin("localhost", "5432", "", "", "calendrier", "postgres", "Aissatoudia") ;

    /* Vérification de la connexion*/
    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "Connection to database failed: %s",
                PQerrorMessage(conn));

    }
    else
        printf("Connexion etablie\n") ;

   Textarea = gtk_text_view_new() ;
   Textarea1 = gtk_text_view_new() ;
   gtk_calendar_get_date(GTK_CALENDAR(p), &annee, &mois, &jours) ;
   text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Textarea)) ;
   gtk_text_buffer_get_start_iter(text_buffer,&iter) ;
   char* str = (char*)malloc(10*sizeof(char));
   sprintf(str, "%d/%d/%d", jours,mois+1,annee);
   //printf("%s\n",str );
   values[0] = (const char*)str;
   res = PQexecParams(conn, "SELECT * FROM Events WHERE dat = $1", 1, NULL, values,
    NULL, NULL, 0);
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
      printf("ERREUR\n");
   free(str) ;
   int tuple = PQntuples(res);
   printf("%d\n",tuple );
   for(i=0; i<tuple; i++){
      gtk_text_buffer_insert(
      text_buffer, &iter,
      PQgetvalue(res,i,0), -1);
      gtk_text_buffer_insert(
      text_buffer, &iter,
      "\r", -1);
    }
   gtk_text_view_set_editable(GTK_TEXT_VIEW(Textarea), 0) ; 
   Windows = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
   label = gtk_label_new(NULL) ;
   label1 = gtk_label_new(NULL) ;
   gtk_calendar_get_date(GTK_CALENDAR(p), &annee, &mois, &jours) ;
   gtk_widget_set_size_request(Textarea,20,150) ;
   gtk_widget_set_size_request(Textarea1,20,150) ;
   text = g_locale_to_utf8("<i><big><b>Evenements</b></big></i>", -1, NULL, NULL, NULL);
   text1 = g_locale_to_utf8("<i><big><b>Ajouter</b></big></i>", -1, NULL, NULL, NULL);
   gtk_label_set_markup(GTK_LABEL(label), text) ;
   gtk_label_set_markup(GTK_LABEL(label1), text1) ;
   g_free(text) ;
   g_free(text1) ;
   gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER) ;
   gtk_label_set_justify(GTK_LABEL(label1), GTK_JUSTIFY_CENTER) ;
   button = gtk_button_new_with_mnemonic("Enregistrer") ;
   button1 = gtk_button_new_with_mnemonic("Quitter") ;
   box1 = gtk_vbox_new(0,20) ;
   box2 = gtk_vbox_new(0,20) ;
   box3 = gtk_vbox_new(0,20) ;
   Gbox = gtk_box_new(0,20) ;
   Gbox1 = gtk_vbox_new(0,20) ;
   gtk_box_pack_start(GTK_BOX(box1), label,0,0,0) ;
   gtk_box_pack_start(GTK_BOX(box1), Textarea,0,0,0) ;
   gtk_box_pack_start(GTK_BOX(box2), label1,0,0,0) ;
   gtk_box_pack_start(GTK_BOX(box2), Textarea1,0,0,0) ;
   gtk_box_pack_start(GTK_BOX(box3), button,0,0,0) ;
   gtk_box_pack_start(GTK_BOX(box3), button1,0,0,0) ;
   gtk_box_pack_start(GTK_BOX(Gbox), box1,0,0,0) ;
   gtk_box_pack_start(GTK_BOX(Gbox), box2,0,0,0) ;
   gtk_box_pack_start(GTK_BOX(Gbox1), Gbox,0,0,0) ;
   gtk_box_pack_start(GTK_BOX(Gbox1), box3,0,0,0) ;
   gtk_container_add(GTK_CONTAINER(Windows), Gbox1) ;
   gtk_container_set_border_width(GTK_CONTAINER(Windows), 100) ;
   gtk_window_set_position(GTK_WINDOW(Windows), GTK_WIN_POS_CENTER) ;
   g_signal_connect(G_OBJECT(Windows), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
   g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(Enregistrer), p);
   g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(Quit), Windows);
   gtk_widget_show_all(Windows) ;
   gtk_main();
}

void Enregistrer(GtkWidget* w , gpointer p)
{
   guint jours;
   guint mois;
   guint annee;
	 GtkTextIter start, end ;
   PGconn     *conn;
   const char *values[2];
   PGresult   *res;
   GtkTextBuffer* text_buffer = NULL ;
   gtk_calendar_get_date(GTK_CALENDAR(p), &annee, &mois, &jours) ;
	text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Textarea1)) ;
	gtk_text_buffer_get_end_iter(text_buffer,&end) ;
  gtk_text_buffer_get_start_iter(text_buffer,&start) ;
	gchar* buf = gtk_text_buffer_get_text(text_buffer, &start, &end, 0) ;
   char* str = (char*)malloc(10*sizeof(char));
   sprintf(str, "%d/%d/%d", jours,mois+1,annee);
   values[0] = (const char*)buf;
   values[1] = (const char*)str;
    conn = PQsetdbLogin("localhost", "5432", "", "", "calendrier", "postgres", "Aissatoudia") ;

    /* Vérification de la connexion*/
    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "Connection to database failed: %s",
                PQerrorMessage(conn));

    }
    else
        printf("Connexion etablie\n") ;
   res = PQexecParams(conn, "INSERT INTO Events VALUES($1, $2)", 2, NULL, values,
    NULL, NULL, 0);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
      printf("ERREUR D'INSERT\n");
	g_free(buf) ;
   free(str) ;
}
