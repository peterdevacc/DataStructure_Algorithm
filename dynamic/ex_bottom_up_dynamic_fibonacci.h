// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter Dev on 2023/2/12.
//

#ifndef EX_BOTTOM_UP_DYNAMIC_H
#define EX_BOTTOM_UP_DYNAMIC_H

#include "core_dynamic.h"

namespace Ex::Dynamic {

    std::pair<unsigned long long, unsigned long> get_fibonacci_bottom_up(uint16_t position) {
        unsigned long long result = 0;
        unsigned long stepCounter = 2;

        unsigned long first = 0;
        unsigned long second = 1;
        for (int i = 2; i < position; ++i) {
            result = first + second;
            first = second;
            second = result;

            stepCounter++;
        }

        if (position == 1) {
            result = 1;
            stepCounter = 3;
        } else {
            result = first + second;
        }
        stepCounter -= 1;

        return std::make_pair(result, stepCounter);
    }

}

#endif //EX_BOTTOM_UP_DYNAMIC_H
