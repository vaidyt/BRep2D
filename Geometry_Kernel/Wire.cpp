#include "Wire.h"
#include "Edge.h"

class Vertex;
class Edge;

namespace Geometry
{
	Wire::Wire(std::vector<Edge*>& edgeList) : m_edgeList(edgeList)
	{
	}
	void Wire::discretize(double d, Wire& result) const
	{
		std::vector<Edge*> edgeList;

		for (auto i = 0; i < this->m_edgeList.size(); i++)
		{
			m_edgeList[i]->discretize(d, edgeList);
		}

		result.m_edgeList = edgeList;


	}
	bool Wire::isSelfIntersecting(bool verbose)
	{
		bool selfIntersection = false;

		int totalSelfIntersections = 0;

		if (verbose)
		{
			for (auto i = 0; i < m_edgeList.size(); i++)
			{
				std::string edgeString = m_edgeList[i]->toString();
				std::cout << m_edgeList[i]->getId() << ". " << edgeString << std::endl;
			}
			std::cout << std::endl;
		}

		for (auto i = 0; i < m_edgeList.size() - 1; i++)
		{
			if (verbose)
			{
				std::cout << "Edge " << m_edgeList[i]->getId() << " intersects Edge < ";
			}
			int count = 0;
			for (auto j = i + 1; j < m_edgeList.size(); j++)
			{
				std::vector<Point> intersectionPts;
				bool isIntersecting = m_edgeList[i]->isIntersecting(*m_edgeList[j], intersectionPts);

				if (isIntersecting && verbose)
				{
					std::cout << m_edgeList[j]->getId() << " ";
					count++;
				}

				selfIntersection = selfIntersection || isIntersecting;
			}

			if (verbose)
			{
				if (count == 0)
				{
					std::cout << "- >" << std::endl;
				}
				else
				{
					std::cout << ">" << std::endl;
				}
				totalSelfIntersections += count;
			}
		}

		if (verbose)
		{
			std::cout << std::endl;
			std::cout << totalSelfIntersections << " Self Intersection(s) Found!" << std::endl;
		}

		return selfIntersection;

	}
	void Wire::serialize(std::vector<std::string>& edgeStrings) const
	{
		for (auto i = 0; i < m_edgeList.size(); i++)
		{
			std::string edgeString(m_edgeList[i]->toString());
			edgeStrings.push_back(edgeString);
		}
	}

	bool Wire::serialize(const std::string& fileName) const
	{
		std::vector<std::string> edgeStrings;
		serialize(edgeStrings);
		if (!StringHelper::writeStringsToFile(fileName, edgeStrings))
		{
			std::cout << "Error: Cannot open output file for writing..." << std::endl;
			return false;
		}

		return true;
	}

	void Wire::deserialize(const std::vector<std::string>& edgeStrings)
	{
		for (auto i = 0; i < edgeStrings.size(); i++)
		{
			auto strings = StringHelper::splitString(edgeStrings[i], ' ');

			if (strings.size() > 4 || strings.size() == 0)
			{
				throw new ParserError("Parsing failed on deserialization");
			}

			std::string startVertexString = StringHelper::extractString(strings[1], "(", ")");
			std::string endVertexString = StringHelper::extractString(strings[3], "(", ")");

			auto startCoordStrings = StringHelper::splitString(startVertexString, ',');
			auto endCoordStrings = StringHelper::splitString(endVertexString, ',');

			if (startCoordStrings.size() > 2 || startCoordStrings.size() == 0 || 
				endCoordStrings.size() > 2 || endCoordStrings.size() == 0 || strings[0].length() > 1)
			{
				throw new ParserError("Parsing failed on deserialization");
			}
			
			bool isCurve = strings[0] == "L" ? false : true;
			const Vertex v1(StringHelper::toDouble(startCoordStrings[0]), 
							StringHelper::toDouble(startCoordStrings[1]));
			const Vertex v2(StringHelper::toDouble(endCoordStrings[0]), 
							StringHelper::toDouble(endCoordStrings[1]));

			// m_vertexList.push_back(v1);
			// m_vertexList.push_back(v2);

			ICurve* ic = nullptr;

			if (!isCurve)
			{
				ic = new LineSegment(v1.getPt(), v2.getPt());
			}
			else
			{
				ic = new Arc(v1.getPt(), v2.getPt());
			}

			Edge* e = new Edge(v1, v2, ic);
			m_edgeList.push_back(e);
			
			
		}
	}

	bool Wire::deserialize(const std::string& fileName)
	{
		std::vector<std::string> edgeStrings;
		if (!StringHelper::readStringsFromFile(fileName, edgeStrings))
		{
			std::cout << "Error: Input file does not exist" << std::endl;
			return false;
		}
		this->deserialize(edgeStrings);

		return true;
	}

	Wire::~Wire()
	{
		for (auto i = 0; i < m_edgeList.size(); i++)
		{
			delete m_edgeList[i];
		}
	}
};