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

namespace uzemne_jednotky
{
	class Stat
	{
	private:
		structures::SortedSequenceTable<std::wstring, uzemne_jednotky::UzemnaJednotka*>* kraje_;
		structures::SortedSequenceTable<std::wstring, uzemne_jednotky::UzemnaJednotka*>* okresy_;
		structures::SortedSequenceTable<std::wstring, uzemne_jednotky::UzemnaJednotka*>* obce_;
	public:
		Stat();
		~Stat();
	};

	inline Stat::Stat() :
		kraje_(new structures::SortedSequenceTable<std::wstring, uzemne_jednotky::UzemnaJednotka*>()),
		okresy_(new structures::SortedSequenceTable<std::wstring, uzemne_jednotky::UzemnaJednotka*>()),
		obce_(new structures::SortedSequenceTable<std::wstring, uzemne_jednotky::UzemnaJednotka*>())
	{
		data_loading::Loader::getInstance().LoadData(kraje_, okresy_, obce_);
	}

	inline Stat::~Stat()
	{
		for (auto obec : *obce_) {
			delete obec->accessData();
		}

		for (auto okres : *okresy_) {
			delete okres->accessData();
		}

		for (auto kraj : *kraje_) {
			delete kraj->accessData();
		}

		delete kraje_;
		delete okresy_;
		delete obce_;

		kraje_ = nullptr;
		okresy_ = nullptr;
		obce_ = nullptr;
	}
}