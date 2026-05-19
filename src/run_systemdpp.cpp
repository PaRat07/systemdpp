#include <iostream>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  if (fork()) {
    execlp("_systemdpp-daemon", "_systemdpp-daemon", nullptr);
    _exit(1);
  } else {
    execlp("zsh", "zsh", nullptr);
    _exit(1);
  }
}