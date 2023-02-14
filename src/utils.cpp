#include "utils.h"
#include <iomanip>
#include <iostream>

char prosesPilihan(std::vector<char> range)
{
    char test;
    std::cin >> test;
    bool flagPass = false;

    while (!flagPass)
    {
        for (auto uji : range)
        {
            if (uji == test)
                flagPass = true;
        }
        if (flagPass == false)
        {
            std::cout << "\nInput yang Anda berikan salah! Tolong ketik ID dari pilihan-pilihan yang tersedia\n"
                      << "Pilih ID: ";
            std::cin >> test;
        }
    }
    std::cin.clear();
    std::cin.ignore();
    return test;
}

char pemilikTokoStart()
{
    clearScreen();
    std::cout << "Selamat datang Kang Roger! (view: pemilik toko)\n\n";

    std::cout << "[1] Pelanggan Masuk\n"
              << "[2] menutup Toko\n"
              << "Pilih keputusan Anda dengan mengetik ID pilihan: ";

    return prosesPilihan({'1', '2'});
}

void tampilkanHistoryPelanggan(std::vector<Pelanggan> cust)
{
    std::vector<Menu> tempMenu;
    for (size_t i = 0; i < cust.size(); ++i)
    {
        tempMenu = cust[i].pesananPelanggan;
        std::cout << "Nama Pelanggan: " << cust[i].Nama << '\n';

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
        for (auto& menu : tempMenu)
        {
            std::cout << std::setw(5) << menu.ID
                      << std::setw(14) << menu.Nama
                      << std::setw(8) << menu.Stock
                      << std::setw(9) << menu.Harga
                      << std::endl;

            totalTransaksi += menu.Harga;
        }

        std::cout << "\nTotal Transaksi: Rp" << totalTransaksi << "\n\n";
    }
}

void clearScreen()
{
#if defined(__linux__) // Or #if __linux__
    system("clear");
#elif __APPLE__
    system("clear");
#elif _WIN32
    system("cls");
#endif
}