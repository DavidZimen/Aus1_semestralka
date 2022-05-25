#pragma once
#include "criterion_UJ_Nazov.h"
#include "filter_Criterion_Value.h"

namespace filter
{
	template<typename K>
	class FilterUJNazov : public FilterCriterionValue<K, uj::UzemnaJednotka, std::wstring>
	{
	public:
		FilterUJNazov(std::wstring nazov);
	};

	template<typename K>
	inline FilterUJNazov<K>::FilterUJNazov(std::wstring nazov) :
		FilterCriterionValue<std::wstring, uj::UzemnaJednotka, std::wstring>(new crits::CriterionUJNazov(), nazov)
	{
	}
}