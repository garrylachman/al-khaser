#pragma once

#ifdef ALKHASER_EXPORTS  
#define ALKHASER_API __declspec(dllexport)   
#else  
#define ALKHASER_API __declspec(dllimport)   
#endif

#include <stdio.h>
#include <vector>

namespace AlKhaser {
	class ALKHASER_API Detector
	{
	public:
		static bool Check();

	private:
		Detector();
		~Detector();
		bool RunCheck(std::vector<int(*)()> list);

		std::vector<int(*)()> checkers_AntiAnalysis;
		std::vector<int(*)()> checkers_AntiDebug;
		std::vector<int(*)()> checkers_AntiDump;
		std::vector<int(*)()> checkers_AntiVM;
		std::vector<int(*)()> checkers_AntiInjection;
		std::vector<int(*)()> checkers_AntiTiminngAttacks;
		static Detector *m_self;
	};
}