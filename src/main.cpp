#include "utils.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main()
{
    std::unordered_map<std::string, Menu> foodMenu;
    foodMenu["Sushi"] = Menu{"Makanan", "Sushi", "111", 25000, 20};
    foodMenu["Ramen"] = Menu{"Makanan", "Ramen", "121", 30000, 30};
    foodMenu["Yakitori"] = Menu{"Makanan", "Yakitori", "131", 5000, 20};
    foodMenu["Niku"] = Menu{"Makanan", "Niku", "141", 25000, 30};
    foodMenu["Takoyaki"] = Menu{"Makanan", "Takoyaki", "151", 18000, 25};
    foodMenu["Okonomiyaki"] = Menu{"Makanan", "Okonomiyaki", "161", 20000, 14};
    foodMenu["Tonkatsu"] = Menu{"Makanan", "Tonkatsu", "171", 30000, 15};

    std::unordered_map<std::string, Menu> drinkMenu;
    drinkMenu["Matcha"] = Menu{"Minuman", "Matcha", "211", 14000, 20};
    drinkMenu["Water"] = Menu{"Minuman", "Water", "221", 5000, 40};
    drinkMenu["Coffee"] = Menu{"Minuman", "Coffee", "231", 10000, 20};

    auto mapMenu = foodMenu;
    mapMenu.insert(drinkMenu.begin(), drinkMenu.end());

    std::vector<Pelanggan> historyPelanggan;

    while (true)
    {
        int pilihan = pemilikTokoStart();
        Pelanggan customer;
        bool flagMembeli = false;

        std::cout << std::endl;
        if (pilihan == 1) // Pelanggan Masuk
        {
            clearScreen();
            std::cout << "Masukkan Nama Anda: ";
            std::cin.ignore();
            getline(std::cin, customer.Nama);

            while (true)
            {
                clearScreen();
                std::cout << "Selamat datang " << customer.Nama << "\n\n";
                int pilUser = pilihanUser();
                if (pilUser == 1) // Melihat menu
                {
                    clearScreen();
                    tampilkanMenu(foodMenu, drinkMenu);
                    std::cin.ignore();

                    std::cout << "Apakah Anda ingin melanjutkan dengan membeli makanan atau minuman? [y/n]: ";
                    char validation;
                    std::cin >> validation;

                    if (validation == 'n' || validation == 'N')
                    {
                        continue;
                    }
                    else if (validation == 'y' || validation == 'Y')
                    {
                        flagMembeli = true;
                        while (true)
                        {
                            std::cout << "\nSilahkan pilih item dengan mengetik ID atau nama item: ";
                            std::string itemChosen;
                            std::cin.ignore();
                            getline(std::cin, itemChosen);

                            int jumlahItem = 0;
                            std::cout << "Jumlah item: ";
                            std::cin >> jumlahItem;

                            bool flagFound = false;
                            auto it = mapMenu.begin();
                            auto itCust = customer.menuPilihan.begin();

                            for (it; it != mapMenu.end(); ++it)
                            {
                                if (it->first == itemChosen || it->second.ID == itemChosen)
                                {
                                    for (itCust; itCust != customer.menuPilihan.end(); ++itCust)
                                    {
                                        if (it->first == itCust->first)
                                        {
                                            customer.menuPilihan[it->first] = itCust->second + jumlahItem;
                                            flagFound = true;
                                        }
                                    }
                                    if (flagFound == false)
                                    {
                                        customer.menuPilihan[it->first] = jumlahItem;
                                    }
                                }
                            }

                            char valid;
                            std::cout << "Apakah Anda ingin menambah item belanja? [y/n]: ";
                            std::cin >> valid;

                            if (valid == 'N' || valid == 'n')
                            {
                                std::cout << "\nSilahkan lakukan pembayaran pada menu keluar!\n"
                                          << "Tekan enter untuk melanjutkan.\n";
                                std::cin.ignore();
                                std::cin.get();

                                break;
                            }
                        }
                    }
                }
                if (pilUser == 2) // Pelanggan mau keluar
                {
                    if (flagMembeli == true)
                    {
                        std::unordered_map<std::string, Menu> hasilStruk;
                        for (auto iter = customer.menuPilihan.begin(); iter != customer.menuPilihan.end(); ++iter)
                        {
                            hasilStruk[iter->first] = mapMenu[iter->first];
                            hasilStruk[iter->first].Stock = iter->second;
                            hasilStruk[iter->first].Harga = iter->second * mapMenu[iter->first].Harga;
                        }

                        customer.summary.insert(hasilStruk.begin(), hasilStruk.end());

                        historyPelanggan.push_back(customer);

                        clearScreen();
                        tampilkanStruk(hasilStruk);
                        std::cin.ignore();
                        std::cout << "Tekan enter untuk melanjutkan.\n";
                        std::cin.get();
                    }

                    break;
                }
            }
        }

        else if (pilihan == 2) // Menutup Toko
        {
            if (historyPelanggan.size() == 0)
            {
                std::cout << "Tidak Ada Penjualan\n";
                return 0;
            }
            else
            {
                int sizeHist = historyPelanggan.size();

                clearScreen();
                std::cin.ignore();

                // for (auto iter = historyPelanggan[0].summary.begin(); iter != historyPelanggan[0].summary.end(); ++iter)
                // {
                //     std::cout << iter->first << ' ' << iter->second.Kategori << std::endl;
                // }

                for (int i = 0; i < sizeHist; ++i)
                {
                    std::cout << "Nama Pelanggan: " << historyPelanggan[i].Nama << '\n';
                    std::unordered_map<std::string, Menu> tempMap;
                    tempMap.insert(historyPelanggan[i].summary.begin(), historyPelanggan[i].summary.end());
                    tampilkanStruk(tempMap);
                    std::cout << '\n';
                }

                for (int i = 0; i < sizeHist; ++i)
                {
                    // std::ofstream ofs{"History-Pelanggan.txt"};
                    // auto cout_buff = std::cout.rdbuf();
                    // std::cout.rdbuf(ofs.rdbuf());

                    std::ofstream ofile("output.txt", std::fstream::app); // output file
                    std::streambuf *oldbuf = std::cout.rdbuf();           // save the buffer
                    std::cout.rdbuf(ofile.rdbuf());                       // redirect to output.txt

                    std::cout << "Nama Pelanggan: " << historyPelanggan[i].Nama << '\n';
                    std::unordered_map<std::string, Menu> tempMap;
                    tempMap.insert(historyPelanggan[i].summary.begin(), historyPelanggan[i].summary.end());
                    tampilkanStruk(tempMap);
                    std::cout << '\n';

                    // std::cout.rdbuf(cout_buff);
                    std::cout.rdbuf(oldbuf);
                }

                std::cout << "History pesanan tersimpan pada output.txt\n";
                return 0;
            }
        }
    }
    return 0;
}