#include <iostream>

class Cell {
	int row;
	int col;
public:
   	Cell(int row, int col);
	Cell operator + (Cell that);
	bool operator == (Cell that);
	friend std::ostream& operator << (std::ostream& os , const Cell& p);
};
