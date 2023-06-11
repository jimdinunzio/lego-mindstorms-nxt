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

// robot dimensions in mm
const float robotWheelBaseLength = 126.0;
const float robotWheelRadius = 27.50; // 56mm diameter printed on the tire, but this value was empircally dervied from testing.
const int robotWheelTicksPerRevolution = 360;
const float robotPenDistanceInX = 107.5;
const Vector2d penOffsetVec = {robotPenDistanceInX, 0};

// calibration constants
const float wheelSizeError = 0.0;
const float ticksPerMm = robotWheelTicksPerRevolution/(2*PI*robotWheelRadius);
const float leftTicksPerMm = ticksPerMm;
const float rightTicksPerMm = ticksPerMm - wheelSizeError;

// Motor control
const int maxPower = 15;
const int rotatePower = 15;
const int fineRotatePower = 15;
//const TSynchedMotors synchLeftRight = synchBC;
const TSynchedMotors synchRightLeft = synchCB;
const TSynchedMotors synchMode = synchRightLeft;
const int Master = Right;

// Location constants
const Vector2d home = {-robotPenDistanceInX, 0};
const Vector2d roomCenter = {914.4, 914.4};

// other constants
const float epsilon = 0.000006;
const int SoundVolume = 4;
const int penUpDownTicks = 180/5;
const float left_bias_offset = 16;
