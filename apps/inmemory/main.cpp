#include <iostream>
#include "CLIFrontend.hpp"
#include "InMemoryBackend.hpp"

using namespace std;

int main() {
  textadventure::CLIFrontend ui;
  textadventure::InMemoryBackend backend;
  return ui.start(backend);
}
