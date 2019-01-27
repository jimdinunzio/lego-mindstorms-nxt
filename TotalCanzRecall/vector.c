// vector.c
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

// Vector math routines
typedef float Vector2d[2];

void assignVector2d(Vector2d& lvalue, Vector2d rvalue)
{
	lvalue[0] = rvalue[0];
	lvalue[1] = rvalue[1];
}

void addVector2d(const Vector2d a, const Vector2d b, Vector2d& sum)
{
	sum[0] = a[0] + b[0];
	sum[1] = a[1] + b[1];
}

//float dotProduct(Vector2d a, Vector2d b)
//{
//	return a[0] * b[0] + a[1] * b[1];
//}

// get the result of rotating a vector by theta radians
void rotateVector2d(const Vector2d v, float theta, Vector2d& newV)
{
	float sinTheta = sin(theta);
  float cosTheta = cos(theta);

  newV[0] = v[0]*cosTheta - v[1]*sinTheta;
  newV[1] = v[0]*sinTheta + v[1]*cosTheta;
}

void rotateAndTransVector2d(const Vector2d v, float theta, const Vector2d vTrans, Vector2d& newV)
{
	rotateVector2d(v, theta, newV);
	Vector2d final;
	addVector2d(newV, vTrans, final);
	assignVector2d(newV, final);
}

float magnitude(Vector2d v)
{
	return sqrt(v[0] * v[0] + v[1] * v[1]);
}
