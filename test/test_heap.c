#include "test_def.h"
#if defined __VSCODE__ || defined TEST_PROJECT_HEAP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "test_def.h"
#include "../lib/cdsar.h"

#define N    8

typedef struct _hnode
{
	int a;
	int b;
}hnode;

bool cmp_max(const void* x, const void* y) { return ((hnode*)x)->a > ((hnode*)y)->a; }
bool cmp_min(const void* x, const void* y) { return ((hnode*)x)->a < ((hnode*)y)->a; }

void test_heap()
{
	int i = 0;

	//create data for test
	hnode** pdata = (hnode**)malloc(sizeof(hnode*) * N);
	srand((unsigned int)time(NULL));
	for (i = 0; i < N; i++)
	{
		pdata[i] = (hnode*)malloc(sizeof(hnode));
		pdata[i]->a = i;
		pdata[i]->b = rand() % N;
	}

	//maxheap
	_pheap maxheap = heap_create(cmp_max);
	for (i = 0; i < N; ++i)
	{
		maxheap->insert(maxheap, pdata[i]);
	}
	printf("-----------<TEST MAXHEAP]\n");
	printf("[size]: %d\n", maxheap->_sz);

	hnode* tmp = NULL;
	while ((tmp = (hnode*)maxheap->pop(maxheap)) != NULL)
	{
		printf("%d %d\n", tmp->a, tmp->b);
	}
	printf("[size]: %d\n", maxheap->_sz);
	maxheap->free(&maxheap);

	//minheap
	_pheap minheap = heap_create(cmp_min);
	for (i = 0; i < N; ++i)
	{
		minheap->insert(minheap, pdata[i]);
	}
	//minheap->clean(minheap);
	printf("-----------<TEST MINHEAP]\n");
	printf("[size]: %d\n", minheap->_sz);

	while (!minheap->empty(minheap))
	{
		tmp = (hnode*)minheap->pop(minheap);
		printf("%d %d\n", tmp->a, tmp->b);
	}
	printf("[size]: %d\n", minheap->_sz);
	minheap->free(&minheap);

	//release memory
	for (i = 0; i < N; i++) { free(pdata[i]); }
	free(pdata);
}

int main(int argv, char** args)
{
	test_heap();

	__PRAGMA_END__
}
#endif