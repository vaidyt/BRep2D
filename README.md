# BRep2D
2D Boundary Representation

-----------------------------------------------------------------------------------------------------------------------------

BRep.CLI.exe (the main client application) has 2 modes of running:

Mode 1: 

> Brep.CLI 

You can simply run it without any parameters and it will do all the things that were asked for in the take home challenge.

Mode 2: 

> Brep.CLI <infile> <d>
              infile: Input file name describing the 2D geometry as a list of strings (format: <L or C> (x1,y1) (x2,y2))
              d: Mimum (chord) distance for discretization (indirectly determining the mesh size)

-----------------------------------------------------------------------------------------------------------------------------

Note on Input File Format:

The format is extremely simple:

L (or C) (x1,y1) (x2,y2)

Here, L denotes a line segment and C denote quadrant of a curve.

(x1,y1) is the starting coordinate of  line or quad-circle

(x2,y2) is the ending coordinate of of line or quad-circle
-----------------------------------------------------------------------------------------------------------------------------

Location of Executable:

You will find BRep.CLI.exe in the release folder - https://github.com/vaidyt/BRep2D/tree/main/Release


Example Usage (Mode 1):
-----------------------

> BRep.CLI


Example Usage (Mode 2):
-----------------------

> BRep.CLI BowTie.txt 0.01