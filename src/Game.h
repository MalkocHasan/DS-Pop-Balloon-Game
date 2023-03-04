#include "Grid.h"
#include <vector>
#include<iostream>
#include <string>
#ifndef GAME_H
#define GAME_H

using namespace std;
class Game
{
    private:
        Grid grid;
        Grid grid2;
        int points;
        vector<int> linkCoords;

    public:
        string inputFile1;
        string inputFile2;
        string outputFile;
        Game(string input1,string input2,string output);
        virtual ~Game();
        void printFinalGame();
        void putBalloons();
        void puttingTheBombs();
        void bomb(int initialRow,int initalCol);
        bool linkCheck(int initialRow,int initialCol,int *linkCount);
        bool checkExists(int targetRow,int targetCol);
        void popBalloons(int initialRow, int initialCol,int *linkcount);

    protected:

};

#endif // GAME_H
