#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;


/*

当量齿轮齿数 Equivalent number of gear teeth
端面压力角  End face pressure angle
inv_function: inv_meshing_alpha_n_deg

端面啮合压角 End face meshing pressure angle
中心距变动系数 Center distance variation coefficient
中心距 Center Distance
分度圆直径 pitch circle diameter
基圆直径 Base circle diameter
啮合部的节径 The pitch circle diameter of the meshing part

啮合节圆螺旋角	Meshing pitch circle helix angle
轴交角	Axis Intersection Angle

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

// 当量齿轮齿数 Equivalent number of gear teeth
double calcEquivalentNumberOfGearTeeth(const double z, const double beta_deg){
	double beta_rad = degToRad(beta_deg);
	return z / pow(cos(beta_rad), 3);
}

// 端面压力角  End face pressure angle
double calcEndFacePressureAngle(const double alpha_n_deg, const double beta_deg) {
	double alpha_n_rad = degToRad(alpha_n_deg);
	double beta_rad = degToRad(beta_deg);
	double alpha_t_rad = atan(tan(alpha_n_rad) / cos(beta_rad));
	return radToDeg(alpha_t_rad);
}

// 渐开线函数 meshing_alpha_n_deg   法面啮合压力角  Normal meshing pressure angle
double invNormalMeshingPressireAngle(const double alpha_n_deg, const double x_n1, const double x_n2, const double z_v1, const double z_v2) {
	double alpha_n_rad = degToRad(alpha_n_deg);
	return 2 * tan(alpha_n_rad) * ((x_n1 + x_n2) / (z_v1 + z_v2)) + inv(alpha_n_deg);
}

// 端面啮合压角 End face meshing pressure angle
double calcEndFaceMeshingPressureAngle(double meshing_alpha_n_deg, double beta_deg) {
	double meshing_alpha_n_rad = degToRad(meshing_alpha_n_deg);
	double beta_rad = degToRad(beta_deg);
	double tmp = atan(tan(meshing_alpha_n_rad) / cos(beta_rad));
	return radToDeg(tmp);
}

// 中心距变动系数 Center distance variation coefficient
double calcCenterDistanceVariationCoefficient(const double z_v1, const double z_v2, const double alpha_n_deg, const double meshing_alpha_n_deg) {
	double alpha_n_rad = degToRad(alpha_n_deg);
	double meshing_alpha_n_rad = degToRad(meshing_alpha_n_deg);
	return (z_v1 + z_v2) / 2 * (cos(alpha_n_rad) / cos(meshing_alpha_n_rad) - 1);
}

// 中心距 center distance
double calcCenterDistance(const double z1, double z2, const double beta1_deg, const double beta2_deg, const double y, const double m_n) {
	double beta1_rad = degToRad(beta1_deg);
	double beta2_rad = degToRad(beta2_deg);
	return (z1 / 2 / cos(beta1_rad) + z2 / 2 / cos(beta2_rad) + y) * m_n;
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

double* calcMeshingPartPitchCircleDiameter(const double a, const double d1, const double d2) {
	double* d_meshing = new double[2] {2 * a * d1 / (d1 + d2), 2 * a * d2 / (d1 + d2)};
	return d_meshing;
}

// 啮合节圆螺旋角	Meshing pitch circle helix angle
double calcMeshingPitchCircleHelixAngle(const double d_meshing,const double d, const double beta_deg){
	double beta_rad = degToRad(beta_deg);
	double tmp = atan(d_meshing / d * tan(beta_rad));
	return radToDeg(tmp);
}

// 轴交角	Axis Intersection Angle
double calcAxisIntersectionAngle(const double meshing_beta1_deg, const double meshing_beta2_deg, const bool isSameDirection){
	if (isSameDirection) {
		return meshing_beta1_deg + meshing_beta2_deg;
	}
	else {
		return fabs(meshing_beta1_deg - meshing_beta2_deg);
	}
	return -1;
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
	return (2.25 + y - x_n1 - x_n2) * m_n;
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
	double beta1_deg = 20, beta2_deg = 30;
	double z1 = 15, z2 = 24;
	double x_n1 = 0.4, x_n2 = 0.2;

	double z_v1 = calcEquivalentNumberOfGearTeeth(z1, beta1_deg);
	double z_v2 = calcEquivalentNumberOfGearTeeth(z2, beta2_deg);

	double alpha_t1_deg = calcEndFacePressureAngle(alpha_n_deg, beta1_deg);
	double alpha_t2_deg = calcEndFacePressureAngle(alpha_n_deg, beta2_deg);

	double inv_meshing_alpha_n = invNormalMeshingPressireAngle(alpha_n_deg, x_n1, x_n2, z_v1, z_v2);
	double meshing_alpha_n_deg = invInverse(inv_meshing_alpha_n);

	double meshing_alpha_t1_deg = calcEndFaceMeshingPressureAngle(meshing_alpha_n_deg, beta1_deg);
	double meshing_alpha_t2_deg = calcEndFaceMeshingPressureAngle(meshing_alpha_n_deg, beta2_deg);

	double y = calcCenterDistanceVariationCoefficient(z_v1, z_v2, alpha_n_deg, meshing_alpha_n_deg);
	double a = calcCenterDistance(z1, z2, beta1_deg, beta2_deg, y, m_n);

	double d1 = calcPitchCircleDiameter(z1, m_n, beta1_deg);
	double d2 = calcPitchCircleDiameter(z2, m_n, beta2_deg);

	double d_b1 = calcBaseCircleDiameter(d1, alpha_t1_deg);
	double d_b2 = calcBaseCircleDiameter(d2, alpha_t2_deg);

	double* d_meshing = calcMeshingPartPitchCircleDiameter(a, d1, d2);
	double d_meshing_1 = d_meshing[0];
	double d_meshing_2 = d_meshing[1];

	double meshing_beta1_deg = calcMeshingPitchCircleHelixAngle(d_meshing_1, d1, beta1_deg);
	double meshing_beta2_deg = calcMeshingPitchCircleHelixAngle(d_meshing_2, d2, beta2_deg);

	double sigma = calcAxisIntersectionAngle(meshing_beta1_deg, meshing_beta2_deg, true);

	double* h_a = calcToothCreastHeight(y, x_n1, x_n2, m_n);
	double h_a1 = h_a[0];
	double h_a2 = h_a[1];

	double h = calcFullToothHeight(y, x_n1, x_n2, m_n);

	double d_a1 = calcTipDiameter(d1, h_a1);
	double d_a2 = calcTipDiameter(d2, h_a2);

	double d_f1 = calcRootdiameter(d_a1, h);
	double d_f2 = calcRootdiameter(d_a2, h);

	print("z_v1", z_v1);
	print("z_v2", z_v2);
	print("alpha_t1_deg", alpha_t1_deg);
	print("alpha_t2_deg", alpha_t2_deg);
	print("inv_meshing_alpha_n", inv_meshing_alpha_n);
	print("meshing_alpha_n_deg", meshing_alpha_n_deg);
	print("meshing_alpha_t1_deg", meshing_alpha_t1_deg);
	print("meshing_alpha_t2_deg", meshing_alpha_t2_deg);
	print("y", y);
	print("a", a);
	print("d1", d1);
	print("d2", d2);
	print("d_b1", d_b1);
	print("d_b2", d_b2);
	print("d_meshing_1", d_meshing_1);
	print("d_meshing_2", d_meshing_2);
	print("meshing_beta1_deg", meshing_beta1_deg);
	print("meshing_beta2_deg", meshing_beta2_deg);
	print("sigma", sigma);
	print("h_a1", h_a1);
	print("h_a2", h_a2);
	print("h", h);
	print("d_a1", d_a1);
	print("d_a2", d_a2);
	print("d_f1", d_f1);
	print("d_f2", d_f2);


	return 0;
}