#pragma once
class SawOsc
{
public:
	SawOsc(double sampleDuration);
	
	~SawOsc();
	
	void Reset();

	void SetFrequency(double frequency, double slideTime);
	
	double GetSample();

private:
	double _sampleDuration;
	double _phase;
	double _phaseInc;
	double _phaseIncSlideInc;
	int _phaseIncSlideSamples;
};

