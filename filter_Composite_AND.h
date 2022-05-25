#pragma once
#include "filter_Composite.h"

namespace filter
{
	template<typename K, typename Object>
	class FilterCompositeAND : public FilterComposite<K, Object>
	{
	public:
		bool pass(const Object& o) override;
	};

	template<typename K, typename Object>
	inline bool FilterCompositeAND<K, Object>::pass(const Object& o)
	{
		int passed = 0;
		for (auto filter : filters_) {
			if (filter->pass(o)) {
				passed++
			}
		}

		passed == filters_.size() ? return true : return false;
	}
}