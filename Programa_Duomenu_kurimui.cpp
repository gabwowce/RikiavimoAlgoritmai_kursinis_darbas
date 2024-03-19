#include <set>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void GeneruotiAtsitiktiniusSkaicius(int kiekis, const string failoPavadinimas) {
    ofstream outputFile(failoPavadinimas);
    if (!outputFile.is_open()) {
        cout << "Nepavyko atidaryti failo '" << failoPavadinimas << "'." << endl;
        return;
    }

    for (int i = 0; i < kiekis; ++i) {
        int atsitiktinisSkaicius = rand() % 100000 + 1;
        outputFile << atsitiktinisSkaicius << endl;

    }

    outputFile.close();
    cout << "Atsitiktiniai skaiciai sekmingai irasyti i faila: '" << failoPavadinimas << endl;
}

void GeneruotiIrRasytiAtvirksciaiSurikiuotusSkaicius(int kiekis, const string failoPavadinimas) {
    vector<int> skaiciai;

    for (int i = 0; i < kiekis; ++i) {
        skaiciai.push_back(rand() % 100000 + 1);
}

    sort(skaiciai.begin(), skaiciai.end(), greater<int>());

    ofstream outputFile(failoPavadinimas);
    if (!outputFile.is_open()) {
        cout << "Nepavyko atidaryti failo '" << failoPavadinimas << "'." << endl;
        return;
    }

    for (int i = 0; i < skaiciai.size(); ++i) {
        outputFile << skaiciai[i] << endl;
        
    }
    outputFile.close();
    cout << "Atvirkðèiai surikiuoti skaiciai sekmingai irasyti i faila: '" << failoPavadinimas << "'." << endl;
}

void GeneruotiIrRasytiSurikiuotusSkaicius(int kiekis, const string& failoPavadinimas) {
    vector<int> skaiciai;

    for (int i = 0; i < kiekis; ++i) {
        skaiciai.push_back(rand() % 100000 + 1);
    }

    sort(skaiciai.begin(), skaiciai.end());

    ofstream outputFile(failoPavadinimas);
    if (!outputFile.is_open()) {
        cout << "Nepavyko atidaryti failo '" << failoPavadinimas << "'." << endl;
        return;
    }

    for (int i = 0; i < skaiciai.size(); ++i) {
        outputFile << skaiciai[i] << endl;
        
    }
    outputFile.close();
    cout << "Surikiuoti skaiciai nuo maziausio iki didziausio sekmingai irasyti i faila: '" << failoPavadinimas << "'." << endl;
}



void IsvalytiEkrana() {
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}

void lauktiVartotojo() {
    cout << "\nPaspauskite bet kuri klavisa norint testi...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void menu() {
    cout << "Pasirinkite kokius duomenis norite sukurti:\n";
    cout << "1 - Nesurikiuotu duomenmu kurimas.\n";
    cout << "2 - Atvirksciai surikiuotu duomenmu kurimas.\n";
    cout << "3 - Surikiuotu duomenmu kurimas.\n";
    cout << "0 - Iseiti\n";
}

void duomenuKiekis() {
    cout << "Pasirinkitekiek norite sukurti duomenu:\n";
    cout << "1 - 5000\n";
    cout << "2 - 10000\n";
    cout << "3 - 50000 \n";
    cout << "4 - 100000  \n";
}

int main() {
    int pasirinkimas, kiekioPasirinkimas;
    srand(time(0));

    do {
        IsvalytiEkrana();
        menu();
        cin >> pasirinkimas;

        if (pasirinkimas == 0) break;

        duomenuKiekis();
        cin >> kiekioPasirinkimas;

        int kiekis = 0;
        switch (kiekioPasirinkimas) {
        case 1: kiekis = 5000; break;
        case 2: kiekis = 10000; break;
        case 3: kiekis = 50000; break;
        case 4: kiekis = 100000; break;
        default: cout << "Netinkamas kiekio pasirinkimas!\n"; continue;
        }


        if (pasirinkimas == 1) {
            string failoPavadinimas = to_string(kiekis) + "_Nesurusiuoti_Duomenys.csv";
            GeneruotiAtsitiktiniusSkaicius(kiekis, failoPavadinimas);
            lauktiVartotojo();
        }
        else if (pasirinkimas == 2) {
            string failoPavadinimas = to_string(kiekis) + "_Atvirksciai_Surusiuoti_Duomenys.csv";
            GeneruotiIrRasytiAtvirksciaiSurikiuotusSkaicius(kiekis, failoPavadinimas);
            lauktiVartotojo();
        }
        else if (pasirinkimas == 3) {
            string failoPavadinimas = to_string(kiekis) + "_Surusiuoti_Duomenys.csv";
            GeneruotiIrRasytiSurikiuotusSkaicius(kiekis, failoPavadinimas);
            lauktiVartotojo();
        }

        
    } while (pasirinkimas != 0);

    return 0;
}
