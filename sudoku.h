#include <iostream>
#include <fstream>
class sudoku
{
private:
	int board[81], boolboard[81], filled;
	
public:
	void fill();
	//default constructor for and empty board
	sudoku()
	{
		for(int i(0);i<81;i++){
			board[i]=boolboard[i]=0;
		}
		filled=0;
	}
	//read a sudoku in from file
	sudoku(std::ifstream& fin)
	{
		filled=0;
		int entry;
		for(int i(0);i<81;i++){
			fin >> entry;
			fill(i,entry);
		}
	}
	
	//return the x co-ord
	int x(int entry){
		return entry%=9;
	}
	//return the y co-ord
	int y(int entry){
		return entry/=9;
	}
	
	//print sudoku to screen
	void print(){
		std::cout << "---------------------" << std::endl;
		for(int i(0);i<81;i++){
			if(x(i)==3||x(i)==6) std::cout << "| ";
			if((y(i)==3||y(i)==6)&&x(i)==0) std::cout << "---------------------" << std::endl;
			std::cout << board[i] << " ";
			if(x(i)==8) std::cout << std::endl;
		}
		std::cout << "---------------------" << std::endl;
		std::cout << "The number of filled squares is " << filled << std::endl;
	}
	
	void printboolboard(){
		std::cout << "---------------------" << std::endl;
		for(int i(0);i<81;i++){
			if(x(i)==3||x(i)==6) std::cout << "| ";
			if((y(i)==3||y(i)==6)&&x(i)==0) std::cout << "---------------------" << std::endl;
			std::cout << boolboard[i] << " ";
			if(x(i)==8) std::cout << std::endl;
		}
		std::cout << "---------------------" << std::endl;
		std::cout << "The number of filled squares is " << filled << std::endl;
	}
	
	void printboolboard(int val){
		
		if (val==10){
			{
				std::cout << "---------------------" << std::endl;
				for(int i(0);i<81;i++){
					if(x(i)==3||x(i)==6) std::cout << "| ";
					if((y(i)==3||y(i)==6)&&x(i)==0) std::cout << "---------------------" << std::endl;
					std::cout << 9-bitcount(boolboard[i]) << " ";
					if(x(i)==8) std::cout << std::endl;
				}
				std::cout << "---------------------" << std::endl;
				std::cout << "The number of filled squares is " << filled << std::endl;
			}
		}
		else {
		std::cout << "---------------------" << std::endl;
		for(int i(0);i<81;i++){
			if(x(i)==3||x(i)==6) std::cout << "| ";
			if((y(i)==3||y(i)==6)&&x(i)==0) std::cout << "---------------------" << std::endl;
			std::cout << isPossible(i,val) << " ";
			if(x(i)==8) std::cout << std::endl;
		}
		std::cout << "---------------------" << std::endl;
		std::cout << "The number of filled squares is " << filled << std::endl;}
	}
	
	//find the other members of row, column or box
	int row(int entry, int place){
		int nrow = y(entry);
		return nrow*9 + place;
	}
	int col(int entry, int place){
		int ncol = x(entry);
		return place * 9 + ncol;
	}
	int box(int entry, int place){
		int boxy = y(entry)/3,boxx = x(entry)/3;
		int start = 27*boxy + 3*boxx;
		int inboxx = place%3;
		int inboxy = place/3;
		return start + (9*inboxy) + inboxx;
	}
	//return first element address of a row
	int row(int n){
		return n*9;
	}
	//return first element address of a box
	int box(int n){
		int x = n%3, y = n/3;
		return (27*y) + (3*x);
	}
	//return box number
	int boxn(int address){
		return (y(address)/3)*3+x(address)/3;
	}
	//fill in an entry
	void fill(int address, int value){
		if(address>=0&&address<81&&value<10&&value>0){
			board[address] = value;
			boolboard[address] = 511; //9 ones in binary rep
			for(int i(0);i<9;i++){
				boolboard[row(address,i)]|=1<<value-1;
				boolboard[col(address,i)]|=1<<value-1;
				boolboard[box(address,i)]|=1<<value-1;
			}
			filled++;
		}
	}
	//count impossible values
    int  bitcount(int x) {
        int count(0);
        for (; x; ++count, x &= (x - 1));
        return count;
    }
	void scanSolver(){
		bool changed(true);
			for(int i(0);i<81;i++){
				//std::cout << bitcount(boolboard[i]) << std::endl;
				if(bitcount(boolboard[i])==8){
					int val = 0;
					while(boolboard[i]&(1<<val)){
						val++; 
					}
						fill(i,val+1);
				}
			}
	}
	
	//look for instances where there is only one place a value can be placed in a row/column/box
	void scanGroup(){
		int binval,rowcount,colcount,boxcount;
		for(int val(1);val<10;val++){
			binval = 1<<val-1;
			for(int group(0);group<9;group++){
				rowcount=0,colcount=0,boxcount = 0;
				int coladd = group, rowadd=row(group), boxadd = box(group);
				for(int place(0);place<9;place++){
					if((boolboard[row(rowadd,place)]&binval) == 0) rowcount++;
					if((boolboard[col(group,place)]&binval) == 0) colcount++;
					if((boolboard[box(boxadd,place)]&binval) == 0) boxcount++;
				}
				//std::cout << rowcount <<'\t' << colcount << '\t' << boxcount << std::endl;
				if(colcount==1){
					for(int i(0);i<9;i++){
						if((boolboard[col(group,i)]&binval)==0)
							fill(col(group,i),val);
							break;
					}
				}
				if(rowcount==1){
					for(int i(0);i<9;i++){
						if((boolboard[row(rowadd,i)]&binval)==0){
							fill(row(rowadd,i),val);
							break;
						}
					}
				}
				if(boxcount==1){
					for(int i(0);i<9;i++){
						if((boolboard[box(boxadd,i)]&binval)==0){
							fill(box(boxadd,i),val);
							break;
						}
					}
				}
			}
		}
	}
	bool isPossible(int address,int val){
		if((boolboard[address]&1<<(val-1))==0) return true;
		return false;
	}
	bool removePos(int address,int val){
		if(isPossible(address,val)){
			boolboard[address]|=1<<val-1;
//			std::cout << "removed " << val << " from " << address << std::endl;
			return true;
		}
		return false;
	}
//remove possible entries from line l, outside of box n, if box n can only have that value in line l
	bool removelinealikes(){
		bool res = false;
		int poscount;
		for(int val(1);val<10;val++){
			for(int group(0);group<9;group++){
				int boxadd = box(group);
				poscount=0;
				for(int place(0);place<9;place++){
					if(isPossible(box(boxadd,place),val)) poscount++;
				}
				int column(-1), nrow(-1);
				if(poscount>1&&poscount<4){
					bool samecol(true), samerow(true);
					for(int i(0);i<9;i++){
						if(isPossible(box(boxadd,i),val)){
							if(column==-1) column = x(box(boxadd,i));
							else if(column!=x(box(boxadd,i))) samecol = false;
							if(nrow==-1) nrow = y(box(boxadd,i));
							else if(nrow!=y(box(boxadd,i))) samerow = false;
						}
					}
					if(samecol){
						for(int i(0);i<9;i++){
							int address = col(column,i);
							if(boxn(address)!=group&&isPossible(address,val)){
								if(removePos(address,val)) res = true;
							}
						}
					}
					if(samerow){
						for(int i(0);i<9;i++){
							int address = row(row(nrow),i);
							if(boxn(address)!=group&&isPossible(address,val)){
								if(removePos(address,val)) res = true;
							}
						}
					}
				}
			}
		}
		return res;
	}
	
	//remove possible entries from box n, if line l can only have that value in box n
	bool removeboxalikes(){
		bool res = false;
		int rowposcount,colposcount;
		for(int val(1);val<10;val++){
			for(int group(0);group<9;group++){
				int coladd = group, rowadd = row(group);
				rowposcount = 0, colposcount = 0;
				for(int place(0);place<9;place++){
					if(isPossible(row(rowadd,place),val)) rowposcount++;
					if(isPossible(col(coladd,place),val)) colposcount++;
				}
				int nbox(-1);
				if(rowposcount>1&&rowposcount<4){
					bool samebox(true);
					for(int i(0);i<9;i++){
						if(isPossible(row(rowadd,i),val)){
							if(nbox==-1) nbox = boxn(row(rowadd,i));
							else if(nbox!=boxn(row(rowadd,i))) samebox = false;
						}
					}
					if(samebox){
						for(int i(0);i<9;i++){
							int address = box(box(nbox),i);
							if(y(address)!=group){
								if(removePos(address,val)) res = true;
							}
						}
					}
				}
				
				////////
				if(colposcount>1&&colposcount<4){
					bool samebox(true);
					for(int i(0);i<9;i++){
						if(isPossible(col(coladd,i),val)){
							if(nbox==-1) nbox = boxn(col(coladd,i));
							else if(nbox!=boxn(col(coladd,i))) samebox = false;
						}
					}
					if(samebox){
						for(int i(0);i<9;i++){
							int address = box(box(nbox),i);
							if(x(address)!=group){
								if(removePos(address,val)) res = true;
							}
						}
					}
				}
				
			}
		}
		return res;
	}
	
	//look for groups of elements that have the same possible values and then elimnate others,
	//for example if two elements in a box can only be a 2 or 5 then no other elements in that box can be a 2 or 5 (naked pairs)
	bool removelikegroupsbox(){
		bool res(false);
		int boolcount,testbool;
		for(int group(0);group<9;group++){
			for(int place(0);place<9;place++){
				testbool = boolboard[box(boxn(group),place)];
				boolcount= 0;
				for(int i(0);i<9;i++){if(testbool==boolboard[box(boxn(group),i)]) boolcount++;}
				if(boolcount==9-bitcount(testbool)){
					for(int i(0);i<9;i++){
						if(testbool!=boolboard[box(boxn(group),i)]&&(testbool&boolboard[box(boxn(group),i)])!=0){
							(boolboard[box(boxn(group),i)]|=~testbool)&=511;
							res = true;
						}
					}
				}
			}
		}
		return res;
	}
	bool removelikegroupsrow(){
		bool res(false);
		int boolcount,testbool;
		for(int group(0);group<9;group++){
			for(int place(0);place<9;place++){
				testbool = boolboard[row(row(group),place)];
				boolcount= 0;
				for(int i(0);i<9;i++){if(testbool==boolboard[row(row(group),i)]) boolcount++;}
				if(boolcount==9-bitcount(testbool)){
					for(int i(0);i<9;i++){
						if(testbool!=boolboard[row(row(group),i)]&&(testbool&boolboard[row(row(group),i)])!=0){
							if((boolboard[row(row(group),i)]|((~testbool)&511))==boolboard[row(row(group),i)]) break;
							(boolboard[row(row(group),i)]|=~testbool)&=511;
							res = true;
						}
					}
				}
			}
		}
		return res;
	}
	bool removelikegroupscol(){
		bool res(false);
		int boolcount,testbool;
		for(int group(0);group<9;group++){
			for(int place(0);place<9;place++){
				testbool = boolboard[col(group,place)];
				boolcount= 0;
				for(int i(0);i<9;i++){if(testbool==boolboard[col(group,i)]) boolcount++;}
				if(boolcount==9-bitcount(testbool)){
					for(int i(0);i<9;i++){
						if(testbool!=boolboard[col(group,i)]&&(testbool&boolboard[col(group,i)])!=0){
							if((boolboard[col(group,i)]|((~testbool)&511))==boolboard[col(group,i)]) break;
							(boolboard[col(group,i)]|=~testbool)&=511;
							res = true;
						}
					}
				}
			}
		}
		return res;
	}

	
	//check is board is broken
	bool boardBroken(){
		for(int i(0);i<81;i++){
			if(board[i]==0&&boolboard[i]==511) return true;
		}
		return false;
	}
	
	void solve(){
		int startfill(filled),k(0);
		scanSolver();
		scanGroup();
		while(true){
			if(removelinealikes()) startfill--;
			if(removeboxalikes()) startfill--;
			if(removelikegroupsbox()) startfill--;
			if(removelikegroupsrow()) startfill--;
			if(removelikegroupscol()) startfill--;
			scanSolver();
			scanGroup();
			k++;
//			std::cout << filled << std::endl;
			if(filled == 81){
				std::cout << "The sudoku is complete and was solved in " << k << " passes" << std::endl;
				break;
			}
			if(filled==startfill){
				std::cout << "The sudoku cannot be solved completely with this method after " << k << " passes\nEither this method is incomplete or the sudoku is invalid or solving it may require guess work" << std::endl;
				if(boardBroken()) std::cout << "THIS SUDOKU IS MOTHERFUCKING BULLSHIT" << std::endl;
				break;
			}
			startfill=filled;
		}
	}
	
};
