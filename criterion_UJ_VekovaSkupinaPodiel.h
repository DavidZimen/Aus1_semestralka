#pragma once
#include "criterion_UJ.h"
#include "criterion_UJ_VekovaSkupinaPocet.h"

namespace crits
{
	class CriterionUJVekovaSkupinaPodiel : public CriterionUj<double>
	{
	private:
		std::wstring vekSkupina_;
	public:
		CriterionUJVekovaSkupinaPodiel(std::wstring vekSkupina);
		double evaluate(uj::UzemnaJednotka& o);
	};

	inline CriterionUJVekovaSkupinaPodiel::CriterionUJVekovaSkupinaPodiel(std::wstring vekSkupina) :
		vekSkupina_(vekSkupina)
	{
	}

	inline double CriterionUJVekovaSkupinaPodiel::evaluate(uj::UzemnaJednotka& o)
	{
		return 100.0 * (static_cast<double>(CriterionUJVekovaSkupinaPocet(vekSkupina_).evaluate(o)) / static_cast<double>(o.getPocetObyvatelov()));
	}
}