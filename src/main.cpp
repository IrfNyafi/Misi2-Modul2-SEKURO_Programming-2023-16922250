#include "utils.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main()
{
    std::vector<Pelanggan> historyPelanggan;

    std::vector<Menu> barangMakanan{
        {"Makanan", "Sushi", "111", 25000, 20},
        {"Makanan", "Ramen", "121", 30000, 30},
        {"Makanan", "Yakitori", "131", 5000, 20},
        {"Makanan", "Niku", "141", 25000, 30},
        {"Makanan", "Takoyaki", "151", 18000, 25},
        {"Makanan", "Okonomiyaki", "161", 20000, 14},
        {"Makanan", "Tonkatsu", "171", 30000, 15}};

    std::vector<Menu> barangMinuman{
        {"Minuman", "Matcha", "211", 14000, 20},
        {"Minuman", "Water", "221", 5000, 40},
        {"Minuman", "Coffee", "231", 10000, 20}};

    KelompokMenu item;

    item.menuMenu.push_back(barangMakanan);
    item.menuMenu.push_back(barangMinuman);

    while (true)
    {
        Pelanggan customer;
        char pilihan = pemilikTokoStart();
        if (pilihan == '1') // Pelanggan Masuk
        {
            clearScreen();
            std::cout << "Masukkan Nama Anda: ";
            getline(std::cin, customer.Nama);
            std::cout << '\n';

            customer.handlePelanggan(item);
            historyPelanggan.push_back(customer);

            if (customer.pesananPelanggan.size() != 0)
            {
                customer.tampilkanStruk();
                std::cout << "Tekan enter untuk melanjutkan.\n";
                std::cin.get();
            }
        }
        else if (pilihan == '2')
        {
            if (historyPelanggan.size() == 0)
            {
                std::cout << "Tidak Ada Penjualan\n";
                return 0;
            }
            else
            {
                clearScreen();
                tampilkanHistoryPelanggan(historyPelanggan);

                std::ofstream ofile("output.txt", std::fstream::app); // output file
                std::streambuf *oldbuf = std::cout.rdbuf();           // save the buffer
                std::cout.rdbuf(ofile.rdbuf());                       // redirect to output.txt

                tampilkanHistoryPelanggan(historyPelanggan);

                std::cout.rdbuf(oldbuf);
                std::cout << "History pesanan tersimpan pada output.txt\n";
                return 0;
            }
        }
    }

    return 0;
}