#ifndef YASI_OUTPUTSOURCE_H
#define YASI_OUTPUTSOURCE_H

#include <string>

class OutputSource {
public:
    virtual ~OutputSource() = default;
    virtual void out(std::string) = 0;
};

#endif
