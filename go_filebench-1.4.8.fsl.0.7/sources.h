#ifndef SOURCES_H
#define SOURCES_H

struct source {
	double s_entropy;
	struct source_operations *s_ops; 
};

struct source_operations {
	int (*fill)(struct source *, void *, unsigned int);
};

extern struct source_operations dummy_operations;
extern struct source_operations constant_operations;
extern struct source_operations entropy_operations;

int dummy_fill(struct source *ds, void *buf, unsigned int size);
int constant_fill(struct source *ds, void *buf, unsigned int size);
int entropy_fill(struct source *ds, void *buf, unsigned int size);
int register_datasource(struct source **source);
int verify_ds(struct source *source);

#endif
