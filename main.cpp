#include <chrono>
#include <future>
#include <iostream>
#include <thread>
using namespace std;

// по времени O(n*log n)
//  по памяти O(n)

const unsigned int max_numb_of_treads{std::thread::hardware_concurrency()};
bool multithread = true;

void merge(int* arr, long l, long m, long r) {
  long number_elements_left = m - l + 1;
  long number_elements_right = r - m;

  // создаем временные массивы
  long* left = new long[number_elements_left];
  long* right = new long[number_elements_right];

  // копируем данные во временные массивы
  for (long i = 0; i < number_elements_left; i++) left[i] = arr[l + i];
  for (long j = 0; j < number_elements_right; j++) right[j] = arr[m + 1 + j];

  long i = 0, j = 0;
  long k = l;  // начало левой части

  while (i < number_elements_left && j < number_elements_right) {
    // записываем минимальные элементы обратно во входной массив
    if (left[i] <= right[j]) {
      arr[k] = left[i];
      i++;
    } else {
      arr[k] = right[j];
      j++;
    }
    k++;
  }
  // записываем оставшиеся элементы левой части
  while (i < number_elements_left) {
    arr[k] = left[i];
    i++;
    k++;
  }
  // записываем оставшиеся элементы правой части
  while (j < number_elements_right) {
    arr[k] = right[j];
    j++;
    k++;
  }
}

/*
long* arr - сортируемый массив
long l - начало сортируемой части
long r - конец сортируемой части
*/
void mergeSort(int* arr, long l, long r) {
  static long numb_of_threads{1};

  if (l >= r) return;  // выходим из рекурсии
  long m = (l + r - 1) / 2;

  if ((numb_of_threads >= (max_numb_of_treads)) || (!multithread)) {
    auto future_1 = async(launch::deferred, [&]() { mergeSort(arr, l, m); });
    mergeSort(arr, m + 1, r);
    future_1.wait();

  } else {
    numb_of_threads++;  // т. к. потоки добавляются только в одном плече - можно
                        // не переживать о превышении числа потоков
    auto future_1 = async(launch::async, [&]() { mergeSort(arr, l, m); });
    mergeSort(arr, m + 1, r);
    future_1.wait();
  }

  merge(arr, l, m, r);
}

void make_merge() {
  srand(0);
  long arr_size = 10000000;
  int* array = new int[arr_size];
  for (long i = 0; i < arr_size; i++) {
    array[i] = rand() % 500000;
  }

  time_t start, end;

  time(&start);
  mergeSort(array, 0, arr_size - 1);
  time(&end);
  double duration = difftime(end, start);

  std::cout << "Hardware threads = " << max_numb_of_treads << std::endl;
  std::cout << "Multithread = " << multithread << " Time: " << duration
            << std::endl;

  for (long i = 0; i < arr_size - 1; i++) {
    if (array[i] > array[i + 1]) {
      std::cout << "Unsorted" << std::endl;
      break;
    }
  }

  delete[] array;
  return;
};

int main() {
  make_merge();
  multithread = false;
  make_merge();
  return 0;
}