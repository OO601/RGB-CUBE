#pragma once

#include <iostream>
#include <vector>
#include <math.h>
class Cube {


	float CDis = 0;





	std::vector<std::vector<int>> faces =
	{
		{0,1,5,4},
		{1,2,6,5},
		{2,3,7,6},
		{3,0,4,7},
		{0,1,2,3},
		{4,5,6,7}

	};


	struct Vector3D {
		float x, y, z;
		Vector3D()
		{
			x = 0, y = 0, z = 0;
		}
		Vector3D(float X, float Y, float Z)
		{
			x = X; y = Y; z = Z;

		}
		Vector3D operator +(Vector3D vec) { return Vector3D(vec.x+x,vec.y+y,vec.z+z); }
		Vector3D operator *(float a) { return Vector3D(x * a, y * a, z * a); }

	};

	Vector3D vertex[8] =
	{
		Vector3D(-1, -1,  1),
		Vector3D( 1, -1,  1),
		Vector3D( 1, -1, -1),
		Vector3D(-1, -1, -1),
		Vector3D(-1,  1,  1),
		Vector3D( 1,  1,  1),
		Vector3D( 1,  1, -1),
		Vector3D(-1,  1, -1)

	};

	Vector3D center = Vector3D(0, 0, 0);


	void move()
	{
		for (int i = 0; i < 8; i++)
		{

			C3D[i] = center + vertex[i] * CDis ;
		}
	}

	float calcDistance(Vector3D view, Vector3D obj)
	{
		float xcb = (view.x - obj.x) * (view.x - obj.x);
		float ycb = (view.y - obj.y) * (view.y - obj.y);
		float zcb = (view.z - obj.z) * (view.z - obj.z);
		return sqrtf(xcb + ycb + zcb);

	}


	void updateDistances(Vector3D view)
	{



		distances[8] = distances[0] = calcDistance(view, C3D[0]);

		for (int i = 1; i < 8; i++)
		{
			distances[i] = calcDistance(view, C3D[i]);
			Dist[i] = distances[i];
			if (distances[i] > distances[8])distances[8] = distances[i];
		}
		for (int i = 0; i < 8; i++)
		{
			if (distances[i] == distances[8])distances[i] = 0;
			else distances[i] = (i + 1);

		}


	}

	void rotateX(float angle)
	{
		float sinF = sin(angle);
		float cosF = cos(angle);
		for (int i = 0; i < 8; i++)
		{
			float y = vertex[i].y;
			float z = vertex[i].z;

			vertex[i].y = y * cosF - z * sinF;
			vertex[i].z = z * cosF + y * sinF;
		}

	}

	void rotateY(float angle)
	{
		float sinF = sin(angle);
		float cosF = cos(angle);
		for (int i = 0; i < 8; i++)
		{
			float x = vertex[i].x;
			float z = vertex[i].z;

			vertex[i].x = x * cosF + z * sinF;
			vertex[i].z = z * cosF - x * sinF;
		}
		move();

	}
	void rotateZ(float angle)
	{
		float sinF = sin(angle);
		float cosF = cos(angle);
		for (int i = 0; i < 8; i++)
		{
			float x = vertex[i].x;
			float y = vertex[i].y;

			vertex[i].x = x * cosF - y * sinF;
			vertex[i].y = y * cosF + x * sinF;

		}
		move();

	}




	float* distances=nullptr;

public :

    Vector3D*                     C3D;
    float                         Dist[8];
	std::vector<std::vector<int>> show;
	Cube(float _size)
	{
		CDis      = _size / 2;
		C3D       = new Vector3D[8];
		distances = new float[9];


		move();

	}

	void draw(float x, float y, float z)
	{

		show.clear();
		updateDistances(Vector3D(x, y, z));
		for (int face = 0; face < 6; face++)
		{
			int index = 0;
			for (int corner = 0; corner < 4; corner++)
				index += faces[face][corner] - (distances[faces[face][corner]]-1);
			if (index == 0)show.push_back(faces[face]);

		}

	}

	float distanceTo(float x, float y, float z)
	{
		return calcDistance(center, Vector3D(x, y, z));
	}

	void rotate(float alfaX, float alfaY, float alfaZ)
	{
		rotateX(alfaX);
		rotateY(alfaY);
		rotateZ(alfaZ);
	}

	void move(float x, float y, float z)
	{
		center = Vector3D(x, y, z);
		move();

	}



};
