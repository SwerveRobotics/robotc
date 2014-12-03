//
// AutoTele.c
//
#define ROBOT_NAME ROBOT_NAME_FTC417_2011_V1

string rgstrAllianceOptionAutoTele[] = { "Inside Bowling", "Outside Bowling", "Straight", "Crates" };
#define rgstrAllianceOption rgstrAllianceOptionAutoTele
//#define DEFAULT_TEAM_COLOR  TEAM_COLOR_RED

typedef enum
    {
    ALLIANCE_OPTION_STRAIGHT,
    ALLIANCE_OPTION_INSIDE_BOWLING,
    ALLIANCE_OPTION_OUTSIDE_BOWLING,
    ALLIANCE_OPTION_CRATES
    } ALLIANCE_OPTION;

#include "..\lib\MainPrelude.h"
#include "config\RobotConfig.h"
#include "..\lib\MainPostlude.h"
#include "TeleOp.h"

void DoAutonomous()
    {
    int teamColorReflection = (TEAM_COLOR_RED==teamColor ? 1 : -1);

    msElapsedStart = nSysTime;
    TRACE(("**** begin autonomous ****"));
    DisplayMessage("<- autonomous ->");

/*    StartReadingGyroSensor(sensGyroHorz);
    TurnRight(30);
    float targetAng = sensGyroHorz.degTarget;
    TRACE(("%f", targetAng));
    return;

    for(int i; i < 12; i++)
    {
    TurnRight(30);
    LockBlackboard();
    float gyroSpeed = sensGyroHorz.degCWPerS;
    float gyroAng = sensGyroHorz.deg;
    ReleaseBlackboard();
    TRACE(("%f", gyroSpeed));
    TRACE(("%f", gyroAng));
    }
    return;*/

    //Raise forklift
    LockBlackboard();
    SetMotorPower(motorForklift, 100);
    SendMotorPowers();
    ReleaseBlackboard();

    wait1Msec(500);

    LockBlackboard();
    SetMotorPower(motorForklift, 0);
    SetMotorPower(motorAnchor, 0);
    SendMotorPowers();
    ReleaseBlackboard();

    if(allianceOption == (int)ALLIANCE_OPTION_INSIDE_BOWLING)
        {
        DriveForwards(-43 * 2.54);              // Go down ramp backwards
        TurnRight(90 * teamColorReflection);
        DriveForwards(8 * 2.54);               // Go to bowling ball
        TurnRight(-38 * teamColorReflection);
        DriveForwards(190);                     // Go to front parking zone
        }
    else if(allianceOption == (int)ALLIANCE_OPTION_OUTSIDE_BOWLING)
        {
        DriveForwards(-44 * 2.54);              // Go down ramp backwards
        TurnRight(93 * teamColorReflection);
        DriveForwards(31 * 2.54);               // Go to bowling ball
        TurnRight(-36 * teamColorReflection);
        DriveForwards(200);                     // Go to front parking zone
        }
    else if(allianceOption == (int)ALLIANCE_OPTION_STRAIGHT)
        {
        DriveForwards(-12 * 12 * 2.54);
        return;
        }
    else if(allianceOption == (int)ALLIANCE_OPTION_CRATES)
	    {
	    DriveForwards(-41 * 2.54);              // Go down ramp backwards
	    if (TEAM_COLOR_RED==teamColor)
	        {
	        TurnRight(-143);   // Turn to crate
	        }
	    else if (TEAM_COLOR_BLUE==teamColor)
		    {
		    TurnRight(163);
		    }
	    UpDownTine(svoLeftTineUpDown, TINE_LOC_DOWN);   // Tines down
	    UpDownTine(svoRightTineUpDown, TINE_LOC_DOWN);
	    wait1Msec(200);
	    DriveForwards(5 * 2.54);                // Drive to crate
	    OpenCloseTine(svoLeftTineOpenClose,  TINE_DIR_RIGHT);   // close tines
        OpenCloseTine(svoRightTineOpenClose, TINE_DIR_LEFT);
        wait1Msec(1500);
        OpenCloseTine(svoLeftTineOpenClose, TINE_DIR_NONE);
        OpenCloseTine(svoRightTineOpenClose, TINE_DIR_NONE);
        DriveForwards(-4 * 2.54);
        if (TEAM_COLOR_RED==teamColor)
            {
            TurnRight(45);
            DriveForwards(-11 * 2.54);
            TurnRight(-45);
            DriveForwards(-184);// take bowling ball to front parking zone
            }
        else if (TEAM_COLOR_BLUE==teamColor)
	        {
	        TurnRight(-60);
	        DriveForwards(-19 * 2.54);
	        TurnRight(47);
	        DriveForwards(-170);// take bowling ball to front parking zone
	        }
        TurnRight(45 * teamColorReflection);
        DriveForwards(12 * 2.54);
        LockBlackboard();
        SetMotorPower(motorForklift, 100);      // raise lift
        SendMotorPowers();
        ReleaseBlackboard();
        wait1Msec(2000);
        LockBlackboard();
        SetMotorPower(motorForklift, 0);
        SendMotorPowers();
        ReleaseBlackboard();
        OpenCloseTine(svoLeftTineOpenClose,  TINE_DIR_LEFT);   // open tines
        OpenCloseTine(svoRightTineOpenClose, TINE_DIR_RIGHT);
        wait1Msec(1500);
        OpenCloseTine(svoLeftTineOpenClose, TINE_DIR_NONE);
        OpenCloseTine(svoRightTineOpenClose, TINE_DIR_NONE);
        LockBlackboard();
        SetMotorPower(motorForklift, -50);     // lower lift
        SendMotorPowers();
        ReleaseBlackboard();
        wait1Msec(3100);
        LockBlackboard();
        SetMotorPower(motorForklift, 0);
        SendMotorPowers();
        ReleaseBlackboard();
        DriveForwards(-24 * 2.54);              // take robot to front parking zone
	    }
return;

    // Here on down is old code, not curently used

    // Over the cliff, backwards!
    DriveForwards(-100);

    // Straighten robot
    int cmDrive = -30;
    if (TEAM_COLOR_RED==teamColor)
        {
        ReadSonic_Main(sonicRight, true);
        DriveForwardsAndStraightenUsingRightSonic(sonicRight, cmDrive, 100);
        }
    else
        {
        ReadSonic_Main(sonicLeft, true);
        DriveForwardsAndStraightenUsingLeftSonic(sonicLeft, cmDrive, 100);
        }

    // Read new location
    int cmY;
    int cmX;
    //
    int dcmRightSonicToCenter = 18;
    int dcmLeftSonicToCenter  = 18;
    int dcmBackSonicToCenter  = 12;
    int dcmFrontSonicToCenter = 12;
    //
    if (TEAM_COLOR_RED==teamColor)
        {
        cmY = ReadSonic_Main(sonicRight, true) + dcmRightSonicToCenter;
        cmX = ReadSonic_Main(sonicBack,  true) + dcmBackSonicToCenter;
        }
    else
        {
        cmY = ReadSonic_Main(sonicLeft, true) + dcmLeftSonicToCenter;
        cmX = ReadSonic_Main(sonicBack, true) + dcmBackSonicToCenter;
        }
    //
    TRACE(("cmx=%d cmy=%d", cmX, cmY));

    // Bowling ball location
    float cmXBall = 6 * 12 * 2.54;
    float cmYBall = 4 * 12 * 2.54;

    // Get to bowling ball
    int cmXTurnLocation = cmXBall - (cmYBall - cmY);
    int dcmXDrive = cmXTurnLocation - cmX;
    TRACE(("cmxTurn=%d dcmXDrive=%d", cmXTurnLocation, dcmXDrive));

    DriveForwards(dcmXDrive);
    TurnRight(-45 * teamColorReflection);

    /*approach bowling ball slowly
    int dFromWall = ReadSonic_Main(sonicBack, true);
    float dBallFromWall = 4 * sqrtTwo * 12 * 2.54;
    DriveForwards(dBallFromWall - dFromWall, 25);*/

    DriveForwards(350, 100);

    // Get to back parking zone
    //DriveForwards(-350);
    }

task main()
    {
    //programFlavor = PROGRAM_FLAVOR_AUTONOMOUS;

    if (InitializeMain(true, true))
        {
            StartReadingTouchSensor(touchForklift);
        SendOneMotorPower(motorAnchor, 100);
        wait1Msec(500);
        SendOneMotorPower(motorAnchor, 0);

        // Configure our telemetry
        TelemetryUse(true,false);       // Bluetooth, but no USB; change if necessary
        TelemetryEnable(false);         // *Note* disabled for now.

        // Raise the tines so we fit inside our 18" cube!
        MoveServo(svoLeftTineUpDown, svposTineUp, true);
        MoveServo(svoRightTineUpDown, svposTineUp, true);

        // Lower the mast to it's lowest position
        // RaiseMastSlightly();
        // LowerMastSlowlyToLimitSwitch();

        // Now that the mast is all the way down, we record its encoder position
        ReadEncoder(OUT encMastBottom, motorForklift);

        // Wait until the FCS tells us to go
        waitForStart();

        // Off to the races!
        if (PROGRAM_FLAVOR_TELEOP == programFlavor)
            {
            StartReadingTouchSensor(touchForklift); // WRONG
            DoTeleOp();
            }
        else
            {
            DoAutonomous();
            }
        }
    else
        {
        InfiniteIdleLoop(); // Just sit there and update the display
        }
    }
