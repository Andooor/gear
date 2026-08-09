#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

/*
	分度圆直径		pitch circle diameter
	分度锥角		dividing cone angle
	大端锥距		Large pitch cone
	齿宽			tooth width
	大端齿顶高		Large end tooth top height
	齿根高			Tooth root height
	齿根角			Tooth root angle
	齿顶角			tip angle
	顶锥角			Top cone angle
	根锥角			Root cone angle
	大端齿顶圆直径	Large end tooth tip circle diameter
	冠顶距			Crown distance
	齿顶间轴向距	Axial distance between tooth tips
	小端齿顶圆直径	Small end tooth tip circle diameter
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


// 分度圆直径	pitch circle diameter
double calcPitchCircleDiameter(const double z, const double m) {
	return z * m;
}

// 分度锥角		dividing cone angle
double* calcDividingConeAngle(const double sigma_deg, const double z1, const double z2) {
	double sigma_rad = degToRad(sigma_deg);
	double delta1_rad = atan(sin(sigma_rad) / (z2 / z1 + cos(sigma_rad)));
	double delta2_rad = sigma_rad - delta1_rad;
	double* delta = new double[2] {radToDeg(delta1_rad), radToDeg(delta2_rad)};
	return delta;
}

// 大端锥距		Large pitch cone
double calcLargePitchCone(const double d2, const double delta2_deg) {
	double delta2_rad = degToRad(delta2_deg);
	return d2 / 2 / sin(delta2_rad);
}

// 齿宽			tooth width
double calcToothWidth(double R) {
	return floor(R / 3);
}

// 大端齿顶高		Large end tooth top height
double calcLargeEndToothTopHeight(const double m) {
	return 1 * m;
}

// 大端齿根高		Large end Tooth root height
double calcLargeEndToothRootHeight(const double m) {
	return 1.25 * m;
}

// 齿根角			Tooth root angle
double calcToothRootAngle(const double h_f, const double R) {
	double theta_f_rad = atan(h_f / R);
	return radToDeg(theta_f_rad);
}

// 齿顶角			tip angle
double calcTipAngle(const double h_a, const double R) {
	double theta_a_rad = atan(h_a / R);
	return radToDeg(theta_a_rad);
}

// 顶锥角			Top cone angle
double calcTopConeAngle(const double delta_deg, const double theta_a_deg) {
	return delta_deg + theta_a_deg;
}

// 根锥角			Root cone angle
double calcRootConeAngle(const double delta_deg, const double theta_f_deg) {
	return delta_deg - theta_f_deg;
}

// 大端齿顶圆直径	Large end tooth tip circle diameter
double calcLargeEndToothTipCircleDiameter(const double d, const double h_a, const double delta_deg) {
	return d + 2 * h_a * cos(degToRad(delta_deg));
}

// 冠顶距	Crown distance
double calcCrownDistance(const double R, const double h_a, const double delta_deg) {
	double delta_rad = degToRad(delta_deg);
	return R * cos(delta_rad) - h_a * sin(delta_rad);
}

// 齿顶间轴向距	Axial distance between tooth tips
double calcAxialDistanceBetweenToothTips(const double b, const double delta_a_deg, const double theta_a_deg) {
	double delta_a_rad = degToRad(delta_a_deg);
	double theta_a_rad = degToRad(theta_a_deg);
	return b * cos(delta_a_rad) / cos(theta_a_rad);
}

// 小端齿顶圆直径	Small end tooth tip circle diameter
double calcSmallEndToothTipCircleDiameter(const double d_a, const double b, const double delta_a_deg, const double theta_a_deg) {
	double delta_a_rad = degToRad(delta_a_deg);
	double theta_a_rad = degToRad(theta_a_deg);
	return d_a - 2 * b * sin(delta_a_rad) / cos(theta_a_rad);
}

void print(const string name, const double value) {
	cout << left << setw(16) << name << " = " << value << endl;
}

int main() {
	double sigma_deg = 90;
	double m = 3;
	double alpha_deg = 20;
	double z1 = 20, z2 = 40;

	double d1 = calcPitchCircleDiameter(z1, m);
	double d2 = calcPitchCircleDiameter(z2, m);

	double* delta_deg = calcDividingConeAngle(sigma_deg, z1, z2);
	double delta1_deg = delta_deg[0];
	double delta2_deg = delta_deg[1];

	double R = calcLargePitchCone(d2, delta2_deg);
	double b = calcToothWidth(R);

	double h_a = calcLargeEndToothTopHeight(m);


	double h_f = calcLargeEndToothRootHeight(m);

	double theta_f_deg = calcToothRootAngle(h_f, R);

	double theta_a_deg = calcTipAngle(h_a, R);

	double delta_a1_deg = calcTopConeAngle(delta1_deg, theta_a_deg);
	double delta_a2_deg = calcTopConeAngle(delta2_deg, theta_a_deg);

	double delta_f1_deg = calcRootConeAngle(delta1_deg, theta_f_deg);
	double delta_f2_deg = calcRootConeAngle(delta2_deg, theta_f_deg);

	double d_a1 = calcLargeEndToothTipCircleDiameter(d1, h_a, delta1_deg);
	double d_a2 = calcLargeEndToothTipCircleDiameter(d2, h_a, delta2_deg);

	double X1 = calcCrownDistance(R, h_a, delta1_deg);
	double X2 = calcCrownDistance(R, h_a, delta2_deg);

	double X_b1 = calcAxialDistanceBetweenToothTips(b, delta_a1_deg, theta_a_deg);
	double X_b2 = calcAxialDistanceBetweenToothTips(b, delta_a2_deg, theta_a_deg);

	double d_i1 = calcSmallEndToothTipCircleDiameter(d_a1, b, delta_a1_deg, theta_a_deg);
	double d_i2 = calcSmallEndToothTipCircleDiameter(d_a2, b, delta_a2_deg, theta_a_deg);



	print("d1", d1);
	print("d2", d2);
	print("delta1_deg", delta1_deg);
	print("delta2_deg", delta2_deg);
	print("R", R);
	print("b", b);
	print("h_a", h_a);
	print("h_f", h_f);
	print("theta_f_deg", theta_f_deg);
	print("theta_a_deg", theta_a_deg);
	print("delta_a1_deg", delta_a1_deg);
	print("delta_a2_deg", delta_a2_deg);
	print("delta_f1_deg", delta_f1_deg);
	print("delta_f2_deg", delta_f2_deg);
	print("d_a1", d_a1);
	print("d_a2", d_a2);
	print("X1", X1);
	print("X2", X2);
	print("X_b1", X_b1);
	print("X_b2", X_b2);
	print("d_i1", d_i1);
	print("d_i2", d_i2);

	return 0;
}