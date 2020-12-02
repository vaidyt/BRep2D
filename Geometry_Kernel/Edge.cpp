#include "Edge.h"


namespace Geometry
{
    Edge::Edge(const Vertex v1, const Vertex v2, ICurve* c) : m_v1(v1), m_v2(v2), m_c(c)
    {
        m_id = edgeCounter++;
    }


    Vertex Edge::v1() const
    {
        return m_v1;
    }

    Vertex Edge::v2() const
    {
        return m_v2;;
    }

    int Edge::getId() const
    {
        return m_id;
    }

    bool Edge::isEndPt(const Point& p) const
    {

        return m_v1.getPt() == p || m_v2.getPt() == p;
    }

    bool Edge::isIntersecting(Edge& e2, std::vector<Point> &intersectionPts) const
    {
        std::vector<Point> initialPtsOfIntersection;
        bool intersecting = m_c->isIntersecting(*e2.m_c, initialPtsOfIntersection);


        if (intersecting)
        {
            for (auto i = 0; i < initialPtsOfIntersection.size(); i++)
            {
                if( !this->isEndPt(initialPtsOfIntersection[i])  )
                {
                    intersectionPts.push_back(initialPtsOfIntersection[i]);
                }
            }

            intersecting = intersectionPts.size() != 0;
        }

        return intersecting;
    }

    std::string Edge::toString() const
    {
        std::string geoPrefix(this->m_c->getType() == CurveType::Arc ? "C" : "L");
        return geoPrefix + " " + m_v1.toString() + " -> " + m_v2.toString();
    }

    Edge::~Edge()
    {
        delete m_c;
    }


    void  Edge::resetIdCounter()
    {
        edgeCounter = 1;
    }

    void Edge::discretize(double d, std::vector<Edge*> &edgeList) const
    {
        std::vector<LineSegment> lineSegments;
        m_c->discretize(d, lineSegments);

        for (auto i = 0; i < lineSegments.size(); i++)
        {
            ICurve* c = new LineSegment(lineSegments[i]);
            Edge *e = new Edge(lineSegments[i].P1(), lineSegments[i].P2(), c);
            edgeList.push_back(e);
        }
    }

    int Edge::edgeCounter = 1;
}