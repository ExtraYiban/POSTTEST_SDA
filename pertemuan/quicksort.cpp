#include <iostream>
#include <string>
using namespace std;

// Definisi Struct Mahasiswa untuk menyimpan data seorang mahasiswa
// Menggunakan string untuk nim (nomor identitas) dan nama
// Alasan: struct memungkinkan kita menyimpan beberapa data terkait dalam satu unit,
// sehingga ketika kita sort, seluruh data mahasiswa tetap bersamaan (tidak terpisah)
struct Mahasiswa {
    string nim;      // Nomor identitas mahasiswa (akan digunakan sebagai kriteria sorting)
    string nama;     // Nama mahasiswa
};

// Fungsi swap: menukar isi dua variabel Mahasiswa
// Parameter: *a (pointer ke Mahasiswa pertama), *b (pointer ke Mahasiswa kedua)
// ALASAN MENGGUNAKAN POINTER:
//   - Tanpa pointer, swap menerima COPY dari data, bukan data asli
//   - Perubahan pada copy tidak akan mempengaruhi data asli di array
//   - Dengan pointer, kita mengubah data yang sebenarnya di memory
//
// ANALOGI: pointer seperti alamat rumah, tanpa pointer kita hanya mengirim fotokopi
//          data, bukan mengirim data asli yang bisa diubah
//
// KESALAHAN UMUM:
//   - Lupa dereferensi (*) ketika mengakses nilai: ini->nim (SALAH)
//   - Menggunakan reference (&) alih-alih pointer: swap(a&, b&) (BERBEDA)
void swap(Mahasiswa* a, Mahasiswa* b) {
    // Buat variabel sementara temp untuk menyimpan salinan elemen di alamat a
    // Contoh: jika *a = {nim: "220910", nama: "Budi"}
    //         maka temp = {nim: "220910", nama: "Budi"}
    Mahasiswa temp = *a;

    // Salin nilai dari b ke a (dereferensi * diperlukan untuk akses nilai)
    // Contoh: *a sekarang berisi data yang sebelumnya di b
    //         Jika *b = {nim: "220901", nama: "Ani"}
    //         maka *a = {nim: "220901", nama: "Ani"}
    *a = *b;

    // Salin nilai dari temp (data asli a) ke b
    // Sehingga b sekarang berisi data yang sebelumnya di a
    // Hasil akhir: kedua elemen sudah tertukar
    *b = temp;
}

// Fungsi Partition: Inti dari Quick Sort
// TUJUAN: Menempatkan pivot pada posisi yang benar dan membagi array menjadi 2 bagian
//   - Bagian kiri: semua NIM < pivot
//   - Bagian kanan: semua NIM >= pivot
//
// ALASAN menggunakan partition:
//   - Setelah partition, pivot tidak perlu diurutkan lagi (sudah di posisi final)
//   - Kita hanya perlu sort bagian kiri dan kanan secara rekursif
//   - Ini membuat quick sort lebih efisien daripada membandingkan semua elemen
int partition(Mahasiswa* arr, int low, int high) {
    // PIVOT SELECTION: Memilih elemen terakhir sebagai pivot
    // Contoh: arr = [220910, 220901, 220915, 220905, 220912]
    //         pivot = "220912" (elemen terakhir)
    // ALASAN memilih elemen terakhir:
    //   - Mudah diimplementasikan
    //   - Pada data acak, performa hampir sama dengan pivot random
    // KESALAHAN UMUM: tidak menyimpan nilai pivot dulu, malah akses (arr+high)->nim berulang kali
    string pivot = (arr + high)->nim;

    // i adalah index yang memisahkan elemen < pivot dan elemen >= pivot
    // Dimulai dari (low - 1) karena akan di-increment sebelum digunakan
    // Contoh: jika low = 0, maka i = -1 (berarti belum ada elemen < pivot)
    int i = (low - 1);

    // Loop dari low sampai high-1 (pivot tidak ikut loop karena sudah dipilih)
    // Contoh: j mulai dari 0 sampai 3 (tidak sampai 4, karena 4 adalah index pivot)
    // ALASAN high-1: pivot sudah berada di posisi high, tidak perlu dibandingkan dengan diri sendiri
    for (int j = low; j <= high - 1; j++) {
        // Jika NIM saat ini lebih kecil dari pivot, pindahkan ke sebelah kiri
        // Contoh: jika arr[0].nim = "220910" dan pivot = "220912"
        //         maka "220910" < "220912" adalah TRUE, elemen dipindahkan
        if ((arr + j)->nim < pivot) {
            // Increment i terlebih dahulu untuk memberi tempat elemen baru
            // Contoh iterasi:
            //   j=0: 220910 < 220912? YES -> i=0, swap(arr[0], arr[0]) -> i=0
            //   j=1: 220901 < 220912? YES -> i=1, swap(arr[1], arr[1]) -> arr = [..., 220901, ...]
            //   j=2: 220915 < 220912? NO  -> tidak ada perubahan
            //   j=3: 220905 < 220912? YES -> i=2, swap(arr[2], arr[3])
            i++;
            // Tukar elemen di posisi i dengan elemen di posisi j
            // HUBUNGAN: area [low..i] adalah elemen < pivot, area [i+1..j-1] adalah >= pivot
            swap((arr + i), (arr + j));
        }
    }

    // Tempatkan pivot di posisi yang benar (antara elemen < dan >= pivot)
    // Contoh: setelah loop, i menunjuk ke elemen terakhir yang < pivot
    //         maka pivot harus ditempatkan di posisi i+1
    // ALASAN: semua elemen [low..i] < pivot, semua elemen [i+1..high-1] >= pivot
    //         jadi pivot milik di posisi i+1
    swap((arr + i + 1), (arr + high));

    // Return posisi final dari pivot
    // Posisi ini tidak akan berubah pada iterasi rekursif selanjutnya
    // Contoh: jika i=2, maka pivot berada di posisi 3 dan tidak perlu diurutkan lagi
    return (i + 1);
}

// Fungsi Utama Quick Sort
// KONSEP DIVIDE & CONQUER:
//   1. DIVIDE: gunakan partition untuk membagi array di sekitar pivot
//   2. CONQUER: rekursi sort bagian kiri dan kanan
//   3. COMBINE: sudah otomatis, karena setelah partition, pivot sudah di posisi final
//
// MENGAPA LEBIH CEPAT DARI MERGE SORT:
//   - Merge Sort: selalu O(n log n) karena selalu membagi 2
//   - Quick Sort: rata-rata O(n log n), tapi pivot yang bagus membuat pembagian lebih seimbang
//   - Quick Sort tidak perlu array sementara (in-place sorting)
//
// KESALAHAN UMUM:
//   - Lupa kondisi low < high, akan infinite recursion
//   - Mengubah pi (posisi pivot) setelah partition, padahal sudah final
void quickSort(Mahasiswa* arr, int low, int high) {
    // Kondisi base case: jika low >= high, bagian ini sudah terurut (hanya 1 atau 0 elemen)
    // Contoh: quickSort(arr, 3, 3) -> return (base case)
    //         quickSort(arr, 5, 2) -> return (invalid range)
    if (low < high) {
        // pi adalah index partisi setelah menempatkan pivot di posisi yang benar
        // Contoh: partition(arr, 0, 4) mengembalikan 2
        //         berarti pivot berada di index 2 dan sudah di posisi final
        int pi = partition(arr, low, high);

        // HUBUNGAN BAGIAN-BAGIAN:
        // - arr[low..pi-1]: elemen < pivot (belum terurut, perlu sorted)
        // - arr[pi]: pivot (SUDAH TERURUT, jangan disentuh)
        // - arr[pi+1..high]: elemen >= pivot (belum terurut, perlu sorted)
        //
        // ALASAN membagi 2: dengan membagi, kita mengubah problem besar menjadi problem kecil
        // Contoh: Sort 5 elemen menjadi sort 2 elemen + sort 2 elemen

        // Rekursi: sort elemen sebelum partisi
        // Contoh: quickSort(arr, 0, 1) akan mengurutkan arr[0] dan arr[1]
        quickSort(arr, low, pi - 1);

        // Rekursi: sort elemen sesudah partisi
        // Contoh: quickSort(arr, 3, 4) akan mengurutkan arr[3] dan arr[4]
        quickSort(arr, pi + 1, high);
    }
}

// Fungsi tampilkanData: menampilkan semua elemen array dalam format tabel
// ALASAN menggunakan pointer arithmetic (arr + i):
//   - (arr + i) = akses elemen ke-i tanpa menggunakan indeks bracket []
//   - Pointer arithmetic otomatis memperhitungkan ukuran struct
//   - Contoh: (arr + 0) = alamat elemen pertama
//            (arr + 1) = alamat elemen pertama + ukuran 1 struct
//
// HUBUNGAN dengan main:
//   - main() melewatkan pointer array dan jumlah elemen
//   - function ini bertanggung jawab menampilkan semua n elemen
void tampilkanData(Mahasiswa* arr, int n) {
    // Tampilkan header tabel dengan pemisah tab
    cout << "NIM\t\tNama" << endl;
    cout << "----------------------------" << endl;

    // Loop untuk menampilkan setiap mahasiswa dalam array
    // Contoh: n=5, maka loop dari i=0 sampai i=4
    for (int i = 0; i < n; i++) {
        // Gunakan pointer arithmetic (arr + i) untuk mengakses elemen ke-i
        // Contoh: (arr + 0)->nim = NIM mahasiswa pertama
        //         (arr + 1)->nim = NIM mahasiswa kedua, dst
        //
        // ALASAN menggunakan -> (arrow):
        //   - (arr + i) adalah pointer ke struct
        //   - -> digunakan untuk akses member melalui pointer
        //   - Ini setara dengan: (*((arr + i))).nim
        cout << (arr + i)->nim << "\t" << (arr + i)->nama << endl;
    }
    cout << endl;
}


// Fungsi main: titik awal program
// ALUR PROGRAM:
//   1. Inisialisasi data mahasiswa dalam array
//   2. Tampilkan data sebelum diurutkan (posisi acak)
//   3. Panggil quickSort untuk mengurutkan berdasarkan NIM
//   4. Tampilkan data setelah diurutkan (urut ascending)
int main() {
    // Deklarasi variabel n untuk menyimpan jumlah mahasiswa
    int n = 5;

    // Inisialisasi Array of Struct dengan 5 data mahasiswa
    // DATA AWAL (POSISI ACAK):
    //   Index 0: {nim: "220910", nama: "Budi"}
    //   Index 1: {nim: "220901", nama: "Ani"}
    //   Index 2: {nim: "220915", nama: "Citra"}
    //   Index 3: {nim: "220905", nama: "Dodi"}
    //   Index 4: {nim: "220912", nama: "Eka"}
    //
    // ALASAN memilih data ini:
    //   - NIM tidak terurut (220910, 220901, 220915, 220905, 220912)
    //   - Menunjukkan bahwa quick sort bisa mengurutkan data acak
    Mahasiswa kelas[] = {
        {"220910", "Budi"},
        {"220901", "Ani"},
        {"220915", "Citra"},
        {"220905", "Dodi"},
        {"220912", "Eka"}
    };

    // Tampilkan data sebelum diurutkan
    cout << "=== DATA MAHASISWA (SEBELUM SORT) ===" << endl;
    // Panggil tampilkanData dengan parameter:
    //   - kelas (pointer ke elemen pertama array)
    //   - n (jumlah elemen)
    // ALASAN: fungsi tampilkanData memerlukan pointer dan ukuran array
    tampilkanData(kelas, n);

    // Panggil quickSort untuk mengurutkan data berdasarkan NIM (ascending)
    // Parameter: pointer array, indeks awal (0), indeks akhir (n-1)
    // PROSES SORTING:
    //   1. Partition pilih pivot = "220912" (elemen terakhir)
    //   2. Elemen < "220912" dipindah ke kiri, >= ke kanan
    //   3. Rekursi sort bagian kiri dan kanan
    //   4. Hasil akhir: array terurut dari "220901" sampai "220915"
    quickSort(kelas, 0, n - 1);

    // Tampilkan data setelah diurutkan
    cout << "=== DATA MAHASISWA (SESUDAH QUICK SORT) ===" << endl;
    // DATA SETELAH SORT (ASCENDING):
    //   Index 0: {nim: "220901", nama: "Ani"}
    //   Index 1: {nim: "220905", nama: "Dodi"}
    //   Index 2: {nim: "220910", nama: "Budi"}
    //   Index 3: {nim: "220912", nama: "Eka"}
    //   Index 4: {nim: "220915", nama: "Citra"}
    tampilkanData(kelas, n);

    // Return 0 menunjukkan program berjalan tanpa error
    return 0;
}