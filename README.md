4dSurface-sandBox
=================

Finds surface elements using convex hulls in 3d and 4d.

./python/ presently contains only a test code that finds convex hulls in 3d with some partially developed matplotlib scripts for visually verifying the giftwrapping.

Requires numpy and matplotlib.

./c++/ contains the tools used to find the temperature isosurfaces required for coupling the hydrodynamic module to the hadronic cascade. Stand-alone. Compiled only with g++-4.2. ./c++/main.cpp shows how to add points to be wrapped and how to call the wrapping function. Functionality for asking for the volume element exists and should be natural.