#include "SawOsc.h"
#include <math.h>


SawOsc::SawOsc(double sampleDuration)
{
	_sampleDuration = sampleDuration;
	_phase = 0;
	_phaseInc = 0;
	_phaseIncSlideSamples = -1;
}


SawOsc::~SawOsc()
{
}

void SawOsc::Reset()
{
	_phase = 0;
}

void SawOsc::SetFrequency(double frequency, double slideTime)
{
	if (slideTime > 0.0)
	{
		double targetPhaseInc = frequency * _sampleDuration;
		double slideSamples = (int)(slideTime / _sampleDuration);
		_phaseIncSlideInc = (targetPhaseInc - _phaseInc) / slideSamples;
		_phaseIncSlideSamples = (int)slideSamples;
	}
	else
	{
		_phaseInc = frequency * _sampleDuration;
		_phaseIncSlideSamples = -1;
	}
}

double SawOsc::GetSample()
{
	if (_phaseIncSlideSamples > 0)
	{
		_phaseInc += _phaseIncSlideInc;
		--_phaseIncSlideSamples;
	}

	_phase = fmod(_phase + _phaseInc, 1.0);

	if (_phaseInc > 1.0)
	{
		return 0.0;
	}

	// Remap phase and kernelSize from [0.0, 1.0] to [-1.0, 1.0]
	double phase = _phase * 2.0 - 1.0;
	double kernelSize = _phaseInc * 2.0;
	double a, b;

	if (phase + kernelSize > 1.0)
	{
		// Kernel wraps around edge of [-1.0, 1.0]
		a = phase;
		b = phase + kernelSize - 2.0;
	}
	else
	{
		// Kernel fits nicely in [-1.0, 1.0]
		a = phase;
		b = phase + kernelSize;
	}

	// Integrate and divide with kernelSize
	return (b * b - a * a) / (2.0 * kernelSize);
}
