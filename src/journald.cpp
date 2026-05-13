#include <journald.hpp>

#include <chrono>
#include <ctime>
#include <errno.h>
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>

static const std::string journal_filename =
    std::format("{}/journal.log", journald::basedir);

static std::ofstream journal_file;
static std::mutex journal_file_mutex;

void ProcessJournalerWorker(std::string filename) {
    std::string cmd = std::format("{}/logger.sh {}", journald::basedir, filename);
    std::cout << cmd << std::endl;
  system(cmd.c_str());
}

#define MAX_EVENTS 1024
#define LEN_NAME 16
#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (MAX_EVENTS * (EVENT_SIZE + LEN_NAME))

void JournalProcess() {
  int i = 0;
  int length;
  int fd;
  int wd;
  char buffer[BUF_LEN];
  fd = inotify_init();
  wd = inotify_add_watch(fd, journald::basedir.c_str(), IN_CREATE);

  while (true) {
    i = 0;
    length = read(fd, buffer, BUF_LEN);

    struct inotify_event *event = (struct inotify_event *)&buffer[i];

    if (event->len) {
      if (event->mask & IN_CREATE) {
        if (event->mask & IN_ISDIR) {
          printf("Ignoring directory %s\n", event->name);
        } else {
          printf("Watching file %s\n", event->name);
          std::string filename = std::format("{}/{}", journald::basedir, std::string(event->name));
          std::thread([filename] {
            ProcessJournalerWorker(filename);
          }).detach();
        }
      }

      i += EVENT_SIZE + event->len;
    }
  }
}

int main(int argc, char **argv) {
  mkdir(journald::basedir.c_str(), 0644);

  journal_file = std::ofstream(journal_filename);

  JournalProcess();
}
