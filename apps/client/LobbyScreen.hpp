#ifndef LOBBY_SCREEN_H
#define LOBBY_SCREEN_H

#include <ui/IScreen.hpp>
#include <ui/FormHelper.hpp>
#include <ui/FormField.hpp>
#include <ui/FormLabel.hpp>

using IScreen = textadventure::IScreen;
using FormHelper = textadventure::FormHelper;
using FormField = textadventure::FormField;
using FormLabel = textadventure::FormLabel;

class LobbyScreen : public IScreen {
public:
  void run() {
    form = std::unique_ptr<FormHelper>(
      new FormHelper(
        {
          FormField(1, 10, 4, 18, 0, 0).addUnderline().disableAutoskip()
        },
        {
          FormLabel(4, 10, "Something: "),
        }
      )
    );
    form->run();
  }
private:
  std::unique_ptr<FormHelper> form;
};

#endif
