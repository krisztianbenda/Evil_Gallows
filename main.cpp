//
//  main.cpp
//  Evil_Gallows
//
//  Created by Benda Krisztián on 2017. 05. 02..
//  Copyright © 2017. Benda Krisztián. All rights reserved.
//

#include "Gallows.hpp"

int main(int argc, const char * argv[]) {
    Gallows gallows("dictionary.txt");
    gallows.play();
    return 0;
}
