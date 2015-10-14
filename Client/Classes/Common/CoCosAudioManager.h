#ifndef __CoCosAudioManager_h_
#define __CoCosAudioManager_h_

#include "GameDef.h"
#include "Singleton.h"

class CoCosAudioManager : public Singleton_Auto<CoCosAudioManager>
{
public:
	CoCosAudioManager();
	~CoCosAudioManager();

	void				SetMusicEnable(bool enable);
	void				SetEffectEnable(bool enable);

	/* Name		：PlayMusic
	 * Author	：PengLongHua
	 * Date		: 2015-07-13
	 * Desc		: 播放背景音乐,支持格式如下:Android(MP3、WAV和3GP),iOS(MP3和CAF),Win32(MID和WAV)
	 * Param	: path 音乐路径 loop 是否循环
	 * Return	: none
	 */
	void PlayMusic(std::string path, bool loop);

	/* Name		：PlayEffect
	 * Author	：PengLongHua
	 * Date		: 2015-07-13
	 * Desc		: 播放音效,支持格式 Android(OGG,WAV),iOS(CAF),Win32(MID和WAV)
	 * Param	: id 配置id
	 * Return	: none
	 */
	void PlayEffect(int id);

	/* Name		：SetMusicVolume
	 * Author	：PengLongHua
	 * Date		: 2015-07-13
	 * Desc		: 设置背景音乐音量 
	 * Param	: volume 音量 值范围 0.0-1.0
	 * Return	: none
	 */
	void SetMusicVolume(float volume);

	/* Name		：SetEffectVolume
	 * Author	：PengLongHua
	 * Date		: 2015-07-13
	 * Desc		: 设置音效音量
	 * Param	: volume 音量 值范围 0.0-1.0
	 * Return	: none
	 */
	void SetEffectVolume(float volume);

	/* Name		：PauseAll
	 * Author	：PengLongHua
	 * Date		: 2015-07-13
	 * Desc		: 暂停
	 * Param	: none
	 * Return	: none
	 */
	void PauseAll();

	/* Name		：ResumeAll
	 * Author	：PengLongHua
	 * Date		: 2015-07-13
	 * Desc		: 恢复
	 * Param	: none
	 * Return	: none
	 */
	void ResumeAll();

	/* Name		：ClearAudioData
	 * Author	：PengLongHua
	 * Date		: 2015-07-13
	 * Desc		: 清除音乐音效数据
	 * Param	: none
	 * Return	: none
	 */
	void ClearAudioData();

private:
	bool			m_bMusicEnable;
	bool			m_bEffectEnable;
};

#define gCocosAudio CoCosAudioManager::Instance()

#endif //__CoCosAudioManager_h_