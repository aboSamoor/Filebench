#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "entropy.h"
#include "filebench.h"
#include "sources.h"

struct source *ds;

#ifdef _FB_FILEBENCH_H
/* Register the data source to be used for writing */
int register_datasource(struct source **source) {
	if (verify_ds(*source)) {
		printf("Could not verify datasource");
		return (FILEBENCH_ERROR);
	}

	ds = *source;
	return 0;
}

/* Verify that the data source is valid */
int verify_ds(struct source *source) {
	if (source->s_entropy < 0.00 || source->s_entropy > 8.00 || source->s_ops == NULL) {
		return (FILEBENCH_ERROR);
	}

	return 0;
}
#endif
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
#ifndef _FB_FILEBENCH_H
	print_pdf(pdf, 5);
	printf("PDF entropy is: %f\n" ,pdf_entropy(pdf, PDF_SIZE));
#endif
	//Calculate cdf from the pdf
	calculate_cdf(pdf, PDF_SIZE, cdf);

	//initializing the symbol table
	for(i=0; i< PDF_SIZE; i++)
		symbols_table[i] = (unsigned char)i;
	//filling the buffer depending on the cdf
	char *tmp = malloc(size);
	for(i=0; i < size; i++){
		tmp[i] = symbols_table[binary_search(rand()/(double)RAND_MAX, cdf, PDF_SIZE)];
	}
	memcpy(buf, tmp, size);
	free(tmp);
	return 0;
}


struct source_operations constant_operations = {
	.fill = constant_fill,
};

struct source_operations entropy_operations = {
	.fill = entropy_fill,
};

struct source_operations dummy_operations = {
	.fill = dummy_fill,
};


#ifndef _FB_FILEBENCH_H
/*
int main(int argc, char **argv){
	
	struct source ds;
	unsigned int size = 1024*1024*10;
	unsigned char* buf=malloc(size);
	ds.s_entropy = 1.45;
	entropy_fill(&ds, buf, size);
	printf("The entropy of buf: %f\n", buf_entropy(buf, size));
	free(buf);
	return 0;
}
*/
#endif
