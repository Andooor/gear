
/*
	分度圆柱导程角	Pitch cylinder lead angle
	切向变位系数	Tangential shift coefficient
	中心距			centerDistance
	齿顶高			tooth creast height
	全齿高			Full tooth height
	齿顶圆直径		tip diameter
	喉径			Throat diameter
	喉圆半径		Radius of throat circle
	齿根圆直径		root diameter

*/

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;


double degToRad(const double deg) {
	return deg * M_PI / 180;
}

double radToDeg(const double rad) {
	return rad / M_PI * 180;
}
double inv(const double alpha_deg) {
	return tan(degToRad(alpha_deg)) - degToRad(alpha_deg);
}
// 牛顿迭代公式反求压力角
double invInverse(const double n) {
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

// 分度圆柱导程角	Pitch cylinder lead angle
double calcPitchCylinderLeadAngle(double m_x, double z1, double d1){
	double tmp = atan(m_x * z1 / d1);
	return radToDeg(tmp);
}

// 中心距	centerDistance
double calcCenterDistance(double d1, double d2, double x_t2, double m_x) {
	return (d1 + d2) / 2 + x_t2 * m_x;
}

// 齿顶高	tooth creast height
double* calcToothCreastHeight(double x_t2, double m_x) {
	double h_a1 = 1.00 * m_x;
	double h_a2 = (1.00 + x_t2) * m_x;
	double* h_a = new double[2] {h_a1, h_a2};
	return h_a;
}

// 全齿高	Full tooth height
double calcFullToothHeight(double m_x) {
	return 2.25 * m_x;
}

// 齿顶圆直径	tip diameter
double* calcTipDiameter(double d1, double d2, double h_a1, double h_a2, double m_x) {
	double d_a1 = d1 + 2 * h_a1;
	double d_a2 = d2 + 2 * h_a2 + m_x;
	double* d_a = new double[2] {d_a1, d_a2};
	return d_a;
}

// 喉径	Throat diameter
double calcThroatDiameter(double d2, double h_a2) {
	return d2 + 2 * h_a2;
}

// 喉圆半径	Radius of throat circle
double calcRadiusOfThroatCircle(double d1, double h_a1) {
	return d1 / 2 - h_a1;
}

// 齿根圆直径	root diameter
double* calcRootDiameter(double d_a1, double h, double d_t) {
	double d_f1 = d_a1 - 2 * h;
	double d_f2 = d_t - 2 * h;
	double* d_f = new double[2] {d_f1, d_f2};
	return d_f;
}

void print(string name, double value) {
	cout << left << setw(20) << name << " = " << value << endl;
}


int main() {
	double m_x = 3;
	double alpha_n_deg = 20;
	double z1 = 2, z2 = 30;
	double d1 = 44, d2 = 90;
	double x_t2 = 0;

	double gamma_deg = calcPitchCylinderLeadAngle(m_x, z1, d1);
	double a = calcCenterDistance(d1, d2, x_t2, m_x);
	
	double* h_a = calcToothCreastHeight(x_t2, m_x);
	double h_a1 = h_a[0];
	double h_a2 = h_a[1];

	double h = calcFullToothHeight(m_x);

	double* d_a = calcTipDiameter(d1, d2, h_a1, h_a2, m_x);
	double d_a1 = d_a[0];
	double d_a2 = d_a[1];
	
	double d_t = calcThroatDiameter(d2, h_a2);
	double r_i = calcRadiusOfThroatCircle(d1, h_a1);
	
	double* d_f = calcRootDiameter(d_a1, h, d_t);
	double d_f1 = d_f[0];
	double d_f2 = d_f[1];


	print("gamma_deg", gamma_deg);
	print("a", a);
	print("h_a1", h_a1);
	print("h_a2", h_a2);
	print("h", h);
	print("d_a1", d_a1);
	print("d_a2", d_a2);
	print("d_t", d_t);
	print("r_i", r_i);
	print("d_f1", d_f1);
	print("d_f2", d_f2);


	return 0;
}