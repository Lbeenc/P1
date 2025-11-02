#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "scanner.h"


static void usageAndExit(const char* msg=nullptr) {
if (msg) std::cerr << msg << "\n";
std::cerr << "Usage: P1 [file]\n";
std::exit(EXIT_FAILURE);
}


int main(int argc, char** argv) {
if (argc > 2) usageAndExit("Too many arguments.");


if (argc == 2) {
const char* path = argv[1];
FILE* f = std::fopen(path, "r");
if (!f) usageAndExit("Cannot open input file.");
initScanner(f);
} else {
// read from stdin
initScanner(nullptr);
}


return testScanner();
}
