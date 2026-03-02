#include <iostream>
using namespace std;

void swapValues(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void displayValues(int a, int b, const char* label) {
    cout << label << " => a = " << a << ", b = " << b << endl;
}

void displayPointerInfo(int* a, int* b) {
    cout << endl << "INFORMASI POINTER (Alamat Memori)" << endl;
    cout << "========================================" << endl;
    cout << "Variabel a:" << endl;
    cout << "  Nilai:  " << *a << endl;
    cout << "  Alamat: " << a << endl;
    cout << endl << "Variabel b:" << endl;
    cout << "  Nilai:  " << *b << endl;
    cout << "  Alamat: " << b << endl;
    cout << "========================================" << endl;
}

int main() {
    cout << endl << "===== SOAL 4: POINTER PADA FUNGSI =====" << endl;
    cout << "Menukar Dua Variabel Integer Menggunakan Pointer" << endl;

    int a = 25;
    int b = 75;

    cout << endl << "Sebelum pertukaran:" << endl;
    displayValues(a, b, "Nilai");
    displayPointerInfo(&a, &b);

    swapValues(&a, &b);

    cout << endl << "Setelah pertukaran:" << endl;
    displayValues(a, b, "Nilai");
    displayPointerInfo(&a, &b);

    return 0;
}
