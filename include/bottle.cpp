//
// Created by zeros on 14.04.2025.
//

#include "bottle.h"

bottle::bottle(const int f, const int c): filling(f), capping(c) {}

int bottle::get_filling() const {
    return filling;
}

int bottle::get_capping() const {
    return capping;
}
