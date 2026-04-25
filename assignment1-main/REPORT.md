# Laporan Programming Assignment 1: Basic C++

**Nama:** Adam Naufal Putra  
**NRP:** 5024251099
**Departemen:** Teknik Komputer  

---

## 1. Deskripsi Tugas
Tugas ini bertujuan untuk mengimplementasikan penggunaan pustaka `<ctime>` dan manipulasi `struct tm` dalam bahasa C++. Program diminta untuk menerima input tanggal lahir dalam format `DD/MM/YYYY` dan menghasilkan output berupa:
1.  Umur dalam satuan tahun.
2.  Total akumulasi umur dalam satuan bulan.
3.  Nama hari pada tanggal lahir tersebut.

---

## 2. Penjelasan Logika Program

### A. Fungsi `yearsOld`
Menghitung selisih antara tahun sekarang (`currentTgl->tm_year`) dengan tahun lahir (`inputTgl->tm_year`). Logika tambahan diterapkan untuk mengecek apakah pada tahun berjalan, pengguna sudah melewati hari ulang tahunnya atau belum. Jika bulan/hari saat ini belum mencapai tanggal lahir, maka hasil tahun dikurangi 1.

### B. Fungsi `monthsOld`
Menghitung total bulan dengan rumus:  
$$(TahunSelisih \times 12) + (BulanSelisih)$$
Sama seperti logika tahun, jika tanggal hari ini (`mday`) belum mencapai tanggal lahir di bulan yang sama, maka total akumulasi bulan dikurangi 1 agar hasilnya akurat secara kalender.

### C. Fungsi `dayOfDate`
Menggunakan fungsi `mktime(inputTgl)` untuk melakukan normalisasi pada data waktu. Fungsi ini secara otomatis mengisi *field* `tm_wday` yang merepresentasikan indeks hari (0 untuk Minggu, 1 untuk Senin, dst). Indeks tersebut kemudian dipetakan ke dalam *array* string untuk mendapatkan nama hari dalam Bahasa Indonesia.

---

## 3. Implementasi Kode
Berikut adalah cuplikan fungsi utama yang dikerjakan:

```cpp
int yearsOld(tm* inputTgl, tm* currentTgl) {
    int age = currentTgl->tm_year - inputTgl->tm_year;
    if (currentTgl->tm_mon < inputTgl->tm_mon || 
       (currentTgl->tm_mon == inputTgl->tm_mon && currentTgl->tm_mday < inputTgl->tm_mday)) {
        age--;
    }
    return age;
}

int monthsOld(tm* inputTgl, tm* currentTgl) {
    int totalMonths = (currentTgl->tm_year - inputTgl->tm_year) * 12 + (currentTgl->tm_mon - inputTgl->tm_mon);
    if (currentTgl->tm_mday < inputTgl->tm_mday) {
        totalMonths--;
    }
    return totalMonths;
}

string dayOfDate(tm* inputTgl) {
    mktime(inputTgl); 
    string days[] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
    return days[inputTgl->tm_wday];
}
```

---

## 4. Hasil Uji Coba (Testing)
Program dikompilasi menggunakan `g++` dan diuji dengan beberapa skenario input:

| Input (Tanggal Lahir) | Output (Tahun Bulan Hari) | Keterangan |
| :--- | :--- | :--- |
| `17/08/1945` | `80 968 Jumat` | Uji coba tanggal sejarah |
| `25/01/2007` | `19 231 Kamis` | Sesuai waktu sistem saat ini |

---

## 5. Kesimpulan
Program telah berhasil memenuhi kriteria *autograding* dengan menerapkan manipulasi *struct* waktu. Penggunaan `mktime` terbukti sangat efektif untuk menentukan hari tanpa harus menghitung algoritma kalender secara manual.