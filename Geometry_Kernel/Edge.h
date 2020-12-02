#pragma once

#ifndef _EDGE_H
#define _EDGE_H

#include<string>
#include "Vertex.h"
#include "ICurve.h"
#include "LineSegment.h"
#include "Arc.h"
#include <memory>


namespace Geometry
{
	class Vertex;
	class LineSegment;
	class Arc;

	class Edge
	{
	private:
		static int edgeCounter;
		int m_id;
		const Vertex m_v1, m_v2;
		ICurve *m_c;

	public:
		Edge(const Vertex v1, const Vertex v2, ICurve *c);
		Vertex v1() const;
		Vertex v2() const;
		int getId() const;
		bool isEndPt(const Point& p) const;
		bool isIntersecting(Edge& e, std::vector<Point> &intersectionPts) const;
		static void resetIdCounter();
		void discretize(double d, std::vector<Edge*> &edgeList) const;
		std::string toString() const;
		virtual ~Edge();
	};
}

#endif

