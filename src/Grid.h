#ifndef GRID_H
#define GRID_H

#include <string>

class Grid
{
    private:
        int rowsize,colsize;
        int* board;
    public:
        Grid();
        Grid(int row,int col);
        virtual ~Grid();

        void setBoard();//initializes to values of grid to zero
        void setRowsize(int row);
        void setColsize(int col);
        int getRowsize();
        int getColsize();

        void printGrid();//prints the whole grid to terminal
        void setCell(int row,int col,int value);//changes the value of the cell
        int getCell(int col, int row);//returns to the value of the cell
    protected:


};

#endif // GRID_H
