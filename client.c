#include <gtk/gtk.h>  
#include <string.h>
#include "my_library.h"

int player1_fields[10][10];
int player2_fields[10][10];
int count=0;
int shipNum=0;
void zero_player_1_fields(){
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            player1_fields[i][j]=0;
            player2_fields[i][j]=0;
        }
    }
}

void button_player2_clicked(GtkWidget *button, gpointer data) {
    //Declare colors
    GdkColor color_red;
    GdkColor color_yellow;
    GdkColor color_blue;
    GdkColor color_grey;
    //"Define" colors
    gdk_color_parse ("red", &color_red);
    gdk_color_parse ("yellow", &color_yellow);
    gdk_color_parse ("blue", &color_blue);
    gdk_color_parse ("grey", &color_grey);

    //Get button index in format x,y from button name
    const gchar *button_text = gtk_widget_get_name (button);
    //Define and declare temp variable
    char text[100] = "";
    //Copy button_text value to text to avoid warnings
    strcpy(text,button_text);
    //Define temp 2D variable to storage indexes as strings
    char** tokens;
    //Declare tokens as splited text (2 strings including indexes as strings)
    tokens = str_split(text, ',');
    //Define and declare x
    int x = atoi(tokens[0]);
    //Define and declare y
    int y = atoi(tokens[1]);
    //If field is not clicked yet, write 's' inside it, and update player fields array
    if(player2_fields[x][y]==0){
        gtk_widget_modify_bg (GTK_WIDGET(data), GTK_STATE_NORMAL, &color_yellow);
        player2_fields[x][y]=1;
    }
    //If it is, make it like not-clicked
    else{
        gtk_widget_modify_bg (GTK_WIDGET(data), GTK_STATE_NORMAL, NULL);
        player2_fields[x][y]=0;
    } 
}


void button_player1_clicked(GtkWidget *button, gpointer data) {
    //Declare colors
    GdkColor color_red;
    GdkColor color_yellow;
    GdkColor color_blue;
    GdkColor color_grey;
    //"Define" colors
    gdk_color_parse ("red", &color_red);
    gdk_color_parse ("yellow", &color_yellow);
    gdk_color_parse ("blue", &color_blue);
    gdk_color_parse ("grey", &color_grey);

    //Get button index in format x,y from button name
    const gchar *button_text = gtk_widget_get_name (button);
    //Define and declare temp variable
    char text[100] = "";
    //Copy button_text value to text to avoid warnings
    strcpy(text,button_text);
    //Define temp 2D variable to storage indexes as strings
    char** tokens;
    //Declare tokens as splited text (2 strings including indexes as strings)
    tokens = str_split(text, ',');
    //Define and declare x
    int x = atoi(tokens[0]);
    //Define and declare y
    int y = atoi(tokens[1]);
    //If field is not clicked yet, write 's' inside it, and update player fields array
    if(player1_fields[x][y]==0){
        gtk_widget_modify_bg (GTK_WIDGET(data), GTK_STATE_NORMAL, &color_grey);
        count++;
        player1_fields[x][y]=1;
    }
    //If it is, make it like not-clicked
    else{
        gtk_widget_modify_bg (GTK_WIDGET(data), GTK_STATE_NORMAL, NULL);
        count--;
        player1_fields[x][y]=0;
    } 
}
static gboolean checkShips(){

    return TRUE;
}
static gboolean writeToTextView(GtkTextBuffer *bufor, char * text){
    char text_to_write[500]  = "";
    strcat(text_to_write,text);
    //Define iter
    GtkTextIter iter;
    GtkTextMark *mark;
    mark = gtk_text_buffer_get_insert (bufor);
    gtk_text_buffer_get_iter_at_mark (bufor, &iter, mark);
    gtk_text_buffer_insert_with_tags_by_name (bufor, &iter, text_to_write, -1, "italic", NULL);
}

//5+4+4+3+3+2+2 =
static gboolean key_event(GtkWidget *widget, GdkEventKey *event, GtkTextBuffer *bufor)
{
    
    char text[100]="";
    strcat(text,gdk_keyval_name (event->keyval));
    if(strcmp(text,"s") == 0){
        if(count<23){
            switch(shipNum)
            {
                case 0:
                    if(count==5){
                        shipNum++;
                        writeToTextView(bufor,"\nGreat, you placed size 5 ship!\nNow, size 4 ship...");
                    }else{
                        writeToTextView(bufor,"\nPlace size 5 ship.");
                    }
                    break;
                case 1:
                    if(count==9){
                        shipNum++;
                        writeToTextView(bufor,"\nGreat, you placed size 4 ship!\nNow, size 4 ship...");
                    }else{
                        writeToTextView(bufor,"\nPlace size 4 ship.");
                    }
                    break;
                case 2:
                    if(count==13){
                        shipNum++;
                        writeToTextView(bufor,"\nGreat, you placed size 4 ship!\nNow, size 3 ship...");
                    }else{
                        writeToTextView(bufor,"\nPlace size 4 ship.");
                    }
                    break;
                case 3:
                    if(count==16){
                        shipNum++;
                        writeToTextView(bufor,"\nGreat, you placed size 3 ship!\nNow, size 3 ship...");
                    }else{
                        writeToTextView(bufor,"\nPlace size 3 ship.");
                    }
                    break;
                case 4:
                    if(count==19){
                        shipNum++;
                        writeToTextView(bufor,"\nGreat, you placed size3 ship!\nNow, size 2 ship...");
                    }else{
                        writeToTextView(bufor,"\nPlace size 3 ship.");
                    }
                    break;
                case 5:
                    if(count==21){
                        shipNum++;
                        writeToTextView(bufor,"\nGreat, you placed size 2 ship!\nNow, size 2 ship...");
                    }else{
                        writeToTextView(bufor,"\nPlace size 2 ship.");
                    }
                    break;
                case 6:
                    if(count==23){
                        shipNum++;
                        
                    }else{
                        writeToTextView(bufor,"\nShips placed. Well done!");
                    }
                    break;
                default:
                    break;
            }
            return FALSE;
        }
        else{
            //tutaj wyslij sygnal
            writeToTextView(bufor,"\nGreat, you placed size 2 ship!\nShips placed. Well done!");
            g_print("l\n");
            return TRUE;
        }
    }
    else{
        
    }
    return FALSE;
}

int main( int  argc,char *argv[] )  
{  
    //Clear player 1 fields
    zero_player_1_fields();

    //Init gtk
    gtk_init (&argc, &argv);  

    //Declare colors
    GdkColor color_red;
    GdkColor color_yellow;
    GdkColor color_blue;
    GdkColor color_grey;
    //"Define" colors
    gdk_color_parse ("red", &color_red);
    gdk_color_parse ("yellow", &color_yellow);
    gdk_color_parse ("blue", &color_blue);
    gdk_color_parse ("grey", &color_grey);


    //Define window
    GtkWidget *window;  
    //Declare window
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL); 
    //Set no-resize to window
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    //Set window size 800x800
    gtk_widget_set_size_request (GTK_WIDGET(window), 800, 800); 
    //Center window on deskop
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    //Set window title
    gtk_window_set_title (GTK_WINDOW(window), "Battleship Game");
    //Set end process after close window
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    //Enable GDK_KEY_PRESS_MASK to catch key pressing (s-start)
    gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);

    //Define main container (includes all elements) 
    GtkWidget *container_main;
    //Declare main container as vbox (all elements one under another)
    container_main = gtk_hbox_new(FALSE, 1);
    //Put main container to window
    gtk_container_add(GTK_CONTAINER(window), container_main);
        

    
    //Define tables container (includes all elements) 
    GtkWidget *container_tables;
    //Declare tables container as vbox (all elements one under another)
    container_tables = gtk_vbox_new(FALSE, 1);
    //Set tables container size
    gtk_widget_set_size_request(GTK_WIDGET(container_tables), 150, 700);
    //Set table container spacing
    gtk_box_set_spacing (GTK_BOX(container_tables), 10);
    //Set container border
    gtk_container_set_border_width (GTK_CONTAINER(container_tables), 10);
    //Put main container to window
    gtk_container_add(GTK_CONTAINER(container_main), container_tables);

    //Define frames
    GtkWidget *frame_player_1; 
    GtkWidget *frame_player_2; 
    //Declare frames
    frame_player_1 = gtk_frame_new (NULL);
    frame_player_2 = gtk_frame_new (NULL);
    //Set frames labels
    gtk_frame_set_label( GTK_FRAME(frame_player_1), "  You  " );
    gtk_frame_set_label( GTK_FRAME(frame_player_2), "  Opponent  " );
    //Align the label at the right of the frame
    gtk_frame_set_label_align( GTK_FRAME(frame_player_1), 0.1, 0.5);
    gtk_frame_set_label_align( GTK_FRAME(frame_player_2), 0.1, 0.5);
    /* Set the style of the frame */
    gtk_frame_set_shadow_type( GTK_FRAME(frame_player_1), GTK_SHADOW_ETCHED_OUT);
    gtk_frame_set_shadow_type( GTK_FRAME(frame_player_2), GTK_SHADOW_ETCHED_OUT);
    //Put frames in tables containers (in reverse order, because we want player2 [opponent] table on top)
    gtk_box_pack_start(GTK_BOX(container_tables), frame_player_2, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(container_tables), frame_player_1, TRUE, TRUE, 1);

    //Define players tables
    GtkWidget *table_player1;
    GtkWidget *table_player2;
    //Declare players tables
    table_player1 = gtk_table_new(10, 10, TRUE);
    table_player2 = gtk_table_new(10, 10, TRUE);
    //Set players tables borders width
    gtk_container_set_border_width (GTK_CONTAINER(table_player1), 10);
    gtk_container_set_border_width (GTK_CONTAINER(table_player2), 10);
    //Set players tables background
    gtk_widget_modify_bg (GTK_WIDGET(table_player1),GTK_STATE_NORMAL, &color_red);
    gtk_widget_modify_bg (GTK_WIDGET(table_player2),GTK_STATE_NORMAL, &color_red);
    //Set players tables row spacings
    gtk_table_set_row_spacings(GTK_TABLE(table_player1), 1);
    gtk_table_set_row_spacings(GTK_TABLE(table_player2), 1);
    //Set players tables col spacings
    gtk_table_set_col_spacings(GTK_TABLE(table_player1), 2);
    gtk_table_set_col_spacings(GTK_TABLE(table_player2), 2);
    //Put tables to frames (in reverse order, because we want player2 [opponent] table on top)
    gtk_container_add(GTK_CONTAINER(frame_player_2), table_player2);
    gtk_container_add(GTK_CONTAINER(frame_player_1), table_player1);

    //Define players tables fields event boxes (so we can color buttons) 
    GtkWidget *event_box_1[10][10];
    GtkWidget *event_box_2[10][10];
    //Declare players tables fields event boxes
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            event_box_1[i][j] = gtk_event_box_new();
            event_box_2[i][j] = gtk_event_box_new();
        }
    }
    //Define players tables fields (buttons)
    GtkWidget *buttons_player1[10][10];
    GtkWidget *buttons_player2[10][10];
    //Declare player tables fields (buttons)
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            char row[5];sprintf(row, "%d", i);
            char col[5];sprintf(col, "%d", j);
            strcat(col, ",");strcat(col, row);
            buttons_player1[i][j] = gtk_button_new();
            gtk_container_add (GTK_CONTAINER(buttons_player1[i][j]), event_box_1[i][j]);
            buttons_player2[i][j] = gtk_button_new();
            gtk_container_add (GTK_CONTAINER(buttons_player2[i][j]), event_box_2[i][j]);
            gtk_widget_set_name(buttons_player1[i][j],col);
            gtk_widget_set_name(buttons_player2[i][j],col);
        }
    }
    //Set buttons sizes to 40x40
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            gtk_widget_set_size_request(GTK_WIDGET(buttons_player1[i][j]), 20, 20);
            gtk_widget_set_size_request(GTK_WIDGET(buttons_player2[i][j]), 20, 20);
        }
    }
    //color buttons to default (blue)
    /*
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            gtk_widget_modify_bg (GTK_WIDGET(event_box_1[i][j]), GTK_STATE_PRELIGHT, &color_yellow);
            gtk_widget_modify_bg (GTK_WIDGET(event_box_2[i][j]), GTK_STATE_PRELIGHT, &color_yellow);

        }
    }
    */
    //Disable player2 table on start (we dont need it until we place our ships)
    /*
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            gtk_widget_set_sensitive (GTK_WIDGET(buttons_player2[i][j]), FALSE);
        }
    }
    */
    //Put fields (buttons) to players tables
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            gtk_table_attach_defaults (GTK_TABLE(table_player1), buttons_player1[i][j], i, i+1, j, j+1);
            gtk_table_attach_defaults (GTK_TABLE(table_player2), buttons_player2[i][j], i, i+1, j, j+1); 
        }
    }

    //Define right container
    GtkWidget *container_right;
    //Declare right container as vbox (all elements one under another)
    container_right = gtk_vbox_new(FALSE, 1); 
    //Set right container borders widh
    gtk_container_set_border_width (GTK_CONTAINER(container_right), 10);
    //Put right container to window
    gtk_container_add(GTK_CONTAINER(container_main), container_right);

    //Define frame
    GtkWidget *frame_console; 
    //Declare frame
    frame_console = gtk_frame_new (NULL);
    //Set frame label
    gtk_frame_set_label( GTK_FRAME(frame_console), "  Console  " );
    //Align the label at the right of the frame
    gtk_frame_set_label_align( GTK_FRAME(frame_console), 0.1, 0.5);
    /* Set the style of the frame */
    gtk_frame_set_shadow_type( GTK_FRAME(frame_console), GTK_SHADOW_ETCHED_OUT);
    //Put frames in tables containers (in reverse order, because we want player2 [opponent] table on top)
    gtk_box_pack_start(GTK_BOX(container_right), frame_console, TRUE, TRUE, 1);

    //Define console log
    GtkWidget *console_log;
    //Declare console log (as text_view)
    console_log = gtk_text_view_new();
    //Set console log non-editable
    gtk_text_view_set_editable(GTK_TEXT_VIEW(console_log), FALSE);
    

    //Define scrolled window to contains console_log
    GtkWidget* scrolled_window;
    //Declare scrolled window
    scrolled_window = gtk_scrolled_window_new(FALSE, NULL);
    //Put console log to scrolled window
    gtk_container_add(GTK_CONTAINER(scrolled_window), console_log);
    //Put scrolled window in bottom container
    gtk_container_add(GTK_CONTAINER(frame_console), scrolled_window);

    //Connect buttons to actions
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            g_signal_connect(G_OBJECT(buttons_player1[i][j]), "clicked",  G_CALLBACK(button_player1_clicked), event_box_1[i][j]);
            g_signal_connect(G_OBJECT(buttons_player2[i][j]), "clicked",  G_CALLBACK(button_player2_clicked), event_box_2[i][j]);
        }
    }

    //Define bufer
    GtkTextBuffer *bufor;
    //Declare bufor
    bufor = gtk_text_view_get_buffer(GTK_TEXT_VIEW(console_log));

    //"Define" text tags
    gtk_text_buffer_create_tag(bufor, "bold", "weight", PANGO_WEIGHT_BOLD, NULL);
    gtk_text_buffer_create_tag(bufor, "italic", "style", PANGO_STYLE_ITALIC, NULL);
    gtk_text_buffer_create_tag(bufor, "blue_font", "foreground", "blue", NULL);

    //Define iter
    GtkTextIter iter;

    //Write start text in text view
    gtk_text_buffer_get_iter_at_offset(bufor, &iter, 0);
    gtk_text_buffer_insert_with_tags_by_name (bufor, &iter, "Welcome to game!\n", -1, "bold", NULL);
    writeToTextView(bufor,"Choose placement for  your ships...\n(After every placement press 's')\nPlace ship size 5");

    //Connect window with keyboard and textview
    g_signal_connect(window, "key-release-event", G_CALLBACK(key_event), bufor);

    //Show all widgets and window
    gtk_widget_show_all(window);  

    gtk_main ();  
    return 0;  
}  