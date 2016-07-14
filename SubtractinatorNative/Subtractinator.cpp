#include "Subtractinator.h"
#include <math.h>

Subtractinator::Subtractinator(double sampleDuration) : _osc1(sampleDuration), _osc2(sampleDuration), _filter(sampleDuration)
{
	_sampleDuration = sampleDuration;
	_detuneAmount = 0;
}


Subtractinator::~Subtractinator()
{
}

void Subtractinator::SetFrequency(double frequency, double slideTime, double detuneAmount)
{
	if (_detuneAmount > 0.0)
	{
		_osc1.SetFrequency(frequency * pow(2.0, _detuneAmount / 12.0), slideTime);
		_osc2.SetFrequency(frequency * pow(2.0, -_detuneAmount / 12.0), slideTime);
	}
	else
	{
		_osc1.SetFrequency(frequency, slideTime);
		_osc2.SetFrequency(frequency, slideTime);
	}

	_detuneAmount = detuneAmount;
}

void Subtractinator::SetEnvelope(double attackDuration, double decayDuration, double sustainLevel, double releaseDuration)
{
	_env.SetEnvelope(attackDuration / _sampleDuration, decayDuration / _sampleDuration, sustainLevel, releaseDuration / _sampleDuration);
}

void Subtractinator::SetFilterCutoffBase(double cutoff)
{
	_filterCutoffBase = fmax(0.0, fmin(cutoff, 1.0));
}

void Subtractinator::SetFilterEnvelopeAmount(double amount)
{
	_filterEnvelopeAmount = fmax(0.0, fmin(amount, 1.0));
}

void Subtractinator::SetFilterResonance(double resonance)
{
	_filter.SetResonance(resonance);
}

void Subtractinator::Start(double startTime)
{
	_env.Start(startTime);
}

void Subtractinator::Release(double releaseTime)
{
	_env.Release(releaseTime);
}

void Subtractinator::ProcessBuffer(float *buffer, int numSamples, int numChannels, double dspTime)
{
	double sample;
	double envAmt;
	bool envWasOn = false;

	for (int i = 0; i < numSamples; i += numChannels)
	{
		envAmt = _env.GetLevel(dspTime);

		if (envAmt > 0.0)
		{
			if (_detuneAmount > 0.0)
			{
				sample = _osc1.GetSample() + _osc2.GetSample();
			}
			else
			{
				sample = _osc1.GetSample();
				_osc2.GetSample();
			}

			if (_filterEnvelopeAmount > 0.0)
			{
				_filter.SetCutoff(_filterCutoffBase + _filterEnvelopeAmount * envAmt);
			}
			else
			{
				_filter.SetCutoff(_filterCutoffBase);
			}

			sample = _filter.GetSample(sample);

			envWasOn = true;
		}
		else
		{
			if (envWasOn)
			{
				_filter.Init();
				envWasOn = false;
			}

			sample = 0.0;
		}

		for (int j = 0; j < numChannels; ++j)
		{
			buffer[i + j] *= (float)sample;
		}

		dspTime += _sampleDuration;
	}
}
