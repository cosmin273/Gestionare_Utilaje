#include <iostream>
#include <string>
#include "Utilaj.h"
#include "Operator.h"
using namespace std;

#include <iostream>
#include <cstdlib> // Pentru funcția "system"
#include <vector>
#include <algorithm>
#include <fstream>
#include "Gestionare_Fisier_Utilaje.h"
#include "Gestionare_Operatori_Fisier.h"

int main()
{
    int optiune;
    Utilaj u("123","tractor","tractor","rosu","case",234,400,5433);
    Utilaj U;
    Operator O;
    std::vector<Operator> operatori=citesteOperatoriDinFisier("operatori.txt");
    U.citesteUtilajeDinFisier("utilaj.txt");
    std::string numeFisier = "utilaj.txt";
    std::vector<Utilaj> utilaje = U.citesteUtilajeDinFisier(numeFisier);
    //cout<<utilaje[0]<<utilaje[1];


    do
    {
        std::cout << "===== MENIU PRINCIPAL =====" << std::endl;
        std::cout << "1. Gestionare Utilaje" << std::endl;
        std::cout << "2. Gestionare Operatori" << std::endl;
        std::cout << "3. Adaugare Munca Operator" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Introduceti optiunea dorita: ";
        std::cin >> optiune;

        clearConsole();

        switch (optiune)
        {
        case 1:
            // Meniul pentru gestionarea utilajelor
            int optiuneUtilaje;

            do
            {
                std::cout << "===== MENIU GESTIONARE UTILAJE =====" << std::endl;
                std::cout << "1. Adaugare Utilaj" << std::endl;
                std::cout << "2. Afisare utilaje" << std::endl;
                std::cout << "3. Vizualizare utilaje care necesita interventie" << std::endl;
                std::cout << "4. Stergerea unui utilaj" << std::endl;
                std::cout << "5. Cautare utilaj" << std::endl;
                std::cout << "6. Afisare utilaje sortate in functie de numarul de hectare lucrate/numarul de ore" << std::endl;
                std::cout << "7. Resetare numar ore revizie " << std::endl;
                std::cout << "8. Inapoi" << std::endl;
                std::cout << "Introduceti optiunea dorita: ";
                std::cin >> optiuneUtilaje;

                clearConsole();

                switch (optiuneUtilaje)
                {
                case 1:
                {
                    std::cout << "Citire Utilaj" << std::endl;
                    std::cin>>U;
                    std::cout << "Utilajul introdus este: " << std::endl << U;
                    utilaje.push_back(U);
                    U.adaugaUtilajInFisier("utilaj.txt");
                    break;
                }
                case 2:
                {
                    std::cout << "Afisare Utilaje" << std::endl;
                    afiseazaUtilaje(utilaje);
                    break;
                }
                case 3:
                    afiseazaUtilajeCuInterventieMare(utilaje);
                    break;
                case 4:
                {
                    std::string serieCautata;
                    std::cout << "Introduceti seria utilajului pe care doriti sa-l stergeti: ";
                    std::cin >> serieCautata;
                    stergeUtilaj(utilaje,serieCautata,"utilaj.txt");
                    break;
                }
                case 5:
                {
                    string denumire;
                    std::cout << "Introduceti denumirea:" ;
                    std::cin >> denumire;
                    cautaUtilaj(utilaje,denumire);
                    break;
                }
                case 6:
                {

                    std::sort(utilaje.begin(), utilaje.end(), comparareUtilaje);
                    afiseazaUtilaje(utilaje);
                    break;
                }
                case 7:
                    {
                        bool cautat=false;
                        std::string serieCautata;
                        std::cout << "Introduceti seria utilajului carauia doriti sa ii resetati orele de revizie ";
                        std::cin >> serieCautata;
                        for ( auto& utilaj : utilaje)
                            if(utilaj.getSerie()==serieCautata)
                            {
                                cautat =true;
                                utilaj.setOreRevizie(0);
                            }
                        if(cautat == true)
                            std::cout<< "Orele au fost resetate"<<endl;
                        else
                            std::cout<<"Utilajul nu a fost gasit"<<endl;
                        break;
                    }
                case 8:
                    std::cout << "Inapoi la Meniul Principal" << std::endl;
                    break;
                default:
                    std::cout << "Optiune invalida!" << std::endl;
                    break;
                }
            }
            while (optiuneUtilaje != 8);

            break;
        case 2:
            // Meniul pentru gestionarea operatorilor
            int optiuneOperatori;

            do
            {
                std::cout << "===== MENIU GESTIONARE OPERATORI =====" << std::endl;
                std::cout << "1. Adaugare operator" << std::endl;
                std::cout << "2. Afisare operatori" << std::endl;
                std::cout << "3. Sortare operatori in functie de numarul de hectare/numarul de ore" << std::endl;
                std::cout << "4. Stergere operator" << std::endl;
                std::cout << "5. Inapoi" << std::endl;
                std::cout << "Introduceti optiunea dorita: ";
                std::cin >> optiuneOperatori;

                clearConsole();

                switch (optiuneOperatori)
                {
                case 1:
                {
                    O=citesteOperatorDeLaTastatura();
                    operatori.push_back(O);
                    adaugaOperatorInFisier(O);
                    break;
                }
                case 2:
                {
                    afiseazaOperatori(operatori);
                    break;
                }
                case 3:
                    {
                        sortareOperatori(operatori);
                        afiseazaOperatori(operatori);
                    }
                    break;
                case 4:
                    {
                        string nume;
                        std::cout << "Introdu numele operatorului:";
                        std::cin.ignore();
                        std::getline(std::cin, nume);
                        stergeOperatorDinFisier(nume);
                        break;
                    }
                case 5:
                    std::cout << "Inapoi la Meniul Principal" << std::endl;
                    break;
                default:
                    std::cout << "Optiune invalida!" << std::endl;
                    break;
                }
            }
            while (optiuneOperatori != 5);

            break;
        case 3:
            // Meniul pentru adaugarea muncii operatorului
            int optiuneMuncaOperator;

            do
            {
                std::cout << "===== MENIU ADAUGARE MUNCA OPERATOR =====" << std::endl;
                std::cout << "1. Vizualizare utilaje" << std::endl;
                std::cout << "2. Introducere numar de ore si numar de hectare pentru un utilaj" << std::endl;
                std::cout << "3. Cautare utilaj" << std::endl;
                std::cout << "4. Inapoi" << std::endl;
                std::cout << "Introduceti optiunea dorita: ";
                std::cin >> optiuneMuncaOperator;

                clearConsole();

                switch (optiuneMuncaOperator)
                {
                case 1:
                    afiseazaUtilaje(utilaje);
                    break;
                case 2:
                    {
                        string nume;
                        bool cautat=false;
                        std::cout<<"Introduceti numele operatorului";
                        std::cin.ignore();
                        std::getline(std::cin, nume);
                        std::string serieCautata;
                        int ore,hectare;
                        std::cout<<"Introduceti numarul de ore lucrate";
                        std::cin>>ore;
                        std::cout<<"Introduceti numarul de hectare lucrate";
                        std::cin>>hectare;
                        for (auto& op:operatori)
                            if(nume==op.getNume())
                            {
                                op.setHectareLucrate(hectare+op.getHectareLucrate());
                                op.setOreLucrate(ore+op.getOreLucrate());
                                cautat=true;
                            }
                        if(cautat==false)
                            cout<<"operatorul nu a fost gasit";
                        cautat=false;
                        std::cout << "Introduceti seria utilajului cu care ati muncit ";
                        std::cin >> serieCautata;
                        for ( auto& utilaj : utilaje)
                            if(utilaj.getSerie()==serieCautata)
                            {
                                cautat =true;
                                utilaj.setNumarOre(ore+utilaj.getNumarOre());
                                utilaj.setHectare(hectare+utilaj.getHectare());
                            }
                        if(cautat == true)
                            std::cout<< "Datele au fost modificate"<<endl;
                        else
                            std::cout<<"Utilajul nu a fost gasit"<<endl;
                    }
                    break;
                case 3:
                    {
                        cout<<"Introduceti denumirea utilajului cautat ";
                        string nume;
                        std::cin.ignore();
                        std::getline(std::cin, nume);
                        cautaUtilaj(utilaje,nume);
                    }
                    break;
                case 4:
                    std::cout << "Inapoi la Meniul Principal" << std::endl;
                    break;
                default:
                    std::cout << "Optiune invalida!" << std::endl;
                    break;
                }
            }
            while (optiuneMuncaOperator != 4);

            break;
        case 4:
            std::cout << "Programul se incheie. La revedere!" << std::endl;
            break;
        default:
            std::cout << "Optiune invalida!" << std::endl;
            break;
        }

    }
    while (optiune != 4);
    return 0;
}


