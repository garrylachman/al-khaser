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
		bool RunCheck();

		std::vector<int(*)()> checkers;
		static Detector *m_self;
	};
}