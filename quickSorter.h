#pragma once
#include "criterion.h"
#include "../SemestralnaPraca_Zimen/structures/table/unsorted_sequence_table.h"

namespace sort
{
	template<typename K, typename Object, typename Value>
	class QuickSorter
	{
	private:
		bool asc_;
		crits::Criterion<Object, Value>* criterion_;
	public:
		QuickSorter();
		~QuickSorter();
		void sort(structures::UnsortedSequenceTable<K, Object*>& tab, crits::Criterion<Object, Value>& criterion, bool vzostupne);
	private:
		void sortTable(structures::UnsortedSequenceTable<K, Object*>& tab);
		void quick(int min, int max, structures::UnsortedSequenceTable<K, Object*>& tab);
	};

	template<typename K, typename Object, typename Value>
	inline QuickSorter<K, Object, Value>::QuickSorter() :
		asc_(true),
		criterion_(nullptr)
	{
	}

	template<typename K, typename Object, typename Value>
	inline QuickSorter<K, Object, Value>::~QuickSorter()
	{
	}

	template<typename K, typename Object, typename Value>
	inline void QuickSorter<K, Object, Value>::sort(structures::UnsortedSequenceTable<K, Object*>& tab, crits::Criterion<Object, Value>& criterion, bool vzostupne)
	{
		criterion_ = &criterion;
		asc_ = vzostupne;
		sortTable(tab);
	}

	template<typename K, typename Object, typename Value>
	inline void QuickSorter<K, Object, Value>::sortTable(structures::UnsortedSequenceTable<K, Object*>& tab)
	{
		quick(0, tab.size() - 1, tab);
	}

	template<typename K, typename Object, typename Value>
	inline void QuickSorter<K, Object, Value>::quick(int min, int max, structures::UnsortedSequenceTable<K, Object*>& tab)
	{
		Value pivot = criterion_->evaluate(*(tab.getItemAtIndex((min + max) / 2).accessData()));
		int left = min;
		int right = max;

		do {
			if (asc_) {
				while (criterion_->evaluate(*(tab.getItemAtIndex(left).accessData())) < pivot) {
					left++;
				}

				while (criterion_->evaluate(*(tab.getItemAtIndex(right).accessData())) > pivot) {
					right--;
				}
			}
			else {
				while (criterion_->evaluate(*(tab.getItemAtIndex(left).accessData())) > pivot) {
					left++;
				}

				while (criterion_->evaluate(*(tab.getItemAtIndex(right).accessData())) < pivot) {
					right--;
				}
			}


			if (left <= right) {
				tab.swap(left, right);
				left++;
				right--;
			}

		} while (left <= right);

		if (min < right) {
			quick(min, right, tab);
		}

		if (left < max) {
			quick(left, max, tab);
		}
	}
}