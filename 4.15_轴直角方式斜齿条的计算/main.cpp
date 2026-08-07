#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;


/*

端面压力角  End face pressure angle
组装距离
分度圆直径 pitch circle diameter
基圆直径 Base circle diameter
齿顶高 tooth creast height
全齿高 Full tooth height
齿顶圆直径  tip diameter
齿根圆直径  root diameter

*/


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

// 组装距离	 Assembly distance
double calcAssemblyDistance(double z, double m_t, double H, double x_t) {
	return z * m_t / 2 + H + x_t * m_t;
}

// 分度圆直径 pitch circle diameter
double calcPitchCircleDiameter(const double z, const double m_t) {
	return z * m_t;
}

// 基圆直径 Base circle diameter
double calcBaseCircleDiameter(const double d, const double alpha_t_deg) {
	double alpha_t_rad = degToRad(alpha_t_deg);
	return d * cos(alpha_t_rad);
}


// 齿顶高 tooth creast height
double calcToothCreastHeight(const double x_t, const double m_t) {
	return m_t * (1 + x_t);
}

// 全齿高 Full tooth height
double calcFullToothHeight(const double m_t) {
	return 2.25 * m_t;
}

// 齿顶圆直径  tip diameter
double calcTipDiameter(const double d, const double h_a) {
	return d + 2 * h_a;
}

// 齿根圆直径  root diameter
double calcRootdiameter(const double d_a, const double h) {
	return d_a - 2 * h;
}

void print(string name, double value) {
	cout << left << setw(20) << name << " = " << value << endl;
}


int main() {
	double m_t = 2.5;
	double alpha_t_deg = 20;
	double beta_deg = 10 + 57.0 / 60 + 49.0 / 3600;
	double z = 20;
	double x_t = 0;
	double H = 27.5;

	double a = calcAssemblyDistance(z, m_t, H, x_t);
	double d1 = calcPitchCircleDiameter(z, m_t);
	double d_b1 = calcBaseCircleDiameter(d1, alpha_t_deg);
	double h_a1 = calcToothCreastHeight(x_t, m_t);
	double h_a2 = calcToothCreastHeight(x_t, m_t);
	double h = calcFullToothHeight(m_t);
	double d_a1 = calcTipDiameter(d1, h_a1);
	double d_f1 = calcRootdiameter(d_a1, h);

	print("a", a);
	print("d1", d1);
	print("d_b1", d_b1);
	print("h_a1", h_a1);
	print("h_a2", h_a2);
	print("h", h);
	print("d_a1", d_a1);
	print("d_f1", d_f1);
	return 0;
}