#pragma once
class LPFFourPole
{
public:
	LPFFourPole(double sampleDuration);

	~LPFFourPole();

	void Init();
	
	void Recalculate();
	
	double GetSample(double input);
	
	void SetCutoff(double cutoff);
		
	void SetResonance(double resonance);
private:
	const double CUTOFF_MIN = 20.0;
	const double CUTOFF_MAX = 10000.0;
	const double RES_MIN = 0.0;
	const double RES_MAX = 0.9;

	double _cutoff;
	double _resonance;
	double _sampleDuration;
	double y1, y2, y3, y4;
	double oldx;
	double oldy1, oldy2, oldy3;
	double x;
	double r;
	double p;
	double k;
};

