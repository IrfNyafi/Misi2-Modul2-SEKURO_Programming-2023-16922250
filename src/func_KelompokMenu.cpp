#include "utils.h"
#include <iomanip>
#include <iostream>
#include <vector>

// Menampilkan daftar manu
void KelompokMenu::tampilkanMenu()
{
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

    int count = 1;
    for (auto& row : menuMenu)
    {
        for (auto& col : row)
        {
            std::cout << std::setw(10) << col.Kategori
                      << std::setw(5) << col.ID
                      << std::setw(14) << col.Nama
                      << std::setw(8) << col.Harga
                      << std::setw(7) << col.Stock
                      << '\n';
            if (count == 7)
                std::cout << '\n';
            count++;
        }
    }
}

// return position of searchStr in menuMenu vector
std::vector<int> KelompokMenu::search_translation(std::string searchStr)
{
    for (size_t i = 0; i < menuMenu.size(); ++i)
    {
        for (size_t k = 0; k < menuMenu[0].size(); ++k)
        {
            if (menuMenu[i][k].Nama == searchStr || menuMenu[i][k].ID == searchStr)
            {
                return {static_cast<int>(i), static_cast<int>(k)};
            }
        }
    }
    return {-1, -1};
}

void KelompokMenu::updateStock(std::string barang, int newValue)
{
    if (search_translation(barang)[0] == -1) // barang does not exist -- ERROR
        return;

    int posKategori = search_translation(barang)[0];
    int posSubArr = search_translation(barang)[1];

    menuMenu[posKategori][posSubArr].Stock = newValue;
}

int KelompokMenu::getStock(std::string barang)
{
    if (search_translation(barang)[0] == -1) // barang does not exist -- ERROR
        return -1;

    int posKategori = search_translation(barang)[0];
    int posSubArr = search_translation(barang)[1];

    return menuMenu[posKategori][posSubArr].Stock;
}