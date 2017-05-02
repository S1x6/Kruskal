#ifndef _DSU_H
#define _DSU_H

#include <stdio.h>
#include <malloc.h>

typedef struct _DSUData {
	int * parent;
	int * rank;
} DSUData;

void make_set(int v, DSUData *data);
int find_set(int v, DSUData *data);
void union_sets(int a, int b, DSUData *data);
DSUData * initDSU(int length);
void destroyDSU(DSUData * data);

#endif // ! _H_DSU
