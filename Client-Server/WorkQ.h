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
		inline WorkQ() :m_Mutex(), m_CV(), m_Q()
		{
		}

		inline void add(T item) {
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_Q.push_back(item);
			m_CV.notify_one();
		}

		inline T remove() {
			std::unique_lock<std::mutex> lock(m_Mutex);
			if (m_Q.size() == 0)
				m_CV.wait(lock);

			T item = m_Q.front();
			m_Q.pop_front();
			return item;
		}

		inline size_t size() {
			std::unique_lock<std::mutex> lock(m_Mutex);
			return m_Q.size();
		}
	protected:
		std::mutex m_Mutex;
		std::condition_variable m_CV;
		std::list<T> m_Q;
	};
}

