#include "LPFFourPole.h"
#include <math.h>


LPFFourPole::LPFFourPole(double sampleDuration)
{
	_sampleDuration = sampleDuration;
	_cutoff = 110;
	_resonance = 0;
	Init();
}

LPFFourPole::~LPFFourPole()
{
}

void LPFFourPole::Init()
{
	// initialize values
	y1 = y2 = y3 = y4 = oldx = oldy1 = oldy2 = oldy3 = 0;
	Recalculate();
};

void LPFFourPole::Recalculate()
{
	double f = (_cutoff + _cutoff) * _sampleDuration; //[0 - 1]
	p = f*(1.8 - 0.8*f);
	k = p + p - 1.0;

	double t = (1.f - p)*1.386249;
	double t2 = 12.0 + t*t;
	r = _resonance*(t2 + 6.0*t) / (t2 - 6.0*t);
};

double LPFFourPole::GetSample(double input)
{
	// process input
	x = input - r*y4;

	//Four cascaded onepole filters (bilinear transform)
	y1 = x*p + oldx*p - k*y1;
	y2 = y1*p + oldy1*p - k*y2;
	y3 = y2*p + oldy2*p - k*y3;
	y4 = y3*p + oldy3*p - k*y4;

	//Clipper band limited sigmoid
	y4 -= (y4*y4*y4) / 6.0;

	oldx = x; 
	oldy1 = y1; 
	oldy2 = y2; 
	oldy3 = y3;
	return y4;
}

void LPFFourPole::SetCutoff(double c)
{
	c = fmax(0.0, fmin(c, 1.0));
	_cutoff = c * c * c * (CUTOFF_MAX - CUTOFF_MIN) + CUTOFF_MIN;
	Recalculate();
}

void LPFFourPole::SetResonance(double r)
{
	r = fmax(0.0, fmin(r, 1.0));
	_resonance = r * (RES_MAX - RES_MIN) + RES_MIN; 
	Recalculate();
}