#include "sources.h"
#include "entropy.h"
#include <string.h>

struct source ds;
struct source_operations s_ops;

/*
	Initialize the ds and s_ops structures according to the user-
	-specified values for data source and its value
*/
void init_ds(char* name, double value) {
	ds.s_name = (char*)malloc(sizeof(strlen(name) + 1));
	strcpy(ds.s_name, name);
	if (strcmp(name, "entropy") == 0) {
		s_ops->fill = entropy_fill;
		s_entropy = value;
		ds.s_ops = s_ops;
	}
}

/*
	This function will not change the buffer allocated in the memory.
	This is the current behavior of io_buf fill. Most proabably the
	buffer is filled with zeros
*/
int dummy_fill(struct *source, void *buf, unsigned int size){
	
	return 0;
}


/*
	This function will fill the buffer with zeros. Can be changed
	to fill with a specific constat.
*/
int constant_fill(struct *source, void *buf, unsigned int size){

	int i=0;
	for(i=0; i < size; i++){
		buf[i] = 0x00;
	}
}

/*
*/
int entropy_fill(struct *source, void *buf, unsigned int size){
	
	int i = 0;
	double pdf[PDF_SIZE];
	double cdf[PDF_SIZE];
	char symbols_table[PDF_SIZE];

	//Calculate pdf according to the given entropy
	generate_pdf(pdf, PDF_SIZE, source-> entropy)

	//Calculate cdf from the pdf
	calculate_cdf(pdf, PDF_SIZE, cdf)

	//initializing the symbol table
	for(i=0; i< PDF_SIZE; i++)
		symbols_table[i] = (char)i;
	
	//filling the buffer depending on the cdf
	for(i=0; i < size; i++){
		buf[i] = symbols_table[binary_search(rand()/(double)RAND_MAX, cdf)]
	}
	
	return 0;
}
