#pragma once
#include "criterion.h"
#include "../SemestralnaPraca_Zimen/structures/table/table.h"
#include "../SemestralnaPraca_Zimen/structures/table/unsorted_sequence_table.h"

namespace scrits
{
	template<typename K, typename Object, typename Value>
	class SelectionCriterion
	{
	private:
		crits::Criterion<Object, Value>* criterion_;
		Value bestValue_;
		Object* bestObject_;
		K bestObjectKey_;
	public:
		SelectionCriterion(crits::Criterion<Object, Value>* criterion, Value bestValue);
		~SelectionCriterion();
		structures::UnsortedSequenceTable<K, Object*>* selectBest(structures::Table<K, Object*>* tab);
		crits::Criterion<Object, Value>* getCriterion();
	protected:
		virtual bool isTestedValueBest(Value bestNow, Value bestTested) = 0;
	};

	template<typename K, typename Object, typename Value>
	inline SelectionCriterion<K, Object, Value>::SelectionCriterion(crits::Criterion<Object, Value>* criterion, Value bestValue) :
		criterion_(criterion),
		bestValue_(bestValue)
	{
	}

	template<typename K, typename Object, typename Value>
	inline SelectionCriterion<K, Object, Value>::~SelectionCriterion()
	{
		delete criterion_;
		criterion_ = nullptr;
	}

	template<typename K, typename Object, typename Value>
	inline structures::UnsortedSequenceTable<K, Object*>* SelectionCriterion<K, Object, Value>::selectBest(structures::Table<K, Object*>* tab)
	{
		Object* testedO = nullptr;
		Value testedV;

		for (auto item : *tab) {
			testedO = item->accessData();
			testedV = criterion_->evaluate(*testedO);
			if (isTestedValueBest(bestValue_, testedV)) {
				bestValue_ = testedV;
				bestObject_ = testedO;
				bestObjectKey_ = item->getKey();
			}
		}

		auto table = new structures::UnsortedSequenceTable<K, Object*>();
		table->insert(bestObjectKey_, bestObject_);

		return table;
	}

	template<typename K, typename Object, typename Value>
	inline crits::Criterion<Object, Value>* SelectionCriterion<K, Object, Value>::getCriterion()
	{
		return criterion_;
	}
}