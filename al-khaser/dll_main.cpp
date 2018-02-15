#include "dll_main.h"
#include "Shared\Main.h"
#include <algorithm>
#include <functional>

namespace AlKhaser
{
	Detector *Detector::m_self = nullptr;

	bool Detector::Check()
	{
		if (m_self == nullptr)
		{
			m_self = new Detector();
		}
		return m_self->RunCheck();
	}

	Detector::Detector()
	{
		checkers.assign({
			&IsDebuggerPresentAPI,
			&IsDebuggerPresentPEB,
			&CheckRemoteDebuggerPresentAPI
		});
	}

	Detector::~Detector()
	{
	}

	bool Detector::RunCheck()
	{
		bool isFail = false;

		std::for_each(checkers.begin(), checkers.end(), [&isFail](int(*callback)()) {
			int result = callback();
			printf("checker result: %i\n", result);
			if (result)
			{
				isFail = true;
				return;
			}
		});

		return isFail;
	}
}
