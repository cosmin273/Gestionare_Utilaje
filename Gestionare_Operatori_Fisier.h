#ifndef GESTIONARE_OPERATORI_FISIER_H_INCLUDED
#define GESTIONARE_OPERATORI_FISIER_H_INCLUDED
#include <fstream>
#include <vector>
#include "Operator.h"
std::vector<Operator> citesteOperatoriDinFisier(const std::string& numeFisier)
{
    std::vector<Operator> operatori;

    std::ifstream fisier(numeFisier);
    if (fisier.is_open())
    {
        std::string linie;
        while (std::getline(fisier, linie))
        {
            Operator op(linie);
            operatori.push_back(op);
        }
        fisier.close();
    }

    return operatori;
}
Operator citesteOperatorDeLaTastatura()
{
    std::string nume;
    std::string dataAngajare;
    float hectareLucrate;
    int oreLucrate;
    int salariu;

    std::cout << "Introduceti numele operatorului: ";
    std::cin.ignore();
    std::getline(std::cin, nume);

    std::cout << "Introduceti data angajarii: ";
    std::getline(std::cin, dataAngajare);

    std::cout << "Introduceti numarul de hectare lucrate: ";
    std::cin >> hectareLucrate;

    std::cout << "Introduceti numarul de ore lucrate: ";
    std::cin >> oreLucrate;

    std::cout << "Introduceti salariul: ";
    std::cin >> salariu;

    // Ignoram '\n' ramas in buffer dupa citirea valorii pentru salariu
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Operator op(nume, dataAngajare, hectareLucrate, oreLucrate, salariu);

    return op;
}
void afiseazaOperatori(const std::vector<Operator>& operatori)
{
    for (const auto& op : operatori)
    {
        std::cout << "Nume: " << op.getNume() << std::endl;
        std::cout << "Data angajarii: " << op.getDataAngajare() << std::endl;
        std::cout << "Hectare lucrate: " << op.getHectareLucrate() << std::endl;
        std::cout << "Ore lucrate: " << op.getOreLucrate() << std::endl;
        std::cout << "Salariu: " << op.getSalariu() << std::endl;
        std::cout << "---------------------" << std::endl;
    }
}
void adaugaOperatorInFisier(const Operator& op)
{
    std::ofstream fisier("operatori.txt", std::ios::app);
    if (fisier.is_open())
    {
        fisier << op.getNume() << ";" << op.getDataAngajare() << ";" << op.getHectareLucrate() << ";" << op.getOreLucrate() << ";" << op.getSalariu() << "\n";
        fisier.close();
    }
}
void stergeOperatorDinFisier(const std::string& nume)
{
    std::ifstream fisierIn("operatori.txt");
    if (!fisierIn.is_open())
    {
        std::cout << "Eroare la deschiderea fisierului operatori.txt\n";
        return;
    }

    std::vector<Operator> operatori;

    std::ifstream fisier("operatori.txt");
    if (fisier.is_open())
    {
        std::string linie;
        while (std::getline(fisier, linie))
        {
            Operator op(linie);
            operatori.push_back(op);
        }
        fisier.close();
    }

    // Deschiderea fișierului în modul de scriere (ștergând conținutul anterior)
    std::ofstream fisierOut("operatori.txt", std::ios::trunc);
    if (!fisierOut.is_open())
    {
        std::cout << "Eroare la deschiderea fisierului operatori.txt\n";
        return;
    }

    bool gasit = false;

    // Căutarea operatorului în vector și scrierea în fișier a operatorilor diferiți de cel căutat
    for (const auto& op : operatori)
    {
        if (op.getNume() != nume)
        {
            adaugaOperatorInFisier(op);
        }
        else
        {
            gasit = true;
        }
    }

    fisierOut.close();

    if (gasit)
    {
        std::cout << "Operatorul cu numele " << nume << " a fost sters din fisier.\n";
    }
    else
    {
        std::cout << "Nu s-a gasit niciun operator cu numele " << nume << " in fisier.\n";
    }
}
bool comparareOperatori(const Operator& op1, const Operator& op2)
{
    float raport1 = op1.getHectareLucrate() / static_cast<float>(op1.getOreLucrate());
    float raport2 = op2.getHectareLucrate() / static_cast<float>(op2.getOreLucrate());
    return raport1 < raport2;
}

void sortareOperatori(std::vector<Operator>& operatori)
{
    std::sort(operatori.begin(), operatori.end(), comparareOperatori);
}
#endif // GESTIONARE_OPERATORI_FISIER_H_INCLUDED
