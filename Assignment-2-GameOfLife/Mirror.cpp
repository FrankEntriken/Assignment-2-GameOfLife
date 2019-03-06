/*
Frank Entriken
2298368
entriken@chapman.edu
CPSC 350
Assignment 2: Game of Life
*/

#include "Mirror.h"
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

//Constructor
Mirror::Mirror()
{
  int rows;
  int columns;
  int arrayLength;
}

//Destructor
Mirror::~Mirror()
{

}

//Set rows value
void Mirror::set_rows(int r)
{
    rows = r;
}

//Set columns value
void Mirror::set_columns(int c)
{
    columns = c;
}

//Set arrayLength value
void Mirror::set_length(int l)
{
    arrayLength = l;
}

//Function to print array to console
void Mirror::printArray(char currentArray[], int generation)
{
  cout << "GENERATION: " << generation << endl;
  int position = 0;
  for(int i=0; i < rows; i++)
  {
    for(int j=0; j < columns; j++)
    {
      cout << currentArray[position] << " ";
      position++;
    }
    cout << endl;
  }
}

//Function to set one array equal to a second
void Mirror::SetArraysEqual(char currentArray[], char newArray[])
{
  for(int i=0; i<arrayLength; i++)
  {
    char a = newArray[i];
    currentArray[i] = a;
  }
}

//Check if previous generation array is equal to new generation array
void Mirror::CheckArrayEquality(char prevArray[], char newArray[])
{
  int counter = 0;
  for(int i=0; i < arrayLength; i++)
  {
    if(prevArray[i] == newArray[i])
    {
      counter++;
    }
  }
  if(counter == arrayLength)
  {
    string response;
    cout << "Simulation is stable, enter any letter to quit..." << endl;
    cin >> response;
    exit(1);
  }
}

//Returns number of neighbors of a given cell
int Mirror::findNeighbors(char array[], int x, int y)
{
  string line;
  int position = x*columns+y;

  //TOP LEFT CORNER
  if(position == 0)
  {
    line += array[(x*columns+y)]; //current position
    line += array[(x*columns+y)];
    line += array[(x*columns+y)];
    line += array[1]; //1
    line += array[1]; //1
    line += array[columns]; //7
    line += array[columns]; //7
    line += array[columns+1]; //8
  }

  //TOP RIGHT CORNER
  if(position == columns-1)
  {
    line += array[(x*columns+y)];
    line += array[(x*columns+y)];
    line += array[(x*columns+y)];
    line += array[columns-2];
    line += array[columns-2];
    line += array[(x*columns+y)+columns]; //13
    line += array[(x*columns+y)+columns]; //13
    line += array[(x*columns+y)+columns-1]; //12
  }

  //BOTTOM LEFT CORNER
  if(position == (rows-1)*columns)
  {
    line += array[(x*columns+y)];
    line += array[(x*columns+y)];
    line += array[(x*columns+y)];
    line += array[(rows-2)*columns]; //21
    line += array[(rows-2)*columns]; //21
    line += array[(rows-2)*columns+1]; //22
    line += array[(rows-1)*columns+1]; //29
    line += array[(rows-1)*columns+1]; //29
  }

  //BOTTOM RIGHT CORNER
  if(position == (rows)*columns-1)
  {
    line += array[(x*columns+y)];
    line += array[(x*columns+y)];
    line += array[(x*columns+y)];
    line += array[(x*columns+y)-1]; //33
    line += array[(x*columns+y)-1]; //33
    line += array[(x*columns+y)-columns]; //27
    line += array[(x*columns+y)-columns]; //27
    line += array[(x*columns+y)-columns-1]; //26
  }

  //LEFT SIDES
  for(int i=1; i<rows-1; i++)
  {
    if(position == i*columns)
    {
      line += array[(x*columns+y)];
      line += array[(x*columns+y)-columns]; //7
      line += array[(x*columns+y)-columns]; //7
      line += array[(x*columns+y)-columns+1];
      line += array[(x*columns+y)+1];
      line += array[(x*columns+y)+columns]; //21
      line += array[(x*columns+y)+columns]; //21
      line += array[(x*columns+y)+columns+1];
    }
  }

  //RIGHT SIDES
  for(int i=2; i<rows; i++)
  {
    if(position == i*columns-1)
    {
      line += array[(x*columns+y)];
      line += array[(x*columns+y)-columns-1];
      line += array[(x*columns+y)-columns]; //13
      line += array[(x*columns+y)-columns]; //13
      line += array[(x*columns+y)-1];
      line += array[(x*columns+y)+columns-1];
      line += array[(x*columns+y)+columns]; //27
      line += array[(x*columns+y)+columns]; //27
    }
  }

  //TOP
  for(int i=1; i<columns-1; i++)
  {
    if(position == i)
    {
      line += array[(x*columns+y)];
      line += array[(x*columns+y)-1]; //2
      line += array[(x*columns+y)-1]; //2
      line += array[(x*columns+y)+1]; //3
      line += array[(x*columns+y)+1]; //3
      line += array[(x*columns+y)+columns-1];
      line += array[(x*columns+y)+columns];
      line += array[(x*columns+y)+columns+1];
    }
  }

  //BOTTOM
  for(int i=1; i<columns-1; i++)
  {
    if(position == (rows-1) * columns + i)
    {
      line += array[(x*columns+y)];
      line += array[(x*columns+y)-columns-1];
      line += array[(x*columns+y)-columns];
      line += array[(x*columns+y)-columns+1];
      line += array[(x*columns+y)-1]; //31
      line += array[(x*columns+y)-1]; //31
      line += array[(x*columns+y)+1]; //33
      line += array[(x*columns+y)+1]; //33
    }
  }

  //SURROUNDED
  for(int j=1; j<rows-1;j++)
  {
    for(int i=1; i<columns-1; i++)
    {
      if(position == j*columns+i)
      {
        line += array[0,(x*columns+y)-columns-1];
        line += array[0,(x*columns+y)-columns];
        line += array[0,(x*columns+y)-columns+1];
        line += array[0,(x*columns+y)-1];
        line += array[0,(x*columns+y)+1];
        line += array[0,(x*columns+y)+columns-1];
        line += array[0,(x*columns+y)+columns];
        line += array[0,(x*columns+y)+columns+1];
      }
    }
  }

  int neighborCount = 0;
  for (char character : line)
  {
    if (character == 'X')
    {
      neighborCount++;
    }
  }
  return neighborCount;
}

//Creates next generation
void Mirror::nextGen(char currentArray[], char newArray[])
{
  for(int i=0; i < rows; i++)
  {
    for(int c=0; c < columns; c++)
    {
      if(findNeighbors(currentArray, i, c) <= 1)
      {
        newArray[i*columns+c] = '-';
      }
      if(findNeighbors(currentArray, i, c) == 2)
      {
        if(currentArray[i*columns+c] == '-')
        {
          newArray[i*columns+c] = '-';
        }
        if(currentArray[i*columns+c] == 'X')
        {
          newArray[i*columns+c] = 'X';
        }
      }
      if(findNeighbors(currentArray, i, c) == 3)
      {
        newArray[i*columns+c] = 'X';
      }
      if(findNeighbors(currentArray, i, c) >= 4)
      {
        newArray[i*columns+c] = '-';
      }
    }
  }
}

//How the game is run, press enter for next generation
void Mirror::Enter_GameLoop(char prevArray[], char currentArray[], char newArray[])
{
  int generation = 0;
  cout << endl;
  cout << "Press ENTER for next generation, or type and enter any other letter to quit..." << endl;

  while(true)
  {
    if(cin.get() == '\n')
    {
      //PRINT ARRAY
      printArray(currentArray, generation);

      //CALCULATE NEXT GENERATION
      nextGen(currentArray, newArray);

      if(generation >= 3)
      {
        CheckArrayEquality(prevArray, newArray);
      }

      //SET CURRENT ARRAY TO NEW GENERATION
      SetArraysEqual(prevArray, currentArray);
      SetArraysEqual(currentArray, newArray);

      cin.clear();
      generation++;
      cout << endl;
      continue;
    }
    else
    {
      cout << "Quitting Program" << endl;
      exit(1);
    }
  }
}

//How the game is run, automated with delay between generations
void Mirror::Delayed_GameLoop(char prevArray[], char currentArray[], char newArray[])
{
  int generation = 0;
  cout << endl;

  while(true)
  {
    //PRINT ARRAY
    printArray(currentArray, generation);

    //CALCULATE NEXT GENERATION
    nextGen(currentArray, newArray);

    if(generation >= 1)
    {
      CheckArrayEquality(prevArray, newArray);
    }

    //SET CURRENT ARRAY TO NEW GENERATION
    SetArraysEqual(prevArray, currentArray);
    SetArraysEqual(currentArray, newArray);

    generation++;
    cout << endl;
    sleep(1);
  }
}

//How the game is run, outputs simulation to given text file
void Mirror::Output_GameLoop(char prevArray[], char currentArray[], char newArray[], ofstream &outfile)
{
  int generation = 0;
  while(true)
  {
    //OUTPUT ARRAY
    outfile << "GENERATION: " << generation << endl;
    int position = 0;
    for(int i=0; i < rows; i++)
    {
      for(int j=0; j < columns; j++)
      {
        outfile << currentArray[position] << " ";
        position++;
      }
      outfile << endl;
    }
    outfile << endl;

    //CALCULATE NEXT GENERATION
    nextGen(currentArray, newArray);

    if(generation >= 1)
    {
      CheckArrayEquality(prevArray, newArray);
    }

    //SET CURRENT ARRAY TO NEW GENERATION
    SetArraysEqual(prevArray, currentArray);
    SetArraysEqual(currentArray, newArray);

    generation++;
  }
}
