#pragma once
#include <string>
#include <vector>

struct Menu
{
    std::string Kategori;
    std::string Nama;
    std::string ID;
    int Harga;
    int Stock;
};

struct KelompokMenu
{
    std::vector<std::vector<Menu>> menuMenu;

    void tampilkanMenu();
    void updateStock(std::string barang, int newValue);
    int getStock(std::string barang);
    std::vector<int> search_translation(std::string searchStr);
};

struct Pelanggan
{
    std::string Nama;
    std::vector<Menu> pesananPelanggan;

    void tampilkanStruk();
    void handlePelanggan(KelompokMenu& data);
};

char pemilikTokoStart();
void clearScreen();
char prosesPilihan(std::vector<char> range);
void tampilkanHistoryPelanggan(std::vector<Pelanggan> cust);