#pragma once
#include "typ_uj.h"
#include <string>

namespace uj
{
	class Conversion
	{
	public:
		static Conversion& getInstance();
	public:
		std::wstring toString(TypUzemJednotka uj);
	private:
		Conversion() = default;
		Conversion(const Conversion&) = delete;
	};


	inline Conversion& Conversion::getInstance()
	{
		static Conversion instance;
		return instance;
	}

	inline std::wstring Conversion::toString(TypUzemJednotka uj)
	{
		switch (uj) {
			case TypUzemJednotka::OBEC:
				return L"obec";
			case TypUzemJednotka::OKRES:
				return L"okres";
			case TypUzemJednotka::KRAJ:
				return L"kraj";
			case TypUzemJednotka::STAT:
				return L"stat";
		}
	}
}