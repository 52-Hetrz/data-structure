#include<stdio.h>
#include<stdlib.h>

void countSort(int * nums, int n) {
	int B[101] = { 0 };
	int * C = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		B[nums[i]]++;
	}

	for (int i = 1; i < 101; i++) {
		B[i] = B[i] + B[i - 1];
	}

	for (int i = 0; i < n; i++) {
		C[B[nums[i]]-1] = nums[i];
		B[nums[i]]--;
	}

	for (int i = 0; i < n; i++) {
		nums[i] = C[i];
	}
}

int main() {
	int a[2] = { 100,3 };
	countSort(a,2);
	for (int i = 0; i < 2; i++) {
		printf_s("%d  ", a[i]);
	}
}