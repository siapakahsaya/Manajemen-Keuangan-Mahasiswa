Mulai Program
STRUCTURE Transaksi
    STRING jenis     // "Pemasukan" atau "Pengeluaran"
    STRING kategori  // Contoh: "Makanan", "Transportasi", dll.
    STRING deskripsi
    DOUBLE jumlah
    STRING tanggal   // Format: YYYY-MM-DD

FUNGSI isValidDate(tanggal)
    JIKA panjang tanggal TIDAK 10 ATAU tanggal[4] TIDAK '-' ATAU tanggal[7] TIDAK '-'
        KEMBALIKAN false
    KEMBALIKAN true

FUNGSI saveToFile(transaksi, namaFile)
    BUKA file dalam mode tulis
    JIKA file berhasil dibuka
        UNTUK SETIAP t DALAM transaksi
            TULIS data t KE file
        TUTUP file
        CETAK "Data berhasil disimpan ke file."
    LAIN
        CETAK "Gagal membuka file untuk menyimpan data."
    END JIKA

FUNGSI loadFromFile(transaksi, namaFile)
    BUKA file dalam mode baca
    JIKA file berhasil dibuka
        UNTUK SETIAP baris DALAM file
            PARSE baris menjadi Transaksi t
            TAMBAHKAN t KE transaksi
        TUTUP file
        CETAK "Data berhasil dimuat dari file."
    LAIN
        CETAK "File tidak ditemukan, memulai dengan data kosong."
    END JIKA

FUNGSI tambahTransaksi(transaksi, jenis)
    BUAT Transaksi t
    SET t.jenis = jenis

    INPUT tanggal UNTUK t.tanggal
    JIKA isValidDate(t.tanggal) == false
        CETAK "Format tanggal tidak valid."
        KEMBALI

    INPUT kategori UNTUK t.kategori
    INPUT deskripsi UNTUK t.deskripsi
    INPUT jumlah UNTUK t.jumlah
    JIKA jumlah <= 0
        CETAK "Jumlah harus lebih besar dari 0."
        KEMBALI

    TAMBAHKAN t KE transaksi
    CETAK jenis + " berhasil ditambahkan!"

FUNGSI hitungTotal(transaksi)
    SET totalPemasukan = 0
    SET totalPengeluaran = 0
    UNTUK SETIAP t DALAM transaksi
        JIKA t.jenis == "Pemasukan"
            totalPemasukan += t.jumlah
        JIKA t.jenis == "Pengeluaran"
            totalPengeluaran += t.jumlah
    CETAK "Total Pemasukan: Rp", totalPemasukan
    CETAK "Total Pengeluaran: Rp", totalPengeluaran
    CETAK "Saldo Akhir: Rp", totalPemasukan - totalPengeluaran

FUNGSI tampilkanMenu()
    CETAK "=== Aplikasi Manajemen Keuangan ==="
    CETAK "1. Tambah Pemasukan"
    CETAK "2. Tambah Pengeluaran"
    CETAK "3. Lihat Total Keuangan"
    CETAK "4. Simpan Data ke File"
    CETAK "5. Keluar"
    CETAK "Pilih menu:"

PROGRAM UTAMA
    BUAT daftar transaksi kosong
    SET namaFile = "keuangan.txt"
    PANGGIL loadFromFile(transaksi, namaFile)

    ULANGI
        PANGGIL tampilkanMenu()
        INPUT pilihan

        SWITCH pilihan
            KASUS 1:
                PANGGIL tambahTransaksi(transaksi, "Pemasukan")
            KASUS 2:
                PANGGIL tambahTransaksi(transaksi, "Pengeluaran")
            KASUS 3:
                PANGGIL hitungTotal(transaksi)
            KASUS 4:
                PANGGIL saveToFile(transaksi, namaFile)
            KASUS 5:
                CETAK "Terima kasih telah menggunakan aplikasi ini!"
            DEFAULT:
                CETAK "Pilihan tidak valid."
        END SWITCH
    SAMPAI pilihan == 5
END PROGRAM
