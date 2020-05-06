#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define num_threads 3
int valid[num_threads] = {0};
int grid = 2;

/* You will need a structure to store the information to be passed to each thread (see "Passing Parameters to Each Thread" in the textbook's project description)*/
typedef struct{
	int row;
	int column;
}parameters;


int sudoku[9][9] = {
{6,2,4,5,3,9,1,8,7},
{5,1,9,7,2,8,6,3,4},
{8,3,7,6,1,4,2,9,5},
{1,4,3,8,6,5,7,2,9},
{9,5,8,2,4,7,3,6,1},
{7,6,2,3,9,1,4,5,8},
{3,7,1,9,5,6,8,4,2},
{4,9,6,1,8,2,5,7,3},
{2,8,5,4,7,3,9,1,6},
};
	
void *column_worker(void *param);
void *row_worker(void *param);
void *puzzle3x3(void *param);

pthread_t col_thread, row_thread, subgrid_thread;

int main(int argc, char *argv[])
{

	//error checking 
	if (argc == 1) {
		fprintf(stderr,"Usage: ./hw2 <starting value>\n");
		return -1;
	}
	
	FILE *f; //pointer to the type and library
	f = fopen(argv[1], "r"); //r to read file. Read file from argv[]


	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			fscanf(f, "%d", &sudoku[i][j]);
		}
	}


	parameters *columnData = (parameters *) malloc(sizeof(parameters));
	columnData->row = 0;
	columnData->column = 0;
 
	
	parameters *rowData = (parameters *) malloc(sizeof(parameters));
	rowData->row = 0;
	rowData->column = 0;
 
	
	parameters *is3x3Data = (parameters *) malloc(sizeof(parameters));
	is3x3Data->row = 0;
	is3x3Data->column = 0;
 	

	void *rows;
	void *cols;
	void *square;
	
	pthread_create(&col_thread, NULL, column_worker, (void *) columnData);
	pthread_create(&row_thread, NULL, row_worker, (void *) rowData);
	pthread_create(&subgrid_thread, NULL, puzzle3x3, (void *) is3x3Data);

	pthread_join(row_thread, &rows);
	pthread_join(col_thread, &cols);
	pthread_join(subgrid_thread, &square);

	int k;
	while(k < 3){
		if(valid[k] == 1){
		k++;
	}else{
		printf("Sudoku puzzle invalid\n");
		exit(0);
		}
	}
	printf("Sudoku puzzle valid\n");
	return 0;
}


/*thread code for child checking all columns*/
void *column_worker(void *params)
{
	parameters *col_worker = (parameters *) params;
	int rowSudoku = col_worker->row;
	int colSudoku = col_worker->column;
	
 		for(int i = 0; i < 9; i++){
			int layout[9] = {0}; //contains sorted array columns
			for(int j = 0; j < 9; j++){
			int matrix = sudoku[i][j]; //sudoku puzzle stores grid
			if(layout[matrix - 1] == 0 && matrix > 0){
				layout[matrix - 1] = matrix;
			}else{
				valid[0] = 0;
				pthread_exit(0);
			}
		}
	}
	valid[0] = 1;
	pthread_exit(0);
}

//Thread for checking rows 
void *row_worker(void *params)
{
	parameters *row_work = (parameters *) params;
	int rowSudoku = row_work->row;
	int colSudoku = row_work->column;
	
	for(int j = 0; j < 9; j++){
		int layout[9] = {0}; //contains sorted array rows
		for(int j = 0; j < 9; j++){
		int matrix = sudoku[rowSudoku][j]; //sudoku puzzle stores grid
			if(layout[matrix - 1] == 0 && matrix > 0){
				layout[matrix - 1] = matrix;
			}else{
				valid[1] = 0;
				pthread_exit(0);
			}
		}
	}
	valid[1] = 1;
	pthread_exit(0);
}

//Thread for checking nine 3x3 subgrids
void *puzzle3x3(void *params)
{
	parameters *puzzle = (parameters *) params;
	int rowSudoku = puzzle->row;
	int colSudoku = puzzle->column;
	
	int layout[9] = {0}; //contains sorted array columns
	for(int i = rowSudoku; i < rowSudoku + 3; i++){
		for(int j = colSudoku; j < colSudoku + 3; j++){
		int matrix = sudoku[i][j]; //sudoku puzzle stores grid
			if(layout[matrix - 1] == 0 && matrix > 0){
				layout[matrix - 1] = matrix;	
			}else{
				valid[grid] = 0;
				grid++;
				pthread_exit(0);				
		}
	    }
	}
	valid[grid] = 1;
	grid++;
	pthread_exit(0);
}
