00062 // Task to control motor A
00063 task _FLACcontrolTaskA() {
00064   long _currentEncVal;                // _currentEncVal encoder value
00065   bool _reverse = false;
00066   bool _done = false;
00067   long _lastEncoderCount = 0;
00068   long _stallCounter = 0;
00069 
00070   // This has to be done to prevent the PID regulator from
00071   // messing with the motor speeds
00072   nMotorPIDSpeedCtrl[motorA] = mtrNoReg;
00073 
00074   // we're not stalled just yet, so reset the variable.
00075   _stalled[motorA] = false;
00076 
00077   _currentEncVal = nMotorEncoder[motorA];
00078   _stallCounter = 0;
00079 
00080   // Flip it and reverse it
00081   if (_encoderTarget[motorA] < _currentEncVal)
00082     _reverse = true;
00083 
00084   while (!_done) {
00085     _currentEncVal = nMotorEncoder[motorA];
00086 
00087     // Are we there yet?
00088     if (_reverse && (_currentEncVal <= _encoderTarget[motorA]))
00089       _done = true;
00090     else if (!_reverse && (_currentEncVal >= _encoderTarget[motorA]))
00091       _done = true;
00092 
00093     // Stall detection magic bits happening here.
00094     if (!_done && (abs(_lastEncoderCount - _currentEncVal) > 0)) {
00095       _stallCounter = 0;
00096     } else if (!_done && (_stallCounter > STALL_TIME_SLOW) && _motorHighPower[motorA] < 50) {
00097       _stalled[motorA] = true;
00098       _done = true;
00099     } else if (!_done && (_stallCounter > STALL_TIME_SLOW) && _motorHighPower[motorA] >= 50) {
00100       _stalled[motorA] = true;
00101       _done = true;
00102     } else {
00103       _stallCounter++;
00104     }


00300 /**
00301  * Check if the motor stalled on the last operation
00302  * @param _motor the motor to be checked
00303  * @return true if the motor stalled, false if it hadn't.
00304  */
00305 bool isStalled(tMotor _motor) {
00306   return _stalled[_motor];
00307 }

