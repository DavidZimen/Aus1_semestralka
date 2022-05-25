#pragma once
#include "criterion_UJ_Nazov.h"
#include "filter_Criterion_Value.h"

namespace filter
{
	class FilterUJNazov : public FilterCriterionValue<std::wstring, uj::UzemnaJednotka, std::wstring>
	{
	public:
		FilterUJNazov(std::wstring nazov);
	};

	inline FilterUJNazov::FilterUJNazov(std::wstring nazov) :
		FilterCriterionValue<std::wstring, uj::UzemnaJednotka, std::wstring>(new crits::CriterionUJNazov(), nazov)
	{
	}
}