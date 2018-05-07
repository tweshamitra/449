/**
  Twesha Mitra- Project 2- mystrings.c
  This program takes a file and prints the contents of the file.
  To run this program, do the following:
	1. run "gcc -o mystrings mystrings.c"
	2. run "./mystrings <filename>", where filename is a file in the directory
*/
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]){
	FILE *f;
	char c;
	char buffer[100];
	int i=0;
	f=fopen(argv[1], "rb");
	//make sure the file specified exists 
	if(f==NULL){
		printf("File not found\n");
		return 0;
	}
	//this loops until we reach the end of the file. 
	while(1){
		if(feof(f))
			break;
		fread(&c, sizeof(c), 1, f);
		//check ASCII values to make sure they are between 36-126
		if(c>=32 && c<=126){
			buffer[i]=c;
			i++;	
			continue;
		}	
		buffer[i]='\0';
		//Only print if length of the string is equal to or greater than 4
		if(i>=4)
			printf("%s\n",buffer);	
		i=0;
		buffer[0]='\0';
	}	
	fclose(f);
	return 0;
}