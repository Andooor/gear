
/*

	轴向模数				Axial modulus
	法向齿形角				Normal tooth profile angle
	蜗杆的头数				Number of worm heads
	蜗杆的分度圆直径		pitch circle diameter
	分度圆柱导程角			Dividing cylinder lead angle
	轴平面齿形角			Axial plane tooth profile angle
	轴向齿距				Axial tooth pitch
	导程					lead

	修正后 轴向齿距			Corrected axial tooth pitch
	修正后 轴平面齿形角		Corrected Axial plane tooth profile angle
	修正后 轴向模数			Corrected Axial modulus
	修正后 分度圆柱导程角	Corrected Dividing cylinder lead angle
	修正后 法向齿形角		Corrected Normal tooth profile angle
	修正后 导程				Corrected lead

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


//分度圆柱导程角			Dividing cylinder lead angle
double calcDividingCylinderLeadAngle(double m_x_unc, double z1, double d1) {
	double tmp = atan(m_x_unc * z1 / d1);
	return radToDeg(tmp);
}

//轴平面齿形角			Axial plane tooth profile angle
double calcAxialPlaneToothProfileAngle(double alpha_n_deg_unc, double gamma_deg_unc) {
	double alpha_n_rad_unc = degToRad(alpha_n_deg_unc);
	double gamma_rad_unc = degToRad(gamma_deg_unc);
	double tmp = atan(tan(alpha_n_rad_unc) / cos(gamma_rad_unc));
	return radToDeg(tmp);
}

//轴向齿距				Axial tooth pitch
double calcAxialToothPitch(double m_x_unc) {
	return M_PI * m_x_unc;
}

//导程					lead
double calcLead(double m_x_unc, double z1) {
	return M_PI * m_x_unc * z1;
}


//修正后 轴向齿距			Corrected axial tooth pitch
double calcCorrectedAxialToothPitch(double p_x_unc, double C_R, double k, double d1) {
	return p_x_unc * (2 * C_R / k / d1 + 1);
}

//修正后 轴平面齿形角		Corrected Axial plane tooth profile angle
double calcCorrectedAxialPlaneToothProfileAngle(double p_x_unc, double p_x_cor, double alpha_x_deg_unc) {
	double alpha_x_rad_unc = degToRad(alpha_x_deg_unc);
	double tmp = acos(p_x_unc / p_x_cor * cos(alpha_x_rad_unc));
	return radToDeg(tmp);
}

//修正后 轴向模数			Corrected Axial modulus
double calcCorrectedAxialModulus(double p_x_cor) {
	return p_x_cor / M_PI;
}

//修正后 分度圆柱导程角	Corrected Dividing cylinder lead angle
double calcCorrectedDividingCylinderLeadAngle(double m_x_cor, double z1, double d1) {
	double tmp = atan(m_x_cor * z1 / d1);
	return radToDeg(tmp);
}

//修正后 法向齿形角		Corrected Normal tooth profile angle
double calcCorrectedNormalToothProfileAngle(double alpha_x_deg_cor, double gamma_deg_cor) {
	double alpha_x_rad_cor = degToRad(alpha_x_deg_cor);
	double gamma_rad_cor = degToRad(gamma_deg_cor);
	double tmp = atan(tan(alpha_x_rad_cor) * cos(gamma_rad_cor));
	return radToDeg(tmp);
}

//修正后 导程				Corrected lead
double calcCorrectedLead(double m_x_cor, double z1) {
	return M_PI * m_x_cor * z1;
}

void print(string name, double value) {
	cout << left << setw(20) << name << " = " << value << endl;
}

int main() {

	double C_R = 0.04;
	double k = 0.41;
	double m_x_unc = 3;
	double alpha_n_deg_unc = 20;
	double z1 = 2;
	double d1 = 44;


	double gamma_deg_unc = calcDividingCylinderLeadAngle(m_x_unc, z1, d1);
	double alpha_x_deg_unc = calcAxialPlaneToothProfileAngle(alpha_n_deg_unc, gamma_deg_unc);
	double p_x_unc = calcAxialToothPitch(m_x_unc);
	double p_z_unc = calcLead(m_x_unc, z1);


	double p_x_cor = calcCorrectedAxialToothPitch(p_x_unc, C_R, k, d1);
	double alpha_x_deg_cor = calcCorrectedAxialPlaneToothProfileAngle(p_x_unc, p_x_cor, alpha_x_deg_unc);
	double m_x_cor = calcCorrectedAxialModulus(p_x_cor);
	double gamma_deg_cor = calcCorrectedDividingCylinderLeadAngle(m_x_cor, z1, d1);
	double alpha_n_deg_cor = calcCorrectedNormalToothProfileAngle(alpha_x_deg_cor, gamma_deg_cor);
	double p_z_cor = calcCorrectedLead(m_x_cor, z1);


	print("gamma_deg_unc", gamma_deg_unc);
	print("alpha_x_deg_unc", alpha_x_deg_unc);
	print("p_x_unc", p_x_unc);
	print("p_z_unc", p_z_unc);
	cout << "-------------------------------------------" << endl;
	print("p_x_cor", p_x_cor);
	print("alpha_x_deg_cor", alpha_x_deg_cor);
	print("m_x_cor", m_x_cor);
	print("gamma_deg_cor", gamma_deg_cor);
	print("alpha_n_deg_cor", alpha_n_deg_cor);
	print("p_z_cor", p_z_cor);
	


	return 0;
}