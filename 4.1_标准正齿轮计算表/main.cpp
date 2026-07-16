#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;


double radToDeg(double rad);
double degToRad(double deg);
double calcCenterDistance(int z1, int z2, int m);
double calcPitchCircleDiameter(int z, int m);
double calcBaseCircleDiameter(double d, double alpha_deg);
double calcToothCrestHeight(int m);
double calcFullToothHeight(int m);
double calcTipDiameter(double d, int m);
double calcRootDiameter(double d, int m);

/*
	中心距		center distance
	分度圆直径	pitch circle diameter
	基圆直径	Base circle diameter
	齿顶高		Tooth crest height
	全齿高		Full tooth height
	齿顶圆直径	tip diameter	
	齿根圆直径	root diameter
*/


/*
	中心距		center distance
	z1: 小齿轮齿数	z2: 大齿轮齿数	m: 模数
*/

double radToDeg(double rad) {
	return rad * 180 / M_PI;
}

double degToRad(double deg) {
	return deg * M_PI / 180;
}
double calcCenterDistance(int z1, int z2, int m) {
	return (z1 + z2) * m / 2;
}


/*
	分度圆直径	pitch circle diameter
	z: 齿轮齿数		m: 模数
*/
double calcPitchCircleDiameter(int z, int m) {
	return z * m;
}

/*
	基圆直径	Base circle diameter

*/

double calcBaseCircleDiameter(double d, double alpha_deg) {
	return d * cos( degToRad(alpha_deg) );
}

/*
	齿顶高		Tooth crest height
	m: 模数
*/
double calcToothCrestHeight(int m) {
	return 1.00 * m;
}

/*
	全齿高		Full tooth height
	m: 模数
*/
double calcFullToothHeight(int m) {
	return 2.25 * m;
}

/*
	齿顶圆直径	tip diameter
	d: 分度圆直径	m: 模数
*/
double calcTipDiameter(double d, int m) {
	return d + 2 * m;
}

/*
	齿根圆直径	root diameter
	d: 分度圆直径	m: 模数
*/
double calcRootDiameter(double d, int m) {
	return d - 2.5 * m;
}

void printValue(string name, double value)
{
	cout << left << setw(8) << name << "=   " << value << endl;
}

int main() {


	int z1 = 12, z2 = 24;
	int m = 3;
	double alpha_deg = 20;

	double a =  calcCenterDistance(z1, z2, m);

	double d1 = calcPitchCircleDiameter(z1, m);
	double d2 = calcPitchCircleDiameter(z2, m);


	double d_b1 = calcBaseCircleDiameter(d1, alpha_deg);
	double d_b2 = calcBaseCircleDiameter(d2, alpha_deg);

	double h_a1 = calcToothCrestHeight(m);
	double h_a2 = calcToothCrestHeight(m);

	double h1 = calcFullToothHeight( m);
	double h2 = calcFullToothHeight(m);


	double d_a1 = calcTipDiameter(d1, m);
	double d_a2 = calcTipDiameter(d2, m);


	double d_f1 =  calcRootDiameter(d1, m);
	double d_f2 = calcRootDiameter(d2, m);



	printValue("a", a);
	printValue("d1", d1);
	printValue("d2", d2);
	printValue("d_b1", d_b1);
	printValue("d_b2", d_b2);
	printValue("h_a1", h_a1);
	printValue("h_a2", h_a2);
	printValue("h1", h1);
	printValue("h2", h2);
	printValue("d_a1", d_a1);
	printValue("d_a2", d_a2);
	printValue("d_f1", d_f1);
	printValue("d_f2", d_f2);

	return 0;
}