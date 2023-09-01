
#include <iostream>
using namespace std;


//по времени O(n*log n)
// по памяти O(n)

void merge(int* arr, int l, int m, int r)
{
    int nl = m - l + 1;
    int nr = r - m;

    // создаем временные массивы
    int* left = new int[nl];
    int* right = new int[nr];

    // копируем данные во временные массивы
    for (int i = 0; i < nl; i++)
        left[i] = arr[l + i];
    for (int j = 0; j < nr; j++)
        right[j] = arr[m + 1 + j];

    int i = 0, j = 0;
    int k = l;  // начало левой части

    while (i < nl && j < nr) {
        // записываем минимальные элементы обратно во входной массив
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    // записываем оставшиеся элементы левой части
    while (i < nl) {
        arr[k] = left[i];
        i++;
        k++;
    }
    // записываем оставшиеся элементы правой части
    while (j < nr) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

/*
int* arr - сортируемый массив
int l - начало сортируемой части
int r - конец сортируемой части
*/
void mergeSort(int* arr, int l, int r)
{
    if (l >= r)
        return; // выходим из рекурсии
    int m = (l + r - 1) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

int main()
{
	int ma = 10;
	int  arr[12]{ 33, 36, 27, 15, 43, 35, 36, 42, 49, 21 };
	int  output[12]{ 0 };
    int  n = sizeof(arr) / sizeof(int);

    mergeSort(arr, 0, 11);

    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";

	return 0;
}