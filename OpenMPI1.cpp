#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 2048
#define M 4096
double a[N][M], b[M][N], c[N][N];
int main(void)
{
	int i, j, k;
	double t1, t2;

	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++)
			a[i][j] = b[j][i] = rand() % 1000;
	t1 = omp_get_wtime();
	int num = 12;
	omp_set_num_threads(num);

#pragma omp parallel for shared(a, b, c) private(i, j, k)
	for (i = 0; i < N; i++) {

		for (j = 0; j < N; j++) {
			c[i][j] = 0.0;

			for (k = 0; k < N; k++) c[i][j] += a[i][k] * b[k][j];
		}
	}
	t2 = omp_get_wtime();

	//Время:
	printf("%lf\n", t2 - t1);
}