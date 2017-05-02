#define _CRT_SECURE_NO_WARNINGS

#include "DSU.h"
#include "ListNode.h"
#include <stdio.h>
#include <stdlib.h>

#define ERROR_WRONG_VERTEX_NUM 1
#define ERROR_WRONG_EDGE_NUM 2
#define ERROR_WRONG_LINES_NUM 3
#define ERROR_NO_TREE 4

typedef struct _Edge {
	int from;
	int to;
	int weight;
} Edge;

void destroyEdges(Edge ** edges, int num);
int checkInput(FILE * fout, int vert, int edge);
int comparator(const void* p1, const void* p2);
void printEdges(FILE * fout, Edge ** edges, ListNode * list);

char * isAdded;
int main()
{
	int vert_num = -1, edge_num = -1;
	int i, ver1, ver2, weight;
	FILE * fin = fopen("in.txt", "r");
	FILE * fout = fopen("out.txt", "w");
	if (fscanf(fin, "%d", &vert_num) == -1) {
		printf("bad number of lines");
		fclose(fin);
		fclose(fout);
		return 0;
	}
	if (fscanf(fin, "%d", &edge_num) == -1) {
		printf("bad number of lines");
		fclose(fin);
		fclose(fout);
		return 0;
	}
	if (checkInput(fout, vert_num, edge_num)) {
		fclose(fin);
		fclose(fout);
		return 0;
	}
		
	
	Edge ** edges = (Edge**)malloc(sizeof(Edge *) * edge_num);
	i = 0;
	for (; i < edge_num; i++) {
		if (fscanf(fin, "%d", &ver1) == -1  || fscanf(fin, "%d", &ver2) == -1 || fscanf(fin, "%d", &weight) == -1) {
			fprintf(fout, "bad number of lines");
			fclose(fin);
			fclose(fout);
			return 0;
		}
		if (ver1 > vert_num || ver1 < 0 || ver2 < 0 || ver2 > vert_num) {
			fprintf(fout, "bad vertex");
			fclose(fin);
			fclose(fout);
			return 0;
		}
		if (weight < 0) {
			fprintf(fout, "bad length");
			fclose(fin);
			fclose(fout);
			return 0;
		}
		Edge *edge = (Edge*)malloc(sizeof(Edge));
		edge->from = ver1;
		edge->to = ver2;
		edge->weight = weight;
		edges[i] = edge;
	}
	qsort(edges, edge_num, sizeof(Edge*), comparator);
	int vertex_left = vert_num;
	int sum_path = 0;
	ListNode * list_index = NULL;
	isAdded = (char*)calloc(vert_num  + 1, sizeof(char));
	DSUData * dsu = initDSU(vert_num);
	i = 1;
	for (; i <= vert_num; i++) {
		make_set(i, dsu);
	}
	i = 0;
	for (; i < edge_num; i++) {
		int a = find_set(edges[i]->from, dsu);
		int b = find_set(edges[i]->to, dsu);
		if (a != b)
		{
			union_sets(a, b, dsu);
			sum_path += edges[i]->weight;
			list_index = push(i, list_index);
			if (!isAdded[edges[i]->from]) {
				isAdded[edges[i]->from] = 1;
				vertex_left--;
			}
			if (!isAdded[edges[i]->to]) {
				isAdded[edges[i]->to] = 1;
				vertex_left--;
			}
		}
	}
	if (!vertex_left || vert_num == 1 )
		printEdges(fout, edges, list_index);
	else fprintf(fout, "no spanning tree");
	destroyDSU(dsu);
	destroyEdges(edges, edge_num);
	return 0;
}

void printEdges(FILE * fout, Edge ** edges, ListNode * list)
{
	int i = 0;
	while (list)
	{
		int a = pop(&list);
		fprintf(fout, "%d %d\n", edges[a]->from, edges[a]->to);
	}
}

int checkInput(FILE * fout, int vert, int edge)
{
	if (vert == -1 || edge == -1) {
		fprintf(fout, "bad number of lines");
		return ERROR_WRONG_LINES_NUM;
	}
	if (vert < 0 || vert > 5000) {
		fprintf(fout, "bad number of vertices");
		return ERROR_WRONG_VERTEX_NUM;
	}
	if (edge < 0 || edge > vert*(vert + 1) / 2) {
		fprintf(fout, "bad number of edges");
		return ERROR_WRONG_EDGE_NUM;
	}
	if (vert == 0)
	{
		fprintf(fout, "no spanning tree");
		return ERROR_NO_TREE;
	}
	return 0;
}

int comparator(const void* p1, const void* p2) {
	return (*(Edge**)p1)->weight - (*(Edge**)p2)->weight;
}

void destroyEdges(Edge ** edges, int num) {
	int i = 0;
	for (; i < num; i++)
	{
		free(edges[i]);
	}
	free(edges);
}