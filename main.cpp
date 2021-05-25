#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

struct Adresat {
    int id;
    string imie, nazwisko, numerTelefonu, email, adres;
};

int wyszukajZnakRozdzialu(string liniaZDanymiAdresata) {
    const int znakRozdzialu=124;
    int pozycjaZnaku=0;
    int dlugoscDanych=liniaZDanymiAdresata.length();
    for(int i=0; i<dlugoscDanych; i++) {
        if(liniaZDanymiAdresata[i]==znakRozdzialu) {
            pozycjaZnaku=i;
            break;
        }
    }
    return pozycjaZnaku;
}

void wczytajDaneZPliku(vector <Adresat> &adresaci) {
    fstream plik;

    plik.open("Dane.txt",ios::in);
    if(plik.good()==false) {
        cout<<"Brak Pliku z Danymi;";
    } else {
        string liniaZDanymiAdresata;
        int pozycjaZnakuRozdzialu;
        int i=0;
        string tymczasoweId="";

        while(getline(plik,liniaZDanymiAdresata)) {
            adresaci.push_back({});

            pozycjaZnakuRozdzialu=wyszukajZnakRozdzialu(liniaZDanymiAdresata);
            tymczasoweId.insert(0,liniaZDanymiAdresata,0,pozycjaZnakuRozdzialu);
            liniaZDanymiAdresata.erase(0,pozycjaZnakuRozdzialu+1);
            adresaci[i].id=stoi(tymczasoweId);
            tymczasoweId="";

            pozycjaZnakuRozdzialu=wyszukajZnakRozdzialu(liniaZDanymiAdresata);
            adresaci[i].imie.insert(0,liniaZDanymiAdresata,0,pozycjaZnakuRozdzialu);
            liniaZDanymiAdresata.erase(0,pozycjaZnakuRozdzialu+1);

            pozycjaZnakuRozdzialu=wyszukajZnakRozdzialu(liniaZDanymiAdresata);
            adresaci[i].nazwisko.insert(0,liniaZDanymiAdresata,0,pozycjaZnakuRozdzialu);
            liniaZDanymiAdresata.erase(0,pozycjaZnakuRozdzialu+1);

            pozycjaZnakuRozdzialu=wyszukajZnakRozdzialu(liniaZDanymiAdresata);
            adresaci[i].numerTelefonu.insert(0,liniaZDanymiAdresata,0,pozycjaZnakuRozdzialu);
            liniaZDanymiAdresata.erase(0,pozycjaZnakuRozdzialu+1);

            pozycjaZnakuRozdzialu=wyszukajZnakRozdzialu(liniaZDanymiAdresata);
            adresaci[i].email.insert(0,liniaZDanymiAdresata,0,pozycjaZnakuRozdzialu);
            liniaZDanymiAdresata.erase(0,pozycjaZnakuRozdzialu+1);

            pozycjaZnakuRozdzialu=wyszukajZnakRozdzialu(liniaZDanymiAdresata);
            adresaci[i].adres.insert(0,liniaZDanymiAdresata,0,pozycjaZnakuRozdzialu);
            liniaZDanymiAdresata.erase(0,pozycjaZnakuRozdzialu+1);

            i++;
        }
    }
    plik.close();
}

////////////////////////////////////

void zapiszDane(vector<Adresat> &adresaci) {
    fstream plik;
    plik.open("Dane.txt", ios::out);

    for(vector<Adresat>::iterator itr=adresaci.begin(); itr<adresaci.end(); itr++) {
        plik<<(*itr).id            <<"|";
        plik<<(*itr).imie          <<"|";
        plik<<(*itr).nazwisko      <<"|";
        plik<<(*itr).numerTelefonu <<"|";
        plik<<(*itr).email         <<"|";
        plik<<(*itr).adres         <<"|"<<endl;
    }
    plik.close();
}
////////////////////////////////////

void dodajAdresata(vector <Adresat> &adresaci) {

    adresaci.push_back({});
    int noweId;
////////////////////////////////////////////////////////
    int pozycjaOstatniegoWpisu;
    if(adresaci.size()==1)
        noweId=adresaci[adresaci.size()-1].id + 1;
    else
        noweId=adresaci[adresaci.size()-2].id + 1;
////////////////////////////////////////////////////////
    pozycjaOstatniegoWpisu=adresaci.size()-1;



    cout << "Dodaj Adresata" << endl;
    adresaci[pozycjaOstatniegoWpisu].id=noweId;
    cout<< "Podaj Imie: ";
    cin.ignore();
    getline(cin, adresaci[pozycjaOstatniegoWpisu].imie);
    cout<< "Podaj Nazwisko: ";
    getline(cin,adresaci[pozycjaOstatniegoWpisu].nazwisko);
    cout<< "Podaj Numer Telefonu: ";
    getline(cin, adresaci[pozycjaOstatniegoWpisu].numerTelefonu);
    cout<< "Podaj email: ";
    getline(cin,adresaci[pozycjaOstatniegoWpisu].email);
    cout<< "Podaj Adres: ";
    getline(cin,adresaci[pozycjaOstatniegoWpisu].adres);

////////////////////////////////////

    zapiszDane(adresaci);

////////////////////////////////////

}

void wyszukajPoImieniuLubNazwisku(vector <Adresat> &adresaci, string wyborImieLubNazwisko) {

    string wyszukiwane;
    int czyIstniejeTakiAdresat=0;
    int calkowitaLiczbaPozycji=adresaci.size();

    if(wyborImieLubNazwisko=="imie")
        cout<<endl<< "Podaj Imie Do Wyszukania: ";
    else
        cout<<endl<< "Podaj Nazwisko Do Wyszukania: ";

    cin>>wyszukiwane;

    for(int i = 0; i<calkowitaLiczbaPozycji; i++)
        if((adresaci[i].imie==wyszukiwane && wyborImieLubNazwisko=="imie") || (adresaci[i].nazwisko==wyszukiwane && wyborImieLubNazwisko=="nazwisko" )) {
            cout<< "Id: "               << adresaci[i].id               <<endl;
            cout<< "Imie: "             << adresaci[i].imie             <<endl;
            cout<< "Nazwisko: "         << adresaci[i].nazwisko         <<endl;
            cout<< "Numer Telefonu: "   << adresaci[i].numerTelefonu    <<endl;
            cout<< "email: "            << adresaci[i].email            <<endl;
            cout<< "Adres: "            << adresaci[i].adres            <<endl<<endl;
            czyIstniejeTakiAdresat=1;
        }
    if(czyIstniejeTakiAdresat==0)
        cout<<"Taki Adresat Nie Wystepuje w bazie. Sprobuj Ponownie";
}

void wyswietlWszystkichAdresatow(vector <Adresat> &adresaci) {
    cout << "Wyswietl Wszystkich Adresatow" << endl;
    int liczbaAdresatow=adresaci.size();
    for(int i = 0 ; i<liczbaAdresatow ; i++) {
        cout<< "Id: "               << adresaci[i].id               <<endl;
        cout<< "Imie: "             << adresaci[i].imie             <<endl;
        cout<< "Nazwisko: "         << adresaci[i].nazwisko         <<endl;
        cout<< "Numer Telefonu: "   << adresaci[i].numerTelefonu    <<endl;
        cout<< "email: "            << adresaci[i].email            <<endl;
        cout<< "Adres: "            << adresaci[i].adres            <<endl<<endl;
    }
}

void usunAdresata(vector <Adresat> &adresaci) {
    int idDoUsuniecia;
    char wyborTN;

    wyswietlWszystkichAdresatow(adresaci);
    cout << "Podaj id adresata, ktory ma zostac usuniety" << endl;
    cin>>idDoUsuniecia;
    cout << "Czy jestes pewien, ze chcesz usunac adresata? Wcisnij t- tak, n- nie"<<endl;
    cin  >> wyborTN;
    if(wyborTN=='t')
        for(vector <Adresat>::iterator itr= adresaci.begin(); itr<adresaci.end(); itr++)
            if((*itr).id==idDoUsuniecia)
                adresaci.erase(itr);

////////////////////////////////////

    zapiszDane(adresaci);

////////////////////////////////////
}

void edytujAdresata(vector <Adresat> &adresaci) {
    int wybor=0, idDoZmiany;
    wyswietlWszystkichAdresatow(adresaci);
    vector<Adresat>::iterator itr;

    cout << "Podaj Id Adresata, ktorego dane maja zostac zmienione" << endl;
    cin >> idDoZmiany;

    for(vector<Adresat>::iterator itr=adresaci.begin(); itr<adresaci.end(); itr++)
        while(wybor!=6 &&(*itr).id==idDoZmiany) {
            cout << "Wybierz Dane do zmiany:" << endl;
            cout<<"1 - imie"<<endl<<"2 - nazwisko"<<endl<<"3 - numer telefonu"<<endl<<"4 - email"<<endl<<"5 - adres"<<endl<<"6 - powrot do menu"<<endl;
            cin>> wybor;

            switch (wybor) {
            case 1:
                cout<<"Podaj nowe imie: ";
                cin>>(*itr).imie;
                break;
            case 2:
                cout<<"Podaj nowe nazwisko: ";
                cin>>(*itr).nazwisko;
                break;
            case 3:
                cout<<"Podaj nowy numer telefonu: ";
                cin>>(*itr).numerTelefonu;
                break;
            case 4:
                cout<<"Podaj nowy email: ";
                cin>>(*itr).email;
                break;
            case 5:
                cout<<"Podaj nowy adres: ";
                cin>>(*itr).adres;
                break;
            case 6:
                break;
            }
        }

////////////////////////////////////

    zapiszDane(adresaci);

////////////////////////////////////
}

int main() {
    vector<Adresat> adresaci;
    int wybranaOpcja;

    wczytajDaneZPliku(adresaci);
    while(1) {
        system("cls");

        cout << "KSIAZKA ADRESOWA"                  << endl;
        cout << "1. Dodaj adresata"                 << endl;
        cout << "2. Wyszukaj po imieniu"            << endl;
        cout << "3. Wyszukaj po nazwisku"           << endl;
        cout << "4. Wyswietl wszystkich adresatow"  << endl;
        cout << "5. Usun adresata"                  << endl;
        cout << "6. Edytuj adresata"                << endl;
        cout << "9. Zakoncz program"                << endl;
        cout << "TWOJ WYBOR: ";

        cin >> wybranaOpcja;

        if (wybranaOpcja == 1)
            dodajAdresata(adresaci);
        else if (wybranaOpcja == 2)
            wyszukajPoImieniuLubNazwisku(adresaci, "imie");
        else if (wybranaOpcja == 3)
            wyszukajPoImieniuLubNazwisku(adresaci, "nazwisko");
        else if (wybranaOpcja == 4)
            wyswietlWszystkichAdresatow(adresaci);
        else if (wybranaOpcja == 5)
            usunAdresata(adresaci);
        else if (wybranaOpcja == 6)
            edytujAdresata(adresaci);
        else if (wybranaOpcja == 9)
////////////////////////////////////
            exit(0);
////////////////////////////////////
        system("pause");
    }


    return 0;
}
