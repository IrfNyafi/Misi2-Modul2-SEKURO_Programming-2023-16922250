#include "utils.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <unordered_map>

int pemilikTokoStart()
{
    clearScreen();
    std::cout << "Selamat datang Kang Roger! (view: pemilik toko)\n\n";

    std::cout << "[1] Pelanggan Masuk\n"
              << "[2] menutup Toko\n"
              << "Pilih keputusan Anda dengan mengetik ID pilihan: ";

    int keputusan;
    std::cin >> keputusan;
    int pilKeputusan[2] = {1, 2};

    return prosesKeputusan(&keputusan, pilKeputusan, 2);
}

void tampilkanStruk(std::unordered_map<std::string, Menu>& pilihanBelanja)
{
    std::cout << std::left;
    std::cout << std::setw(5) << "ID";
    std::cout << std::setw(14) << "Nama";
    std::cout << std::setw(8) << "Jumlah";
    std::cout << std::setw(9) << "Harga";
    std::cout << '\n';

    for (int i = 0; i < 35; ++i)
    {
        std::cout << "=";
    }
    std::cout << '\n';

    int totalTransaksi = 0;
    for (auto& [name, menu] : pilihanBelanja)
    {
        std::cout << std::setw(5) << menu.ID
                  << std::setw(14) << name
                  << std::setw(8) << menu.Stock
                  << std::setw(9) << menu.Harga
                  << std::endl;

        totalTransaksi += menu.Harga;
    }

    std::cout << "\nTotal Transaksi: Rp" << totalTransaksi << '\n';
}

void tampilkanMenu(std::unordered_map<std::string, Menu>& menuFood, std::unordered_map<std::string, Menu>& menuDrink)
{
    std::cout << std::left;
    std::cout << std::setw(10) << "Kategori";
    std::cout << std::setw(5) << "ID";
    std::cout << std::setw(14) << "Nama";
    std::cout << std::setw(8) << "Harga";
    // std::cout << std::setw(7) << "Stock";
    std::cout << std::endl;

    for (int i = 0; i < 35; ++i)
        std::cout << '=';
    std::cout << std::endl;

    for (auto& [name, menu] : menuFood)
    {
        std::cout << std::setw(10) << menu.Kategori;
        std::cout << std::setw(5) << menu.ID;
        std::cout << std::setw(14) << name;
        std::cout << std::setw(8) << menu.Harga;
        // std::cout << std::setw(7) << menu.Stock;
        std::cout << std::endl;
    }

    std::cout << '\n';
    for (auto& [name, menu] : menuDrink)
    {
        std::cout << std::setw(10) << menu.Kategori;
        std::cout << std::setw(5) << menu.ID;
        std::cout << std::setw(14) << name;
        std::cout << std::setw(8) << menu.Harga;
        // std::cout << std::setw(7) << menu.Stock;
        std::cout << std::endl;
    }
}

int pilihanUser()
{
    std::cout << "[1] Melihat Menu atau Membeli Makanan/Minuman\n"
              << "[2] Keluar dari Warung\n"
              << "Pilih keputusan Anda dengan mengetik ID pilihan: ";

    int keputusan;
    std::cin >> keputusan;
    int pilKeputusan[2] = {1, 2};

    return prosesKeputusan(&keputusan, pilKeputusan, 2);
}

// Memvalidasi jawaban user -> Akan mengiterasi input user sampai pilihan user benar
int prosesKeputusan(int *usrInput, int *ptrArr, int sizeArr)
{
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore();
        *usrInput = -1;
    }

    bool salahInput = false;

    for (int i = 0; i < sizeArr; ++i)
    {
        if (*usrInput == *(ptrArr + i))
        {
            salahInput = true;
        }
    }

    if (salahInput)
    {
        return *usrInput;
    }
    else
    {
        std::cout << "\nInput yang Anda berikan salah! Tolong ketik ID dari pilihan-pilihan yang tersedia, yaitu ";
        bool flagTunggal = true;
        for (int i = 0; i < sizeArr - 1; ++i)
        {
            std::cout << *(ptrArr + i) << ", ";
            flagTunggal = false;
        }
        if (flagTunggal)
        {
            std::cout << *(ptrArr + sizeArr - 1) << ".\n\n";
        }
        else
        {
            std::cout << "dan " << *(ptrArr + sizeArr - 1) << ".\n\n";
        }

        int newUsrInput;
        std::cout << "Pilih ID: ";
        std::cin >> newUsrInput;

        return prosesKeputusan(&newUsrInput, ptrArr, sizeArr);
    }
}

void clearScreen()
{
#if defined(__linux__) // Or #if __linux__
    system("clear");
#elif __APPLE__
    system("cls");
#elif _WIN32
    system("cls");
#endif
}