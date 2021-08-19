#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

#include "tube.h"
#include "move.h"

using namespace std;

void solveRandomly(vector<tube_t> &puzzle, vector<tube_t> original, vector<move_t> &possMoves, vector<move_t> &solution, int &attempt);

void averageStepCounter(vector<tube_t> &puzzle, vector<tube_t> original, vector<move_t> &possMoves, vector<move_t> &solution, int &attempt);

void printColorKey();
void setUpPuzzle(vector<tube_t> &puzzle);
int  numPossibleMoves(vector<tube_t> &puzzle, vector<move_t> &mv);
void pourColor(vector<tube_t> &puzzle, int a, int b);

bool isSolved(vector<tube_t> puzzle);
void printTubes(vector<tube_t> puzzle);
void printSolution(vector<move_t> sol);

int main(int argc, char* agv[]){
    srand(time(NULL));

    vector<tube_t> puzzle;
    setUpPuzzle(puzzle);

    vector<tube_t> original;
    original = puzzle;

    vector<move_t> solution;

    vector<move_t> possMoves;
    int attempt = 1;
    averageStepCounter(puzzle, original, possMoves, solution, attempt);
    
  //  int startFirstMoves = numPossibleMoves(puzzle, possMoves);
//    int attempt = 1;
//    solveRandomly(puzzle, original, possMoves, solution, attempt);
//    printTubes(puzzle);
//    printf("Attempt %d:\n", attempt);
//    printSolution(solution);
    return 0;   
}

void printColorKey(){
    printf("Green  (Gn) | Dark Blue  (DB) | Light Blue  (LB) | Brown (Bw) | Yellow (Yw) | Orange (Og)\n");
    printf("Purple (Pr) | Dark Green (DG) | Light Green (LG) | Pink  (Pk) | Gray   (Gy) | Red    (Rd)\n");
    printf("Empty  (Em) |\n\n");
}

void setUpPuzzle(vector<tube_t> &puzzle){
    int numTubes; 
    printf("How many Tubes: ");
    cin >> numTubes; cout << '\n';

    string temp; tube_t curr;
    for(int i=0; i<numTubes; i++){
        printColorKey();
        for(int x=0; x<4; x++){
            printf("Enter Color %d of Tube %d: ", x+1, i+1); 
            cin >> temp; cout << '\n';
            curr.setColor(x, temp);
        }
        puzzle.push_back(curr);
    }
    cout << '\n';
}

int numPossibleMoves(vector<tube_t> &puzzle, vector<move_t> &mv){
    if(isSolved(puzzle)) return 0;
    mv.clear();
    int num = 0;
    for(int i=0; i<puzzle.size(); i++){
        if(!puzzle[i].isTubeEmpty() && !puzzle[i].isTubeFinished()){
            for(int x=0; x<puzzle.size(); x++){
                if(i!=x && !puzzle[x].isTubeFull() && (puzzle[x].isTubeEmpty() || puzzle[i].getTopColor() == puzzle[x].getTopColor()) && puzzle[i].amountTopColor() <= puzzle[x].numFreeSlots() && !(puzzle[i].oneParticalColor() && puzzle[x].isTubeEmpty())){
                    move_t curr;
                    curr.setMove(i, x);
                    mv.push_back(curr);
                    num++;
                }
            }
        }
    }
    return num;
}

void pourColor(vector<tube_t> &puzzle, int a, int b){
    int atc = puzzle[a].amountTopColor();
    for(int i=0; i<atc; i++){
        puzzle[b].setColor(puzzle[b].numFreeSlots()-1, puzzle[a].getTopColor());
        puzzle[a].setColor(puzzle[a].numFreeSlots(), "Em");
    }
}

bool isSolved(vector<tube_t> puzzle){
    for(int i=0; i<puzzle.size(); i++){
        if(puzzle[i].getColor(0) != puzzle[i].getColor(3)) return false;
    }
    return true;
}

void printTubes(vector<tube_t> puzzle){
    for(int x=0; x<4; x++){
        for(int i=0; i<puzzle.size(); i++){
            cout << setw(5) << puzzle[i].getColor(x);
        }
        cout << "\n\n";
    }
    cout << "\n\n";
}

void printSolution(vector<move_t> sol){
    for(int i=0; i<sol.size(); i++){
        printf("Step #%d: ", i+1);
        cout << right << setw(2) << sol[i].getS()+1 << ' ' << setw(2) << sol[i].getD()+1 << "\n\n";
        string trash; cin >> trash;
    }
}

void solveRandomly(vector<tube_t> &puzzle, vector<tube_t> original, vector<move_t> &possMoves, vector<move_t> &solution, int &attempt){
    while(!isSolved(puzzle)){
        int rng = rand()%numPossibleMoves(puzzle, possMoves);
        int randA = possMoves[rng].getS();
        int randB = possMoves[rng].getD();
        pourColor(puzzle, randA, randB);
        move_t c; c.setMove(randA, randB);
        solution.push_back(c);
        if(numPossibleMoves(puzzle, possMoves) == 0 && !isSolved(puzzle)){
            puzzle = original;
            solution.clear();
            attempt++;
        }
    }
}

void averageStepCounter(vector<tube_t> &puzzle, vector<tube_t> original, vector<move_t> &possMoves, vector<move_t> &solution, int &attempt){
    double ave = 0; int min = INT32_MAX; int max = 0; vector<move_t> worst;
    for(int i=0; i<100; i++){
        attempt = 1;
        puzzle = original;
        solution.clear();
        solveRandomly(puzzle, original, possMoves, solution, attempt);
        ave += solution.size();
        if(solution.size() < min) min = solution.size();
        if(solution.size() > max){ max = solution.size(); worst = solution;}
    }
    printf("Current Average: %.2f\nBest Case Scenario: %d\nWorst Case Scenario: %d\n", ave/100, min, max);
    printSolution(worst);
}