#include "color.h"
#include <sstream>
#include <algorithm>
#include <cmath>
#include "vector.h"
using namespace std;


Color::Color() {
	r = g = b = 0;
}

Color::Color(double r,double g,double b) : r(r),g(g),b(b) {
}

Color Color::adjust()const {
	return Color(min(r,1.0),min(g,1.0),min(b,1.0));
}


Color operator +(const Color& a,const Color &b) {
	return Color(a.r+b.r,a.g+b.g,a.b+b.b);
}

Color operator *(const Color& a,const Color &b) {
	return Color(a.r*b.r,a.g*b.g,a.b*b.b);
}

Color operator *(const Color& a,double k) {
	return Color(a.r*k,a.g*k,a.b*k);
}

Color Color::exp()const {
	return Color(::exp(r),::exp(g),::exp(b));
}

Color Color::operator +=(const Color& a) {
	r += a.r;
	g += a.g;
	b += a.b;
	return (*this);
}
void Color::accept(const Json::Value& val) {
	r = val["r"].asDouble();
	g = val["g"].asDouble();
	b = val["b"].asDouble();
}
std::string Color::description()const {
	std::stringstream ss;
	ss<<"Color<"<<r<<","<<g<<","<<b<<">"<<std::endl;
	std::string res;
	ss>>res;
	return res;
}
