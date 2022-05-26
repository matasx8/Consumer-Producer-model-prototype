#pragma once
#include <string>
#include <chrono>

namespace Utils
{
	struct AutoTimeLog
	{
		AutoTimeLog(std::string name);
		void StopAndPrint();

	private:
		std::string testname;
		std::chrono::steady_clock::time_point start;
	};
};

