#ifndef FILES_H
#define FILES_H

#include <stdio.h>
#include <string>

long filesize(FILE* f);

//You have to free whatever this returns
std::string read_source(const char* f);

#endif //FILES_H
