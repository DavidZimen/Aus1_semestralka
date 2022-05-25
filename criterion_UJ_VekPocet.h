#pragma once
#include "criterion_UJ.h"

namespace crits
{
	class CriterionUJVekPocet : public CriterionUj<int>
	{
	private:
		int vek_;
		std::wstring pohlavie_;
	public:
		CriterionUJVekPocet(int vek, std::wstring pohlavie);
		int evaluate(uj::UzemnaJednotka& o);
	};

	inline CriterionUJVekPocet::CriterionUJVekPocet(int vek, std::wstring pohlavie) :
		vek_(vek),
		pohlavie_(pohlavie)
	{
	}

	inline int CriterionUJVekPocet::evaluate(uj::UzemnaJednotka& o)
	{
		return o.pocetObyvatelovSDanymVekomAPohlavim(vek_, pohlavie_);
	}
}