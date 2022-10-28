#include "func.h"

int Max(int a[], int n)
{
	int max = a[0];
	for (int i = 1; i < n; ++i)
		if (a[i] > max) max = a[i];
	return max;
}

double Avg(int a[], int n)
{
	double avg = 0.0;
	for (int i = 0; i < n; ++i)
		avg += a[i];
	return avg / n;
}
