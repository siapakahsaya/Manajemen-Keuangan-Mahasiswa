#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <iomanip> // Untuk manipulasi format angka

using namespace std;

struct Transaction {
    string type;      // "Pemasukan" atau "Pengeluaran"
    string category;  // Kategori (Makanan, Transportasi, dll.)
    string description;
    double amount;
    string date;      // Format: YYYY-MM-DD
};

// Fungsi untuk validasi tanggal
bool isValidDate(const string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }
    return true; // Validasi sederhana, bisa ditingkatkan.
}

// Fungsi untuk menyimpan data ke file
void saveToFile(const vector<Transaction>& transactions, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& t : transactions) {
            file << t.type << "|" << t.category << "|" << t.description << "|"
                 << t.amount << "|" << t.date << "\n";
        }
        file.close();
        cout << "Data berhasil disimpan ke file.\n";
    } else {
        cout << "Gagal membuka file untuk menyimpan data.\n";
    }
}

// Fungsi untuk memuat data dari file
void loadFromFile(vector<Transaction>& transactions, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Transaction t;
            size_t pos = 0;
            pos = line.find('|'); t.type = line.substr(0, pos); line.erase(0, pos + 1);
            pos = line.find('|'); t.category = line.substr(0, pos); line.erase(0, pos + 1);
            pos = line.find('|'); t.description = line.substr(0, pos); line.erase(0, pos + 1);
            pos = line.find('|'); t.amount = stod(line.substr(0, pos)); line.erase(0, pos + 1);
            t.date = line;
            transactions.push_back(t);
        }
        file.close();
        cout << "Data berhasil dimuat dari file.\n";
    } else {
        cout << "File tidak ditemukan, memulai dengan data kosong.\n";
    }
}

// Fungsi untuk menambah transaksi
void addTransaction(vector<Transaction>& transactions, const string& type) {
    Transaction t;
    t.type = type;
    string cancel;

    cout << "Masukkan tanggal (YYYY-MM-DD) (atau ketik 'cancel' untuk batal): ";
    cin >> t.date;
    if (t.date == "cancel") {
        cout << "Input dibatalkan.\n";
        return;
    }
    if (!isValidDate(t.date)) {
        cout << "Format tanggal tidak valid. Silakan ulangi.\n";
        return;
    }

    cout << "Masukkan kategori (Makanan/Transportasi/Hiburan/Lainnya) (atau ketik 'cancel' untuk batal): ";
    cin >> t.category;
    if (t.category == "cancel") {
        cout << "Input dibatalkan.\n";
        return;
    }

    cout << "Masukkan deskripsi (atau ketik 'cancel' untuk batal): ";
    cin.ignore();
    getline(cin, t.description);
    if (t.description == "cancel") {
        cout << "Input dibatalkan.\n";
        return;
    }

    cout << "Masukkan jumlah (atau ketik 'cancel' untuk batal): Rp ";
    cin >> cancel;
    if (cancel == "cancel") {
        cout << "Input dibatalkan.\n";
        return;
    }
    try {
        t.amount = stod(cancel);
        if (t.amount <= 0) throw invalid_argument("Jumlah harus lebih besar dari 0.");
    } catch (...) {
        cout << "Jumlah tidak valid. Silakan ulangi.\n";
        return;
    }

    transactions.push_back(t);
    cout << type << " berhasil ditambahkan!\n";
}

// Fungsi untuk menghitung total pemasukan dan pengeluaran
void calculateTotals(const vector<Transaction>& transactions) {
    double totalIncome = 0, totalExpense = 0;
    for (const auto& t : transactions) {
        if (t.type == "Pemasukan") {
            totalIncome += t.amount;
        } else if (t.type == "Pengeluaran") {
            totalExpense += t.amount;
        }
    }
    cout << fixed << setprecision(2); // Format angka tidak menggunakan notasi ilmiah
    cout << "\n=== Total Keuangan ===\n";
    cout << "Total Pemasukan: Rp " << totalIncome << endl;
    cout << "Total Pengeluaran: Rp " << totalExpense << endl;
    cout << "Saldo Akhir: Rp " << totalIncome - totalExpense << endl;
}

// Fungsi untuk menampilkan menu
void displayMenu() {
    cout << "\n=== Aplikasi Manajemen Keuangan Pribadi ===\n";
    cout << "1. Tambah Pemasukan\n";
    cout << "2. Tambah Pengeluaran\n";
    cout << "3. Lihat Total Keuangan\n";
    cout << "4. Simpan Data ke File\n";
    cout << "5. Keluar\n";
    cout << "Pilih menu: ";
}

int main() {
    vector<Transaction> transactions;
    string filename = "keuangan.txt";

    // Memuat data dari file
    loadFromFile(transactions, filename);

    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            addTransaction(transactions, "Pemasukan");
            break;
        case 2:
            addTransaction(transactions, "Pengeluaran");
            break;
        case 3:
            calculateTotals(transactions);
            break;
        case 4:
            saveToFile(transactions, filename);
            break;
        case 5:
            cout << "Terima kasih telah menggunakan aplikasi ini!\n";
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (choice != 5);

    return 0;
}
