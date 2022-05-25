#pragma once
#include <string>
#include "criterion.h"
#include "uzemna_jednotka.h"
#include "typ_uj.h"

namespace crits
{
	template<typename Result>
	class CriterionUj : public Criterion<uj::UzemnaJednotka, Result>
	{
	};
}