#ifndef CALENDAR_H_INCLUDED
#define CALENDAR_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <libpq-fe.h>

static GtkWidget* Textarea = NULL ;
static GtkWidget* Textarea1 = NULL ;
static GtkTextIter endfirst ;
void Quit(GtkWidget* , gpointer) ;
void Calendar_Window(GtkWidget* , gpointer) ;
void Events(GtkCalendar*, gpointer) ;
void Enregistrer(GtkWidget* , gpointer) ;


#endif // CALENDAR_H_INCLUDED
