#include<stdio.h>

void InsertSort(int* nums, int n) {

	int middle, current;

	for (int j = 1; j < n; j++) {

		current = nums[j];

		for (int i = j - 1; i >= 0; i--) {
			if (nums[i] > current)
				nums[i + 1] = nums[i];
			else {
				nums[i + 1] = current;
				break;
			}
			if (i == 0)
				nums[i] = current;
		}

	}

}

int main() {
	int a[8]= { 2,3,6,3,4,5,1,8 };

	InsertSort(a, 8);
	for (int i = 0; i < 8; i++)
		printf_s("%d ", a[i]);
}
