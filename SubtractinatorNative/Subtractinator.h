#pragma once
#include "SawOsc.h"
#include "ADSR.h"
#include "LPFFourPole.h"

class Subtractinator
{
public:
	Subtractinator(double sampleDuration);

	~Subtractinator();

	void SetFrequency(double frequency, double slideTime, double detuneAmount);

	void SetEnvelope(double attackDuration, double decayDuration, double sustainLevel, double releaseDuration);

	void SetFilterCutoffBase(double cutoff);

	void SetFilterEnvelopeAmount(double amount);

	void SetFilterResonance(double resonance);

	void Start(double startTime);

	void Release(double releaseTime);

	void ProcessBuffer(float *buffer, int numSamples, int numChannels, double dspTime);

private:
	double _sampleDuration;
	SawOsc _osc1;
	SawOsc _osc2;
	ADSR _env;
	LPFFourPole _filter;
	double _detuneAmount;
	double _filterCutoffBase;
	double _filterEnvelopeAmount;
};

