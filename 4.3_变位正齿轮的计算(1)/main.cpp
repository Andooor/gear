#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

double degToRad(double deg) {
	return deg * M_PI / 180;
}

double radToDeg(double rad) {
	return rad * 180 / M_PI;
}

double inv(double alpha_deg) {
	return tan(degToRad(alpha_deg)) - degToRad(alpha_deg);
}

// 啮合压力角的渐开线函数 inva~
double calcInvMeshingPressureAngle(double alpha_deg, double x1, double x2, double z1, double z2) {
	double alpha_rad = degToRad(alpha_deg);
	return 2 * tan(alpha_rad) * ((x1 + x2) / (z1 + z2)) + inv(alpha_deg);
}

// 牛顿迭代公式反求压力角
double invInverse(double inva) {
	double a = cbrt(3 * inva);
	const double eps = 1e-12;
	const int maxIter = 20;
	for (int i = 0; i < maxIter; ++i) {
		double f = tan(a) - a - inva;
		double df = tan(a) * tan(a);
		double next = a - f / df;
		if (fabs(next - a) < eps) {
			a = next;
			break;
		}
		a = next;
	}
	return radToDeg(a);
}


// 中心距变动系数 y   Center distance variation coefficient
double calcCenterDistanceVariationCoeffivient(double z1, double z2, double alpha_deg, double meshing_alpha_deg) {
	double alpha_rad = degToRad(alpha_deg);
	double meshing_alpha_rad = degToRad(meshing_alpha_deg);
	return (z1 + z2) / 2 * (cos(alpha_rad) / cos(meshing_alpha_rad) - 1);
}

// 中心距 a
double calcCenterDistance(double z1, double z2, double y, int m) {
	return ((z1 + z2) / 2 + y) * m;
}

// 分度圆直径 d pitch circle diameter
double calcPitchCircleDiameter(double z, int m) {
	return z * m;
}

// 基圆直径 d_b BaseCircleDiameter
double calcBaseCircleDiameter(double d, double alpha_deg) {
	return d * cos( degToRad(alpha_deg) );
}

// 啮合部的节圆直径  d~ Meshing part node diameter
double calcMeshingPartNodeDiameter(double d_b, double meshing_alpha_deg) {
	return d_b / cos(degToRad(meshing_alpha_deg));
}

// 齿顶高 h_a  Tooth crest height
double calcToothCrestHeight(double y, double x, int m) {
	return (1 + y - x )* m;
}

// 全齿高 h  Full tooth height
double calcFullToothHeight(double y, double x1, double x2, int m) {
	return (2.25 + y - x1 - x2) * m;
}

// 齿顶圆直径 d_a  tip diameter
double calcTipDiameter(double d, double h_a) {
	return d + 2 * h_a;
}

// 齿根圆直径 d_f  root diameter
double calcRootDiameter(double d_a, double h) {
	return d_a - 2 * h;
}


void print(string name, double value) {
	cout << left << setw(20) << name << " = " << value << endl;
}

int main() {
	int m = 3;
	double alpha_deg = 20;
	double z1 = 12, z2 = 24;
	double x1 = 0.6, x2 = 0.36;

	double inv_meshing_alpha = calcInvMeshingPressureAngle(alpha_deg, x1, x2, z1, z2);
	
	double meshing_alpha_deg = invInverse(inv_meshing_alpha);
	double y = calcCenterDistanceVariationCoeffivient(z1, z2, alpha_deg, meshing_alpha_deg);
	double a = calcCenterDistance(z1, z2, y, m);
	double d1 = calcPitchCircleDiameter(z1, m);
	double d2 = calcPitchCircleDiameter(z2, m);

	double d_b1 = calcBaseCircleDiameter(d1, alpha_deg);
	double d_b2 = calcBaseCircleDiameter(d2, alpha_deg);

	double d_n1 = calcMeshingPartNodeDiameter(d_b1, meshing_alpha_deg);
	double d_n2 = calcMeshingPartNodeDiameter(d_b2, meshing_alpha_deg);

	double h_a1 = calcToothCrestHeight(y, x2, m);
	double h_a2 = calcToothCrestHeight(y, x1, m);

	double h = calcFullToothHeight(y, x1, x2, m);
	double d_a1 = calcTipDiameter(d1, h_a1);
	double d_a2 = calcTipDiameter(d2, h_a2);

	double d_f1 = calcRootDiameter(d_a1, h);
	double d_f2 = calcRootDiameter(d_a2, h);



	print("inv_meshing_alpha", inv_meshing_alpha);
	print("meshing_alpha_deg", meshing_alpha_deg);
	print("y", y);
	print("a", a);
	print("d1", d1);
	print("d2", d2);
	print("d_b1", d_b1);
	print("d_b2", d_b2);
	print("d_n1", d_n1);
	print("d_n2", d_n2);
	print("h_a1", h_a1);
	print("h_a2", h_a2);
	print("h", h);
	print("d_a1", d_a1);
	print("d_a2", d_a2);
	print("d_f1", d_f1);
	print("d_f2", d_f2);
	


	return 0;
}