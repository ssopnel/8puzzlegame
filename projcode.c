
//Sopnel Saha

//Modified version of code 

#include <stdio.h>
#include <stdlib.h> //for malloc functions
#include <string.h> //for strings and strcmp function


//prototypes
void randomize(int **,int,int); //complete
int **createboard(int); //complete
void deallocateboard(int **,int); //complete
void displayboard(int **,int); //complete
int findempty(int **,int); //complete
int move(int **,int,char *); //complete
int validmove(char *); //complete
void play(int); //complete

//function to randomize the puzzle into something thats unsolved

void randomize(int **board, int dim, int count) {
	
	//valid moves of the game
	char *moves[] =  {"u","d","l","r"};
	
	for(int i=0; i < count; i++) {
		
		int mi = rand()%4;
		char *randmove = moves[mi];
		move(board,dim, randmove);
	}
}

//function to create a puzzle board as a 2D array of integers

int **createboard(int d) {
	
	//1 allocate space for row vector
	 int**b = malloc(sizeof(int*) * d);
	 b[0] = malloc(sizeof(int) * d * d);

	
	for(int i=0;i <=d-1; i++) {
		b[i] = b[0] + i *  d;
	}
	
	//2 initialize values
	
	for(int r = 0; r <= d-1 ; r++) {
		for(int c = 0; c <= d-1; c++) {
			b[r][c] = (r*d) + c;
		}
		
	}
	//randomize function call 
	
	  randomize(b,d,1000);
	  return b;
			
}

//function to deallocate memory using free() function

void deallocateboard(int **b, int d) {	
		free(b[0]);
	    free(b);
}

//function to display the board with the number of dimensions d onto screen 

void displayboard(int **b, int d) {
	
	printf("==========\n");
	//nested loops for row (r) and col (c)
	for(int r = 0; r <= d-1; r++) {   
		for(int c = 0; c <= d-1; c++) {
			if(b[r][c]==0) {
				printf("%3s","_"); //prints out an underscore in place of 0
			}
			else {
				printf("%3d", b[r][c]);	//prints the nonzero tile number
		}
		
		}
			printf("\n");
	} 
	
}

//function to find an empty spot
int findempty(int **b,int d) {
	
	//double loop for r and c
	for(int r = 0; r <= d-1; r++) {
		for(int c = 0; c <= d-1; c++) {
			if(b[r][c] == 0) {
				return r*d+c;
			}
		}
	}
	return -1;
}

//functiom to move whenever user puts in their command 

int move(int **b, int d, char *m) {
	//locating empty tile using find empty function
	int index = findempty(b,d);
	int emptyRow = index / d;
	int emptyCol = index % d;
	
	int tileRow = emptyRow;
	int tileCol = emptyCol;
	
	//checks the letters and numbers move based on what is stated
	if(*m == 'u') {
		tileRow = emptyRow + 1;
	} else if (*m == 'd') {
		tileRow = emptyRow - 1;
	
	} else if (*m == 'l') {
		tileCol = emptyCol + 1;
	} else if(*m == 'r') {
		tileCol = tileCol - 1;
	}
	
	if(tileRow < 0 || tileRow >= d) {
		return 0;
		
	}
	
	if(tileCol < 0 || tileCol >= d) {
		return 0;
		
	}
	
	//switching empty tile for the target one
	b[emptyRow][emptyCol] = b[tileRow][tileCol];
	b[tileRow][tileCol] = 0;
	
	return 1;

	
	
	
}

//checks if the movements are valid based on possible ways to move

int validmove(char *cmd) {
	
	if(strcmp(cmd,"u") ==0) {
		return 1;
		
	} else if(strcmp(cmd,"d") ==0) {
		return 1;
		
	} else if(strcmp(cmd,"l") ==0) {
		return 1;
		
	} else if(strcmp(cmd,"r") ==0) {
		return 1;
		
	} else {
		return 0;
		
	}
		
	
}

//function to play 
void play(int d) {
	
	int **board = createboard(d);
	char cmd[20];
	displayboard(board, d);
	
	while(1) {
		printf(">");
		scanf("%s",cmd);
	
	//comparing each letter user input and checking if valid
		if (strcmp(cmd,"q") == 0) {  //q is the quit command
		 printf("goodbyee!");
		 break;

		} else if (strcmp(cmd,"s") == 0) {
		
			displayboard(board,d);


		} else if (validmove(cmd)) { 
				//checks if move function is 0 then prints illegal move if it applies
			if(move(board,d, cmd) == 0) { 
				printf("illegal move! "); 
		
			}
			else {
			displayboard(board,d);

		}
		}

		else {
			printf("This is not a valid command"); //printed for commands not listed
			
			}		
	}
			deallocateboard(board,d);
}

//method to test if the puzzle works properly
int main(void) {
	play(3); 
	return 0;
}


