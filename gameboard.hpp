//
//  game.hpp
//  connect4C++
//
//  Created by Steven Martinez on 12/18/18.
//  Copyright © 2018 Steven Martinez. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include <stdio.h>
#include "player.hpp"

enum token {red, yellow, empty};
enum currentgamestate {ongoing, tie, redWins, yellowWins};

class game
{
private:
    int turn;
    int boardlength;
    int boardwidth;
    currentgamestate gameState;
    token** board;
    
public:
    game(currentgamestate gamestate1)
    {
        gameState = gamestate1;
    }
    
    int getTurn()
    {
        return turn;
    }
    
    int getWidth()
    {
        return boardwidth;
    }
    
    int getLength()
    {
        return boardlength;
    }
    
    void setLength(int len)
    {
        boardlength = len;
    }
    
    void setWidth(int wid)
    {
        boardwidth = wid;
    }
    
    currentgamestate getGamestate()
    {
        return gameState;
    }
    
    void setGameState();
    
    void initializeboard();
    void createboard();
    void print_board();
    void deleteboard();
    void insertToken(int col, token color);
    void decideGamestate();
    void declareOutcome(std::string redname, std::string yellowname);
    void startGame();
};

#endif /* game_hpp */

