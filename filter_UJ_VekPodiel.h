#pragma once
#include "criterion_UJ_VekPodiel.h"
#include "filter_Criterion_Interval.h"

namespace filter
{
	class FilterUJVekPodiel : public FilterCriterionInterval<std::wstring, uj::UzemnaJednotka, double>
	{
	public:
		FilterUJVekPodiel(int vek, std::wstring pohlavie, double vFrom, double vTo);
	};

	inline FilterUJVekPodiel::FilterUJVekPodiel(int vek, std::wstring pohlavie, double vFrom, double vTo) :
		FilterCriterionInterval<std::wstring, uj::UzemnaJednotka, double>(new crits::CriterionUJVekPodiel(vek, pohlavie), vFrom, vTo)
	{
	}
}

