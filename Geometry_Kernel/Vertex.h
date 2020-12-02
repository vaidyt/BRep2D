#pragma once

#ifndef VERTEX_H
#define VERTEX_H

#include "Point.h"

// Point.h
#include <string>

namespace Geometry
{
	class Vertex
	{
	private:
		static int vertexIdCounter;
		Point m_p;
		int m_id;

	public:
		Vertex();
		Vertex(double x_co, double y_co, double z_co = 0);
		Vertex(const Point& p);
		double getX() const;
		double getY() const;
		double getZ() const;
		Point getPt() const;
		int getId() const;
		bool operator == (const Vertex& v) const;
		std::string toString() const;
	};
}
#endif