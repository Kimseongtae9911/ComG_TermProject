#pragma once
class CSoundManager
{
	DECLARE_SINGLETON(CSoundManager)

private:
	CSoundManager();
	~CSoundManager();

public:
	enum CHANNELID { BGM, DEAD, PORTAL, JUMP, CLEAR, ATTACK, END };
	// �Ҹ��� ���� �����°� �����ϱ� ���ؼ� ä�η� ������ ��

public:
	void Ready_SoundManager();
	void Update_SoundManager();

public:
	bool Play_Sound(const wstring& strSoundKey, CHANNELID eID);						// ȿ���� ó�� �ѹ��� ����Ǵ°�
	void Play_BGM(const wstring& strSoundKey);															// �ݺ���� �ɷ��ִ°� (������ ���)
	void Stop_Sound(CHANNELID eID);																			// �ش� ä�� �Ҹ� ���߰� �ϴ°�
	void Stop_All();																													// ��� ä�� ���°�

public:
	HRESULT	Load_SoundFile(const char* pFilePath);


private:
	void Release();

private:
	// ���� ���ҽ� ���� ���� �ִ� ��ü 
	map<wstring, FMOD_SOUND*> m_mapSound;
	// ����ϰ� �ִ� ���带 ������ ��ü 
	FMOD_CHANNEL* m_pChannel[END];
	//���� ä�� ��ü�� ��ġ�� ������ ��ü 
	FMOD_SYSTEM* m_pSystem;
};

