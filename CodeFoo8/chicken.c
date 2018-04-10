/*******************************************
 *Author: Thomas Korsness
 *File: Chicken.c
 *Description: Program built for the IGN Code Foo 8 application. Program creates a 4x4 grid and places random potholes. It then recursively finds a path from a random start point on the far left(x=0) to any point on the far right(x=3).
 *
 ******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define xcoord 4
#define ycoord 4
char grid[xcoord][ycoord];//global grid
/**********************
 *Function: makeGrid
  Description: creates a 4x4 grid and places random pot holes. The number of holes is random between 1 and 8. O is open road, X is a pot hole. Function will edit the global variable "grid". No paramaters needed.
 ********************/
void makeGrid(){
	int xrand, yrand, num_holes,i,j,k;
	for(j=0; j < ycoord; j++){
		for(k=0; k < xcoord; k++){
			grid[k][j] = 'O';
			printf(" %c",grid[k][j]);
		}
		printf("\n");
	}
	printf("\n");
	j=0;
	k=0;

	srand(time(NULL));
	num_holes = (rand() %8) + 1;
	for(i=0; i < num_holes; i++){
		xrand = rand() % 4;
		yrand = rand() % 4;
		grid[xrand][yrand] = 'X';
		//printf("num is %d xrand is %d yrand is %d i is %d\n",num_holes,xrand,yrand,i);
	}
	for(j=0; j < ycoord; j++){
		for(k=0; k < xcoord; k++){
			printf(" %c",grid[k][j]);
		}
		printf("\n");
	}
	printf("\n");
	
}
/**************************************
 *Function: setStart
  Description: randomly chooses a point on the x=0 axis for the "chicken" to start. Chicken can only start on open road, not a pot hole. It is possible for the chicken to be placed in a maze with no solution. Function edits the "grid" global by placing a '!' at the starting point of the chicken. No parameters needed.
 *********************************/
void setStart(){
	int x,j,k;
	int i=0;
	int q=0;
	char copy[xcoord][ycoord];
	while(i<4){
		if(grid[0][i] == 'X'){
			q++;
		}
		if(q == 4){
			printf("no valid start tile!\n");
			exit(0);
		}
		i++;
	}
	do{
	x = rand() %4;
	}while(grid[0][x] == 'X');
	grid[0][x] = '!';
	for(j=0; j < ycoord; j++){
		for(k=0; k < xcoord; k++){
			printf(" %c",grid[k][j]);
			copy[k][j]=grid[k][j];
		}
		printf("\n");
	}
	printf("\n");
	findPath(0,x,copy);
}
/***********************
 *Function: findPaths
  Description: gets the grid and start point from the setStart function. Uses recursion to find a valid path from the start to the finish. After each step the program prints out the path of the "chicken". That path is shown by '!'. The program notifies the user when a path is found by printing "This is a complete path!!". The program also prints out when it finds a dead end or finds an open space. This is to show the logic the "chicken" uses to move. "Chicken" can onlu move up down and right and cant backtrack.
 ********************/
int findPath(int xstart, int ystart, char copy[xcoord][ycoord]){//recursive function
	int j,k;
	//char copy[xcoord][ycoord];
	for(j=0; j < ycoord; j++){
		for(k=0; k < xcoord; k++){
			//copy[k][j] = grid[k][j];
			printf(" %c",copy[k][j]);
		}
		printf("\n");
	}
	printf("\n");
	//copy[xstart][ystart] = 'X';
	//printf("start y is %d\n",ystart);
	if(xstart == 3){
		printf("This is a complete path!!!\n");
	}
	else{
		printf("pass\n");
	}


	//go right
	if(copy[xstart+1][ystart] != 'O' || xstart+1 > 3){
		printf("dead end right\n");
		//return 0;
	}
	else{
		printf("open to go right\n");
		copy[xstart+1][ystart]='!';
		findPath(xstart+1, ystart, copy);
	}
	//go up
	if(copy[xstart][ystart-1] != 'O' || ystart-1 < 0){
		printf("dead end up\n");
		//return 0;
	}
	else{
		printf("open to go up\n");
		copy[xstart][ystart-1]='!';
		findPath(xstart, ystart-1, copy);
	}
	//go down
	if(copy[xstart][ystart+1] != 'O' || ystart+1 > 3){
		printf("dead end down\n");
		//return 0;
	}
	else{
		printf("open to go down\n");
		copy[xstart][ystart+1]='!';
		findPath(xstart, ystart+1, copy);
	}
	printf("dead end \n");

}

/****************
 *Function: Main
  Description: calls the makeGrid and setStart Function. No paramaters. findPath is called in the setStart Function.
 **************/
void main(){
	makeGrid();
	setStart();
}
