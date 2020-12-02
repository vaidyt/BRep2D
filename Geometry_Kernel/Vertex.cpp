#include "Vertex.h"

namespace Geometry
{
	Vertex::Vertex() : Vertex(0, 0, 0)
	{
	}

	Vertex::Vertex(double x_co, double y_co, double z_co) : m_p(x_co, y_co, z_co)
	{
		m_id = vertexIdCounter++;
	}

	Vertex::Vertex(const Point& p) : Vertex(p.getX(), p.getY(), p.getZ())
	{
	}

	double Vertex::getX() const
	{
		return m_p.getX();
	}

	double Vertex::getY() const
	{
		return m_p.getY();
	}

	double Vertex::getZ() const
	{
		return m_p.getZ();
	}

	Point Vertex::getPt() const
	{
		return m_p;
	}

	int Vertex::getId() const
	{
		return m_id;
	}

	bool Vertex::operator==(const Vertex& v) const
	{
		return m_p == v.m_p;
	}

	std::string Vertex::toString() const
	{
		return "(" + to_string(m_p.getX()) +  "," + to_string(m_p.getY()) + ")";
	}

	int Vertex::vertexIdCounter = 1;
}