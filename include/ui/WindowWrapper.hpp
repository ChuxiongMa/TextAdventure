#ifndef WINDOW_WRAPPER_H
#define WINDOW_WRAPPER_H

#include <form.h>

namespace textadventure {
  /**
   * A RAII container for wrapping the window setup and teardown logic.
   */
  class WindowWrapper {
  public:
    WindowWrapper() {
      initscr();
      cbreak();
      noecho();
      keypad(stdscr, true);
    }

    ~WindowWrapper() {
      endwin();
    }
  };
}


#endif
