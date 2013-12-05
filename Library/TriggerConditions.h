//
// TriggerConditions.h
//
typedef struct
    {
    BOOL        fTriggered;                 // whether configured trigger conditions have been hit or not
    BOOL        fRequireTrigger;            // if true, then turning and driving fail unless the trigger condition is hit
    float       cmAdditional;               // for driving: an additional distance to travel after a trigger
    float       fractionRemaining;          // for driving or turning: if trigger conditions are hit, indicates what fraction of the commanded distance / turn remains
    } TRIGGERCONDITIONS;

TRIGGERCONDITIONS trig;      // a global TRIGGERCONDITIONS that can be used by the main task

void InitializeTriggerConditions()
    {
    TRIGGER_SENSORS_CONTEXT context;
    InitializeTriggerSensorsContext(context, TRIGGER_ACTION_INITIALIZE);
    TriggerSensors(context);
    //
    trig.fRequireTrigger        = false;
    trig.fTriggered             = false;
    trig.cmAdditional           = 0.0;
    trig.fractionRemaining      = 0.0;
    }

void ArmTriggerConditions()
    {
    TRIGGER_SENSORS_CONTEXT context; context.action = TRIGGER_ACTION_ARM;
    TriggerSensors(context);
    }

void DisarmTriggerConditions()
    {
    TRIGGER_SENSORS_CONTEXT context; context.action = TRIGGER_ACTION_DISARM;
    TriggerSensors(context);
    }

void CheckTriggerConditions()
    {
    LockBlackboard();
    /**/
    TRIGGER_SENSORS_CONTEXT context;
    context.action = TRIGGER_ACTION_CHECK;
    context.fTriggered = false;
    TriggerSensors(context);
    trig.fTriggered = context.fTriggered;
    /**/
    ReleaseBlackboard();
    }
