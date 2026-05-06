#include <cstdlib>

#include <iostream>

int main(int argc, char** argv) {
    if (argc == 1) {
        std::cerr << "No subcommand supplied, exiting. Try --help\n";
        return 1;
    }
}
