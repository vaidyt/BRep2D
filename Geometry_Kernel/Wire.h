#pragma once

#ifndef _WIRE_H
#define _WIRE_H

#include <iostream>
#include <vector>
#include <fstream>
#include "Edge.h"
#include "Vertex.h"
#include "ICurve.h"
#include "LineSegment.h"
#include "Arc.h"
#include "StringHelper.h"


namespace Geometry
{
	class Vertex;
	class Edge;

	class ParserError : public std::logic_error
	{
	public:
		ParserError(string msg) : std::logic_error(msg) { };
	};

	class Wire
	{
	private:
		// ToDo: We could introduce  vertex list and avoid duplicate vertices
		// Then we could have the edge point to 2 of these vertices
		// This way we can save on memory and also topological checks
		// would become lot easier - I will not do this for now
		// std::vector<Vertex> m_vertexList;
		std::vector<Edge*> m_edgeList;

	public:
		// Wire(std::vector<EdgeString> &e);
		Wire() {};
		Wire(std::vector<Edge*>& edgeList);
		void discretize(double d, Wire& result) const;
		bool isSelfIntersecting(bool verbose = true);
		void serialize(std::vector<std::string>& edgeStrings) const;
		bool serialize(const std::string &fileName) const;
		void deserialize(const std::vector<std::string>& edgeStrings);
		bool deserialize(const std::string &fileName);
		~Wire();
	};
}

#endif

