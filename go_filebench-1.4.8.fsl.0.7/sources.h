#include<stdio.h>

struct source {
	char* s_name;
	double s_entropy;
	struct source_operations *sops; 
};

struct source_operations{
	int (*fill)(struct source *, void *buf);
};
