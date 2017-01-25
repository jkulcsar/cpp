
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <iterator>

#include <string>
#include <list>
#include <set>

std::string::size_type stringLengthSum(std::string::size_type sumSoFar,
	const std::string s)	{
		return sumSoFar + s.size();
}

struct Point {
	Point(double x, double y) : x_(x), y_(y) {}
	double x_,y_;

	std::ostream& print (std::ostream& s) const {
		std::ios_base::fmtflags old_flags = s.setf(std::ios::left, std::ios::adjustfield);
		s << "x = " << std::setw(10) << x_ ;
		s << "y = " << std::setw(10) << y_ ;
		s << std::endl;
		s.setf(old_flags);
		return s;
	}
};

//std::ostream& operator << (std::ostream& s, const Point& p) {
//	std::ios_base::fmtflags old_flags = s.setf(std::ios::left, std::ios::adjustfield);
//	s << "x = " << std::setw(10) << p.x_ ;
//	s << "y = " << std::setw(10) << p.y_ ;
//	s << std::endl;
//	s.setf(old_flags);
//	return s;
//}
std::ostream& operator << (std::ostream& s, const Point& p) {
	return p.print(s);
}


class PointAverage : std::binary_function<Point, Point, Point> {
public:
	PointAverage() : numPoints(0), xSum(0), ySum(0) {}

	const Point operator()(const Point& averageSoFar, const Point& p) {
		++numPoints;
		xSum += p.x_;
		ySum += p.y_;
		return Point(xSum/numPoints, ySum/numPoints);
	}

	std::ostream& print ( std::ostream& s) {
		s << "number of points averaged: " << numPoints
			<< "xSum = " << xSum << "ySum = " << ySum 
			<< std::endl;
		return s;
	}
private:
	size_t numPoints;
	double xSum;
	double ySum;
};

//std::ostream& operator << ( std::ostream& s, const PointAverage& p) {
//	p.print(s);
//	return s;
//}


int main(int argc, char** argv) {
	
	typedef std::list<double> ListOfDoubles;

	ListOfDoubles ld;
	ld.push_back(2.78);
	ld.push_back(3.14);
	double sum = std::accumulate(ld.begin(), ld.end(), 0.0);
	std::cout << sum << std::endl;


	std::set<std::string> ss;
	ss.insert("first_string");
	ss.insert("second_string");

	std::string::size_type stringLength = std::accumulate(
		ss.begin(),ss.end(), 0, stringLengthSum);
	std::cout << stringLength << std::endl;

	std::list<Point> lpoints;
	lpoints.push_back(Point(1.0, 1.1));
	lpoints.push_back(Point(2.0, 1.2));
	lpoints.push_back(Point(5.0, 1.5));
	lpoints.push_back(Point(7.0, 1.7));
	lpoints.push_back(Point(9.0, 1.9));

	//
	// show the list of Point objects
	// use copy to copy it on a stream (here: std::cout)
	std::copy(lpoints.begin(), lpoints.end(), 
		std::ostream_iterator<Point>(std::cout));

	//
	// calculate average using std::accumulate
	Point averagePoint = std::accumulate(
		lpoints.begin(), lpoints.end(),
		Point(0.0, 0.0), PointAverage()
		);

	//
	// show result of averaging Point objects
	std::cout << averagePoint << std::endl;


	return 0;
}