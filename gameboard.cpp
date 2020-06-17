//
//  game.cpp
//  connect4C++
//
//  Created by Steven Martinez on 12/18/18.
//  Copyright © 2018 Steven Martinez. All rights reserved.
//

#include "gameboard.hpp"
#include <iostream>
#include <string>

void game::createboard()
{
    std::cout << "Enter the length and width of the board." << std::endl;
    std::cin >> boardlength >> boardwidth;
    
    while ((boardlength < 4) && (boardwidth < 4)) {
      
        std::cout << "Length and width must be at least size 4" << std::endl;
        std::cin >> boardlength >> boardwidth;
    }
    setLength(boardlength);
    setWidth(boardwidth);
    initializeboard();
    print_board();
}

void game::startGame()
{
    std::string Player1, Player2;
    std::cout << "What is the name of the red player?" << std::endl;
    std::cin >> Player1;
    std::cout << "What is the name of yellow player?" << std::endl;
    std::cin >> Player2;
    
    player redPlayer(Player1);
    player yellowPlayer (Player2);
    
    while(gameState == ongoing)
    {
        int chosenColumn;
        if(turn % 2 == 0)
        {
            std::cout << redPlayer.getName() << " choose a column to insert the token." << std::endl;
            std::cin >> chosenColumn;
            insertToken(chosenColumn, red);
        }
        else
        {
            std::cout << yellowPlayer.getName() << " choose a column to insert the token." << std::endl;
            std::cin >> chosenColumn;
            insertToken(chosenColumn, yellow);
        }
        
        print_board();
        turn++;
        decideGamestate();
    }
    
    declareOutcome(Player1, Player2);
}

void game::decideGamestate()
{
    //int redtarget = 0;
    //int yellowtarget = 0;
    bool redtarget = false;
    bool yellowtarget = false;
    
    if(turn >= (boardwidth * boardlength))                  // TIE
    {
        gameState = tie;
    }
    
    for(int i = 0; i < boardlength; i++)                    // Same Col
    {
        for(int j = 0; j < boardwidth; j++)
        {
            if(i >= 3)
            {
                if(board[i][j] == red && board[i-1][j] == red && board[i-2][j] == red && board[i-3][j] == red )
                    redtarget = true;
                
                else if(board[i][j] == yellow && board[i-1][j] == yellow && board[i-2][j] == yellow && board[i-3][j] == yellow)
                    yellowtarget = true;
            }
        }
    }
    
    for(int i = 0; i < boardlength; i++)                    // Same Row
    {
        for(int j = 0; j < boardwidth; j++)
        {
            if(j >= 3)
            {
                if(board[i][j] == red && board[i][j-1] == red && board[i][j-2] == red && board[i][j-3] == red )
                    redtarget = true;
            
                else if(board[i][j] == yellow && board[i][j-1] == yellow && board[i][j-2] == yellow && board[i][j-3] == yellow)
                    yellowtarget = true;
            }
        }
    }
    
    
    for(int i = 0; i < boardlength; i++)                    // Diagonal Down Right
    {
        for(int j = 0; j < boardwidth; j++)
        {
            if(j >= 3 && i>= 3)
            {
                if(board[i][j] == red && board[i-1][j-1] == red && board[i-2][j-2] == red && board[i-3][j-3] == red )
                    redtarget = true;
                
                else if(board[i][j] == yellow && board[i-1][j-1] == yellow && board[i-2][j-2] == yellow && board[i-3][j-3] == yellow)
                    yellowtarget = true;
            }
        }
    }
    
    for(int i = 0; i < boardlength; i++)                    // Diagonal Up Right
    {
        for(int j = 0; j < boardwidth; j++)
        {
            if((j+3) < boardwidth && i>= 3)
            {
                if(board[i][j] == red && board[i-1][j+1] == red && board[i-2][j+2] == red && board[i-3][j+3] == red )
                    redtarget = true;
                
                else if(board[i][j] == yellow && board[i-1][j+1] == yellow && board[i-2][j+2] == yellow && board[i-3][j+3] == yellow)
                    yellowtarget = true;
            }
        }
    }
    
    if(yellowtarget == true)
        gameState = yellowWins;
    if(redtarget == true)
        gameState = redWins;
}

void game::declareOutcome(std::string redname, std::string yellowname)
{
    if(gameState == tie)
        std::cout << "It's a tie!" << std::endl;
    
    if(gameState == redWins)
        std::cout << redname << " wins!" << std::endl;
   
    if(gameState == yellowWins)
        std::cout << yellowname << " wins!" << std::endl;
    
    if (gameState == ongoing)
        std::cout << "Error Somewhere :,(" << std::endl << std::endl << std::endl;
}

void game::insertToken(int col, token color)
{
    bool isInserted = false;
    
    for(int i = boardlength-1; i >= 0; i--)
    {
        if(board[i][col] == empty)
        {
            board[i][col] = color;
            isInserted = true;
            break;
        }
    }
    
    int newcol;
    while (!isInserted) {
        std::cout << "Column is full. Please pick another column." << std::endl;
        std::cin >> newcol;
        if(newcol >= boardwidth || newcol < 0)
        {
            std::cout << "Choose an appropriate column." << std::endl;
            continue;
        }
        for(int i = boardlength-1; i >= 0; i--)
        {
            if(board[i][newcol] == empty)
            {
                board[i][newcol] = color;
                isInserted = true;
                break;
            }
        }
    }
}

void game::print_board()
{
    int col = 0;
    
    for(int i = 0; i < boardlength; i++)
    {
        std::cout << "|";
        for(int j = 0; j < boardwidth; j++)
        {
           if(board[i][j] == empty)
               std::cout << " |";
            
           if(board[i][j] == red)
               std::cout << "R|";
            
           if(board[i][j] == yellow)
               std::cout << "Y|";
        }
        std::cout << std::endl;
    }
    
    for(int k = 0; k < (boardwidth * 2 +1); k++)
        std::cout << "=";
    
    std::cout << std::endl;
    
    for(int k = 0; k < (boardwidth * 2 +1); k++)
    {
        if(k % 2 == 0)
            std::cout << " ";
        else
        {
            std::cout << col;
             col++;
        }
    }
    std::cout << std::endl;
}

void game::initializeboard()
{
    board = new token*[boardlength];
    for(int i = 0; i < boardlength; i++)
    {
        board[i] = new token[boardwidth];
    }
    
    for (int i = 0; i < boardlength; i++)
    {
        for(int j = 0; j < boardwidth; j++)
        {
            board[i][j] = empty;
        }
    }
}

void game::deleteboard()
{
    for(int i = 0; i < boardlength; i++)
    {
        delete[] board[i];
    }
    delete[] board;
    std::cout << "Game Over. \nGameboard has been deleted." << std::endl;
}
