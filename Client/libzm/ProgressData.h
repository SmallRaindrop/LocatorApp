#ifndef __ProgressData_h_
#define __ProgressData_h_

#include <string>
using namespace std;

class CProgressData
{
public:
	CProgressData() : m_nRange(0),m_nPos(0),m_sInfo(""){}
	virtual ~CProgressData(){}

	inline void setRange(int range){ m_nRange = range; }
	inline void setPos(int pos){ m_nPos = pos; }
	inline void setInfo(const string& info){ m_sInfo = info; }

	inline int		getRange(){ return m_nRange; }
	inline int		getPos(){ return m_nPos; }
	inline string	getInfo(){ return m_sInfo; }
	inline float	getProgress(){ return getRange()>0?(float)getPos()/(float)getRange()*100.0f:0; }

	inline void		reset(){ m_nRange=0;m_nPos=0;m_sInfo = "";}
	
protected:
	int		m_nRange;
	int		m_nPos;
	string	m_sInfo;
};

#endif