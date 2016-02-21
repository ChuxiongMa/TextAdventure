#ifndef ISCREEN_CHANGEABLE_H
#define ISCREEN_CHANGEABLE_H

#include <memory>

#include <ui/IScreen.hpp>

using IScreen = textadventure::IScreen;

class IScreenChangeable {
public:
  virtual void setScreen(std::unique_ptr<IScreen> screen) = 0;
};

#endif
