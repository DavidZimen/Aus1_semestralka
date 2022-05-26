#pragma once
#include <string>
#include "../SemestralnaPraca_Zimen/structures/table/sorted_sequence_table.h"
#include "../SemestralnaPraca_Zimen/structures/table/unsorted_sequence_table.h"
#include "typ_uj.h"

namespace uj 
{
	class UzemnaJednotka 
	{
	private:
		TypUzemJednotka typ_;
		UzemnaJednotka* nadradena_;

		std::wstring code_;
		std::wstring officialTitle_;
		std::wstring mediumTitle_;
		std::wstring shortTitle_;

		structures::ArrayList<uj::UzemnaJednotka*>* subUnits_;
		structures::Array<int>* vekMuzi;
		structures::Array<int>* vekZeny_;
		structures::UnsortedSequenceTable<std::wstring, int>* vzdelanie_;
	public:
		UzemnaJednotka(TypUzemJednotka typ, std::wstring code, std::wstring officialTitle, std::wstring mediumTitle, std::wstring shortTitle);
		~UzemnaJednotka();

		void setNadradena(UzemnaJednotka* nadradena);
		void setSubUnits(structures::ArrayList<uj::UzemnaJednotka*>* subUnits);
		void setAgeMen(structures::Array<int>* ageMen);
		void setAgeWomen(structures::Array<int>* ageWomen);
		void setScholarship(structures::UnsortedSequenceTable<std::wstring, int>* scholarship);
		void addSubUnit(UzemnaJednotka* subUnit);
		int spocitajVekSkupinu(int vekOd, int vekDo);

		std::wstring& getNazov() { return shortTitle_; };
		UzemnaJednotka* getNadradena() { return nadradena_; };
		TypUzemJednotka getTyp() { return typ_; };
		int getPocetObyvatelov();

		bool patriDoVyssiehoCelku(std::wstring vyssiCelok);
		int pocetObyvatelovSoVzdelanim(std::wstring vzdelanie);
		int pocetObyvatelovSDanymVekomAPohlavim(int vek, std::wstring pohlavie);
		int pocetObyvatelovVDanejVekovejSkupine(std::wstring vekSkupina);

		void vypis();
	};

	inline UzemnaJednotka::UzemnaJednotka(TypUzemJednotka typ, std::wstring code, std::wstring officialTitle, std::wstring mediumTitle, std::wstring shortTitle) :
		typ_(typ),
		code_(code),
		officialTitle_(officialTitle),
		mediumTitle_(mediumTitle),
		shortTitle_(shortTitle),
		nadradena_(nullptr)
	{
		subUnits_ = nullptr;
		vekMuzi = nullptr;
		vekZeny_ = nullptr;
		vzdelanie_ = nullptr;
	}

	inline UzemnaJednotka::~UzemnaJednotka()
	{
		delete subUnits_;
		delete vekMuzi;
		delete vekZeny_;
		delete vzdelanie_;

		subUnits_ = nullptr;
		vekMuzi = nullptr;
		vekZeny_ = nullptr;
		vzdelanie_ = nullptr;
	}

	inline void UzemnaJednotka::setNadradena(UzemnaJednotka* nadradena)
	{
		if (nadradena_ == nullptr) {
			nadradena_ = nadradena;
		}
	}

	inline void UzemnaJednotka::setSubUnits(structures::ArrayList<uj::UzemnaJednotka*>* subUnits)
	{
		if (subUnits_ == nullptr) {
			subUnits_ = subUnits;
		}
	}

	inline void UzemnaJednotka::setAgeMen(structures::Array<int>* ageMen)
	{
		if (vekMuzi == nullptr) {
			vekMuzi = ageMen;
		}
	}

	inline void UzemnaJednotka::setAgeWomen(structures::Array<int>* ageWomen)
	{
		if (vekZeny_ == nullptr) {
			vekZeny_ = ageWomen;
		}
	}

	inline void UzemnaJednotka::setScholarship(structures::UnsortedSequenceTable<std::wstring, int>* scholarship)
	{
		if (vzdelanie_ == nullptr) {
			vzdelanie_ = scholarship;
		}
	}

	inline void UzemnaJednotka::addSubUnit(UzemnaJednotka* subUnit)
	{
		subUnits_->add(subUnit);
	}

	inline int UzemnaJednotka::spocitajVekSkupinu(int vekOd, int vekDo)
	{
		int result = 0;
		for (int i = vekOd; i <= vekDo; i++) {
			result += vekMuzi->at(i);
			result += vekZeny_->at(i);
		}
		return result;
	}

	inline int UzemnaJednotka::getPocetObyvatelov()
	{
		int result = 0;
		for (auto item : *vzdelanie_) {
			result += item->accessData();
		}

		return result;
	}

	inline bool UzemnaJednotka::patriDoVyssiehoCelku(std::wstring vyssiCelok)
	{
		if (this->nadradena_ == nullptr) {
			return false;
		}
		else if (this->nadradena_->getNazov() == vyssiCelok) {
			return true;
		}
		else {
			return this->nadradena_->patriDoVyssiehoCelku(vyssiCelok);
		}
	}

	inline int UzemnaJednotka::pocetObyvatelovSoVzdelanim(std::wstring vzdelanie)
	{
		return vzdelanie_->find(vzdelanie);
	}

	inline int UzemnaJednotka::pocetObyvatelovSDanymVekomAPohlavim(int vek, std::wstring pohlavie)
	{
		if (pohlavie == L"muž") {
			return vekMuzi->at(vek);
		}
		else if (pohlavie == L"žena") {
			return vekZeny_->at(vek);
		}
		else {
			return -1;
		}
	}

	inline int UzemnaJednotka::pocetObyvatelovVDanejVekovejSkupine(std::wstring vekSkupina)
	{
		if (vekSkupina == L"predproduktívni") {
			return spocitajVekSkupinu(0, 14);
		}
		else if (vekSkupina == L"produktívni") {
			return spocitajVekSkupinu(15, 64);
		}
		else if (vekSkupina == L"poproduktívni") {
			return spocitajVekSkupinu(65, 100);
		}
		else {
			return -1;
		}
	}

	inline void UzemnaJednotka::vypis()
	{
		if (nadradena_ != nullptr) {
			std::wcout << shortTitle_ << L" " << getPocetObyvatelov() << L" " << nadradena_->getNazov() << std::endl;
		}
	}
}