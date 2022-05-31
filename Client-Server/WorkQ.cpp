#include "WorkQ.h"

namespace prl
{
	template<typename T>
	WorkQ<T>::WorkQ()
		:m_Mutex(), m_CV(), m_Q()
	{
	}

	template<typename T>
	void WorkQ<T>::add(T item)
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		m_Q.push_back(item);
		m_CV.notify_one();
	}

	template<typename T>
	T WorkQ<T>::remove()
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		if (m_Q.size() == 0)
			m_CV.wait(lock);

		T item = m_Q.front();
		m_Q.pop_front();
		return item;
	}

	template<typename T>
	size_t WorkQ<T>::size()
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		return m_Q.size();
	}
}