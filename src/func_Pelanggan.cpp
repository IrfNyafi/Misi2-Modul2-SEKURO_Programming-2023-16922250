#include "utils.h"
#include <iomanip>
#include <iostream>

void Pelanggan::tampilkanStruk()
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
    for (auto& menu : pesananPelanggan)
    {
        std::cout << std::setw(5) << menu.ID
                  << std::setw(14) << menu.Nama
                  << std::setw(8) << menu.Stock
                  << std::setw(9) << menu.Harga
                  << std::endl;

        totalTransaksi += menu.Harga;
    }

    std::cout << "\nTotal Transaksi: Rp" << totalTransaksi << '\n';
}

void Pelanggan::handlePelanggan(KelompokMenu& data)
{
    while (true)
    {
        std::cout << "Selamat datang " << Nama << std::endl;

        std::cout << "[1] Melihat Menu atau Membeli Makanan/Minuman\n"
                  << "[2] Keluar dari Warung\n"
                  << "Pilih keputusan Anda dengan mengetik ID pilihan: ";

        char keputusan = prosesPilihan({'1', '2'});

        if (keputusan == '1')
        {
            clearScreen();
            if (pesananPelanggan.size() != 0)
            {
                std::cout << "Keranjang Pesanan\n";
                tampilkanStruk();
                std::cout << "\n\n";
            }

            data.tampilkanMenu();

            std::cout << "Apakah Anda ingin melanjutkan dengan membeli makanan atau minuman? [y/n]: ";
            char validation = prosesPilihan({'y', 'Y', 'n', 'N'});

            if (validation == 'y' || validation == 'Y')
            {
                char valid = 'n';
                do
                {
                    std::cout << "\nSilahkan pilih item dengan mengetik ID atau nama item: ";
                    std::string menuTerpilih;
                    getline(std::cin, menuTerpilih);

                    std::vector<int> loc = data.search_translation(menuTerpilih);
                    while (loc[0] == -1)
                    {
                        std::cout << "Input yang Anda berikan salah!\n";
                        std::cout << "\nSilahkan pilih item dengan mengetik ID atau nama item yang sesuai dengan menu: ";
                        getline(std::cin, menuTerpilih);
                        loc = data.search_translation(menuTerpilih);
                    }

                    auto temp_menu = data.menuMenu[loc[0]][loc[1]];

                    int jumlahItem;
                    bool flagBarangTakSiap = false;
                    std::cout << "Jumlah item: ";
                    std::cin >> jumlahItem;

                    while (temp_menu.Stock - jumlahItem < 0)
                    {
                        // std::cout << "Mohon maaf, stock barang tidak cukup\n";
                        if (temp_menu.Stock == 0)
                        {
                            std::cout << "Mohon maaf, stock barang tidak tersedia. "
                                      << "Silahkan pilih menu yang lain\n\n";
                            flagBarangTakSiap = true;
                            break;
                        }
                        else
                        {
                            std::cout << "Mohon maaf, stock barang tidak cukup. "
                                      << "Tolong masukkan jumlah yang tersedia!\n\n";
                            std::cout << "Jumlah item: ";
                            std::cin >> jumlahItem;
                        }
                    }

                    if (!flagBarangTakSiap)
                    {
                        data.updateStock(temp_menu.Nama, temp_menu.Stock - jumlahItem);
                        temp_menu.Stock = jumlahItem;
                        pesananPelanggan.push_back(temp_menu);
                    }

                    std::cout << "Apakah Anda ingin memesan menu yang lain? [y/n]: ";
                    valid = prosesPilihan({'y', 'Y', 'n', 'N'});

                    if (valid == 'y' || valid == 'Y')
                    {
                        clearScreen();

                        std::cout << "Keranjang Pesanan\n";
                        tampilkanStruk();
                        std::cout << "\n\n";

                        data.tampilkanMenu();
                    }

                } while (valid == 'y' || valid == 'Y');
            }
            if (pesananPelanggan.size() != 0)
            {
                std::cout << "\nSilahkan lakukan pembayaran pada menu keluar!\n"
                          << "Tekan enter untuk melanjutkan.\n";
                std::cin.get();
            }
            clearScreen();
        }
        else if (keputusan == '2')
        {
            clearScreen();
            return;
        }
    }
}