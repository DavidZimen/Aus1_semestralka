#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "../SemestralnaPraca_Zimen/structures/table/unsorted_sequence_table.h"	
#include "../SemestralnaPraca_Zimen/structures/table/sorted_sequence_table.h"
#include "../SemestralnaPraca_Zimen/structures/array/array.h"
#include "uzemna_jednotka.h"
#include "typ_uj.h"

namespace hlavny
{
	class Main 
	{
	private:
		structures::SortedSequenceTable<std::wstring, uzemne_jednotky::UzemnaJednotka*>* kraje_;
		structures::SortedSequenceTable<std::wstring, uzemne_jednotky::UzemnaJednotka*>* okresy_;
		structures::SortedSequenceTable<std::wstring, uzemne_jednotky::UzemnaJednotka*>* obce_;

		const wchar_t delimeter_ = L';';
		const wchar_t eolChar_ = L'\n';
	public:
		Main();
		~Main();
		void LoadData();
		void dataLoaderOnSteroids();
		void parseAge(std::wstring& ageLine, structures::Array<int>* ageArray);
		void parseScholarship(std::wstring& scholLine, structures::UnsortedSequenceTable<std::wstring, int>* scholTable);
		int findAndMove(std::wstring& line, int& iDel, int& iSubstr);
	};


	inline Main::Main() :
		kraje_(new structures::SortedSequenceTable<std::wstring, uzemne_jednotky::UzemnaJednotka*>),
		okresy_(new structures::SortedSequenceTable<std::wstring, uzemne_jednotky::UzemnaJednotka*>),
		obce_(new structures::SortedSequenceTable<std::wstring, uzemne_jednotky::UzemnaJednotka*>)
	{
		LoadData();
	}

	inline Main::~Main()
	{
		delete kraje_;
		delete okresy_;
		delete obce_;

		kraje_ = nullptr;
		okresy_ = nullptr;
		obce_ = nullptr;
	}

	inline void Main::LoadData()
	{
		std::wcout << "Starting loading..." << std::endl;

		std::wifstream fileObce;
		std::wifstream fileOkresy;
		std::wifstream fileKraje;
		std::wifstream fileMuzi;
		std::wifstream fileZeny;
		std::wifstream fileVzdelanie;

		fileObce.imbue(std::locale("sk.UTF-8"));
		fileOkresy.imbue(std::locale("sk.UTF-8"));
		fileKraje.imbue(std::locale("sk.UTF-8"));
		fileMuzi.imbue(std::locale("sk.UTF-8"));
		fileZeny.imbue(std::locale("sk.UTF-8"));
		fileVzdelanie.imbue(std::locale("sk.UTF-8"));

		std::wstring toThrow, code, officialTitle, mediumTitle, shortTitle, lineAge, lineSchool = L"";

		fileKraje.open("../SemestralnaPraca_Zimen/data/kraje.csv");
		//hlavicka, ktora je nepotrebna
		std::getline(fileKraje, toThrow);
		while (!fileKraje.eof()) {
			std::getline(fileKraje, code, delimeter_);
			std::getline(fileKraje, officialTitle, delimeter_);
			std::getline(fileKraje, shortTitle, eolChar_);

			auto kraj = new uzemne_jednotky::UzemnaJednotka(uzemne_jednotky::TypUzemJednotka::KRAJ, code, officialTitle, officialTitle, shortTitle);
			kraje_->insert(code, kraj);
		}
		fileKraje.close();

		fileOkresy.open("../SemestralnaPraca_Zimen/data/okresy.csv");
		//hlavicka, ktora je nepotrebna
		std::getline(fileOkresy, toThrow);
		while (!fileOkresy.eof()) {
			std::getline(fileOkresy, code, delimeter_);
			std::getline(fileOkresy, officialTitle, delimeter_);
			std::getline(fileOkresy, shortTitle, eolChar_);

			auto okres = new uzemne_jednotky::UzemnaJednotka(uzemne_jednotky::TypUzemJednotka::OKRES, code, officialTitle, officialTitle, shortTitle);
			okresy_->insert(code, okres);
		}
		fileOkresy.close();

		//otvorenie suborov, ktore suvisia s obcami
		fileObce.open("../SemestralnaPraca_Zimen/data/obce.csv");
		fileMuzi.open("../SemestralnaPraca_Zimen/data/vek_muzi.csv");
		fileZeny.open("../SemestralnaPraca_Zimen/data/vek_zeny.csv");
		fileVzdelanie.open("../SemestralnaPraca_Zimen/data/vzdelanie.csv");

		//hlavicka, ktora je nepotrebna
		std::getline(fileObce, toThrow);
		std::getline(fileMuzi, toThrow);
		std::getline(fileZeny, toThrow);
		std::getline(fileVzdelanie, toThrow);

		while (!fileObce.eof()) {
			auto vekMuzi = new structures::Array<int>(101);
			auto vekZeny = new structures::Array<int>(101);
			auto vzdelanie = new structures::UnsortedSequenceTable<std::wstring, int>();

			std::getline(fileObce, code, delimeter_);
			std::getline(fileObce, officialTitle, delimeter_);
			std::getline(fileObce, mediumTitle, delimeter_);
			std::getline(fileObce, shortTitle, eolChar_);

			uzemne_jednotky::UzemnaJednotka* obec = new uzemne_jednotky::UzemnaJednotka(uzemne_jednotky::TypUzemJednotka::OBEC, code, officialTitle, mediumTitle, shortTitle);

			//odstrani prve dva stlpce, kedze su nepotrebne
			std::getline(fileMuzi, toThrow, delimeter_);
			std::getline(fileMuzi, toThrow, delimeter_);
			std::getline(fileZeny, toThrow, delimeter_);
			std::getline(fileZeny, toThrow, delimeter_);
			std::getline(fileVzdelanie, toThrow, delimeter_);
			std::getline(fileVzdelanie, toThrow, delimeter_);

			//nacitanie riadka s hodnotami a ulozenie do prislusneho pola
			std::getline(fileMuzi, lineAge, eolChar_);
			parseAge(lineAge, vekMuzi);
			obec->setAgeMen(vekMuzi);
			std::getline(fileZeny, lineAge, eolChar_);
			parseAge(lineAge, vekZeny);
			obec->setAgeWomen(vekZeny);
			std::getline(fileVzdelanie, lineSchool, eolChar_);
			parseScholarship(lineSchool, vzdelanie);
			obec->setScholarship(vzdelanie);

			obce_->insert(code, obec);
		}
		fileObce.close();
		fileMuzi.close();
		fileZeny.close();
		fileVzdelanie.close();

		std::wcout << "Poèet obcí: " << obce_->size() << std::endl;
		std::wcout << "Poèet okresov: " << okresy_->size() << std::endl;
		std::wcout << "Poèet krajov: " << kraje_->size() << std::endl;
	}

	inline void Main::dataLoaderOnSteroids()
	{
		std::wcout << "Starting loading..." << std::endl;

		//definovanie suborov
		std::wifstream fileObce;
		std::wifstream fileOkresy;
		std::wifstream fileKraje;
		std::wifstream fileMuzi;
		std::wifstream fileZeny;
		std::wifstream fileVzdelanie;

		//priradenie utf-8 kodavania do jednotlivych suborov
		fileObce.imbue(std::locale("sk.UTF-8"));
		fileOkresy.imbue(std::locale("sk.UTF-8"));
		fileKraje.imbue(std::locale("sk.UTF-8"));
		fileMuzi.imbue(std::locale("sk.UTF-8"));
		fileZeny.imbue(std::locale("sk.UTF-8"));
		fileVzdelanie.imbue(std::locale("sk.UTF-8"));

		//otvorenie kazdeho suboru
		fileKraje.open("../SemestralnaPraca_Zimen/data/kraje.csv");
		fileOkresy.open("../SemestralnaPraca_Zimen/data/okresy.csv");
		fileObce.open("../SemestralnaPraca_Zimen/data/obce.csv");
		fileMuzi.open("../SemestralnaPraca_Zimen/data/vek_muzi.csv");
		fileZeny.open("../SemestralnaPraca_Zimen/data/vek_zeny.csv");
		fileVzdelanie.open("../SemestralnaPraca_Zimen/data/vzdelanie.csv");

		//odhodenie hlaviciek, ktore su nepotrebne
		std::wstring toThrow = L"";
		std::getline(fileKraje, toThrow);
		std::getline(fileOkresy, toThrow);
		std::getline(fileObce, toThrow);
		std::getline(fileMuzi, toThrow);
		std::getline(fileZeny, toThrow);
		std::getline(fileVzdelanie, toThrow);

		//definovanie premennych pre ukladanie udajov so suborov, pre kazdy subor jedna sada premennych
		std::wstring krCode, krOfficialTitle = L"";
		std::wstring okCode, okOfficialTitle = L"";
		std::wstring obCode, obOfficialTitle, obMediumTitle, obShortTitle, lineAge, lineSchool = L"";
	}

	inline void Main::parseAge(std::wstring& ageLine, structures::Array<int>* ageArray)
	{
		int indexDelimeter = ageLine.find(delimeter_);
		int indexSubstr = 0;
		int indexArray = 0;

		while (indexArray < ageArray->size()) {
			ageArray->at(indexArray) = findAndMove(ageLine, indexDelimeter, indexSubstr);
			std::cout << ageArray->at(indexArray) << std::endl;
			indexArray++;

			if (indexDelimeter == std::string::npos) {
				ageArray->at(indexArray) = std::stoi(ageLine.substr(indexSubstr, ageLine.length()));
			}
		}
	}

	inline void Main::parseScholarship(std::wstring& scholLine, structures::UnsortedSequenceTable<std::wstring, int>* scholTable)
	{
		int indexDelimeter = scholLine.find(delimeter_);
		int indexSubstr = 0;

		scholTable->insert(L"bez ukonèeného vzdelania", findAndMove(scholLine, indexDelimeter, indexSubstr));
		scholTable->insert(L"základné", findAndMove(scholLine, indexDelimeter, indexSubstr));
		scholTable->insert(L"uènovské", findAndMove(scholLine, indexDelimeter, indexSubstr));
		scholTable->insert(L"stredné", findAndMove(scholLine, indexDelimeter, indexSubstr));
		scholTable->insert(L"vyššie", findAndMove(scholLine, indexDelimeter, indexSubstr));
		scholTable->insert(L"vysokoškolské", findAndMove(scholLine, indexDelimeter, indexSubstr));
		scholTable->insert(L"bez vzdelania", findAndMove(scholLine, indexDelimeter, indexSubstr));
		scholTable->insert(L"nezistené", findAndMove(scholLine, indexDelimeter, indexSubstr));
	}

	inline int Main::findAndMove(std::wstring& line, int& iDel, int& iSubstr)
	{
		int result = std::stoi(line.substr(iSubstr, iDel));
		iSubstr = iDel + 1;
		iDel = line.find(delimeter_, iSubstr);
		return result;
	}
}
