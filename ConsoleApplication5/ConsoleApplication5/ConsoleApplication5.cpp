// ConsoleApplication5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <omp.h>
using namespace std;

//сортировкка пузырьком

int* bubble_sort(int a[1000], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1])
            {
                int k = a[j];
                a[j] = a[j + 1];
                a[j + 1] = k;
            }
    return a;
}

//сортировка Шелла
void shell_sort(int* array, int size) {
    for (int s = size / 2; s > 0; s /= 2) {
        for (int i = s; i < size; ++i) {
            for (int j = i - s; j >= 0 && array[j] > array[j + s]; j -= s) {
                int temp = array[j];
                array[j] = array[j + s];
                array[j + s] = temp;
            }
        }
    }
}

//сортировка чет-нечет
void oddEvenSort(int* arr, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = (i % 2) ? 0 : 1; j < n - 1; j += 2)  // (i % 2) ? 0 : 1 возвращает 0, если i четное, 1, если i не четное
        {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void oddEvenSortParallel(int* arr, int n)
{
    for (int i = 0; i < n; i++) {
#pragma omp parallel for
        for (int j = (i % 2) ? 0 : 1; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void shell_sortParall(int* array, int size) {
    for (int s = size / 2; s > 0; s /= 2)
    {
#pragma omp parallel for
        for (int i = s; i < size; ++i)
        {
            for (int j = i - s; j >= 0 && array[j] > array[j + s]; j -= s)
            {
                int temp = array[j];
                array[j] = array[j + s];
                array[j + s] = temp;
            }
        }
    }
}
int* newArray(int n)
{
    int* a = new int[n];
    for (int i = 0; i < n; i++)
        a[i] = rand();
    return a;
}
void printArr(int* a, int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << endl;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    double start, end;
    cout << "Размерность массива: " << endl;
    int n;
    cin >> n;
    int* a = newArray(n);
    int* b = new int[n], * c = new int[n], * c2 = new int[n];
    int* b2 = new int[n];
    for (int i = 0; i < n; i++)
    {
        b[i] = a[i];
        c[i] = a[i];
        c2[i] = a[i];
        b2[i] = a[i];
    }
    //вывод изначального массива
    //cout << "newArr = " << endl;
    //printArr(a,n);
    start = omp_get_wtime();
    bubble_sort(a, n);
    end = omp_get_wtime();
    cout << "Time bubble: " << end - start << endl;
    //сортировка пузырьком
    //cout << "afterSort Array = " << endl;
    //printArr(a,n);
    start = omp_get_wtime();
    oddEvenSort(b, n);
    end = omp_get_wtime();
    cout << "Time чёт-нечёт: " << end - start << endl;
    //сортировка чет-нечет
    //cout << "afterSort Array = " << endl;
    //printArr(b,n);

    start = omp_get_wtime();
    oddEvenSortParallel(b2, n);
    end = omp_get_wtime();
    cout << "Time чёт-нечёт parallel: " << end - start << endl;
    //сортировка чет-нечет параллел
    //cout << "afterSort Array = " << endl;
    //printArr(b2,n);


    start = omp_get_wtime();
    shell_sort(c, n);
    end = omp_get_wtime();
    cout << "Time Шелла: " << end - start << endl;
    //сортировка  Шелла 
 //cout << "afterSort Array = " << endl;
 //printArr(c,n);

    start = omp_get_wtime();
    shell_sortParall(c2, n);
    end = omp_get_wtime();
    cout << "Time Шелла parallel: " << end - start << endl;
    //сортировка  Шелла параллел
//cout << "afterSort Array = " << endl;
//printArr(c2,n);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
