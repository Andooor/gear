#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;


/*
	
啮合压力角 meshing pressure angle
中心距变动系数 Center distance variation coefficient
中心距 center distance

分度圆直径 pitch circle diameter
基圆直径 Base circle diameter
啮合部的节径 The pitch circle diameter of the meshing part
齿顶高 tooth creast height
全齿高 Full tooth height
齿顶圆直径  tip diameter
齿根圆直径  root diameter

*/


double degToRad(double deg) {
	return deg * M_PI / 180;
}

double radToDeg(double rad) {
	return rad / M_PI * 180;
}
double inv(double alpha_deg) {
	return tan(degToRad(alpha_deg)) - degToRad(alpha_deg);
}

double invＭeshing(double alpha_deg, double z1, double z2, double x1, double x2) {
	return 2 * tan(degToRad(alpha_deg)) * (x2 - x1) / (z2 - z1) + inv(alpha_deg);
}

// 牛顿迭代公式反求压力角
double invInverse(double n) {
	double a = cbrt(3 * n);
	const double eps = 1e-12;
	const int maxIter = 20;
	for (int i = 0; i < maxIter; ++i) {
		double f = tan(a) - a - n;
		double df = tan(a) * tan(a);
		double next = a - f / df;
		if (fabs(a - next) < eps) {
			a = next;
			break;
		}
		a = next;
	}
	return radToDeg(a);
}

// 中心距变动系数 Center distance variation coefficient
double calcCenterDistanceVariationCoefficient(double z1, double z2, double alpha_deg, double alpha_meshing_deg) {
	double alpha_rad = degToRad(alpha_deg);
	double alpha_meshing_rad = degToRad(alpha_meshing_deg);
	return (z2 - z1) / 2 * ( cos(alpha_rad) / cos(alpha_meshing_rad) - 1);
}

// 中心距 center distance
double calcCenterDistance(double z1, double z2, double y, double m) {
	return ((z2 - z1) / 2 + y) * m;
}

// 分度圆直径 pitch circle diameter
double calcPitchCircleDiameter(double z, double m) {
	return z * m;
}

// 基圆直径 Base circle diameter
double calcBaseCircleDiameter(double d, double alpha_deg) {
	return d * cos(degToRad(alpha_deg));
}

// 啮合部的节径 The pitch circle diameter of the meshing part
double calcPitchCircleDiameterMeshingPart(double d_b, double meshing_alpha_deg) {
	return d_b / cos(degToRad(meshing_alpha_deg));
}

// 齿顶高 tooth creast height
double calcToothCreastHeight(double x, double m, string gearType) {
	if (gearType == "inGear") {
		return (1 - x) * m;
	}
	else if (gearType == "outGear") {
		return (1 + x) * m;
	}
	return -1;
}

// 全齿高 Full tooth height
double calcFullToothHeight(double m) {
	return 2.25 * m;
}

// 齿顶圆直径  tip diameter
double calcTipDiameter(double d, double h_a, string gearType) {
	if (gearType == "inGear") {
		return  d - 2 * h_a;
	}
	else if (gearType == "outGear") {
		return d + 2 * h_a;
	}
	return -1;
}

// 齿根圆直径  root diameter
double calcRootDiameter(double d_a, double h, string gearType) {
	if (gearType == "inGear") {
		return  d_a  + 2 * h;
	}
	else if (gearType == "outGear") {
		return d_a - 2 * h;
	}
	return -1;
}

void print(string name, double value) {
	cout << left << setw(20) << name << " = " << value << endl;
}


int main() {
	
	double m = 3;
	double alpha_deg = 20;
	double z1 = 16, z2 = 24;
	double x1 = 0, x2 = 0.5;

	double inv_alpha_meshing = invＭeshing(alpha_deg, z1, z2, x1, x2);
	double meshing_alpha_deg = invInverse(inv_alpha_meshing);
	double y = calcCenterDistanceVariationCoefficient(z1, z2, alpha_deg, meshing_alpha_deg);
	double a = calcCenterDistance(z1, z2, y, m);
	
	double d1 = calcPitchCircleDiameter(z1, m);
	double d2 = calcPitchCircleDiameter(z2, m);

	double d_b1 = calcBaseCircleDiameter(d1, alpha_deg);
	double d_b2 = calcBaseCircleDiameter(d2, alpha_deg);

	double d_meshing1 = calcPitchCircleDiameterMeshingPart(d_b1, meshing_alpha_deg);
	double d_meshing2 = calcPitchCircleDiameterMeshingPart(d_b2, meshing_alpha_deg);

	double h_a1 = calcToothCreastHeight(x1, m, "outGear");
	double h_a2 = calcToothCreastHeight(x2, m, "inGear");

	double h = calcFullToothHeight(m);

	double d_a1 = calcTipDiameter(d1, h_a1, "outGear");
	double d_a2 = calcTipDiameter(d2, h_a2, "inGear");

	double d_f1 = calcRootDiameter(d_a1, h, "outGear");
	double d_f2 = calcRootDiameter(d_a2, h, "inGear");



	print("inv_alpha_meshing", inv_alpha_meshing);
	print("meshing_alpha_deg", meshing_alpha_deg);
	print("y", y);
	print("a", a);
	print("d1", d1);
	print("d2", d2);
	print("d_b1", d_b1);
	print("d_b2", d_b2);
	print("d_meshing1", d_meshing1);
	print("d_meshing2", d_meshing2);
	print("h_a1", h_a1);
	print("h_a2", h_a2);
	print("h", h);
	print("d_a1", d_a1);
	print("d_a2", d_a2);
	print("d_f1", d_f1);
	print("d_f2", d_f2);

	return 0;
}
