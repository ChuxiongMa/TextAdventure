#ifndef FORM_HELPER_H
#define FORM_HELPER_H

#include <string>
#include <vector>
#include <assert.h>
#include <functional>
#include <deque>

#include <form.h>
#include <ncurses.h>
#include <uvpp/GlobalLoop.hpp>

#include "FormField.hpp"
#include "FormLabel.hpp"

namespace textadventure {
  class FormHelper {
  public:
    FormHelper(
      const std::vector<FormField>& fields,
      const std::vector<FormLabel>& labels
    ) {
      fillWithFields(fields);
      createNcursesForm();
      prependLabels(labels);
    }

    ~FormHelper() {
      unpost_form(ncursesForm);
      free_form(ncursesForm);
      for (int i = 0; i < numberOfFields; i++) {
        free_field(fields[i]);
      }
      delete fields;
    }

    void run() {
      auto self = this;
      int ch = getch();
      if (ch != KEY_F(1)) {
        switch (ch) {
        case KEY_DOWN:
          form_driver(ncursesForm, REQ_NEXT_FIELD);
          form_driver(ncursesForm, REQ_END_LINE);
          break;
        case KEY_UP:
          form_driver(ncursesForm, REQ_PREV_FIELD);
          form_driver(ncursesForm, REQ_END_LINE);
          break;
        case KEY_LEFT:
          form_driver(ncursesForm, REQ_LEFT_CHAR);
          break;
        case KEY_RIGHT:
          form_driver(ncursesForm, REQ_RIGHT_CHAR);
          break;
        case KEY_BACKSPACE:
          form_driver(ncursesForm, REQ_DEL_PREV);
          break;  
        default:
          form_driver(ncursesForm, ch);
          break;
        }
        self->run();
      } else {
        notifyCallbacks();
      }
    }

    void onDone(std::function<void (void)> callback) {
      callbacks.push_back(callback);
    }
  private:
    FIELD** fields;
    FORM* ncursesForm;
    int numberOfFields;
    std::deque<std::function<void (void)>> callbacks;

    void notifyCallbacks() {
      for (auto callback : callbacks) {
        callback();
      }
    }

    void fillWithFields(const std::vector<FormField>& fields) {
      numberOfFields = fields.size();

      this->fields = new FIELD*[numberOfFields + 1];

      int i = 0;
      for (auto field : fields) {
        this->fields[i] = field.generateField();
        i++;
      }
      assert(i == fields.size());
      this->fields[i] = nullptr;
    }

    void createNcursesForm() {
      ncursesForm = new_form(this->fields);
      post_form(ncursesForm);
      refresh();
    }

    void prependLabels(const std::vector<FormLabel>& labels) {
      for (auto label : labels) {
        mvprintw(label.getY(), label.getX(), label.getText().c_str());
      }
      refresh();
    }
  };
}


#endif
