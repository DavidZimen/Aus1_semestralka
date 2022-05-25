#pragma once
#include "criterion_UJ.h"
#include "criterion_UJ_VekPocet.h"

namespace crits
{
	class CriterionUJVekPodiel : public CriterionUj<double>
	{
	private:
		int vek_;
		std::wstring pohlavie_;
	public:
		CriterionUJVekPodiel(int vek, std::wstring pohlavie);
		double evaluate(uj::UzemnaJednotka& o);
	};

	inline CriterionUJVekPodiel::CriterionUJVekPodiel(int vek, std::wstring pohlavie) :
		vek_(vek),
		pohlavie_(pohlavie)
	{
	}

	inline double CriterionUJVekPodiel::evaluate(uj::UzemnaJednotka& o)
	{
		return 100.0 * (static_cast<double>(CriterionUJVekPocet(vek_, pohlavie_).evaluate(o)) / static_cast<double>(o.getPocetObyvatelov()));
	}
}