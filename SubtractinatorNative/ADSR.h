#pragma once
class ADSR
{
public:
	ADSR();

	~ADSR();

	void SetEnvelope(double attackDuration, double decayDuration, double sustainLevel, double releaseDuration);

	void Start(double startTime);

	void Release(double releaseTime);

	double GetLevel(double dspTime);

	enum EnvState
	{
		env_idle = 0,
		env_attack,
		env_decay,
		env_sustain,
		env_release
	};
private:
	int _state;
	double _output;
	double _startTime;
	double _releaseTime;
	double _attackInc;
	double _decayInc;
	double _sustainLevel;
	double _releaseInc;
};

