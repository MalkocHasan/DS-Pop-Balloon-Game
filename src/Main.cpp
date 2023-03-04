#include"Game.h"
#include"Grid.h"
#include<iostream>
#include<fstream>
#include <string>
using namespace std;



int main(int argc, char* argv[]){

    /*string inputFile1="input1.txt";
    string inputFile2="input2.txt";
    string outputFile="output.txt";*/
    std::vector<std::string> all_args;

    if (argc > 1) {
        all_args.assign(argv + 1, argv + argc);
    }
    string inputFile1=argv[1];
    string inputFile2=argv[2];
    string outputFile=argv[3];

    Game game(inputFile1,inputFile2,outputFile);
    game.~Game();

    return 0;
}
