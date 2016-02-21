#ifndef LOOP_H
#define LOOP_H

#include <functional>
#include <deque>

#include <uv.h>

using ParameterLessCallback = std::function<void (void)>;

namespace uvpp {
  class Loop {
    uv_loop_t loop;
    bool shouldRequestIOPollSkip;

    static void work(uv_work_t* req);
    static void postWork(uv_work_t *req, int status);
    static void timerDone(uv_timer_t* handle);

  public:
    static const int minDeferSkipTime;

    void initialize();
    int runLoop();
    uv_loop_t* getLoop();
    void defer(ParameterLessCallback);
    void setTimeout(int time, ParameterLessCallback);
    void doWork(
      std::function<void* (void)> work,
      std::function<void (void*)> callback
    );
  };
}

#endif
