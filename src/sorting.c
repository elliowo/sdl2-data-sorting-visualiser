#include <stdlib.h>
#include "sorting.h"

static inline void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Bubble sort
void bubble_sort(int *arr, int n, void (*swap_callback)(int, int)) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap_callback(j, j + 1);
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Insertion sort
void insertion_sort(int *arr, int n, void (*swap_callback)(int, int)) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            swap_callback(j, j + 1);
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Selection sort
void selection_sort(int *arr, int n, void (*swap_callback)(int, int)) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) min_idx = j;
        }
        if (min_idx != i) {
            swap_callback(i, min_idx);
            swap(&arr[i], &arr[min_idx]);
        }
    }
}

// Quick sort helpers
static void quick_sort_helper(int *arr, int low, int high, void (*swap_callback)(int, int)) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                swap_callback(i, j);
                swap(&arr[i], &arr[j]);
            }
        }
        swap_callback(i + 1, high);
        swap(&arr[i + 1], &arr[high]);

        quick_sort_helper(arr, low, i, swap_callback);
        quick_sort_helper(arr, i + 2, high, swap_callback);
    }
}

void quick_sort(int *arr, int n, void (*swap_callback)(int, int)) {
    quick_sort_helper(arr, 0, n - 1, swap_callback);
}

// Merge sort helpers
static void merge(int *arr, int left, int mid, int right, void (*swap_callback)(int, int)) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
          arr[k++] = L[i++];
	  swap_callback(k, left + i); 
        } else {
          arr[k++] = R[j++];
	  swap_callback(k, mid + 1 + j); 
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

static void merge_sort_helper(int *arr, int left, int right, void (*swap_callback)(int, int)) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_helper(arr, left, mid, swap_callback);
        merge_sort_helper(arr, mid + 1, right, swap_callback);
        merge(arr, left, mid, right, swap_callback);
	//	swap_callback(left, right);
    }
}

void merge_sort(int *arr, int n, void (*swap_callback)(int, int)) {
    merge_sort_helper(arr, 0, n - 1, swap_callback);
}

// Heap sort helpers
static void heapify(int *arr, int n, int i, void (*swap_callback)(int, int)) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        swap_callback(i, largest);
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest, swap_callback);
    }
}

void heap_sort(int *arr, int n, void (*swap_callback)(int, int)) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i, swap_callback);
    for (int i = n - 1; i > 0; i--) {
        swap_callback(0, i);
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0, swap_callback);
    }
}

// Shell sort
void shell_sort(int *arr, int n, void (*swap_callback)(int, int)) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                swap_callback(j - gap, j);
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

// Radix sort
void radix_sort(int *arr, int n, void (*swap_callback)(int, int)) {
    int max = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];

    for (int exp = 1; max / exp > 0; exp *= 10) {
        int output[n];
        int count[10] = {0};

        for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;

        for (int i = 1; i < 10; i++) count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            output[--count[(arr[i] / exp) % 10]] = arr[i];
        }

        for (int i = 0; i < n; i++) arr[i] = output[i];
    }
}

// Bucket sort
void bucket_sort(int *arr, int n, void (*swap_callback)(int, int)) {
    int max = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];

    int bucket_count = 10;
    int *buckets[bucket_count];
    int bucket_sizes[bucket_count];
    

    for (int i = 0; i < bucket_count; i++) buckets[i] = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int idx = (arr[i] * bucket_count) / (max + 1);
        buckets[idx][bucket_sizes[idx]++] = arr[i];
    }

    int idx = 0;
    for (int i = 0; i < bucket_count; i++) {
        for (int j = 0; j < bucket_sizes[i]; j++) {
            arr[idx++] = buckets[i][j];
        }
        free(buckets[i]);
    }
}

// Counting sort
void counting_sort(int *arr, int n, void (*swap_callback)(int, int)) {
    int max = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];

    int *count = (int*)calloc(max + 1, sizeof(int));
    for (int i = 0; i < n; i++) count[arr[i]]++;

    int idx = 0;
    for (int i = 0; i <= max; i++) {
        while (count[i]--) arr[idx++] = i;
    }
    free(count);
}
