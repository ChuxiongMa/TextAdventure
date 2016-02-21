#include <vector>
#include <assert.h>
#include <string>
#include <memory>

#include <uvpp/GlobalLoop.hpp>
#include <ui/FormField.hpp>
#include <ui/FormLabel.hpp>
#include <ui/FormHelper.hpp>
#include <ui/WindowWrapper.hpp>
#include <ui/IScreen.hpp>

using FormHelper = textadventure::FormHelper;
using FormLabel = textadventure::FormLabel;
using FormField = textadventure::FormField;
using WindowWrapper = textadventure::WindowWrapper;
using IScreen = textadventure::IScreen;

class IScreenChangeable {
public:
  virtual void changeScreen(std::unique_ptr<IScreen> screen) = 0;
};

class LobbyScreen: public IScreen {
public:
  void run() {
    FormHelper form(
      {
        FormField(1, 10, 4, 18, 0, 0).addUnderline().disableAutoskip()
      },
      {
        FormLabel(4, 10, "Something: "),
      }
    );
    form.run();
  }
};

class FormScreen: public IScreen {
public:
  FormScreen(IScreenChangeable& changeable) {
    this->changeable = &changeable;
  }
  void run() {
    FormHelper form(
      {
        FormField(1, 10, 4, 18, 0, 0).addUnderline().disableAutoskip(),
        FormField(1, 10, 6, 18, 0, 0).addUnderline().disableAutoskip()
      },
      {
        FormLabel(4, 10, "Value 1: "),
        FormLabel(6, 10, "Value 2: ")
      }
    );
    form.onDone([=]() {
      auto newScreen = new LobbyScreen();
      newScreen->run();
      this->changeable->changeScreen(std::unique_ptr<IScreen>(newScreen));
    });
    form.run();
  }
private:
  IScreenChangeable* changeable;
};

class Application: public IScreenChangeable, public WindowWrapper {
public:
  Application()
    : WindowWrapper() {}

  void runScreen(std::unique_ptr<IScreen> screen) {
    currentScreen = std::move(screen);
    currentScreen->run();
  }

  void changeScreen(std::unique_ptr<IScreen> screen) {
    currentScreen = std::move(screen);
    currentScreen->run();
  }
private:
  std::unique_ptr<IScreen> currentScreen;
};

int main() {
  uvpp::GlobalLoop::initializeLoop();

  Application wrapper;
  wrapper.runScreen(std::unique_ptr<IScreen>(new FormScreen(wrapper)));

  return uvpp::GlobalLoop::runLoop();
}
