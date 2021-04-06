#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<atltime.h>

int ** makeMatrix(int gap) {
	int ** middle;
	middle = (int **)malloc(gap * sizeof(int *));
	for (int i = 0; i < gap; i++)
		middle[i] = (int *)malloc(gap * sizeof(int));
	for (int i = 0; i < gap; i++) {
		for (int j = 0; j < gap; j++) {
			middle[i][j] = 0;
		}
	}
	return middle;
}

int ** MatrixAdd(int * a[], int x1, int y1, int * b[], int x2, int y2, int gap) {
	if (gap == 1) {
		int ** middle;
		middle = (int **)malloc(sizeof(int *));
		middle[0] = (int *)malloc(sizeof(int));
		middle[0][0] = a[x1][y1] + b[x2][y2];
		return middle;
	}
	else {
		int ** middle = makeMatrix(gap);
		for (int i = 0; i < gap; i++) {
			for (int j = 0; j < gap; j++) {
				middle[j][i] = a[x1 + j][y1 + i] + b[x2 + j][y2 + i];
			}
		}
		return middle;
	}
}

int ** MatrixSub(int * a[],  int x1, int y1, int * b[],int x2, int y2, int gap) {
	if (gap == 1) {
		int ** middle;
		middle = (int **)malloc(sizeof(int *));
		middle[0] = (int *)malloc(sizeof(int));
		middle[0][0] = a[x1][y1] - b[x2][y2];
		return middle;
	}
	int ** middle = makeMatrix(gap);
	for (int i = 0; i < gap; i++) {
		for (int j = 0; j < gap; j++) {
			middle[j][i] = a[x1 + j][y1 + i] - b[x2 + j][y2 + i];
		}
	}
	return middle;
}

int** MatrixMultiplyStrassen(int * a[], int x1, int y1 ,int * b[],  int x2, int y2, int gap) {
	if (gap == 1) {
		int **gapOne;
		gapOne = (int **)malloc(sizeof(int *));
		gapOne[0] = (int *)malloc(sizeof(int));
		gapOne[0][0] = a[x1][y1] * b[x2][y2];
		return gapOne;
	}
	int ngap = gap / 2;
	int ** fin = makeMatrix(gap);
	int ** S1;
	S1 = MatrixMultiplyStrassen(a, x1, y1, MatrixSub(b, x2 + ngap, y2, b, x2 + ngap, y2 + ngap, ngap), 0, 0, ngap);
	int ** S2;
	S2 = MatrixMultiplyStrassen(MatrixAdd(a, x1, y1, a, x1 + ngap, y1, ngap), 0, 0, b, x2 + ngap, y2 + ngap, ngap);
	int ** S3 ;
	S3 = MatrixMultiplyStrassen(MatrixAdd(a, x1, y1 + ngap, a, x1 + ngap, y1 + ngap, ngap), 0, 0, b, x2, y2, ngap);
	int ** S4;
	S4 = MatrixMultiplyStrassen(a, x1 + ngap, y1 + ngap, MatrixSub(b, x2, y2 + ngap, b, x2, y2, ngap), 0, 0, ngap);
	int ** S5 ;
	S5 = MatrixMultiplyStrassen(MatrixAdd(a, x1, y1, a, x1 + ngap, y1 + ngap, ngap), 0, 0, MatrixAdd(b, x2, y2, b, x2 + ngap, y2 + ngap, ngap), 0,0,ngap);
	int ** S6;
	S6 = MatrixMultiplyStrassen(MatrixSub(a, x1 + ngap, y1, a, x1 + ngap, y1 + ngap, ngap), 0, 0, MatrixAdd(b, x2, y2 + ngap, b, x2 + ngap, y2 + ngap, ngap), 0, 0, ngap);
	int ** S7 ;
	S7 = MatrixMultiplyStrassen(MatrixSub(a, x1 , y1, a, x1 , y1 + ngap, ngap), 0, 0, MatrixAdd(b, x2, y2 , b, x2 + ngap, y2 , ngap), 0, 0, ngap);
	int ** I;
	I = MatrixAdd(MatrixAdd(S5, 0, 0, S6, 0, 0, ngap), 0, 0, MatrixSub(S4, 0, 0, S2, 0, 0, ngap), 0, 0, ngap);
	int ** J;
	J = MatrixAdd(S1, 0, 0, S2, 0, 0, ngap);
	int ** K;
	K = MatrixAdd(S3, 0, 0, S4, 0, 0, ngap);
	int ** L;
	L = MatrixSub(MatrixSub(S1, 0, 0, S7, 0, 0, ngap), 0, 0, MatrixSub(S3, 0, 0, S5, 0, 0, ngap), 0, 0, ngap);

	for (int i = 0; i < ngap; i++) {
		for (int j = 0; j < ngap; j++) {
			fin[i][j] = I[i][j];
			fin[i + ngap][j] = J[i][j];
			fin[i][j + ngap] = K[i][j];
			fin[i + ngap][j + ngap] = L[i][j];
		}
	}

	return fin;
}

int ** MatrixMultiplyMath(int * a[], int * b[], int n) {
	int **fin = makeMatrix(n);
	int sum = 0;
	for (int i = 0; i < n; i++) {
		
		for (int j = 0; j < n; j++) {
			sum = 0;
			for (int k = 0; k < n; k++) {
				sum += a[k][i] * b[j][k];
			}
			fin[j][i] = sum;
		}
	}
	return fin;
}

void test(int n, int flag) {
	int **a;
	int **b = makeMatrix(n);
	int **c = makeMatrix(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			b[j][i] = j + 1;
			c[j][i] = n - j;
		}
	}
	clock_t start, end;
	double time;
	if (flag == 1) {
		start = clock();
		for (int t = 0; t < 10; t++) {
			a = MatrixMultiplyStrassen(b, 0, 0, c, 0, 0, n);
		}
		end = clock();
	}
	else {
		start = clock();
		for (int t = 0; t < 10; t++) {
			a = MatrixMultiplyMath(b, c, n);
		}
		end = clock();
	}
	time = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf_s("%d : %f \n", n, time);
	
}

void test1(int n) {
	int **a;
	int **b = makeMatrix(n);
	int **c = makeMatrix(n);
	clock_t start, end;
	double time;	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			b[j][i] = j + 1;
			c[j][i] = n - j;
		}
	}
	
		a = MatrixMultiplyStrassen(b, 0, 0, c, 0, 0, n);
	

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf_s("%d ", a[j][i]);
		}
		printf_s("\n");
	}
}

void test2(int n) {
	int **a;
	int **b = makeMatrix(n);
	int **c = makeMatrix(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			b[j][i] = j + 1;
			c[j][i] = n - j;
		}
	}
	a = MatrixMultiplyMath(b, c, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf_s("%d ", a[j][i]);
		}
		printf_s("\n");
	}
}

int main() {
	/*for (int i = 0; i <= 1; i++) {
		if (i == 1)
			printf_s("Strassen: \n");
		else
			printf_s("Math:\n");
		for(int j=10;j<=40;j+=2)
			test(j, i);
	}*/
		test(64, 1);
}