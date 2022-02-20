#include <iostream>
#include <chrono>

using namespace std::chrono;

void testuj_tablice(int** tablica, int x, int y) {
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            tablica[i][j] = 42;
        }
    }
    std::cout << "didn't segfault";
}

const int X = 1024*1024*1024; // :)
const int Y = 1024;

int main() {
    std::cout << "miszczyk:\n";
    auto before_miszczyk = steady_clock::now();
    int** tablica_dwuwymiarowa = new int*[X];
    for (int i = 0; i < X; ++i) {
        tablica_dwuwymiarowa[i] = new int[Y];
    }
    auto after_miszczyk = steady_clock::now();


    auto before_miszczyk_delete = steady_clock::now();
    for (int i = 0; i < X; ++i) {
        delete[] tablica_dwuwymiarowa[i];
    }
    delete[] tablica_dwuwymiarowa;
    auto after_miszczyk_delete = steady_clock::now();

    std::cout << "\nja:\n";

    auto before_ja = steady_clock::now();
    int* tablica_dwuwymiarowa_szybciej_tmp = new int[X*Y];
    int** tablica_dwuwymiarowa_szybciej = new int*[X];
    for (int i = 0; i < X; ++i) {
        tablica_dwuwymiarowa_szybciej[i] = &tablica_dwuwymiarowa_szybciej_tmp[i*Y];
    }
    auto after_ja= steady_clock::now();


    auto before_ja_delete = steady_clock::now();
    delete[] tablica_dwuwymiarowa_szybciej_tmp;
    delete[] tablica_dwuwymiarowa_szybciej;
    auto after_ja_delete = steady_clock::now();

    // czas tworzenia tablicy
    auto miszczyk_alloc = duration_cast<milliseconds>(after_miszczyk-before_miszczyk).count();
    auto ja_alloc = duration_cast<milliseconds>(after_ja-before_ja).count();
    // czas usuwania tablicy
    auto miszczyk_delete = duration_cast<milliseconds>(after_miszczyk_delete-before_miszczyk_delete).count();
    auto ja_delete = duration_cast<milliseconds>(after_ja_delete-before_ja_delete).count();

    std::cout <<
              "\nCzasy:\n  Miszczyk: alloc " << miszczyk_alloc << "ms + delete " << miszczyk_delete << "ms = total " << miszczyk_alloc + miszczyk_delete << "ms"
              << "\n  Ja: alloc " << ja_alloc << "ms + delete " << ja_delete << "ms = total " << ja_alloc + ja_delete << "ms";

    return 0;
}