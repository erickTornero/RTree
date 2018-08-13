# RTree

Build command:
```
g++ source.cpp RTree.cpp Object.cpp
```
Basic example how to use it, can be found in **source.cpp** file
## TODO LIST:

### Polygons points are inserted by copy not with pointers, check & fix this

## DONE LIST

## SEARCH OR QUERYS.
Tested with a single root non leaf. Missing especificantions what is an intersection of poligons,
It includes a single line?, solve with classmates.

## Insert on root - leaf
Single insertion when only exists the root. 

## Create parent with cuadratic split when the leaf is the root.
Create parent and split the root -leaf using cuadratic split. Missing more testing with more data.

## Insert:

### Go from root to the right leaf!.

### Insert internal node when it node overflows!.

### Handle poligons of any amount of vertices.
At the moment only rectangles are handled, this could be solved with a single vector of points.

### FIX, parent argument in a sort of functions.
It's maybe no longer necessary.

### k - nearest neighbor
Join Israel Functions.
