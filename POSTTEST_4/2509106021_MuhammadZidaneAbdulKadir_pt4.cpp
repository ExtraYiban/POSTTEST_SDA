#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

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

struct NodeHewan {
	Hewan data;
	NodeHewan* next;
};

struct NodeRiwayat {
	RiwayatTindakan data;
	NodeRiwayat* next;
};

bool parseInt(const string &text, int &nilai) {
	stringstream ss(text);
	ss >> nilai;
	return ss && ss.eof();
}

string inputNonKosong(const string &prompt) {
	while (true) {
		cout << prompt;
		string line;
		getline(cin, line);
		if (!line.empty()) return line;
		cout << "Input tidak boleh kosong." << endl;
	}
}

void tampilSemuaData(const vector<Hewan> &data) {
	cout << endl << "=== DATA HEWAN ===" << endl;
	for (auto &h : data) {
		cout << h.id << " - " << h.nama << endl;
	}
}

int cariHewanById(const vector<Hewan> &data, int idCari) {
	for (int i = 0; i < data.size(); i++) {
		if (data[i].id == idCari) return i;
	}
	return -1;
}

void enqueue(NodeHewan*& front, NodeHewan*& rear, Hewan data) {
	NodeHewan* baru = new NodeHewan{data, nullptr};

	if (front == nullptr) {
		front = rear = baru;
	} else {
		rear->next = baru;
		rear = baru;
	}

	cout << "Pasien masuk antrian." << endl;
}

bool dequeue(NodeHewan*& front, NodeHewan*& rear, Hewan& keluar) {
	if (front == nullptr) {
		cout << "Antrian kosong (underflow)." << endl;
		return false;
	}

	NodeHewan* hapus = front;
	keluar = front->data;
	front = front->next;

	if (front == nullptr) rear = nullptr;

	delete hapus;
	return true;
}

void peekAntrian(NodeHewan* front) {
	if (front == nullptr) {
		cout << "Antrian kosong." << endl;
		return;
	}
	cout << "Front: " << front->data.nama << endl;
}

void tampilAntrian(NodeHewan* front) {
	if (front == nullptr) {
		cout << "Antrian kosong." << endl;
		return;
	}

	NodeHewan* p = front;
	while (p != nullptr) {
		cout << p->data.id << " - " << p->data.nama << endl;
		p = p->next;
	}
}

void pushRiwayat(NodeRiwayat*& top, Hewan pasien, string tindakan) {
	NodeRiwayat* baru = new NodeRiwayat{{pasien, tindakan}, top};
	top = baru;
	cout << "Riwayat ditambahkan." << endl;
}

void popRiwayat(NodeRiwayat*& top) {
	if (top == nullptr) {
		cout << "Riwayat kosong (underflow)." << endl;
		return;
	}

	NodeRiwayat* hapus = top;
	cout << "Hapus: " << top->data.pasien.nama << endl;

	top = top->next;
	delete hapus;
}

void peekRiwayat(NodeRiwayat* top) {
	if (top == nullptr) {
		cout << "Riwayat kosong." << endl;
		return;
	}
	cout << "Top: " << top->data.pasien.nama << endl;
}

void tampilRiwayat(NodeRiwayat* top) {
	if (top == nullptr) {
		cout << "Riwayat kosong." << endl;
		return;
	}

	NodeRiwayat* p = top;
	while (p != nullptr) {
		cout << p->data.pasien.nama << " - " << p->data.tindakan << endl;
		p = p->next;
	}
}

// ================= MAIN =================
int main() {
	vector<Hewan> data = {
		{102, "Milo", "Kucing", 2, 75000},
		{88, "Buddy", "Anjing", 3, 125000},
		{150, "Nemo", "Ikan", 1, 50000}
	};

	NodeHewan* front = nullptr;
	NodeHewan* rear = nullptr;
	NodeRiwayat* top = nullptr;

	int pilihan;

	do {
		cout << endl << "=== MENU ===" << endl;
		cout << "1. Tampil Data" << endl;
		cout << "2. Enqueue" << endl;
		cout << "3. Dequeue" << endl;
		cout << "4. Peek Antrian" << endl;
		cout << "5. Tampil Antrian" << endl;
		cout << "6. Pop Riwayat" << endl;
		cout << "7. Peek Riwayat" << endl;
		cout << "8. Tampil Riwayat" << endl;
		cout << "0. Keluar" << endl;
		cout << "Pilih: ";

		string input;
		getline(cin, input);
		parseInt(input, pilihan);

		if (pilihan == 1) {
			tampilSemuaData(data);
		}

		else if (pilihan == 2) {
			int id;
			cout << "ID: ";
			cin >> id;
			cin.ignore();

			int idx = cariHewanById(data, id);
			if (idx == -1) {
				cout << "ID tidak ditemukan." << endl;
			} else {
				enqueue(front, rear, data[idx]);
			}
		}

		else if (pilihan == 3) {
			Hewan keluar;
			if (dequeue(front, rear, keluar)) {
				cout << "Dipanggil: " << keluar.nama << endl;

				string tindakan = inputNonKosong("Tindakan: ");
				pushRiwayat(top, keluar, tindakan);
			}
		}

		else if (pilihan == 4) peekAntrian(front);
		else if (pilihan == 5) tampilAntrian(front);
		else if (pilihan == 6) popRiwayat(top);
		else if (pilihan == 7) peekRiwayat(top);
		else if (pilihan == 8) tampilRiwayat(top);

	} while (pilihan != 0);

	return 0;
}