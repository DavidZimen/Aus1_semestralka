#pragma once
#include "criterion_UJ.h"

namespace crits
{
	class CriterionUJVzdelaniePocet : public CriterionUj<int>
	{
	private:
		std::wstring vzdelanie_;
	public:
		CriterionUJVzdelaniePocet(std::wstring vzdelanie);
		int evaluate(uj::UzemnaJednotka& o);
	};

	inline CriterionUJVzdelaniePocet::CriterionUJVzdelaniePocet(std::wstring vzdelanie) :
		vzdelanie_(vzdelanie)
	{
	}
	inline int CriterionUJVzdelaniePocet::evaluate(uj::UzemnaJednotka& o)
	{
		return o.pocetObyvatelovSoVzdelanim(vzdelanie_);
	}
}