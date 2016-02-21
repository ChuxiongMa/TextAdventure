#include <iostream>
#include <vector>

#ifdef WIN32

#include <windows.h>

#else

#include <termios.h>
#include <unistd.h>

#endif

#include <boost/algorithm/string.hpp>

#include <deque>
#include "CLIFrontend.hpp"
#include "Backend.hpp"
#include "Room.hpp"

using namespace std;

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

string getPassword() {
  setStdinEcho(false);
  string password;
  cin >> password;
  setStdinEcho();
  cout << endl;
  return password;
}

struct NewUserCredentials {
  string username;
  string password;
  NewUserCredentials(string username, string password) {
    this->username = username;
    this->password = password;
  }
};

NewUserCredentials getUserRegistrationInfo() {
  string username;
  string password;
  string passwordRepeat;

  cout << endl;

  do {
    cout << "Choose a username: ";
    cin >> username;
    if (username.size() < 1) {
      cout << "Your username is too short: " << endl;
    }
  } while (username.size() < 1);

  do {
    cout << "Choose a password: ";
    password = getPassword();

    cout << "Repeat chosen password: ";
    passwordRepeat = getPassword();
    if (password.compare(passwordRepeat) != 0) {
      cout << "The chosen password does not match with repeat" << endl;
    }
  } while (password.compare(passwordRepeat) != 0);

  NewUserCredentials credentials(username, password);
  return credentials;
}

bool isActionHelp(const string &action) {
  vector<string> actionArguments;
  boost::split(actionArguments, action, boost::is_any_of(" "));
  return actionArguments[0].compare("help") == 0;
}

string promptUser() {
  string action;

  while (action.size() == 0 || isActionHelp(action)) {
    cout << "Type 'help' for a list of commands" << endl;
    cout << endl;
    cout << "> ";
    string newAction;
    getline(cin, action);

    if (isActionHelp(action)) {
      cout << endl << "Here are all your help" << endl << endl;
      cout << "\tgo (north|east|west|south)" << endl << endl;
    }
  }

  return action;
}

void displayDoors(std::deque<textadventure::Door> doors) {
  /*if (!(~doors.north) && !(~doors.east) && !(~doors.west) && !(~doors.south)) {
    cout << "You are trapped!" << endl << endl;
    return;
  }

  cout << "Doors available" << endl << endl;
  if (~doors.north) {
    cout << "\tnorth" << endl;
  }

  if (~doors.east) {
    cout << "\teast" << endl;
  }

  if (~doors.west) {
    cout << "\twest" << endl;
  }

  if (~doors.south) {
    cout << "\nsouth" << endl;
  }
  cout << endl;*/
}

int textadventure::CLIFrontend::start(Backend& backend) {
  // TODO: the architecture might need some revamping here. So far, the code
  //   assumes that all actions will be synchronous, where as this isn't true.
  //   Actions may be asynchronous, and the following code needs to handle
  //   that.

  while (true) {
    if (!backend.getState().loggedIn) {
      cout << endl;
      cout << "You are not logged in. ";
      cout << "Pick the following options: " << endl << endl;
      cout << "\t1) to log in" << endl;
      cout << "\t2) to register" << endl << endl;
      cout << "> ";

      int option;
      cin >> option;
      if (option == 1) {
        cout << "Enter username: ";
        string username;
        cin >> username;

        cout << "Enter password: ";
        auto password = getPassword();

        backend.logIn(username, password);
        cout << backend.getState().error << endl;
      } else if (option == 2) {
        auto credentials = getUserRegistrationInfo();
        backend.registerUser(credentials.username, credentials.password);
        cout << backend.getState().error << endl;
      } else {
        cout << "Please pick either the option 1 or 2" << endl;
        continue;
      }
    } else {
      if (backend.getState().firstRun) {
        cout << "Welcome to text adventure" << endl;

        // This is to avoid the ending "newline" character from being read.
        cin.ignore();
      }
      cout << endl;

      if (backend.getState().message.length() > 0) {
        cout << backend.getState().message << endl << endl;
      }

      cout << "You are in:" << endl << endl;
      cout << backend.getState().room.getDescription() << endl << endl;
      displayDoors(backend.getState().room.getDoors());
      auto action = promptUser();
      backend.handleAction(action);
    }
  }
  return 0;
}
