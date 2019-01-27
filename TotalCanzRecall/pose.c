// pose.c
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

// Pose structure and routines

struct Pose
{
	Vector2d pos;
	float theta;
};

void assignPose(Pose& lvalue, Pose rvalue)
{
	lvalue.pos[0] = rvalue.pos[0];
	lvalue.pos[1] = rvalue.pos[1];
	lvalue.theta = rvalue.theta;
}

void setPose(Pose& pose, float x, float y, float theta)
{
	pose.pos[0] = x;
	pose.pos[1] = y;
	pose.theta = theta;
}

void invertPose(Pose inPose, Pose& invertedPose)
{
	invertedPose.theta = -inPose.theta;
	inPose.pos[0] = -inPose.pos[0];
	inPose.pos[1] = -inPose.pos[1];
	rotateVector2d(inPose.pos, invertedPose.theta, invertedPose.pos);
}

// calculate heading vector to destination from robot's POV
void calculateVectorToDest(Pose pose, const Vector2d dest, Vector2d& toDest)
{
	// get the inverse of the robot's pose
	Pose invertedPose;
	invertPose(pose, invertedPose);

	// calculate the vector to the destination from the robot's POV
	rotateAndTransVector2d(dest, invertedPose.theta, invertedPose.pos, toDest);
}
