#include <functional>
#include <memory>
#include <stdint.h>
#include <iostream>

#include <uv.h>

#include "uvpp/GlobalLoop.hpp"

uvpp::Loop uvpp::GlobalLoop::loop;

using ParameterLessCallback = std::function<void (void)>;

void uvpp::GlobalLoop::initializeLoop() {
  uvpp::GlobalLoop::initializeLoop(uvpp::Loop());
}

void uvpp::GlobalLoop::initializeLoop(uvpp::Loop loop) {
  uvpp::GlobalLoop::loop = loop;
  uvpp::GlobalLoop::loop.initialize();
}

int uvpp::GlobalLoop::runLoop() {
  return uvpp::GlobalLoop::loop.runLoop();
}

uv_loop_t* uvpp::GlobalLoop::getUVLoop() {
  return uvpp::GlobalLoop::loop.getLoop();
}

uvpp::Loop* uvpp::GlobalLoop::getLoop() {
  return &uvpp::GlobalLoop::loop;
}

void uvpp::GlobalLoop::defer(ParameterLessCallback callback) {
  uvpp::GlobalLoop::defer(uvpp::GlobalLoop::loop, callback);
}

void uvpp::GlobalLoop::defer(
  uvpp::Loop& loop,
  ParameterLessCallback callback
) {
  loop.defer(callback);
}

void uvpp::GlobalLoop::setTimeout(int time, ParameterLessCallback callback) {
  uvpp::GlobalLoop::setTimeout(uvpp::GlobalLoop::loop, time, callback);
}

void uvpp::GlobalLoop::setTimeout(
  uvpp::Loop& loop,
  int timeout,
  ParameterLessCallback callback
) {
  loop.setTimeout(timeout, callback);
}

using WorkCallback = std::function<void* (void)>;
using PostWorkCallback = std::function<void (void*)>;

void uvpp::GlobalLoop::doWork(
  std::function<void* (void)> work,
  std::function<void (void*)> callback
) {
  uvpp::GlobalLoop::doWork(uvpp::GlobalLoop::loop, work, callback);
}

void uvpp::GlobalLoop::doWork(
  uvpp::Loop& loop,
  WorkCallback workCallback,
  PostWorkCallback callback
) {
  loop.doWork(workCallback, callback);
}
