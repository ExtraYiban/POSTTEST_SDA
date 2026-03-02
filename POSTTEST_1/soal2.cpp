#include <iostream>

using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

void print(string text) {
    cout << text;
};

void println(string text) {
    cout << text << endl;
};


int main() {
    Mahasiswa jumlah_mahasiswa[5];
    float ipk_terbesar = 0;
    string nama_terbesar, nim_terbesar;

    for (int i = 0; i < 5; i++) {
        cout << "Masukkan Data Mahasiswa ke-" << i + 1 << "/" << 5 << endl;
        cout << "Nama : ";
        cin >> jumlah_mahasiswa[i].nama;
        cout << "NIM : ";
        cin >> jumlah_mahasiswa[i].nim;
        cout << "IPK : ";
        cin >> jumlah_mahasiswa[i].ipk;

        if (jumlah_mahasiswa[i].ipk > ipk_terbesar) {
            nama_terbesar = jumlah_mahasiswa[i].nama;
            nim_terbesar = jumlah_mahasiswa[i].nim;
            ipk_terbesar = jumlah_mahasiswa[i].ipk;
        }
    }


    println("Mahasiswa Dengan IPK terbesar:");
    println("Nama : " + nama_terbesar);
    println("NIM : " + nim_terbesar);
    print("IPK : ");
    cout << ipk_terbesar << endl;
    return 0;
}
