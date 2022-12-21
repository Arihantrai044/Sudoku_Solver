#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

class SudokuSolver {

    public:

        int     NUM;                    // Constant 9
        int     ROW;                    // Constant 3
        int     COL;                    // Constant 3
        int     BLK;                    // Constant 3
        int     problemMatrix [9][9];   // Main problem matrix
        bool    tagRow [9][9];          // Row tags
        bool    tagCol [9][9];          // Column tags
        bool    tagBlk [9][9];          // Block tags

    SudokuSolver (int (&inputMatrix) [9][9]) {
        NUM = 9;
        ROW = 3;
        COL = 3;
        BLK = 3;
        initTag ();
        initPuzzle ();
        for (int j = 0; j < NUM; j++)
            for (int k = 0; k < NUM; k++) {
                if (inputMatrix[j][k] < 1 || inputMatrix[j][k] > NUM)
                    continue;
                else
                    problemMatrix [j][k] = inputMatrix [j][k];
            }
        fillTags();
        if (solvePuzzle ()) {
            for (int j = 0; j < NUM; j++)
                for (int k = 0; k < NUM; k++)
                    inputMatrix [j][k] = problemMatrix [j][k];
        }
        else {
            cerr << "Error: Puzzle cannot  be solved." << endl;
            exit (1);
        }
    }

    /*  This function initializes all the tags to false (as in empty). The tags
     *  are later used to determine if a number is valid in a row, column or
     *  block. Whenever the number is filled, the corresponding tags are set.
     */
    void initTag (void) {
        for (int j = 0; j < NUM; j++) {
            for (int k = 0; k < NUM; k++) {
                tagRow[j][k] = false;
                tagCol[j][k] = false;
                tagBlk[j][k] = false;
            }
        }
    }
    void initPuzzle (void) {
        for (int j = 0; j < NUM; j++) {
            for (int k = 0; k < NUM; k++) {
                problemMatrix   [j][k]  = 0;
            }
        }
    }

    void fillTags (void) {
        for (int i = 0; i < NUM; i++)
            for (int j = 0; j < NUM; j++)
                assignTag (i, j, problemMatrix[i][j]);
    }


    bool checkValid (int i, int j, int c) {
        c--;
        if (tagRow[i][c] == true)
            return false;
        if (tagCol[c][j] == true)
            return false;
        if (tagBlk[(i/BLK)*BLK+j/BLK][c] == true)
            return false;
        return true;
    }

    void assignTag (int i, int j, int n) {
        if (n == 0)
            return;
        n--;
        tagRow[i][n] = true;
        tagCol[n][j] = true;
        tagBlk[(i/BLK)*BLK+j/BLK][n] = true;
    }

   
    void resetTag (int i, int j, int n) {
        if (n == 0)
            return;
        n--;
        tagRow[i][n] = false;
        tagCol[n][j] = false;
        tagBlk[(i/BLK)*BLK+j/BLK][n] = false;
    }

   
    bool solvePuzzle(void) {
        solveLogical ();
        //printPuzzle();
        return solveBacktrack (0, 0, problemMatrix);
    }

   
    void solveLogical (void) {
        int i, j, k, l = 0, row = 0, col = 0, cnt = 0;
        bool flagNotSingle = false; // Used to check if the cell is indeed a singles cell.
        bool flagValueSet = false;  // Is set if we made an assignment in the while loop.
        while (true) {
            flagValueSet = false; // Assume we make no assignment.
            for (k = 0; k < NUM; k++) { // Check all the 9 blocks for singles.
                for (l = 1; l < (NUM+1); l++) {
                    cnt = 0;
                    flagNotSingle = false; // Assume we have no singles.
                    for (i = (k/COL)*COL; i < ((k/COL)*COL + COL); i++) {
                        for (j = (k%COL)*ROW; j < ((k%COL)*ROW + ROW); j++) {
                            if (problemMatrix [i][j] > 0) // Skip the cells that are already filled.
                                continue;
                            if (checkValid (i,j,l)) { // If empty cell found, check if current value is valid.
                                row = i;
                                col = j;
                                cnt ++;
                            }
                            if (cnt > 1) { // Make sure it was a singles value and not doubles or more.
                                flagNotSingle = true; // If more than one valid value was found, break.
                                break;
                            }
                        }
                        if (flagNotSingle) // More than one valid value found, break.
                            break;
                    }
                    if (cnt == 1) { // If any singles value was found then assign it.
                        problemMatrix [row][col] = l;
                        assignTag (row, col, l); // Then set tags.
                        flagValueSet = true; // Set the flag that assignment was made.
                    }
                }
            }

            for (i = 0; i < NUM; i++) { // Check all columns.
                for (l = 1; l < NUM; l++) {
                    cnt = 0;
                    for (j = 0; j < NUM; j++) {
                        if (problemMatrix [i][j] > 0) // Skip cells that are already filled.
                            continue;
                        if (checkValid (i, j, l)) { // If empty cell found, check if current value is valid.
                            row = i;
                            col = j;
                            cnt++;
                        }
                        if (cnt > 1) { // Make sure it was a singles value and not doubles or more.
                            flagNotSingle = true; // If more than one valid value was found, break.
                            break;
                        }
                    }
                    if (cnt == 1) { // If any singles value was found then assign it.
                        problemMatrix [row][col] = l;
                        assignTag (row, col, l); // Then set tags.
                        flagValueSet = true; // Set the flag that assignment was made.
                    }
                }
            }

            for (i = 0; i < NUM; i++) { // Check all rows.
                for (l = 1; l < NUM; l++) {
                    cnt = 0;
                    for (j = 0; j < NUM; j++) {
                        if (problemMatrix [j][i] > 0) // Skip cells that are already filled.
                            continue;
                        if (checkValid (j, i, l)) { // If empty cell found, check if current value is valid.
                            row = j;
                            col = i;
                            cnt++;
                        }
                        if (cnt > 1) { // Make sure it was a singles value and not doubles or more.
                            flagNotSingle = true; // If more than one valid value was found, break.
                            break;
                        }
                    }
                    if (cnt == 1) { // If any singles value was found then assign it.
                        problemMatrix [row][col] = l;
                        assignTag (row, col, l); // Then set tags.
                        flagValueSet = true; // Set the flag that assignment was made.
                    }
                }
            }
            if(!flagValueSet) // If assignment was not made during an iteration, break out of logical solve.
                break;
        }
    }

    bool solveBacktrack (int i, int j, int proMat [9][9]) {
        if (i == NUM) { // This function goes checking row after row.
            i = 0;
            if (++j == NUM)   // Once a row is finished, go to next row.
                return true; // If final cell is reached, puzzle is solved.
        }
        if (proMat[i][j] > 0)  // Skip filled cells
            return solveBacktrack (i + 1, j, proMat); // Check next row of current column.

        for (int val = 1; val <= NUM; val++) { // Empty cell found. Check from 1 to 9.
            if (checkValid(i, j, val)) { // If it is legal (check description of legal) then fill the cell.
                proMat[i][j] = val;
                assignTag (i, j, val); // Also set the tags for checking next value.
                if (solveBacktrack (i+1,j,proMat)) // And call the solve function again.
                    return true; // If it returns true that means the puzzle is solved.
                else // If not then we need to reset the tags and backtrack.
                    resetTag (i, j, proMat[i][j]);
            }
        }
        resetTag (i, j, proMat[i][j]); // Reset tags and backtrack.
        proMat[i][j] = 0; // Also reset the value for next iteration.
        return false;
    }

       void printPuzzle (void) {
        cout << "-------------------------------------------------------" << endl;
        for (int row = 0; row < NUM; row++) {
            cout << "| ";
            for (int col = 0; col < NUM; col++) {
                cout << " *" << problemMatrix[row][col] << "* ";
                if (!((col+1) % BLK))
                    cout << " | ";
            }
            if (!((row+1) % BLK))
                cout << endl << "-------------------------------------------------------" << endl;
            else
                cout << endl;
        }
    }

};

