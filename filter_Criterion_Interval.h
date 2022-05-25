#pragma once
#include "filter_Criterion.h"

namespace filter
{
	template<typename K, typename Object, typename Value>
	class FilterCriterionInterval : public FilterCriterion<K, Object, Value>
	{
	private:
		Value vFrom_;
		Value vTo_;
	public:
		FilterCriterionInterval(crits::Criterion<Object, Value>* criterion, Value vFrom, Value vTo);
	protected:
		bool passFilter(Value v) override;
	};

	template<typename K, typename Object, typename Value>
	inline FilterCriterionInterval<K, Object, Value>::FilterCriterionInterval(crits::Criterion<Object, Value>* criterion, Value vFrom, Value vTo) :
		FilterCriterion<K, Object, Value>(criterion),
		vFrom_(vFrom),
		vTo_(vTo)
	{
	}

	template<typename K, typename Object, typename Value>
	inline bool FilterCriterionInterval<K, Object, Value>::passFilter(Value v)
	{
		return v >= vFrom_ && v <= vTo_;
	}
}