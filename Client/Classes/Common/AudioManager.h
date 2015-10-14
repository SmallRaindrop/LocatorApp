#ifndef __AudioManager_h_
#define __AudioManager_h_

#include "GameDef.h"
#include "AudioPlayer.h"
#include "Singleton.h"

typedef map<string,AudioPlayer*> AudioPlayers;

class AudioManager : public Singleton_Auto<AudioManager>
{
public:
	AudioManager();
	~AudioManager();

	AudioPlayer* Load(const string& key);
	void Play(const int& id,bool once = true);
	void Stop(const int& id);
	void Pause(const int& id);
	void Play(const string& file,bool once);
	void Stop(const string& file);
	void Pause(const string& file);

	void StopAll();
	void PauseAll();
	void ResumeAll();

	void Clear();

protected:
	AudioPlayers m_AudioPlayers;
};

#define gAudio AudioManager::Instance()

#endif //__AudioManager_h_