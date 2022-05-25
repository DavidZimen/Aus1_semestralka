#pragma once
#include "criterion_UJ.h"
#include "criterion_UJ_VzdelaniePocet.h"

namespace crits
{
	class CriterionUJVzdelaniePodiel : public CriterionUj<double>
	{
	private:
		std::wstring vzdelanie_;
	public:
		CriterionUJVzdelaniePodiel(std::wstring vzdelanie);
		double evaluate(uj::UzemnaJednotka& o);
	};

	inline CriterionUJVzdelaniePodiel::CriterionUJVzdelaniePodiel(std::wstring vzdelanie) :
		vzdelanie_(vzdelanie)
	{
	}
	inline double CriterionUJVzdelaniePodiel::evaluate(uj::UzemnaJednotka& o)
	{
		return 100.0 * (static_cast<double>(CriterionUJVzdelaniePocet(vzdelanie_).evaluate(o)) / static_cast<double>(o.getPocetObyvatelov()));
	}
}