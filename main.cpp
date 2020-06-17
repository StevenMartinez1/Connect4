//
//  main.cpp
//  connect4C++
//
//  Created by Steven Martinez on 12/18/18.
//  Copyright © 2018 Steven Martinez. All rights reserved.
//

#include <iostream>
#include "gameboard.hpp"
#include "player.cpp"

int main(int argc, const char * argv[]) {
    game gameboard(ongoing);
    gameboard.createboard();
    gameboard.startGame();
    gameboard.deleteboard();
}
