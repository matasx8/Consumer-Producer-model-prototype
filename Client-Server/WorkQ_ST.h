#pragma once
#include "WorkQ.h"

namespace prl
{
	template <typename T> class WorkQ_ST : public WorkQ<T>
	{
	public:
		WorkQ_ST(T& functionOwner)
			: WorkQ<T>(), m_FunctionOwner(functionOwner)
		{}

		inline void add(std::_Mem_fn<void (T::*)()> item) override {
			item(m_FunctionOwner);
		}

		inline size_t size() override{
			return this->m_Q.size();
		}
	private:
		T& m_FunctionOwner;
	};
}