#define _USE_MATH_DEFINES
#define RAD_TO_DEG (180 / M_PI)
#define DEG_TO_RAD (M_PI / 180)

#include <iostream>
#include <cmath>

using namespace std;

double radToDeg(double rad);
double degToRad(double deg);
double invDeg(double alpha);
double calcToothTipCirclePressureAngle(double d_b, double d_a);
double calcToothThicknessHalfAngle(int z, double x, double alpha_deg, double alpha_a_deg);
double calcToothTipThickness(double phsi, double d_a);


double radToDeg(double rad) {
	return rad * 180 / M_PI;
}

double degToRad(double deg) {
	return deg * M_PI / 180;
}

// inv a = tan a - a ;
double invDeg(double alpha_deg) {
	return tan(alpha_deg * DEG_TO_RAD) - alpha_deg * DEG_TO_RAD;
}

/*
	齿顶圆压力角  Tooth tip circle pressure angle
	d-b:基圆直径     d_a : 齿顶圆直径
*/

double calcToothTipCirclePressureAngle(double d_b, double d_a) {
	return acos(d_b / d_a);
}


/*
	齿顶圆齿厚半角 Tooth tip circular, tooth thickness half angle
	z: 齿数  	x: 变位系数	   alpha: 压力角    alpha_a: 齿顶圆压力角
*/

double calcToothThicknessHalfAngle(int z, double x, double alpha_deg, double alpha_a_deg) {
	double tmp = M_PI / (2 * z) + (2 * x * tan(alpha_deg * DEG_TO_RAD)) / z + invDeg(alpha_deg) - invDeg(alpha_a_deg);
	return radToDeg(tmp);
}

/*
	齿顶厚  tooth tip thickness
	phsi: 齿顶圆齿厚半角    d_a: 齿顶圆直径
*/
double calcToothTipThickness(double phsi_deg, double d_a) {
	return degToRad(phsi_deg) * d_a;
}



int main() {

	int z = 16;
	double x = 0.3;
	double alph_deg = 20;
	double d_b = 30.07016;
	double d_a = 37.2;
	double alph_a_deg = radToDeg(calcToothTipCirclePressureAngle(d_b, d_a));
	double phsi_deg = calcToothThicknessHalfAngle(z, x, alph_deg, alph_a_deg);
	cout << "==========================================================" << endl;
	cout << "alph_a = " << alph_a_deg << endl;
	cout << "phsi_deg = " << phsi_deg << endl;
	cout << "s_a = " << calcToothTipThickness(phsi_deg, d_a) << endl;
	return 0;
}