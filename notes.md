Conway
======

Structure
---------

Objects:
	* Cells (alive or dead)
	* Grid contains Cells

Data:
	* Cell : status
	* Grid : cell location

Functions:
	* Cell : change state -> (status)
	* Grid : update cells -> (previousGrid)

should translate between terminal space (0,0) is top left and grid space (0,0) is middle
not in grid, that is implementation specific.
