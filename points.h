// these are the points that i am using to do the maths in the rotation
typedef struct points_a {
	float x;
	float y;
	float z;
}	point_s;

// these are the converted points from 3d to 2d to display the points on the screen
typedef struct renderpoints_a {
	float x2d;
	float y2d;
}	renderpoints_s;