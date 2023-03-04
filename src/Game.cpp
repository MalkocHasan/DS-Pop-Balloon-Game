#include"Game.h"
#include"Grid.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include <vector>
#include <string>
using namespace std;


Game::Game(string input1,string input2,string output)
{
    inputFile1=input1;
    inputFile2=input2;
    outputFile=output;
    points=0;
    putBalloons();//part 1
    puttingTheBombs();//part2




}

Game::~Game()
{
    grid.~Grid();
    grid2.~Grid();
    linkCoords.clear();
    //dtor
}

void Game::printFinalGame()
{
    fstream of(outputFile.c_str(), ios::out);
    if(!of){
        cout<<"File creation failed";
    }
    else
    {
        of<<"PART 1:"<<endl;
        for(int i=0;i<grid.getRowsize();i++){//print grid1
            for(int k=0;k<grid.getColsize();k++){
                of<< grid.getCell(i,k)<<" ";
            }
            of<<endl;
        }
        of<<"\nPART 2:"<<endl;
        for(int x=0;x<grid2.getRowsize();x++){//print grid2
            for(int y=0;y<grid2.getColsize();y++){
                of<< grid2.getCell(x,y)<<" ";
            }
            of<<endl;
        }
        of<<"Final Points: "<<points<<"p"<<endl;
        of.close();
    }

}



void Game::putBalloons()
{

    fstream if1(inputFile1.c_str(), ios::in);
    string line;

    if(if1.is_open()){
        getline(if1,line);
        int N;
        stringstream ss;//build the grid
        ss<<line;
        ss>>N;
        grid.setColsize(N);
        grid.setRowsize(N);
        grid.setBoard();

        int numbers[3];
        while(!if1.eof()){//put the balloons
            getline (if1, line);
            stringstream ss1,ss2,ss3;
            string strRow,strCol,strValue;
            int i=0;
            for(i=0;i<line.size();i++){
                if(line[i]!=' '){
                    strValue=strValue+line[i];
                }else{
                    break;
                }
            }
            int k=i+1;
            for(k=i+1;k<line.size();k++){
                if(line[k]!=' '){
                    strRow=strRow+line[k];
                }else{
                    break;
                }
            }
            for(int j=k+1;j<line.size();j++){
                if(line[j]!=' '){
                    strCol=strCol+line[j];
                }else{
                    break;
                }
            }
            ss1<<strValue;
            ss1>>numbers[0];//value
            ss2<<strRow;
            ss2>>numbers[1];//row
            ss3<<strCol;
            ss3>>numbers[2];//col
            grid.setCell(numbers[1],numbers[2],numbers[0]);//put the balloon to the cell

            linkCoords.clear();
            int zero=0;
            int *linkCount=&zero;
            while(linkCheck(numbers[1],numbers[2],linkCount)){
                popBalloons(numbers[1],numbers[2],linkCount);
                linkCoords.clear();
                int *linkCount=&zero;
                if(!linkCheck(numbers[1],numbers[2],linkCount)) break;
            }

        }
        if1.close();
    }


}

void Game::puttingTheBombs()
{
    fstream if2(inputFile2.c_str(), ios::in);
    string line;
    if(!if2) {
        cout<<"No such file"<<inputFile2<<endl;
    } else {
        stringstream ss;//build the grid
        int N;
        getline (if2, line);
        ss<<line;
        ss>>N;
        grid2.setColsize(N);
        grid2.setRowsize(N);
        grid2.setBoard();
        for(int row=0;row<N;row++){//we will set the grid here
            getline (if2, line);
            int i=0;
            int col=0;
            string strId;
            for(i=i;i<line.size();i++){
                if(line[i]==' '){
                    stringstream sstream;
                    int value;
                    sstream<<strId;
                    sstream>>value;
                    grid2.setCell(row,col,value);
                    col++;
                    strId.clear();
                    if(i>=line.size()) break;
                }else{
                    strId=strId+line[i];
                }
            }
            stringstream sstream;
            int value;
            sstream<<strId;
            sstream>>value;
            grid2.setCell(row,col,value);
        }
        while (getline (if2, line)) {//we will put the bombs here

            stringstream ss1,ss2;
            int initialRow,initialCol;
            string strRow,strCol;
            int i=0;
            for(i=0;i<line.size();i++){
                if(line[i]!=' '){
                    strRow=strRow+line[i];
                }else{
                    break;
                }
            }
            for(int k=i+1;k<line.size();k++){
                if(line[k]!=' '){
                    strCol=strCol+line[k];
                }else{
                    break;
                }
            }
            ss1<<strRow;
            ss2<<strCol;
            ss1>>initialRow;
            ss2>>initialCol;
            bomb(initialRow,initialCol);
        }

        printFinalGame();
        if2.close();
    }
}

void Game::bomb(int initialRow,int initialCol)
{
    int balloonId = grid2.getCell(initialRow,initialCol);
    grid2.setCell(initialRow,initialCol,0);
    points+=balloonId;

    //check horizontal,vertical and diagonal
    for(int i=-1;i<=1;i++){
        for(int k=-1;k<=1;k++){
            if(!(i==0&&k==0)){
                int targetRow=initialRow+i;
                int targetCol=initialCol+k;
                while(targetRow>-1 &&targetRow<grid2.getRowsize()&&targetCol>-1 && targetCol<grid2.getColsize()){
                    if(grid2.getCell(targetRow,targetCol)==balloonId){
                        points+=grid2.getCell(targetRow,targetCol);
                        grid2.setCell(targetRow,targetCol,0);
                    }
                targetRow=targetRow+i;
                targetCol=targetCol+k;
                }
            }
        }
    }

}

bool Game::linkCheck(int initialRow,int initialCol,int *linkCount)
{

    int value=grid.getCell(initialRow,initialCol);
    int targetRow,targetCol;
    //check left
    targetRow=initialRow;
    targetCol=initialCol-1;
    if(targetRow>-1 &&targetRow<grid.getRowsize()&&targetCol>-1 && targetCol<grid.getColsize()){
        if(grid.getCell(targetRow,targetCol)==value){//checks if it links with the same value
            if(!checkExists(targetRow,targetCol)){
                linkCoords.push_back(targetRow);
                linkCoords.push_back(targetCol);
                (*linkCount)++;
                linkCheck(targetRow,targetCol,linkCount);
            }
        }
    }

    //check right
    targetRow=initialRow;
    targetCol=initialCol+1;
    if(targetRow>-1 &&targetRow<grid.getRowsize()&&targetCol>-1 && targetCol<grid.getColsize()){
        if(grid.getCell(targetRow,targetCol)==value){//checks if it links with the same value
            if(!checkExists(targetRow,targetCol)){
                linkCoords.push_back(targetRow);
                linkCoords.push_back(targetCol);
                (*linkCount)++;
                linkCheck(targetRow,targetCol,linkCount);
            }
        }
    }
    //check up
    targetRow=initialRow-1;
    targetCol=initialCol;
    if(targetRow>-1 &&targetRow<grid.getRowsize()&&targetCol>-1 && targetCol<grid.getColsize()){
        if(grid.getCell(targetRow,targetCol)==value){//checks if it links with the same value
            if(!checkExists(targetRow,targetCol)){
                linkCoords.push_back(targetRow);
                linkCoords.push_back(targetCol);
                (*linkCount)++;
                linkCheck(targetRow,targetCol,linkCount);
            }
        }
    }
    //check bottom
    targetRow=initialRow+1;
    targetCol=initialCol;
    if(targetRow>-1 &&targetRow<grid.getRowsize()&&targetCol>-1 && targetCol<grid.getColsize()){
        if(grid.getCell(targetRow,targetCol)==value){//checks if it links with the same value
            if(!checkExists(targetRow,targetCol)){
                linkCoords.push_back(targetRow);
                linkCoords.push_back(targetCol);
                (*linkCount)++;
                linkCheck(targetRow,targetCol,linkCount);
            }
        }
    }

    bool returnvalue=false;
    if((*linkCount)>=3) returnvalue=true;
    return returnvalue;
}


bool Game::checkExists(int targetRow,int targetCol){
    bool returnValue=false;
    for(int i=0;i<linkCoords.size()/2;i++){
        if(linkCoords.at(2*i)==targetRow && linkCoords.at(2*i+1)==targetCol ){//checks is same value exists
            returnValue=true;
            break;
        }
    }
    return returnValue;
}
/*
0   1 2     2
1   1 2     4
2   1 2     6
3   1 2     8
*/
void Game::popBalloons(int initialRow, int initialCol,int *linkcount)
{
    for(int i=0;i<=(linkCoords.size()-2)/2;i++){
        int targetRow=linkCoords.at(2*i);
        int targetCol=linkCoords.at(2*i+1);
        if(!(targetRow==initialRow && targetCol==initialCol)){
            grid.setCell(targetRow,targetCol,0);
        }
    }
    int value=grid.getCell(initialRow,initialCol);
    grid.setCell(initialRow,initialCol,value+1);
    *linkcount=0;

}





