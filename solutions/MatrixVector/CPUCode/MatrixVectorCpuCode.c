#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Maxfiles.h"
#include "MaxSLiCInterface.h"

#define n MatrixVector_N

float x[n], a[n][n], expected[n], out[n];

void prettyPrint();

int main(void) {

	// Generate input data and expected results
	for (int i = 0; i < n; ++i) {
		x[i] = random() % 100;
		expected[i] = 0;
		for (int j = 0; j < n; j++) {
			a[i][j] = random() % 100;
			expected[i] += x[i] * a[i][j];
		}
	}

	printf("Running on DFE.\n");
	MatrixVector(n, 1, x, a, out);

	prettyPrint();

	printf("Done.\n");
	return 0;
}

void prettyPrint() {
	// Pretty print the output
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			if (i == n / 2)
				printf("%6.3f ", x[j]);
			else
				printf("       ");
		if (i == n / 2)
			printf("  X  ");
		else
			printf("     ");

		for (int j = 0; j < n; ++j)
			printf("%6.3f ", a[i][j]);

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
