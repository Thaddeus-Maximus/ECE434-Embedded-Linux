#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <curses.h>
#include <unistd.h>

int main(int argc, char** argv) {

  // Read from the CLI
  int rows = 8;
  if (argc > 1)
    rows = atoi(argv[1]);
  int cols = rows;
  if (argc > 2)
    cols = atoi(argv[2]);

  // Windows, cursor position, temp variables
  WINDOW *mainwin, *childwin;
  char ch;
  int x = 1;
  int y = 1;
  int i, j;
 

  // Try to initialize ncurses
  if ( (mainwin = initscr()) == NULL ) {
    fprintf(stderr, "Error starting ncurses\n");
    exit(EXIT_FAILURE);
  }
 
  // Disable keystrokes being printed and enable the keypad
  noecho();
  keypad(mainwin, TRUE);
 
  // Create a child window with a border for the user
  childwin = subwin(mainwin, rows+2, cols+2, 1, 1);
  box(childwin, 0, 0);

  // Draw it
  refresh();

  // Lay down the first etch
  mvwaddstr(childwin, y, x, "#");
  wmove(childwin, y, x);
  wrefresh(childwin);

  // Loop until the user presses q
  while ( (ch = getch()) != 'q' ) {
    // Go the correct direction
    switch ( ch ) {
      case KEY_UP:
        if ( y > 1 )
          y--;
        break;
     
      case KEY_DOWN:
        if ( y < rows )
          y++;
        break;
     
      case KEY_LEFT:
        if ( x > 1 )
          x--;
        break;
     
      case KEY_RIGHT:
        if ( x < cols )
          x++;
        break;

      // If home is pressed, wipe the screen
      case KEY_HOME:
        
        for (i=0; i<rows; i++) {
          for (j=0; j<cols; j++)
            mvwaddstr(childwin, i+1, j+1, " ");
        }
    }
    
    // Write the new cursor position
    mvwaddstr(childwin, y, x, "#");
    wmove(childwin, y, x);
    wrefresh(childwin);
  }

  // Clean up
  delwin(childwin);
  delwin(mainwin);
  endwin();
  refresh();

  return EXIT_SUCCESS;
}