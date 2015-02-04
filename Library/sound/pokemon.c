
#include "sound.h"

void PlayPokemon()
{
	const int no = 125;
	int speed = 7;
	int waitTime = 1;
	int song_notes[no] =
	{
		note[A][4],  note[Gs][4],
		note[G][4],  note[Fs][4],
		note[A][4],  note[G][4],
		note[Fs][4],  note[F][4],

		note[E][4], note[F][4],
		note[A][4], note[E][4],
		note[Ds][4],  note[A][4],
		note[E][4], note[Ds][4],

		note[D][4],  note[A][4],
		note[Ds][4],  note[D][4],
		note[Cs][4],  note[A][4],
		note[D][4],  note[Cs][4],

		note[A][4], note[C][4],
		note[Cs][4],  note[B][3],

		note[D][4],  note[E][3],
		note[F][3], note[D][3],
		note[E][3],  note[F][3],
		note[C][3],

		note[D][3],	note[E][3],
		note[F][3], note[D][3],
		note[E][3], note[F][3],
		note[C][3],  note[Cs][3],

		note[D][4],	note[E][4],
		note[F][4], note[D][4],
		note[E][4], note[F][4],
		note[C][4],  note[Cs][4],

		note[B][3],	note[Fs][3],
		note[B][3], note[Fs][3],
		note[B][3], note[C][4],

		note[C][3], note[Cs][3],
		note[D][3], note[Ds][3],
		note[E][3], note[Ds][3],
		note[D][3], note[Cs][3],

		note[C][3], note[Cs][3],
		note[D][3], note[Ds][3],
		note[E][3], note[F][3],
		note[Fs][3], note[G][3],

		note[Gs][3], note[G][3],
		note[Fs][3], note[F][3],
		note[E][3], note[Ds][3],
		note[D][3], note[Cs][3],

		note[B][3],	note[Fs][3],
		note[B][3], note[Fs][3],
		note[B][3], note[A][3],

		note[Cs][3], note[B][2],
		note[Cs][3],

		note[D][3], note[Cs][3],
		note[B][2], note[A][2],
		note[G][2],

		note[D][3], note[Cs][3],
		note[B][2], note[A][2],
		note[G][2],

		note[D][3], note[Cs][3],
		note[B][2], note[Cs][3],
		note[E][3],

		note[A][2], note[B][2],
		note[C][3], note[Cs][3],
		note[D][3],

		note[G][2], note[A][2],
		note[B][3], note[C][3],
		note[Cs][3],

		note[A][2], note[B][2],
		note[C][3], note[Cs][3],
		note[D][3],

		note[G][2], note[A][2],
		note[B][3], note[C][3],
		note[Cs][3],

	};

	int song_lengths[no] =
	{
		1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,
		1,1,1,1,
		10,10,6,2,6,10,6,
		10,10,6,2,6,10,2,2,
		10,10,6,2,6,10,2,2,
		10,26,6,6,6,14,
		1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,
		10,26,6,6,6,14,
		14,14,14,
		2,2,2,2,6,
		2,2,2,2,6,
		2,2,2,2,6,
		1,1,1,1,6,
		1,1,1,1,6,
		1,1,1,1,6,
		1,1,1,1,6,
	};

	for (int n = 0; n < no; n++)
	{
		PlayTone(song_notes[n] * 2, song_lengths[n] * speed);
		wait10Msec(song_lengths[n] * speed + waitTime);
	}

}
