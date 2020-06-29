//
//  main.cpp
//  CS300_HW1
//
//  Created by selçuk yılmaz on 2/29/20.
//  Copyright © 2020 selçuk yılmaz. All rights reserved.

#include <iostream>
#include "Stack.cpp"
#include "Stack.hpp"
#include <vector>
#include <fstream>

struct Cell//Cell struct for creating the maze.
{
public:
    int xCor;
    int yCor;
    Cell(int xCor = 0,int yCor = 0){
        this->xCor = xCor;
        this->yCor = yCor;
    };
    
    bool visited;
    bool top_wall;
    bool bot_wall;
    bool left_wall;
    bool right_wall;
};

void pathFinder(int row,int column,vector<vector<Cell>> maze,int entryX,int entryY,int exitX,int exitY,int mazeID){ // pathFinder Function to find the path and it is same as generatemaze function except if statements will look for if there is a wall or not to move.
    int CellCount = row*column;
    //  Cell m(0,0);
    // vector<vector<Cell>> maze(row,vector<Cell>(column,m));//creating a 2d maze with user input with all elements 1.
    for(int i=0; i<row; i++) {
        for(int j=0; j<column; j++) {
            
            maze[i][j].visited = false;   // all cells visit boolean set to false to prevent infinite loops.
            
            
        }
        
    }
    int visitedCells = 1;
    Stack<Cell> mazeStack;
    int currentX = entryX;
    int currentY = entryX;
    int counter = 0;
    bool temp = false;
    int randDirection = 0;
    mazeStack.push(maze[currentY][currentX]);
    maze[currentY][currentX].visited = true;
    while(CellCount > visitedCells){
        if(temp == false){
            randDirection = rand() % 4 ;
            counter = 0;
            
        }
        if(maze[currentY][currentX].xCor == exitX && maze[currentY][currentX].yCor == exitY){   // if current cell's coordinates is the same as exit coordinates
            Stack<Cell> myStack;//create a stack to traverse the firstly created stack and use it to print the pathway to file.
            while(!mazeStack.isEmpty()){
                myStack.push(mazeStack.topAndPop()); // traversing the stack
            }
            ofstream writer2;
            writer2.open("maze_" + to_string(mazeID) +"_path_"+ to_string(entryX )+"_"+ to_string(entryY)+"_"+ to_string(exitX )+"_"+ to_string(exitY )+  ".txt",fstream::out) ;
            
            while (!myStack.isEmpty()) {
                writer2 << myStack.top().xCor <<" " << myStack.top().yCor << endl; // printing to the path file.
                myStack.pop();
            }
            writer2 << flush;
            writer2.close();
            
            break;
        }
        else if ((currentY < row - 1 && randDirection == 0) && (maze[currentY+1][currentX].visited == false) && (maze[currentY][currentX].top_wall == false) ){ // UP (AFTER THİS PART İS EXPLAINED IN MAZEGENERATION PART. Except this part maze[currentY][currentX].top_wall == false and this means there should be not a wall where the rat will move on the maze.
            
            maze[currentY+1][currentX].visited = true;
            
            mazeStack.push(maze[currentY+1][currentX]);
            currentY = currentY+1;
            visitedCells++;
            
            temp = false;
            
        }
        
        
        
        
        else if ( (currentX < column -1 && randDirection == 1 )&& (maze[currentY][currentX+1].visited == false) &&(maze[currentY][currentX].right_wall == false)){ // RİGHT
            
            maze[currentY][currentX+1].visited = true;
            
            mazeStack.push(maze[currentY][currentX+1]);
            currentX = currentX + 1;
            visitedCells++;
            
            temp = false;
        }
        
        
        
        
        else if ( (currentY > 0 && randDirection == 2) && (maze[currentY-1][currentX].visited == false)&&(maze[currentY][currentX].bot_wall == false)){ // DOWN
            maze[currentY-1][currentX].visited = true;
            
            mazeStack.push(maze[currentY-1][currentX]);
            currentY = currentY-1;
            visitedCells++;

            temp = false;
        }
        
        
        
        else if ((currentX > 0 && randDirection == 3) && (maze[currentY][currentX-1].visited == false) && (maze[currentY][currentX].left_wall== false)){ // LEFT
            maze[currentY][currentX-1].visited = true;
            
            mazeStack.push(maze[currentY][currentX-1]);
            currentX = currentX-1;
            visitedCells++;
            
            temp = false;
        }
        else{
            randDirection = ((randDirection + 1) % 4) ;
            temp = true;
            counter++;
            if(counter == 4){
                mazeStack.pop();
                currentX =  mazeStack.top().xCor;
                currentY =  mazeStack.top().yCor;
                
                
                temp = false;
                
            }
        }
        
        
    }
    
    
}




vector<vector<Cell>> mazeGenerate(int row,int column){
    int CellCount = row*column;
    Cell m(0,0);
    vector<vector<Cell>> maze(row,vector<Cell>(column,m));//creating a 2d maze with user input with all elements as Cells.
    for(int i=0; i<row; i++) {
        for(int j=0; j<column; j++) {
            maze[i][j].xCor = j;
            maze[i][j].yCor = i;
            maze[i][j].visited = false;
            maze[i][j].top_wall = true;
            maze[i][j].bot_wall = true;
            maze[i][j].right_wall = true;
            maze[i][j].left_wall = true;
            
        }
        
    }
    int visitedCells = 1;
    Stack<Cell> mazeStack;
    int currentX = 0;
    int currentY = 0;
    int counter = 0;
    bool temp = false;
    int randDirection = 0;
    mazeStack.push(maze[currentY][currentX]);
    maze[currentY][currentX].visited = true;
    while(CellCount > visitedCells){
        if(temp == false){ // if random direction did not try all direction dont go in.
            randDirection = rand() % 4 ; // create a random integer 0 to 3;
            counter = 0;
        }
        if ((currentY < row - 1 && randDirection == 0) && (maze[currentY+1][currentX].visited == false)){ // UP , if up is not out of the maze and the next cell is not visited move.
            
            maze[currentY+1][currentX].visited = true;//
            maze[currentY][currentX].top_wall = false;// break the current cells top wall
            maze[currentY+1][currentX].bot_wall = false;//and the next wall's down wall
            mazeStack.push(maze[currentY+1][currentX]);
            currentY = currentY+1;
            visitedCells++; //uptade the visited cells to prevent infinite while loop
            
            temp = false;
            
        }
        
        
        
        
        else if ( (currentX < column -1 && randDirection == 1 )&& (maze[currentY][currentX+1].visited == false)){ // RİGHT, if right is not out of the maze and the next cell is not visited move.
            
            maze[currentY][currentX+1].visited = true;
            maze[currentY][currentX].right_wall = false;
            maze[currentY][currentX+1].left_wall = false;
            mazeStack.push(maze[currentY][currentX+1]);
            currentX = currentX + 1;
            visitedCells++;
            
            temp = false;
        }
        
        
        
        
        else if ( (currentY > 0 && randDirection == 2) && (maze[currentY-1][currentX].visited == false)){ // DOWN, if down is not out of the maze and the next cell is not visited move.
            maze[currentY-1][currentX].visited = true;
            maze[currentY][currentX].bot_wall = false;
            maze[currentY-1][currentX].top_wall = false;
            mazeStack.push(maze[currentY-1][currentX]);
            currentY = currentY-1;
            visitedCells++;
            
            temp = false;
        }
        
        
        
        else if ((currentX > 0 && randDirection == 3) && (maze[currentY][currentX-1].visited == false)){ // LEFT, if left is not out of the maze and the next cell is not visited move.
            maze[currentY][currentX-1].visited = true;
            maze[currentY][currentX].left_wall = false;
            maze[currentY][currentX-1].right_wall = false;
            mazeStack.push(maze[currentY][currentX-1]);
            currentX = currentX-1;
            visitedCells++;
            // CellCount--;
            temp = false;
        }
        else{
            randDirection = ((randDirection + 1) % 4) ; // if the random direction is blocked try others.
            temp = true;
            counter++;
            if(counter == 4){
                
                mazeStack.pop(); // if current position is a dead end pop from stack and backtrack until there is a new path.
                currentX =  mazeStack.top().xCor;
                currentY =  mazeStack.top().yCor;
                
                temp = false;
                
            }
        }
        
        
    }
    
    return maze;
}




int main() {
    int Column,Row,matrixCount;
    cout << "Enter the number of mazes: ";
    cin >> matrixCount;
    cout << "Enter the number of rows and columns (M and N): " ;
    cin >> Row >> Column;
    
    
    
    
    
    vector<vector<vector<Cell>>> Allmazes;
    for(int z = 0; z <matrixCount; z++){
        Allmazes.push_back(mazeGenerate(Row,Column));
    }
    
    ofstream writer;
    
    
    
    
    
    
    for(int z = 0; z < Allmazes.size(); z++){
        if(z != 0){
            writer.close();
        }
        writer.open("maze_" + to_string(z) + ".txt");
        writer << Row << " " << Column << endl;
        for(int i = 0; i < Allmazes[z].size(); i++){
            for(int j = 0; j < Allmazes[z][i].size(); j++){
                
                writer << "x=" << Allmazes[z][i][j].xCor << " y=" << Allmazes[z][i][j].yCor << " l=" << Allmazes[z][i][j].left_wall << " r=" << Allmazes[z][i][j].right_wall <<" u="<< Allmazes[z][i][j].top_wall << " d=" << Allmazes[z][i][j].bot_wall << endl;
            }
        }
    }
    writer.close();
    cout << "All mazes are generated." << endl;
    int mazeID,entryX,entryY,exitX,exitY;
    cout <<"Enter a maze ID between 1 to "<< matrixCount << " inclusive to find a path:";
    cin >> mazeID;
    
    cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): " ;
    cin >> entryX >> entryY;
    cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
    cin >> exitX >> exitY;
    
    pathFinder(Row,Column,Allmazes[mazeID-1],entryX,entryY,exitX,exitY,mazeID);
 
    
    
    return 0;
}































