// movementCommands.c
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

// Robot moving commands

// Rotate the robot around the center between its drive wheels
// power right wheel and left wheel in opposite directions
void rotateRobot(float angle, int power = rotatePower)
{
	if (fabs(angle) < epsilon)
	{
		return;
	}
	// compute number of ticks
	float distanceToGo = angle * robotWheelBaseLength / 2.0;
	int ticksToGo = round(distanceToGo * ticksPerMm);
	if (ticksToGo < 0)
	{
		ticksToGo = -ticksToGo;
		power = -power;
	}

	if (ticksToGo == 0)
	{
		return;
	}

	nSyncedMotors = synchMode; // sync motors Right as master and Left as slave
	nSyncedTurnRatio = -100; // motors move in opposite direction of each other
	nMotorEncoderTarget[Master] = ticksToGo;
	motor[Master] = power;

	while (nMotorRunState[Master] != runStateIdle) //while Right motor is not in idle
	{
		// do nothing until the motor encoder target has been reached
	}
	motor[Master] = 0;
	nSyncedMotors = synchNone;
}

void rotateRobotInDeg(float degrees, int power = rotatePower)
{
	rotateRobot(myDegreesToRadians(degrees), power);
}

void rotateRobotToHeadingInDeg(float newHeading, int power = rotatePower)
{
	float result = (newHeading - myRadiansToDegrees(gCurrentPose.theta)) % 360;
	if (result >= 180.0)
	{
		result -= 360.0;
	}
	rotateRobotInDeg(result, power);
}

void driveRobotStraight(int ticks)
{
	// Drive robot in straight line to destination
	nSyncedMotors = synchMode; // sync motors Left as master and Right as slave
	nSyncedTurnRatio = 100; // motors move at 100% alignment to each other
	if (ticks == 0)
	{
		return;
	}

	int power = maxPower;
	if (ticks < 0)
	{
		ticks = -ticks;
		power = -power;
	}

	// vector in robot POV to target
	Pose startPose;
	semaphoreLock(currentPose);
	assignPose(startPose, gCurrentPose);
	semaphoreUnlock(currentPose);

	nMotorEncoderTarget[Master] = ticks;
	motor[Master] = power;

	while (nMotorRunState[Master] != runStateIdle) // while Master motor is not in idle
	{
  	wait1Msec(10);
	}
	motor[Master] = 0;
	nSyncedMotors = synchNone;
}

void driveRobotStraightInMm(float distance)
{
	driveRobotStraight(distanceToTicks(distance));
}

void goToDestination(const Vector2d dest)
{
	Pose pose;
	Vector2d toDest;
	int ticksToDest;

	semaphoreLock(currentPose);
	assignPose(pose, gCurrentPose);
	semaphoreUnlock(currentPose);
	// calculate vector to destination in robots POV
	calculateVectorToDest(pose, dest, toDest);
	float angleToTurn = calculateTurnAngleToDest(toDest);
	ticksToDest = calculateTicksToDest(pose, toDest);

	// Turn robot to face destination
	rotateRobot(angleToTurn);

	wait1Msec(50);
	// Drive robot straight toward destination
	driveRobotStraight(ticksToDest);
	wait1Msec(50);
}

void goToDestination(float x, float y)
{
	Vector2d dest = {x, y};
	goToDestination(dest);
}

void turnTorwardCenterOfRoom()
{
	writeDebugStreamLine("Turning toward center of room.");
	Vector2d toRoomCenter;
	Pose pose;
	semaphoreLock(currentPose);
	assignPose(pose, gCurrentPose);
	semaphoreUnlock(currentPose);
	// calculate vector to destination in robots POV
	calculateVectorToDest(pose, roomCenter, toRoomCenter);
	float angleToTurn = calculateTurnAngleToDest(toRoomCenter);
	writeDebugStreamLine("angle = %d", myRadiansToDegrees(angleToTurn));
	rotateRobot(angleToTurn);
}
