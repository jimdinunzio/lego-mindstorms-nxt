// globals.c
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

TSemaphore currentPose; // a synchronization locking primitive to prevent localize and other tasks from reading and writing to gCurrentPose global simultaneously.
Pose gCurrentPose;			// global holding current position of robot.
TSemaphore gFindObjectResultSemaphore; // coordinate between main task and findClosestTargetDuringScan task to deliver closest target distance & heading
TSemaphore gSweepingForObjectSemaphore; // locking mechanism to coordinate between main task while sweeping and findClosestTargetDuringScan task
float gTargetAngle = 0.0;
float gTargetDistance = 0.0;
bool gTurnTowardCenterIfBlackLineHitActing = false;
enum PenState { UP, DOWN };
PenState gPenState = DOWN;
bool gPenEnabled = false;
