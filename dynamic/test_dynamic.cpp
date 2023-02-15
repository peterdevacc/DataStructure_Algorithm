// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter Dev on 2023/2/12.
//

#include "ex_top_down_dynamic_fibonacci.h"
#include "ex_bottom_up_dynamic_fibonacci.h"

void Ex::test_dynamic() {

    auto resultTopDown = Dynamic::get_fibonacci_top_down(12);
    assert(resultTopDown.first == 144);
    assert(resultTopDown.second == 12);

    auto resultBottomUp = Dynamic::get_fibonacci_bottom_up(12);
    assert(resultBottomUp.first == 144);
    assert(resultBottomUp.second == 11);

}
