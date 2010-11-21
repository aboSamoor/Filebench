#include <stdlib.h>
#include <stdio.h>
#include "sources.h"
#include "entropy.h"

/*
	This function will not change the buffer allocated in the memory.
	This is the current behavior of io_buf fill. Most proabably the
	buffer is filled with zeros
*/
int dummy_fill(struct source *ds, void *buf, unsigned int size){
	
	return 0;
}


/*
	This function will fill the buffer with zeros. Can be changed
	to fill with a specific constat.
*/
int constant_fill(struct source *ds, void *buf, unsigned int size){

	int i=0;
	for(i=0; i < size; i++){
		((char *)buf)[i] = 0;
	}
	return 0;
}

/*
	This function fills the buffer with random data according to
	a pdf has the entropy specified in the source.
*/
int entropy_fill(struct source *ds, void *buf, unsigned int size){
	
	int i = 0;
	double pdf[PDF_SIZE];
	double cdf[PDF_SIZE];
	unsigned char symbols_table[PDF_SIZE];

	//Calculate pdf according to the given entropy
	generate_pdf(pdf, PDF_SIZE, ds-> s_entropy);

	//Calculate cdf from the pdf
	calculate_cdf(pdf, PDF_SIZE, cdf);

	//initializing the symbol table
	for(i=0; i< PDF_SIZE; i++)
		symbols_table[i] = (char)i;
	//filling the buffer depending on the cdf
	for(i=0; i < size; i++){
		printf("Integer %d\n",i);	
		((char *)buf)[i] = symbols_table[binary_search(rand()/(double)RAND_MAX, cdf, PDF_SIZE)];
	}
	
	return 0;
}


int main(int argc, char **argv){
	
	struct source ds;
	unsigned int size = 1024*2;
	unsigned char buf[size];
	ds.s_entropy = 3.56;
	entropy_fill(&ds, &buf, size);
	printf("The entropy of buf: %f\n", buf_entropy(&buf, size));
	return 0;
}
