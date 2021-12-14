#pragma once
class CSoundManager
{
	DECLARE_SINGLETON(CSoundManager)

private:
	CSoundManager();
	~CSoundManager();

public:
	enum CHANNELID { BGM, DEAD, PORTAL, JUMP, CLEAR, ATTACK, END };
	// 소리가 서로 씹히는걸 방지하기 위해서 채널로 관리를 함

public:
	void Ready_SoundManager();
	void Update_SoundManager();

public:
	bool Play_Sound(const wstring& strSoundKey, CHANNELID eID);						// 효과음 처럼 한번만 재생되는거
	void Play_BGM(const wstring& strSoundKey);															// 반복재생 걸려있는거 (무한히 재생)
	void Stop_Sound(CHANNELID eID);																			// 해당 채널 소리 멈추게 하는거
	void Stop_All();																													// 모든 채널 끄는거

public:
	HRESULT	Load_SoundFile(const char* pFilePath);


private:
	void Release();

private:
	// 사운드 리소스 정보 갖고 있는 객체 
	map<wstring, FMOD_SOUND*> m_mapSound;
	// 재생하고 있는 사운드를 관리할 객체 
	FMOD_CHANNEL* m_pChannel[END];
	//사운드 채널 객체및 장치를 관리할 객체 
	FMOD_SYSTEM* m_pSystem;
};

