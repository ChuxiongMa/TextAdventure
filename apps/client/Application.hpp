#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>

#include <ui/WindowWrapper.hpp>
#include <uvpp/GlobalLoop.hpp>

#include "IScreenChangeable.hpp"

using GlobalLoop = uvpp::GlobalLoop;

using WindowWrapper = textadventure::WindowWrapper;

class Application: public IScreenChangeable, public WindowWrapper {
public:
  Application()
    : WindowWrapper() {}

  void setScreen(std::unique_ptr<IScreen> screen) {
    currentScreen = std::move(screen);
  }

  void start() {
    queueWork();
  }
private:
  std::unique_ptr<IScreen> currentScreen;

  void queueWork() {
    GlobalLoop::defer([=]() {
      currentScreen->run();
      queueWork();
    });
  }
};

#endif
