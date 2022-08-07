
/*
bubble sortは値を1つずつ比較してから値を交換しますが、
一度に交換するのは前後の値の1つだけですが、
これは必ず再比較してから比較を繰り返し、交換を繰り返します。
値の比較と交換が大幅に増加します。

quick sortは、ある値を中間値として選び、
それ以外の値を中間値よりも小さいものと中間値よりも大きいものに分割するというもので、
少なくとも 一つの辺が中央値よりも小さいか大きいと判断されます。
これを繰り返し行うことで、必要な比較と値交換の回数を大幅に減らすことができます。
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define swap(x, y){int tmp; tmp = x; x = y; y = tmp;}

int* quick_sort(int* arr, int left, int right, int* steps)
{
	if (left < right)
	{
		int mid = arr[(left + right) / 2];
		int i = left - 1;
		int j = right + 1;

		while (1)
		{
			while (arr[++i] < mid);
			while (arr[--j] > mid);

			if (i >= j)
			{
				break;
			}
			swap(arr[i], arr[j]);
			*steps += 1;
		}

		quick_sort(arr, left, i - 1, steps);
		quick_sort(arr, j + 1, right, steps);
	}
}

void bubble_sort(int* arr, int input_max, int* steps)
{
	for (int i = 0; i < input_max; i++)
	{
		for (int j = 0; j < input_max - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
				*steps += 1;
			}
		}
	}
}

int* array_make(int* input_max)
{
	int* data_num, min = 10000;

	srand((unsigned)time(NULL));

	for (int i = 0; i < 10; i++)
	{
		*input_max = (rand() % (50000 - min + 1) + min);
	}

	data_num = (int*)malloc(sizeof(int) * *input_max);

	for (int i = 0; i < *input_max; i++)
	{
		data_num[i] = rand();
	}

	return data_num;
}

int* array_copy(int* arr, int input_max)
{
	int* data_num;

	data_num = (int*)malloc(sizeof(int) * input_max);

	for (int i = 0; i < input_max; i++)
	{
		data_num[i] = arr[i];
	}

	return data_num;
}

void print_data(int* arr, int input_max)
{
	for (int i = 0; i < input_max; i++)
	{
		printf("%d.%d  ", i + 1, arr[i]);
		if (i > 0 && i % 10 == 0)
		{
			printf("\n");
		}
	}
	printf("\n");
}

int main()
{
	int input_max, bubble_steps = 0, quick_steps = 0;
	double start, end;

	int* arr = array_make(&input_max);
	int* bubble_arr = array_copy(arr, input_max);
	int* quick_arr = array_copy(arr, input_max);

	printf("number of input data:%d\n\n", input_max);
	//print_data(arr, input_max);

	start = clock();
	bubble_sort(bubble_arr, input_max, &bubble_steps);
	end = clock();
	printf("Bubble steps:%d    Bubble sort usage time:%lf\n\n", bubble_steps, (end - start) / CLOCKS_PER_SEC);
	//print_data(bubble_arr, input_max);

	start = clock();
	quick_sort(quick_arr, 0, input_max - 1, &quick_steps);
	end = clock();
	printf("Quick steps:%d    Quick sort usage time:%lf\n\n", quick_steps, (end - start) / CLOCKS_PER_SEC);
	//print_data(quick_arr, input_max);

	//system("PAUSE");
	free(arr);
	free(bubble_arr);
	free(quick_arr);
	return 0;
}
