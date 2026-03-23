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

void clearInputLine() {
	char ch;
	while (cin.get(ch) && ch != '\n') {
	}
}

void swapHewan(Hewan *a, Hewan *b) {
	Hewan temp = *a;
	*a = *b;
	*b = temp;
}

void tampilSemuaData(const Hewan *arr, int n) {
	if (n == 0) {
		cout << "\nBelum ada data hewan.\n";
		return;
	}

	cout << "\n==================== DATA HEWAN PAWCARE ====================\n";
	cout << left << setw(6) << "ID" << setw(18) << "Nama" << setw(16) << "Jenis"
		 << setw(8) << "Umur" << "Harga" << '\n';
	cout << "------------------------------------------------------------\n";

	const Hewan *p = arr;
	for (int i = 0; i < n; ++i) {
		cout << left << setw(6) << (p + i)->id << setw(18) << (p + i)->nama << setw(16)
			 << (p + i)->jenis << setw(8) << (p + i)->umur << "Rp " << fixed
			 << setprecision(0) << (p + i)->harga << '\n';
	}
}

void tambahDataBaru(Hewan *arr, int &n, int kapasitas) {
	if (n >= kapasitas) {
		cout << "\nKapasitas penuh. Data gagal ditambahkan.\n";
		return;
	}

	Hewan *target = arr + n;
	cout << "\nMasukkan data hewan baru\n";
	cout << "ID hewan      : ";
	cin >> target->id;
	clearInputLine();

	cout << "Nama hewan    : ";
	getline(cin, target->nama);

	cout << "Jenis hewan   : ";
	getline(cin, target->jenis);

	cout << "Umur (tahun)  : ";
	cin >> target->umur;

	cout << "Harga layanan : ";
	cin >> target->harga;

	++n;
	cout << "Data hewan berhasil ditambahkan.\n";
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

	cout << "\nKapasitas diperbesar menjadi " << kapasitas << " data.\n";
	tambahDataBaru(arr, n, kapasitas);
}

int linearSearchNama(Hewan *arr, int n, const string &namaDicari) {
	for (int i = 0; i < n; ++i) {
		if ((arr + i)->nama == namaDicari) {
			if (i != 0) {
				swapHewan(arr, arr + i);
				cout << "Data ditemukan dan dipindah ke indeks 0 (swap pointer).\n";
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
			 << ")\n";

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
				cout << "Data ditemukan dan dipindah ke indeks 0 (swap pointer).\n";
				return 0;
			}
			return i;
		}
	}

	if (fibMm1 && offset + 1 < n && (arr + (offset + 1))->id == idDicari) {
		int idx = offset + 1;
		cout << "Iterasi " << iterasi << ": cek index " << idx << " (ID=" << (arr + idx)->id
			 << ")\n";
		if (idx != 0) {
			swapHewan(arr, arr + idx);
			cout << "Data ditemukan dan dipindah ke indeks 0 (swap pointer).\n";
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
	cout << "ID      : " << h->id << '\n';
	cout << "Nama    : " << h->nama << '\n';
	cout << "Jenis   : " << h->jenis << '\n';
	cout << "Umur    : " << h->umur << " tahun\n";
	cout << "Harga   : Rp " << fixed << setprecision(0) << h->harga << "\n";
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
		cout << "\n========== MENU PAWCARE PETSHOP =========="
			 << "\n1. Tampil semua data hewan"
			 << "\n2. Tambah data hewan baru"
			 << "\n3. Linear Search berdasarkan nama"
			 << "\n4. Fibonacci Search berdasarkan ID"
			 << "\n5. Bubble Sort nama (A-Z)"
			 << "\n6. Selection Sort harga (termurah)"
			 << "\n0. Keluar"
			 << "\nPilih menu: ";
		cin >> pilihan;
		   clearInputLine();

		if (pilihan == 1) {
			tampilSemuaData(data, jumlah);
		} else if (pilihan == 2) {
			tambahDataDenganResize(data, jumlah, kapasitas);
		} else if (pilihan == 3) {
			string namaCari;
			cout << "\nMasukkan nama hewan yang dicari: ";
			getline(cin, namaCari);

			int idx = linearSearchNama(data, jumlah, namaCari);
			if (idx != -1) {
				cout << "Data hewan ditemukan:\n";
				tampilDataSingle(data + idx);
			} else {
				cout << "Data hewan dengan nama tersebut tidak ditemukan.\n";
			}
		} else if (pilihan == 4) {
			int idCari;
			cout << "\nMasukkan ID hewan yang dicari: ";
			cin >> idCari;

			Hewan *temp = new Hewan[jumlah];
			for (int i = 0; i < jumlah; ++i) {
				*(temp + i) = *(data + i);
			}

			sortIdAsc(temp, jumlah);

			cout << "\nProses Fibonacci Search:\n";
			int idx = fibonacciSearchById(temp, jumlah, idCari);
			if (idx != -1) {
				cout << "Data hewan ditemukan:\n";
				tampilDataSingle(temp + idx);
			} else {
				cout << "Data hewan dengan ID tersebut tidak ditemukan.\n";
			}
			delete[] temp;
		} else if (pilihan == 5) {
			bubbleSortNamaAZ(data, jumlah);
			cout << "Data berhasil diurutkan berdasarkan nama (A-Z).\n";
		} else if (pilihan == 6) {
			selectionSortHargaMurah(data, jumlah);
			cout << "Data berhasil diurutkan berdasarkan harga (termurah).\n";
		} else if (pilihan == 0) {
			cout << "Program selesai.\n";
		} else {
			cout << "Pilihan tidak valid.\n";
		}
	} while (pilihan != 0);

	delete[] data;
	return 0;
}
