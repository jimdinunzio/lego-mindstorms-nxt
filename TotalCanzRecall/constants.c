// constants.c
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

//const int LightSensor_WhitePaper = 60;
const int LightSensor_FloorTile = 40;
const int LightSensor_BlackTape = 30;
const int LightSensor_FloorTile_BlackTape_Threshhold = (LightSensor_FloorTile + LightSensor_BlackTape) / 2;
//const int LightSensor_BlackTape_WhitePaper_Threshhold = (LightSensor_BlackTape + LightSensor_WhitePaper) / 2;

// robot dimensions in mm
const float robotWheelBaseLength = 124.25;
const float robotWheelRadius = 27.45; // 56mm diameter printed on the tire, but this value was empircally dervied from testing.
const int robotWheelTicksPerRevolution = 360;

// calibration constants
const float wheelSizeError = 0.0;
const float ticksPerMm = robotWheelTicksPerRevolution/(2*PI*robotWheelRadius);
const float leftTicksPerMm = ticksPerMm;
const float rightTicksPerMm = ticksPerMm - wheelSizeError;

// Motor control
const int maxPower = 50;
const int rotatePower = 25;
const int fineRotatePower = 15;
//const TSynchedMotors synchLeftRight = synchBC;
const TSynchedMotors synchRightLeft = synchCB;
const TSynchedMotors synchMode = synchRightLeft;
const int Master = Right;

// Search constants
const int captureSlopDistance = 25;
const int NumberOfCansToCollect = 3;
const int halfSweepAngle = 75;
const int BackupDistanceAfterDropOff = -200;
const int DistCloseEnoughForNoCorrection = 600;
const int MaxCaptureDistance = 12;

// Location constants
const Vector2d home = {139.7, 107.95};
const Vector2d roomCenter = {914.4, 914.4};

// other constants
const float epsilon = 0.000006;
const int SoundVolume = 4;
const int AngleToRotateToSenseCanColor = 18;
