#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//procedures
void showBoard(char mx[9]);
//funcs
int insertData(char mx[9], int opt);
int statusGame(char mx[9], int player, char mark);
int botStep(char mx[9]);

int main(){
   char mx[9];
   int opt;
   memset(mx, ' ', 9);

   printf("\033[1;31m.--TicTacToe Game---\n\
         \r|\033[0m[1] - Versus other Player\n\
         \r\033[1;31m|\033[0m[2] - Versus the Computer\n\
         \r\033[1;31m|\033[0m[3] - Abort the Program\n\
         \r\033[1;31m'--->\033[0m ");
   scanf("%d", &opt);

   switch(opt){
      case 1:
	 showBoard(mx);
	 insertData(mx, opt);
         break;
      case 2:
	 showBoard(mx);
	 insertData(mx, opt);
         break;
      case 3:
	 printf("\n\033[0;31mBye!\033[0m\n\n");
   }
}

int insertData(char mx[9], int opt){
   int i, pass, house, player;
   char mark;

   //Versus other Player
   for(i=1; i<10; i++){
      if(opt == 1){
	 pass = 0;
	 //Player{[1], [2]}
	 while(pass == 0){
	    player = (i % 2 == 1) ? 1 : 2;
	    mark = (player % 2 == 1) ? 'o' : 'x';
	    do{
	       printf("\n\n.---Player[%d]\n", player);
	       printf("'-----> ");
	       scanf("%d", &house);
	       if((house > 0) && (house <= 9)){
		  pass++;
	       }
	       else
		  printf("\n\033[1;31mWrong number, try again!\033[0m\n");
	    }while(pass == 0);
	    pass = 0;
	    if((mx[house-1] == ' ')){
	       mx[house-1] = mark;
	       if(statusGame(mx, player, mark) == 0){
		  showBoard(mx);
		  return 0;
	       }
	       pass++;
	    } else {
	       printf("\n\033[1;31mOccupied Position! Try Again!\033[0m\n");
	    }
	 }
	 showBoard(mx);

      //Player Versus Computer
      } else {
	 pass = 0;
	 while(pass == 0){
	    mark = 'o';
	    do{
	       printf("\n\n.---Player\n");
	       printf("'-----> ");
	       scanf("%d", &house);
	       if((house > 0) && (house <= 9)){
		  pass++;
	       }
	       else
		  printf("\n\033[1;31mWrong number, try again!\033[0m\n");
	    }while(pass == 0);
	    pass = 0;
	    if((mx[house-1] == ' ')){
	       mx[house-1] = mark;
	       player = 1;
	       pass++;
	       if(statusGame(mx, player, mark) == 0){
		  showBoard(mx);
		  return 0;
	       }
	    }
	 }
	 if(botStep(mx) == 0){
	    showBoard(mx);
	    return 0;
	 } 
      }
   }
   return 1;
}

int statusGame(char mx[9], int player, char mark){
   int j = 0, draw = 0;
   //{Horizontal, Vertical} Check
   for(int i=0; i<3;){
      for(; j<3; j++){
	 if((mx[i] == mark) && (mx[i+1] == mark) && (mx[i+2] == mark)||\
	    (mx[j] == mark) && (mx[j+3] == mark) && (mx[j+6] == mark)){
	    if((player ==1) || (player ==2)){
	       printf("\n\033[1;31mPlayer[%d] - Winner!!!\033[0m\n", player);
	    }
	    return 0;
	 }
	 i += 3;
      }
   }

   //Diagonal Check
   if((mx[0] == mark) && (mx[4] == mark) && (mx[8] == mark) ||\
      (mx[6] == mark) && (mx[4] == mark) && (mx[2] == mark)){
      if((player == 1) || (player == 2)){
	 printf("\n\033[1;31mPlayer[%d] - Winner!!!\033[0m\n", player);
      }
      return 0;
   }

   //Draw Game
   for(j=0; j<9; j++){
      draw = (mx[j] != ' ') ? draw + 1 : draw;
   }
   if(draw == 9){
      printf("\n\033[1;31mDraw Game\033[0m\n\n");
      return 0;
   }
   return 1;
}

void showBoard(char mx[9]){
   printf(".-----------.\n\
         \r| %c | %c | %c |\n\
	 \r|-----------|\n\
         \r| %c | %c | %c |\n\
         \r|-----------|\n\
         \r| %c | %c | %c |\n\
         \r'-----------'\n",\
	 mx[0], mx[1], mx[2],\
	 mx[3], mx[4], mx[5],\
	 mx[6], mx[7], mx[8]);

}

int botStep(char mx[9]){
   int pass = 0, house;
   char mark = 'x';
   srand( time(NULL) );
   while(pass == 0){
      house = rand() % 10;
      if(mx[house] == ' '){
	 mx[house] = mark;
	 showBoard(mx);
	 pass++;
      }
   }
   if(statusGame(mx, 0, mark) == 0){
      printf("\n\033[1;31mWe Will ");
      printf("\033[0;31mRULE\033[0m ");
      printf("\033[1;31mThe World!!! >:) \n\033[0m");
      printf("\033[0;31m[CAUTION] - The Computer is the Winner!\033[0m\n");
      return 0;
   }
   return 1;
}
