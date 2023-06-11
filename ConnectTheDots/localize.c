// localize.c
/*
	Copyright (c) [2019] [James C DiNunzio, II]

	This file is part of TotalCanzRecall.
	TotalCanzRecall is free software: you can redistribute it and/or modify
  it under the terms of the Lesser GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  TotalCanzRecall is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with TotalCanzRecall.  If not, see <https://www.gnu.org/licenses/>.
*/

// Odometry routines
//void updateOdometry2(WheelsTicks& prevTicks, Pose prevPose, Pose& newPose)
//{
//	// compute difference in ticks since prevTicks
//	int ticksRight = nMotorEncoder[Right];
//	int ticksLeft = nMotorEncoder[Left];

//	int dTicksRight = ticksRight - prevTicks.right;
//	int dTicksLeft = ticksLeft - prevTicks.left;

//	// estimate the wheel movements
//	float dRightWheel = dTicksRight / rightTicksPerMm;
//	float dLeftWheel =  dTicksLeft / leftTicksPerMm;
//	float dCenter = 0.5 * (dRightWheel + dLeftWheel);

//	// calculate the new pose
//	newPose.pos[0] = prevPose.pos[0] + (dCenter * cos(prevPose.theta));
//	newPose.pos[1] = prevPose.pos[1] + (dCenter * sin(prevPose.theta));
//	newPose.theta = normalizeAngle(prevPose.theta + ((dRightWheel - dLeftWheel) / robotWheelBaseLength));

//	// update the previous ticks
//	prevTicks.right = ticksRight;
//	prevTicks.left = ticksLeft;
//}

// this is the slower and more accurate method
void updateOdometry(WheelsTicks& prevTicks, Pose prevPose, Pose& newPose)
{
	// compute difference in ticks since last iteration
	int ticksRight = nMotorEncoder[Right];
	int ticksLeft = nMotorEncoder[Left];

	int dTicksRight = ticksRight - prevTicks.right;
	int dTicksLeft = ticksLeft - prevTicks.left;

	// estimate the wheel movements
	float dRightWheel = dTicksRight / rightTicksPerMm;
	float dLeftWheel = dTicksLeft / leftTicksPerMm;

	// handle case if going straight
	if (fabs(dLeftWheel - dRightWheel) < epsilon)
	{
		newPose.pos[0] = prevPose.pos[0] + dLeftWheel * cos(prevPose.theta);
		newPose.pos[1] = prevPose.pos[1] + dRightWheel * sin(prevPose.theta);
		newPose.theta = prevPose.theta;
	}
	else
	{
		// calculate the new pose not going straight
		float R = (robotWheelBaseLength * (dLeftWheel + dRightWheel)) / (2 * (dRightWheel - dLeftWheel));
		float wd = (dRightWheel - dLeftWheel) / robotWheelBaseLength;
		// calibration factor
		wd *= 1.024;
		newPose.pos[0] = prevPose.pos[0] + R * sin(wd + prevPose.theta) - R * sin(prevPose.theta);
		newPose.pos[1] = prevPose.pos[1] - R * cos(wd + prevPose.theta) + R * cos(prevPose.theta);
		newPose.theta = normalizeAngle(prevPose.theta + wd);
	}

	// update the previous ticks
	prevTicks.right = ticksRight;
	prevTicks.left = ticksLeft;
}

// must call this periodically to avoid "wrap around" of values ~90 revolutions)
void resetMotorEncoders()
{
	nMotorEncoder[Right] = 0;
	nMotorEncoder[Left] = 0;
}

// task to keep track of the x,y position and heading of the robot using dead reckoning
task localize()
{
	semaphoreInitialize(currentPose);
	const int maxSafeTicks = 45 * 360;
	Pose newPose;
	WheelsTicks currentTicks;
	assignWheelsTicks(currentTicks, 0, 0);

	while (1) // run forever
	{
		updateOdometry(currentTicks, gCurrentPose, newPose);
		semaphoreLock(currentPose);
		assignPose(gCurrentPose, newPose);
		semaphoreUnlock(currentPose);
		if (nSyncedMotors == synchNone && (currentTicks.left > maxSafeTicks || currentTicks.right > maxSafeTicks))
		{
			resetMotorEncoders();
			assignWheelsTicks(currentTicks, 0, 0);
		}
		// uncomment the lines below to display x,y and angle heading on the NXT display.
		//displayCenteredBigTextLine(1, "x=%d", round(gCurrentPose.pos[0]));
		//displayCenteredBigTextLine(3, "y=%d", round(gCurrentPose.pos[1]));
		//displayCenteredBigTextLine(5, "a=%d", round(myRadiansToDegrees(gCurrentPose.theta)));
		wait1Msec(50);
	}
}
