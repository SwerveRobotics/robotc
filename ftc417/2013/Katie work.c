#pragma config(Sensor, S1,     salmon,         sensorTouch)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while(true)
	{
		if(SensorValue(salmon) == 1)
		{

  //        125 = Tempo
  //          5 = Default octave
  //    Quarter = Default note length
  //        10% = Break between notes
  //
  PlayTone(  932,   43); wait1Msec( 480);  // Note(A#)
  PlayTone(  698,   65); wait1Msec( 720);  // Note(F, Duration(Quarter .))
  PlayTone(  932,   22); wait1Msec( 240);  // Note(A#, Duration(Eighth))
  PlayTone(  932,   11); wait1Msec( 120);  // Note(A#, Duration(16th))
  PlayTone(  784,   11); wait1Msec( 120);  // Note(C6, Duration(16th))
  PlayTone(  880,   11); wait1Msec( 120);  // Note(D6, Duration(16th))
  PlayTone(  933,   11); wait1Msec( 120);  // Note(D#6, Duration(16th))
  PlayTone( 1047,   86); wait1Msec( 960);  // Note(F6, Duration(Half))
  PlayTone(    0,   22); wait1Msec( 240);  // Note(Rest, Duration(Eighth))
  PlayTone( 1047,   22); wait1Msec( 240);  // Note(F6, Duration(Eighth))
  PlayTone( 1047,   16); wait1Msec( 180);  // Note(F6, Duration(16th .))
  PlayTone( 1109,   11); wait1Msec( 120);  // Note(F#6, Duration(16th))
  PlayTone( 1245,   16); wait1Msec( 180);  // Note(G#6, Duration(16th .))
  PlayTone( 1398,  130); wait1Msec(1440);  // Note(A#6, Duration(Half .))
  PlayTone( 1398,   16); wait1Msec( 180);  // Note(A#6, Duration(16th .))
  PlayTone( 1245,   11); wait1Msec( 120);  // Note(G#6, Duration(16th))
  PlayTone( 1109,   16); wait1Msec( 180);  // Note(F#6, Duration(16th .))
  PlayTone( 1245,   32); wait1Msec( 360);  // Note(G#6, Duration(Eighth .))
  PlayTone( 1109,   16); wait1Msec( 180);  // Note(F#6, Duration(16th .))
  PlayTone( 1047,   86); wait1Msec( 960);  // Note(F6, Duration(Half))
  PlayTone( 1047,   43); wait1Msec( 480);  // Note(F6)
  PlayTone(  933,   22); wait1Msec( 240);  // Note(D#6, Duration(Eighth))
  PlayTone(  933,   11); wait1Msec( 120);  // Note(D#6, Duration(16th))
  PlayTone( 1047,   11); wait1Msec( 120);  // Note(F6, Duration(16th))
  PlayTone( 1109,   86); wait1Msec( 960);  // Note(F#6, Duration(Half))
  PlayTone( 1047,   22); wait1Msec( 240);  // Note(F6, Duration(Eighth))
  PlayTone(  933,   22); wait1Msec( 240);  // Note(D#6, Duration(Eighth))
  PlayTone(  831,   22); wait1Msec( 240);  // Note(C#6, Duration(Eighth))
  PlayTone(  831,   11); wait1Msec( 120);  // Note(C#6, Duration(16th))
  PlayTone(  933,   11); wait1Msec( 120);  // Note(D#6, Duration(16th))
  PlayTone( 1047,   86); wait1Msec( 960);  // Note(F6, Duration(Half))
  PlayTone(  933,   22); wait1Msec( 240);  // Note(D#6, Duration(Eighth))
  PlayTone(  831,   22); wait1Msec( 240);  // Note(C#6, Duration(Eighth))
  PlayTone(  784,   22); wait1Msec( 240);  // Note(C6, Duration(Eighth))
  PlayTone(  784,   11); wait1Msec( 120);  // Note(C6, Duration(16th))
  PlayTone(  880,   11); wait1Msec( 120);  // Note(D6, Duration(16th))
  PlayTone(  988,   86); wait1Msec( 960);  // Note(E6, Duration(Half))
  PlayTone( 1175,   43); wait1Msec( 480);  // Note(G6)
  PlayTone( 1047,   22); wait1Msec( 240);  // Note(F6, Duration(Eighth))
  PlayTone(  698,   11); wait1Msec( 120);  // Note(F, Duration(16th))
  PlayTone(  698,   11); wait1Msec( 120);  // Note(F, Duration(16th))
  PlayTone(  698,   22); wait1Msec( 240);  // Note(F, Duration(Eighth))
  PlayTone(  698,   11); wait1Msec( 120);  // Note(F, Duration(16th))
  PlayTone(  698,   11); wait1Msec( 120);  // Note(F, Duration(16th))
  PlayTone(  698,   22); wait1Msec( 240);  // Note(F, Duration(Eighth))
  PlayTone(  698,   11); wait1Msec( 120);  // Note(F, Duration(16th))
  PlayTone(  698,   11); wait1Msec( 120);  // Note(F, Duration(16th))
  PlayTone(  698,   22); wait1Msec( 240);  // Note(F, Duration(Eighth))
  PlayTone(  698,   22); wait1Msec( 240);  // Note(F, Duration(Eighth))
  PlayTone(  932,   43); wait1Msec( 480);  // Note(A#)
  PlayTone(  698,   65); wait1Msec( 720);  // Note(F, Duration(Quarter .))
  PlayTone(  932,   22); wait1Msec( 240);  // Note(A#, Duration(Eighth))
  PlayTone(  932,   11); wait1Msec( 120);  // Note(A#, Duration(16th))
  PlayTone(  784,   11); wait1Msec( 120);  // Note(C6, Duration(16th))
  PlayTone(  880,   11); wait1Msec( 120);  // Note(D6, Duration(16th))
  PlayTone(  933,   11); wait1Msec( 120);  // Note(D#6, Duration(16th))
  PlayTone( 1047,   86); wait1Msec( 960);  // Note(F6, Duration(Half))
  PlayTone(    0,   22); wait1Msec( 240);  // Note(Rest, Duration(Eighth))
  PlayTone( 1047,   22); wait1Msec( 240);  // Note(F6, Duration(Eighth))
  PlayTone( 1047,   16); wait1Msec( 180);  // Note(F6, Duration(16th .))
  PlayTone( 1109,   11); wait1Msec( 120);  // Note(F#6, Duration(16th))
  PlayTone( 1245,   16); wait1Msec( 180);  // Note(G#6, Duration(16th .))
  PlayTone( 1398,  130); wait1Msec(1440);  // Note(A#6, Duration(Half .))
  PlayTone( 1108,   43); wait1Msec( 480);  // Note(C#7)
  PlayTone( 1046,   43); wait1Msec( 480);  // Note(C7)
  PlayTone( 1320,   86); wait1Msec( 960);  // Note(A6, Duration(Half))
  PlayTone( 1047,   43); wait1Msec( 480);  // Note(F6)
  PlayTone( 1109,  130); wait1Msec(1440);  // Note(F#6, Duration(Half .))
  PlayTone( 1398,   43); wait1Msec( 480);  // Note(A#6)
  PlayTone( 1320,   43); wait1Msec( 480);  // Note(A6)
  PlayTone( 1047,   86); wait1Msec( 960);  // Note(F6, Duration(Half))
  PlayTone( 1047,   43); wait1Msec( 480);  // Note(F6)
  PlayTone( 1109,  130); wait1Msec(1440);  // Note(F#6, Duration(Half .))
  PlayTone( 1398,   43); wait1Msec( 480);  // Note(A#6)
  PlayTone( 1320,   43); wait1Msec( 480);  // Note(A6)
  PlayTone( 1047,   86); wait1Msec( 960);  // Note(F6, Duration(Half))
  PlayTone(  880,   43); wait1Msec( 480);  // Note(D6)
  PlayTone(  933,  130); wait1Msec(1440);  // Note(D#6, Duration(Half .))
  PlayTone( 1109,   43); wait1Msec( 480);  // Note(F#6)
  PlayTone( 1047,   43); wait1Msec( 480);  // Note(F6)
  PlayTone(  831,   86); wait1Msec( 960);  // Note(C#6, Duration(Half))
  PlayTone(  932,   43); wait1Msec( 480);  // Note(A#)
  PlayTone(  784,   43); wait1Msec( 480);  // Note(C6)
  PlayTone(  880,   11); wait1Msec( 120);  // Note(D6, Duration(16th))
  PlayTone(  988,   86); wait1Msec( 960);  // Note(E6, Duration(Half))
  PlayTone( 1175,   43); wait1Msec( 480);  // Note(G6)
  PlayTone( 1047,   22); wait1Msec( 240);  // Note(F6, Duration(Eighth))
  PlayTone(  698,   11); wait1Msec( 120);  // Note(F, Duration(16th))
  PlayTone(  698,   11); wait1Msec( 120);  // Note(F, Duration(16th))
  PlayTone(  698,   22); wait1Msec( 240);  // Note(F, Duration(Eighth))
  PlayTone(  698,   11); wait1Msec( 120);  // Note(F, Duration(16th))
  PlayTone(  698,   11); wait1Msec( 120);  // Note(F, Duration(16th))
  PlayTone(  698,   22); wait1Msec( 240);  // Note(F, Duration(Eighth))
  PlayTone(  698,   11); wait1Msec( 120);  // Note(F, Duration(16th))
  PlayTone(  698,   11); wait1Msec( 120);  // Note(F, Duration(16th))
  PlayTone(  698,   22); wait1Msec( 240);  // Note(F, Duration(Eighth))
  PlayTone(  698,   22); wait1Msec( 240);  // Note(F, Duration(Eighth))
  return;
}



	else
	{

	}




	}
}
