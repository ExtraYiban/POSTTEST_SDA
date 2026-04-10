#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

const int MAX = 50;

struct Hewan {
	int id;
	string nama;
	string jenis;
	int umur;
	double harga;
};

struct RiwayatTindakan {
	Hewan pasien;
	string tindakan;
};

bool parseInt(const string &text, int &nilai) {
	stringstream ss(text);
	ss >> nilai;
	return ss && ss.eof();
}

bool parseDouble(const string &text, double &nilai) {
	stringstream ss(text);
	ss >> nilai;
	return ss && ss.eof();
}

int inputIntMin(const string &prompt, int minVal) {
	while (true) {
		cout << prompt;
		string line;
		getline(cin, line);

		int nilai;
		if (parseInt(line, nilai) && nilai >= minVal) {
			return nilai;
		}

		cout << "Input tidak valid. Minimal nilai adalah " << minVal << "." << endl;
	}
}

double inputDoubleMin(const string &prompt, double minVal) {
	while (true) {
		cout << prompt;
		string line;
		getline(cin, line);

		double nilai;
		if (parseDouble(line, nilai) && nilai >= minVal) {
			return nilai;
		}

		cout << "Input tidak valid. Nilai tidak boleh kurang dari " << fixed << setprecision(0)
			 << minVal << "." << endl;
	}
}

string inputNonKosong(const string &prompt) {
	while (true) {
		cout << prompt;
		string line;
		getline(cin, line);
		if (!line.empty()) {
			return line;
		}
		cout << "Input tidak boleh kosong." << endl;
	}
}

void tampilSemuaData(const vector<Hewan> &data) {
	if (data.empty()) {
		cout << endl << "Belum ada data hewan." << endl;
		return;
	}

	cout << endl << "==================== DATA HEWAN PAWCARE ====================" << endl;
	cout << left << setw(6) << "ID" << setw(18) << "Nama" << setw(16) << "Jenis"
		 << setw(8) << "Umur" << "Harga" << endl;
	cout << "------------------------------------------------------------" << endl;

	const Hewan *p = data.data();
	for (size_t i = 0; i < data.size(); ++i) {
		cout << left << setw(6) << (*(p + i)).id << setw(18) << (*(p + i)).nama << setw(16)
			 << (*(p + i)).jenis << setw(8) << (*(p + i)).umur << "Rp " << fixed
			 << setprecision(0) << (*(p + i)).harga << endl;
	}
}

int cariHewanById(const vector<Hewan> &data, int idCari) {
	const Hewan *p = data.data();
	for (size_t i = 0; i < data.size(); ++i) {
		if ((*(p + i)).id == idCari) {
			return static_cast<int>(i);
		}
	}
	return -1;
}

void tambahDataBaru(vector<Hewan> &data) {
	cout << endl << "Masukkan data hewan baru" << endl;

	int idBaru;
	while (true) {
		idBaru = inputIntMin("ID hewan      : ", 1);
		if (cariHewanById(data, idBaru) == -1) {
			break;
		}
		cout << "ID sudah terdaftar. Masukkan ID lain." << endl;
	}

	Hewan baru;
	baru.id = idBaru;
	baru.nama = inputNonKosong("Nama hewan    : ");
	baru.jenis = inputNonKosong("Jenis hewan   : ");
	baru.umur = inputIntMin("Umur (tahun)  : ", 0);
	baru.harga = inputDoubleMin("Harga layanan : ", 0);

	data.push_back(baru);
	cout << "Data hewan berhasil ditambahkan." << endl;
}

int linearSearchNama(const vector<Hewan> &data, const string &namaDicari) {
	const Hewan *p = data.data();
	for (size_t i = 0; i < data.size(); ++i) {
		if ((*(p + i)).nama == namaDicari) {
			return static_cast<int>(i);
		}
	}
	return -1;
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

	while (fibM > 1) {
		int i = min(offset + fibMm2, n - 1);

		if ((*(arr + i)).id < idDicari) {
			fibM = fibMm1;
			fibMm1 = fibMm2;
			fibMm2 = fibM - fibMm1;
			offset = i;
		} else if ((*(arr + i)).id > idDicari) {
			fibM = fibMm2;
			fibMm1 = fibMm1 - fibMm2;
			fibMm2 = fibM - fibMm1;
		} else {
			return i;
		}
	}

	if (fibMm1 && offset + 1 < n && (*(arr + (offset + 1))).id == idDicari) {
		return offset + 1;
	}

	return -1;
}

void sortNamaAZ(vector<Hewan> &data) {
	sort(data.begin(), data.end(), [](const Hewan &a, const Hewan &b) {
		return a.nama < b.nama;
	});
}

void sortHargaMurah(vector<Hewan> &data) {
	sort(data.begin(), data.end(), [](const Hewan &a, const Hewan &b) {
		return a.harga < b.harga;
	});
}

void tampilDataSingle(const Hewan *h) {
	cout << "ID      : " << (*h).id << endl;
	cout << "Nama    : " << (*h).nama << endl;
	cout << "Jenis   : " << (*h).jenis << endl;
	cout << "Umur    : " << (*h).umur << " tahun" << endl;
	cout << "Harga   : Rp " << fixed << setprecision(0) << (*h).harga << endl;
}
void enqueuePasien(Hewan *antrian, int &jumlahAntrian, const Hewan *pasien) {
	if (jumlahAntrian >= MAX) {
		cout << "Antrian penuh (overflow). Pasien gagal ditambahkan." << endl;
		return;
	}

	for (int i = 0; i < jumlahAntrian; ++i) {
		if ((*(antrian + i)).id == (*pasien).id) {
			cout << "Pasien sudah ada di antrian. Tidak boleh duplikat." << endl;
			return;
		}
	}

	*(antrian + jumlahAntrian) = *pasien;
	++jumlahAntrian;
	cout << "Pasien masuk ke antrian pemeriksaan." << endl;
}

bool dequeuePasien(Hewan *antrian, int &jumlahAntrian, Hewan *keluar) {
	if (jumlahAntrian <= 0) {
		cout << "Antrian kosong (underflow). Tidak ada pasien untuk dipanggil." << endl;
		return false;
	}

	*keluar = *antrian;

	for (int i = 0; i < jumlahAntrian - 1; ++i) {
		*(antrian + i) = *(antrian + i + 1);
	}

	--jumlahAntrian;
	return true;
}

void tampilSemuaAntrian(const Hewan *antrian, int jumlahAntrian) {
	if (jumlahAntrian == 0) {
		cout << "Antrian pemeriksaan masih kosong." << endl;
		return;
	}

	cout << "\n===== ANTRIAN PEMERIKSAAN (Front -> Rear) =====" << endl;
	cout << left << setw(6) << "ID" << setw(18) << "Nama" << setw(16) << "Jenis" << endl;
	cout << "------------------------------------------" << endl;

	const Hewan *p = antrian;
	for (int i = 0; i < jumlahAntrian; ++i) {
		cout << left << setw(6) << (*(p + i)).id << setw(18) << (*(p + i)).nama << setw(16)
			 << (*(p + i)).jenis << endl;
	}
}

void peekAntrian(const Hewan *antrian, int jumlahAntrian) {
	if (jumlahAntrian == 0) {
		cout << "Antrian kosong. Tidak ada front." << endl;
		return;
	}

	cout << "Front antrian: " << (*antrian).nama << " (ID " << (*antrian).id << ")" << endl;
}

void pushRiwayat(RiwayatTindakan *stack, int &top, const Hewan *pasien, const string &tindakan) {
	if (top >= MAX - 1) {
		cout << "Riwayat penuh (overflow). Data tindakan gagal disimpan." << endl;
		return;
	}

	++top;
	(*(stack + top)).pasien = *pasien;
	(*(stack + top)).tindakan = tindakan;
	cout << "Tindakan berhasil dicatat ke riwayat." << endl;
}

void popRiwayat(RiwayatTindakan *stack, int &top) {
	if (top < 0) {
		cout << "Riwayat kosong (underflow). Tidak ada tindakan untuk dihapus." << endl;
		return;
	}

	cout << "Riwayat terakhir dihapus: " << (*(stack + top)).pasien.nama << " (ID "
		 << (*(stack + top)).pasien.id << ") - " << (*(stack + top)).tindakan << endl;
	--top;
}

void peekRiwayat(const RiwayatTindakan *stack, int top) {
	if (top < 0) {
		cout << "Riwayat kosong. Tidak ada top stack." << endl;
		return;
	}

	cout << "Tindakan terakhir: " << (*(stack + top)).pasien.nama << " (ID "
		 << (*(stack + top)).pasien.id << ") - " << (*(stack + top)).tindakan << endl;
}

void tampilSemuaRiwayat(const RiwayatTindakan *stack, int top) {
	if (top < 0) {
		cout << "Riwayat tindakan masih kosong." << endl;
		return;
	}

	cout << "\n===== RIWAYAT TINDAKAN (Top -> Bottom) =====" << endl;
	cout << left << setw(6) << "ID" << setw(18) << "Nama" << "Tindakan" << endl;
	cout << "--------------------------------------------------" << endl;

	const RiwayatTindakan *p = stack;
	for (int i = top; i >= 0; --i) {
		cout << left << setw(6) << (*(p + i)).pasien.id << setw(18) << (*(p + i)).pasien.nama
			 << (*(p + i)).tindakan << endl;
	}
}

int main() {
	vector<Hewan> data = {
		{102, "Milo", "Kucing", 2, 75000},
		{88, "Buddy", "Anjing", 3, 125000},
		{150, "Nemo", "Ikan", 1, 50000},
		{73, "Coco", "Kelinci", 2, 60000},
		{120, "Luna", "Kucing", 4, 90000}
	};

	Hewan antrianPemeriksaan[MAX];
	int jumlahAntrian = 0;

	RiwayatTindakan riwayatTindakan[MAX];
	int topRiwayat = -1;

	int pilihan;
	do {
		cout << endl
			 << "========== MENU PAWCARE PETSHOP ==========" << endl
			 << "1. Tampil semua data hewan" << endl
			 << "2. Tambah data hewan baru" << endl
			 << "3. Linear Search berdasarkan nama" << endl
			 << "4. Fibonacci Search berdasarkan ID" << endl
			 << "5. Sort nama (A-Z)" << endl
			 << "6. Sort harga (termurah)" << endl
			 << "7. Enqueue antrian pemeriksaan" << endl
			 << "8. Dequeue (panggil pasien)" << endl
			 << "9. Peek antrian & riwayat" << endl
			 << "10. Pop riwayat tindakan" << endl
			 << "11. Tampil semua antrian" << endl
			 << "12. Tampil semua riwayat tindakan" << endl
			 << "0. Keluar" << endl
			 << "Pilih menu: ";
		string menuInput;
		getline(cin, menuInput);
		if (!parseInt(menuInput, pilihan)) {
			pilihan = -1;
		}

		if (pilihan == 1) {
			tampilSemuaData(data);
		} else if (pilihan == 2) {
			tambahDataBaru(data);
		} else if (pilihan == 3) {
			string namaCari = inputNonKosong("\nMasukkan nama hewan yang dicari: ");

			int idx = linearSearchNama(data, namaCari);
			if (idx != -1) {
				cout << "Data hewan ditemukan:" << endl;
				tampilDataSingle(data.data() + idx);
			} else {
				cout << "Data hewan dengan nama tersebut tidak ditemukan." << endl;
			}
		} else if (pilihan == 4) {
			int idCari = inputIntMin("\nMasukkan ID hewan yang dicari: ", 1);

			vector<Hewan> temp = data;
			sort(temp.begin(), temp.end(), [](const Hewan &a, const Hewan &b) {
				return a.id < b.id;
			});

			cout << endl << "Proses Fibonacci Search:" << endl;
			int idx = fibonacciSearchById(temp.data(), static_cast<int>(temp.size()), idCari);
			if (idx != -1) {
				cout << "Data hewan ditemukan:" << endl;
				tampilDataSingle(temp.data() + idx);
			} else {
				cout << "Data hewan dengan ID tersebut tidak ditemukan." << endl;
			}
		} else if (pilihan == 5) {
			sortNamaAZ(data);
			cout << "Data berhasil diurutkan berdasarkan nama (A-Z)." << endl;
		} else if (pilihan == 6) {
			sortHargaMurah(data);
			cout << "Data berhasil diurutkan berdasarkan harga (termurah)." << endl;
		} else if (pilihan == 7) {
			int idDaftar = inputIntMin("\nMasukkan ID hewan yang ingin masuk antrian: ", 1);

			int idxData = cariHewanById(data, idDaftar);
			if (idxData == -1) {
				cout << "ID tidak ditemukan pada data hewan." << endl;
			} else {
				enqueuePasien(antrianPemeriksaan, jumlahAntrian, data.data() + idxData);
			}
		} else if (pilihan == 8) {
			Hewan pasienDipanggil;
			if (dequeuePasien(antrianPemeriksaan, jumlahAntrian, &pasienDipanggil)) {
				cout << "Pasien dipanggil: " << pasienDipanggil.nama << " (ID "
					 << pasienDipanggil.id << ")" << endl;

				cout << "Masukkan tindakan medis: ";
				string tindakan;
				getline(cin, tindakan);

				if (tindakan.empty()) {
					tindakan = "Pemeriksaan umum";
				}

				pushRiwayat(riwayatTindakan, topRiwayat, &pasienDipanggil, tindakan);
			}
		} else if (pilihan == 9) {
			peekAntrian(antrianPemeriksaan, jumlahAntrian);
			peekRiwayat(riwayatTindakan, topRiwayat);
		} else if (pilihan == 10) {
			popRiwayat(riwayatTindakan, topRiwayat);
		} else if (pilihan == 11) {
			tampilSemuaAntrian(antrianPemeriksaan, jumlahAntrian);
		} else if (pilihan == 12) {
			tampilSemuaRiwayat(riwayatTindakan, topRiwayat);
		} else if (pilihan == 0) {
			cout << "Program selesai." << endl;
		} else {
			cout << "Pilihan tidak valid." << endl;
		}
	} while (pilihan != 0);

	return 0;
}
