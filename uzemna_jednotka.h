#pragma once
#include <string>
#include "../SemestralnaPraca_Zimen/structures/table/sorted_sequence_table.h"
#include "../SemestralnaPraca_Zimen/structures/table/unsorted_sequence_table.h"
#include "../SemestralnaPraca_Zimen/typ_uj.h"

namespace uzemne_jednotky 
{

	class UzemnaJednotka 
	{
	private:
		TypUzemJednotka typ_;

		std::wstring code_;
		std::wstring officialTitle_;
		std::wstring mediumTitle_;
		std::wstring shortTitle_;

		structures::ArrayList<UzemnaJednotka*>* subUnits_;
		structures::Array<int>* ageMen_;
		structures::Array<int>* ageWomen_;
		structures::UnsortedSequenceTable<std::wstring, int>* scholarship_;
	public:
		UzemnaJednotka(TypUzemJednotka typ, std::wstring code, std::wstring officialTitle, std::wstring mediumTitle, std::wstring shortTitle);
		~UzemnaJednotka();

		void setSubUnits(structures::ArrayList<UzemnaJednotka*>* subUnits);
		void setAgeMen(structures::Array<int>* ageMen);
		void setAgeWomen(structures::Array<int>* ageWomen);
		void setScholarship(structures::UnsortedSequenceTable<std::wstring, int>* scholarship);

		void addSubUnit(UzemnaJednotka* subUnit);
	};

	inline UzemnaJednotka::UzemnaJednotka(TypUzemJednotka typ, std::wstring code, std::wstring officialTitle, std::wstring mediumTitle, std::wstring shortTitle) :
		code_(code),
		officialTitle_(officialTitle),
		mediumTitle_(mediumTitle),
		shortTitle_(shortTitle)
	{
		subUnits_ = nullptr;
		ageMen_ = nullptr;
		ageWomen_ = nullptr;
		scholarship_ = nullptr;
	}

	inline UzemnaJednotka::~UzemnaJednotka()
	{
		delete subUnits_;
		delete ageMen_;
		delete ageWomen_;
		delete scholarship_;

		subUnits_ = nullptr;
		ageMen_ = nullptr;
		ageWomen_ = nullptr;
		scholarship_ = nullptr;
	}

	inline void UzemnaJednotka::setSubUnits(structures::ArrayList<UzemnaJednotka*>* subUnits)
	{
		if (subUnits_ == nullptr) {
			subUnits_ = subUnits;
		}
	}

	inline void UzemnaJednotka::setAgeMen(structures::Array<int>* ageMen)
	{
		if (ageMen_ == nullptr) {
			ageMen_ = ageMen;
		}
	}

	inline void UzemnaJednotka::setAgeWomen(structures::Array<int>* ageWomen)
	{
		if (ageWomen_ == nullptr) {
			ageWomen_ = ageWomen;
		}
	}

	inline void UzemnaJednotka::setScholarship(structures::UnsortedSequenceTable<std::wstring, int>* scholarship)
	{
		if (scholarship_ == nullptr) {
			scholarship_ = scholarship;
		}
	}

	inline void UzemnaJednotka::addSubUnit(UzemnaJednotka* subUnit)
	{
		subUnits_->add(subUnit);
	}
}