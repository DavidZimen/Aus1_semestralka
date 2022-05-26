#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include "../SemestralnaPraca_Zimen/structures/table/unsorted_sequence_table.h"	
#include "../SemestralnaPraca_Zimen/structures/table/sorted_sequence_table.h"
#include "../SemestralnaPraca_Zimen/structures/array/array.h"
#include "uzemna_jednotka.h"
#include "typ_uj.h"
#include "loader.h"

namespace uj
{
	class Stat : public UzemnaJednotka
	{
	private:
		structures::SortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* kraje_;
		structures::SortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* okresy_;
		structures::SortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* obce_;

		structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* krajeU_;
		structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* okresyU_;
		structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* obceU_;
	public:
		Stat();
		~Stat();

		structures::SortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* getKraje() { return kraje_; };
		structures::SortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* getOkresy() { return okresy_; };
		structures::SortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* getObce() { return obce_; };

		structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* getKrajeU() { return krajeU_; };
		structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* getOkresyU() { return okresyU_; };
		structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* getObceU() { return obceU_; };

	};

	inline Stat::Stat() :
		UzemnaJednotka(TypUzemJednotka::STAT, L"SK", L"Slovenská republika", L"Slovensko", L"Slovensko"),
		kraje_(new structures::SortedSequenceTable<std::wstring, uj::UzemnaJednotka*>()),
		okresy_(new structures::SortedSequenceTable<std::wstring, uj::UzemnaJednotka*>()),
		obce_(new structures::SortedSequenceTable<std::wstring, uj::UzemnaJednotka*>()),
		krajeU_(new structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>()),
		okresyU_(new structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>()),
		obceU_(new structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>())
	{
	}

	inline Stat::~Stat()
	{
		for (auto obec : *obceU_) {
			delete obec->accessData();
		}

		for (auto okres : *okresyU_) {
			delete okres->accessData();
		}

		for (auto kraj : *krajeU_) {
			delete kraj->accessData();
		}

		delete krajeU_;
		delete okresyU_;
		delete obceU_;

		delete kraje_;
		delete okresy_;
		delete obce_;

		krajeU_ = nullptr;
		okresyU_ = nullptr;
		obceU_ = nullptr;

		kraje_ = nullptr;
		okresy_ = nullptr;
		obce_ = nullptr;
	}
}