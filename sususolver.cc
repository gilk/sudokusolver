#include "sudoku.h"
using namespace std;

int main(int argc, char *argv[]) {
	ifstream fin ("sudokus/fiendish105.in");
	sudoku test2(fin);
	test2.print();
	test2.solve();
	test2.print();
	return 0;
}