#pragma once

const ULONG MAX_SAMPLE_COUNT = 50; // 50회의 프레임 처리시간을 누적하여 평균한다

class CGameTimer
{
public:
	CGameTimer();
	virtual ~CGameTimer();
	void Tick(float fLockFPS = 0.0f); 
	void Start(); 
	void Stop();
	void Reset(); 
	unsigned long GetFrameRate(LPTSTR lpszString = NULL, int nCharacters = 0); 
	float GetTimeElapsed(); 
	float GetTotalTime();

private: bool m_bHardwareHasPerformanceCounter; 
		 float m_fTimeScale;
		 float m_fTimeElapsed;
		 __int64 m_nCurrentTime; 
		 __int64 m_nLastTime;
		 __int64 m_nBaseTime; 
		 __int64 m_nPausedTime;
		 __int64 m_nStopTime;
		 __int64 m_nPerformanceFrequency;
		 float m_fFrameTime[MAX_SAMPLE_COUNT];
		 ULONG m_nSampleCount;
		 unsigned long m_nCurrentFrameRate; 
		 unsigned long m_nFramesPerSecond; 
		 float m_fFPSTimeElapsed;
		 bool m_bStopped;

};

