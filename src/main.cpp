#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>

struct Menu
{
    std::string Kategori;
    std::string Nama;
    std::string ID;
    int Harga;
    int Stock;
};

struct Pelanggan
{
    std::string Nama;
    std::unordered_map<std::string, int> menuPilihan;
};

int pemilikTokoStart();
int prosesKeputusan(int *usrInput, int *ptrArr, int sizeArr);
int pilihanUser();
void clearScreen();
void tampilkanMenu(std::unordered_map<std::string, Menu>& menuFood, std::unordered_map<std::string, Menu>& menuDrink);
void tampilkanStruk(std::unordered_map<std::string, Menu>& pilihanBelanja);

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

    while (true)
    {
        int pilihan = pemilikTokoStart();
        bool flagMembeli = false;

        std::cout << std::endl;
        if (pilihan == 1) // Pelanggan Masuk
        {
            clearScreen();
            Pelanggan customer;
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

                        // for (auto iter = customer.menuPilihan.begin(); iter != customer.menuPilihan.end(); ++iter)
                        // {
                        //     std::cout << iter->first << ' ' << iter->second << std::endl;
                        // }
                        // std::cin.ignore();
                        // std::cin.get();
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
    }
    return 0;
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

    std::cout << "\nTotal Transaksi: Rp" << totalTransaksi << "\n";
}

void tampilkanMenu(std::unordered_map<std::string, Menu>& menuFood, std::unordered_map<std::string, Menu>& menuDrink)
{
    std::cout << std::endl;
    std::cout << std::left;
    std::cout << std::setw(10) << "Kategori";
    std::cout << std::setw(5) << "ID";
    std::cout << std::setw(14) << "Nama";
    std::cout << std::setw(8) << "Harga";
    std::cout << std::setw(7) << "Stock";
    std::cout << std::endl;

    for (int i = 0; i < 42; ++i)
        std::cout << '=';
    std::cout << std::endl;

    for (auto& [name, menu] : menuFood)
    {
        std::cout << std::setw(10) << menu.Kategori;
        std::cout << std::setw(5) << menu.ID;
        std::cout << std::setw(14) << name;
        std::cout << std::setw(8) << menu.Harga;
        std::cout << std::setw(7) << menu.Stock;
        std::cout << std::endl;
    }

    std::cout << '\n';
    for (auto& [name, menu] : menuDrink)
    {
        std::cout << std::setw(10) << menu.Kategori;
        std::cout << std::setw(5) << menu.ID;
        std::cout << std::setw(14) << name;
        std::cout << std::setw(8) << menu.Harga;
        std::cout << std::setw(7) << menu.Stock;
        std::cout << std::endl;
    }
}

int pemilikTokoStart()
{
    clearScreen();
    std::cout << "Selamat datang Kang Roger! (view: pemilik toko)\n\n";

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

void melihatMenu()
{
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