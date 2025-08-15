#ifndef SORTING_H
#define SORTING_H

void bubble_sort(int* arr, int n, void (*swap_callback)(int, int));
void selection_sort(int* arr, int n, void (*swap_callback)(int, int));
void insertion_sort(int* arr, int n, void (*swap_callback)(int, int));
void quick_sort(int* arr, int n, void (*swap_callback)(int, int));
void merge_sort(int* arr, int n, void (*swap_callback)(int, int));
void heap_sort(int *arr, int n, void (*swap_callback)(int, int));
void shell_sort(int *arr, int n, void (*swap_callback)(int, int));
void radix_sort(int *arr, int n, void (*swap_callback)(int, int));
void bucket_sort(int *arr, int n, void (*swap_callback)(int, int));
void counting_sort(int* arr, int n, void (*swap_callback)(int, int));


#endif
