#pragma once

#include "Vector.h"
#include "Point.h"
#include "LineSegment.h"

#include <vector>
using namespace std;

namespace Geometry
{

	class Polygon
	{
		std::vector<Geometry::Point> pointList;
		std::vector<Geometry::Edge> edgeList;

		Polygon(std::vector<Geometry::Point> pv)
		{
			pointVector = pv;
		}

		int getNumberOfEdges()
		{
			return edgeList.size();
		}

		double computeArea()
		{
			// return area based on the close form expression
		}

		void computeIntersectionPts(Geometry::Edge& testEdge, std::vector<Geometry::Point> &pList, std::vector<Geometry::Edge> &eList)
		{
			
			for(auto i = 0; i < getNumberOfEdges(); i++  )
			{
				if( edgeList[i].intersect(testEdge) )
				{
					eList.push_back(edgeList[i]);
					Point intersectionPt;
					edgeList[i].getIntersection(testEdge, intersectionPt);
					pList.push_back(intersectionPt);
				}

			}
		}

		bool clipPolygon( Geometry::Edge &testEdge, std::vector<Polygon> &pList )
		{
			std::vector<Point> intersectionPtList;
			std::vector<Edge> intersectionEdgeList;
			
			for(auto i = 0; i < edgeList.size(); i++)
			{
				if( testEdge.isIntersect(edgeList[i]))
				{
					testEdge.intersection(edgeList[i], intersectionPtList, intersectionEdgeList );

					if( intersectionEdgeList.size() == 0 || intersectionPtList.size() == 0)
					{
						throw error;
					}
					
					split(intersectionEdgeList[0], intersectionPtList[0]);
					if( intersectionEdgeList.size() > 1 )
						split(intersectionEdgeList[1], intersectionPtList[1]);
				}
			}

			Point startPt = intersectionPtList[0];
			Point endPt = intersectionPtList[1];
			// Form two polygons
			int startIndex = findIndex(startPt);
			int endIndex = findIndex(endPt);
			Polygon p1;
			Polygon p2;

			for (auto i = startIndex; i <= endIndex; i++)
			{
				p1.addPoint(pointList[i]);
			}

			for (auto i = endIndex; i <= startIndex; i--)
			{
				p2.addPoint(pointList[i]);
			}

			pList.push_back(p1);
			pList.push_back(p2);
		}
	};
}