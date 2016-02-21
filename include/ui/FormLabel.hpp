#ifndef FORM_LABEL_H
#define FORM_LABEL_H

#include <string>

namespace textadventure {
  class FormLabel {
  public:
    FormLabel(int y, int x, const std::string& text) : x(x), y(y), text(text) {}

    int getX() { return x; }
    int getY() { return y; }
    const std::string& getText() { return text; }
  private:
    int x;
    int y;
    std::string text;
  };
}


#endif
