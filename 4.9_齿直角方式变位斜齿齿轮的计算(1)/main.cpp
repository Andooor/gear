#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;


/*
* 
端面压力角  Transverse pressure angle
端面啮合压力角  Transverse Pressure Angle
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


// 端面压力角  Transverse pressure angle
double calcTransversePressureAngle(const double alpha_n_deg, const double beta_deg) {
	double alpha_n_rad = degToRad(alpha_n_deg);
	double beta_rad = degToRad(beta_deg);
	double alpha_t_rad = atan(tan(alpha_n_rad) / cos(beta_rad));
	return radToDeg(alpha_t_rad);
}

// 渐开线函数 meshing_alpha_t_deg
double invMeshingTramsversePressireAngle(const double alpha_n_deg, const double alpha_t_deg, const double x_n1, const double x_n2, const double z1, const double z2) {
	double alpha_n_rad = degToRad(alpha_n_deg);
	return 2 * tan(alpha_n_rad) * (x_n1 + x_n2) / (z1 + z2) + inv(alpha_t_deg);
}

// 中心距变动系数 Center distance variation coefficient
double calcCenterDistanceVariationCoefficient(const double z1, const double z2, const double beta_deg, const double alpha_t_deg, const double meshing_alpha_t_deg) {
	double beta_rad = degToRad(beta_deg);
	double alpha_t_rad = degToRad(alpha_t_deg);
	double meshing_alpha_t_rad = degToRad(meshing_alpha_t_deg);
	return (cos(alpha_t_rad) / cos(meshing_alpha_t_rad) - 1) * (z1 + z2) / 2 / cos(beta_rad);
}

// 中心距 center distance
double calcCenterDistance(const double z1, double z2, const double beta_deg, const double y, const double m_n) {
	double beta_rad = degToRad(beta_deg);
	return ((z1 + z2) / 2 / cos(beta_rad) + y) * m_n;
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

// 啮合部的节径 The pitch circle diameter of the meshing part

double calcMeshingPartPitchCircleDiameter(const double d_b, const double meshing_alpha_t_deg) {
	double meshing_alpha_t_rad = degToRad(meshing_alpha_t_deg);
	return d_b / cos(meshing_alpha_t_rad);
}

// 齿顶高 tooth creast height
double* calcToothCreastHeight(const double y, const double x_n1, const double x_n2, const double m_n) {
	double h_a1 = (1 + y - x_n2) * m_n;
	double h_a2 = (1 + y - x_n1) * m_n;
	double* h_a = new double[2] {h_a1, h_a2};
	return h_a;
}

// 全齿高 Full tooth height
double calcFullToothHeight(const double y, const double x_n1, const double x_n2, const double m_n) {
	return (2.25 + y - x_n1 - x_n2)* m_n;
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
	double m_n = 3;
	double alpha_n_deg = 20;
	double beta_deg = 30;
	double z1 = 12, z2 = 60;
	double x_n1 = 0.09809, x_n2 = 0;

	double alpha_t_deg = calcTransversePressureAngle(alpha_n_deg, beta_deg);
	double inv_meshing_alpha_t = invMeshingTramsversePressireAngle(alpha_n_deg, alpha_t_deg, x_n1, x_n2, z1, z2);
	double meshing_alpha_t_deg = invInverse(inv_meshing_alpha_t);
	double y = calcCenterDistanceVariationCoefficient(z1, z2, beta_deg, alpha_t_deg, meshing_alpha_t_deg);
	double a = calcCenterDistance(z1, z2, beta_deg, y, m_n);
	double d1 = calcPitchCircleDiameter(z1, m_n, beta_deg);
	double d2 = calcPitchCircleDiameter(z2, m_n, beta_deg);
	double d_b1 = calcBaseCircleDiameter(d1, alpha_t_deg);
	double d_b2 = calcBaseCircleDiameter(d2, alpha_t_deg);
	double d_meshing_1 = calcMeshingPartPitchCircleDiameter(d_b1, meshing_alpha_t_deg);
	double d_meshing_2 = calcMeshingPartPitchCircleDiameter(d_b2, meshing_alpha_t_deg);
	double* h_a = calcToothCreastHeight(y, x_n1, x_n2, m_n);
	double h_a1 = h_a[0];
	double h_a2 = h_a[1];
	double h = calcFullToothHeight(y, x_n1, x_n2, m_n);
	double d_a1 = calcTipDiameter(d1, h_a1);
	double d_a2 = calcTipDiameter(d2, h_a2);
	double d_f1 = calcRootdiameter(d_a1, h);
	double d_f2 = calcRootdiameter(d_a2, h);


	print("alpha_t_deg", alpha_t_deg);
	print("inv_meshing_alpha_t", inv_meshing_alpha_t);
	print("meshing_alpha_t_deg", meshing_alpha_t_deg);
	print("y", y);
	print("a", a);
	print("d1", d1);
	print("d2", d2);
	print("d_b1", d_b1);
	print("d_b2", d_b2);
	print("d_meshing_1", d_meshing_1);
	print("d_meshing_2", d_meshing_2);
	print("h_a1", h_a1);
	print("h_a2", h_a2);
	print("h", h);
	print("d_a1", d_a1);
	print("d_a2", d_a2);
	print("d_f1", d_f1);
	print("d_f2", d_f2);


	return 0;
}