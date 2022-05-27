#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "../SemestralnaPraca_Zimen/structures/table/unsorted_sequence_table.h"	
#include "../SemestralnaPraca_Zimen/structures/table/sorted_sequence_table.h"
#include "../SemestralnaPraca_Zimen/structures/array/array.h"
#include "uzemna_jednotka.h"
#include "typ_uj.h"
#include "stat.h"


namespace data_loading
{
	class Loader
	{
	private:
		const wchar_t delimeter_ = L';';
		const wchar_t eolChar_ = L'\n';

	public:
		static Loader& getInstance();

	public:
		uj::Stat* LoadData();

		void parseLine(std::wstring& pLine, structures::Array<int>* pArray);
		void toScholarshipTable(structures::Array<int>* scholArray, structures::UnsortedSequenceTable<std::wstring, int>* scholTable);
		int findAndMove(std::wstring& line, int& iDel, int& iSubstr);
		void addToSupUnit(structures::Array<int>* sup, structures::Array<int>* sub);

	private:
		Loader() = default;
		Loader(const Loader&) = delete;
	};


	inline Loader& Loader::getInstance()
	{
		static Loader instance;
		return instance;
	}

	inline uj::Stat* Loader::LoadData()
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
		fileObce.open("../SemestralnaPraca_Zimen/data/obce_1.csv");
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
		std::wstring krCode, krOfficialTitle, krShortTitle = L"";
		std::wstring okCode, okOfficialTitle, okShortTitle = L"";
		std::wstring obCode, obOfficialTitle, obMediumTitle, obShortTitle, lineAge, lineSchool = L"";

		//vytvorenie statu a prebranie jeho zoznamov na naplnenie datami
		uj::Stat* stat = new uj::Stat();
		auto kraje = stat->getKraje();
		auto okresy = stat->getOkresy();
		auto obce = stat->getObce();
		auto krajeU = stat->getKrajeU();
		auto okresyU = stat->getOkresyU();
		auto obceU = stat->getObceU();

		//premenne na vytvorenie uzemnej jednotky po nacitani prislusnych hodnot zo suboru
		uj::UzemnaJednotka* kraj = nullptr;
		uj::UzemnaJednotka* okres = nullptr;
		uj::UzemnaJednotka* obec = nullptr;

		//pomocne struktury na informacie pre stat
		structures::Array<int>* vekMuziSt = new structures::Array<int>(101);
		structures::Array<int>* vekZenySt = new structures::Array<int>(101);
		structures::Array<int>* vzdelanieArrSt = new structures::Array<int>(8);
		structures::UnsortedSequenceTable<std::wstring, int>* vzdelanieSt = new structures::UnsortedSequenceTable<std::wstring, int>();

		//pomocne struktury na informacie pre kraj 
		structures::Array<int>* vekMuziKr = nullptr;
		structures::Array<int>* vekZenyKr = nullptr;
		structures::Array<int>* vzdelanieArrKr = nullptr;
		structures::UnsortedSequenceTable<std::wstring, int>* vzdelanieKr = nullptr;

		//pomocne struktury na informacie pre okres 
		structures::Array<int>* vekMuziOk = nullptr;
		structures::Array<int>* vekZenyOk = nullptr;
		structures::Array<int>* vzdelanieArrOk = nullptr;
		structures::UnsortedSequenceTable<std::wstring, int>* vzdelanieOk = nullptr;

		//pomocne struktury na informacie pre obec 
		structures::Array<int>* vekMuziOb = nullptr;
		structures::Array<int>* vekZenyOb = nullptr;
		structures::Array<int>* vzdelanieArrOb = nullptr;
		structures::UnsortedSequenceTable<std::wstring, int>* vzdelanieOb = nullptr;

		//uchovanie uj, ktora uz je mimo daneho kraja, aby nedoslo ku strate dat
		uj::UzemnaJednotka* okresMimoKraja = nullptr;
		uj::UzemnaJednotka* obecMimoOkresu = nullptr;

		while (!fileKraje.eof()) {
			vekMuziKr = new structures::Array<int>(101);
			vekZenyKr = new structures::Array<int>(101);
			vzdelanieArrKr = new structures::Array<int>(8);
			vzdelanieKr = new structures::UnsortedSequenceTable<std::wstring, int>();

			std::getline(fileKraje, krCode, delimeter_);
			std::getline(fileKraje, krOfficialTitle, delimeter_);
			std::getline(fileKraje, krShortTitle, eolChar_);

			kraj = new uj::UzemnaJednotka(uj::TypUzemJednotka::KRAJ, krCode, krOfficialTitle, krOfficialTitle, krShortTitle);
			kraj->setSubUnits(new structures::ArrayList<uj::UzemnaJednotka*>());
			std::wstring toCompareKr = krCode.substr(5, 5);
			if (toCompareKr == L"*****") {
				toCompareKr = L"SKZZZ";
			}

			if (okresMimoKraja != nullptr) {
				addToSupUnit(vekMuziKr, vekMuziOk);
				addToSupUnit(vekZenyKr, vekZenyOk);
				addToSupUnit(vzdelanieArrKr, vzdelanieArrOk);
				okres->setNadradena(kraj);

				okresyU->insert(okCode, okres);
				okresy->insert(okOfficialTitle, okres);
				kraj->addSubUnit(okres);
				okresMimoKraja = nullptr;
				delete vzdelanieArrOk;
			}

			while (okresMimoKraja == nullptr && !fileOkresy.eof()) {
				vekMuziOk = new structures::Array<int>(101);
				vekZenyOk = new structures::Array<int>(101);
				vzdelanieArrOk = new structures::Array<int>(8);
				vzdelanieOk = new structures::UnsortedSequenceTable<std::wstring, int>();

				std::getline(fileOkresy, okCode, delimeter_);
				std::getline(fileOkresy, okOfficialTitle, delimeter_);
				std::getline(fileOkresy, okShortTitle, eolChar_);

				okres = new uj::UzemnaJednotka(uj::TypUzemJednotka::OKRES, okCode, okOfficialTitle, okOfficialTitle, okShortTitle);
				okres->setSubUnits(new structures::ArrayList<uj::UzemnaJednotka*>());

				if (obecMimoOkresu != nullptr) {
					addToSupUnit(vekMuziOk, vekMuziOb);
					addToSupUnit(vekZenyOk, vekZenyOb);
					addToSupUnit(vzdelanieArrOk, vzdelanieArrOb);
					obec->setNadradena(okres);

					obceU->insert(obCode, obec);
					obce->insert(obMediumTitle, obec);
					okres->addSubUnit(obec);
					obecMimoOkresu = nullptr;
					delete vzdelanieArrOb;
				}

				while (obecMimoOkresu == nullptr && !fileObce.eof()) {
					vekMuziOb = new structures::Array<int>(101);
					vekZenyOb = new structures::Array<int>(101);
					vzdelanieArrOb = new structures::Array<int>(8);
					vzdelanieOb = new structures::UnsortedSequenceTable<std::wstring, int>();

					std::getline(fileObce, obCode, delimeter_);
					std::getline(fileObce, obOfficialTitle, delimeter_);
					std::getline(fileObce, obMediumTitle, delimeter_);
					std::getline(fileObce, obShortTitle, eolChar_);

					obec = new uj::UzemnaJednotka(uj::TypUzemJednotka::OBEC, obCode, obOfficialTitle, obMediumTitle, obShortTitle);

					//odstrani prve dva stlpce, kedze su nepotrebne
					std::getline(fileMuzi, toThrow, delimeter_);
					std::getline(fileMuzi, toThrow, delimeter_);
					std::getline(fileZeny, toThrow, delimeter_);
					std::getline(fileZeny, toThrow, delimeter_);
					std::getline(fileVzdelanie, toThrow, delimeter_);
					std::getline(fileVzdelanie, toThrow, delimeter_);

					//nacitanie riadka s hodnotami a ulozenie do prislusneho pola
					std::getline(fileMuzi, lineAge, eolChar_);
					parseLine(lineAge, vekMuziOb);
					obec->setAgeMen(vekMuziOb);
					std::getline(fileZeny, lineAge, eolChar_);
					parseLine(lineAge, vekZenyOb);
					obec->setAgeWomen(vekZenyOb);
					std::getline(fileVzdelanie, lineSchool, eolChar_);
					parseLine(lineSchool, vzdelanieArrOb);
					toScholarshipTable(vzdelanieArrOb, vzdelanieOb);
					obec->setScholarship(vzdelanieOb);

					if (obCode.substr(0, 6) == okCode) {
						addToSupUnit(vekMuziOk, vekMuziOb);
						addToSupUnit(vekZenyOk, vekZenyOb);
						addToSupUnit(vzdelanieArrOk, vzdelanieArrOb);
						obec->setNadradena(okres);


						obceU->insert(obCode, obec);
						obce->insert(obMediumTitle, obec);
						okres->addSubUnit(obec);
						delete vzdelanieArrOb;
					}
					else {
						obecMimoOkresu = obec;
					}
				}

				okres->setAgeMen(vekMuziOk);
				okres->setAgeWomen(vekZenyOk);
				toScholarshipTable(vzdelanieArrOk, vzdelanieOk);
				okres->setScholarship(vzdelanieOk);

				if (okCode.substr(0, 5) == toCompareKr) {
					addToSupUnit(vekMuziKr, vekMuziOk);
					addToSupUnit(vekZenyKr, vekZenyOk);
					addToSupUnit(vzdelanieArrKr, vzdelanieArrOk);
					okres->setNadradena(kraj);

					okresyU->insert(okCode, okres);
					okresy->insert(okOfficialTitle, okres);
					kraj->addSubUnit(okres);
					delete vzdelanieArrOk;
				}
				else {
					okresMimoKraja = okres;
				}
			}

			kraj->setAgeMen(vekMuziKr);
			kraj->setAgeWomen(vekZenyKr);
			toScholarshipTable(vzdelanieArrKr, vzdelanieKr);
			kraj->setScholarship(vzdelanieKr);

			addToSupUnit(vekMuziSt, vekMuziKr);
			addToSupUnit(vekZenySt, vekZenyKr);
			addToSupUnit(vzdelanieArrSt, vzdelanieArrKr);
			kraj->setNadradena(stat);

			krajeU->insert(krCode, kraj);
			kraje->insert(krOfficialTitle, kraj);
			delete vzdelanieArrKr;
		}

		stat->setAgeMen(vekMuziSt);
		stat->setAgeWomen(vekZenySt);
		toScholarshipTable(vzdelanieArrSt, vzdelanieSt);
		stat->setScholarship(vzdelanieSt);
		delete vzdelanieArrSt;

		fileKraje.close();
		fileOkresy.close();
		fileObce.close();
		fileMuzi.close();
		fileZeny.close();
		fileVzdelanie.close();

		std::wcout << "Data successfully loaded." << std::endl;

		return stat;
	}

	inline void Loader::parseLine(std::wstring& pLine, structures::Array<int>* pArray)
	{
		int indexDelimeter = pLine.find(delimeter_);
		int indexSubstr = 0;
		int indexArray = 0;

		while (indexArray < pArray->size()) {
			pArray->at(indexArray) = findAndMove(pLine, indexDelimeter, indexSubstr);
			indexArray++;

			if (indexDelimeter == std::string::npos) {
				pArray->at(indexArray) = std::stoi(pLine.substr(indexSubstr, pLine.length()));
			}
		}
	}

	inline void Loader::toScholarshipTable(structures::Array<int>* scholArray, structures::UnsortedSequenceTable<std::wstring, int>* scholTable)
	{
		scholTable->insert(L"bez ukonèeného vzdelania", scholArray->at(0));
		scholTable->insert(L"základné", scholArray->at(1));
		scholTable->insert(L"uènovské", scholArray->at(2));
		scholTable->insert(L"stredné", scholArray->at(3));
		scholTable->insert(L"vyššie", scholArray->at(4));
		scholTable->insert(L"vysokoškolské", scholArray->at(5));
		scholTable->insert(L"bez vzdelania", scholArray->at(6));
		scholTable->insert(L"nezistené", scholArray->at(7));
	}

	inline int Loader::findAndMove(std::wstring& line, int& iDel, int& iSubstr)
	{
		int result = std::stoi(line.substr(iSubstr, iDel));
		iSubstr = iDel + 1;
		iDel = line.find(delimeter_, iSubstr);
		return result;
	}

	inline void Loader::addToSupUnit(structures::Array<int>* sup, structures::Array<int>* sub)
	{
		for (int i = 0; i < sup->size(); i++) {
			sup->at(i) += sub->at(i);
		}
	}
}