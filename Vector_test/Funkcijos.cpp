#include "Header.h"
#include "Funkcijos.h"
#include "MyVector.h"
///
/// Isvedimo operatoriaus funkcija
///
std::ostream& operator<<(std::ostream& os, const Studentas& studentas)
{
	os << fixed << setprecision(2) << std::left << std::setw(13) << studentas.getVardas()
		<< std::left << std::setw(20) << studentas.getPavarde()
		<< std::left << std::setw(20) << studentas.get_vidurkis()
		<< std::left << std::setw(20) << studentas.get_mediana();
	return os;
}
///
///Failo sukurimo (generavimo) funkcija
///
void FailoSukurimas(MyVector <Studentas>& grupe, int failoDydis, int pazymiuSkaicius)
{
	auto start = std::chrono::high_resolution_clock::now();

	ofstream sugeneruotas("sugeneruotas" + std::to_string(failoDydis) + ".txt");

	auto startGeneravimas = std::chrono::high_resolution_clock::now();

	std::random_device rd;
	std::mt19937 mt(static_cast<long unsigned int> (rd()));
	std::uniform_int_distribution<int> Dist(0, 99);
	std::uniform_int_distribution<int> paz_dist(0, 10);

	sugeneruotas << left << setw(15) << "Vardas" << setw(20) << "Pavarde";
	for (int j = 0; j < pazymiuSkaicius; j++)
	{
		sugeneruotas << left << setw(6) << ("ND" + std::to_string(j + 1));
	}
	sugeneruotas << left << setw(7) << "Egz." << endl;
	for (int i = 0; i < failoDydis; i++)
	{
		sugeneruotas << left << setw(15) << VARDAI[Dist(mt)] << setw(20) << PAVARDES[Dist(mt)];
		for (int j = 0; j <= pazymiuSkaicius; j++)
		{
			sugeneruotas << left << setw(5) << paz_dist(mt) << " ";
		}
		sugeneruotas << endl;
	}
	sugeneruotas.close();

	auto endGeneravimas = std::chrono::high_resolution_clock::now();
	auto generacija = std::chrono::duration_cast<std::chrono::milliseconds>(endGeneravimas - startGeneravimas).count();
	cout << "Failo sugeneruotas" + std::to_string(failoDydis) + ".txt" " generavimas truko: " << fixed << setprecision(2) << static_cast<double>(generacija) / 1000 << "s" << endl;
	string strategija = "2";
	KitiSkaiciavimai(grupe, strategija);
}
///
///Failo nuskaitymo funkcija
///
void Skaitymas(MyVector <Studentas>& grupe, float& nuskaitymas)
{

	string failas;
	ifstream duomenys;

	while (true)
	{
		cout << "Iveskite is kurio failo noretumete nuskaityti duomenis:" << endl;
		cin >> failas;

		try {
			duomenys.open(failas);

			if (!duomenys)
			{
				throw std::runtime_error("Failo atverti nepavyko, bandykite dar karta: ");
			}
			else
			{
				cout << "Failas atidarytas sekmingai, nuskaitoma..." << endl;
				break;
			}

		}
		catch (std::exception& e)
		{
			cout << "Error: " << e.what() << endl;
			cout << "Galimi tekstinio failo pavadinimai:" << endl;
			system("dir /b | findstr \\.txt$ | findstr /v protingi.txt | findstr /v neprotingi.txt");
		}
	}
	auto startNuskaitymas = std::chrono::high_resolution_clock::now();
	int perskirstymai = 0;
	string pirmaEilute;
	getline(duomenys, pirmaEilute);
	string line, vardas, pavarde;
	while (getline(duomenys, line)) {
		Studentas temp;
		std::istringstream ss(line);
		ss >> vardas >> pavarde;
		temp.setVardas(vardas);
		temp.setPavarde(pavarde);

		std::vector<int> marks;

		int pazymys;
		while (ss >> pazymys) {
			marks.push_back(pazymys);
		}
		int egzaminas = marks.back();
		marks.pop_back();
		temp.Vidurkis(marks, egzaminas);
		temp.Mediana(marks, egzaminas);

		temp.set_pazymiai(std::move(marks));

		grupe.push_back(temp);

		if (grupe.capacity() == grupe.size())
			perskirstymai++;
	}
	duomenys.close();

	auto endSkaitymas = std::chrono::high_resolution_clock::now();
	auto skaitymas = std::chrono::duration_cast<std::chrono::milliseconds>(endSkaitymas - startNuskaitymas).count();
	nuskaitymas = skaitymas;
	cout << "Failo nuskaitymas truko: " << fixed << setprecision(2) << static_cast<double>(skaitymas) / 1000 << "s" << endl;
	cout << "PERSKIRSTYMU SKAICIUS: " << perskirstymai << endl;

	duomenys.close();

}
///
/// Rikiavimo, rusiavimo, programos laiko skaiciavimo funkcija
///
void KitiSkaiciavimai(MyVector <Studentas>& grupe, string strategija)
{
	float nuskaitymas;

	for (auto& i : grupe)
	{
		i.get_pazymiai().clear();
	}
	grupe.clear();

	Skaitymas(grupe, nuskaitymas);

	auto start = std::chrono::high_resolution_clock::now();

	auto startRikiavimas = std::chrono::high_resolution_clock::now();
	sort(grupe.begin(), grupe.end(), Palyginimas1);
	auto endRikiavimas = std::chrono::high_resolution_clock::now();
	auto Rikiavimas = std::chrono::duration_cast<std::chrono::milliseconds>(endRikiavimas - startRikiavimas).count();
	cout << "Failo rikiavimas truko " << fixed << setprecision(2) << static_cast<double>(Rikiavimas) / 1000 << "s" << endl;

	float isvedimas = 0.0;
	float rusiavimas = 0.0;

	if (strategija == "1")
	{
		auto startRusiavimas = std::chrono::high_resolution_clock::now();
		vector <Studentas> protingi;
		vector <Studentas> neprotingi;
		for (auto& i : grupe)
		{
			if (i.get_vidurkis() < 5)
			{
				neprotingi.push_back(i);
			}
			else
			{
				protingi.push_back(i);
			}
		}
		auto endRusiavimas = std::chrono::high_resolution_clock::now();
		auto rusiavimas = std::chrono::duration_cast<std::chrono::milliseconds>(endRusiavimas - startRusiavimas).count();
		cout << "Failo rusiavimas truko: " << fixed << setprecision(2) << static_cast<double>(rusiavimas) / 1000 << "s" << endl;

		IsvedimasIFaila(protingi, neprotingi, isvedimas);
	}
	else if (strategija == "2")
	{
		isvedimas = 0;
		auto startRusiavimas = std::chrono::high_resolution_clock::now();
		vector <Studentas> neprotingi;

		auto it = std::remove_if(grupe.begin(), grupe.end(), [](const Studentas& s) { return !(s.get_vidurkis() < 5.0); });
		std::copy(it, grupe.end(), std::back_inserter(neprotingi));
		grupe.erase(it, grupe.end());

		auto endRusiavimas = std::chrono::high_resolution_clock::now();
		auto rusiavimas = std::chrono::duration_cast<std::chrono::milliseconds>(endRusiavimas - startRusiavimas).count();
		cout << "Failo rusiavimas truko: " << fixed << setprecision(2) << static_cast<double>(rusiavimas) / 1000 << "s" << endl;

		//permesti grupe i nauja vektoriu

		vector<Studentas> protingi(grupe.begin(), grupe.end());

		IsvedimasIFaila(neprotingi, protingi, isvedimas);
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	std::cout << "Programos trukme: " << fixed << setprecision(2) << static_cast<double>(Rikiavimas + rusiavimas + nuskaitymas + isvedimas) / 1000 << "s" << endl;
}
///
/// Palyginimo funkcija rusiavimui pagal pavarde
///
bool Palyginimas(const Studentas& a, Studentas& b)
{
	return a.getVardas() < b.getPavarde();
}
///
/// Palyginimo funkcija rusiavimui pagal vidurki
///
bool Palyginimas1(const Studentas& a, Studentas& b)
{
	return a.get_vidurkis() < b.get_vidurkis();
}
///
/// Isvedimo i gaila funkcija
///
void IsvedimasIFaila(vector<Studentas> protingi, vector<Studentas> neprotingi, float& isvestis)
{
	auto startIsvedimas = std::chrono::high_resolution_clock::now();
	ofstream smart("protingi.txt");

	smart << left << setw(13) << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis (Vid.) /" << setw(20) << "Galutinis (Med.)" << endl;
	smart << "-----------------------------------------------------------------------------------" << endl;
	for (auto& i : protingi)
	{
		smart << i << endl;
	}

	smart.close();

	ofstream stupid("neprotingi.txt");

	stupid << left << setw(13) << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis (Vid.) /" << setw(20) << "Galutinis (Med.)" << endl;
	stupid << "-----------------------------------------------------------------------------------" << endl;
	for (auto& i : neprotingi)
	{
		stupid << i << endl;
	}

	auto endIsvedimas = std::chrono::high_resolution_clock::now();
	auto isvedimas = std::chrono::duration_cast<std::chrono::milliseconds>(endIsvedimas - startIsvedimas).count();
	cout << "Failo isvedimas truko: " << fixed << setprecision(2) << static_cast<double>(isvedimas) / 1000 << "s" << endl;
	isvestis = isvedimas;

	stupid.close();
}
