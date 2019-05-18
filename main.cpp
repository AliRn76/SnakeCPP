d#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <time.h>

#define SIZE_X 40
#define SIZE_Y 20

using namespace std;

char map[SIZE_Y][SIZE_X];

class SnakeMap{
		
	public:	
		void snakeBorder(){                                                     
			for(int i = 0; i < SIZE_Y; i++){
				for(int j = 0; j < SIZE_X; j++){
					if(i == 0 || j == 0 || i == SIZE_Y-1 || j == SIZE_X-1) 
						map[i][j] = '#'; 									          
					else 
						map[i][j]=' ';
				}
			}
		}
		
		void showConsoleCursor  (bool showFlag) {   
			HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);   
			CONSOLE_CURSOR_INFO     cursorInfo;   
			GetConsoleCursorInfo(out, &cursorInfo);   
			cursorInfo.bVisible = showFlag;   
			SetConsoleCursorInfo(out, &cursorInfo); 
		}
			
		void clearScreen(){
			COORD start_pos;
			HANDLE hOut;
			
			start_pos = {0 , 0};
			hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			
		//	system("cls");
			SetConsoleCursorPosition(hOut, start_pos);
			showConsoleCursor(false);		
		}
		
		void printMap(){                                                         
			clearScreen();
			for(int i = 0; i < SIZE_Y; i++){
				for(int j = 0; j < SIZE_X; j++){
					if(map[i][j] == '#') 
						cout <<(char)219<<(char)219;
					else if(map[i][j] == 'f') 
						cout << " *";
					else if(map[i][j] == 'p')
						cout << " O";
					else cout << "  ";
				}
				cout<<endl;
			}
		}
};

class MovePlayer{
	public:		
		char get_key;
		int i = 10 ,j = 20 , snake_len = 1;
		bool up = true, down = true, left = true, right = true;
		HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
		SnakeMap print;
		
		void gameLogic(){
				while (down == false && get_key == 's'){            
					get_key = 'w';	
				};
				while (up == false && get_key == 'w'){
					get_key = 's';	
				};
				while (left == false && get_key == 'a'){
					get_key = 'd';	
				};
				while (right == false && get_key == 'd'){
					get_key = 'a';	
				};
		}
		
		void pressKey(){
			
			while(!winCheck() && !loseCheck()){	
					
				do{
					get_key = _getch();
				}while(get_key != 'w' && get_key != 'a' && get_key != 's' && get_key != 'd');

				gameLogic();

				int beforeJ = (j - snake_len + 1);
				int presentJ = j;
				int afterJ = (j + snake_len - 1);
				
				int beforeI = (i - snake_len + 1);
				int presentI = i;
				int afterI = (i + snake_len - 1);
			
				switch (get_key){                                          
					case 'w':
						
						while(!kbhit() && !loseCheck() && !winCheck()){					
							if (beforeJ < presentJ){
								if(map[presentI][beforeJ] == 'p'){
									map[presentI][beforeJ] = ' ';			
								}
								beforeJ ++;		
							}
							if (afterJ > presentJ){
								if(map[presentI][afterJ] == 'p'){
									map[presentI][afterJ] = ' ';				
								}	
								afterJ --;
							}

							i--;
							food();
							eatFood();
							map[i][j] = 'p';
							if (map[i + snake_len][j] == 'p') 
								map[i + snake_len][j] = ' ';	
							print.printMap();	
							Sleep(200);			
							down =false;
							left= true;
							right = true;			
								
						};
						break;
						
					case 'a':
						
						while(!kbhit() && !loseCheck() && !winCheck()){
							if(beforeI < presentI){
								if(map[beforeI][presentJ] == 'p'){
									map[beforeI][presentJ] = ' ';				
								}
								beforeI ++;
							}
							if(afterI > presentI){
								if(map[afterI][presentJ] == 'p'){
									map[afterI][presentJ] = ' ';				
								}
								afterI --;
							}
							
							j--;
							food();
							eatFood();
							map[i][j] = 'p';
							if(map[i][j + snake_len] == 'p')
								map[i][j + snake_len] = ' ';
							print.printMap();
							Sleep(200);
							right= false;
							up =true;
							down= true;									

						};
						break;
						
					case 's':
						
						while(!kbhit() && !loseCheck() && !winCheck()){

							if (beforeJ < presentJ){
								if(map[presentI][beforeJ] == 'p'){
									map[presentI][beforeJ] = ' ';			
								}
								beforeJ ++;		
							}
							if (afterJ > presentJ){
								if(map[presentI][afterJ] == 'p'){
									map[presentI][afterJ] = ' ';				
								}	
								afterJ --;
							}
							
							i++;
							food();
							eatFood();
							map[i][j] = 'p';
							if(map[i - snake_len][j] == 'p')
								map[i - snake_len][j] = ' ';
							print.printMap();		
							Sleep(200);	
							up= false;
							left = true;
							right= true;
						
						};
						break;
						
					case 'd':
						
						while(!kbhit() && !loseCheck() && !winCheck()){

							if(beforeI < presentI){
								if(map[beforeI][presentJ] == 'p'){
									map[beforeI][presentJ] = ' ';				
								}
								beforeI ++;
							}
							if(afterI > presentI){
								if(map[afterI][presentJ] == 'p'){
									map[afterI][presentJ] = ' ';				
								}
								afterI --;
							}
							
							j++;
							food();
							eatFood();
							map[i][j] = 'p';
							if(map[i][j - snake_len] == 'p')
								map[i][j - snake_len] = ' ';
							print.printMap();
							Sleep(200);
							left= false;
							up=true;
							down=true;								

						};
						break;	
				}
			};
		}

		bool winCheck(){
			bool win = false;
			if(snake_len == 6)
				win = true;
			return win;
		}
		
		bool loseCheck(){
			bool lose = false;
			if(i == SIZE_Y-1 || i == 0 || j == SIZE_X-1 || j == 0/* || map[i][j] == 'p' */) 
				lose = true;
			return lose;
		}
		
		
		void food(){
			bool isFood = true;
			for(int i = 0; i < SIZE_X; i++){
				for(int j = 0; j < SIZE_Y; j++){
					if(map[j][i] == 'f')
						isFood = false;
				}
			}
			if(isFood){
				srand(time(NULL));
				int food_x;
				int food_y;
			
				food_x = rand() % SIZE_X - 1 ;
				food_y = rand() % SIZE_Y - 1;				
				
				if (map[food_y][food_x] == ' ' ){
					map[food_y][food_x] = 'f';					
				}
				else{
					while(map[food_y][food_x] !=  ' '){
						food_x = rand() % SIZE_X - 1;
						food_y = rand() % SIZE_Y - 1;
					};
					map[food_y][food_x] = 'f';
				}
			}
		}
		
		void eatFood(){
			if(map[i][j] == 'f')
				snake_len ++;			
		}
		
		void finish(){
			COORD finish_pos = {3, 24};
			SetConsoleCursorPosition(h,finish_pos);
			
			if (loseCheck()) {		
				cout<<"Game Over"<<endl;
			}

			else {
			cout<<"You Win , Good Job"<<endl;
			}
		}
};

int main(int argc, char** argv) {
	SnakeMap a;
	a.snakeBorder();
	map[10][20] = 'p';
	
	a.printMap();
	cout<<"\n w = up , a = left , s = down , d = right \n\n eat 5 food to win";
	map[10][20] = ' ';
	
	
	
	MovePlayer b;
	b.pressKey();
	
	b.finish();

	return 0;
}
