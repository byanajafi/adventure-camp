
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define JUMLAH_PERALATAN 5
#define MAKS_TRANSAKSI 10
#define PANJANG_NAMA 100

char namaPeralatan[JUMLAH_PERALATAN][50] = {
    "Tenda Kapasitas 4 Orang",
    "Sleeping Bag",
    "Kompor Portable",
    "Matras Camping",
    "Lampu Camping"
};

int hargaPeralatan[JUMLAH_PERALATAN] = {
    50000, 15000, 20000, 10000, 12000
};

char namaPenyewa[MAKS_TRANSAKSI][PANJANG_NAMA];
int nomorPeralatan[MAKS_TRANSAKSI];
int jumlahUnit[MAKS_TRANSAKSI];
int lamaSewa[MAKS_TRANSAKSI];
long long totalBayar[MAKS_TRANSAKSI];

int jumlahTransaksi = 0;

void bacaTeks(const char *pesan, char hasil[], int ukuran) {
    printf("%s", pesan);

    if (fgets(hasil, ukuran, stdin) == NULL) {
        hasil[0] = '\0';
        return;
    }

    hasil[strcspn(hasil, "\n")] = '\0';

    if (strlen(hasil) == ukuran - 1 &&
        hasil[strlen(hasil) - 1] != '\0') {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }
}

int bacaAngka(const char *pesan, int minimum, int maksimum) {
    char input[100];
    char *akhir;
    long nilai;

    while (1) {
        bacaTeks(pesan, input, sizeof(input));

        nilai = strtol(input, &akhir, 10);

        while (isspace((unsigned char)*akhir)) {
            akhir++;
        }

        if (input[0] != '\0' &&
            akhir != input &&
            *akhir == '\0' &&
            nilai >= minimum &&
            nilai <= maksimum) {
            return (int)nilai;
        }

        printf("Input tidak valid! Masukkan angka %d-%d.\n",
               minimum, maksimum);
    }
}

void tampilkanPeralatan() {
    printf("\n========================================\n");
    printf("       DAFTAR PERALATAN CAMPING\n");
    printf("========================================\n");
    printf("%-4s %-28s %s\n", "No.", "Nama Peralatan", "Harga/Hari");

    for (int i = 0; i < JUMLAH_PERALATAN; i++) {
        printf("%-4d %-28s Rp%d\n",
               i + 1, namaPeralatan[i], hargaPeralatan[i]);
    }

    printf("========================================\n");
}

int hitungDiskon(int hari) {
    if (hari >= 5) {
        return 15;
    } else if (hari >= 3) {
        return 10;
    } else {
        return 0;
    }
}

void tampilkanStruk(int indeks, long long subtotal,
                    int diskon) {
    long long potongan = subtotal * diskon / 100;

    printf("\n========================================\n");
    printf("           ADVENTURE CAMP\n");
    printf("            STRUK PENYEWAAN\n");
    printf("========================================\n");
    printf("Nama Penyewa   : %s\n", namaPenyewa[indeks]);
    printf("Peralatan      : %s\n",
           namaPeralatan[nomorPeralatan[indeks]]);
    printf("Harga per Hari : Rp%d\n",
           hargaPeralatan[nomorPeralatan[indeks]]);
    printf("Jumlah Unit    : %d\n", jumlahUnit[indeks]);
    printf("Lama Sewa      : %d hari\n", lamaSewa[indeks]);
    printf("----------------------------------------\n");
    printf("Subtotal       : Rp%lld\n", subtotal);
    printf("Diskon (%d%%)   : Rp%lld\n", diskon, potongan);
    printf("----------------------------------------\n");
    printf("TOTAL BAYAR    : Rp%lld\n", totalBayar[indeks]);
    printf("========================================\n");
    printf("Terima kasih telah menggunakan\n");
    printf("layanan Adventure Camp!\n");
}

int prosesPenyewaan() {
    if (jumlahTransaksi >= MAKS_TRANSAKSI) {
        printf("\nKapasitas transaksi sudah penuh!\n");
        printf("Tidak dapat menerima transaksi baru.\n");
        return 0;
    }

    int i = jumlahTransaksi;
    int pilihan, unit, hari, diskon;
    long long subtotal, potongan;
    char nama[PANJANG_NAMA];

    printf("\n========== SEWA PERALATAN ==========\n");

    do {
        bacaTeks("Nama penyewa: ", nama, sizeof(nama));

        if (nama[0] == '\0') {
            printf("Nama tidak boleh kosong!\n");
        }
    } while (nama[0] == '\0');

    tampilkanPeralatan();

    pilihan = bacaAngka("Pilih nomor peralatan [1-5]: ",
                        1, JUMLAH_PERALATAN);

    unit = bacaAngka("Jumlah unit yang disewa: ", 1, 1000000);
    hari = bacaAngka("Lama penyewaan (hari): ", 1, 1000000);

    subtotal = (long long)hargaPeralatan[pilihan - 1]
               * unit * hari;

    diskon = hitungDiskon(hari);
    potongan = subtotal * diskon / 100;

    strcpy(namaPenyewa[i], nama);
    nomorPeralatan[i] = pilihan - 1;
    jumlahUnit[i] = unit;
    lamaSewa[i] = hari;
    totalBayar[i] = subtotal - potongan;

    jumlahTransaksi++;

    tampilkanStruk(i, subtotal, diskon);

    return 1;
}

void tampilkanRiwayat() {
    long long pendapatan = 0;

    printf("\n========================================\n");
    printf("          RIWAYAT TRANSAKSI\n");
    printf("========================================\n");

    if (jumlahTransaksi == 0) {
        printf("Belum ada transaksi penyewaan.\n");
        return;
    }

    printf("%-4s %-20s %-25s %s\n",
           "No.", "Nama", "Peralatan", "Total");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < jumlahTransaksi; i++) {
        printf("%-4d %-20.20s %-25s Rp%lld\n",
               i + 1,
               namaPenyewa[i],
               namaPeralatan[nomorPeralatan[i]],
               totalBayar[i]);

        pendapatan += totalBayar[i];
    }

    printf("---------------------------------------------------------------\n");
    printf("Jumlah Transaksi : %d\n", jumlahTransaksi);
    printf("Total Pendapatan : Rp%lld\n", pendapatan);
    printf("========================================\n");
}

void tampilkanMenu() {
    printf("\n========================================\n");
    printf("           ADVENTURE CAMP\n");
    printf("      SISTEM PENYEWAAN PERALATAN\n");
    printf("========================================\n");
    printf("1. Lihat Daftar Peralatan\n");
    printf("2. Sewa Peralatan\n");
    printf("3. Lihat Riwayat Transaksi\n");
    printf("4. Keluar\n");
    printf("========================================\n");
}

int main() {
    int menu;
    char jawaban[20];

    do {
        tampilkanMenu();
        menu = bacaAngka("Pilih menu [1-4]: ", 1, 4);

        switch (menu) {
            case 1:
                tampilkanPeralatan();
                break;

            case 2:
                if (prosesPenyewaan()) {
                    bacaTeks("\nKembali ke menu utama? (Y/T): ",
                             jawaban, sizeof(jawaban));

                    while (toupper((unsigned char)jawaban[0]) != 'Y' &&
                           toupper((unsigned char)jawaban[0]) != 'T') {
                        bacaTeks("Masukkan Y atau T: ",
                                 jawaban, sizeof(jawaban));
                    }

                    if (toupper((unsigned char)jawaban[0]) == 'T') {
                        menu = 4;
                    }
                }
                break;

            case 3:
                tampilkanRiwayat();
                break;

            case 4:
                printf("\nTerima kasih telah menggunakan "
                       "Adventure Camp!\n");
                break;
        }

    } while (menu != 4);

    return 0;
}
