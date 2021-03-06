#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Maxfiles.h"
#include "MaxSLiCInterface.h"

#define n MatrixVector_N

float x[n], a[n][n], out[n];

void prettyPrint();

void check();

int main(void) {

	// Generate input data and expected results
	for (int i = 0; i < n; ++i) {
		x[i] = random() % 100;
		for (int j = 0; j < n; j++)
			a[i][j] = random() % 100;
	}

	printf("Running on DFE.\n");
	MatrixVector(*a, x, out);

	prettyPrint();

	check();

	printf("Done.\n");
	return 0;
}

void prettyPrint() {
	// Pretty print the output
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			printf("%6.3f ", a[i][j]);

		if (i == n / 2)
					printf("  X  ");
				else
					printf("     ");

		printf("%6.3f ", x[i]);

		if (i == n / 2)
			printf("  =   ");
		else
			printf("     ");

		for (int j = 0; j < n; ++j)
			if (i == n / 2)
				printf("%6.3f ", out[j]);
			else
				printf("       ");
		printf("\n");
	}
}

void check() {
	for (int i = 0; i < n; ++i) {
		float expected = 0;
		for (int j = 0; j < n; j++) {
			expected += x[j] * a[i][j];
		}
		if (expected != out[i])
			printf("Error! Expected: %.3f, got %.3f\n", expected, out[i]);
	}
}
