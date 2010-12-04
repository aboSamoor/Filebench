#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
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
	_search_fill fills the buffer with random data according to
	a pdf has the entropy specified in the source. It calculates
    the cdf then populate the buffer by searching in the cdf for 
    the random number. Sometimes this approach is called roulette
    algorithm. The binary search is expected to add 8x factor.
*/
int entropy_search_fill(struct source *ds, void *buf, unsigned int size){
	
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

	//shuffle the symbols table
	permutate(symbols_table, PDF_SIZE);

	for(i=0; i < size; i++){
		((unsigned char*)buf)[i] = symbols_table[binary_search(rand()/(double)RAND_MAX, cdf, PDF_SIZE)];
	}
	return 0;
}

/*
	_cont_fill fills the buffer with random data according to
	the pdf. It will generate contigouos segements of data in the
    buffer to make different same size buffer look different, we
    shuffle the symbols table. It takes less time but it does not
    give homogeous entropy data stream. Because of rounding errors
    we will have some remaining elements are not filled, so we will
    use the search method to fill them.
*/
int entropy_cont_fill(struct source *ds, void *buf, unsigned int size){
	
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

	//shuffle the buffer
    permutate(symbols_table, PDF_SIZE);

	int k=0;
	int j=0;
	
	for(i=0; i< PDF_SIZE; i++){
		//printf("values %u %f %u",i,pdf[i],size);
		for(j=0; j < (int)(pdf[i]*size); j++){
			((unsigned char*)buf)[k] = symbols_table[i];
			k++;
		}
	}
	//remaining elements
	for(; k < size; k++){
		((unsigned char *)buf)[k] = symbols_table[binary_search(rand()/(double)RAND_MAX, cdf, PDF_SIZE)];
	}
    
	return 0;
}

/*
	_permutate_fill fills the buffer with random data according to
	the pdf. It will generate contigouos segements of data in the
    buffer. After that a permutation function will be called to make
    the buffer looks with homogenous entropy. The permutation
    function has high overhead, because it is not cache friendly.
    tests show 16x overhead
    
*/

int entropy_permutate_fill(struct source *ds, void *buf, unsigned int size){
    int err = entropy_cont_fill(ds, buf, size);
    permutate((unsigned char*)buf,size); 
	return err;
}

/*
    _lookup_fill initializes a vector using _*_fill method then
    using that vector we will initilize our buffer by lookuping
    differnt elements using a random index. 
*/

int entropy_lookup_fill(struct source *ds, void *buf, unsigned int size){
	
	int i = 0;

    //initilize the vector
    int lookup_size = 16*1024;
    void *lookup_table = malloc(lookup_size);
    int err = entropy_cont_fill(ds, lookup_table,lookup_size);

#ifndef _FB_FILEBENCH_H
	printf("The entropy of the lookup table: %f\n", buf_entropy(lookup_table, lookup_size));
#endif
	for(i=0; i <size ; i++){
		((unsigned char*)buf)[i] = ((unsigned char*)lookup_table)[rand()%lookup_size];
		}
    
    free(lookup_table);
    //copy the tmp buffer to the target one
	return err;
}

/*
    This function will create a tmp buffer and call the actual
    function to fill the tmp buffer with the specific entropy.
    Creating a tmp buffer is because of a weird error happens
    in filebench in case we manipulate the original buffer directly.
*/

int entropy_fill(struct source *ds, void *buf, unsigned int size){
	void *tmp = malloc(size);
    int err = entropy_cont_fill(ds, tmp, size);
    memcpy(buf, tmp, size);
    free(tmp);
    return err;
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

int main(int argc, char **argv){
	
	struct source ds;
	unsigned int size = 256*1024*1024;
	unsigned char* buf=malloc(size);
	clock_t start = clock();
	ds.s_entropy = 7.84;
	entropy_fill(&ds, buf, size);
	printf("Time elapsed: %f\n", ((double)clock() - start) / CLOCKS_PER_SEC);
	printf("The entropy of buf: %f\n", buf_entropy(buf, size));
	free(buf);
	return 0;
}

#endif
