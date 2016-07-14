#include "Subtractinator.h"

#if _MSC_VER // this is defined when compiling with Visual Studio
#define EXPORT_API __declspec(dllexport) // Visual Studio needs annotating exported functions with this
#else
#define EXPORT_API // XCode does not need annotating exported functions, so define is empty
#endif

extern "C"
{
	EXPORT_API Subtractinator *Sub_New(double sampleDuration)
	{
		return new Subtractinator(sampleDuration);
	}

	EXPORT_API void Sub_Delete(Subtractinator *sub)
	{
		if (sub)
		{
			delete sub;
		}
	}

	EXPORT_API void Sub_SetFrequency(Subtractinator *sub, double frequency, double slideTime, double detuneAmount)
	{
		if (sub)
		{
			sub->SetFrequency(frequency, slideTime, detuneAmount);
		}
	}

	EXPORT_API void Sub_SetEnvelope(Subtractinator *sub, double attackDuration, double decayDuration, double sustainLevel, double releaseDuration)
	{
		if (sub)
		{
			sub->SetEnvelope(attackDuration, decayDuration, sustainLevel, releaseDuration);
		}
	}

	EXPORT_API void Sub_SetFilterCutoffBase(Subtractinator *sub, double cutoff)
	{
		if (sub)
		{
			sub->SetFilterCutoffBase(cutoff);
		}
	}

	EXPORT_API void Sub_SetFilterEnvelopeAmount(Subtractinator *sub, double amount)
	{
		if (sub)
		{
			sub->SetFilterEnvelopeAmount(amount);
		}
	}

	EXPORT_API void Sub_SetFilterResonance(Subtractinator *sub, double resonance)
	{
		if (sub)
		{
			sub->SetFilterResonance(resonance);
		}
	}

	EXPORT_API void Sub_Start(Subtractinator *sub, double startTime)
	{
		if (sub)
		{
			sub->Start(startTime);
		}
	}

	EXPORT_API void Sub_Release(Subtractinator *sub, double releaseTime)
	{
		if (sub)
		{
			sub->Release(releaseTime);
		}
	}


	EXPORT_API void Sub_ProcessBuffer(Subtractinator *sub, float *buffer, int numSamples, int numChannels, double dspTime)
	{
		if (sub)
		{
			sub->ProcessBuffer(buffer, numSamples, numChannels, dspTime);
		}
	}
}