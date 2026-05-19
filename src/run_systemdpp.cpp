#include <iostream>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  if (fork()) {
    execlp("systemdpp-daemon", "systemdpp-daemon", nullptr);
    _exit(1);
  } else {
    execlp("zsh", "zsh", nullptr);
    _exit(1);
  }
}