/*
Frank Entriken
2298368
entriken@chapman.edu
CPSC 350
Assignment 2: Game of Life
*/

#include "Classic.h"
#include "Doughnut.h"
#include "Mirror.h"
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

int main(int argc, char **argv)
{
  int rows, columns;
  string arrayFormula;
  string response;
  string userFile;
  string expression;

  cout << "Would you like to use a file or be provided with a random assignment?" << endl;
  cout << "'f' for file and 'r' for random...";
  cin >> response;

  while(true)
  {
    //USER FILE
    if(response == "f")
    {
      cout << "Please enter the name of the file...";
      cin >> userFile;

      ifstream inputFile;
      inputFile.open(userFile);

      if(!inputFile)
      {
        cout << "Unable to find file" << endl;
        exit(1);
      }
      else
      {
        //convert every character to one string
        int lineNumber = 1;
        string str;
        while (getline(inputFile, str))
        {
          if(lineNumber == 1)
          {
            rows = stoi(str); //https://www.techiedelight.com/convert-string-to-int-cpp/
          }
          if(lineNumber == 2)
          {
            columns = stoi(str); //https://www.techiedelight.com/convert-string-to-int-cpp/
          }
          if(lineNumber >= 3)
          {
            for (char character : str)
            {
              expression += character;
            }
          }
          lineNumber++;
        }
        break;
      }
    }

    //RANDOM ARRAY
    if(response == "r")
    {
      cout << "Please enter dimensions of your game:" << endl;
      int r, c;

      cin.clear();
      cout << "Rows...";
      cin >> r;
      while(true)
      {
        if(!cin)
        {
          cout << "Not a valid number" << endl;
          exit(1);
        }
        else
        {
          break;
        }
      }

      cin.clear();
      cout << "Columns...";
      cin >> c;
      while(true)
      {
        if(!cin)
        {
          cout << "Not a valid number" << endl;
          exit(1);
        }
        else
        {
          break;
        }
      }

      rows = r;
      columns = c;
      break;
    }
    else
    {
      cout << "Please choose either 'f' or 'r'...";
      cin >> response;
      continue;
    }
  }

  //Create current array
  int arrayLength = rows*columns;
  char prevArray[arrayLength];
  char currentArray[arrayLength];
  char newArray[arrayLength];

  //Set values to current array from file
  if(response=="f")
  {
    arrayFormula = expression.substr(0,expression.length());

    int position = 0;
    char temp;
    for(int i=0; i<arrayFormula.length(); i++)
    {
      temp = arrayFormula.at(position);
      currentArray[i] = temp;
      position++;
    }
    cout << endl;
  }

  //Set values to current array from random assignment based on probability
  if(response=="r")
  {
    double probability;
    cout << "Enter a decimal value between 0 and 1 that represents the randomness of the board...";
    while(true)
    {
      cin >> probability;
      if(probability > 1 || probability <= 0)
      {
        cout << "Enter a value between 0 and 1...";
        continue;
      }
      else
      {
        srand(time(NULL)); //https://stackoverflow.com/questions/9459035/why-does-rand-yield-the-same-sequence-of-numbers-on-every-run
        int position=0;
        for (int i=0; i<rows; i++)
        {
          for (int c=0; c<columns; c++)
          {
            int a = (rand()%100);
            char b = '-';

            if(probability*100 > a)
            {
              b = 'X';
            }
            currentArray[position] = b;
            position++;
          }
        }
        break;
      }
    }
  }

  //CHOOSE MODE
  string mode;
  cout << endl;
  cout << "What mode do you want to play in?" << endl;
  cout << "1. Classic" << endl;
  cout << "2. Doughnut" << endl;
  cout << "3. Mirror" << endl;
  cout << "Enter 1, 2, or 3...";
  cin >> mode;

  //Classic
  if(mode=="1")
  {
    Classic life;
    life.set_rows(rows);
    life.set_columns(columns);
    life.set_length(arrayLength);

    cout << endl;
    cout << "Would you like to: " << endl;
    cout << "1. Iterate through the generations using the ENTER key" << endl;
    cout << "2. Program runs automatically with a brief pause between generations" << endl;
    cout << "3. All generations will be outputted to a file" << endl;
    cout << "Enter 1, 2, or 3...";
    cin >> response;

    while(true)
    {
      if(response=="1")
      {
        life.Enter_GameLoop(prevArray, currentArray, newArray);
        break;
      }
      if(response=="2")
      {
        life.Delayed_GameLoop(prevArray, currentArray, newArray);
        break;
      }
      if(response=="3")
      {
        string userText;
        cout << "Enter the name of the text file for the simulation to output to...";
        cin >> userText;
        ofstream outFile(userText);
        life.Output_GameLoop(prevArray, currentArray, newArray, outFile);
        break;
      }
      else
      {
        cout << "Please enter a valid number...";
        cin >> response;
        continue;
      }
    }
  }

  //Doughnut
  if(mode=="2")
  {
    Doughnut life;
    life.set_rows(rows);
    life.set_columns(columns);
    life.set_length(arrayLength);

    cout << endl;
    cout << "Would you like to: " << endl;
    cout << "1. Iterate through the generations using the ENTER key" << endl;
    cout << "2. Program runs automatically with a brief pause between generations" << endl;
    cout << "3. All generations will be outputted to a file" << endl;
    cout << "Enter 1, 2, or 3...";
    cin >> response;

    while(true)
    {
      if(response=="1")
      {
        life.Enter_GameLoop(prevArray, currentArray, newArray);
        break;
      }
      if(response=="2")
      {
        life.Delayed_GameLoop(prevArray, currentArray, newArray);
        break;
      }
      if(response=="3")
      {
        string userText;
        cout << "Enter the name of the text file for the simulation to output to...";
        cin >> userText;
        ofstream outFile(userText);
        life.Output_GameLoop(prevArray, currentArray, newArray, outFile);
        break;
      }
      else
      {
        cout << "Please enter a valid number...";
        cin >> response;
        continue;
      }
    }
  }

  //Mirror
  if(mode=="3")
  {
    Mirror life;
    life.set_rows(rows);
    life.set_columns(columns);
    life.set_length(arrayLength);

    cout << endl;
    cout << "Would you like to: " << endl;
    cout << "1. Iterate through the generations using the ENTER key" << endl;
    cout << "2. Program runs automatically with a brief pause between generations" << endl;
    cout << "3. All generations will be outputted to a file" << endl;
    cout << "Enter 1, 2, or 3...";
    cin >> response;

    while(true)
    {
      if(response=="1")
      {
        life.Enter_GameLoop(prevArray, currentArray, newArray);
        break;
      }
      if(response=="2")
      {
        life.Delayed_GameLoop(prevArray, currentArray, newArray);
        break;
      }
      if(response=="3")
      {
        string userText;
        cout << "Enter the name of the text file for the simulation to output to...";
        cin >> userText;
        ofstream outFile(userText);
        life.Output_GameLoop(prevArray, currentArray, newArray, outFile);
        break;
      }
      else
      {
        cout << "Please enter a valid number...";
        cin >> response;
        continue;
      }
    }
  }

  else
  {
    cout << "Please enter a valid number...";
    cin >> response;
    exit(1);
  }
}
