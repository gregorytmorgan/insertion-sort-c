/* 
 * File:   main.c
 * Author: gmorgan
 *
 * Created on November 18, 2014, 8:49 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int MAX_NAMES = 128;
static const int MAX_NAME_LENGTH = 64;
static char INPUT_FORMAT[256];

/**
 * Read in a file
 */
char **readFile(char *fname) {
	FILE *fp;
	char name[MAX_NAME_LENGTH + 1];
	char **names = (char **)malloc(sizeof(char *) * MAX_NAMES);
	int idxNames = 0;
	int i;

	// initialize the names array
	for (i = 0; i < MAX_NAMES; i++) {
		names[i] = 0;
	}
	
	printf("Opening %s for reading.\n", fname);
	
	fp = fopen(fname, "r");
	
	if (fp == NULL) {
	  fprintf(stderr, "Can't open input file %s.\n", fname);
	  return NULL;
	}
	
	snprintf(INPUT_FORMAT, sizeof(INPUT_FORMAT), "%%%ds", MAX_NAMES);
	
	idxNames = 0;
	while (!feof(fp) && idxNames < MAX_NAMES) {
		
	  if (fscanf(fp, INPUT_FORMAT, name) != 1) { // 15 + null term, 
		break;
	  }
	  
	  // white space / trim ????
	  names[idxNames++] = strdup(name);
	}	
	
	printf("Read %d names.\n", idxNames);

	fclose(fp);

	return names;
}

/**
 * 
 */
void dumpNames(char **names) {
	int i;
	
	for(i = 0; i < MAX_NAMES; i++) {
		if (names[0] == 0) {
			break;
		}
		printf("%s\n", names[i]);
	}
}

/**
 * 
 */
int compNames(char *a, char *b) {
	return strcmp(a, b);
}

/**
 * 
 */
void swapNames(char *a, char *b) {
	char * tmp = a;
	a = b;
	b = tmp;
}

/**
 * Insertion Sort
 * 
   for i = 1 to length(A)
    x = A[i]
    j = i
    while j > 0 and A[j-1] > x
        A[j] = A[j-1]
        j = j - 1
    A[j] = x
 * 
 */
void sortNames(char **names) {
	char * x;
	int j, i = 1;

	while (names[i] != 0) {
		x = names[i];
		j = i;
		while (j > 0 && compNames(names[j - 1], x) > 0) {
			names[j] = names[j - 1];
			j--;
		}
		names[j] = x;
		i++;
	}
}

/*
 * main
 */
int main(int argc, char** argv) {
	int i;
	char *fname = 0;
	char **names; // array of names

	// note: arg[0] is the binary itself	
	if (argc > 1) {
		fname = argv[1];
	} else {
		printf("No input file\n", fname);
		return (EXIT_FAILURE);
	}
	
	printf("Calling readFile() on %s\n", fname);
	
	names = readFile(fname);
	
	if (!names) {
		return (EXIT_FAILURE);
	}

	sortNames(names);
	
	printf("Post sort dump:\n");
	dumpNames(names);

	// clean up
	for (i = 0; i < MAX_NAMES; i++) {
		if (names[i] == 0) {
			break;
		}
		free(names[i]);
	}	

	return (EXIT_SUCCESS);
}

// end file
