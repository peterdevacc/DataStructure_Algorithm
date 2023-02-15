// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter Dev on 2023/2/12.
//

#ifndef EX_TOP_DOWN_DYNAMIC_H
#define EX_TOP_DOWN_DYNAMIC_H

#include "core_dynamic.h"

namespace Ex::Dynamic {

    std::pair<unsigned long long, unsigned long> get_fibonacci_top_down(uint16_t position) {
        unsigned long long result = 0;
        unsigned long stepCounter = 2;

        std::vector<unsigned long> cache(position + 1, 0);

        auto fibonacci = [&cache](uint16_t position){
            if (position == 0 || position == 1) {
                cache[position] = position;
                return static_cast<unsigned long>(position);
            }

            if (cache[position] == 0) {
                cache[position] = cache[position - 1] + cache[position - 2];
            }
            return cache[position];
        };

        std::stack<std::function<unsigned long()>> st{};
        while (position > 0) {
            st.emplace(
                [fibonacci, position] {
                    return fibonacci(position);
                }
            );
            position--;
        }

        while (!st.empty()) {
            auto fibonacciStep = st.top();
            fibonacciStep();
            stepCounter++;

            st.pop();
        }

        result = cache.back();
        stepCounter -= 2;

        return std::make_pair(result, stepCounter);
    }


}

#endif //EX_TOP_DOWN_DYNAMIC_H
