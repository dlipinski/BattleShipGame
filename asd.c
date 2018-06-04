/*

  HelloX.C
  ========
  (c) Copyright Paul Griffiths 1999
  Email: mail@paulgriffiths.net

  "Hello, World!", X Window System style.

*/


#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/cursorfont.h>	/* pre-defined crusor shapes */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Buttons structure */
typedef struct{
    int x1,x2,y1,y2,clicked,ship;
} MyField;
/* Game structure */
typedef struct{
    int state; /* 0 - choosing ships positions, 1 - waiting for 2nd player, 3-my turn, 4-his tour, 5-end */
    int ships_placed;
} Game;
/* Communicats */
const char *communicats[] ={
    "one" /* 0 */,
    "two" /* 1 */
};
/*  Global variables  */

Display *     display;
int           screen_num;
static char * appname;


/*  main() function  */

int main( int argc, char * argv[] ) {

    /* Declare and define buttons */
    MyField opponent_fields[10][10];
    MyField my_fields[10][10];
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            my_fields[i][j].clicked = 0;
            my_fields[i][j].ship = 0;
            opponent_fields[i][j].clicked = 0;
        }
    }
    /* Declare and define game */
    Game game;
    game.state=0;
    game.ships_placed = 0;
    /*  Window variables  */

    Window       win;
    int          x, y;
    unsigned int width, height;
    unsigned int border_width;
    char *       window_name = "BattleShip!";
    char *       icon_name   = "HelloX";


    /*  Display variables  */

    char *       display_name = NULL;
    unsigned int display_width, display_height;
    

    /*  Miscellaneous X variables  */

    XSizeHints *  size_hints;
    XWMHints   *  wm_hints;
    XClassHint *  class_hints;
    XTextProperty windowName, iconName;
    XEvent        report;
    XFontStruct * font_info;
    XGCValues     values;
    GC            gc;
    
    appname = argv[0];


    /*  Allocate memory for our structures  */

    if ( !( size_hints  = XAllocSizeHints() ) || 
	 !( wm_hints    = XAllocWMHints()   ) ||
	 !( class_hints = XAllocClassHint() )    ) {
	fprintf(stderr, "%s: couldn't allocate memory.\n", appname);
	exit(EXIT_FAILURE);
    }


    /*  Connect to X server  */

    if ( (display = XOpenDisplay(display_name)) == NULL ) {
	fprintf(stderr, "%s: couldn't connect to X server %s\n",
		appname, display_name);
	exit(EXIT_FAILURE);
    }


    /*  Get screen size from display structure macro  */

    screen_num     = DefaultScreen(display);
    display_width  = DisplayWidth(display, screen_num);
    display_height = DisplayHeight(display, screen_num);


    /*  Set initial window size and position, and create it  */

    x = y = 0;
    width  = 330;
    height = 650;

    win = XCreateSimpleWindow(display, RootWindow(display, screen_num),
			      x, y, width, height, border_width,
			      BlackPixel(display, screen_num),
			      WhitePixel(display, screen_num));


    /*  Set hints for window manager before mapping window  */

    if ( XStringListToTextProperty(&window_name, 1, &windowName) == 0 ) {
	fprintf(stderr, "%s: structure allocation for windowName failed.\n",
		appname);
	exit(EXIT_FAILURE);
    }

    if ( XStringListToTextProperty(&icon_name, 1, &iconName) == 0 ) {
	fprintf(stderr, "%s: structure allocation for iconName failed.\n",
		appname);
	exit(EXIT_FAILURE);
    }

    size_hints->flags       = PPosition | PSize | PMinSize;
    size_hints->min_width   = 200;
    size_hints->min_height  = 100;

    wm_hints->flags         = StateHint | InputHint;
    wm_hints->initial_state = NormalState;
    wm_hints->input         = True;

    class_hints->res_name   = appname;
    class_hints->res_class  = "hellox";

    XSetWMProperties(display, win, &windowName, &iconName, argv, argc,
		     size_hints, wm_hints, class_hints);


    /*  Choose which events we want to handle  */

    XSelectInput(display, win, ExposureMask | KeyPressMask |
		 ButtonPressMask | StructureNotifyMask);


    /*  Load a font called "9x15"  */

    if ( (font_info = XLoadQueryFont(display, "9x15")) == NULL ) {
	fprintf(stderr, "%s: cannot open 9x15 font.\n", appname);
	exit(EXIT_FAILURE);
    }


    /*  Create graphics context  */

    gc = XCreateGC(display, win, 0, &values);

    XSetFont(display, gc, font_info->fid);
    XSetForeground(display, gc, BlackPixel(display, screen_num));


    /*  Display Window  */

    XMapWindow(display, win);

    
    /* Set colors */
    Status rc;			/* return status of various Xlib functions.  */
    Colormap screen_colormap;  
    XColor red, brown, blue, yellow, green,black;
    screen_colormap = DefaultColormap(display, DefaultScreen(display));
    /* allocate a new GC (graphics context) for drawing in the window. */
    XSync(display, False);

    /* get access to the screen's color map. */
    screen_colormap = DefaultColormap(display, DefaultScreen(display));

    /* allocate the set of colors we will want to use for the drawing. */
    rc = XAllocNamedColor(display, screen_colormap, "red", &red, &red);
    if (rc == 0) {
        fprintf(stderr, "XAllocNamedColor - failed to allocated 'red' color.\n");
        exit(1);
    }
    rc = XAllocNamedColor(display, screen_colormap, "brown", &brown, &brown);
    if (rc == 0) {
        fprintf(stderr, "XAllocNamedColor - failed to allocated 'brown' color.\n");
        exit(1);
    }
    rc = XAllocNamedColor(display, screen_colormap, "blue", &blue, &blue);
    if (rc == 0) {
        fprintf(stderr, "XAllocNamedColor - failed to allocated 'blue' color.\n");
        exit(1);
    }
    rc = XAllocNamedColor(display, screen_colormap, "yellow", &yellow, &yellow);
    if (rc == 0) {
        fprintf(stderr, "XAllocNamedColor - failed to allocated 'yellow' color.\n");
        exit(1);
    }
    rc = XAllocNamedColor(display, screen_colormap, "green", &green, &green);
    if (rc == 0) {
        fprintf(stderr, "XAllocNamedColor - failed to allocated 'green' color.\n");
        exit(1);
    }
    rc = XAllocNamedColor(display, screen_colormap, "black", &black, &black);
    if (rc == 0) {
        fprintf(stderr, "XAllocNamedColor - failed to allocated 'black' color.\n");
        exit(1);
    }
    XSetForeground(display, gc, black.pixel);

    /* Set rectangle and text variables */
    int rectangle_size = 30;
    int spacing = 10;
    int rec_x,rec_y;
    /* Cursor stuff */
    Window root_return,child_return;
    int root_x_return, root_y_return;
    int cursor_x, cursor_y;
    unsigned int mask_return;
    /*  Enter event loop  */

    while ( 1 ) {
	static char * message = "Hello, X Window System!";
	static int    length;
	static int    font_height;
	static int    msg_x, msg_y;
    static int    rectangle_size = 30;
    static int    spacing = 10;
    static int    rec_x,rec_y;
    static char   pos_string[20];
    static char   i_string[20],j_string[20];
	XNextEvent(display, &report);

	switch ( report.type ) {

	case Expose:

	    if ( report.xexpose.count != 0 )
		    break;
        XDrawString(display,win,gc,100,330,"Welcome to game!",strlen("Welcome to game!"));
        /* Set opponent rectangles */
        for ( int i=0; i< 10; i++){
            for (int j=0; j<10; j++){
                opponent_fields[i][j].x1 = i * rectangle_size + spacing;
                opponent_fields[i][j].x2 = i * rectangle_size + rectangle_size;
                opponent_fields[i][j].y1 = j*rectangle_size+ spacing;
                opponent_fields[i][j].y2 = j*rectangle_size+ spacing + rectangle_size;
            }
        }
        /* Set player rectangles */
        for ( int i=0; i< 10; i++){
            for (int j=0; j<10; j++){
                rec_x = i*rectangle_size+spacing;
                rec_y =j*rectangle_size+ spacing + spacing*rectangle_size + rectangle_size;
                my_fields[i][j].x1 = i * rectangle_size + spacing;
                my_fields[i][j].x2 = i * rectangle_size + rectangle_size;
                my_fields[i][j].y1 = j*rectangle_size+ spacing + spacing*rectangle_size + rectangle_size;
                my_fields[i][j].y2 = j*rectangle_size+ spacing + spacing*rectangle_size + rectangle_size + rectangle_size;
            }
        }
	    break;


	case ConfigureNotify:

	    /*  Store new window width & height  */

	    width  = report.xconfigure.width;
	    height = report.xconfigure.height;

	    break;

    case KeyPress:
        break;
    case ButtonPress:
        XQueryPointer(display,win,&root_return,&child_return,&root_x_return,&root_y_return,&cursor_x,&cursor_y,&mask_return);
        for(int i=0; i<10; i++){
            for( int j=0; j<10; j++){
                if(cursor_x > my_fields[i][j].x1 && cursor_x < my_fields[i][j].x2 && cursor_y > my_fields[i][j].y1 && cursor_y < my_fields[i][j].y2 && my_fields[i][j].ship!=1){
                    if(my_fields[i][j].clicked == 1)
                        my_fields[i][j].clicked = 0;
                    else
                        my_fields[i][j].clicked = 1;
                    break;
                }
                if(cursor_x > opponent_fields[i][j].x1 && cursor_x < opponent_fields[i][j].x2 && cursor_y > opponent_fields[i][j].y1 && cursor_y < opponent_fields[i][j].y2 && game.state==3){
                    if(opponent_fields[i][j].clicked == 1)
                        opponent_fields[i][j].clicked = 0;
                    else
                        opponent_fields[i][j].clicked = 1;
                    break;
                }
            }
        }
        XClearWindow(display,win);
        int clicked_amount = 0;
        
        
        switch (game.state){
            case 0: /* Setting up ships */
                for(int i=0;i<10;i++) /* count clicked fields */
                    for(int j=0;j<10;j++)
                        if(my_fields[i][j].clicked==1)
                            clicked_amount++;
                int i1,j1,i2,j2;
                if( clicked_amount == 2){/* selected 2 points for new ship */
                    for(int i=0;i<10;i++) /* find 1st point of ship */
                        for(int j=0;j<10;j++)
                            if(my_fields[i][j].clicked==1){
                                i1 = i;j1 = j;
                            }
                    for(int i=0;i<10;i++) /* find 2nd point of ship */
                        for(int j=0;j<10;j++)
                            if(my_fields[i][j].clicked==1 && (i!= i1 || j!=j1)){
                                i2 = i;j2 = j;
                            }
                    switch (game.ships_placed){ /* depends on how many ships we arleady placed */
                        case 0: /* 1st, 5-fields ship */
                            if( i1 == i2 || j1 == j2 ){ /* check if points are in 1 line */
                                if(i1 == i2 && j1 == j2+4) { for(int j = j2;j<=j1;j++) { my_fields[i1][j].ship=1;} game.ships_placed++; break;} /* case from left to right */
                                if(i1 == i2 && j1 == j2-4) { for(int j = j1;j<=j2;j++) { my_fields[i2][j].ship=1;} game.ships_placed++; break;} /* case from right to left */
                                if(j1 == j2 && i1 == i2+4) { for(int i = i2;i<=i1;i++) { my_fields[i][j1].ship=1;} game.ships_placed++; break;} /* case from bottom to top */
                                if(j1 == j2 && i1 == i2-4) { for(int i = i1;i<=i2;i++) { my_fields[i][j2].ship=1;} game.ships_placed++; break;} /* case from top to bottom */
                            }
                            break;
                        case 1: /* 2nd, 4-fields ship */
                            if( i1 == i2 || j1 == j2 ){ /* check if points are in 1 line */
                                if(i1 == i2 && j1 == j2+3) { for(int j = j2;j<=j1;j++) { my_fields[i1][j].ship=1;} game.ships_placed++; break;} /* case from left to right */
                                if(i1 == i2 && j1 == j2-3) { for(int j = j1;j<=j2;j++) { my_fields[i1][j].ship=1;} game.ships_placed++; break;} /* case from right to left */
                                if(j1 == j2 && i1 == i2+3) { for(int i = i2;i<=i1;i++) { my_fields[i][j1].ship=1;} game.ships_placed++; break;} /* case from bottom to top */
                                if(j1 == j2 && i1 == i2-3) { for(int i = i1;i<=i2;i++) { my_fields[i][j1].ship=1;} game.ships_placed++; break;} /* case from top to bottom */
                            }
                            break;
                        case 2: /* 2nd, 4-fields ship */
                            if( i1 == i2 || j1 == j2 ){ /* check if points are in 1 line */
                                if(i1 == i2 && j1 == j2+3) { for(int j = j2;j<=j1;j++) { my_fields[i1][j].ship=1;} game.ships_placed++; break;} /* case from left to right */
                                if(i1 == i2 && j1 == j2-3) { for(int j = j1;j<=j2;j++) { my_fields[i1][j].ship=1;} game.ships_placed++; break;} /* case from right to left */
                                if(j1 == j2 && i1 == i2+3) { for(int i = i2;i<=i1;i++) { my_fields[i][j1].ship=1;} game.ships_placed++; break;} /* case from bottom to top */
                                if(j1 == j2 && i1 == i2-3) { for(int i = i1;i<=i2;i++) { my_fields[i][j1].ship=1;} game.ships_placed++; break;} /* case from top to bottom */
                            }
                            break;
                        case 3: /* 3rd, 3-fields ship */
                            if( i1 == i2 || j1 == j2 ){ /* check if points are in 1 line */
                                if(i1 == i2 && j1 == j2+2) { for(int j = j2;j<=j1;j++) { my_fields[i1][j].ship=1;} game.ships_placed++; break;} /* case from left to right */
                                if(i1 == i2 && j1 == j2-2) { for(int j = j1;j<=j2;j++) { my_fields[i1][j].ship=1;} game.ships_placed++; break;} /* case from right to left */
                                if(j1 == j2 && i1 == i2+2) { for(int i = i2;i<=i1;i++) { my_fields[i][j1].ship=1;} game.ships_placed++; break;} /* case from bottom to top */
                                if(j1 == j2 && i1 == i2-2) { for(int i = i1;i<=i2;i++) { my_fields[i][j1].ship=1;} game.ships_placed++; break;} /* case from top to bottom */
                            }
                            break;
                        case 4: /* 4th, 3-fields ship */
                            if( i1 == i2 || j1 == j2 ){ /* check if points are in 1 line */
                                if(i1 == i2 && j1 == j2+2) { for(int j = j2;j<=j1;j++) { my_fields[i1][j].ship=1;} game.ships_placed++; break;} /* case from left to right */
                                if(i1 == i2 && j1 == j2-2) { for(int j = j1;j<=j2;j++) { my_fields[i1][j].ship=1;} game.ships_placed++; break;} /* case from right to left */
                                if(j1 == j2 && i1 == i2+2) { for(int i = i2;i<=i1;i++) { my_fields[i][j1].ship=1;} game.ships_placed++; break;} /* case from bottom to top */
                                if(j1 == j2 && i1 == i2-2) { for(int i = i1;i<=i2;i++) { my_fields[i][j1].ship=1;} game.ships_placed++; break;} /* case from top to bottom */
                            }
                            break;
                        case 5: /* 5th, 2-fields ship */
                            if( i1 == i2 || j1 == j2 ){ /* check if points are in 1 line */
                                if(i1 == i2 && j1 == j2+1) { for(int j = j2;j<=j1;j++) { my_fields[i1][j].ship=1;} game.ships_placed++; break;} /* case from left to right */
                                if(i1 == i2 && j1 == j2-1) { for(int j = j1;j<=j2;j++) { my_fields[i1][j].ship=1;} game.ships_placed++; break;} /* case from right to left */
                                if(j1 == j2 && i1 == i2+1) { for(int i = i2;i<=i1;i++) { my_fields[i][j1].ship=1;} game.ships_placed++; break;} /* case from bottom to top */
                                if(j1 == j2 && i1 == i2-1) { for(int i = i1;i<=i2;i++) { my_fields[i][j1].ship=1;} game.ships_placed++; break;} /* case from top to bottom */
                            }
                            break;
                        case 6: /* 6th, 2-fields ship */
                            if( i1 == i2 || j1 == j2 ){ /* check if points are in 1 line */
                                if(i1 == i2 && j1 == j2+1) { for(int j = j2;j<=j1;j++) { my_fields[i1][j].ship=1;} game.ships_placed++;  break;} /* case from left to right */
                                if(i1 == i2 && j1 == j2-1) { for(int j = j1;j<=j2;j++) { my_fields[i1][j].ship=1;} game.ships_placed++;  break;} /* case from right to left */
                                if(j1 == j2 && i1 == i2+1) { for(int i = i2;i<=i1;i++) { my_fields[i][j1].ship=1;} game.ships_placed++;  break;} /* case from bottom to top */
                                if(j1 == j2 && i1 == i2-1) { for(int i = i1;i<=i2;i++) { my_fields[i][j1].ship=1;} game.ships_placed++;  break;} /* case from top to bottom */
                            }
                            
                            break;
                        default:
                            break;
                    }
                    for(int i=0;i<10;i++) /* unclick all fields */
                        for(int j=0;j<10;j++)
                            my_fields[i][j].clicked = 0;
                        
                }
                XSetForeground(display, gc, black.pixel);
                switch (game.ships_placed){
                    case 0:
                        XDrawString(display,win,gc,10,330,"Choose points of 1st ship (size 5)",strlen("Choose points of 1st ship (size 5)"));
                        break;
                    case 1:
                        XDrawString(display,win,gc,10,330,"Choose points of 2nd ship (size 4)",strlen("Choose points of 2nd ship (size 4)"));
                        break;
                    case 2:
                        XDrawString(display,win,gc,10,330,"Choose points of 3rd ship (size 4)",strlen("Choose points of 3rd ship (size 4)"));
                        break;
                    case 3:
                        XDrawString(display,win,gc,10,330,"Choose points of 4th ship (size 3)",strlen("Choose points of 4th ship (size 3)"));
                        break;
                    case 4:
                        XDrawString(display,win,gc,10,330,"Choose points of 5th ship (size 3)",strlen("Choose points of 5th ship (size 3)"));
                        break;
                    case 5:
                        XDrawString(display,win,gc,10,330,"Choose points of 6th ship (size 2)",strlen("Choose points of 6th ship (size 2)"));
                        break;
                    case 6:
                        XDrawString(display,win,gc,10,330,"Choose points of 7th ship (size 2)",strlen("Choose points of 7th ship (size 2)"));
                        break;
                    case 7:
                        game.state=1;
                        XDrawString(display,win,gc,10,330,"Waiting for second player...",strlen("Waiting for second player..."));
                        break;
                    default:
                        break;
                }
                break;
            
            case 1:
                XSetForeground(display, gc, black.pixel);
                XDrawString(display,win,gc,10,330,"Waiting for second player...",strlen("Waiting for second player..."));
                break;
            default:
                break;
        }
        
        /* Print oppontnt rectangles */
        for ( int i=0; i< 10; i++){
            for (int j=0; j<10; j++){
                rec_x = opponent_fields[i][j].x1;
                rec_y = opponent_fields[i][j].y1;
                XSetForeground(display, gc, green.pixel);
                XDrawRectangle(display, win, gc, i*rectangle_size+spacing, rec_y, rectangle_size, rectangle_size);
                if(opponent_fields[i][j].clicked == 1 && game.state > 0){
                    XFillRectangle(display,win,gc,opponent_fields[i][j].x1,opponent_fields[i][j].y1,rectangle_size,rectangle_size);
                }
            }
        }
        /* Print player rectangles */
        for ( int i=0; i< 10; i++){
            for (int j=0; j<10; j++){
                rec_x = my_fields[i][j].x1;
                rec_y = my_fields[i][j].y1;
                XSetForeground(display, gc, blue.pixel);
                XDrawRectangle(display, win, gc, i*rectangle_size+spacing, rec_y, rectangle_size, rectangle_size);
                if(my_fields[i][j].clicked == 1 && my_fields[i][j].ship != 1  && game.state == 0){
                    XSetForeground(display, gc, yellow.pixel);
                    XFillRectangle(display,win,gc,my_fields[i][j].x1,my_fields[i][j].y1,rectangle_size,rectangle_size);
                }
                if(my_fields[i][j].clicked != 1 && my_fields[i][j].ship == 1){
                    XSetForeground(display, gc, blue.pixel);
                    XFillRectangle(display,win,gc,my_fields[i][j].x1,my_fields[i][j].y1,rectangle_size,rectangle_size);
                }
            }
        }
	    //XUnloadFont(display, font_info->fid);
	    //XFreeGC(display, gc);
	    //XCloseDisplay(display);
	    //exit(EXIT_SUCCESS);

	}
    }

    return EXIT_SUCCESS;   /*  We shouldn't get here  */
}

