#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <libpq-fe.h>
#include "Calendar.h"

static void
exit_nicely(PGconn *conn)
{
    PQfinish(conn);
    exit(1);
}

int main(int argc, char **argv)
{
  gtk_init(&argc, &argv) ;
  PGconn     *conn ;
  GtkWidget* MainWindow = NULL ;
  GtkWidget* label = NULL ;
  GtkWidget* button1 = NULL ;
  GtkWidget* button2 = NULL ;
  GtkWidget* vbox = NULL ;
  gchar* text = NULL ;

    //Connexion à la base de donnée
  conn = PQsetdbLogin("localhost", "5432", "", "", "postgres", "postgres", "Aissatoudia") ;

    /* Vérification de la connexion*/
    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "Connection to database failed: %s",
                PQerrorMessage(conn));
        exit_nicely(conn);
    }
    else
        printf("Connexion etablie\n") ;

  MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
  label = gtk_label_new(NULL) ;
  text = g_locale_to_utf8("<i><big><b>Que Voulez-vous faire?</b></big></i>", -1, NULL, NULL, NULL);
  gtk_label_set_markup(GTK_LABEL(label), text) ;
  g_free(text) ;
  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER) ;
  button1 = gtk_button_new_with_mnemonic("Calendrier") ;
  button2 = gtk_button_new_with_mnemonic("Quitter") ;
  vbox = gtk_vbox_new(0,20) ;
  gtk_window_set_title(GTK_WINDOW(MainWindow), "MENU") ;
  gtk_window_set_position(GTK_WINDOW(MainWindow), GTK_WIN_POS_CENTER) ;
  gtk_window_resize(GTK_WINDOW(MainWindow), 300, 300) ;
  gtk_box_pack_start(GTK_BOX(vbox), label,0,0,0) ;
  gtk_box_pack_start(GTK_BOX(vbox), button1,0,0,0) ;
  gtk_box_pack_start(GTK_BOX(vbox), button2,0,0,0) ;
  gtk_container_add(GTK_CONTAINER(MainWindow), vbox) ;
  gtk_container_set_border_width(GTK_CONTAINER(MainWindow), 100) ;
  g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(Calendar_Window), NULL);
  gtk_widget_show_all(MainWindow) ;
  gtk_main();
  return 0 ;
}
