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
double calcAssemblyDistance(double z, double m_n, double beta_deg, double H, double x_n) {
	double beta_rad = degToRad(beta_deg);
	return z * m_n / 2 / cos(beta_rad) + H + x_n * m_n;
}

// 端面压力角  End face pressure angle
double calcEndFacePressureAngle(const double alpha_n_deg, const double beta_deg) {
	double alpha_n_rad = degToRad(alpha_n_deg);
	double beta_rad = degToRad(beta_deg);
	double alpha_t_rad = atan(tan(alpha_n_rad) / cos(beta_rad));
	return radToDeg(alpha_t_rad);
}


// 分度圆直径 pitch circle diameter
double calcPitchCircleDiameter(const double z, const double m_n, const double beta_deg) {
	double beta_rad = degToRad(beta_deg);
	return z * m_n / cos(beta_rad);
}

// 基圆直径 Base circle diameter
double calcBaseCircleDiameter(const double d, const double alpha_t_deg) {
	double alpha_t_rad = degToRad(alpha_t_deg);
	return d * cos(alpha_t_rad);
}


// 齿顶高 tooth creast height
double calcToothCreastHeight(const double x_n, const double m_n) {
	return m_n * (1 + x_n);
}

// 全齿高 Full tooth height
double calcFullToothHeight(const double m_n) {
	return 2.25 * m_n;
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
	double m_n = 2.5;
	double alpha_n_deg = 20;
	double beta_deg = 10 + 57.0 / 60 + 49.0 / 3600;
	double z = 20;
	double x_n = 0;
	double H = 27.5;

	double alpha_t_deg = calcEndFacePressureAngle(alpha_n_deg, beta_deg);
	double a = calcAssemblyDistance(z, m_n, beta_deg, H, x_n);
	double d1 = calcPitchCircleDiameter(z, m_n, beta_deg);
	double d_b1 = calcBaseCircleDiameter(d1, alpha_t_deg);
	double h_a1 = calcToothCreastHeight(x_n, m_n);
	double h_a2 = calcToothCreastHeight(x_n, m_n);
	double h = calcFullToothHeight(m_n);
	double d_a1 = calcTipDiameter(d1, h_a1);
	double d_f1 = calcRootdiameter(d_a1, h);

	print("alpha_t_deg", alpha_t_deg);
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