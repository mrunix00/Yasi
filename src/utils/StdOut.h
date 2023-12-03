#ifndef YASI_STDOUT_H
#define YASI_STDOUT_H

#include "utils/OutputSource.h"
#include <string>

class StdOut : public OutputSource {
    void out(std::string);
};

#endif
