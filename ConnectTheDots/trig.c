// trig.c
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

// Trigonometry routines
//float normalizeAngle(float angleInRadians)
//{
//	float angle = myRadiansToDegrees(angleInRadians);

//	// reduce the angle
//	float normAngle =  angle % 360;

//	// force it to be the positive remainder, so that 0 <= angle < 360
//	normAngle = (angle + 360) % 360;

//	// force into the minimum absolute value, so that -180 < angle <= 180
//	if (normAngle > 180)
//	{
//	    normAngle -= 360;
//	}
//	return myDegreesToRadians(normAngle);
//}

float myRadiansToDegrees(float radians);
float myDegreesToRadians(float degrees);

float normalizeAngle(float theta)
{
	return atan2(sin(theta), cos(theta));
}

float myRadiansToDegrees(float radians)
{
	return (180 * radians) / PI;
}

float myDegreesToRadians(float degrees)
{
	return (PI * degrees) / 180.0;
}
