#ifndef ENTROPY_H
#define ENTROPY_H

#define PDF_SIZE 256

int generate_pdf(double pdf[], int, double);
int calculate_cdf(double pdf[], unsigned int size, double cdf[]);
double pdf_entropy(double pdf[], unsigned int size);
int binary_search(double key, double array[], unsigned int);
void print_pdf(double pdf[], unsigned int size);
double buf_entropy(void *buf, unsigned int);

#endif
