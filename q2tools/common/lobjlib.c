/*
===========================================================================
Copyright (C) 1997-2006 Id Software, Inc.

This file is part of Quake 2 Tools source code.

Quake 2 Tools source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake 2 Tools source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Quake 2 Tools source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/

//
// l3dslib.c: library for loading triangles from an Alias triangle file
//

#include <stdio.h>
#include "cmdlib.h"
#include "mathlib.h"
#include "trilib.h"
#include "lobjlib.h"

#define MAXVERTS	2000
#define MAX_OBJ_LINE	512
float verts[MAXVERTS][3];

static int parse_ind(char **p)
{
	char *ref = *p;
	int ret;
	ret = atoi(ref);
	while(*ref++) {
		if (*ref == '\n' || *ref == ' ' || *ref == 0)
			break;
	}
	*p = ref;
	return ret;
}

void LoadOBJTriangleList (char *filename, triangle_t **pptri, int *numtriangles)
{
	FILE        *input;
	triangle_t	*ptri;
	int vertindex = 1, triindex = 0;

	if ((input = fopen(filename, "rb")) == 0) {
		fprintf(stderr,"reader: could not open file '%s'\n", filename);
		exit(0);
	}
	ptri = malloc (MAXTRIANGLES * sizeof(triangle_t));
	*pptri = ptri;
	while(!feof(input)) {
		char vline[MAX_OBJ_LINE];
		if(!fgets(vline, MAX_OBJ_LINE, input))
			break;
		if (!strncmp(vline, "v ", 2)) {
			sscanf(vline + 2, "%f %f %f", &verts[vertindex][0],
				&verts[vertindex][1], &verts[vertindex][2]);
			vertindex++;
		} else if (!strncmp(vline, "f ", 2)) {
			int ind1, ind2, ind3, ind4;
			char *p;
			int i;
			printf("line %s\n", vline);
			p = vline + 2;
			ind1 = parse_ind(&p);
			ind2 = parse_ind(&p);
			ind3 = parse_ind(&p);
			ind4 = parse_ind(&p);
			printf("Got indices %d %d %d %d\n",
				ind1, ind2, ind3, ind4);
			for (i = 0; i < 3; i++) {
				ptri[triindex].verts[2][i] = verts[ind1][i];
				ptri[triindex].verts[1][i] = verts[ind2][i];
				ptri[triindex].verts[0][i] = verts[ind3][i];
			}
			triindex++;
			if (ind4 > 0) {
				for (i = 0; i < 3; i++) {
					ptri[triindex].verts[2][i] = verts[ind1][i];
					ptri[triindex].verts[1][i] = verts[ind3][i];
					ptri[triindex].verts[0][i] = verts[ind4][i];
				}
				triindex++;
			}
		}
	}
	*numtriangles = triindex;
	printf("Number of triangles: %d\n", triindex);

	// fread(&tshort, sizeof(tshort), 1, input);

	fclose (input);
}

