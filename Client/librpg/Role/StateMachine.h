#ifndef __StateMachine_h_
#define __StateMachine_h_

struct IStateEvent
{
	IStateEvent(int type) : _type(type){}
	virtual ~IStateEvent(){}

	int _type;
};

template <class T>
class IState
{
public:
	IState(int id) : m_nStateID(id){}
	virtual ~IState(){}

	virtual void OnEnter(T* pTarget) = 0;
	virtual void OnLeave(T* pTarget) = 0;
	virtual void OnTimer(T* pTarget,float dt) = 0;
	virtual void OnEvent(T* pTarget,IStateEvent* event) = 0;

	inline int GetStateID(){ return m_nStateID; }

protected:
	int		m_nStateID;
};

template <class T>
class IStateSet
{
public:
	inline void	AddState(IState<T>* pState){ m_States.push_back(pState); }
	IState<T>*	GetState(int stateID);
	void		Clear();
protected:
	vector<IState<T>*>	m_States;
};

template <class T>
IState<T>* IStateSet<T>::GetState(int stateID)
{
	for ( size_t i=0;i<m_States.size();++i )
	{
		IState<T>* pState = m_States[i];
		if ( pState && pState->GetStateID() == stateID )
		{
			return pState;
		}
	}

	return NULL;
}

template <class T>
void IStateSet<T>::Clear()
{
	for ( size_t i=0;i<m_States.size();++i )
	{
		IState<T>* pState = m_States[i];
		if ( pState )
		{
			delete pState;
		}
	}

	m_States.clear();
}

template<class T>
class StateMachine
{
public:
	StateMachine(T* pTarget) : m_pTarget(pTarget),m_pCurrState(NULL){ m_vStateFlags.resize(4); ClrStateFlag(); }
	virtual ~StateMachine(){ m_SSet.Clear(); }
	// ×´Ì¬»ú
public:
	virtual void EnterState(int stateID);
	virtual void LeaveState();

	virtual void Update(float dt);

	virtual void PushEvent(IStateEvent* event);
	virtual void ClearEvent();

	inline void SetStateFlag(int flag){ m_vStateFlags[flag / 8] |= (1 << (flag % 8)); }
	inline bool HasStateFlag(int flag){ return (m_vStateFlags[flag / 8] & (1 << (flag % 8))) != 0; }
	inline void ClrStateFlag(int flag){ m_vStateFlags[flag / 8] &= ~(1 << (flag % 8)); }
	inline void ClrStateFlag()
	{ 
		for (size_t i = 0; i < m_vStateFlags.size(); i++)
		{
			m_vStateFlags[i] = 0;
		}
	}

	inline void			InsertState(IState<T>* pState){ m_SSet.AddState(pState); }
	inline IState<T>*	GetCurrState(){ return m_pCurrState; }
	inline int			GetCurrStateID(){ return m_pCurrState?m_pCurrState->GetStateID():0; }
	
protected:
	T*				m_pTarget;
	IState<T>*		m_pCurrState;
	IStateSet<T>	m_SSet;
	vector<int>		m_vStateFlags;
	queue<IStateEvent*> m_queEvents;
};

template<class T>
void StateMachine<T>::EnterState(int stateID)
{
	LeaveState();

	IState<T>* pState = m_SSet.GetState(stateID);
	if ( pState )
	{
		m_pCurrState = pState;
		pState->OnEnter(m_pTarget);
	}
}

template<class T>
void StateMachine<T>::LeaveState()
{
	if ( m_pCurrState )
	{
		m_pCurrState->OnLeave(m_pTarget);
	}

	m_pCurrState = NULL;
}

template<class T>
void StateMachine<T>::Update(float dt)
{
	if ( m_pCurrState )
	{
		m_pCurrState->OnTimer(m_pTarget,dt);
	}

	while (m_queEvents.size() > 0)
	{
		IStateEvent *event = m_queEvents.front();
		m_queEvents.pop();

		//_ignoreFrameEvent = true;

		if( m_pCurrState )
		{
			m_pCurrState->OnEvent(m_pTarget,event);
		}

		//_ignoreFrameEvent = false;

		CC_SAFE_DELETE(event);
	}
}

template<class T>
void StateMachine<T>::PushEvent(IStateEvent* event)
{
	m_queEvents.push(event);
}

template<class T>
void StateMachine<T>::ClearEvent()
{
	while (m_queEvents.size() > 0)
	{
		IStateEvent *event = m_queEvents.front();
		m_queEvents.pop();

		CC_SAFE_DELETE(event);
	}
}

#endif	// __StateMachine_h_