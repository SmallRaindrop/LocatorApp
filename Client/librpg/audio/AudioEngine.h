#ifndef __AudioEngine_h_
#define __AudioEngine_h_

#include "AudioPlayer.h"
#include "AL\alc.h"
#include "AudioDecoder.h"

class AudioEngine
{
public:
	AudioEngine();
	~AudioEngine();

	static AudioEngine* GetInterface();

	bool Initialize();
	void Destory();

	AudioPlayer*	GetAudioPlayer(const char* file);
	AudioPlayer*	GetAudioPlayer(const unsigned char* buffer,size_t len);
	AudioDecoder*	GetAudioDecoder();

private:
	ALCdevice*	m_pALCDevice;
	ALCcontext*	m_pALCContext;
};

#endif // __AudioEngine_h_