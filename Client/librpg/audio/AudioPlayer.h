#ifndef __AudioPlayer_h_
#define __AudioPlayer_h_

#include "AL\al.h"

enum AudioPlayerState
{
	APS_None,
	APS_Playing,
	APS_Paused,
};

class AudioPlayer
{
public:
	AudioPlayer();
	virtual ~AudioPlayer();

	virtual bool Load(const char* file);
	virtual bool Load(const unsigned char* buffer,int len);
	virtual void Loop(bool loop = true);
	virtual void Play();
	virtual void Stop();
	virtual void Pause();
	virtual void Release();

	inline bool IsPaused(){ return m_ALState == APS_Paused; }
	inline bool IsPlayeing(){ return m_ALState == APS_Playing; }

private:
	ALuint m_ALSource;
	ALuint m_ALBuffer;
	ALuint m_ALState;
};

#endif // __AudioPlayer_h_