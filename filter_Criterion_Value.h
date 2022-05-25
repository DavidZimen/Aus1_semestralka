#pragma once
#include "filter_Criterion.h"
#include "uzemna_jednotka.h"

namespace filter
{
	template<typename K, typename Object, typename Value>
	class FilterCriterionValue : public FilterCriterion<K, Object, Value>
	{
	private:
		Value value_;
	public:
		FilterCriterionValue(crits::Criterion<Object, Value>* criterion, Value value);
	protected:
		bool passFilter(Value v) override;
	};

	template<typename K, typename Object, typename Value>
	inline FilterCriterionValue<K, Object, Value>::FilterCriterionValue(crits::Criterion<Object, Value>* criterion, Value value) :
		FilterCriterion<K, Object, Value>(criterion),
		value_(value)
	{
	}

	template<typename K, typename Object, typename Value>
	inline bool FilterCriterionValue<K, Object, Value>::passFilter(Value v)
	{
		return v == value_;
	}
}