#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include <memory>

#include "IUpdateable.hpp"

namespace textadventure {

  /**
   * The heartbeat will serve as the base class for the game logic.
   */
  class Heartbeat {
  public:
    Heartbeat(IUpdateable& logic);
    Heartbeat(IUpdateable& logic, int timeout);
    void start();

  private:
    int timeout;
    IUpdateable* logic;

    static const int defaultTimeout;

    void queueWork();
  };
}

#endif
