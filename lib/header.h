#ifndef HEADER_H
#define HEADER_H

#include "static_config.h"

struct header {
        char key[MAX_HEADER_KEY_SIZE];
        char value[MAX_HEADER_VALUE_SIZE];
};

#endif
