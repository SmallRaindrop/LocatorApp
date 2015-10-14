#ifndef __AudioDecoder_h_
#define __AudioDecoder_h_

#include <commonRef.h>
#include <stdio.h>
#include <string>

#include "AL/al.h"

#ifdef _WIN32
#include "win32/mpg123.h"
#else
#include "android/mpg123.h"
#endif

class AudioDecoder
{
public:
	AudioDecoder();
	virtual ~AudioDecoder();

	virtual void	Clear();
	virtual bool	Decode(const unsigned char* buffer,int len) = 0;
	

	inline ALsizei	GetDataSize(){ return m_iSize; };
	inline ALsizei	GetFreq(){ return m_iFreq; }
	inline unsigned char*	GetData(){ return m_pData; };
	inline ALenum	GetFormat(){ return m_eFormat; }

protected:
	virtual long	PushData(const unsigned char* data,int size);

protected:
	ALsizei m_iSize;
	ALsizei m_iFreq;
	unsigned char* m_pData;
	ALenum	m_eFormat;
};

class AudioDecoder_WAV : public AudioDecoder
{
public:
	AudioDecoder_WAV();
	~AudioDecoder_WAV();

	bool Decode(const unsigned char* inmemory,int inmemsize);

protected:
	void SetInfo(long rate,int channels,int encoding);
};

#endif // __AudioDecoder_h_