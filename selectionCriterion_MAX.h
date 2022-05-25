#pragma once
#include "selectionCriterion.h"

namespace scrits
{
	template<typename K, typename Object, typename Value>
	class SelectionCriterionMAX : public SelectionCriterion<K, Object, Value>
	{
	public:
		SelectionCriterionMAX(crits::Criterion<Object, Value>* criterion);
	protected:
		bool isTestedValueBest(Value bestNow, Value bestTested);
	};

	template<typename K, typename Object, typename Value>
	inline SelectionCriterionMAX<K, Object, Value>::SelectionCriterionMAX(crits::Criterion<Object, Value>* criterion) :
		SelectionCriterion<K, Object, Value>(criterion)
	{
	}

	template<typename K, typename Object, typename Value>
	inline bool SelectionCriterionMAX<K, Object, Value>::isTestedValueBest(Value bestNow, Value bestTested)
	{
		return bestTested > bestNow;
	}
}