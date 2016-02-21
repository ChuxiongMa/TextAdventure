#ifndef IUPDATEABLE_H
#define IUPDATEABLE_H

namespace textadventure {
  class IUpdateable {
  public:
    /**
     * This will act as the updatable's "main loop".
     */
    virtual void update() = 0;

    /**
     * This notifies the client code whether or not the game has stopped.d
     *
     * @returns whether or not the game has stopped.
     */
    virtual bool hasStopped() = 0;
  };
}

#endif
