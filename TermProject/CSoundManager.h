#pragma once
class CSoundManager
{
	DECLARE_SINGLETON(CSoundManager)

private:
	CSoundManager();
	~CSoundManager();

public:
	enum CHANNELID { BGM, DEAD, PORTAL, JUMP, CLEAR, ATTACK, END };


public:
	void Ready_SoundManager();
	void Update_SoundManager();

public:
	bool Play_Sound(const wstring& strSoundKey, CHANNELID eID);						
	void Play_BGM(const wstring& strSoundKey);											
	void Stop_Sound(CHANNELID eID);																	
	void Stop_All();		
	void Set_Volume(float volume, CHANNELID eID);

public:
	HRESULT	Load_SoundFile(const char* pFilePath);


private:
	void Release();

private:
	map<wstring, FMOD_SOUND*> m_mapSound;
	FMOD_CHANNEL* m_pChannel[END];
	FMOD_SYSTEM* m_pSystem;
};

