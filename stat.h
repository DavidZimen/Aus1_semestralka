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
	class Stat
	{
	private:
		structures::SortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* krajeS_;
		structures::SortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* okresyS_;
		structures::SortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* obceS_;

		structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* krajeU_;
		structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* okresyU_;
		structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* obceU_;
	public:
		Stat();
		~Stat();
	};

	inline Stat::Stat() :
		krajeS_(new structures::SortedSequenceTable<std::wstring, uj::UzemnaJednotka*>()),
		okresyS_(new structures::SortedSequenceTable<std::wstring, uj::UzemnaJednotka*>()),
		obceS_(new structures::SortedSequenceTable<std::wstring, uj::UzemnaJednotka*>()),
		krajeU_(new structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>()),
		okresyU_(new structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>()),
		obceU_(new structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>())
	{
		data_loading::Loader::getInstance().LoadData(krajeS_, okresyS_, obceS_);
	}

	inline Stat::~Stat()
	{
		for (auto obec : *obceS_) {
			delete obec->accessData();
		}

		for (auto okres : *okresyS_) {
			delete okres->accessData();
		}

		for (auto kraj : *krajeS_) {
			delete kraj->accessData();
		}

		delete krajeS_;
		delete okresyS_;
		delete obceS_;

		krajeS_ = nullptr;
		okresyS_ = nullptr;
		obceS_ = nullptr;
	}
}