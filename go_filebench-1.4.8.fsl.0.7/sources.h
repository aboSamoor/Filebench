struct source {
	char *name;
	double s_entropy;
	struct source_operations *s_ops; 
};

struct source_operations {
	int (*fill)(struct source *, void *, unsigned int);
};
