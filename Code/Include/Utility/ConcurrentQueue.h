#pragma once

// https://www.justsoftwaresolutions.co.uk/threading/implementing-a-thread-safe-queue-using-condition-variables.html

#include <condition_variable>
#include <mutex>
#include <queue>

BEGIN_NAMESPACE(Utility)

template<typename TYPE>
class ConcurrentQueue
{
public:
	void Push(const TYPE &a_Element)
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		m_Queue.push(a_Element);
		lock.unlock();
		m_ConditionVariable.notify_one();
	}

	TYPE& Front()
	{
		return m_Queue.front();
	}

	const TYPE& Front() const
	{
		return m_Queue.front();
	}

	bool Empty() const
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		return m_Queue.empty();
	}

	
	bool Pop(TYPE &a_PoppedValue)
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		bool result = false;
		if (!m_Queue.empty())
		{
			a_PoppedValue = m_Queue.front();
			m_Queue.pop();
			result = true;
		}
		return result;
	}

	void WaitAndPop(TYPE &a_PoppedValue)
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		while (m_Queue.empty())
		{
			m_ConditionVariable.wait(lock);
		}
		a_PoppedValue = m_Queue.front();
		m_Queue.pop();
	}

private:
	std::queue<TYPE> m_Queue;
	mutable std::mutex m_Mutex;
	std::condition_variable m_ConditionVariable;
};

END_NAMESPACE(Utility)
