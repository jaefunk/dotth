//
//  main.cpp
//  testdotth
//
//  Created by jwkim on 26/09/2019.
//  Copyright © 2019 dotth. All rights reserved.
//

#include <iostream>

#include "dotth.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    auto kk = dotth::test(1, 3);
    std::cout << "Hello, World! %d\n" ;
    dotth::test2(123);
    return 0;
}
