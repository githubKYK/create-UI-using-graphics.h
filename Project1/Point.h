#pragma once

class Point2 {
public:
	Point2() {
		x = 0;
		y = 0;
	}
	Point2(const float& sX, const float& sY) {
		x = sX;
		y = sY;
	}

	float x, y;
};

class Point3 {
public:
	int x, y, z;

	Point3() {
		x = 0;
		y = 0;
		z = 0;
	}

	Point3(const float& sX, const float& sY, const float& sZ) {
		x = sX;
		y = sY;
		z = sZ;
	}
};