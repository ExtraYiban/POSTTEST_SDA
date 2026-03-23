#include <iostream>
#include <string>
using namespace std;

// Struct untuk menyimpan data produk dengan id, nama, dan harga
struct Produk {
    int id;
    string nama;
    int harga;
};

// ========================================================================
// FUNGSI MERGE: Menggabungkan dua bagian array yang sudah terurut
// ========================================================================
// TUJUAN: Proses penting dalam merge sort - menggabung 2 sub-array terurut
//         menjadi 1 array terurut
//
// MENGAPA perlu fungsi merge?
//   - Setelah mergeSort membagi array menjadi bagian kecil, perlu
//     menggabungkannya kembali dengan menjaga urutan
//   - Ini adalah bagian "COMBINE" dari strategi Divide & Conquer
//   - Merge berbeda dari concatenate: merge MENJAGA URUTAN
//
// ANALOGI: Bayangkan 2 tumpukan kartu terurut (kecil ke besar)
//          Merge = mengambil kartu terkecil dari salah satu tumpukan
//          sampai semua habis
//
// PARAMETER:
//   arr   = pointer ke array produk yang sedang diproses
//   left  = index awal bagian kiri yang akan digabung
//   mid   = index akhir bagian kiri (bagian kanan mulai dari mid+1)
//   right = index akhir bagian kanan
void merge(Produk* arr, int left, int mid, int right) {
    // LANGKAH 1: Hitung jumlah elemen di bagian kiri dan kanan
    // ========================================================
    // ALASAN: Perlu tahu size array sementara sebelum alokasi memory
    //
    // Hitung elemen BAGIAN KIRI: dari index left sampai index mid (INKLUSIF)
    // Contoh: left=0, mid=1 -> n1 = 1-0+1 = 2 elemen (index 0 dan 1)
    // PENTING: +1 karena menghitung JUMLAH elemen, bukan selisih index
    int n1 = mid - left + 1;

    // Hitung elemen BAGIAN KANAN: dari index (mid+1) sampai index right
    // Contoh: mid=1, right=3 -> n2 = 3-1 = 2 elemen (index 2 dan 3)
    // CATATAN: Bagian kanan dimulai dari (mid+1), BUKAN mid
    int n2 = right - mid;

    // LANGKAH 2: Alokasikan memory untuk array sementara
    // ==================================================
    // MENGAPA perlu array SEMENTARA?
    //   - Tidak bisa langsung menimpa array asli sambil membaca data
    //   - Contoh kesalahan: jika timpa arr[0], data arr[0] lama hilang
    //   - Solusi: buat copy di L dan R, merge kembali ke arr
    //
    // MENGAPA dynamic allocation (new)?
    //   - Ukuran array ditentukan saat RUNTIME (saat program berjalan)
    //   - Tidak bisa int L[n1] karena n1 bukan konstanta saat compile
    //   - new memungkinkan alokasi dengan ukuran variabel
    //
    // KESALAHAN UMUM:
    //   - Lupa delete[] di akhir -> memory leak
    //   - Menggunakan delete (singular) bukan delete[] -> error
    Produk* L = new Produk[n1];  // Array sementara untuk bagian kiri
    Produk* R = new Produk[n2];  // Array sementara untuk bagian kanan

    // LANGKAH 3: Salin data dari array asli ke array sementara
    // ========================================================
    // MENGAPA ada 2 loop TERPISAH?
    //   - Bagian kiri dan kanan berada di posisi berbeda di array asli
    //   - Bagian kiri: arr[left] sampai arr[mid]
    //   - Bagian kanan: arr[mid+1] sampai arr[right]
    //   - Perlu offset berbeda untuk setiap bagian
    //
    // POINTER ARITHMETIC:
    //   - (arr + left + i) = akses elemen dengan offset
    //   - Contoh: (arr + 0 + 0) = arr[0], (arr + 0 + 1) = arr[1]
    //
    // *(L + i) adalah cara mengakses L[i] menggunakan pointer
    // Keduanya sama, tapi pointer adalah versi "polos"
    for (int i = 0; i < n1; i++)
        *(L + i) = *(arr + left + i);  // Salin arr[left..mid] ke L[0..n1-1]

    // Salin BAGIAN KANAN, dimulai dari mid+1
    // Perhatikan: mid + 1 + j (bukan hanya mid + j)
    for (int j = 0; j < n2; j++)
        *(R + j) = *(arr + mid + 1 + j);  // Salin arr[mid+1..right] ke R[0..n2-1]

    // LANGKAH 4: MERGE (penggabungan) dua array sementara ke array asli
    // =================================================================
    // STRATEGI: Gunakan 3 pointer untuk melacak posisi
    //   - i = index di array L
    //   - j = index di array R
    //   - k = index di array hasil (arr)
    //
    // ALASAN menggunakan 3 pointer:
    //   - Kami berjalan melalui L dan R SEKALIGUS (linear)
    //   - Efisiensi TIME: O(n) bukan O(n^2)
    //   - Tanpa 3 pointer, harus cari terus menerus (lambat)
    int i = 0, j = 0, k = left;

    // PROSES PERBANDINGAN: Bandingkan elemen L dan R, ambil yg lebih kecil
    // ===================================================================
    // KONDISI: Loop jika KEDUA array masih punya elemen yang belum diproses
    //   - (i < n1): L masih punya elemen
    //   - (j < n2): R masih punya elemen
    //   - Jika salah satu habis, loop berhenti
    //
    // ALASAN kondisi AND (&&):
    //   - Jika hanya salah satu yang habis, tidak bisa dibandingkan
    //   - Elemen yang tertinggal ditangani di langkah SELANJUTNYA
    //
    // CONTOH PROSES MERGE:
    //   L = [150, 8000]  (Mouse.harga, Laptop.harga)
    //   R = [500, 2500]  (Keyboard.harga, Monitor.harga)
    //
    //   Iter 1: 150 <= 500? YES -> arr[k]=150 (Mouse), i++, k++
    //   Iter 2: 8000 <= 500? NO  -> arr[k]=500 (Keyboard), j++, k++
    //   Iter 3: 8000 <= 2500? NO -> arr[k]=2500 (Monitor), j++, k++
    //   Sekarang j=2 (habis), loop keluar
    while (i < n1 && j < n2) {
        // Bandingkan harga: ambil dari L jika lebih kecil ATAU SAMA
        // CATATAN: <= (less than or equal), bukan < (less than)
        //
        // ALASAN menggunakan <=:
        //   - Ini membuat sorting STABIL (stable sort)
        //   - Data yang sama menjaga urutan aslinya
        //   - Penting untuk data kompleks dengan multiple criteria
        if ((L + i)->harga <= (R + j)->harga) {
            *(arr + k) = *(L + i);  // Ambil elemen dari L
            i++;  // Maju ke elemen berikutnya di L
        }
        // Jika harga R lebih kecil, ambil dari R
        else {
            *(arr + k) = *(R + j);  // Ambil elemen dari R
            j++;  // Maju ke elemen berikutnya di R
        }
        k++;  // Selalu maju ke posisi berikutnya di array hasil
    }

    // LANGKAH 5: Salin SISA elemen dari L (jika masih ada)
    // ===================================================
    // MENGAPA perlu langkah khusus?
    //   - Loop while di atas hanya jalan sampai salah satu array habis
    //   - Ada kemungkinan L MASIH PUNYA elemen yang belum diproses
    //   - R mungkin sudah habis, tapi L masih ada
    //
    // ALASAN bisa langsung dikopi (tanpa perbandingan):
    //   - Elemen sisa di L SUDAH TERURUT
    //   - Semua elemen di L lebih besar dari yang sudah dikopi
    //   - Jadi tinggal dikopi apa adanya ke arr
    //
    // CONTOH: Jika pada loop sebelumnya L masih punya [8000, 9000]
    //         dan R sudah habis, tinggal copy [8000, 9000] ke arr
    //         Tanpa perlu compare lagi
    while (i < n1) {
        *(arr + k) = *(L + i);
        i++;
        k++;
    }

    // LANGKAH 6: Salin SISA elemen dari R (jika masih ada)
    // ===================================================
    // Logika sama dengan langkah 5, tapi untuk array R
    // Jika R masih punya elemen sedangkan L habis, copy R ke arr
    while (j < n2) {
        *(arr + k) = *(R + j);
        j++;
        k++;
    }

    // LANGKAH 7: Bebaskan memory yang sudah dialokasikan
    // =================================================
    // SANGAT PENTING! Jangan pernah lupa delete[]
    //
    // MENGAPA harus delete[]?
    //   - Memory yang dialokasikan dengan new HARUS dibebaskan kembali
    //   - Jika tidak, memory terus bertambah (MEMORY LEAK)
    //   - Program besar akan kehabisan memory dan crash
    //
    // KESALAHAN UMUM:
    //   1. Lupa delete[] sama sekali -> memory leak (paling sering!)
    //   2. Pakai delete bukan delete[] -> undefined behavior, crash
    //   3. delete[] dua kali -> double free error, crash
    //   4. delete[] di function lain -> pointer invalid di sini
    //
    // ALASAN pakai delete[] (bukan delete):
    //   - [] menunjukkan ini array, bukan single element
    //   - delete tanpa [] hanya bebaskan 1 elemen pertama
    delete[] L;  // Bebaskan memory array L
    delete[] R;  // Bebaskan memory array R
}

// ========================================================================
// FUNGSI MERGESORT: Mengurutkan array secara REKURSIF
// ========================================================================
// STRATEGI: DIVIDE & CONQUER
//   1. DIVIDE: Bagi array menjadi 2 bagian
//   2. CONQUER: Sort setiap bagian secara rekursif
//   3. COMBINE: Merge 2 bagian yang sudah sorted (via fungsi merge)
//
// MENGAPA Divide & Conquer?
//   - Problem besar dipecah jadi problem kecil (lebih mudah)
//   - Setiap bagian kecil lebih cepat diproses
//   - Total waktu: O(n log n) lebih cepat dari O(n^2)
//
// HUBUNGAN dengan fungsi merge():
//   - mergeSort() MEMBAGI array
//   - merge() MENGGABUNGKAN bagian yang sudah sorted
//   - Keduanya bekerja sama untuk mengurutkan
//
// PARAMETER:
//   arr   = pointer ke array produk
//   left  = index awal bagian yang diurutkan
//   right = index akhir bagian yang diurutkan
void mergeSort(Produk* arr, int left, int right) {
    // BASE CASE: Jika hanya 1 atau 0 elemen, sudah terurut
    // ===================================================
    // KONDISI: left < right
    //   - Jika left == right: hanya 1 elemen (sudah terurut)
    //   - Jika left > right: invalid range (JANGAN proses)
    //
    // MENGAPA perlu base case?
    //   - Tanpa ini, rekursi akan infinite loop
    //   - Base case adalah "kapan rekursi berhenti"
    //
    // ALASAN left < right bukan <=:
    //   - Jika left == right: sudah terurut (1 elemen)
    //   - Tidak perlu proses lebih lanjut
    if (left < right) {
        // LANGKAH DIVIDE: Cari titik tengah
        // =================================
        // FORMULA: mid = left + (right - left) / 2
        //
        // MENGAPA formula ini?
        //   - Rumus normal: (left + right) / 2 bisa integer overflow
        //   - Rumus aman: left + (right - left) / 2 tidak overflow
        //   - Overflow terjadi jika left dan right sangat besar
        //
        // CONTOH:
        //   left=0, right=3 -> mid = 0 + (3-0)/2 = 1
        //   Bagi jadi [0..1] dan [2..3]
        int mid = left + (right - left) / 2;

        // LANGKAH CONQUER: Rekursi sort BAGIAN KIRI
        // ==========================================
        // ALASAN perlu rekursi:
        //   - Bagian kiri belum terurut, perlu sort terlebih dahulu
        //   - Rekursi akan terus membagi sampai 1 elemen (base case)
        //   - Setiap pemanggilan rekursi LEBIH DEKAT ke base case
        //
        // CONTOH:
        //   mergeSort(arr, 0, 3) -> mergeSort(arr, 0, 1)
        //                           -> mergeSort(arr, 0, 0) [base case]
        //                           -> mergeSort(arr, 1, 1) [base case]
        mergeSort(arr, left, mid);

        // LANGKAH CONQUER: Rekursi sort BAGIAN KANAN
        // ===========================================
        // Logika sama dengan sort bagian kiri
        mergeSort(arr, mid + 1, right);

        // LANGKAH COMBINE: Merge dua bagian yang sudah sorted
        // ==================================================
        // ALASAN merge perlu dipanggil DI SINI:
        //   - Setelah mergeSort(left..mid) dan mergeSort(mid+1..right)
        //   - Kedua bagian SUDAH terurut
        //   - Sekarang tinggal merge untuk gabungkan
        //
        // HUBUNGAN PENTING:
        //   - Jika tidak ada merge(), sorting tidak jadi
        //   - Jika merge() dipanggil sebelum rekursi, salah urutan
        //   - Urutan BENAR: divide -> conquer kiri -> conquer kanan -> merge
        merge(arr, left, mid, right);
    }
}

// ========================================================================
// FUNGSI TAMPILKANDATA: Menampilkan semua elemen array
// ========================================================================
// TUJUAN: Output data dalam format tabel yang mudah dibaca
//
// ALASAN menggunakan pointer arithmetic (arr + i):
//   - (arr + i) = akses elemen ke-i melalui pointer arithmetic
//   - Bukan bracket notation arr[i]
//   - Keduanya sama, tapi pointer menunjukkan low-level operation
//
// HUBUNGAN dengan main():
//   - main() melewatkan pointer array dan jumlah elemen
//   - Function ini bertanggung jawab menampilkan semua n elemen
//   - KESALAHAN UMUM: lupa parameter n, akses elemen invalid
void tampilkanData(Produk* arr, int n) {
    // Tampilkan header tabel dengan pemisah tab
    cout << "ID\tNama\tHarga" << endl;
    cout << "------------------------" << endl;

    // Loop untuk menampilkan setiap elemen dalam array
    // MENGAPA loop dari i=0 sampai i < n?
    //   - Array index dimulai dari 0 (0-based indexing)
    //   - n elemen berarti index 0 sampai n-1
    //   - Jadi kondisi: i < n (bukan i <= n)
    //
    // CONTOH: n=4 elemen
    //   i=0: arr[0]
    //   i=1: arr[1]
    //   i=2: arr[2]
    //   i=3: arr[3]
    //   i=4: STOP (i < 4 FALSE)
    //
    // KESALAHAN UMUM: i <= n -> akses arr[n] (out of bounds!)
    for (int i = 0; i < n; i++) {
        // Gunakan pointer arithmetic (arr + i) untuk akses elemen ke-i
        //
        // MENGAPA pointer arithmetic?
        //   - (arr + i) = alamat elemen ke-i
        //   - Pointer otomatis hitung offset berdasarkan ukuran struct
        //   - Contoh: (arr + 0) = alamat Produk[0]
        //            (arr + 1) = alamat Produk[0] + sizeof(Produk)
        //
        // EQUIVALENSI:
        //   - (arr + i) setara dengan &arr[i]
        //   - Keduanya menunjuk ke elemen yang sama
        cout << (arr + i)->nim << "\t" << (arr + i)->nama << endl;
    }
    cout << endl;
}

// ========================================================================
// FUNGSI MAIN: Titik awal program
// ========================================================================
// ALUR PROGRAM:
//   1. Inisialisasi data produk dalam array
//   2. Tampilkan data sebelum diurutkan (posisi acak)
//   3. Panggil mergeSort untuk mengurutkan berdasarkan harga
//   4. Tampilkan data setelah diurutkan (urut ascending)
//
// MENGAPA perlu tampilkan BEFORE dan AFTER?
//   - BEFORE: buktikan bahwa data awal tidak terurut
//   - AFTER: buktikan bahwa algoritma bekerja dengan benar
//   - Perbandingan menunjukkan efektivitas sorting
int main() {
    // LANGKAH 1: Tentukan jumlah elemen
    // ==================================
    int n = 4;

    // LANGKAH 2: Inisialisasi Array of Struct
    // =======================================
    // DATA AWAL (POSISI ACAK):
    //   Index 0: {id: 101, nama: "Laptop", harga: 8000}   <- HARGA BESAR (awal)
    //   Index 1: {id: 102, nama: "Mouse ", harga: 150}    <- HARGA KECIL (awal)
    //   Index 2: {id: 103, nama: "Monitor", harga: 2500}  <- HARGA SEDANG (awal)
    //   Index 3: {id: 104, nama: "Keyboard", harga: 500}  <- HARGA SEDANG (awal)
    //
    // ALASAN data ini dipilih:
    //   - Harga TIDAK terurut (8000, 150, 2500, 500)
    //   - Menunjukkan bahwa mergeSort BISA mengurutkan data acak
    //   - Setiap produk memiliki id dan nama (real-world data)
    //
    // MENGAPA struct?
    //   - Menyimpan informasi terkait (id, nama, harga) bersama
    //   - Ketika sort, data tetap bersama (tidak terpisah)
    //   - Lebih efisien daripada 3 array terpisah
    Produk daftarProduk[4] = {
        {101, "Laptop", 8000},
        {102, "Mouse ", 150},
        {103, "Monitor", 2500},
        {104, "Keyboard", 500}
    };

    // LANGKAH 3: Tampilkan data SEBELUM sorting
    // =========================================
    cout << "Data Sebelum Sorting (Berdasarkan Harga):" << endl;
    // Panggil tampilkanData dengan:
    //   - daftarProduk: pointer ke elemen pertama array
    //   - n: jumlah elemen yang ingin ditampilkan
    //
    // ALASAN: function tampilkanData memerlukan pointer dan ukuran array
    // CATATAN: daftarProduk automatic convert jadi pointer dalam C++
    tampilkanData(daftarProduk, n);

    // LANGKAH 4: Panggil mergeSort untuk mengurutkan
    // ==============================================
    // Parameter:
    //   daftarProduk: pointer ke array
    //   0: index awal (SELALU 0 untuk full array)
    //   n-1: index akhir (SELALU n-1 untuk full array)
    //
    // MENGAPA n-1 bukan n?
    //   - Index dimulai dari 0, jadi 4 elemen = index 0,1,2,3
    //   - Index akhir adalah 3, bukan 4
    //   - Akses arr[4] akan OUT OF BOUNDS
    //
    // PROSES INTERNAL MERGESORT:
    //   1. Divide: bagi [0,3] jadi [0,1] dan [2,3]
    //   2. Divide lagi: [0,0], [1,1], [2,2], [3,3]
    //   3. Merge: [0,1], [2,3]
    //   4. Merge: [0,3] <- RESULT SORTED
    mergeSort(daftarProduk, 0, n - 1);

    // LANGKAH 5: Tampilkan data SETELAH sorting
    // =========================================
    cout << "Data Setelah Sorting (Merge Sort O(n log n)):" << endl;
    // DATA SETELAH SORT (ASCENDING by harga):
    //   Index 0: {id: 102, nama: "Mouse ", harga: 150}    <- TERKECIL
    //   Index 1: {id: 104, nama: "Keyboard", harga: 500}
    //   Index 2: {id: 103, nama: "Monitor", harga: 2500}
    //   Index 3: {id: 101, nama: "Laptop", harga: 8000}   <- TERBESAR
    //
    // BUKTI: Harga terurut ascending (150 < 500 < 2500 < 8000)
    // KESALAHAN UMUM: Lupa mergeSort(), data masih acak seperti awal
    tampilkanData(daftarProduk, n);

    // Return 0 menunjukkan program berjalan tanpa error
    return 0;
}

