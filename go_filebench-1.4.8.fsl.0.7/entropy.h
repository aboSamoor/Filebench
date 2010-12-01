#ifndef ENTROPY_H
#define ENTROPY_H

#define PDF_SIZE 256


int permutate(unsigned char array[], unsigned int size);
int generate_pdf(double pdf[], int, double);
int calculate_cdf(double pdf[], unsigned int size, double cdf[]);
double pdf_entropy(double pdf[], unsigned int size);
int binary_search(double key, double array[], unsigned int);
void print_pdf(double pdf[], unsigned int size);
void print_array(unsigned char array[], unsigned int size);
double buf_entropy(void *buf, unsigned int);

#endif
