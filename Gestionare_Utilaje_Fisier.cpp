#include <iostream>
#include <string>
#include "Utilaj.h"
using namespace std;

#include <iostream>
#include <cstdlib> // Pentru funcția "system"
#include <vector>
#include <algorithm>
#include <fstream>

void clearConsole()
{
#ifdef _WIN32
    std::system("cls");
#else
    // Presupunem că folosim un sistem de operare bazat pe Unix
    std::system("clear");
#endif
}
bool comparareUtilaje(const Utilaj& utilaj1, const Utilaj& utilaj2)
{
    float raport1 = utilaj1.calculeazaRaport();
    float raport2 = utilaj2.calculeazaRaport();
    return raport1 > raport2;
}
void afiseazaUtilaje(const std::vector<Utilaj>& utilaje)
{
    for (const auto& utilaj : utilaje)
    {
        std::cout << utilaj << std::endl;
    }
}
void afiseazaUtilajeCuInterventieMare(const std::vector<Utilaj>& utilaje)
{
    for (const auto& utilaj : utilaje)
    {
        if (utilaj.getOreRevizie() >= 300)
        {
            std::cout << "Utilaj cu nevoie de interventie: " << utilaj << std::endl;
        }
    }
}
void cautaUtilaj(const std::vector<Utilaj>& utilaje, const std::string& denumire)
{
    std::vector<Utilaj> utilajeGasite;

    // Căutare după denumire
    for (const auto& utilaj : utilaje)
    {
        if (utilaj.getDenumire() == denumire)
        {
            utilajeGasite.push_back(utilaj);
        }
    }

    if (utilajeGasite.empty())
    {
        std::cout << "Nu s-au gasit utilaje cu denumirea " << denumire << std::endl;
    }
    else if (utilajeGasite.size() == 1)
    {
        std::cout << "Utilajul gasit: " << utilajeGasite[0].getSerie() << " - " << utilajeGasite[0].getDenumire() << " - " << utilajeGasite[0].getNumarOre() << " - " << utilajeGasite[0].getOreRevizie() << std::endl;
    }
    else
    {
        // Căutare după serie în cazul în care există mai multe utilaje cu aceeași denumire
        std::string serie;
        std::cout << "Exista mai multe utilaje cu denumirea " << denumire << ". Introduceti seria pentru a specifica utilajul dorit: ";
        std::cin >> serie;

        for (const auto& utilaj : utilajeGasite)
        {
            if (utilaj.getSerie() == serie)
            {
                std::cout << "Utilajul gasit: " << utilaj.getSerie() << " - " << utilaj.getDenumire() << utilaj.getNumarOre() << " - " << utilaj.getOreRevizie() << std::endl;
                return;
            }
        }

        std::cout << "Nu s-a gasit un utilaj cu denumirea " << denumire << " si seria " << serie << std::endl;
    }
}
void stergeUtilaj(std::vector<Utilaj>& utilaje, const std::string& serie, const std::string& numeFisier)
{
    // Cauta utilajul in vector
    auto it = std::find_if(utilaje.begin(), utilaje.end(), [&](const Utilaj& utilaj)
    {
        return utilaj.getSerie() == serie;
    });

    if (it != utilaje.end())
    {
        // Sterge utilajul din vector
        utilaje.erase(it);

        // Sterge utilajul din fisier
        std::ofstream file(numeFisier, std::ios::out | std::ios::trunc);
        if (file.is_open())
        {
            for (const auto& utilaj : utilaje)
            {
                file << utilaj.getSerie() << ";" << utilaj.getDenumire() << ";" << utilaj.getCategorie() << ";" << utilaj.getCuloare() << ";"
                     << utilaj.getProducator() << ";" << utilaj.getNumarOre() << ";" << utilaj.getOreRevizie() << ";" << utilaj.getHectare() << "\n";
            }
            file.close();
            std::cout << "Utilajul cu seria " << serie << " a fost sters din vector si din fisierul " << numeFisier << std::endl;
        }
        else
        {
            std::cout << "Eroare la deschiderea fisierului " << numeFisier << std::endl;
        }
    }
    else
    {
        std::cout << "Nu s-a gasit un utilaj cu seria " << serie << std::endl;
    }
}
