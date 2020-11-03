/*-----------------------------------------------------------

	[Audio.h]
	Author : 出合翔太

------------------------------------------------------------*/
#pragma once
#include "xaudio2.h"

namespace Sound
{
	// ラベル名の列挙
	enum Label
	{
		LABEL_SAMPLE,
		LABEL_MAX
	};
	// パラメータ
	struct Param
	{
		char* Filename; // ファイル名
		int LoopCount;	// ループカウント -1ならループor0なら1回
	};
}

class Audio
{
private:
	static IXAudio2* m_xAudio2;
	static IXAudio2MasteringVoice* m_masteringVoice;
	static IXAudio2SourceVoice* m_sourceVoice[Sound::LABEL_MAX];
	static BYTE* m_dataAudio[Sound::LABEL_MAX];
	static DWORD m_sizeAudio[Sound::LABEL_MAX];
	static Sound::Param m_param[Sound::LABEL_MAX];

	static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	static HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
public:
	static void Init();
	static void Uninit();
	static void Play(Sound::Label label);
	static void Stop();
};

