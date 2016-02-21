#include <iostream>
#include <vector>
#include <assert.h>
#include <string>

#ifdef WIN32

#include <windows.h>

#else

#include <termios.h>
#include <unistd.h>

#endif

#include <uvpp/GlobalLoop.hpp>
#include <bufferednetworking/BufferedClient.hpp>

#include "LoginScreen.hpp"
#include "Application.hpp"
#include "InMemoryBackend.hpp"

using namespace textadventure;
using BufferedClient = bufferednetworking::BufferedClient;

void startLogin(InMemoryBackend::Backend& backend);
std::string getPassword();
// std::unique_ptr<IScreen> createLobbyScreen(Application& wrapper);

// Stolen from http://stackoverflow.com/a/1455007/538570
void setStdinEcho(bool enable = true) {
#ifdef WIN32
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  DWORD mode;
  GetConsoleMode(hStdin, &mode);

  if( !enable )
    mode &= ~ENABLE_ECHO_INPUT;
  else
    mode |= ENABLE_ECHO_INPUT;

  SetConsoleMode(hStdin, mode );

#else
  struct termios tty;
  tcgetattr(STDIN_FILENO, &tty);
  if( !enable )
    tty.c_lflag &= ~ECHO;
  else
    tty.c_lflag |= ECHO;

  (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
}

struct NewUserCredentials {
  std::string username;
  std::string password;
  NewUserCredentials(std::string username, std::string password) {
    this->username = username;
    this->password = password;
  }
};

NewUserCredentials getUserRegistrationInfo() {
  std::string username;
  std::string password;
  std::string passwordRepeat;

  std::cout << endl;

  do {
    std::cout << "Choose a username: ";
    std::cin >> username;
    if (username.size() < 1) {
      std::cout << "Your username is too short: " << endl;
    }
  } while (username.size() < 1);

  do {
    std::cout << "Choose a password: ";
    password = getPassword();

    std::cout << "Repeat chosen password: ";
    passwordRepeat = getPassword();
    if (password.compare(passwordRepeat) != 0) {
      std::cout << "The chosen password does not match with repeat" << endl;
    }
  } while (password.compare(passwordRepeat) != 0);

  NewUserCredentials credentials(username, password);
  return credentials;
}

int main() {
  uvpp::GlobalLoop::initializeLoop();

  // BufferedClient client;

  textadventure::InMemoryBackend backend;
  startLogin(backend);

  // Application wrapper;
  // wrapper.setScreen(
  //   createLobbyScreen(wrapper)
  // );
  // wrapper.start();

  // client.connect("127.0.0.1", 5000);

  return uvpp::GlobalLoop::runLoop();
}

void startLogin(InMemoryBackend::Backend& backend) {
  while (true) {
    if (!backend.getState().loggedIn) {
      std::cout << endl;
      std::cout << "You are not logged in. ";
      std::cout << "Pick the following options: " << endl << endl;
      std::cout << "\t1) to log in" << endl;
      std::cout << "\t2) to register" << endl << endl;
      std::cout << "> ";

      int option;
      std::cin >> option;
      if (option == 1) {
        std::cout << "Enter username: ";
        std::string username;
        std::cin >> username;

        std::cout << "Enter password: ";
        auto password = getPassword();

        backend.logIn(username, password);
        std::cout << backend.getState().error << endl;
      } else if (option == 2) {
        auto credentials = getUserRegistrationInfo();
        backend.registerUser(credentials.username, credentials.password);
        std::cout << backend.getState().error << endl;
      } else {
        std::cout << "Please pick either the option 1 or 2" << endl;
        continue;
      }
    } else {
      if (backend.getState().firstRun) {
        std::cout << "Entering game" << endl << endl;
        break;
      }
      std::cout << endl;

      if (backend.getState().message.length() > 0) {
        std::cout << backend.getState().message << endl << endl;
      }
    }
  }
}

std::string getPassword() {
  setStdinEcho(false);
  std::string password;
  std::cin >> password;
  setStdinEcho();
  std::cout << endl;
  return password;
}

// std::unique_ptr<IScreen> createLobbyScreen(Application& wrapper) {
//   return std::unique_ptr<IScreen>(new LobbyScreen(wrapper));
// }