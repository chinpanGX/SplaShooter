/*-----------------------------------------------------------

	[Audio.h]
	Author : 出合翔太

------------------------------------------------------------*/
#include "Audio.h"
#include "DirectX11.h"

IXAudio2* Audio::m_xAudio2 = nullptr;
IXAudio2MasteringVoice* Audio::m_masteringVoice = nullptr;
IXAudio2SourceVoice* Audio::m_sourceVoice[Sound::LABEL_MAX] = {};
BYTE* Audio::m_dataAudio[Sound::LABEL_MAX] = {};
DWORD Audio::m_sizeAudio[Sound::LABEL_MAX] = {};
Sound::Param Audio::m_param[Sound::LABEL_MAX] = {};

HRESULT Audio::CheckChunk(HANDLE hFile, DWORD format, DWORD * pChunkSize, DWORD * pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

HRESULT Audio::ReadChunkData(HANDLE hFile, void * pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}
	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}
	return S_OK;
}

void Audio::Init()
{
	using namespace Sound;
	HRESULT hr;
	
	// サンプル↓
	//m_param[LABEL_SAMPLE].Filename = (char*)"Assetファイル"；
	//m_param[LABEL_SAMPLE].LoopCount = -1; -1ならループ

	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&m_xAudio2, 0);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr,"Xaudio2オブジェクト作成失敗");

		// COMライブラリの終了処理
		CoUninitialize();

		return;
	}

	// マスターボイスの生成
	hr = m_xAudio2->CreateMasteringVoice(&m_masteringVoice);
	if (FAILED(hr))
	{
		ThrowIfFailed(hr, "マスターボイスの生成に失敗");
		if (m_xAudio2)
		{
			// XAudio2オブジェクトの開放
			m_xAudio2->Release();
			m_xAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return;
	}

	// サウンドデータの初期化
	for (int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// バッファのクリア
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// サウンドデータファイルの生成
		hFile = CreateFile(m_param[nCntSound].Filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			ThrowIfFailed(hr, "サウンドデータファイルの生成に失敗(1)");
			return;
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// ファイルポインタを先頭に移動
			ThrowIfFailed(hr, "サウンドデータファイルの生成に失敗(2)");
			return;
		}

		// WAVEファイルのチェック
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			ThrowIfFailed(hr, "WAVEファイルのチェックに失敗！(1)");
			return;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(hr))
		{
			ThrowIfFailed(hr, "WAVEファイルのチェックに失敗！(2)");
			return;
		}
		if (dwFiletype != 'EVAW')
		{
			ThrowIfFailed(hr, "WAVEファイルのチェックに失敗！(3)");
			return;
		}

		// フォーマットチェック
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			ThrowIfFailed(hr, "フォーマットチェックに失敗！(1)");
			return;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(hr))
		{
			ThrowIfFailed(hr, "フォーマットチェックに失敗！(2)");
			return;
		}

		// オーディオデータ読み込み
		hr = CheckChunk(hFile, 'atad', &m_sizeAudio[nCntSound], &dwChunkPosition);
		if (FAILED(hr))
		{
			ThrowIfFailed(hr, "オーディオデータ読み込みに失敗！(1)");
			return;
		}
		m_dataAudio[nCntSound] = (BYTE*)malloc(m_sizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, m_dataAudio[nCntSound], m_sizeAudio[nCntSound], dwChunkPosition);
		if (FAILED(hr))
		{
			ThrowIfFailed(hr, "オーディオデータ読み込みに失敗！(2)");
			return;
		}

		// ソースボイスの生成
		hr = m_xAudio2->CreateSourceVoice(&m_sourceVoice[nCntSound], &(wfx.Format));
		if (FAILED(hr))
		{
			ThrowIfFailed(hr, "ソースボイスの生成に失敗！");
			return;
		}

		// バッファの値設定
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_sizeAudio[nCntSound];
		buffer.pAudioData = m_dataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = m_param[nCntSound].LoopCount;

		// オーディオバッファの登録
		m_sourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);
	}
}

void Audio::Uninit()
{
	using namespace Sound;
	// 一時停止
	for (int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		if (m_sourceVoice[nCntSound])
		{
			// 一時停止
			m_sourceVoice[nCntSound]->Stop(0);

			// ソースボイスの破棄
			m_sourceVoice[nCntSound]->DestroyVoice();
			m_sourceVoice[nCntSound] = NULL;

			// オーディオデータの開放
			free(m_dataAudio[nCntSound]);
			m_dataAudio[nCntSound] = NULL;
		}
	}

	// マスターボイスの破棄
	m_masteringVoice->DestroyVoice();
	m_masteringVoice = NULL;

	if (m_xAudio2)
	{
		// XAudio2オブジェクトの開放
		m_xAudio2->Release();
		m_xAudio2 = NULL;
	}

	// COMライブラリの終了処理
	CoUninitialize();
}

void Audio::Play(Sound::Label label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_sizeAudio[label];
	buffer.pAudioData = m_dataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_param[label].LoopCount;

	// 状態取得
	m_sourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
	 // 一時停止
		m_sourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		m_sourceVoice[label]->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	m_sourceVoice[label]->SubmitSourceBuffer(&buffer);

	// 再生
	m_sourceVoice[label]->Start(0);
}

void Audio::Stop()
{
	using namespace Sound;
	// 一時停止
	for (int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		if (m_sourceVoice[nCntSound])
		{
			// 一時停止
			m_sourceVoice[nCntSound]->Stop(0);
		}
	}
}
