#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <iostream>
#include <locale.h>
#include <windows.h>
#include <cstring>
#include <fstream>
using namespace std;

#define INF 9999999

#define V 5

FILE* file = fopen("prym zapysal.txt", "a");


void Alg_Prima(int n, int** matr, int* selected) {

	int no_edge;
	// Изначально установим false 

	for (int i = 0; i < n; i++)
	{
		selected[i] = false;
	}

	no_edge = 0;

	// число ребер в минимальном остовном дереве будет 
	// всегда меньше (V -1), где V-число вершин в
	//графе


	selected[0] = true;

	int x;            //  номер строки
	int y;            //  номер столбца
	int tr = 0;

	printf("Ребро  :  Вес\n");

	while (no_edge < n - 1) {
		int min = INF;
		x = 0;
		y = 0;

		for (int i = 0; i < n; i++)
		{
			if (selected[i])
			{
				for (int j = 0; j < n; j++)
				{
					if (!selected[j] && matr[i][j]) // не выбрана и есть край
					{
						if (min > matr[i][j])
						{
							min = matr[i][j];
							x = i;
							y = j;
						}

					}
				}
			}
		}
		tr += matr[x][y];
		printf("%d ", x);  printf(" - ");  printf("%d ", y);
		printf(" : ");  printf("%d\n", matr[x][y]);

		fprintf(file, "%d ", x); fprintf(file, " - "); fprintf(file, "%d ", y);
		fprintf(file, " : ");  fprintf(file, "%d\n", matr[x][y]);


		selected[y] = true;
		no_edge++;
	}
	printf("Размер остовного дерева %d\n", tr);
}

void Output(int** matr, int n)
{
	for (int i = 0; i < n; i++) // вывод сгенерированной матрицы
	{

		for (int j = 0; j < n; j++)
		{
			printf("%3d ", matr[i][j]);
		}
		printf("\n");
	}

	printf("\n   ");
}


int main()
{


	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int** matr;//указатель для массива указателей 
	int* selected; // Массив для отслеживания вершины
	int* stp;
	int n, d;
	d = 0;


	while (d != 3) {

		printf(" ГЛАВНАЯ СТРАНИЦА : \n");
		printf(" 1) Сгенерировать матрицу автоматически (1) \n");
		printf(" 2) Ввести матрицу вручную (2) \n");
		printf(" 3) Закрыть (3)\n");

		d = _getch();

		if (d == '1')
		{
			printf("\n");
			printf(" Введите размер матрицы:");
			scanf_s("%d", &n);
			stp = (int*)malloc(n * sizeof(int));
			selected = (int*)malloc(n * sizeof(int)); //выделение памяти под массив отслеживания вершин

			matr = (int**)malloc(n * sizeof(int*)); //выделение памяти под массив указателей


			for (int i = 0; i < n; i++) //выделение памяти для массива значений
			{
				matr[i] = (int*)malloc(n * sizeof(int));
			}


			for (int i = 0; i < n; i++) // генерация массива случайных чисел
			{
				for (int j = 0; j < n; j++)
				{
					if (i == j)
					{
						matr[i][j] = 0;
					}

					if (i < j)
					{
						matr[i][j] = rand() % 80;
						matr[j][i] = matr[i][j];
					}

					if (matr[i][j] > 0)
					{
						stp[i]++;
					}
				}
			}

			printf("Результат: \n");


			Output(matr, n);
			for (int i = 0; i < n; i++)
			{
				if (stp[i] == 0)
				{
					printf("Алгоритм не работает при наличии изолированных вершин");
					exit(0);
				}
			}
			Alg_Prima(n, matr, selected);
		}


		if (d == '2')
		{
			printf("\n");
			printf(" Введите размер матрицы:");
			scanf_s("%d", &n);

			stp = (int*)malloc(n * sizeof(int));
			selected = (int*)malloc(n * sizeof(int)); //выделение памяти под массив отслеживания вершин

			matr = (int**)malloc(n * sizeof(int*)); //выделение памяти под массив указателей


			for (int i = 0; i < n; i++) //выделение памяти для массива значений
			{
				matr[i] = (int*)malloc(n * sizeof(int));
			}

			for (int i = 0; i < n; i++) // генерация массива случайных чисел
			{
				for (int j = 0; j < n; j++)
				{
					printf("Введите элемент матрицы:\n");

					if (i == j)
					{
						matr[i][j] = 0;
						printf("%d\n", matr[i][j]);
					}

					if (i < j)
					{

						scanf_s("%d", &matr[i][j]);
						matr[j][i] = matr[i][j];
					}

					if (matr[i][j] > 0)
					{
						stp[i]++;
					}
				}
			}

			printf("Результат: \n");


			Output(matr, n);

			for (int i = 0; i < n; i++)
			{
				if (stp[i] == 0)
				{
					printf("Алгоритм не работает при наличии изолированных вершин");
					exit(0);
				}
			}
			Alg_Prima(n, matr, selected);
		}

		if (d == '3')
		{

			exit(0);

		}
	}

	_getch();
	return 1;
}
