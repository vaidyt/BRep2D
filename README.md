# BRep2D

BRep2D is a C++ app for doing simple geometric computations over simple 1D/2D geometric objects.

Currently, the app supports the following:
  - line segment Vs line segment intersection (test and point of intersection computation)
  - line segment vs arc intersection (test and point of intersection computation)
  - Distance of a line/line segment from a point in 2D (and 3D)
  - Discretization of a circular arc (given some measure of mesh size using a distance parameter 'd')
  - Serialization of geometric objects (i.e. line/arc) in to strings
  - Deserialization of strings back to geometric objects (i.e. line/arc)
  - Represent a collection of line segments/ curves as a wire data structure (with topological notions of Edges and Vertices built in)
  
# 

### Build and Installation

```sh
$ git clone https://github.com/vaidyt/BRep2D.git
$ cd BRep2D\Release
$ BRep2D.exe
```

For production environments...

```sh
$ cd BRep2D
$ VS FormLogicChallenge.sln
```

Then from Visual Studio 2019 build the following:
- Geometric_Kernel Project [Builds the Geometric_Kernel.lib static library]
- Unit_Test Project (Optional) [Builds the 40+ unit tests for a variety of geometric algorithms]
- BRep2D.CLI Project [Builds the CLI app or exe for performing geometric computations]

### Usage
```sh
$ BRep2D.exe <infileName> <d>
```
- infile: Input file name describing the 2D geometry as a list of strings (format: (x1,y1) (x2,y2))
- d: Minimum (chord) distance for discretization (indirectly determining the mesh size) [default value : 0.01]

#### Mode 1 (no parameters):

Mode 1 simply solves all the problems in Formlogic take-home challenge for both Rounded Rectangle an  Bow Tie Geometry!

```sh
$ BRep2D.exe
```

#### Mode 2 (with one or two parameters):

Mode 2 can be used to run the program for any user defined input defined via an input file with an optional distance parametr 'd' for discretization of curves. When the distance parameter (i.e. second parameter) is ignored, d is defaulted to a value of 0.01.

```sh
$ BRep2D.exe BoxTie.txt 0.001
```

#### Description of Projects
Geometric_Kernel:
- Vector.h / Vector.cpp - Models a Vector in 2D (and 3D)
- Point.h / Point.cpp - Models a Point in 2D (and 3D)
- ICurve.h - Abstract base class from which LineSegment and Arc class are derived from
- LineSegment.h / LineSegment.cpp - Models a line segement in 2D
- Arc.h / Arc.cpp - Models a circular arc [t <= 0 < 2*pi] in 2D
- Vertex.h / Vertex.cpp - Models a vertex in 2D (and 3D)
- Edge.h / Edge.cpp - Models an edge that can point to any geometric curve in 2D (of type ICurve*)
- Wire.h / Wire.cpp - Models a wire i.e. one or more edges representing a curves in 2D

Unit_Tests:
- lineTest.cpp - Unit tests for line segment class [mainly intersection tests with lines/arcs and distance to a point]
- ArcTest.cpp - Unit tests for Arc class [mainly arc and line segment intersection tests]
- WireTest.cpp - Unit tests for Wire class [mainly serialization/deserialization tests]

Plot Script:
- drawGeometry.m - Contains a simple MATLAB script to visualize the input and output files
- RoundedRectangle.Txt / BowTie.out - Input / Output file for the Rounded Rectangle Geometry
- BowTie.Txt / BowTie.out - Input / Output file for the BowTie Geometry

### TODOs

 - Add unit tests for arc discretization
 - Add unit tests for generic arc vs arc and arc vs line intersection

License
----

MIT