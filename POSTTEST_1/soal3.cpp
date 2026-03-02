#include <iostream>
using namespace std;

// Fungsi untuk membalik array menggunakan pointer
void reverseArray(int* arr, int n) {
    int *awal = arr;
    int *akhir = arr + n - 1;

    while (awal < akhir) {
        int temp = *awal;
        *awal = *akhir;
        *akhir = temp;

        awal++;
        akhir--;
    }
}

// Fungsi untuk menampilkan array dan alamat memori
void tampilkanArray(int* arr, int n) {
    int *p = arr;

    for (int i = 0; i < n; i++) {
        cout << "Nilai: " << *p
             << " | Alamat: " << p << endl;
        p++;
    }
}

int main() {

    int primes[7] = {2, 3, 5, 7, 11, 13, 17};

    cout << "Array sebelum dibalik:" << endl;
    tampilkanArray(primes, 7);

    reverseArray(primes, 7);

    cout << endl << "Array setelah dibalik:" << endl;
    tampilkanArray(primes, 7);

    return 0;
}