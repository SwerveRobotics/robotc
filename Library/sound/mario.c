
#include "sound.h"


void PlayMario()
{
	int speed = 15;
	int waitTime = 2;
	const int no = 27;
	int song_notes[no] =
	{
		note[G][3],  note[C][4],
		note[E][4],  note[G][4],
		note[C][5],  note[E][5],
		note[G][5],  note[E][5],

		note[Gs][3], note[C][4],
		note[Ds][4], note[Gs][4],
		note[C][5],  note[Ds][5],
		note[Gs][5], note[Ds][5],

		note[As][3],  note[D][4],
		note[F][4],  note[As][4],
		note[D][5],  note[F][5],
		note[A][5],

		note[As][5],  note[As][5],
		note[As][5],  note[C][6],
	};

	int song_lengths[no] =
	{
		1,1,1,1,1,1,1,2,
		1,1,1,1,1,1,1,2,
		1,1,1,1,1,1,1,
		1,1,1,4,
	};

	for (int n = 0; n < 27; n++)
	{
		PlayTone(song_notes[n], song_lengths[n] * speed);
		wait10Msec(song_lengths[n] * speed + waitTime);
	}

}
