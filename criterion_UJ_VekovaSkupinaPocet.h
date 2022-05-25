#pragma once
#include "criterion_UJ.h"

namespace crits
{
	class CriterionUJVekovaSkupinaPocet : public CriterionUj<int>
	{
	private:
		std::wstring vekSkupina_;
	public:
		CriterionUJVekovaSkupinaPocet(std::wstring vekSkupina);
		int evaluate(uj::UzemnaJednotka& o);
	};

	inline CriterionUJVekovaSkupinaPocet::CriterionUJVekovaSkupinaPocet(std::wstring vekSkupina) :
		vekSkupina_(vekSkupina)
	{
	}

	inline int CriterionUJVekovaSkupinaPocet::evaluate(uj::UzemnaJednotka& o)
	{
		return o.pocetObyvatelovVDanejVekovejSkupine(vekSkupina_);
	}
}