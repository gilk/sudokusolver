Sudoku solver which does not use trial and error or at least not by default, I might add a brute force method just to check if a sudoku can be solved. After coding this and still not being able to solve fiendish104.in I found a list of sudoku solving techniques @ http://www.sudokuoftheday.com/pages/techniques-overview.php


List of possible logical techniques and coded status
n	Name					Status				Function name/notes
1	single position			coded				scanGroup
2	single candidate		coded				scanSolver
3	candidate lines			coded				removelinealikes
4	double pair				not coded
5	multiple lines			coded				removeboxalikes
6	naked pairs				coded				removelikegroup... (code does triplets, quads...)
7	hidden pairs			not coded
8	X-wing					not coded
9	Swordfish				not coded
10	Forcing Chains			not coded			A form of trial and error
11	Nishio					not coded			Another trial and error method
12	Guessing				not coded			Ummm, no