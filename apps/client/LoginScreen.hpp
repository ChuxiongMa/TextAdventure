#ifndef LOGIN_SCREEN_H
#define LOGIN_SCREEN_H

#include <ui/IScreen.hpp>
#include <ui/FormHelper.hpp>
#include <ui/FormField.hpp>
#include <ui/FormLabel.hpp>

#include "IScreenChangeable.hpp"
#include "LobbyScreen.hpp"

using IScreen = textadventure::IScreen;
using FormHelper = textadventure::FormHelper;
using FormField = textadventure::FormField;
using FormLabel = textadventure::FormLabel;

class LoginScreen: public IScreen {
public:
  LoginScreen(IScreenChangeable& changeable) {
    this->changeable = &changeable;
    form = std::unique_ptr<FormHelper>(
      new FormHelper(
        {
          FormField(1, 15, 5, 20, 0, 0).addUnderline().disableAutoskip(),
          FormField(1, 15, 7, 20, 0, 0).addUnderline().disableAutoskip(),
          FormField(1, 15, 10, 20, 0, 0).addUnderline().disableAutoskip(),
          FormField(1, 15, 12, 20, 0, 0).addUnderline().disableAutoskip(),
          FormField(1, 15, 15, 20, 0, 0).addUnderline().disableAutoskip()
        },
        {
          //TODO: Get strings for username and pw
          FormLabel(1, 5, "Welcome, please enter username & password, or register."),
          FormLabel(2, 5, "Press enter when fields are complete."),
          FormLabel(4, 4, "*LOGIN HERE*"),
          FormLabel(7, 10, "Password: "),

          FormLabel(9, 4, "*REGISTER HERE*"),
          FormLabel(10, 10, "Username: "),
          FormLabel(12, 10, "Password: "),
          FormLabel(14, 10, "Re-enter"),
          FormLabel(15, 10, "password: "),
          FormLabel(5, 10, "Username: ")
        }
      )
    );
    form->onDone([=]() {
      this->changeable->setScreen(std::unique_ptr<IScreen>(new LobbyScreen()));
    });
  }

  void run() {
    form->run();
  }
private:
  std::unique_ptr<FormHelper> form;
  IScreenChangeable* changeable;
};

#endif