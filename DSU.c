#include "DSU.h"

void swap(int *a, int *b);

void swap(int *a, int *b)
{
	int c = *b;
	*b = *a;
	*a = c;
}

DSUData* initDSU(int length)
{
	DSUData * data = (DSUData*)malloc(sizeof(DSUData));
	data->parent = (int*)malloc(sizeof(int)*(length+1));
	data->rank = (int*)malloc(sizeof(int)*(length+1));
	return data;
}

void make_set(int v, DSUData *data) {
	data->parent[v] = v;
	data->rank[v] = 0;
}

int find_set(int v, DSUData *data) {
	if (v == data->parent[v])
		return v;
	return data->parent[v] = find_set(data->parent[v], data);
}

void union_sets(int a, int b, DSUData *data) {
	a = find_set(a, data);
	b = find_set(b, data);
	if (a != b) {
		if (data->rank[a] < data->rank[b])
			swap(&a, &b);
		data->parent[b] = a;
		if (data->rank[a] == data->rank[b])
			++data->rank[a];
	}
}

void destroyDSU(DSUData * data) {
	free(data->parent);
	free(data->rank);
	free(data);
}