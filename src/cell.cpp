#include "cell.hpp"

Cell::Cell(int row, int col) : row(row), col(col) { };

Cell Cell::operator + (Cell that) {
	return Cell {row + that.row, col + that.col};
}

bool Cell::operator == (Cell that) {
	return (row == that.row) && (col == that.col);
}


std::ostream& operator << (std::ostream& os , const Cell& p) {
	os << "(" << p.row << "," << p.col << ")";
	return os;
}
