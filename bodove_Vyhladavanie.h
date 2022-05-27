#pragma once
#include "funcionality.h"
#include "criterion_UJ_Nazov.h"

namespace func
{
	class BodoveVyhladavanie : public Funcionality
	{
	public:
		void spusti(uj::Stat* stat) override;
	private:
		void getUJ(std::wstring& uj);
		structures::SequenceTable<std::wstring, uj::UzemnaJednotka*>* getTab(uj::Stat* stat, int moznost) override;
	};

	inline void BodoveVyhladavanie::spusti(uj::Stat* stat)
	{
		//crits::CriterionUJNazov critNazov;

		crits::CriterionUJNazov* crit = new crits::CriterionUJNazov();

		auto tab = Funcionality::zvolUroven(stat);

		std::wstring nazov;
		getUJ(nazov);

		while (nazov != L"K" || nazov != L"k") {
			if (nazov == L"K" || nazov == L"k") {
				break;
			}

			try {
				auto uj = tab->find(nazov);
				if (nazov == crit->evaluate(*uj)) {
					uj->vypis();
				}
				getUJ(nazov);
			}
			catch (const std::logic_error&) {
				std::wcout << L"Nenach�dza sa v tabu�ke." << std::endl;
				getUJ(nazov);
			}
		}

		delete crit;
	}

	inline void BodoveVyhladavanie::getUJ(std::wstring& uj)
	{
		std::wcout << '\n';
		std::wcout << L"�zemn� jednotka: ";
		std::getline(std::wcin, uj);
	}
	inline structures::SequenceTable<std::wstring, uj::UzemnaJednotka*>* BodoveVyhladavanie::getTab(uj::Stat* stat, int moznost)
	{
		switch (moznost) {
		case OBEC_MOZNOST:
			return stat->getObce();
		case OKRES_MOZNOST:
			return stat->getOkresy();
		case KRAJ_MOZNOST:
			return stat->getKraje();
		default:
			return nullptr;
		}
	}
}