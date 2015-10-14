#pragma once

// 角色，特效工厂；处理异步加载；
template <class T>
class NotifyCenter
{
public:
	NotifyCenter(){ }
	~NotifyCenter(){ }
	void registerElement(int msg,T* element)
	{
		if( element )
		{
			m_vElements.push_back(make_pair(msg,element));
		}
	}

	void eraseElement(T* element)
	{
		for (typename vector<pair<int,T*>>::iterator itr = m_vElements.begin();itr != m_vElements.end(); )
		{
			if ( itr->second == element )
			{
				itr = m_vElements.erase(itr);
			}
			else
			{
				++itr;
			}
		}
	}

	void postNotify(int msg)
	{
		for (typename vector<pair<int,T*>>::iterator itr = m_vElements.begin();itr != m_vElements.end(); )
		{
			if ( itr->first == msg )
			{
				itr->second->onNotifyCenter(msg);
				itr = m_vElements.erase(itr);
			}
			else
			{
				++itr;
			}
		}
	}

	void postNotifyAll()
	{
		for (typename vector<pair<int,T*>>::iterator itr = m_vElements.begin();itr != m_vElements.end();++itr )
		{
			itr->second->onNotifyCenter(itr->first);
		}
		m_vElements.clear();
	}

protected:
	vector<pair<int,T*>>	m_vElements;
};