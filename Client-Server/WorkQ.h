#pragma once
#include <functional>
#include <vector>
#include <list>
#include <mutex>

namespace prl
{
	template <typename T> class WorkQ
	{
	public:
		WorkQ();

		void add(T item);
		T remove();

		size_t size();
	private:
		std::mutex m_Mutex;
		std::condition_variable m_CV;
		std::list<T> m_Q;
	};
}

