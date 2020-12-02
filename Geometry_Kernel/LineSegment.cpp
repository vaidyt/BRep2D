#include "LineSegment.h"

constexpr double eps = std::numeric_limits<double>::epsilon();

namespace Geometry
{

	LineSegment::LineSegment(const Point& point1, const Point& point2) 
		:p1(point1), p2(point2), v1(point1), v2(point2)
	{
	}

	LineSegment::LineSegment(const LineSegment& l) : LineSegment(l.p1, l.p2)
	{
	}

	double LineSegment::getLength() const
	{
		return (v2 - v1).getLength();
	}

	Vector LineSegment::getUnitVector() const
	{
		return (v2 - v1).getNormalized();
	}

	Vector LineSegment::getDirectionVector() const
	{
		return v2 - v1;
	}

	Point LineSegment::P1() const
	{
		return p1;
	}

	Point LineSegment::P2() const
	{
		return p2;
	}


	void LineSegment::Print() const
	{
		p1.Print();
		p2.Print();
	}

	/// <summary>
	/// Checks for degeneracy of the line
	/// </summary>
	/// <returns>true if the line segment is just a point 
	///			 (and false otherwise)
	/// </returns>
	bool LineSegment::isDegenerate() const
	{
		return p1 == p2 || getLength() == 0;
	}

	CurveType LineSegment::getType() const
	{
		return CurveType::LineSegment;
	}

	/// <summary>
	/// Checks if the query point lies with in the line segment
	/// </summary>
	/// <param name="p">query point</param>
	/// <returns>true if the point lies on the line segment
	///          (and false otherwise)
	/// </returns>
	bool LineSegment::isPointOnLineSegment(const Point& p) const
	{
		if (p == p1 || p == p2)
			return true;

		Vector P1P3(p - p1);
		Vector P1P2(p2 - p1);
		// compute area formed by triangle P1, P2 and p
		auto area = P1P3.cross(P1P2).getLength();

		if (Numerical::isZero(area))
		{

			// Now project point p on to the line segment
			// and compute the parametric coordinate (i.e. time param)
			auto t = P1P3.dot(P1P2.getNormalized())/P1P2.getLength();

			// check if the projection is between the two ends
			if (t >= 0 && t <= 1)
				return true;
		}

		// the point does not line on the segment 
		// as the area of the triangle is non-zero

		return false;
	}
	/// <summary>
	/// computes line segment (l1) - line segment (l2) intersection
	/// </summary>
	/// <param name="l2">Test line segment</param>
	/// <param name="intersectionPt">point of intersection; When the line segments
	///  are overlapping - it just returns 'a' point/// </param> 
	/// <returns>true if the lines intersect</returns>
	bool LineSegment::isIntersecting(const LineSegment& l2, Point &intersectionPt) const
	{
		auto p1x = this->P1().getX();
		auto p1y = this->P1().getY();

		auto  v1 = getDirectionVector();
		auto  v1x = v1.getX();
		auto  v1y = v1.getY();
		
		Vector v21(l2.P1());
		Vector v22(l2.P2());
		auto  v2 = v22 - v21;
		auto  v2x = v2.getX();
		auto  v2y = v2.getY();

		auto  p3x = l2.P1().getX();
		auto  p3y = l2.P1().getY();

		auto c1 = p3x - p1x;
		auto c2 = p3y - p1y;

		// Use cramer's rule to solve the 2 x 2 linear system
		auto detA = -v1x * v2y + v2x * v1y;
		auto detDt = -c1 * v2y + c2 * v2x;
		auto detDs = v1x * c2 - c1 * v1y;

		if (detA == 0)
		{
			// Points are collinear
			if (this->isPointOnLineSegment(l2.P1()) || this->isPointOnLineSegment(l2.P2()))
			{
				// The line segments overlap
				if (this->isPointOnLineSegment(l2.P1()))
				{
					intersectionPt = l2.P1();
				}
				else
				{
					intersectionPt = l2.P2();
				}
				intersectionPt.setValidity(true);
				return true;
			}
			// The line segments are parallel but do not intersect
			intersectionPt.setValidity(false);
			return false;
		}

		auto t = detDt / detA;
		auto s = detDs / detA;

		intersectionPt.setValidity(false);

		
		if (t >= 0 && t <= 1 && s >= 0 && s <= 1)
		{
			// The line segements intersect
			Vector pv1(P1());
			Point p(pv1 + t * v1);
			intersectionPt = p;
			intersectionPt.setValidity(true);
			return true;
		}

		// The line segments do not intersect (and only the line intersects)
		return false;
	}

	/// <summary>
	/// computes line segment (this) - arc (arc) intersection
	/// </summary>
	/// <param name="arc">arc</param>
	/// <param name="p1">First point of intersection (only valid if isValid is true)</param>
	/// <param name="p2">Second point of intersection (only valid if isValid is true)</param>
	/// <returns>true if the line intersects the arc and false otherwise</returns>
	bool LineSegment::isIntersecting(const Arc& arc, Point& p1, Point &p2) const
	{
		Vector center = arc.getCenter();
		auto  v1 = getDirectionVector();
		Vector pv1(P1());
		Vector v3(pv1 - center);
		auto r = arc.getRadius();

		auto A = v1.dot(v1);
		auto B = 2*v1.dot(v3);
		auto C = v3.dot(v3) - r*r;

		double t1 = 0.0, t2 = 0.0;
		
		Numerical::solveQuadratic(A, B, C, t1, t2);

		if ((t1 < 0 || t1 > 1) && (t2 < 0 || t2 > 1))
		{
			// The line segment does not intersect with the full circle
			// and hence the arc
			p1.setValidity(false);
			p2.setValidity(false);

			return false;
		}

		
		Point testP1(P1() + t1 * v1);
		Point testP2(P1() + t2 * v1);

		p1 = testP1;
		p2 = testP2;

		// The intersection points computed are for the full circle
		// So check if the intersection points actually
		// lie in the arc if they do not lie on the arc,
		// then set isValid to false

		if (!arc.isPointOnBoundary(p1))
		{
			p1.setValidity(false);
		}

		if (!arc.isPointOnBoundary(p2))
		{
			p2.setValidity(false);
		}

		return p1.isValid() || p2.isValid();
	}



	bool LineSegment::isIntersecting(const ICurve&curve) const
	{
		Point p1,p2;
		return computeIntersection(curve, p1, p2);
	}

	/// <summary>
	/// computes the point(s) of intersection of any given curve with the line segment
	/// </summary>
	/// <param name="curve">This is the curve for which the intersection is to be
	///						computed (with the line segment)</param>	
	/// <param name="p1">First point of intersection 
	///					 (if p1.isValid() is false then this point should be discarded)</param>	
	/// <param name="p2">Second point of intersection (if p2.isValid() is false 
	///					 then this point should be discarded)</param>
	/// <returns>true if there is an intersection (and the 
	///          point(s) of intersection as out params)</returns>
	bool LineSegment::computeIntersection(const Geometry::ICurve& curve, Point &p1, Point &p2) const
	{
		auto type = curve.getType();

		switch (type)
		{
			case CurveType::LineSegment:
			{
				LineSegment* l = dynamic_cast<LineSegment*>(const_cast<ICurve*>(&curve));
				return isIntersecting(*l, p1);
			}
			case CurveType::Arc:
			{
				Arc* q = dynamic_cast<Arc*>(const_cast<ICurve*>(&curve));
				return isIntersecting(*q, p1,p2);
			}
			default:
			{
				throw new NotImplemented("Curve Type not implemented");
			}
		}
	}

	/// <summary>
	/// Computes the shortest distance of a point to a line segment (or line)
	/// For a line the algorithm is simply to project the point on to the line and
	/// compute the distance between the query point and projected point.
	/// For a line segment the algorithm  performs additional checks
	/// to see if the projected point lies inside the line segment or not
	/// If the projected point is outside, then the shortest distance is simply
	/// the distance between one of the end points of the line segment and the query point.
	/// </summary>
	/// <param name="lineSeg">Line segement to which distance is required</param>
	/// <param name="p">Query point</param>
	/// <param name="extend">If set to true, treats the line segment as line</param>
	/// <returns>Shortest distance of the point to the line segment (or line)</returns>
	double LineSegment::distanceFromPoint(const Point& p, bool extend) const
	{
		const Vector vec_p(p);

		// Check if the line segment is degenerate
		// In other words, is the line segment just a point?

		if (isDegenerate())
		{
			// Since the line segment is degenerate,
			// we simply return the distance between
			// one of the end points and p
			const Vector vec_q(P1());
			return (vec_q - vec_p).getLength();
		}


		// Get a unit vector in the direction of the given line segment
		const auto d = getUnitVector();

		// Project point p on to line segment
		const Vector vec_p1(P1());
		const auto vec_p1p = (vec_p - vec_p1);
		// Compute projected length
		const auto t = vec_p1p.dot(d);
		// Scale projected length 
		const auto s = t / getLength();

		if (s < 0 && !extend)
		{
			const Vector vec_q(P1());
			return (vec_q - vec_p).getLength();
		}
		else if (s > 1 && !extend)
		{
			const Vector vec_q(P2());
			return (vec_q - vec_p).getLength();
		}
		else
		{
			// Point q is inside the line segment i.e. 0 <= s <= 1
			// Get position vector of point q
			const auto vec_q = vec_p1 + t * d;
			// Compute distance between p & q and return it
			return (vec_q - vec_p).getLength();
		}
	}

	std::unique_ptr<ICurve> LineSegment::clone() const
	{
		return std::make_unique<LineSegment>(*this);
	}


	/// <summary>
	/// The main intersection method that computes the point(s) of intersection of 
	/// the line segment with the given curve
	/// </summary>
	/// <param name="c">Curve for which intersection is to be computed</param>
	/// <param name="intersectionPts">Output intersection points</param>
	/// <returns>true if there is an intersection and the point(s) of intersection as an out
	///  param (if point.isValid() is false then this point should be discarded)</returns>
	bool LineSegment::isIntersecting(const ICurve&c, std::vector<Point>& intersectionPts) const
	{
		Point p1;
		Point p2;

		bool isIntersecting = computeIntersection(c, p1, p2);

		if (p1.isValid())
		{
			intersectionPts.push_back(p1);
		}

		if (p2.isValid())
		{
			intersectionPts.push_back(p2);
		}
		return isIntersecting;
	}


	void LineSegment::discretize(double d, std::vector<LineSegment>& q) const
	{
		q.push_back(*this);
		return;
	}


}