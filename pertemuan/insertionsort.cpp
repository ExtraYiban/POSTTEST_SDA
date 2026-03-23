#include <iostream>
#include <string>
using namespace std;
// Definisi Struktur Data Buku
struct Buku {
    int idBuku;
    string judul;
};
// Fungsi Insertion Sort dengan akses Pointer
void insertionSort(Buku* rak, int n) {
    // Dimulai dari buku kedua (index 1)
    for (int i = 1; i < n; i++) {
        // 'key' adalah buku yang sedang diambil dari rak untuk disisipkan
        Buku key = *(rak + i);
        int j = i - 1;
        /* Loop While: Mencari posisi yang tepat untuk 'key'.
        Di sini terjadi perbandingan (Comparison) dan pergeseran

        (Shifting).
        */
        while (j >= 0 && (rak + j)->idBuku > key.idBuku) {
            // Geser buku yang lebih besar ke kanan
            *(rak + j + 1) = *(rak + j);
            j = j - 1;
        }
        // Letakkan buku 'key' di posisi yang sudah kosong
        *(rak + j + 1) = key;
    }
}
// Fungsi untuk menampilkan daftar buku di rak
void tampilkanRak(Buku* rak, int n) {
    cout << "ID\t| Judul Buku" << endl;
    cout << "--------------------------" << endl;
    for (int i = 0; i < n; i++) {
        cout << (rak + i)->idBuku << "\t| " << (rak + i)->judul << endl;
    }
    cout << endl;
}
int main() {
    int n = 5;
    // --- SKENARIO 1: BEST CASE ---
    // Buku sudah terurut dari ID terkecil ke terbesar.
    Buku rakUrut[] = {
        {101, "Laskar Pelangi"},
        {102, "Bumi Manusia"},
        {103, "Negeri 5 Menara"},
        {104, "Filosofi Teras"},
        {105, "Hujan"}
    };
    cout << ">>> SKENARIO: BEST CASE (Sudah Terurut) <<<" << endl;
    cout << "Data Sebelum: (Sudah rapi)" << endl;
    insertionSort(rakUrut, n);
    tampilkanRak(rakUrut, n);
    cout << "Analisis: Loop 'while' tidak pernah berjalan. Hanya perlu n
    iterasi." << endl;
    cout << "Kompleksitas Waktu: O(n)" << endl;
    cout << "------------------------------------------" << endl << endl;

    // --- SKENARIO 2: WORST CASE ---
    // Buku terurut terbalik (ID terbesar di depan).
    Buku rakTerbalik[] = {
        {105, "Hujan"},
        {104, "Filosofi Teras"},
        {103, "Negeri 5 Menara"},
        {102, "Bumi Manusia"},
        {101, "Laskar Pelangi"}
    };
    cout << ">>> SKENARIO: WORST CASE (Terurut Terbalik) <<<" << endl;
    cout << "Data Sebelum:" << endl;
    tampilkanRak(rakTerbalik, n);

    insertionSort(rakTerbalik, n);
    cout << "Data Sesudah (Berhasil Diurutkan):" << endl;
    tampilkanRak(rakTerbalik, n);
    cout << "Analisis: Setiap buku harus dibandingkan dan digeser ke posisi
    paling awal." << endl;
    cout << "Kompleksitas Waktu: O(n^2)" << endl;
    return 0;
}