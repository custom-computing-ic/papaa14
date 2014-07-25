#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Maxfiles.h"
#include "MaxSLiCInterface.h"

#define n 16
int a[n], b[n], out[n];

void prettyPrint(int expected, int out);

void check(int expected, int actual);

int main(void) {

	// Generate input data
	srand(0);

	int expected = 0;
	for(int i = 0; i < n; ++i) {
		a[i] = random() % 100;
		b[i] = random() % 100;
		expected += a[i] * b[i];
	}

	printf("Running on DFE.\n");
	DotProduct(n / 4, a, b, out);

	// Reduce results on CPU
	int s = 0;
	for (int i = 0 ; i < n; ++i)
		s += out[i];

	prettyPrint(expected, s);

	check(expected, s);

	printf("Done.\n");
	return 0;
}

void prettyPrint(int expected, int result) {
	// Pretty print the output
	for (int i = 0; i < n; ++i)
		printf("%6d ", a[i]);
	printf("  X\n");

	for (int i = 0; i < n; ++i)
		printf("%6d ", b[i]);

	printf("\n = %d (expected = %d)\n", result, expected);
}

void check(int expected, int s) {
	if (expected != s) {
		printf("Error: Expected %d, got %d!",
				expected, s);
	}
}
