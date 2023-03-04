#include"Game.h"
#include"Grid.h"
#include<iostream>
#include <fstream>
#include <string>
using namespace std;

Grid::Grid(){}
Grid::Grid(int row,int col)
{
    setRowsize(row);
    setColsize(col);
    setBoard();

}

Grid::~Grid()
{
    delete board;
    //dtor

}

int Grid::getCell(int row, int col)
{
    return board[row + getRowsize()*col];//returns to the value of the cell
}

void Grid::setCell(int row,int col,int value)
{
    board[row + getRowsize()*col] = value;//changes the value of the cell
}

void Grid::printGrid()
{//prints the whole grid to terminal
    for(int i=0;i<getRowsize();i++){
        for(int k=0;k<getColsize();k++){
            cout<< getCell(i,k)<<" ";
        }
        cout<<endl;
    }
}
void Grid::setBoard()
{//initializes to values of grid to zero
    board=new int[getRowsize()*getColsize()];
    for(int i=0;i<getRowsize();i++){
        for(int k=0;k<getColsize();k++){
            setCell(i,k,0);
        }
    }
}

//getters and setters
void Grid::setColsize(int col){colsize=col;}
void Grid::setRowsize(int row){rowsize=row;}
int Grid::getColsize(){return colsize;}
int Grid::getRowsize(){  return rowsize;}

