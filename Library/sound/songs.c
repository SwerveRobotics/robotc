
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


void Play2001()
{
	int speed = 16;
	int waitTime = 2;
	const int no = 53;
	int song_notes[no] =
	{
		note[C][4], note[G][4],
		note[C][5], note[E][5],
		note[Ds][5],

		note[C][4], note[G][3],
		note[C][4], note[G][3],
		note[C][4], note[G][3],
		note[C][4], note[G][3],

		note[C][4], note[G][3],
		note[C][4], note[G][3],
		note[C][3],

		note[C][4], note[G][4],
		note[C][5], note[Ds][5],
		note[E][5],

		note[C][4], note[G][3],
		note[C][4], note[G][3],
		note[C][4], note[G][3],
		note[C][4], note[G][3],

		note[C][4], note[G][3],
		note[C][4], note[G][3],
		note[C][3],

		note[C][4], note[G][4],
		note[C][5], note[Ds][5],
		note[F][5], note[F][5],
		note[G][5], note[A][5],

		note[B][5],note[C][6],
		note[D][6],
		note[B][5],note[C][6],
		note[D][6],

		note[E][5],note[F][5],
		note[G][5],
	};

	int song_lengths[no] =
	{
		16,16,14,2,16,
		2,2,2,2,2,2,2,2,
		2,2,2,2,3,
		16,16,14,2,16,
		2,2,2,2,2,2,2,2,
		2,2,2,2,3,
		16,16,14,2,14,4,4,10,
		4,7,10,4,7,10,
		10,10,20,
	};

	for (int n = 0; n < 53; n++)
	{
		PlayTone(song_notes[n], song_lengths[n] * speed);
		wait10Msec(song_lengths[n] * speed + waitTime);
	}
}

/*
void PlayBaba()
{
	int speed = 10;
	int waitTime = 2;
	const int no = 53;
	int song_notes[no] =
	{
		note[G][2],note[][],
		note[][],note[][],
	};

	int song_lengths[no] =
	{

	};

	for (int n = 0; n < 53; n++)
	{
		PlayTone(song_notes[n], song_lengths[n] * speed);
		wait10Msec(song_lengths[n] * speed + waitTime);
	}
}*/
