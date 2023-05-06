#include <stdio.h>

// Implementação do algoritmo ShellSort
void shellSort(int arr[], int n) {
    int i, j, gap, temp;
    for (gap = n/2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            temp = arr[i];
            for (j = i; j >= gap && arr[j-gap] > temp; j -= gap)
                arr[j] = arr[j-gap];
            arr[j] = temp;
        }
    }
}

int main() {
    int arr[] = {4, 67, 5, 34, 21, 32, 60, 1, 13, 53, 11, 90, 3, 17};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("Lista original:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    shellSort(arr, n);

    printf("\nLista ordenada:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}
