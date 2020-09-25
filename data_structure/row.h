#ifndef DATA_STRUCTURE_ROW_H
#define DATA_STRUCTURE_ROW_H

#include "key_value.h"

struct row {
        struct key_value columns[16];
};

#endif
