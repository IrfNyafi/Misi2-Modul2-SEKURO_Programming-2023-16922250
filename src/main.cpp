#include "pelanggan.h"
#include "pemilik.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

void keluar(bool flagPenjualan);

struct Menu
{
    std::string Kategori;
    std::string Nama;
    int ID;
    int Harga;
    int Quantity;
};

struct Customer
{
    std::string Nama;
    // std::unordered_map<int, int> pilUser;
};

int main()
{
    bool flagAdaPenjualan = false;
    int pil1 = pemilikTokoStart();

    if (pil1 == 1)
    {
        std::cout << "Masukkan Nama Anda: ";
        Customer pelanggan;
        getline(std::cin, pelanggan.Nama);

        std::cout << "Nama pelanggan adalah " << pelanggan.Nama << std::endl;
    }
    else if (pil1 == 2) // Artinya Toko akan ditutup
    {
        keluar(flagAdaPenjualan);
        // return 0;
    }

    std::unordered_map<std::string, Menu> isiMenu;
    isiMenu["Sushi"] = Menu{"Makanan", "Sushi", 111, 25000, 20};
    isiMenu["Ramen"] = Menu{"Makanan", "Ramen", 121, 30000, 30};
    isiMenu["Yakitori"] = Menu{"Makanan", "Yakitori", 131, 5000, 20};
    isiMenu["Niku"] = Menu{"Makanan", "Niku", 141, 25000, 30};
    isiMenu["Takoyaki"] = Menu{"Makanan", "Takoyaki", 151, 18000, 25};
    isiMenu["Okonomiyaki"] = Menu{"Makanan", "Okonomiyaki", 161, 20000, 14};
    isiMenu["Tonkatsu"] = Menu{"Makanan", "Tonkatsu", 171, 30000, 15};
    isiMenu["Matcha"] = Menu{"Minuman", "Matcha", 211, 14000, 20};
    isiMenu["Water"] = Menu{"Minuman", "Water", 221, 5000, 40};
    isiMenu["Coffee"] = Menu{"Minuman", "Coffee", 231, 10000, 20};

    return 0;
}

// Fitur bagi si pemilik toko

void keluar(bool flagPenjualan)
{
    if (flagPenjualan == false) // Belum ada penjualan jika flagPenjualan false
    {
        std::cout << "Tidak Ada Penjualan :(\n";
    }
}

// class Makanan : public Menu
// {
// };

// class Minuman : public Menu
// {
// };

// Fitur bagi pelanggan

void melihatMenu()
{
}

void memilihMenu()
{
}

void rekapPembelian()
{
}

void pembayaran()
{
}
