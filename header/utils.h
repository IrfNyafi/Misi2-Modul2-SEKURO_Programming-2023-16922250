#pragma once
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
    std::unordered_map<std::string, Menu> summary;
};

int pemilikTokoStart();
int prosesKeputusan(int *usrInput, int *ptrArr, int sizeArr);
int pilihanUser();
void clearScreen();
void tampilkanMenu(std::unordered_map<std::string, Menu>& menuFood, std::unordered_map<std::string, Menu>& menuDrink);
void tampilkanStruk(std::unordered_map<std::string, Menu>& pilihanBelanja);