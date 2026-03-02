#include <iostream>
using namespace std;

int main() {

    // Deklarasi dan inisialisasi array
    int primes[7] = {2, 3, 5, 7, 11, 13, 17};

    // Pointer menunjuk ke elemen pertama array
    int *p = primes;

    cout << "===== ARRAY AWAL =====" << endl;

    // Menampilkan isi array menggunakan pointer
    for (int i = 0; i < 7; i++) {
        cout << "Nilai: " << *p
             << " | Alamat: " << p << endl;
        p++;
    }

    // Reset pointer ke awal array
    p = primes;

    // Membalik isi array menggunakan pointer
    int *awal = primes;
    int *akhir = primes + 6;   // elemen terakhir

    while (awal < akhir) {
        int temp = *awal;
        *awal = *akhir;
        *akhir = temp;

        awal++;
        akhir--;
    }

    cout << endl << "===== ARRAY SETELAH DIBALIK =====" << endl;

    // Tampilkan kembali isi array
    p = primes;
    for (int i = 0; i < 7; i++) {
        cout << "Nilai: " << *p
             << " | Alamat: " << p << endl;
        p++;
    }

    return 0;
}