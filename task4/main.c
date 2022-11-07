#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

#define BIGRAND (rand()*rand())

void shuffle(int* niz, int n) {
	for (int i = 0; i < n - 1; i++) {
		int j = i + BIGRAND % (n - i);
		int tmp = niz[i];
		niz[i] = niz[j];
		niz[j] = tmp;
	}
}

int* generate(int n) {
	int* niz = (int*)malloc(sizeof(int) * n);
	niz[0] = 1 + BIGRAND % 3;
	for (int i = 1; i < n; i++)
		niz[i] = niz[i - 1] + BIGRAND % 3 + 1;
	shuffle(niz, n);
	return niz;
}

void print_array(int *arr, size_t size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}

	printf("\n");
}

int comparator(const void *a, const void *b) {
	return (*(int*)a - *(int*)b);
}

int presjek(int *skup_a, int *skup_b, size_t size) {
	int count = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (skup_a[i] == skup_b[j])
			{
				count++;
			}
		}
	}

	return count;
}

int presjek_jedan_sortiran(int *skup_a, int *skup_b, size_t size) {
	qsort(skup_b, size, sizeof(int), comparator);

	int count = 0;

	for (int i = 0; i < size; i++) {
		int *result = (int *)bsearch(skup_a + i, skup_b, size, sizeof(int), comparator);

		if (result != NULL) {
			count++;
		}
	}

	return count;
}

int presjek_oba_sortirana(int *skup_a, int *skup_b, size_t size) {
	qsort(skup_a, size, sizeof(int), comparator);
	qsort(skup_b, size, sizeof(int), comparator);

	int count = 0;

	int i = 0, j = 0;

	while (i < size && j < size) {
		if (skup_a[i] == skup_b[j])
		{
			count++;
			i++;
			j++;
			continue;
		}

		if (skup_a[i] < skup_b[j])
		{
			i++;
			continue;
		}

		if (skup_b[j] < skup_a[i])
		{
			j++;
			continue;
		}
	}

	return count;
}

int get_max(int* arr, size_t size) 
{
	int max = -1;

	for (int i = 0; i < size; i++)
	{
		if (arr[i] > max)
			max = arr[i];
	}

	return max;
}

int presjek_po_indeksima(int* skup_a, int* skup_b, size_t size) {
	int index_size = max(get_max(skup_a, size), get_max(skup_b, size));
	
	int* index_a = (int *)malloc(index_size * sizeof(int));
	int* index_b = (int *)malloc(index_size * sizeof(int));

	int count = 0;

	for (int i = 0; i < index_size; i++) 
	{
		index_a[i] = 0;
		index_b[i] = 0;
	}

	for (int i = 0; i < size; i++) {
		int a = skup_a[i];
		int b = skup_b[i];

		index_a[a] = 1;
		index_b[b] = 1;
	}

	for (int i = 0; i < index_size; i++) {
		if (index_a[i] && index_b[i]) {
			count++;
		}
	}

	return count;
}

void test(char *algo_name, int count, int (*algo_ptr)(int*, int*, int)) 
{
	int* skup_a = generate(count);
	int* skup_b = generate(count);

	clock_t start = clock();
	(*algo_ptr)(skup_a, skup_b, count);
	clock_t time = clock() - start;

	printf("Execution of %s took %f seconds.\n", algo_name, (float)time / CLOCKS_PER_SEC);

	free(skup_a);
	free(skup_b);
}

void main() {
	int count = 10000;

	test("presjek", count, &presjek);
	test("presjek_jedan_sortiran", count, &presjek_jedan_sortiran);
	test("presjek_oba_sortirna", count, &presjek_oba_sortirana);
	test("presjek_po_indeksima", count, &presjek_po_indeksima);
}