#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

struct Hewan {
	int id;
	string nama;
	string jenis;
	int umur;
	double harga;
};

void swapHewan(Hewan *a, Hewan *b) {
	Hewan temp = *a;
	*a = *b;
	*b = temp;
}

void tampilSemuaData(const Hewan *arr, int n) {
	if (n == 0) {
		cout << endl << "Belum ada data hewan." << endl;
		return;
	}

	cout << endl << "==================== DATA HEWAN PAWCARE ====================" << endl;
	cout << left << setw(6) << "ID" << setw(18) << "Nama" << setw(16) << "Jenis"
		 << setw(8) << "Umur" << "Harga" << endl;
	cout << "------------------------------------------------------------" << endl;

	const Hewan *p = arr;
	for (int i = 0; i < n; ++i) {
		cout << left << setw(6) << (p + i)->id << setw(18) << (p + i)->nama << setw(16)
			 << (p + i)->jenis << setw(8) << (p + i)->umur << "Rp " << fixed
			 << setprecision(0) << (p + i)->harga << endl;
	}
}

void tambahDataBaru(Hewan *arr, int &n, int kapasitas) {
	if (n >= kapasitas) {
		cout << endl << "Kapasitas penuh. Data gagal ditambahkan." << endl;
		return;
	}

	Hewan *target = arr + n;
	cout << endl << "Masukkan data hewan baru" << endl;
	cout << "ID hewan      : ";
	cin >> target->id;
	char buang;
	while (cin.get(buang) && buang != 10) {
	}

	cout << "Nama hewan    : ";
	getline(cin, target->nama);

	cout << "Jenis hewan   : ";
	getline(cin, target->jenis);

	cout << "Umur (tahun)  : ";
	cin >> target->umur;

	cout << "Harga layanan : ";
	cin >> target->harga;

	++n;
	cout << "Data hewan berhasil ditambahkan." << endl;
}

void tambahDataDenganResize(Hewan *&arr, int &n, int &kapasitas) {
	if (n < kapasitas) {
		tambahDataBaru(arr, n, kapasitas);
		return;
	}

	int kapasitasBaru = kapasitas * 2;
	Hewan *arrBaru = new Hewan[kapasitasBaru];

	for (int i = 0; i < n; ++i) {
		*(arrBaru + i) = *(arr + i);
	}

	delete[] arr;
	arr = arrBaru;
	kapasitas = kapasitasBaru;

	cout << endl << "Kapasitas diperbesar menjadi " << kapasitas << " data." << endl;
	tambahDataBaru(arr, n, kapasitas);
}

int linearSearchNama(Hewan *arr, int n, const string &namaDicari) {
	for (int i = 0; i < n; ++i) {
		if ((arr + i)->nama == namaDicari) {
			if (i != 0) {
				swapHewan(arr, arr + i);
				cout << "Data ditemukan dan dipindah ke indeks 0 (swap pointer)." << endl;
				return 0;
			}
			return i;
		}
	}
	return -1;
}

void sortIdAsc(Hewan *arr, int n) {
	for (int i = 0; i < n - 1; ++i) {
		int idxMin = i;
		for (int j = i + 1; j < n; ++j) {
			if ((arr + j)->id < (arr + idxMin)->id) {
				idxMin = j;
			}
		}
		if (idxMin != i) {
			swapHewan(arr + i, arr + idxMin);
		}
	}
}

int fibonacciSearchById(Hewan *arr, int n, int idDicari) {
	if (n == 0) {
		return -1;
	}

	int fibMm2 = 0;
	int fibMm1 = 1;
	int fibM = fibMm2 + fibMm1;

	while (fibM < n) {
		fibMm2 = fibMm1;
		fibMm1 = fibM;
		fibM = fibMm2 + fibMm1;
	}

	int offset = -1;
	int iterasi = 1;

	while (fibM > 1) {
		int i = min(offset + fibMm2, n - 1);
		cout << "Iterasi " << iterasi++ << ": cek index " << i << " (ID=" << (arr + i)->id
			 << ")" << endl;

		if ((arr + i)->id < idDicari) {
			fibM = fibMm1;
			fibMm1 = fibMm2;
			fibMm2 = fibM - fibMm1;
			offset = i;
		} else if ((arr + i)->id > idDicari) {
			fibM = fibMm2;
			fibMm1 = fibMm1 - fibMm2;
			fibMm2 = fibM - fibMm1;
		} else {
			if (i != 0) {
				swapHewan(arr, arr + i);
				cout << "Data ditemukan dan dipindah ke indeks 0 (swap pointer)." << endl;
				return 0;
			}
			return i;
		}
	}

	if (fibMm1 && offset + 1 < n && (arr + (offset + 1))->id == idDicari) {
		int idx = offset + 1;
		cout << "Iterasi " << iterasi << ": cek index " << idx << " (ID=" << (arr + idx)->id
			 << ")" << endl;
		if (idx != 0) {
			swapHewan(arr, arr + idx);
			cout << "Data ditemukan dan dipindah ke indeks 0 (swap pointer)." << endl;
			return 0;
		}
		return idx;
	}

	return -1;
}

void bubbleSortNamaAZ(Hewan *arr, int n) {
	for (int i = 0; i < n - 1; ++i) {
		bool swapped = false;
		for (int j = 0; j < n - i - 1; ++j) {
			if ((arr + j)->nama > (arr + j + 1)->nama) {
				swapHewan(arr + j, arr + j + 1);
				swapped = true;
			}
		}
		if (!swapped) {
			break;
		}
	}
}

void selectionSortHargaMurah(Hewan *arr, int n) {
	for (int i = 0; i < n - 1; ++i) {
		int idxMin = i;
		for (int j = i + 1; j < n; ++j) {
			if ((arr + j)->harga < (arr + idxMin)->harga) {
				idxMin = j;
			}
		}
		if (idxMin != i) {
			swapHewan(arr + i, arr + idxMin);
		}
	}
}

void tampilDataSingle(const Hewan *h) {
	cout << "ID      : " << h->id << endl;
	cout << "Nama    : " << h->nama << endl;
	cout << "Jenis   : " << h->jenis << endl;
	cout << "Umur    : " << h->umur << " tahun" << endl;
	cout << "Harga   : Rp " << fixed << setprecision(0) << h->harga << endl;
}

int main() {
	int kapasitas = 10;
	int jumlah = 5;

	Hewan *data = new Hewan[kapasitas];
	data[0] = {102, "Milo", "Kucing", 2, 75000};
	data[1] = {88, "Buddy", "Anjing", 3, 125000};
	data[2] = {150, "Nemo", "Ikan", 1, 50000};
	data[3] = {73, "Coco", "Kelinci", 2, 60000};
	data[4] = {120, "Luna", "Kucing", 4, 90000};

	int pilihan;
	do {
		cout << endl
			 << "========== MENU PAWCARE PETSHOP ==========" << endl
			 << "1. Tampil semua data hewan" << endl
			 << "2. Tambah data hewan baru" << endl
			 << "3. Linear Search berdasarkan nama" << endl
			 << "4. Fibonacci Search berdasarkan ID" << endl
			 << "5. Bubble Sort nama (A-Z)" << endl
			 << "6. Selection Sort harga (termurah)" << endl
			 << "0. Keluar" << endl
			 << "Pilih menu: ";
		cin >> pilihan;
		   char buang;
		   while (cin.get(buang) && buang != 10) {
		   }

		if (pilihan == 1) {
			tampilSemuaData(data, jumlah);
		} else if (pilihan == 2) {
			tambahDataDenganResize(data, jumlah, kapasitas);
		} else if (pilihan == 3) {
			string namaCari;
			cout << endl << "Masukkan nama hewan yang dicari: ";
			getline(cin, namaCari);

			int idx = linearSearchNama(data, jumlah, namaCari);
			if (idx != -1) {
				cout << "Data hewan ditemukan:" << endl;
				tampilDataSingle(data + idx);
			} else {
				cout << "Data hewan dengan nama tersebut tidak ditemukan." << endl;
			}
		} else if (pilihan == 4) {
			int idCari;
			cout << endl << "Masukkan ID hewan yang dicari: ";
			cin >> idCari;

			Hewan *temp = new Hewan[jumlah];
			for (int i = 0; i < jumlah; ++i) {
				*(temp + i) = *(data + i);
			}

			sortIdAsc(temp, jumlah);

			cout << endl << "Proses Fibonacci Search:" << endl;
			int idx = fibonacciSearchById(temp, jumlah, idCari);
			if (idx != -1) {
				cout << "Data hewan ditemukan:" << endl;
				tampilDataSingle(temp + idx);
			} else {
				cout << "Data hewan dengan ID tersebut tidak ditemukan." << endl;
			}
			delete[] temp;
		} else if (pilihan == 5) {
			bubbleSortNamaAZ(data, jumlah);
			cout << "Data berhasil diurutkan berdasarkan nama (A-Z)." << endl;
		} else if (pilihan == 6) {
			selectionSortHargaMurah(data, jumlah);
			cout << "Data berhasil diurutkan berdasarkan harga (termurah)." << endl;
		} else if (pilihan == 0) {
			cout << "Program selesai." << endl;
		} else {
			cout << "Pilihan tidak valid." << endl;
		}
	} while (pilihan != 0);

	delete[] data;
	return 0;
}
