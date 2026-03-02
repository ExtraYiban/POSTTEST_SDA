#include <iostream>
using namespace std;

void reverseArray(int* arr, int n) {
    int* start = arr;
    int* end = arr + n - 1;

    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }
}

void displayArray(int* arr, int n, const char* label) {
    cout << endl << label << endl;
    cout << "========================================" << endl;
    cout << "Index | Elemen | Alamat Memori" << endl;
    cout << "========================================" << endl;

    for (int i = 0; i < n; i++) {
        int* ptr = arr + i;
        cout << i << "     | " << *ptr << "      | " << ptr << endl;
    }
    cout << "========================================" << endl;
}

void printArray(int* arr, int n) {
    cout << "Array: ";
    for (int i = 0; i < n; i++) {
        cout << *(arr + i) << " ";
    }
    cout << endl;
}

int main() {
    int primes[] = {2, 3, 5, 7, 11, 13, 17};
    int n = 7;

    cout << endl << "===== SOAL 3: ARRAY & POINTER =====" << endl;

    int* arrPtr = primes;

    cout << endl << "[1] ARRAY AWAL (Bilangan Prima)" << endl;
    printArray(arrPtr, n);
    displayArray(arrPtr, n, "[DETAIL ARRAY AWAL]");

    cout << endl << "[2] MEMBALIK ARRAY..." << endl;
    reverseArray(arrPtr, n);

    cout << endl << "[3] ARRAY SETELAH DIBALIK" << endl;
    printArray(arrPtr, n);
    displayArray(arrPtr, n, "[DETAIL ARRAY SETELAH DIBALIK]");

    return 0;
}
