// navigation.c
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

// Navigation routines
int distanceToTicks(float distance)
{
	return round(distance * ticksPerMm);
}

// calculate and return the angle in radians to turn the robot to face the destination
// input: toDest - vector in robot's POV to destination
float calculateTurnAngleToDest(Vector2d toDest)
{
	return atan2(toDest[1], toDest[0]);
}

// calculate number of wheel ticks to go to reach destination
int calculateTicksToDest(Pose pose, Vector2d toDest)
{
	return distanceToTicks(magnitude(toDest));
}
