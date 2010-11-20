#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "entropy.h"

double pdf_entropy(double pdf[], unsigned int size){
	
	double entropy =0;
	int i= 0;

	if(size <= 0)
		return -1;

	for(i=0; i<size; i++){
		if(pdf[i] > 0)
			entropy+= pdf[i]*log2(1.0/pdf[i]);
	}
	return entropy;
}

int binary_search(double key, double array[], unsigned int size){

	int start = 0;
	int end = size-1;
	int mid;

	if(size <= 0)
		return -2;

	while(end-start < 2){
		mid = (end+start)/2;
		if(key == array[mid])
			return mid;
		if(key < array[mid])
			end = mid;
		else
			start = mid;
	}
	return end;	
}

int calculate_cdf(double pdf[], unsigned int size, double cdf[]){

	if (size <= 0)
		return -1;

	cdf[0] = pdf[0];
	for(i=1; i < size; i++){
		cdf[i] = cdf[i-1] + pdf[i];
	}
	return 0;
}

double secant_method(double (*func)(double, double, double), double n, double e, double start, double end){
	int i =0;
	double d, temp;
	for(i=0; i<20 ;i++){
		temp = func(n, e, end);
		d = (end-start) / (temp - func(n, e, start)) * temp;
		if(fabs(d) < 5e-11)
			return end;
		start = end;
		end = end - d;
	}
	return end;
}

double equation(double n, double e, double x){
	double p = 1.0/n;
    double residual = e - ((n-2.0)/n)*log2(1.0/p);
    return (p+x)*log2(1.0/(p+x)) + (p-x)*log2(1.0/(p-x)) - residual;
}

double numerical_solve(double (*func)(double, double, double), double n, double e){
	return secant_method(func, n, e, 1e-10, -1e-10+ 1.0/n);
}

int generate_pdf(double pdf[], int size , double e){
	
	int i = 0;
	if(size <= 0)
		return -1;
	for(i=0; i< size; i++)
		pdf[i]=0.0;
    double num_sym = (int) ceil(pow(2.0,e));
    for(i = 0; i < (int)num_sym; i++){
        pdf[i] = 1.0/num_sym;
	}
    double epsilon = numerical_solve(equation, num_sym, e);
    pdf[0] -= epsilon;
    pdf[1] += epsilon;
	return 0;
}

void print_pdf(double pdf[], int size){
	int i;
	for(i=0; i< size; i++)
		printf("%f, ", pdf[i]);
	printf("\n");
}

int main(int argc, char* argv[]){
	int i=0;
	
	double pdf[PDF_SIZE];
	double cdf[PDF_SIZE];
	double key = .455;
	generate_pdf(pdf, PDF_SIZE, i/100.0);
	calculate_cdf(pdf, PDF_SIZE, cdf);
	int index = binary_search(key, cdf, PDF_SIZE);
	print_pdf(cdf, PDF_SIZE);
	printf("%f is found at %d, which is between %f and %f\n", key, index, cdf[index-1], cdf[index]);
	for(i=0; i< 801; i++){
		generate_pdf(pdf, PDF_SIZE, i/100.0);
		printf("Entropy requested: %f\n",i/100.0);
		print_pdf(pdf, 5);
		printf("Entropy generated: %f\n\n", pdf_entropy(pdf, PDF_SIZE));
	}
	return 0;
}
