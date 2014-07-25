#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Maxfiles.h"
#include "MaxSLiCInterface.h"

// Matrix size set to match hardware
#define n MatrixMultiplier_N

float a[n][n], b[n][n], out[n][n];

// Print the multiplication results
void prettyPrint();

// Check the FPGA results against CPU implementation
void check();

int main(void) {

	// Generate input data
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			a[i][j] = random() % 10;
			b[i][j] = random() % 10;
		}

	printf("Running on DFE.\n");
	int numMults = 1;
	MatrixMultiplier(numMults, // param_numMults
			// stream inputs:
			*a, *b,
			// stream outputs:
			*out);

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
		for (int j = 0; j < n; ++j)
			printf("%6.3f ", b[i][j]);
		if (i == n / 2)
			printf("  =  ");
		else
			printf("     ");
		for (int j = 0; j < n; ++j)
			printf("%7.3f ", out[i][j]);
		printf("\n");
	}
}

void check() {
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			float expected = 0;
			for (int k = 0; k < n; ++k)
				expected += a[i][k] * b[k][j];
			if (out[i][j] != expected) {
				printf("Error! Expected %f, got %f\n", expected, out[i][j]);
			}
		}
}
