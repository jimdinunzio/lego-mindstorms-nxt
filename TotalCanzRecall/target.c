// target.c
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

task main();

// This task continually checks the distance sensor while the robot is sweeping and
// if it is the lowest yet, it records the current heading of the robot and the distance observed.
// owned by the main task
task findClosestTargetDuringScan()
{
  semaphoreInitialize(gFindObjectResultSemaphore);
	float closestTargetDistance;
	float closestTargetAngle;

	while (1)
	{
		closestTargetDistance = 1000;
		closestTargetAngle = 0;
		semaphoreLock(gFindObjectResultSemaphore);
		while (getSemaphoreTaskOwner(gSweepingForObjectSemaphore) != main)
		{
			//wait until sweep starts
		}
		while (!bDoesTaskOwnSemaphore(gSweepingForObjectSemaphore))
		{
			if (SensorValue[Distance] < closestTargetDistance)
			{
				closestTargetDistance = SensorValue[Distance];
				closestTargetAngle = gCurrentPose.theta;
			}
			semaphoreLock(gSweepingForObjectSemaphore, 50);
		}
		gTargetDistance = closestTargetDistance;
		gTargetAngle = closestTargetAngle;
		semaphoreUnlock(gSweepingForObjectSemaphore);
		semaphoreUnlock(gFindObjectResultSemaphore);
	}
}

// Find closest can by sweeping the robot back and forth while using a sub task to measure the
// distance from sensor
// returns true if one is found, false otherwise
bool findClosestTarget(float& distance, float& angle)
{
	bool found = false;
	semaphoreInitialize(gSweepingForObjectSemaphore);

	startTask(findClosestTargetDuringScan);
	while (!found)
	{
		float thetaInDegrees = myRadiansToDegrees(gCurrentPose.theta);

		semaphoreLock(gSweepingForObjectSemaphore);
		writeDebugStreamLine("Main: scanning for object");
		rotateRobotToHeadingInDeg(thetaInDegrees - halfSweepAngle, fineRotatePower);
		rotateRobotToHeadingInDeg(thetaInDegrees + halfSweepAngle, fineRotatePower);
		semaphoreUnlock(gSweepingForObjectSemaphore);
		semaphoreLock(gFindObjectResultSemaphore);
		writeDebugStreamLine("Main: object distance is %d, angle is %d degrees",
				gTargetDistance * 10, myRadiansToDegrees(gTargetAngle));
		semaphoreUnlock(gFindObjectResultSemaphore);
		if (gTargetDistance < 255)
		{
			found = true;
		}
		else
		{
			break;
		}
		wait1Msec(50);
	};
	stopTask(findClosestTargetDuringScan);
	distance = gTargetDistance * 10;
	angle = myRadiansToDegrees(gTargetAngle);
	return found;
}

// Capture the can, returns true if succeeded, false otherwise
bool captureTarget(float distanceToTarget, float angleToTarget)
{
  if (angleToTarget >= 180.0)
	{
		angleToTarget -= 360.0;
	}

	rotateRobotToHeadingInDeg(angleToTarget, rotatePower);
	wait1Msec(50);
	int ticks = distanceToTicks(distanceToTarget);

	// Drive robot in straight line to destination
	nSyncedMotors = synchMode; // sync motors Right as master and Left as slave
	nSyncedTurnRatio = 100; // motors move at 100% alignment to each other

	nMotorEncoderTarget[Master] = ticks;
	motor[Master] = maxPower;

	while (nMotorRunState[Master] != runStateIdle) // while Master motor is not in idle
	{
		// if we are < MaxCaptureDistance cm have run into object
		if (SensorValue[Distance] < MaxCaptureDistance)
		{
			writeDebugStreamLine("capture distance achieved");
			break;
		}
	}
	motor[Master] = 0;
	nSyncedMotors = synchNone;
	return (SensorValue[Distance] < MaxCaptureDistance);
}
