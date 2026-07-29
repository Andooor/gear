#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;


/*

组装距离 Assembly distance
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

// 组装距离 Assembly distance
double calcAssemblyDistance(double z, double m, double H, double x) {
	return z * m / 2 + H + x * m;
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
double calcToothCreastHeight(double m, double x) {
	return m * (1 + x);
}

// 全齿高 Full tooth height
double calcFullToothHeight(double m) {
	return 2.25 * m;
}

// 齿顶圆直径  tip diameter
double calcTipDiameter(double d, double h_a) {
	return d + 2 * h_a;
}


// 齿根圆直径  root diameter
double calcRootDiameter(double d_a, double h) {
	return d_a - 2 * h;
}

void print(string name, double value) {
	cout << left << setw(20) << name << " = " << value << endl;
}

int main() {

	double m = 3;
	double alpha_deg = 20;
	double z = 12;
	double x = 0.6;
	double x0 = 0;
	double H = 32;
	double meshing_alpha_deg = 20;

	double a = calcAssemblyDistance(z, m, H, x);
	double d = calcPitchCircleDiameter(z, m);
	double d_b = calcBaseCircleDiameter(d, alpha_deg);
	double d_meshing = calcPitchCircleDiameterMeshingPart(d_b, meshing_alpha_deg);
	double h_a1 = calcToothCreastHeight(m, x);
	double h_a2 = calcToothCreastHeight(m, x0);
	double h = calcFullToothHeight(m);
	double d_a = calcTipDiameter(d, h_a1);
	double d_f = calcRootDiameter(d_a, h);

	print("a", a);
	print("d", d);
	print("d_b", d_b);
	print("d_meshing", d_meshing);
	print("h_a1", h_a1);
	print("h_a2", h_a2);
	print("h", h);
	print("d_a", d_a);
	print("d_f", d_f);


	return 0;
}









