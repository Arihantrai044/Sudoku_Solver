
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "SudokuSolver.cc"  // The SudokuSolver class.

using namespace std;

void openInFile (char *fileName, ifstream &inFile); 
void openOutFile (char *fileName, ofstream &inFile); 
void initPuzzle (int (&problemMatrix) [9][9]);
void printPuzzle (int (&problemMatrix) [9][9]);
void writeOutFile (char *puzzleName, ofstream &outFile, int (&problemMatrix) [9][9]);

int main (int argc, char *argv[]) {
    ifstream inFile;
    ofstream outFile;
    int row, col, value;
    int problemMatrix [9][9];
    
    if (argc <= 2 || argc > 3) {
        cerr << "Error: Usage: " << argv[0] << " <InputFilename> <OutputFilename>" << endl;
        exit(1);
    }
    
    initPuzzle (problemMatrix);    
    
    openInFile(argv[1], inFile);
    do {
        inFile >> row;
        inFile >> col;
        inFile >> value;
        if (row < 1 || row > 9 || col < 1 || col > 9 || value < 1 || value > 9)
            continue;
        else
            problemMatrix [row - 1][col - 1] = value;
    } while (!inFile.eof());
    inFile.close();

    printPuzzle (problemMatrix);
    SudokuSolver SS(problemMatrix);
    printPuzzle (problemMatrix);

    openOutFile (argv[2], outFile);
    writeOutFile (argv[1], outFile, problemMatrix);
    outFile.close();

    return 0;
}

void initPuzzle (int (&problemMatrix) [9][9]) {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            problemMatrix [i][j] = 0;
}

void printPuzzle (int (&problemMatrix) [9][9]) {
    cout << "-------------------------------------------------------" << endl;
    for (int row = 0; row < 9; row++) {
        cout << "| ";
        for (int col = 0; col < 9; col++) {
            cout << " *" << problemMatrix[row][col] << "* ";
            if (!((col+1) % 3))
                cout << " | ";
        }
        if (!((row+1) % 3))
            cout << endl << "-------------------------------------------------------" << endl;
        else
            cout << endl;
    }
}

void openInFile (char *fileName, ifstream &inFile) {
    inFile.open (fileName, ifstream::in);
    if (!inFile) { // File could not be opened.
        cerr << "Error: File could not be opened." << endl;
        exit (1);
    }

    else {
        cout << "File opened successfully" << endl;
    }
}

void openOutFile (char *fileName, ofstream &inFile) {
    inFile.open (fileName, ofstream::app);
    if (!inFile) { // File could not be opened.
        cerr << "Error: File could not be opened." << endl;
        exit (1);
    }

    else {
        cout << "File opened successfully" << endl;
    }
}

void writeOutFile (char *puzzleName, ofstream &outFile, int (&problemMatrix) [9][9]) {
    outFile << puzzleName << endl;
    //outFile << "-------------------------------------------------------" << endl;
    for (int row = 0; row < 9; row++) {
        //outFile << "| ";
        for (int col = 0; col < 9; col++) {
            outFile << " *" << problemMatrix[row][col] << "* ";
            if (!((col+1) % 3) && col != 8)
                outFile << " | ";
        }
        if (!((row+1) % 3) && row != 8)
            outFile << endl << "---------------------------------------------------" << endl;
        else
            outFile << endl;
    }
}

