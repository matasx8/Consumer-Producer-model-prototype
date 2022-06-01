#pragma once
#include "WorkQ.h"

namespace prl
{
	template <typename T, typename F> class WorkQ_ST : WorkQ<T>
	{
	public:
		WorkQ_ST(F& functionOwner)
			: WorkQ<T>(), m_FunctionOwner(functionOwner)

		inline void add(T item) override {
			item(m_FunctionOwner);
		}

		inline T remove() override {} // delete?

		inline size_t size() override{
			return this->m_Q.size();
		}
	private:
		F& m_FunctionOwner;
	};
}