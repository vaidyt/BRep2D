// Brep.CLI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "../Geometry_Kernel/Wire.h"

using namespace Geometry;

void printStrings(std::vector<std::string> strings)
{
	for (auto i = 0; i < strings.size(); i++)
	{
		std::cout << strings[i] << std::endl;
	}
}

void getRoundedRectangleStrings(std::vector<std::string> &edgeStrings)
{
	std::string edges[8] = {
		 "L (0,9) -> (0,1)",
		"L (1,0) -> (9,0)",
		"L (9,10) -> (1,10)",
		"L (10,1) -> (10,9)",
		"C (0,1) -> (1,0)",
		"C (1,10) -> (0,9)",
		"C (9,0) -> (10,1)",
		"C (10,9) -> (9,10)" };

	for (auto i = 0; i < 8; i++)
	{
		edgeStrings.push_back(edges[i]);
	}
}

void getBowTie(std::vector<std::string>& edgeStrings)
{
	std::string edges[8] = {
		 "L (9,-10) -> (-9,10)",
		"L (-9,-10) -> (9,10)",
		"L (-10,-9) -> (-10,9)",
		"L (10,-9) -> (10,9)",
		"C (-10,-9) -> (-9,-10)",
		"C (9,-10) -> (10,-9)",
		"C (10,9) -> (9,10)",
		"C (-9,10) -> (-10,9)" };

	for (auto i = 0; i < 8; i++)
	{
		edgeStrings.push_back(edges[i]);
	}
}

void deserialize(Geometry::Wire& w, std::vector<std::string>& edgeStrings)
{
	std::cout << "Performing Deserialization..." << std::endl;
	w.deserialize(edgeStrings);

	if (edgeStrings.size() == 8)
	{
		std::cout << "Deserialization Successful..." << std::endl;
		printStrings(edgeStrings);
	}
	else
	{
		std::cout << "Deserialization Failed..." << std::endl;
	}
}

void deserializationDemo(Wire &roundedRectangle, Wire &bowTie)
{
    // Rounded Rectangle
	std::cout << "-------------------------------Deserialization Demo-------------------------------" << std::endl;
	std::cout << "Constructing Rounded Rectangle From Strings" << std::endl;
	std::vector<std::string> edgeStrings;
	getRoundedRectangleStrings(edgeStrings);
	deserialize(roundedRectangle, edgeStrings);

	std::cout << "Constructing Bow-Tie From Strings" << std::endl;
	edgeStrings.clear();
	getBowTie(edgeStrings);
	deserialize(bowTie, edgeStrings);
}



void serialize(const Geometry::Wire& w)
{
	std::vector<std::string> edgeStrings;
	w.serialize(edgeStrings);
	if (edgeStrings.size() == 8)
	{
		std::cout << "Serialization Successful..." << std::endl;
		printStrings(edgeStrings);
	}
	else
	{
		std::cout << "Serialization Failed..." << std::endl;
	}
}

void serializationDemo(const Geometry::Wire& roundedRectangle, const Geometry::Wire& bowTie)
{
	std::cout << "-------------------------------Serialization Demo-------------------------------" << std::endl;
	std::cout << "Serializing Rounded Rectangle to strings..." << std::endl;
	serialize(roundedRectangle);
	std::cout << "Serializing Bow Tie to strings..." << std::endl;
	serialize(bowTie);
}


void discretizationDemo(const Geometry::Wire& roundedRectangle, const Geometry::Wire& bowTie)
{
	std::cout << "-------------------------------Discretization Demo-------------------------------" << std::endl;
	std::cout << "Discretizing Rounded Rectangle..." << std::endl;
	Wire discreteRoundedRectangle;
	roundedRectangle.discretize(0.01, discreteRoundedRectangle);
	std::vector<std::string> edgeStrings;
	discreteRoundedRectangle.serialize(edgeStrings);
	printStrings(edgeStrings);


	std::cout << "Discretizing Bow Tie ..." << std::endl;
	Wire discretizedBowTie;
	bowTie.discretize(0.01, discretizedBowTie);
	edgeStrings.clear();
	discreteRoundedRectangle.serialize(edgeStrings);
	printStrings(edgeStrings);

}

void selfIntersectionDemo(Geometry::Wire& roundedRectangle, Geometry::Wire& bowTie)
{
	std::cout << "-------------------------------Self Intersection Demo-------------------------------" << std::endl;
	std::cout << "Self Intersection Test on Rounded Rectangle..." << std::endl;

	if( roundedRectangle.isSelfIntersecting(true) )
		std::cout << "Rounded Rectangle is self intersecting " << std::endl;
	else
		std::cout << "Rounded Rectangle is NOT self intersecting " << std::endl;

	std::cout << "-----------------------------------------------------------------------------------" << std::endl;

	std::cout << "Self Intersection Test on Bow Tie..." << std::endl;
	bowTie.isSelfIntersecting(true);

	if (bowTie.isSelfIntersecting(true))
		std::cout << "Bow Tie is self intersecting " << std::endl;
	else
		std::cout << "Bow Tie is NOT self intersecting " << std::endl;
	std::cout << "-----------------------------------------------------------------------------------" << std::endl;
}

void runTakeHomeChallenge()
{
	Wire roundedRectangle, bowTie;
	std::cout << "-------------------------------Formlogic : Take Home Challenge-------------------------------" << std::endl;
	deserializationDemo(roundedRectangle, bowTie);
	serializationDemo(roundedRectangle, bowTie);
	discretizationDemo(roundedRectangle, bowTie);
	selfIntersectionDemo(roundedRectangle, bowTie);
}


void displayUsage()
{
	std::cout << "Usage: Brep.CLI <infile> <d>" << std::endl;
	std::cout << "infile: Input file name describing the 2D geometry as a list of strings (format: <L or C> (x1,y1) (x2,y2))" << std::endl;
	std::cout << "d: Minimum (chord) distance for discretization (indirectly determining the mesh size)" << std::endl;
}


int main(int argc, char **argv)
{
	if (argc > 3 )
	{
		std::cout << "Error: Invalid input" << std::endl;
		displayUsage();
	}
    else if (argc == 1)
    {
        runTakeHomeChallenge();
    }
	else if(argc >= 2 && argc <= 3)
	{
		string inputFile(argv[1]);

		if (!strcmp(argv[1], "-o"))
		{
			displayUsage();
			return 0;
		}


		try
		{
			double d = 0.01;
			if (argc == 3)
			{
				std::string dStr(argv[2]);
				if (!StringHelper::is_number(dStr))
				{
					std::cout << "Error: Invalid parameter 'd'" << std::endl;
					displayUsage();
					return 0;
				}

				d = StringHelper::toDouble(dStr);
				if (d <= 0)
				{
					std::cout << "Error: parameter 'd' cannot be zero or negative" << std::endl;
					displayUsage();
					return 0;
				}
			}

			Wire w;
			std::cout << "-----------------------------------------------------------------------------------" << std::endl;
			std::cout << "Deserializing from " << inputFile << std::endl;
			if (!w.deserialize(inputFile))
			{
				return 0;
			}
			std::cout << "-----------------------------------------------------------------------------------" << std::endl;
			std::cout << "Serializing the object to strings..." << std::endl;
			std::vector<std::string> edgeStrings;
			w.serialize(edgeStrings);
			printStrings(edgeStrings);
			std::cout << "-----------------------------------------------------------------------------------" << std::endl;
			std::cout << "Performing self intersection test..." << std::endl;
			w.isSelfIntersecting();
			std::cout << "-----------------------------------------------------------------------------------" << std::endl;

			std::cout << "Performing discretization with d = " << d << std::endl;
			Wire discretizedWire;
			w.discretize(d, discretizedWire);
			edgeStrings.clear();
			discretizedWire.serialize(edgeStrings);
			printStrings(edgeStrings);
			std::cout << "-----------------------------------------------------------------------------------" << std::endl;
			
			size_t lastindex = inputFile.find_last_of(".");
			std::string rawname = inputFile.substr(0, lastindex);
			std::string outFileName = rawname + ".out";

			StringHelper::writeStringsToFile(outFileName, edgeStrings);
			std::cout << "Serializing discretized output to " << outFileName << std::endl;
			std::cout << "-----------------------------------------------------------------------------------" << std::endl;
		}
		catch(exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}
