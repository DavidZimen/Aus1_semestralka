#pragma once
#include "../SemestralnaPraca_Zimen/structures/table/unsorted_sequence_table.h"
#include "../SemestralnaPraca_Zimen/structures/table/table.h"

namespace filter
{
	template<typename K, typename Object>
	class Filter
	{
	public:
		virtual ~Filter() {};
		virtual bool pass(Object& o) = 0;
		void filterTable(structures::Table<K, Object*>* inTab, structures::UnsortedSequenceTable<K, Object*>* filteredTab);
	};

	template<typename K, typename Object>
	inline void Filter<K, Object>::filterTable(structures::Table<K, Object*>* inTab, structures::UnsortedSequenceTable<K, Object*>* filteredTab)
	{
		for (auto item : *inTab) {
			if (pass(*(item->accessData()))) {
				filteredTab->insert(item->getKey(), item->accessData());
			}
		}
	}
}