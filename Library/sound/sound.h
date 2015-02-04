#ifndef SOUND_H
#define SOUND_H

float note[12][9];

typedef enumWord
{
	C = 0,
	Cs,
	D,
	Ds,
	E,
	F,
	Fs,
	G,
	Gs,
	A,
	As,
	B,
}NoteEnum;

void initializeNotes()
{
	nVolume = 4;
	note[0][0]  = 16.35;
	note[1][0]  = 17.32;
	note[2][0]  = 18.35;
	note[3][0]  = 19.45;
	note[4][0]  = 20.60;
	note[5][0]  = 21.83;
	note[6][0]  = 23.12;
	note[7][0]  = 24.50;
	note[8][0]  = 25.96;
	note[9][0]  = 27.50;
	note[10][0] = 29.14;
	note[11][0] = 30.87;
	for (int o = 0; o < 9; o++)
	{
		for (int n = 0; n < 12; n++)
		{
			note[n][o] = note[n][0] * pow(2, o);
		}
	}
}



#endif
