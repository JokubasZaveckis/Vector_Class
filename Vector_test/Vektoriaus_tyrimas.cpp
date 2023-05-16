#include "Header.h"
#include "Funkcijos.h"
#include "MyVector.h"
///
///Main funkcija programos tipo pasirinkimams
///
int main()
{
	int pasirinkimas = 0;
	MyVector<Studentas> grupe;
	int talpa = 50;
	grupe.reserve(talpa);

	while (true)
	{
		string choice;
		cout << "Iveskite 0 kad studentai butu nuskaitomi is failo" << endl;
		cout << "Iveskite 1 kad sugeneruotumete studentu faila" << endl;
		cin >> choice;
		if (choice == "0")
		{
			string strategija;
			cout << "Kokia strategija noretumete naudoti? (1 arba 2)" << endl;
			cin >> strategija;
			while (true)
			{
				if (strategija == "1" || strategija == "2")
				{
					break;
				}
				else
				{
					cout << "Netinkama ivestis, bandykite is naujo" << endl;
					cin >> strategija;
				}
			}

			KitiSkaiciavimai(grupe, strategija);
			cout << "Ar norite testi? (Iveskite 1, jei taip, arba bet koki kita skaiciu, jei ne.)" << endl;
			cin >> pasirinkimas;
			if (pasirinkimas != 1) {
				break;
			}
		}
		else if (choice == "1")
		{
			cout << "Iveskite kokio dydzio faila norite sugeneruoti:" << endl;
			cout << "Galimi failo dydziai: 1 000, 10 000, 100 000, 1 000 000, 10 000 000" << endl;
			string failuDydis;
			while (true)
			{
				cin >> failuDydis;
				if (failuDydis == "1000" || failuDydis == "10000" || failuDydis == "100000" || failuDydis == "1000000" || failuDydis == "10000000")
				{
					int dydis = stoi(failuDydis);
					int pazymiai;
					while (true)
					{
						cout << "Iveskite kiek pazymiu turi kiekvienas studentas (nuo 1 iki 10)" << endl;
						cin >> pazymiai;
						if (pazymiai > 0 && pazymiai <= 10)
						{
							FailoSukurimas(grupe, dydis, pazymiai);
							break;
						}
						else
						{
							cout << "Netinkama ivestis, bandykite dar karta" << endl;
						}
					}
					break;
				}
				else
				{
					cout << "Tokio pasirinkimo nera, bandykite dar karta: " << endl;
				}
			}
			cout << "Ar norite testi? (Iveskite 1, jei taip, arba bet koki kita skaiciu, jei ne.)" << endl;
			cin >> pasirinkimas;
			if (pasirinkimas != 1) {
				break;
			}
		}
		else
		{
			cout << "Ivestis netinkama, bandykite is naujo" << endl;
			cin >> choice;
		}
	}
	grupe.clear();
	return 0;
}


