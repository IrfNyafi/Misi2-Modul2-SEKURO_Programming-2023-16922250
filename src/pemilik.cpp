#include "pemilik.h"
#include "pelanggan.h"
#include <iostream>
#include <unordered_map>

int pemilikTokoStart()
{
    std::cout << "Selamat datang Kang Roger!\n\n";

    std::cout << "[1] Pelanggan Masuk\n"
              << "[2] menutup Toko\n"
              << "[3] Check Ketersediaan Menu\n"
              << "[4] Mengedit Ketersediaan Menu\n"
              << "Pilih keputusan Anda dengan mengetik ID pilihan: ";

    int keputusan;
    std::cin >> keputusan;
    int pilKeputusan[4] = {1, 2, 3, 4};

    return prosesKeputusan(&keputusan, pilKeputusan, 4);
}


void cleanScreen()
{
#if defined(__linux__) // Or #if __linux__
    std::system("clear");
#elif __APPLE__
    std::system("clear");
#elif _WIN32
    std::system("cls");
#endif
}