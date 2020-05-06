/*Kwame Armenteros Asamoa
Operating System(OS)
2/4/2020
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h> //import library to support atoi usage.
#include <sys/wait.h> //allows usage of wait function.


//collatz sequence 
void collatz(int n){
	int count = 0;

	while(n > 1){
	//n is even
		if(n % 2 == 0){
		n = n/2;
	}else{
	//n is odd
		n = 3*n+1;
		count++;
	}
		printf("%d",n);
		printf(" ");
	}
	printf("\n");
}


int main(int argc, char *argv[]){

int n;
pid_t child,parent; //process identifier 

	child = fork();
	n = atoi(argv[1]); //n is the input starting value.

	if (argc == 1) {
		fprintf(stderr,"Usage: ./hw1 <starting value>\n");
		return -1;
	}

	//fork method
	if(child == 0){ //child process
		parent = getpid(); //to get current process ID.
		printf("child: pid = %d\n", child);
		printf("child: pid1 = %d\n", parent);
	}
	else{ //parent process
		parent = getpid();
		printf("%d ",n); //print entered integer in console argument.
		collatz(n); //calling collatz sequence.
		wait(NULL);
		printf("parent: pid = %d\n", child);
		printf("parent: pid1 = %d\n", parent);
	}
	return 0;
}
 
