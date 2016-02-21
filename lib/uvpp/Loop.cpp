#include <uv.h>

#include "uvpp/Loop.hpp"

const int uvpp::Loop::minDeferSkipTime = 1;

void uvpp::Loop::initialize() {
  uv_loop_init(&loop);
}

uv_loop_t* uvpp::Loop::getLoop() {
  return &loop;
}

int uvpp::Loop::runLoop() {
  return uv_run(&loop, UV_RUN_DEFAULT);
}

void uvpp::Loop::defer(ParameterLessCallback callback) {
  // So, as it turns out, libuv prioritizes timer events over I/O. So this
  // means that the moment there is a timer event in the queue, the event with
  // the lowest timeout is what libuv will set as its *own* timeout for I/O
  // polling. So this means that calling setTimeout recursively will
  // essentially starve the I/O poller, and we will never know if we ever got
  // any TCP packet.
  setTimeout(uvpp::Loop::minDeferSkipTime, callback);
}

struct DeferContainer {
  ParameterLessCallback callback;
  DeferContainer(ParameterLessCallback callback) : callback(callback) {}
};

void uvpp::Loop::timerDone(uv_timer_t* handle) {
  reinterpret_cast<DeferContainer *>(handle->data)->callback();
  delete handle;
}

void uvpp::Loop::setTimeout(int timeout, ParameterLessCallback callback) {
  uv_timer_t *handle = new uv_timer_t;
  uv_timer_init(&loop, handle);
  handle->data = new DeferContainer(callback);
  uv_timer_start(handle, timerDone, timeout, 0);
}

using WorkCallback = std::function<void* (void)>;
using PostWorkCallback = std::function<void (void*)>;

struct WorkContainer {
  WorkCallback work;
  PostWorkCallback callback;
  WorkContainer(WorkCallback work, PostWorkCallback callback)
    : work(work)
    , callback(callback) {}
};

struct PostWorkContainer {
  PostWorkCallback callback;
  void* result;
  PostWorkContainer(PostWorkCallback callback, void* result)
    : callback(callback)
    , result(result) {}
};

void uvpp::Loop::work(uv_work_t* req) {
  auto container = reinterpret_cast<WorkContainer*>(req->data);
  req->data = new PostWorkContainer(container->callback, container->work());
  delete container;
}

void uvpp::Loop::postWork(uv_work_t *req, int status) {
  auto container = reinterpret_cast<PostWorkContainer*>(req->data);
  container->callback(container->result);

  delete reinterpret_cast<PostWorkContainer*>(req->data);
  delete req;
}

void uvpp::Loop::doWork(
  WorkCallback workCallback,
  PostWorkCallback callback
) {
  uv_work_t *req = new uv_work_t;
  req->data = new WorkContainer(workCallback, callback);
  uv_queue_work(
    &loop,
    req,
    work,
    postWork
  );
}
