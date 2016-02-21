#ifndef GLOBAL_LOOP_H
#define GLOBAL_LOOP_H

#include <functional>

#include <uv.h>

#include "Loop.hpp"

using ParameterLessCallback = std::function<void (void)>;

namespace uvpp {

  // TODO: refactor this code even further so that the `initializeLoop` isn't
  //   even required.

  /**
   * Usage:
   *
   *     GlobalLoop::initializeLoop();
   *
   *     // Use event-loop related stuff here.
   *
   *     int runResult = GlobalLoop::runLoop();
   */
  class GlobalLoop {
    static Loop loop;

  public:

    /**
     * Initializes the main libuv event loop.
     */
    static void initializeLoop();
    static void initializeLoop(Loop loop);

    /**
     * Runs the loop.
     */
    static int runLoop();

    /**
     * Gets the global libuv loop instance. Use this method sparingly.
     */
    static uv_loop_t* getUVLoop();

    /**
     * Gets the loop instance.
     */
    static Loop* getLoop();

    /**
     * Defers the specific callback until the next loop.
     */
    static void defer(std::function<void (void)>);
    static void defer(uvpp::Loop&, std::function<void (void)>);

    /**
     * Calls the specified callback after the specified elapsed time. The
     * callback is thrown into the event loop.
     */
    static void setTimeout(int time, ParameterLessCallback);
    static void setTimeout(uvpp::Loop&, int time, ParameterLessCallback);

    /**
     * Performs the tasks specified in the work callback.
     */
    static void doWork(
      std::function<void* (void)> work,
      std::function<void (void*)> callback
    );
    static void doWork(
      uvpp::Loop& loop,
      std::function<void* (void)> work,
      std::function<void (void*)> callback
    );
  };
}

#endif
