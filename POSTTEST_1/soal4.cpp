#include <iostream>
using namespace std;

int main() {

    int a = 25;
    int b = 75;

    int *pA;
    int *pB;

    // Pointer menyimpan alamat variabel
    pA = &a;
    pB = &b;

    cout << "Sebelum ditukar:" << endl;
    cout << "Nilai a: " << a << endl;
    cout << "Nilai b: " << b << endl;
    cout << "Alamat a: " << &a << endl;
    cout << "Alamat b: " << &b << endl;

    // Menukar nilai menggunakan pointer
    int temp = *pA;
    *pA = *pB;
    *pB = temp;

    cout << endl << "Setelah ditukar:" << endl;
    cout << "Nilai a: " << a << endl;
    cout << "Nilai b: " << b << endl;
    cout << "Alamat a: " << &a << endl;
    cout << "Alamat b: " << &b << endl;

    return 0;
}