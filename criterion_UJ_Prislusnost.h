#pragma once
#include "criterion_UJ.h"

namespace crits
{
	class CriterionUJPrislusnost : public CriterionUj<bool>
	{
	private:
		std::wstring vyssiCelok_;
	public:
		CriterionUJPrislusnost(std::wstring vyssiCelok);
		bool evaluate(uj::UzemnaJednotka& o);
	};

	inline CriterionUJPrislusnost::CriterionUJPrislusnost(std::wstring vyssiCelok) :
		vyssiCelok_(vyssiCelok)
	{
	}
	inline bool CriterionUJPrislusnost::evaluate(uj::UzemnaJednotka& o)
	{
		return o.patriDoVyssiehoCelku(vyssiCelok_);
	}
}