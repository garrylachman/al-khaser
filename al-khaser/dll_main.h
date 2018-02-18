#pragma once

/*#ifdef ALKHASER_EXPORTS  
#define ALKHASER_API __declspec(dllexport)   
#else  
#define ALKHASER_API __declspec(dllimport)   
#endif*/

#include <stdio.h>
#include <vector>

namespace AlKhaser {
	//class ALKHASER_API Detector
	class Detector
	{
	public:
		static enum CHECKERS {
			ANALYSIS = 0,
			DEBUG,
			DUMP,
			VM,
			ALL
		} CTYPE;

		static int Check(Detector::CHECKERS _checker);
		Detector();
		~Detector();
		int RunCheck(std::vector<int(*)()> list);

	private:
		std::vector<int(*)()> checkers_AntiAnalysis;
		std::vector<int(*)()> checkers_AntiDebug;
		std::vector<int(*)()> checkers_AntiDump;
		std::vector<int(*)()> checkers_AntiVM;
		static Detector *m_self;
	};
}