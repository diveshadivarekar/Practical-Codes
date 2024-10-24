#include <iostream>
using namespace std;

template <typename T>
void selectionSort(T arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        T temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}


template <typename T>
void inputArray(T arr[], int size) {
    cout << "Enter " << size << " elements:" << endl;
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }
}

template <typename T>
void outputArray(const T arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    // integer array
    int intArr[5];
    cout << "Input for integer array:" << endl;
    inputArray(intArr, 5);
    selectionSort(intArr, 5);
    cout << "Sorted integer array: ";
    outputArray(intArr, 5);

    // float array
    float floatArr[5];
    cout << "Input for float array:" << endl;
    inputArray(floatArr, 5);
    selectionSort(floatArr, 5);
    cout << "Sorted float array: ";
    outputArray(floatArr, 5);

    return 0;
}
