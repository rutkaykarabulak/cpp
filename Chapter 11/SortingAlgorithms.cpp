#include <algorithm>
#include <iostream>

void selectionSort(int arr[], int size) {
    for (int i=size-1; i >= 0; i--) {
        int largestIndex = i;
        for (int j=0; j < i; j++) {
            if (arr[j] > arr[largestIndex]) {
                largestIndex = j;
            }
        }
        std::swap(arr[i], arr[largestIndex]);
    }
}

void bubbleSort(int arr[], int size) {
    int pass = 1;

    while (pass < size) {
        for (int i=0; i < size - pass; i++) {
            if (arr[i] > arr[i+1]) {
                std::swap(arr[i], arr[i+1]);
            }
        }
        pass++;
    }
}

void insertionSort(int arr[], int size) {
    int sorted;
    int unsorted;

    for (unsorted = 1; unsorted < size; unsorted++) {
        sorted = unsorted-1;

        while (sorted >=0 && arr[sorted] > arr[unsorted]) {
            std::swap(arr[sorted], arr[unsorted]);
            sorted--;
            unsorted--;
        }
    }
}

void merge(int arr[], int first, int mid, int last) {
    int first1 = first;
    int last1 = mid;
    int first2 = mid+1;
    int last2 = last;

    int currentIndex = first;
    int tempArr[first + last];

    // compare
    while (first1 <= last1 && first2 <= last2) {
        if (arr[first1] < arr[first2]) {
            tempArr[currentIndex] = arr[first1];
            first1++;
        } else {
            tempArr[currentIndex] = arr[first2];
            first2++;
        }
        currentIndex++;
    }

    // finish up the first part of array
    while (first1 <= last1) {
        tempArr[currentIndex] = arr[first1];
        currentIndex++;
        first1++;
    }

    // finish up the second part of array
    while (first2 <= last2) {
        tempArr[currentIndex] = arr[first2];
        currentIndex++;
        first2++;
    }

    for (int i=first; i <= last; i++) {
        arr[i] = tempArr[i];
    }

}

void mergeSort(int arr[], int first, int last) {
    if (first < last) {
        int mid = first + (last - first) / 2;

        mergeSort(arr, first, mid);
        mergeSort(arr, mid+1, last);
        merge(arr, first, mid, last);
    }
}

void sortFirstMidLast(int arr[], int first, int mid, int last) {
    if (arr[first] > arr[mid])
        std::swap(arr[first], arr[mid]);
    if (arr[mid] > arr[last])
        std::swap(arr[mid], arr[last]);
    if (arr[first] > arr[mid])
        std::swap(arr[first], arr[last]);
    
}

int partition(int arr[], int first, int last) {
    int mid = first + (last - first) / 2;
    sortFirstMidLast(arr, first, mid, last);
    // pivot is mid now
    std::swap(arr[mid], arr[last]); 
    int pivotIndex = last;
    int pivot = arr[pivotIndex];

    int indexFromLeft = first;
    int indexFromRight = last-1;

    while (indexFromLeft  < indexFromRight) {
        while (arr[indexFromLeft] < pivot)
            indexFromLeft++;
        while (arr[indexFromRight] > pivot)
            indexFromRight--;
        
        if (indexFromLeft < indexFromRight)
            std::swap(arr[indexFromLeft], arr[indexFromRight]);
    }

    std::swap(arr[indexFromLeft], arr[pivotIndex]);

    pivotIndex = indexFromLeft;
    return pivotIndex;

    return -1;
}

void quickSort(int arr[], int first, int last) {
    if (first < last) {
        int pivotIndex = partition(arr, first, last);
        quickSort(arr,first, pivotIndex-1);
        quickSort(arr,pivotIndex+1, last);
    }
}

int quickSelect(int k, int arr[], int first, int last) {
    int pivotIndex = partition(arr, first, last);

    int numberOfElements = pivotIndex - first + 1;

    if (k < numberOfElements) {
        return quickSelect(k, arr, first, pivotIndex - 1);
    } else if (k == numberOfElements) {
        return arr[pivotIndex];
    } else {
        return quickSelect(k-numberOfElements, arr, pivotIndex+1, last);
    }
}


int main() {
    int arr[] = {-1,-5,12,0,7,5,15};
    quickSort(arr, 0, 6);

    for (int i=0; i < 7; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout<<std::endl;
    std::cout << "4th smallest element of array: " << quickSelect(5, arr, 0, 6);
    // 1 2 3 4 5 6 7 8
 }