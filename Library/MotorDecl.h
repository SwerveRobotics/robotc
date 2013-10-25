//
// MotorDecl.h
//

// Constants for specifying motor properties in InitializeMotor()
typedef enum
    {
    // Use either this:
    MOTORPROP_NONE          = 0x00,

    // Or a combination of these:
    MOTORPROP_REFLECTED     = 0x01,
    MOTORPROP_ENCODER       = 0x02,
    MOTORPROP_NOSTALLCHECK  = 0x04,
    } MOTORPROP;

typedef struct
    {
    BOOL             fActive;           // has this MOTOR been initialized to contain an active motor?
    int              imotor;            // index of this motor in rgmotor
    int              imotorPaired;      // if there is a motor which is paired with this one for added oomph, this is its index in rgmotor
    BOOL             fReflected;        // is this motor manually reflected / reversed?
    BOOL             fHasEncoder;       // does this motor have an associated controller?
    ENCOD            encoder;           // a duplicate of MtrOf(motor).encoder, but one much nicer syntactically

    int              imotorctlr;        // the controller with which this motor is associated
    int              imtr;              // the index of this controller on that controller (zero-based)
    string           displayName;       // a user-comprehensible name for this motor

    float            powerScaling;      // see discussion in SetMotorPower

    // Stall-related state
    BOOL             fDoStallCheck;     // should we check this motor for stall?
    ENCOD            encStallPrev;      // encoder value at last stall check on this motor
    MILLI            msLastOkStall;     // time at which stall check was last carried out on this motor
    MILLI            msLastEncStall;    // last time we read the encoders in stall logic
    } MOTOR;

#define imotorMax 8
int imotorMac = 0;
MOTOR rgmotor[imotorMax];

void InitializeMotor(IN OUT STICKYFAILURE& fOverallSuccess, MOTOR& motor, MOTORCONTROLLER& controllerParam, ubyte jmtr /*one based*/, string displayNameParam, int prop);
