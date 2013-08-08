/*
    QShed <http://www.icculus.org/qshed>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "anorms.h"

/* compressed vertex normals used by mdl and md2 model formats */
const float anorms[162][3] =
{
	{ -0.525731f,  0.000000f,  0.850651f },
	{ -0.442863f,  0.238856f,  0.864188f }, 
	{ -0.295242f,  0.000000f,  0.955423f }, 
	{ -0.309017f,  0.500000f,  0.809017f }, 
	{ -0.162460f,  0.262866f,  0.951056f }, 
	{  0.000000f,  0.000000f,  1.000000f },
	{  0.000000f,  0.850651f,  0.525731f },
	{ -0.147621f,  0.716567f,  0.681718f },
	{  0.147621f,  0.716567f,  0.681718f }, 
	{  0.000000f,  0.525731f,  0.850651f }, 
	{  0.309017f,  0.500000f,  0.809017f }, 
	{  0.525731f,  0.000000f,  0.850651f }, 
	{  0.295242f,  0.000000f,  0.955423f }, 
	{  0.442863f,  0.238856f,  0.864188f }, 
	{  0.162460f,  0.262866f,  0.951056f }, 
	{ -0.681718f,  0.147621f,  0.716567f }, 
	{ -0.809017f,  0.309017f,  0.500000f }, 
	{ -0.587785f,  0.425325f,  0.688191f }, 
	{ -0.850651f,  0.525731f,  0.000000f }, 
	{ -0.864188f,  0.442863f,  0.238856f }, 
	{ -0.716567f,  0.681718f,  0.147621f }, 
	{ -0.688191f,  0.587785f,  0.425325f }, 
	{ -0.500000f,  0.809017f,  0.309017f }, 
	{ -0.238856f,  0.864188f,  0.442863f }, 
	{ -0.425325f,  0.688191f,  0.587785f }, 
	{ -0.716567f,  0.681718f, -0.147621f }, 
	{ -0.500000f,  0.809017f, -0.309017f }, 
	{ -0.525731f,  0.850651f,  0.000000f }, 
	{  0.000000f,  0.850651f, -0.525731f }, 
	{ -0.238856f,  0.864188f, -0.442863f }, 
	{  0.000000f,  0.955423f, -0.295242f }, 
	{ -0.262866f,  0.951056f, -0.162460f }, 
	{  0.000000f,  1.000000f,  0.000000f }, 
	{  0.000000f,  0.955423f,  0.295242f }, 
	{ -0.262866f,  0.951056f,  0.162460f }, 
	{  0.238856f,  0.864188f,  0.442863f }, 
	{  0.262866f,  0.951056f,  0.162460f }, 
	{  0.500000f,  0.809017f,  0.309017f }, 
	{  0.238856f,  0.864188f, -0.442863f }, 
	{  0.262866f,  0.951056f, -0.162460f }, 
	{  0.500000f,  0.809017f, -0.309017f }, 
	{  0.850651f,  0.525731f,  0.000000f }, 
	{  0.716567f,  0.681718f,  0.147621f }, 
	{  0.716567f,  0.681718f, -0.147621f }, 
	{  0.525731f,  0.850651f,  0.000000f }, 
	{  0.425325f,  0.688191f,  0.587785f }, 
	{  0.864188f,  0.442863f,  0.238856f }, 
	{  0.688191f,  0.587785f,  0.425325f }, 
	{  0.809017f,  0.309017f,  0.500000f }, 
	{  0.681718f,  0.147621f,  0.716567f }, 
	{  0.587785f,  0.425325f,  0.688191f }, 
	{  0.955423f,  0.295242f,  0.000000f }, 
	{  1.000000f,  0.000000f,  0.000000f }, 
	{  0.951056f,  0.162460f,  0.262866f }, 
	{  0.850651f, -0.525731f,  0.000000f }, 
	{  0.955423f, -0.295242f,  0.000000f }, 
	{  0.864188f, -0.442863f,  0.238856f }, 
	{  0.951056f, -0.162460f,  0.262866f }, 
	{  0.809017f, -0.309017f,  0.500000f }, 
	{  0.681718f, -0.147621f,  0.716567f }, 
	{  0.850651f,  0.000000f,  0.525731f }, 
	{  0.864188f,  0.442863f, -0.238856f }, 
	{  0.809017f,  0.309017f, -0.500000f }, 
	{  0.951056f,  0.162460f, -0.262866f }, 
	{  0.525731f,  0.000000f, -0.850651f }, 
	{  0.681718f,  0.147621f, -0.716567f }, 
	{  0.681718f, -0.147621f, -0.716567f }, 
	{  0.850651f,  0.000000f, -0.525731f }, 
	{  0.809017f, -0.309017f, -0.500000f }, 
	{  0.864188f, -0.442863f, -0.238856f }, 
	{  0.951056f, -0.162460f, -0.262866f }, 
	{  0.147621f,  0.716567f, -0.681718f }, 
	{  0.309017f,  0.500000f, -0.809017f }, 
	{  0.425325f,  0.688191f, -0.587785f }, 
	{  0.442863f,  0.238856f, -0.864188f }, 
	{  0.587785f,  0.425325f, -0.688191f }, 
	{  0.688191f,  0.587785f, -0.425325f }, 
	{ -0.147621f,  0.716567f, -0.681718f }, 
	{ -0.309017f,  0.500000f, -0.809017f }, 
	{  0.000000f,  0.525731f, -0.850651f }, 
	{ -0.525731f,  0.000000f, -0.850651f }, 
	{ -0.442863f,  0.238856f, -0.864188f }, 
	{ -0.295242f,  0.000000f, -0.955423f }, 
	{ -0.162460f,  0.262866f, -0.951056f }, 
	{  0.000000f,  0.000000f, -1.000000f }, 
	{  0.295242f,  0.000000f, -0.955423f }, 
	{  0.162460f,  0.262866f, -0.951056f }, 
	{ -0.442863f, -0.238856f, -0.864188f }, 
	{ -0.309017f, -0.500000f, -0.809017f }, 
	{ -0.162460f, -0.262866f, -0.951056f }, 
	{  0.000000f, -0.850651f, -0.525731f }, 
	{ -0.147621f, -0.716567f, -0.681718f }, 
	{  0.147621f, -0.716567f, -0.681718f }, 
	{  0.000000f, -0.525731f, -0.850651f }, 
	{  0.309017f, -0.500000f, -0.809017f }, 
	{  0.442863f, -0.238856f, -0.864188f }, 
	{  0.162460f, -0.262866f, -0.951056f }, 
	{  0.238856f, -0.864188f, -0.442863f }, 
	{  0.500000f, -0.809017f, -0.309017f }, 
	{  0.425325f, -0.688191f, -0.587785f }, 
	{  0.716567f, -0.681718f, -0.147621f }, 
	{  0.688191f, -0.587785f, -0.425325f }, 
	{  0.587785f, -0.425325f, -0.688191f }, 
	{  0.000000f, -0.955423f, -0.295242f }, 
	{  0.000000f, -1.000000f,  0.000000f }, 
	{  0.262866f, -0.951056f, -0.162460f }, 
	{  0.000000f, -0.850651f,  0.525731f }, 
	{  0.000000f, -0.955423f,  0.295242f }, 
	{  0.238856f, -0.864188f,  0.442863f }, 
	{  0.262866f, -0.951056f,  0.162460f }, 
	{  0.500000f, -0.809017f,  0.309017f }, 
	{  0.716567f, -0.681718f,  0.147621f }, 
	{  0.525731f, -0.850651f,  0.000000f }, 
	{ -0.238856f, -0.864188f, -0.442863f }, 
	{ -0.500000f, -0.809017f, -0.309017f }, 
	{ -0.262866f, -0.951056f, -0.162460f }, 
	{ -0.850651f, -0.525731f,  0.000000f }, 
	{ -0.716567f, -0.681718f, -0.147621f }, 
	{ -0.716567f, -0.681718f,  0.147621f }, 
	{ -0.525731f, -0.850651f,  0.000000f }, 
	{ -0.500000f, -0.809017f,  0.309017f }, 
	{ -0.238856f, -0.864188f,  0.442863f }, 
	{ -0.262866f, -0.951056f,  0.162460f }, 
	{ -0.864188f, -0.442863f,  0.238856f }, 
	{ -0.809017f, -0.309017f,  0.500000f }, 
	{ -0.688191f, -0.587785f,  0.425325f }, 
	{ -0.681718f, -0.147621f,  0.716567f }, 
	{ -0.442863f, -0.238856f,  0.864188f }, 
	{ -0.587785f, -0.425325f,  0.688191f }, 
	{ -0.309017f, -0.500000f,  0.809017f }, 
	{ -0.147621f, -0.716567f,  0.681718f }, 
	{ -0.425325f, -0.688191f,  0.587785f }, 
	{ -0.162460f, -0.262866f,  0.951056f }, 
	{  0.442863f, -0.238856f,  0.864188f }, 
	{  0.162460f, -0.262866f,  0.951056f }, 
	{  0.309017f, -0.500000f,  0.809017f }, 
	{  0.147621f, -0.716567f,  0.681718f }, 
	{  0.000000f, -0.525731f,  0.850651f }, 
	{  0.425325f, -0.688191f,  0.587785f }, 
	{  0.587785f, -0.425325f,  0.688191f }, 
	{  0.688191f, -0.587785f,  0.425325f }, 
	{ -0.955423f,  0.295242f,  0.000000f }, 
	{ -0.951056f,  0.162460f,  0.262866f }, 
	{ -1.000000f,  0.000000f,  0.000000f }, 
	{ -0.850651f,  0.000000f,  0.525731f }, 
	{ -0.955423f, -0.295242f,  0.000000f }, 
	{ -0.951056f, -0.162460f,  0.262866f }, 
	{ -0.864188f,  0.442863f, -0.238856f }, 
	{ -0.951056f,  0.162460f, -0.262866f }, 
	{ -0.809017f,  0.309017f, -0.500000f }, 
	{ -0.864188f, -0.442863f, -0.238856f },
	{ -0.951056f, -0.162460f, -0.262866f }, 
	{ -0.809017f, -0.309017f, -0.500000f }, 
	{ -0.681718f,  0.147621f, -0.716567f }, 
	{ -0.681718f, -0.147621f, -0.716567f }, 
	{ -0.850651f,  0.000000f, -0.525731f }, 
	{ -0.688191f,  0.587785f, -0.425325f }, 
	{ -0.587785f,  0.425325f, -0.688191f }, 
	{ -0.425325f,  0.688191f, -0.587785f }, 
	{ -0.425325f, -0.688191f, -0.587785f }, 
	{ -0.587785f, -0.425325f, -0.688191f }, 
	{ -0.688191f, -0.587785f, -0.425325f }
};

int compress_normal(const float *normal)
{
	int i, besti;
	float dot, bestdot;

	bestdot = normal[0] * anorms[0][0] + normal[1] * anorms[0][1] + normal[2] * anorms[0][2];
	besti = 0;

	for (i = 1; i < 162; i++)
	{
		dot = normal[0] * anorms[i][0] + normal[1] * anorms[i][1] + normal[2] * anorms[i][2];
		if (dot > bestdot)
		{
			bestdot = dot;
			besti = i;
		}
	}

	return besti;
}