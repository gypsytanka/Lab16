#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <math.h>


double calc(double x);
double* full_elements(double* ptr_array, int n);
double* full_random(double* ptr_array, int n);
double* calc_elements(double* ptr_array, int n);
int put_elements(double* ptr_array, int n);
int delete_k(double* ptr_arr, int size, int k);
int find_max_index(double* ptr_arr, int size);
int insert_before(double* ptr_arr, int size, int index, double value);
void delete_two_max(double* ptr_arr, int* size);
void insert_before_max(double* ptr_arr, int* size);

int main() {
    setlocale(LC_CTYPE, "RUS");
    srand(time(NULL));

    double* ptr_array;
    int size;

    // ЗАДАНИЕ 1
    printf("=== ЗАДАНИЕ 1 ===\n");

    printf("Введите размер массива: ");
    scanf("%d", &size);

    ptr_array = (double*)malloc(size * sizeof(double));
    if (ptr_array == NULL) {
        puts("error");
        return -1;
    }

    full_elements(ptr_array, size);
    put_elements(ptr_array, size);

    calc_elements(ptr_array, size);
    
    free(ptr_array);

    // ЗАДАНИЕ 2
    printf("\n=== ЗАДАНИЕ 2 ===\n");

    printf("Введите размер массива: ");
    scanf("%d", &size);

    ptr_array = (double*)malloc(size * sizeof(double));
    if (ptr_array == NULL) {
        puts("error");
        return -1;
    }

    full_random(ptr_array, size);

    put_elements(ptr_array, size);

    printf("2.1 Удаление двух максимальных элементов:\n");
    int current_size = size;
    delete_two_max(ptr_array, &current_size);
    put_elements(ptr_array, current_size);

    printf("2.2 Вставка -999 перед максимальным элементом:\n");
    insert_before_max(ptr_array, &current_size);
    put_elements(ptr_array, current_size);

    free(ptr_array);

    return 0;
}

double calc(double x) {
    return fabs(log10(x)) - pow(x - 2, 2);
}

double* full_elements(double* ptr_array, int n) {
    float start = 2.0f;
    float end_val = 4.1f;
    float step = (end_val - start) / (n - 1);
    for (int i = 0; i < n; i++) {
        float x = start + i * step;
        ptr_array[i] = calc(x);
    }
    return ptr_array;
}

double* full_random(double* ptr_array, int n) {
    for (int i = 0; i < n; i++) {
        ptr_array[i] = (double)rand() / RAND_MAX * 2.0 - 1.0;
    }
    return ptr_array;
}

double* calc_elements(double* ptr_array, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += ptr_array[i];
    }
    double sr = sum / n;

    printf("Среднее арифметическое: %.4f\n", sr);

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (ptr_array[i] < sr) {
            count++;
        }
    }

    printf("Количество элементов меньше среднего: %d\n\n", count);
    return ptr_array;
}

int put_elements(double* ptr_array, int n) {
    for (int i = 0; i < n; i++) {
        printf("[%d] = %.4f\n", i, ptr_array[i]);
    }
    printf("\n");
    return n;
}

int delete_k(double* ptr_arr, int size, int k) {
    for (int i = k; i < (size - 1); i++) {
        ptr_arr[i] = ptr_arr[i + 1];
    }
    return size - 1;
}

int find_max_index(double* ptr_arr, int size) {
    int max_index = 0;
    for (int i = 1; i < size; i++) {
        if (ptr_arr[i] > ptr_arr[max_index]) {
            max_index = i;
        }
    }
    return max_index;
}

int insert_before(double* ptr_arr, int size, int index, double value) {
    for (int i = size; i > index; i--) {
        ptr_arr[i] = ptr_arr[i - 1];
    }
    ptr_arr[index] = value;
    return size + 1;
}

void delete_two_max(double* ptr_arr, int* size) {
    int max1_index = find_max_index(ptr_arr, *size);
    *size = delete_k(ptr_arr, *size, max1_index);

    int max2_index = find_max_index(ptr_arr, *size);
    *size = delete_k(ptr_arr, *size, max2_index);
}

void insert_before_max(double* ptr_arr, int* size) {
    int max_index = find_max_index(ptr_arr, *size);
    *size = insert_before(ptr_arr, *size, max_index, -999.0);
}