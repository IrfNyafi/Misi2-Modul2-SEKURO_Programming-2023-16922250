# Warung Kang Roger

## Detail-Detail Program

## Bagaimana Cara Mengorganisir Data-data yang Berkaitan
Agar data-data dapat dengan mudah diakses dan lebih terorganisir maka penulis membagikan data-data menjadi 3 objek yang ditampung dalam struct.

```cpp
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
```

**Penjelasan:** Dalam satu menu, terdiri atas unsur-unsur, seperti jenis kategori, nama barang, ID barang, harga barang, dan status stock barang (disimpan dalam struct Menu). Kumpulan-kumpulan menu tersebut, kemudian disimpan sebagai sebuah member dari struct KelompokMenu dalam bentuk array atau vector. Kedua struct yang telah disebutkan tersebut akan menjadi gerbang dari interaksi-interaksi berkaitan dengan menu dan propertinya.

Kemudian, struct Pelanggan digunakan untuk menampung informasi-informasi berkaitan dengan para pelanggan dari toko, seperti nama dari pelanggan dan pesanan-pesanan yang dipilih oleh pelanggan.

## Proses Validasi Input
Program yang penulis buat berbasiskan console sehingga input dan output dari program ditampilkan melalui console. Permasalahan yang sering muncul dari memasukkan input melalui console adalah biasanya user salah mengetikan input Permasalahan tersebut, penulis selesaikan dengan memanfaatkan fungsi berikut

```cpp
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
```

## Proses Input Nama Makanan atau ID Makanan
Salah satu fitur yang harus dimiliki oleh program Warung Kang Roger ini adalah meng-input barang hanya dari nama atau ID-nya saja. Proses yang penulis ambil untuk mencapai fitur tersebut adalah dengan men-tranvers setiap element dalam vector. Berikut implementasinya

```cpp
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
```

## Format Output
Dalam menampilkan menu dan struk belanja, format console out dibuat dengan format tabel. Hal tersebut dapat dicapai dengan memanfaatkan library *iomanip*. Berikut adalah implementasinya

```cpp
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
```
## Menambahkan fitur stok
Dengan menggunakan struct untuk mengorganisir data-data yang berkaitan, data stok barang juga menjadi lebih mudah untuk diimplementasikan. Untuk memanipulasi stock barang dengan lebih mudah, penulis membuat sebuah fungsi untuk menangani perubahan nilai dari stok
```cpp
void KelompokMenu::updateStock(std::string barang, int newValue)
{
    if (search_translation(barang)[0] == -1) // barang does not exist -- ERROR
        return;

    int posKategori = search_translation(barang)[0];
    int posSubArr = search_translation(barang)[1];

    menuMenu[posKategori][posSubArr].Stock = newValue;
}
```