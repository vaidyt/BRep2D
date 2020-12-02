#include "pch.h"
#include <string>

TEST(Test3, RoundedRectangleTest)
{
	Geometry::Wire w;


	// std::cout << "Rounded Rectangle Example" << std::endl;

	std::string edges[8] = {
		 "L (0,9) -> (0,1)",
		"L (1,0) -> (9,0)",
		"L (9,10) -> (1,10)",
		"L (10,1) -> (10,9)",
		"C (0,1) -> (1,0)",
		"C (1,10) -> (0,9)",
		"C (9,0) -> (10,1)",
		"C (10,9) -> (9,10)" };

	std::vector<std::string> edgeStrings;

	for (auto i = 0; i < 8; i++)
	{
		edgeStrings.push_back(edges[i]);
	}
	w.deserialize(edgeStrings);

	std::vector<std::string> serializedStrings;

	// w.serialize(serializedStrings);

	//for (auto i = 0; i < serializedStrings.size(); i++)
	//{
	//	std::cout << serializedStrings[i] << std::endl;
	//}

	bool isIntersecting = w.isSelfIntersecting(false);

	EXPECT_TRUE(isIntersecting == false);

}


TEST(Test3, BowTieTest)
{
	Geometry::Wire w;

	Geometry::Edge::resetIdCounter();

	// std::cout << "Bow Tie Example" << std::endl;
	std::string edges[4] = {
		"C (1,0) -> (0,1)",
		"C (1,1) -> (0,0)",
		"L (0,1) -> (0,0)",
		"L (1,0) -> (1,1)",
		 };

	std::vector<std::string> edgeStrings;

	for (auto i = 0; i < 4; i++)
	{
		edgeStrings.push_back(edges[i]);
	}
	w.deserialize(edgeStrings);

	std::vector<std::string> serializedStrings;

	// w.serialize(serializedStrings);

	/*for (auto i = 0; i < serializedStrings.size(); i++)
	{
		std::cout << serializedStrings[i] << std::endl;
	}*/

	bool isIntersecting = w.isSelfIntersecting(false);

	EXPECT_TRUE(isIntersecting == true);
}


//TEST(Test3, DiscretizationTest1)
//{
//	Geometry::Wire w;
//
//	Geometry::Edge::resetIdCounter();
//
//	// std::cout << "Bow Tie Example" << std::endl;
//	std::string edges[4] = {
//		"C (1,0) -> (0,1)",
//		"C (1,1) -> (0,0)",
//		"L (0,1) -> (0,0)",
//		"L (1,0) -> (1,1)",
//	};
//
//	std::vector<std::string> edgeStrings;
//
//	for (auto i = 0; i < 4; i++)
//	{
//		edgeStrings.push_back(edges[i]);
//	}
//	w.deserialize(edgeStrings);
//
//	std::vector<std::string> serializedStrings;
//
//	 w.serialize(serializedStrings);
//
//	std::cout << "Before Discretization " << std::endl;
//	for (auto i = 0; i < serializedStrings.size(); i++)
//	{
//		std::cout << serializedStrings[i] << std::endl;
//	}
//
//	Geometry::Wire resWire;
//	w.discretize(0.01,resWire);
//
//	std::cout << "After Discretization " << std::endl;
//	serializedStrings.clear();
//	resWire.serialize(serializedStrings);
//
//	for (auto i = 0; i < serializedStrings.size(); i++)
//	{
//		std::cout << serializedStrings[i] << std::endl;
//	}
//	
//}
//
//
//TEST(Test3, DiscretizationTest2)
//{
//	Geometry::Wire w;
//
//	Geometry::Edge::resetIdCounter();
//
//	// std::cout << "Rounded Rectangle Example" << std::endl;
//
//	std::string edges[8] = {
//		 "L (0,9) -> (0,1)",
//		"L (1,0) -> (9,0)",
//		"L (9,10) -> (1,10)",
//		"L (10,1) -> (10,9)",
//		"C (0,1) -> (1,0)",
//		"C (1,10) -> (0,9)",
//		"C (9,0) -> (10,1)",
//		"C (10,9) -> (9,10)" };
//
//	std::vector<std::string> edgeStrings;
//
//	for (auto i = 0; i < 8; i++)
//	{
//		edgeStrings.push_back(edges[i]);
//	}
//	w.deserialize(edgeStrings);
//
//	std::vector<std::string> serializedStrings;
//
//	w.serialize(serializedStrings);
//
//	std::cout << "Before Discretization " << std::endl;
//	for (auto i = 0; i < serializedStrings.size(); i++)
//	{
//		std::cout << serializedStrings[i] << std::endl;
//	}
//
//	Geometry::Wire resWire;
//	w.discretize(0.01, resWire);
//
//	std::cout << "After Discretization " << std::endl;
//	serializedStrings.clear();
//	resWire.serialize(serializedStrings);
//
//	for (auto i = 0; i < serializedStrings.size(); i++)
//	{
//		std::cout << serializedStrings[i] << std::endl;
//	}
//
//}
//
//TEST(Test3, DeSerialization)
//{
//		std::vector<std::string> serializedStrings;
//		Geometry::Wire newWire;
//		std::string fileName("test.txt");
//		newWire.deserialize(fileName);
//		serializedStrings.clear();
//		newWire.serialize(serializedStrings);
//		std::cout << "Printing deserialization contents from a file:" << std::endl;
//		for (auto i = 0; i < serializedStrings.size(); i++)
//		{
//			std::cout << serializedStrings[i] << std::endl;
//		}
//}