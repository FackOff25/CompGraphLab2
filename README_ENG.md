# CompGraphLab2

A task for the second laboratory work for 3 year in BSTU, RK6 department, course of Computer Graphics.

The work done on Unreal Engine 4.27

## Task
In the 3D graphics visualization environment based on Unreal Engine 4, implement
(a) Visualization of an object moving along a graph. 
(b) To do this, decompose the problem into the following:
(c) Graph generation: the vertices of the graph are points of a regular rectangular grid in the XY plane. For each point there is a displacement limit, the values of which are less than half a step of the grid. The program stores the graph in a developer-friendly form;
(d) Implementation of the Dijkstra algorithm (or A*);
(e) Movement of an object through the graph.
Requirements:
- The object appears at one of the vertices of the graph when the program starts.
- The end point of the "journey" for the object on the graph is chosen.
- The shortest path to this point is searched for.
- The object continues traveling until it reaches the destination.
- A new destination point is chosen.
- The object travels through the graph indefinitely.
- Several objects can "travel" through the graph. Objects can pass through each other without presenting obstacles for movement.
- The object is represented as a sphere.
- The graph is drawn as regular black lines.
- The found shortest path is drawn with lines of pre-selected colors other than black and each edge of the path is markedly different from the neighboring ones in color
- The following parameters should be available in the setup file:
	- SizeX and SizeY - Number of vertices vertically and horizontally
	- Disperce - the vertex offset limit.
	- Walkers - The number of objects (hereinafter referred to as walkers) moving on the grid

## Implementation Description
Implementation Description in russian can be found in Report.pdf file
