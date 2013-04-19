//
// Blackboard.h
//

//---------------------------------------------------------------------------------------
// Blackboard-related data
//---------------------------------------------------------------------------------------

int32         cBlackboardUpdate = 0;    // how many times has the blackboard been updated?
int32         msBlackboardUpdate;       // time at which the last blackboard update occurred

//---------------------------------------------------------------------------------------
// Reading the blackboard
//---------------------------------------------------------------------------------------

void CALLED_WITH_BB_LOCK UpdateBlackboard();

// Execute the blackboard update the blackboard even though we're not
// running on the blackboard task. This can usefully serve as the core
// 'idle' loop of things like turning and driving.
#define SpeculativelyUpdateBlackboard()                                         \
    {                                                                           \
    /* We just go ahead and refresh the data now? I mean, */                    \
    /* what else is there to do now, anyway?              */                    \
    /**/                                                                        \
    LockBlackboard();                                                           \
    UpdateBlackboard();                                                         \
    ReleaseBlackboard();                                                        \
    /**/                                                                        \
    /* Let other tasks run at least a bit. */                                   \
    /**/                                                                        \
    EndTimeSlice();                                                             \
    }

//---------------------------------------------------------------------------------------
// Compass
//
// REVIEW: This is a little stale, and needs updating
//---------------------------------------------------------------------------------------

#if SensorIsDefined(sensnmCompass)
ANGLE CALLEDBY(iTaskMain) ReadCompass()
// Access the compass value from the main task
    {
    LockBlackboard();
    ANGLE angle = sensCompass.value;
    ReleaseBlackboard();
    return angle;
    }
#else
#define ReadCompass()    (0.0)
#endif

#if SensorIsDefined(sensnmCompass)
void ZeroCompass()
    {
    LockBlackboard();
    sensCompass.valueZero = 0.0;
    ReadCompassSensor(sensCompass);
    sensCompass.valueZero = sensCompass.value;
    ReleaseBlackboard();
    }
#else
#define ZeroCompass()  {}
#endif

//---------------------------------------------------------------------------------------
// Initialization and update
//---------------------------------------------------------------------------------------

#if SensorIsDefined(sensnmCompass)
    #define DetectCompass() { StartReadingCompassSensor(sensCompass); }
#else
    #define DetectCompass() {}
#endif

#define InitializeBlackboard()                            \
    {                                                     \
    cBlackboardUpdate = 0;                                \
    DetectCompass();                                      \
    ZeroCompass();                                        \
    }

void CALLED_WITH_BB_LOCK UpdateBlackboard()
// Do the work of updating the blackboard. Note that (per Dave Schilling) we can't actually read
// the compass (or any of the other sensors?) faster than 100Hz, so we enforce a throttle here.
// That won't be significant when we're called from the BlackboardTask (it doesn't call that often),
// but might be when we're called manually via SpeculativelyUpdateBlackboard().
//
// REVIEW: further research indicates that's probably hookum, esp. when sensor are on a mux.
// But actual removal of that throttle needs more testing before it can be implemented.
    {
    const MILLI msBlackboardThrottle = 8;   // was 11
    MILLI msNow = nSysTime;                 // read the current clock
    //
    // Read sensors that should be called as often as possible rather than throttled.
    //
    READ_SENSORS_CONTEXT context; InitializeReadSensorsContext(context, SENSOR_READ_FREQ_OFTEN);
    ReadSensors(context);
    //
    if (0==cBlackboardUpdate || (msNow - msBlackboardUpdate) > msBlackboardThrottle)
        {
        msBlackboardUpdate = msNow;
        //
        // Read sensors that should be polled at the throttled rate (note that inside each individual
        // ReadXXXSensor routine the sensor is *actually* read only if someone has indicated that it's
        // of current interest).
        //
        context.sensorReadFrequency = SENSOR_READ_FREQ_NORMAL;
        ReadSensors(context);
        //
        // Do other misc things that need doing
        //
        CheckForMotorStall(msNow);
        TickleServos(msNow);
        DoRotorTaskStallWork(msNow);
        //
        cBlackboardUpdate++;
        }
    }

task BlackboardTask()
    {
    // We just go round and round
    //
    for (;;)
        {
        // Since we're going to update the state in the blackboard, make
        // sure that no one is reading it at the moment, and that no one
        // will do so while we do our updates
        //
        LockBlackboard();
        //
        // Do the work to update things
        //
        UpdateBlackboard();
        //
        // Let others read the state
        //
        ReleaseBlackboard();
        //
        // Wait a while before we grab the lock again: otherwise, pretty
        // much no one will ever be able to get in to read it, since
        // we'd always have it locked.
        //
        wait1Msec(msBlackboardPolling);
        }
    }



//---------------------------------------------------------------------------------------
// Startup
//---------------------------------------------------------------------------------------

#define StartBlackboardTask()   { StartTask(BlackboardTask);    }

// We'd like to just 'suspendTask' & 'resumeTask', but apparently those functions aren't functional in RobotC
#define SuspendBlackboard()                                                 \
    {                                                                       \
    /* get the lock to ensure that the task isn't anywhere important */     \
    LockBlackboard();                                                       \
    StopTask(BlackboardTask);                                               \
    ReleaseBlackboard();                                                    \
    }
#define ResumeBlackboard()      { StartTask(BlackboardTask);   }
