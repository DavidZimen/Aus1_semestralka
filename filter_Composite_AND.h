#pragma once
#include "filter_Composite.h"

namespace filter
{
	template<typename K, typename Object>
	class FilterCompositeAND : public FilterComposite<K, Object>
	{
	public:
		bool pass(Object& o) override;
	};

	template<typename K, typename Object>
	inline bool FilterCompositeAND<K, Object>::pass(Object& o)
	{
		int passed = 0;
		for (auto filter : *FilterComposite<K, Object>::filters_) {
			if (filter->pass(o)) {
				passed++;
			}
		}

		if (passed == FilterComposite<K, Object>::filters_->size()) {
			return true;
		}
		else {
			return false;
		}
	}
}