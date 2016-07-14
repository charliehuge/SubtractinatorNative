#include "ADSR.h"
#include <math.h>

ADSR::ADSR()
{
	_state = env_idle;
	_output = 0.0;
	_startTime = -1;
	_releaseTime = -1;
	_attackInc = 0;
	_decayInc = 0;
	_sustainLevel = 0;
	_releaseInc = 0;
}


ADSR::~ADSR()
{
}

void ADSR::SetEnvelope(double attackDuration, double decayDuration, double sustainLevel, double releaseDuration)
{
	_sustainLevel = fmax(0.0, fmin(sustainLevel, 1.0));
	_attackInc = attackDuration > 0.0 ? 1.0 / attackDuration : -1;
	_decayInc = decayDuration > 0 ? (1.0 - _sustainLevel) / decayDuration : -1;
	_releaseInc = releaseDuration > 0 ? _sustainLevel / releaseDuration : -1;
}

void ADSR::Start(double startTime)
{
	_startTime = startTime;
	_releaseTime = -1;
}

void ADSR::Release(double releaseTime)
{
	_releaseTime = releaseTime;
	_startTime = -1;
	_state = env_sustain;
}

double ADSR::GetLevel(double dspTime)
{
	if (_startTime > 0.0 && dspTime > _startTime)
	{
		_output = 0.0;
		_state = env_attack;
		_startTime = -1;
	}

	switch (_state)
	{
	case env_idle:
		break;
	case env_attack:
		if (_attackInc < 0)
		{
			_output = 1.0;
			_state = env_decay;
			break;
		}

		_output += _attackInc;

		if (_output > 1.0)
		{
			_output = 1.0;
			_state = env_decay;
		}

		break;
	case env_decay:
		if (_decayInc < 0)
		{
			_output = _sustainLevel;
			_state = env_sustain;
			break;
		}

		_output -= _decayInc;

		if (_output < _sustainLevel)
		{
			_output = _sustainLevel;
			_state = env_sustain;
		}
		break;
	case env_sustain:
		if (_sustainLevel > 0.0)
		{
			if (_releaseTime > 0.0 && dspTime > _releaseTime)
			{
				_state = env_release;
				_releaseTime = -1;
			}
		}
		else
		{
			_state = env_release;
		}
		break;
	case env_release:
		if (_releaseInc < 0)
		{
			_output = 0.0;
			_state = env_idle;
			break;
		}

		_output -= _releaseInc;

		if (_output < 0.0)
		{
			_output = 0.0;
			_state = env_idle;
		}
		break;
	default:
		break;
	}

	return _output;
}
