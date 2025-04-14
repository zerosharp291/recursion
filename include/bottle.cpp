//
// Created by zeros on 14.04.2025.
//

#include "bottle.h"

bottle::bottle(const unsigned long f, const unsigned long c): filling(f), capping(c) {}

unsigned long bottle::get_filling() const {
    return filling;
}

unsigned long bottle::get_capping() const {
    return capping;
}

unsigned long bottle::get_processing_time() const {
    return filling + capping;
}
