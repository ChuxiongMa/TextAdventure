#ifndef FORM_FIELD_H
#define FORM_FIELD_H

#include <form.h>

namespace textadventure {
  class FormField {
  public:
    FormField(
      int height,
      int width,
      int toprow,
      int leftcol,
      int offscreen,
      int nbuffers
    )
      : height(height)
      , width(width)
      , toprow(toprow)
      , leftcol(leftcol)
      , offscreen(offscreen)
      , nbuffers(nbuffers)
      , underline(false)
      , autoskip(true) {}

    FIELD* generateField() {
      auto field = new_field(height, width, toprow, leftcol, offscreen, nbuffers);

      if (underline) {
        set_field_back(field, A_UNDERLINE);
      }
      if (!autoskip) {
        field_opts_off(field, O_AUTOSKIP);
      }

      return field;
    }

    /**
     * Adds an underline to the form field.
     *
     * @returns a copy of this instance.
     */
    FormField addUnderline() {
      underline = true;
      return *this;
    }

    /**
     * Disables autoskip.
     *
     * @returns a copy of this instance.
     */
    FormField disableAutoskip() {
      autoskip = false;
      return *this;
    }

  private:
    int height;
    int width;
    int toprow;
    int leftcol;
    int offscreen;
    int nbuffers;
    bool underline;
    bool autoskip;
  };
}


#endif
