#include <gtk/gtk.h>  
#include <string.h>
#include "my_library.h"


int main( int  argc,char *argv[] )  
{  

     /* GtkWidget is the storage type for widgets */
  GtkWidget *window;

  /* Initialise GTK */
  gtk_init (&argc, &argv);
    
  /* Create a new window */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Frame Example");

  /* Here we connect the "destroy" event to a signal handler */ 
  g_signal_connect (window, "destroy",
		    G_CALLBACK (gtk_main_quit), NULL);

  gtk_widget_set_size_request (window, 300, 300);
  /* Sets the border width of the window. */
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    GtkWidget *main; 
    main = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), main);









    GtkWidget *frame;
  /* Create a Frame */
  frame = gtk_frame_new (NULL);
  gtk_container_add (GTK_CONTAINER (main), frame);

  /* Set the frame's label */
  gtk_frame_set_label (GTK_FRAME (frame), "  You  ");

  /* Align the label at the right of the frame */
  gtk_frame_set_label_align (GTK_FRAME (frame), 0.1, 0.5);

  /* Set the style of the frame */
  gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_ETCHED_OUT);

   GtkWidget *frame1;
  /* Create a Frame */
  frame1 = gtk_frame_new (NULL);
  gtk_container_add (GTK_CONTAINER (main), frame1);

  /* Set the frame's label */
  gtk_frame_set_label (GTK_FRAME (frame1), "  You  ");

  /* Align the label at the right of the frame */
  gtk_frame_set_label_align (GTK_FRAME (frame1), 0.1, 0.5);

  /* Set the style of the frame */
  gtk_frame_set_shadow_type (GTK_FRAME (frame1), GTK_SHADOW_ETCHED_OUT);

gtk_widget_show_all(window);  

  /* Enter the event loop */
  gtk_main ();
    
  return 0;
}  