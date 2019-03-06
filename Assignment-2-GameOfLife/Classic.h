/*
Frank Entriken
2298368
entriken@chapman.edu
CPSC 350
Assignment 2: Game of Life
*/

#include <iostream>

using namespace std;

class Classic
{
  private:
    int rows;
    int columns;
    int arrayLength;

  public:
    Classic();
    ~Classic();

    void set_rows(int r);
    void set_columns(int c);
    void set_length(int l);

    void printArray(char array[], int generation);
    void nextGen(char currentArray[], char newArray[]);
    void SetArraysEqual(char currentArray[], char newArray[]);
    void CheckArrayEquality(char prevArray[], char newArray[]);
    int findNeighbors(char array[], int x, int y);

    void Enter_GameLoop(char prevArray[], char currentArray[], char newArray[]);
    void Delayed_GameLoop(char prevArray[], char currentArray[], char newArray[]);
    void Output_GameLoop(char prevArray[], char currentArray[], char newArray[], ofstream &outfile);
};
