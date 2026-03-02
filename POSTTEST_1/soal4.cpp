#include <iostream>
using namespace std;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {

    int x = 10;
    int y = 20;

    cout << "Sebelum ditukar:" << endl;
    cout << "Nilai x: " << x << endl;
    cout << "Nilai y: " << y << endl;
    cout << "Alamat x: " << &x << endl;
    cout << "Alamat y: " << &y << endl;

    swap(&x, &y);

    cout << endl << "Setelah ditukar:" << endl;
    cout << "Nilai x: " << x << endl;
    cout << "Nilai y: " << y << endl;
    cout << "Alamat x: " << &x << endl;
    cout << "Alamat y: " << &y << endl;

    return 0;
}