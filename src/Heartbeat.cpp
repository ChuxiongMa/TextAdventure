#include <memory>

#include <Heartbeat.hpp>
#include <uvpp/GlobalLoop.hpp>

using GlobalLoop = uvpp::GlobalLoop;

namespace textadventure {
  Heartbeat::Heartbeat(IUpdateable& logic)
    : Heartbeat(logic, Heartbeat::defaultTimeout) {}
  Heartbeat::Heartbeat(IUpdateable& logic, int timeout)
    : timeout(timeout)
    , logic(&logic) {}

  void Heartbeat::start() {
    queueWork();
  }

  const int Heartbeat::defaultTimeout = 100;

  void Heartbeat::queueWork() {
    GlobalLoop::setTimeout(timeout, [=](){
      logic->update();
      if (!logic->hasStopped()) {
        queueWork();
      }
    });
  }
}
