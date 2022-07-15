#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <thread>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int green_1_default_x=147,green_2_default_x=245,green_3_default_x=147,green_4_default_x=245;
int green_1_default_y=170,green_2_default_y=170,green_3_default_y=235,green_4_default_y=235;

int red_1_default_x=172,red_2_default_x=235,red_3_default_x=172,red_4_default_x=239;
int red_1_default_y=536,red_2_default_y=536,red_3_default_y=594,red_4_default_y=593;

int blue_1_default_x=537,blue_2_default_x=600,blue_3_default_x=537,blue_4_default_x=605;
int blue_1_default_y=536,blue_2_default_y=536,blue_3_default_y=594,blue_4_default_y=594;

int yellow_1_default_x=531,yellow_2_default_x=593,yellow_3_default_x=530,yellow_4_default_x=596;
int yellow_1_default_y=177,yellow_2_default_y=177,yellow_3_default_y=235,yellow_4_default_y=235;

bool Choose_token=false;

struct red_index{
	int x;
	int y;
};
red_index red_all[57];

struct yellow_index{
	int x;
	int y;
};
yellow_index yellow_all[57];

struct blue_index{
	int x;
	int y;
};
blue_index blue_all[57];


struct green_index{
	int x;
	int y;
};
green_index green_all[57];



bool R1=false,R2=false,R3=false,R4=false;
bool B1=false,B2=false,B3=false,B4=false;
bool Y1=false,Y2=false,Y3=false,Y4=false;
bool G1=false,G2=false,G3=false,G4=false;


bool R_hit = false;
bool Y_hit = false;
bool G_hit = false;
bool B_hit = false;


int six_count = 0;
int not_six_red = 0;
int not_six_blue = 0;
int not_six_green = 0;
int not_six_yellow = 0;

bool red_out = false;
bool green_out = false;
bool blue_out = false;
bool yellow_out = false;

int temp_pos_1_x=0;
int temp_pos_1_y=0;
int temp_pos_2_x=0;
int temp_pos_2_y=0;
int temp_pos_3_x=0;
int temp_pos_3_y=0;
int temp_pos_4_x=0;
int temp_pos_4_y=0;


int dice_value=1,dice_value_play=1;
bool dice_hit=false;//,dice_select=false;
bool isRunning = true;
int random_turn=0,number_of_players=4;
int mouse_x=0;
int mouse_y=0;
bool mega_close=true;
SDL_Event sdl_event;


pthread_t red;
pthread_t green;
pthread_t yellow;
pthread_t blue;
pthread_t master;
pthread_t Locker;

pthread_mutex_t dice_lock=PTHREAD_MUTEX_INITIALIZER;

sem_t lock1;
sem_t lock2;
sem_t lock3;
sem_t lock4;

SDL_Window *sdl_window = NULL;
SDL_Renderer *render = NULL;
SDL_Texture* Texture_RED_1 = NULL;
SDL_Texture* Texture_RED_2 = NULL;
SDL_Texture* Texture_RED_3 = NULL;
SDL_Texture* Texture_RED_4 = NULL;
SDL_Texture* Texture_BLUE_1 = NULL;
SDL_Texture* Texture_BLUE_2 = NULL;
SDL_Texture* Texture_BLUE_3 = NULL;
SDL_Texture* Texture_BLUE_4 = NULL;
SDL_Texture* Texture_GREEN_1 = NULL;
SDL_Texture* Texture_GREEN_2 = NULL;
SDL_Texture* Texture_GREEN_3 = NULL;
SDL_Texture* Texture_GREEN_4 = NULL;
SDL_Texture* Texture_YELLOW_1 = NULL;
SDL_Texture* Texture_YELLOW_2 = NULL;
SDL_Texture* Texture_YELLOW_3 = NULL;
SDL_Texture* Texture_YELLOW_4 = NULL;
SDL_Texture* Texture_DICE_1 = NULL;
SDL_Texture* Texture_DICE_2 = NULL;
SDL_Texture* Texture_DICE_3 = NULL;
SDL_Texture* Texture_DICE_4 = NULL;
SDL_Texture* Texture_DICE_5 = NULL;
SDL_Texture* Texture_DICE_6 = NULL;
SDL_Texture* Texture = NULL;


SDL_Rect destination;
SDL_Rect RED_1;
SDL_Rect RED_2;
SDL_Rect RED_3;
SDL_Rect RED_4;
SDL_Rect BLUE_1;
SDL_Rect BLUE_2;
SDL_Rect BLUE_3;
SDL_Rect BLUE_4;
SDL_Rect GREEN_1;
SDL_Rect GREEN_2;
SDL_Rect GREEN_3;
SDL_Rect GREEN_4;
SDL_Rect YELLOW_1;
SDL_Rect YELLOW_2;
SDL_Rect YELLOW_3;
SDL_Rect YELLOW_4;
SDL_Rect DICE_1;
SDL_Rect DICE_2;
SDL_Rect DICE_3;
SDL_Rect DICE_4;
SDL_Rect DICE_5;
SDL_Rect DICE_6;

void initializer(){
		///////////////////////////////RED indexes//////////////////////////////////////

	 for(int i=0;i<5;i++){
	 red_all[i].x = 340;
	 red_all[i].y = 668 - ( (i+1) *41);
	 }
	 for(int i=5;i<11;i++){
	 red_all[i].x = 299 - ( (i-5) * 41 );
	 red_all[i].y = 422;
	 }
 red_all[11].x = 94;
	 red_all[11].y = 379;
	 for(int i=12;i<18;i++){
	 red_all[i].x = 94 + ( (i-12) * 41);
	 red_all[i].y = 336;
	 }
	 for(int i=18;i<24;i++){
	 red_all[i].x = 340;
	 red_all[i].y = 295 - ( (i-18) *41);
	 }
	 red_all[24].x = 382;
	 red_all[24].y = 92;
 for(int i=25;i<31;i++){
	 	red_all[i].x = 424;
	 	red_all[i].y = 92 + ( (i-25) *41);
	 }
	 for(int i=31;i<37;i++){
	 	red_all[i].x = 465 + ((i-31) * 41);
	 	red_all[i].y = 338;
	 }
	 red_all[37].x = 670;
	 red_all[37].y = 379;
	 for(int i=38;i<44;i++){
	 	red_all[i].x = 670 - ((i-38)*41);
	 	red_all[i].y = 421;
	 }
 for(int i=44;i<50;i++){
	 	red_all[i].x = 424;
	 	red_all[i].y = 464 + ((i-44) *41);
	 }
	 for(int i=50;i<57;i++){
	 	red_all[i].x = 383;
	 	red_all[i].y =  669 - ((i-50) *41);
 }

    
    
    
    
    
    
    
    
    
    
    
    
    	///////////////////////////////green indexes//////////////////////////////////////
	for(int i=0;i<5;i++){
	green_all[i].x = 94 + ( (i+1) * 41 );
	green_all[i].y = 336;
	}
	
	for(int i=5;i<11;i++){
	green_all[i].x = 340;
	green_all[i].y = 295 - ( (i-5) *41);
	}

	green_all[11].x = 382;
	green_all[11].y = 92;
	
	for(int i=12;i<18;i++){
		green_all[i].x = 424;
		green_all[i].y = 92 + ( (i-12) *41);
	}
	for(int i=18;i<24;i++){
		green_all[i].x = 465 + ((i-18) * 41);
		green_all[i].y = 338;
	}

	green_all[24].x = 670;
	green_all[24].y = 379;
	
	for(int i=25;i<31;i++){
		green_all[i].x = 670 - ((i-25)*41);
		green_all[i].y = 421;
	}
	
	for(int i=31;i<37;i++){
		green_all[i].x = 424;
		green_all[i].y = 464 + ((i-31) *41);
	}
	
	green_all[37].x = 383;
	green_all[37].y = 669;


	for(int i=38;i<44;i++){
		green_all[i].x = 340 ;
		green_all[i].y = 668-((i-38)*41) ;
	}
	
	for(int i=44;i<50;i++){
		green_all[i].x = 299 - ( (i-44) * 41 );
	    green_all[i].y = 422;
	}
	for(int i=50;i<57;i++){
		green_all[i].x = 94 + ( (i-50) * 41 );
		green_all[i].y = 379;
	}
	

	///////////////////////////////green indexes//////////////////////////////////////




    	for(int i=0;i<5;i++){
	yellow_all[i].x = 424;
	yellow_all[i].y = 92+( (i+1) *41);
	}
	for(int i=5;i<11;i++){
	yellow_all[i].x = 465+( (i-5) * 41 );
	yellow_all[i].y = 338;
	}
	yellow_all[11].x = 670;
	yellow_all[11].y = 379;

	for(int i=12;i<18;i++){
	yellow_all[i].x = 670-( (i-12) * 41 );
	yellow_all[i].y = 421;
	}

	for(int i=18;i<24;i++){
	yellow_all[i].x = 424;
	yellow_all[i].y = 464+( (i-18) *41);
	}

	yellow_all[24].x = 383;
	yellow_all[24].y = 669;
	for(int i=25;i<31;i++){
		yellow_all[i].x = 340;
		yellow_all[i].y = 668 - ( (i-25) *41);
	}
	for(int i=31;i<37;i++){
		yellow_all[i].x = 299 - ( (i-31) * 41);
		yellow_all[i].y = 422;
	}
	yellow_all[37].x = 94;
	yellow_all[37].y = 379;

	for(int i=38;i<44;i++){
	yellow_all[i].x = 94 + ((i-38)*41);
	yellow_all[i].y = 336;
	}
	for(int i=44;i<50;i++){
		yellow_all[i].x = 340;
		yellow_all[i].y = 295 - ((i-44) *41);
	}
	for(int i=50;i<57;i++){
		yellow_all[i].x = 382;
		yellow_all[i].y = 94 + ((i-50) *41);

	}





	///////////////////////////////blue indexes//////////////////////////////////////
	for(int i=0;i<5;i++){
	blue_all[i].x = 670 -( (i+1) * 41 );
	blue_all[i].y = 421;
	}
	
	for(int i=5;i<11;i++){
	blue_all[i].x = 424 ;
	blue_all[i].y = 464 +((i-5)*41);
	}

	blue_all[11].x = 383;
	blue_all[11].y = 669;
	
	for(int i=12;i<18;i++){
	blue_all[i].x = 340;
	blue_all[i].y = 668-((i-12)*41) ;
	}
	for(int i=18;i<24;i++){
	blue_all[i].x = 299 - ( (i-18) * 41);
	blue_all[i].y = 422;
	}

	blue_all[24].x = 94;
	blue_all[24].y = 379;
	
	for(int i=25;i<31;i++){
	blue_all[i].x = 94 + ( (i-25) * 41 );
	blue_all[i].y = 336;
	}
	
	for(int i=31;i<37;i++){
	blue_all[i].x = 340;
	blue_all[i].y = 295 - ( (i-31) *41);
	}
	
	blue_all[37].x = 382;
	blue_all[37].y = 94;


	for(int i=38;i<44;i++){
		blue_all[i].x = 424;
		blue_all[i].y = 92 + ( (i-38) *41);
	}
	
	for(int i=44;i<50;i++){
		blue_all[i].x = 465 + ((i-44) * 41);
		blue_all[i].y = 338;
	}
	for(int i=50;i<57;i++){
		blue_all[i].x = 670 - ((i-50)*41);
		blue_all[i].y = 379;
	}



	///////////////////////////////blue indexes//////////////////////////////////////
	
	
	
	
	
	
	//////////////////////////////////DICE////////////////////////////////////////////////////
	DICE_1.x = 370;
	DICE_1.y = 370;
	DICE_1.w = 60;
	DICE_1.h = 60;



	DICE_2.x = 370;
	DICE_2.y = 370;
	DICE_2.w = 60;
	DICE_2.h = 60;





	DICE_3.x = 370;
	DICE_3.y = 370;
	DICE_3.w = 60;
	DICE_3.h = 60;




	DICE_4.x = 370;
	DICE_4.y = 370;
	DICE_4.w = 60;
	DICE_4.h = 60;


	DICE_5.x = 370;
	DICE_5.y = 370;
	DICE_5.w = 60;
	DICE_5.h = 60;



	DICE_6.x = 370;
	DICE_6.y = 370;
	DICE_6.w = 60;
	DICE_6.h = 60;



	///board

	destination.x = 50;
	destination.y = 50;
	destination.w = 700;
	destination.h = 700;





	//////////////////////////////////DICE////////////////////////////////////////////////////
	///////////////////////////////// RED  GOTIAN ////////////////////////////////////////////
	//RED 1
	
	
	RED_1.x = red_1_default_x;
	RED_1.y = red_1_default_y;
	RED_1.w = 35;
	RED_1.h = 35;
	//RED 2
	
	
	
	
	RED_2.x = red_2_default_x;
	RED_2.y = red_2_default_y;
	RED_2.w = 35;
	RED_2.h = 35;

	//RED 3

	
	
	
	RED_3.x = red_3_default_x;
	RED_3.y = red_3_default_y;
	RED_3.w = 35;
	RED_3.h = 35;


	//RED 4
	
	
	
	
	RED_4.x = red_4_default_x;
	RED_4.y = red_4_default_y;
	RED_4.w = 35;
	RED_4.h = 35;

	///////////////////////////////// RED  GOTIAN ////////////////////////////////////////////
	if(number_of_players > 3){
	///////////////////////////////// GREEN  GOTIAN ////////////////////////////////////////////
	//GREEN 1
	
	
	
	GREEN_1.x = green_1_default_x;
	GREEN_1.y = green_1_default_y;
	GREEN_1.w = 35;
	GREEN_1.h = 35;
	//GREEN 2
	
	
	
	GREEN_2.x = green_2_default_x;
	GREEN_2.y = green_2_default_y;
	GREEN_2.w = 35;
	GREEN_2.h = 35;

	//GREEN 3
	
	
	
	GREEN_3.x = green_3_default_x;
	GREEN_3.y = green_3_default_y;
	GREEN_3.w = 35;
	GREEN_3.h = 35;


	//GREEN 4
	
	
	
	GREEN_4.x = green_4_default_x;
	GREEN_4.y = green_4_default_y;
	GREEN_4.w = 35;
	GREEN_4.h = 35;

	///////////////////////////////// GREEN  GOTIAN ////////////////////////////////////////////
	}

	///////////////////////////////// YELLOW  GOTIAN ////////////////////////////////////////////
	
	//YELLOW 1

	YELLOW_1.x = yellow_1_default_x;
	YELLOW_1.y = yellow_1_default_y;
	YELLOW_1.w = 35;
	YELLOW_1.h = 35;
	
	//YELLOW 2
	YELLOW_2.x = yellow_2_default_x;
	YELLOW_2.y = yellow_2_default_y;
	YELLOW_2.w = 35;
	YELLOW_2.h = 35;

	
	//YELLOW 3
	YELLOW_3.x = yellow_3_default_x;
	YELLOW_3.y = yellow_3_default_y;
	YELLOW_3.w = 35;
	YELLOW_3.h = 35;


	
	//YELLOW 4
	YELLOW_4.x = yellow_4_default_x;
	YELLOW_4.y = yellow_4_default_y;
	YELLOW_4.w = 35;
	YELLOW_4.h = 35;




	///////////////////////////////// YELLOW  GOTIAN ////////////////////////////////////////////
	if(number_of_players>2){
	///////////////////////////////// BLUE  GOTIAN ////////////////////////////////////////////
	//BLUE 1
	//Load PNG texture
	
	
	BLUE_1.x = blue_1_default_x;
	BLUE_1.y = blue_1_default_y;
	BLUE_1.w = 35;
	BLUE_1.h = 35;
	//BLUE 2
	//Load PNG textur
	
	
	
	BLUE_2.x = blue_2_default_x;
	BLUE_2.y = blue_2_default_y;
	BLUE_2.w = 35;
	BLUE_2.h = 35;

	//BLUE 3
	//Load PNG texture
	
	
	
	BLUE_3.x = blue_3_default_x;
	BLUE_3.y = blue_3_default_y;
	BLUE_3.w = 35;
	BLUE_3.h = 35;


	//BLUE 4
	//Load PNG texture
	
	
	
	BLUE_4.x = blue_4_default_x;
	BLUE_4.y = blue_4_default_y;
	BLUE_4.w = 35;
	BLUE_4.h = 35;




	///////////////////////////////// BLUE  GOTIAN ////////////////////////////////////////////
	}
	dice_hit=false;

}




void *  dice_locking(void * arg){
	pthread_mutex_lock(&dice_lock);
	dice_value_play = ( rand() % 6 ) + 1;
	pthread_mutex_unlock(&dice_lock);
	pthread_exit(NULL);

}
void R_CHECK(SDL_Rect  RED_1){
	
	if(RED_1.x==red_all[0].x && RED_1.y==red_all[0].y){
		cout << "NOT CHECKING..." << endl;
	}else if((RED_1.x==red_all[8].x && RED_1.y==red_all[8].y) ||
			(RED_1.x==red_all[13].x && RED_1.y==red_all[13].y) ||
			(RED_1.x==red_all[21].x && RED_1.y==red_all[21].y) ||
			(RED_1.x==red_all[26].x && RED_1.y==red_all[26].y) ||
			(RED_1.x==red_all[34].x && RED_1.y==red_all[34].y) ||
			(RED_1.x==red_all[39].x && RED_1.y==red_all[39].y) ||
			(RED_1.x==red_all[47].x && RED_1.y==red_all[47].y)
		){
			cout << "NOT CHECKING..." << endl;

	}else

	if(RED_1.x == YELLOW_1.x && RED_1.y == YELLOW_1.y){
		
					YELLOW_1.x=yellow_1_default_x;
					YELLOW_1.y=yellow_1_default_y;
					R_hit=true;
		

				}else
				if(RED_1.x == YELLOW_2.x && RED_1.y == YELLOW_2.y){
		
					YELLOW_2.x=yellow_2_default_x;
					YELLOW_2.y=yellow_2_default_y;
					R_hit=true;

				}else
				if(RED_1.x == YELLOW_3.x && RED_1.y == YELLOW_3.y){
		
					YELLOW_3.x=yellow_3_default_x;
					YELLOW_3.y=yellow_3_default_y;
					R_hit=true;

				}else
				if(RED_1.x == YELLOW_4.x && RED_1.y == YELLOW_4.y){
		
					YELLOW_4.x=yellow_4_default_x;
					YELLOW_4.y=yellow_4_default_y;
					R_hit=true;
		

				}else
				if(RED_1.x == BLUE_1.x && RED_1.y == BLUE_1.y){
		
					BLUE_1.x=blue_1_default_x;
					BLUE_1.y=blue_1_default_y;
					R_hit=true;
		

				}else
				if(RED_1.x == BLUE_2.x && RED_1.y == BLUE_2.y){
		
					BLUE_2.x=blue_2_default_x;
					BLUE_2.y=blue_2_default_y;
					R_hit=true;

				}else
				if(RED_1.x == BLUE_3.x && RED_1.y == BLUE_3.y){
		
					BLUE_3.x=blue_3_default_x;
					BLUE_3.y=blue_3_default_y;
					R_hit=true;

				}else
				if(RED_1.x == BLUE_4.x && RED_1.y == BLUE_4.y){
		
					BLUE_4.x=blue_4_default_x;
					BLUE_4.y=blue_4_default_y;
					R_hit=true;
	
				}else
				if(RED_1.x == GREEN_1.x && RED_1.y == GREEN_1.y){
		
					GREEN_1.x=green_1_default_x;
					GREEN_1.y=green_1_default_y;
					R_hit=true;
		

				}else
				if(RED_1.x == GREEN_2.x && RED_1.y == GREEN_2.y){
		
					GREEN_2.x=green_2_default_x;
					GREEN_2.y=green_2_default_y;
					R_hit=true;

				}else
				if(RED_1.x == GREEN_3.x && RED_1.y == GREEN_3.y){
		
					GREEN_3.x=green_3_default_x;
					GREEN_3.y=green_3_default_y;
					R_hit=true;

				}else
				if(RED_1.x == GREEN_4.x && RED_1.y == GREEN_4.y){
		
					GREEN_4.x=green_4_default_x;
					GREEN_4.y=green_4_default_y;
					R_hit=true;
		

				}
}
void Y_CHECK(SDL_Rect  YELLOW_1){
	
	if(YELLOW_1.x==yellow_all[0].x && YELLOW_1.y==yellow_all[0].y){
		cout << "NOT CHECKING..." << endl;
	}else if((YELLOW_1.x==yellow_all[8].x && YELLOW_1.y==yellow_all[8].y) ||
			(YELLOW_1.x==yellow_all[13].x && YELLOW_1.y==yellow_all[13].y) ||
			(YELLOW_1.x==yellow_all[21].x && YELLOW_1.y==yellow_all[21].y) ||
			(YELLOW_1.x==yellow_all[26].x && YELLOW_1.y==yellow_all[26].y) ||
			(YELLOW_1.x==yellow_all[34].x && YELLOW_1.y==yellow_all[34].y) ||
			(YELLOW_1.x==yellow_all[39].x && YELLOW_1.y==yellow_all[39].y) ||
			(YELLOW_1.x==yellow_all[47].x && YELLOW_1.y==yellow_all[47].y)
		){
			cout << "NOT CHECKING..." << endl;

	}else

	if(YELLOW_1.x == RED_1.x && YELLOW_1.y == RED_1.y){
		
					RED_1.x=red_1_default_x;
					RED_1.y=red_1_default_y;
					Y_hit=true;
		

				}else
				if(YELLOW_1.x == RED_2.x && YELLOW_1.y == RED_2.y){
		
					RED_2.x=red_2_default_x;
					RED_2.y=red_2_default_y;
					Y_hit=true;

				}else
				if(YELLOW_1.x == RED_3.x && YELLOW_1.y == RED_3.y){
		
					RED_3.x=red_3_default_x;
					RED_3.y=red_3_default_y;
					Y_hit=true;

				}else
				if(YELLOW_1.x == RED_4.x && YELLOW_1.y == RED_4.y){
		
					RED_4.x=red_4_default_x;
					RED_4.y=red_4_default_y;
					Y_hit=true;
		

				}else
				if(YELLOW_1.x == BLUE_1.x && YELLOW_1.y == BLUE_1.y){
		
					BLUE_1.x=blue_1_default_x;
					BLUE_1.y=blue_1_default_y;
					Y_hit=true;
		

				}else
				if(YELLOW_1.x == BLUE_2.x && YELLOW_1.y == BLUE_2.y){
		
					BLUE_2.x=blue_2_default_x;
					BLUE_2.y=blue_2_default_y;
					Y_hit=true;

				}else
				if(YELLOW_1.x == BLUE_3.x && YELLOW_1.y == BLUE_3.y){
		
					BLUE_3.x=blue_3_default_x;
					BLUE_3.y=blue_3_default_y;
					Y_hit=true;

				}else
				if(YELLOW_1.x == BLUE_4.x && YELLOW_1.y == BLUE_4.y){
		
					BLUE_4.x=blue_4_default_x;
					BLUE_4.y=blue_4_default_y;
					Y_hit=true;
	
				}else
				if(YELLOW_1.x == GREEN_1.x && YELLOW_1.y == GREEN_1.y){
		
					GREEN_1.x=green_1_default_x;
					GREEN_1.y=green_1_default_y;
					Y_hit=true;
		

				}else
				if(YELLOW_1.x == GREEN_2.x && YELLOW_1.y == GREEN_2.y){
		
					GREEN_2.x=green_2_default_x;
					GREEN_2.y=green_2_default_y;
					Y_hit=true;

				}else
				if(YELLOW_1.x == GREEN_3.x && YELLOW_1.y == GREEN_3.y){
		
					GREEN_3.x=green_3_default_x;
					GREEN_3.y=green_3_default_y;
					Y_hit=true;

				}else
				if(YELLOW_1.x == GREEN_4.x && YELLOW_1.y == GREEN_4.y){
		
					GREEN_4.x=green_4_default_x;
					GREEN_4.y=green_4_default_y;
					Y_hit=true;
		

				}
}
void B_CHECK(SDL_Rect  BLUE_1){
	
	if(BLUE_1.x==blue_all[0].x && BLUE_1.y==blue_all[0].y){
		cout << "NOT CHECKING..." << endl;
	}else if((BLUE_1.x==blue_all[8].x && BLUE_1.y==blue_all[8].y) ||
			(BLUE_1.x==blue_all[13].x && BLUE_1.y==blue_all[13].y) ||
			(BLUE_1.x==blue_all[21].x && BLUE_1.y==blue_all[21].y) ||
			(BLUE_1.x==blue_all[26].x && BLUE_1.y==blue_all[26].y) ||
			(BLUE_1.x==blue_all[34].x && BLUE_1.y==blue_all[34].y) ||
			(BLUE_1.x==blue_all[39].x && BLUE_1.y==blue_all[39].y) ||
			(BLUE_1.x==blue_all[47].x && BLUE_1.y==blue_all[47].y)
		){
			cout << "NOT CHECKING..." << endl;

	}else

	if(BLUE_1.x == YELLOW_1.x && BLUE_1.y == YELLOW_1.y){
		
					YELLOW_1.x=yellow_1_default_x;
					YELLOW_1.y=yellow_1_default_y;
					B_hit=true;
		

				}else
				if(BLUE_1.x == YELLOW_2.x && BLUE_1.y == YELLOW_2.y){
		
					YELLOW_2.x=yellow_2_default_x;
					YELLOW_2.y=yellow_2_default_y;
					B_hit=true;

				}else
				if(BLUE_1.x == YELLOW_3.x && BLUE_1.y == YELLOW_3.y){
		
					YELLOW_3.x=yellow_3_default_x;
					YELLOW_3.y=yellow_3_default_y;
					B_hit=true;

				}else
				if(BLUE_1.x == YELLOW_4.x && BLUE_1.y == YELLOW_4.y){
		
					YELLOW_4.x=yellow_4_default_x;
					YELLOW_4.y=yellow_4_default_y;
					B_hit=true;
		

				}else
				if(BLUE_1.x == RED_1.x && BLUE_1.y == RED_1.y){
		
					BLUE_1.x=red_1_default_x;
					BLUE_1.y=red_1_default_y;
					B_hit=true;
		

				}else
				if(BLUE_1.x == RED_2.x && BLUE_1.y == RED_2.y){
		
					RED_2.x=red_2_default_x;
					RED_2.y=red_2_default_y;
					B_hit=true;

				}else
				if(BLUE_1.x == RED_3.x && BLUE_1.y == RED_3.y){
		
					RED_3.x=red_3_default_x;
					RED_3.y=red_3_default_y;
					B_hit=true;

				}else
				if(BLUE_1.x == RED_4.x && BLUE_1.y == RED_4.y){
		
					RED_4.x=red_4_default_x;
					RED_4.y=red_4_default_y;
					B_hit=true;
	
				}else
				if(BLUE_1.x == GREEN_1.x && BLUE_1.y == GREEN_1.y){
		
					GREEN_1.x=green_1_default_x;
					GREEN_1.y=green_1_default_y;
					B_hit=true;
		

				}else
				if(BLUE_1.x == GREEN_2.x && BLUE_1.y == GREEN_2.y){
		
					GREEN_2.x=green_2_default_x;
					GREEN_2.y=green_2_default_y;
					B_hit=true;

				}else
				if(BLUE_1.x == GREEN_3.x && BLUE_1.y == GREEN_3.y){
		
					GREEN_3.x=green_3_default_x;
					GREEN_3.y=green_3_default_y;
					B_hit=true;

				}else
				if(BLUE_1.x == GREEN_4.x && BLUE_1.y == GREEN_4.y){
		
					GREEN_4.x=green_4_default_x;
					GREEN_4.y=green_4_default_y;
					B_hit=true;
		

				}
}
void G_CHECK(SDL_Rect  GREEN_1){
	
	if(GREEN_1.x==green_all[0].x && GREEN_1.y==green_all[0].y){
		cout << "NOT CHECKING..." << endl;
	}else if((GREEN_1.x==green_all[8].x && GREEN_1.y==green_all[8].y) ||
			(GREEN_1.x==green_all[13].x && GREEN_1.y==green_all[13].y) ||
			(GREEN_1.x==green_all[21].x && GREEN_1.y==green_all[21].y) ||
			(GREEN_1.x==green_all[26].x && GREEN_1.y==green_all[26].y) ||
			(GREEN_1.x==green_all[34].x && GREEN_1.y==green_all[34].y) ||
			(GREEN_1.x==green_all[39].x && GREEN_1.y==green_all[39].y) ||
			(GREEN_1.x==green_all[47].x && GREEN_1.y==green_all[47].y)
		){
			cout << "NOT CHECKING..." << endl;

	}else

	if(GREEN_1.x == YELLOW_1.x && GREEN_1.y == YELLOW_1.y){
		
					YELLOW_1.x=yellow_1_default_x;
					YELLOW_1.y=yellow_1_default_y;
					G_hit=true;
		

				}else
				if(GREEN_1.x == YELLOW_2.x && GREEN_1.y == YELLOW_2.y){
		
					YELLOW_2.x=yellow_2_default_x;
					YELLOW_2.y=yellow_2_default_y;
					G_hit=true;

				}else
				if(GREEN_1.x == YELLOW_3.x && GREEN_1.y == YELLOW_3.y){
		
					YELLOW_3.x=yellow_3_default_x;
					YELLOW_3.y=yellow_3_default_y;
					G_hit=true;

				}else
				if(GREEN_1.x == YELLOW_4.x && GREEN_1.y == YELLOW_4.y){
		
					YELLOW_4.x=yellow_4_default_x;
					YELLOW_4.y=yellow_4_default_y;
					G_hit=true;
		

				}else
				if(GREEN_1.x == BLUE_1.x && GREEN_1.y == BLUE_1.y){
		
					BLUE_1.x=blue_1_default_x;
					BLUE_1.y=blue_1_default_y;
					G_hit=true;
		

				}else
				if(GREEN_1.x == BLUE_2.x && GREEN_1.y == BLUE_2.y){
		
					BLUE_2.x=blue_2_default_x;
					BLUE_2.y=blue_2_default_y;
					G_hit=true;

				}else
				if(GREEN_1.x == BLUE_3.x && GREEN_1.y == BLUE_3.y){
		
					BLUE_3.x=blue_3_default_x;
					BLUE_3.y=blue_3_default_y;
					G_hit=true;

				}else
				if(GREEN_1.x == BLUE_4.x && GREEN_1.y == BLUE_4.y){
		
					BLUE_4.x=blue_4_default_x;
					BLUE_4.y=blue_4_default_y;
					G_hit=true;
	
				}else
				if(GREEN_1.x == RED_1.x && GREEN_1.y == RED_1.y){
		
					GREEN_1.x=red_1_default_x;
					GREEN_1.y=red_1_default_y;
					G_hit=true;
		

				}else
				if(GREEN_1.x == RED_2.x && GREEN_1.y == RED_2.y){
		
					RED_2.x=red_2_default_x;
					RED_2.y=red_2_default_y;
					G_hit=true;

				}else
				if(GREEN_1.x == RED_3.x && GREEN_1.y == RED_3.y){
		
					RED_3.x=red_3_default_x;
					RED_3.y=red_3_default_y;
					G_hit=true;

				}else
				if(GREEN_1.x == RED_4.x && GREEN_1.y == RED_4.y){
		
					RED_4.x=red_4_default_x;
					RED_4.y=red_4_default_y;
					G_hit=true;
		

				}
}



	

void* RED_Board (void * arg){

	temp_pos_1_x = RED_1.x;
	temp_pos_1_y = RED_1.y;
	temp_pos_2_x = RED_2.x;
	temp_pos_2_y = RED_2.y;
	temp_pos_3_x = RED_3.x;
	temp_pos_3_y = RED_3.y;
	temp_pos_4_x = RED_4.x;
	temp_pos_4_y = RED_4.y;
	dice_hit=false;


	sem_wait(&lock1);
	six_count=0;

	cout << "RED HOUSE" << endl;

	bool red_turn=true;
	if(mega_close==true)
	while(red_turn){
		if (SDL_PollEvent(&sdl_event) != 0){
				if (sdl_event.type == SDL_QUIT)
				{
					isRunning = false;
					mega_close=false;
					break;	
				}
				else if (sdl_event.type == SDL_KEYDOWN){
					if(sdl_event.key.keysym.sym==SDLK_ESCAPE){
						red_turn = false;
						isRunning = false;
						mega_close=false;
						break;
					}else if (sdl_event.key.keysym.sym==SDLK_RETURN) {
						dice_hit=true;
					
					pthread_create(&Locker,NULL,dice_locking,NULL);
					
				
					if(dice_value_play==6){
						six_count++;
					}else{
						six_count=0;
					}
					}else if(Choose_token==true && sdl_event.key.keysym.sym==SDLK_1){
						
						R1=true;
						R2=false;
						R3=false;
						R4=false;
					}else if(Choose_token==true && sdl_event.key.keysym.sym==SDLK_2){
						
						R1=false;
						R2=true;
						R3=false;
						R4=false;
					}else if(Choose_token==true && sdl_event.key.keysym.sym==SDLK_3){
						
						R1=false;
						R2=false;
						R3=true;
						R4=false;
					}else if(Choose_token==true && sdl_event.key.keysym.sym==SDLK_4){
						
						R1=false;
						R2=false;
						R3=false;
						R4=true;
					}

				}
		}


		//Render texture to screen
			//Board
			SDL_RenderCopy(render, Texture, NULL, &destination);



			


			
			
			//RED	
			SDL_RenderCopy(render, Texture_RED_1, NULL, &RED_1);
			SDL_RenderCopy(render, Texture_RED_2, NULL, &RED_2);
			SDL_RenderCopy(render, Texture_RED_3, NULL, &RED_3);
			SDL_RenderCopy(render, Texture_RED_4, NULL, &RED_4);
			//BLUE
			
			if(number_of_players > 2){
			SDL_RenderCopy(render, Texture_BLUE_1, NULL, &BLUE_1);
			SDL_RenderCopy(render, Texture_BLUE_2, NULL, &BLUE_2);
			SDL_RenderCopy(render, Texture_BLUE_3, NULL, &BLUE_3);
			SDL_RenderCopy(render, Texture_BLUE_4, NULL, &BLUE_4);
			}
			//GREEN
			
			if(number_of_players > 3){
			SDL_RenderCopy(render, Texture_GREEN_1, NULL, &GREEN_1);
			SDL_RenderCopy(render, Texture_GREEN_2, NULL, &GREEN_2);
			SDL_RenderCopy(render, Texture_GREEN_3, NULL, &GREEN_3);
			SDL_RenderCopy(render, Texture_GREEN_4, NULL, &GREEN_4);
			}
			//YELLOW
			SDL_RenderCopy(render, Texture_YELLOW_1, NULL, &YELLOW_1);
			SDL_RenderCopy(render, Texture_YELLOW_2, NULL, &YELLOW_2);
			SDL_RenderCopy(render, Texture_YELLOW_3, NULL, &YELLOW_3);
			SDL_RenderCopy(render, Texture_YELLOW_4, NULL, &YELLOW_4);
			
			
			if(dice_hit==false && Choose_token==false){
				dice_value = ( rand() % 6 ) + 1;

				if(dice_value==1){
					SDL_RenderCopy(render, Texture_DICE_1, NULL, &DICE_1);
				}else if(dice_value==2){
					SDL_RenderCopy(render, Texture_DICE_2, NULL, &DICE_2);
				}else if(dice_value==3){
					SDL_RenderCopy(render, Texture_DICE_3, NULL, &DICE_3);
				}else if(dice_value==4){
					SDL_RenderCopy(render, Texture_DICE_4, NULL, &DICE_4);
				}else if(dice_value==5){
					SDL_RenderCopy(render, Texture_DICE_5, NULL, &DICE_5);
				}else if(dice_value==6){
					SDL_RenderCopy(render, Texture_DICE_6, NULL, &DICE_6);
				}
				SDL_RenderPresent(render);
				
				
			}else{
				

				if(dice_value_play==1){
					SDL_RenderCopy(render, Texture_DICE_1, NULL, &DICE_1);
				}else if(dice_value_play==2){
					SDL_RenderCopy(render, Texture_DICE_2, NULL, &DICE_2);
				}else if(dice_value_play==3){
					SDL_RenderCopy(render, Texture_DICE_3, NULL, &DICE_3);
				}else if(dice_value_play==4){
					SDL_RenderCopy(render, Texture_DICE_4, NULL, &DICE_4);
				}else if(dice_value_play==5){
					SDL_RenderCopy(render, Texture_DICE_5, NULL, &DICE_5);
				}else if(dice_value_play==6){
					SDL_RenderCopy(render, Texture_DICE_6, NULL, &DICE_6);
				}
				SDL_RenderPresent(render);
				
				dice_hit=false;
				

				if(dice_value_play!=6 &&  RED_1.x==red_1_default_x && RED_1.y == red_1_default_y && RED_2.x==red_2_default_x && RED_2.y == red_2_default_y && RED_3.x==red_3_default_x && RED_3.y == red_3_default_y && RED_4.x==red_4_default_x && RED_4.y == red_4_default_y){
					not_six_red++;
					sleep(1);
					break;
				}else if(
						( (RED_1.x==red_1_default_x && RED_1.y == red_1_default_y)  ||  (RED_1.x==red_all[56].x && RED_1.y == red_all[56].y)) && 
						( (RED_2.x==red_2_default_x && RED_2.y == red_2_default_y)  ||  (RED_2.x==red_all[56].x && RED_2.y == red_all[56].y)) &&
						( (RED_3.x==red_3_default_x && RED_3.y == red_3_default_y)  ||  (RED_3.x==red_all[56].x && RED_3.y == red_all[56].y)) &&
						( (RED_4.x==red_4_default_x && RED_4.y == red_4_default_y)  ||  (RED_4.x==red_all[56].x && RED_4.y == red_all[56].y)) &&
						(dice_value_play!=6)
						){
						    sleep(1);
							break;
						}else if(six_count>2){
							cout << "Turn expired." << endl;
							R1=false;
							R2=false;
							R3=false;
							R4=false;
							RED_1.x = temp_pos_1_x;
							RED_1.y = temp_pos_1_y;
							RED_2.x = temp_pos_2_x;
							RED_2.y = temp_pos_2_y;
							RED_3.x = temp_pos_3_x;
							RED_3.y = temp_pos_3_y;
							RED_4.x = temp_pos_4_x;
							RED_4.y = temp_pos_4_y;
							six_count=0;
							sleep(1);
							break;









						}else{
							not_six_red=0;
					Choose_token=true;
				}
			}

			///////////////////////////////conditions/////////////////////////////////


			if(R1==true){
				if(dice_value_play==6 && RED_1.x==red_1_default_x && RED_1.y==red_1_default_y){
					RED_1.x = red_all[0].x;
					RED_1.y = red_all[0].y;
					R1=false;
					Choose_token=false;
					

				}else if(dice_value_play==6 && RED_1.x!=red_1_default_x && RED_1.y!=red_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_1.x==red_all[i].x && RED_1.y==red_all[i].y){
							break;
						} 
						

					}
					if((i+6)<57){
						RED_1.x = red_all[i+6].x;
						RED_1.y = red_all[i+6].y;
						R1=false;
						Choose_token=false;
					}
					R_CHECK(RED_1);

				}else if(dice_value_play==5 && RED_1.x!=red_1_default_x && RED_1.y!=red_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_1.x==red_all[i].x && RED_1.y==red_all[i].y){
							break;
						} 

					}
					if((i+5)<57){
						RED_1.x = red_all[i+5].x;
						RED_1.y = red_all[i+5].y;
						R1=false;
						Choose_token=false;
						R_CHECK(RED_1);
						break;
					}

				}else if(dice_value_play==4 && RED_1.x!=red_1_default_x && RED_1.y!=red_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_1.x==red_all[i].x && RED_1.y==red_all[i].y){
							break;
						} 

					}
					if((i+4)<57){
						RED_1.x = red_all[i+4].x;
						RED_1.y = red_all[i+4].y;
						R1=false;
						Choose_token=false;
						R_CHECK(RED_1);
						break;
					}

				}else if(dice_value_play==3 && RED_1.x!=red_1_default_x && RED_1.y!=red_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_1.x==red_all[i].x && RED_1.y==red_all[i].y){
							break;
						} 

					}
					if((i+3)<57){
						RED_1.x = red_all[i+3].x;
						RED_1.y = red_all[i+3].y;
						R1=false;
						Choose_token=false;
						R_CHECK(RED_1);
						break;
					}

				}else if(dice_value_play==2 && RED_1.x!=red_1_default_x && RED_1.y!=red_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_1.x==red_all[i].x && RED_1.y==red_all[i].y){
							break;
						} 

					}
					if((i+2)<57){
						RED_1.x = red_all[i+2].x;
						RED_1.y = red_all[i+2].y;
						R1=false;
						Choose_token=false;
						R_CHECK(RED_1);
						break;
					}

				}else if(dice_value_play==1 && RED_1.x!=red_1_default_x && RED_1.y!=red_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_1.x==red_all[i].x && RED_1.y==red_all[i].y){
							break;
						} 

					}
					if((i+1)<57){
						RED_1.x = red_all[i+1].x;
						RED_1.y = red_all[i+1].y;
						R1=false;
						Choose_token=false;
						R_CHECK(RED_1);
						break;
					}

				}
				
			}else if(R2==true){
				if(dice_value_play==6 && RED_2.x==red_2_default_x && RED_2.y==red_2_default_y){
					RED_2.x = red_all[0].x;
					RED_2.y = red_all[0].y;
					R2=false;
					Choose_token=false;
					

				}else if(dice_value_play==6 && RED_2.x!=red_2_default_x && RED_2.y!=red_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_2.x==red_all[i].x && RED_2.y==red_all[i].y){
							break;
						} 
						

					}
					if((i+6)<57){
						RED_2.x = red_all[i+6].x;
						RED_2.y = red_all[i+6].y;
						R2=false;
						Choose_token=false;
					}
					R_CHECK(RED_2);

				}else if(dice_value_play==5 && RED_2.x!=red_2_default_x && RED_2.y!=red_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_2.x==red_all[i].x && RED_2.y==red_all[i].y){
							break;
						} 

					}
					if((i+5)<57){
						RED_2.x = red_all[i+5].x;
						RED_2.y = red_all[i+5].y;
						R2=false;
						Choose_token=false;
						R_CHECK(RED_2);
						break;
					}

				}else if(dice_value_play==4 && RED_2.x!=red_2_default_x && RED_2.y!=red_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_2.x==red_all[i].x && RED_2.y==red_all[i].y){
							break;
						} 

					}
					if((i+4)<57){
						RED_2.x = red_all[i+4].x;
						RED_2.y = red_all[i+4].y;
						R2=false;
						Choose_token=false;
						R_CHECK(RED_2);
						break;
					}

				}else if(dice_value_play==3 && RED_2.x!=red_2_default_x && RED_2.y!=red_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_2.x==red_all[i].x && RED_2.y==red_all[i].y){
							break;
						} 

					}
					if((i+3)<57){
						RED_2.x = red_all[i+3].x;
						RED_2.y = red_all[i+3].y;
						R2=false;
						Choose_token=false;
						R_CHECK(RED_2);
						break;
					}

				}else if(dice_value_play==2 && RED_2.x!=red_2_default_x && RED_2.y!=red_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_2.x==red_all[i].x && RED_2.y==red_all[i].y){
							break;
						} 

					}
					if((i+2)<57){
						RED_2.x = red_all[i+2].x;
						RED_2.y = red_all[i+2].y;
						R2=false;
						Choose_token=false;
						R_CHECK(RED_2);
						break;
					}

				}else if(dice_value_play==1 && RED_2.x!=red_2_default_x && RED_2.y!=red_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_2.x==red_all[i].x && RED_2.y==red_all[i].y){
							break;
						} 

					}
					if((i+1)<57){
						RED_2.x = red_all[i+1].x;
						RED_2.y = red_all[i+1].y;
						R2=false;
						Choose_token=false;
						R_CHECK(RED_2);
						break;
					}

				}

			}else if(R3==true){
				if(dice_value_play==6 && RED_3.x==red_3_default_x && RED_3.y==red_3_default_y){
					RED_3.x = red_all[0].x;
					RED_3.y = red_all[0].y;
					R3=false;
					Choose_token=false;
					

				}else if(dice_value_play==6 && RED_3.x!=red_3_default_x && RED_3.y!=red_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_3.x==red_all[i].x && RED_3.y==red_all[i].y){
							break;
						} 
						

					}
					if((i+6)<57){
						RED_3.x = red_all[i+6].x;
						RED_3.y = red_all[i+6].y;
						R3=false;
						Choose_token=false;
					}
					R_CHECK(RED_3);

				}else if(dice_value_play==5 && RED_3.x!=red_3_default_x && RED_3.y!=red_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_3.x==red_all[i].x && RED_3.y==red_all[i].y){
							break;
						} 

					}
					if((i+5)<57){
						RED_3.x = red_all[i+5].x;
						RED_3.y = red_all[i+5].y;
						R3=false;
						Choose_token=false;
						R_CHECK(RED_3);
						break;
					}

				}else if(dice_value_play==4 && RED_3.x!=red_3_default_x && RED_3.y!=red_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_3.x==red_all[i].x && RED_3.y==red_all[i].y){
							break;
						} 

					}
					if((i+4)<57){
						RED_3.x = red_all[i+4].x;
						RED_3.y = red_all[i+4].y;
						R3=false;
						Choose_token=false;
						R_CHECK(RED_3);
						break;
					}

				}else if(dice_value_play==3 && RED_3.x!=red_3_default_x && RED_3.y!=red_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_3.x==red_all[i].x && RED_3.y==red_all[i].y){
							break;
						} 

					}
					if((i+3)<57){
						RED_3.x = red_all[i+3].x;
						RED_3.y = red_all[i+3].y;
						R3=false;
						Choose_token=false;
						R_CHECK(RED_3);
						break;
					}

				}else if(dice_value_play==2 && RED_3.x!=red_3_default_x && RED_3.y!=red_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_3.x==red_all[i].x && RED_3.y==red_all[i].y){
							break;
						} 

					}
					if((i+2)<57){
						RED_3.x = red_all[i+2].x;
						RED_3.y = red_all[i+2].y;
						R3=false;
						Choose_token=false;
						R_CHECK(RED_3);
						break;
					}

				}else if(dice_value_play==1 && RED_3.x!=red_3_default_x && RED_3.y!=red_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_3.x==red_all[i].x && RED_3.y==red_all[i].y){
							break;
						} 

					}
					if((i+1)<57){
						RED_3.x = red_all[i+1].x;
						RED_3.y = red_all[i+1].y;
						R3=false;
						Choose_token=false;
						R_CHECK(RED_3);
						break;
					}

				}
				
			}else if(R4==true){
				if(dice_value_play==6 && RED_4.x==red_4_default_x && RED_4.y==red_4_default_y){
					RED_4.x = red_all[0].x;
					RED_4.y = red_all[0].y;
					R4=false;
					Choose_token=false;
					

				}else if(dice_value_play==6 && RED_4.x!=red_4_default_x && RED_4.y!=red_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_4.x==red_all[i].x && RED_4.y==red_all[i].y){
							break;
						} 
						

					}
					if((i+6)<57){
						RED_4.x = red_all[i+6].x;
						RED_4.y = red_all[i+6].y;
						R4=false;
						Choose_token=false;
					}
					R_CHECK(RED_4);

				}else if(dice_value_play==5 && RED_4.x!=red_4_default_x && RED_4.y!=red_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_4.x==red_all[i].x && RED_4.y==red_all[i].y){
							break;
						} 

					}
					if((i+5)<57){
						RED_4.x = red_all[i+5].x;
						RED_4.y = red_all[i+5].y;
						R4=false;
						Choose_token=false;
						R_CHECK(RED_4);
						break;
					}

				}else if(dice_value_play==4 && RED_4.x!=red_4_default_x && RED_4.y!=red_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_4.x==red_all[i].x && RED_4.y==red_all[i].y){
							break;
						} 

					}
					if((i+4)<57){
						RED_4.x = red_all[i+4].x;
						RED_4.y = red_all[i+4].y;
						R4=false;
						Choose_token=false;
						R_CHECK(RED_4);
						break;
					}

				}else if(dice_value_play==3 && RED_4.x!=red_4_default_x && RED_4.y!=red_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_4.x==red_all[i].x && RED_4.y==red_all[i].y){
							break;
						} 

					}
					if((i+3)<57){
						RED_4.x = red_all[i+3].x;
						RED_4.y = red_all[i+3].y;
						R4=false;
						Choose_token=false;
						R_CHECK(RED_4);
						break;
					}

				}else if(dice_value_play==2 && RED_4.x!=red_4_default_x && RED_4.y!=red_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_4.x==red_all[i].x && RED_4.y==red_all[i].y){
							break;
						} 

					}
					if((i+2)<57){
						RED_4.x = red_all[i+2].x;
						RED_4.y = red_all[i+2].y;
						R4=false;
						Choose_token=false;
						R_CHECK(RED_4);
						break;
					}

				}else if(dice_value_play==1 && RED_4.x!=red_4_default_x && RED_4.y!=red_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(RED_4.x==red_all[i].x && RED_4.y==red_all[i].y){
							break;
						} 

					}
					if((i+1)<57){
						RED_4.x = red_all[i+1].x;
						RED_4.y = red_all[i+1].y;
						R4=false;
						Choose_token=false;
						R_CHECK(RED_4);
						break;
					}

				}
			
	
			}
	}
	
   sem_post(&lock1);
	
	

	SDL_RenderPresent(render);

	pthread_exit(NULL);
}
	
void* GREEN_Board (void * arg){



	temp_pos_1_x = GREEN_1.x;
	temp_pos_1_y = GREEN_1.y;
	temp_pos_2_x = GREEN_2.x;
	temp_pos_2_y = GREEN_2.y;
	temp_pos_3_x = GREEN_3.x;
	temp_pos_3_y = GREEN_3.y;
	temp_pos_4_x = GREEN_4.x;
	temp_pos_4_y = GREEN_4.y;
	dice_hit=false;




	sem_wait(&lock1);
	six_count=0;
	

	cout << "GREEN HOUSE" << endl;

	bool green_turn=true;
	if(mega_close==true)
	while(green_turn){
		dice_value = ( rand() % 6 ) + 1;
		if (SDL_PollEvent(&sdl_event) != 0){
				if (sdl_event.type == SDL_QUIT)
				{
					isRunning = false;
					mega_close=false;
					break;
					
				}
				else if (sdl_event.type == SDL_KEYDOWN){
					if(sdl_event.key.keysym.sym==SDLK_ESCAPE){
						green_turn = false;
						isRunning = false;
						mega_close=false;
						break;
					}else if (sdl_event.key.keysym.sym==SDLK_RETURN) {
						dice_hit=true;
					
					pthread_create(&Locker,NULL,dice_locking,NULL);
									
					if(dice_value_play==6){
						six_count++;
					}else{
						six_count=0;
					}

					}else if(Choose_token==true && sdl_event.key.keysym.sym==SDLK_1){
						
						G1=true;
						G2=false;
						G3=false;
						G4=false;
					}else if(Choose_token==true && sdl_event.key.keysym.sym==SDLK_2){
						
						G1=false;
						G2=true;
						G3=false;
						G4=false;
					}else if(Choose_token==true && sdl_event.key.keysym.sym==SDLK_3){
						
						G1=false;
						G2=false;
						G3=true;
						G4=false;
					}else if(Choose_token==true && sdl_event.key.keysym.sym==SDLK_4){
						
						G1=false;
						G2=false;
						G3=false;
						G4=true;
					}
				}
				
		}



		//Render texture to screen
			//Board
			SDL_RenderCopy(render, Texture, NULL, &destination);



			


			
			
			//RED	
			SDL_RenderCopy(render, Texture_RED_1, NULL, &RED_1);
			SDL_RenderCopy(render, Texture_RED_2, NULL, &RED_2);
			SDL_RenderCopy(render, Texture_RED_3, NULL, &RED_3);
			SDL_RenderCopy(render, Texture_RED_4, NULL, &RED_4);
			//BLUE
			
			if(number_of_players > 2){
			SDL_RenderCopy(render, Texture_BLUE_1, NULL, &BLUE_1);
			SDL_RenderCopy(render, Texture_BLUE_2, NULL, &BLUE_2);
			SDL_RenderCopy(render, Texture_BLUE_3, NULL, &BLUE_3);
			SDL_RenderCopy(render, Texture_BLUE_4, NULL, &BLUE_4);
			}
			//GREEN
			
			if(number_of_players > 3){
			SDL_RenderCopy(render, Texture_GREEN_1, NULL, &GREEN_1);
			SDL_RenderCopy(render, Texture_GREEN_2, NULL, &GREEN_2);
			SDL_RenderCopy(render, Texture_GREEN_3, NULL, &GREEN_3);
			SDL_RenderCopy(render, Texture_GREEN_4, NULL, &GREEN_4);
			}
			//YELLOW
			SDL_RenderCopy(render, Texture_YELLOW_1, NULL, &YELLOW_1);
			SDL_RenderCopy(render, Texture_YELLOW_2, NULL, &YELLOW_2);
			SDL_RenderCopy(render, Texture_YELLOW_3, NULL, &YELLOW_3);
			SDL_RenderCopy(render, Texture_YELLOW_4, NULL, &YELLOW_4);
			if(dice_hit==false && Choose_token==false){
				if(dice_value==1){
					SDL_RenderCopy(render, Texture_DICE_1, NULL, &DICE_1);
				}else if(dice_value==2){
					SDL_RenderCopy(render, Texture_DICE_2, NULL, &DICE_2);
				}else if(dice_value==3){
					SDL_RenderCopy(render, Texture_DICE_3, NULL, &DICE_3);
				}else if(dice_value==4){
					SDL_RenderCopy(render, Texture_DICE_4, NULL, &DICE_4);
				}else if(dice_value==5){
					SDL_RenderCopy(render, Texture_DICE_5, NULL, &DICE_5);
				}else if(dice_value==6){
					SDL_RenderCopy(render, Texture_DICE_6, NULL, &DICE_6);
				}
				SDL_RenderPresent(render);
			}else{
				
				if(dice_value_play==1){
					SDL_RenderCopy(render, Texture_DICE_1, NULL, &DICE_1);
				}else if(dice_value_play==2){
					SDL_RenderCopy(render, Texture_DICE_2, NULL, &DICE_2);
				}else if(dice_value_play==3){
					SDL_RenderCopy(render, Texture_DICE_3, NULL, &DICE_3);
				}else if(dice_value_play==4){
					SDL_RenderCopy(render, Texture_DICE_4, NULL, &DICE_4);
				}else if(dice_value_play==5){
					SDL_RenderCopy(render, Texture_DICE_5, NULL, &DICE_5);
				}else if(dice_value_play==6){
					SDL_RenderCopy(render, Texture_DICE_6, NULL, &DICE_6);
				}
				SDL_RenderPresent(render);
				dice_hit=false;
				

				if(dice_value_play!=6 &&  GREEN_1.x==green_1_default_x && GREEN_1.y == green_1_default_y && GREEN_2.x==green_2_default_x && GREEN_2.y == green_2_default_y && GREEN_3.x==green_3_default_x && GREEN_3.y == green_3_default_y && GREEN_4.x==green_4_default_x && GREEN_4.y == green_4_default_y){
					not_six_green++;
					sleep(1);
					break;
				}else if(
						( (GREEN_1.x==green_1_default_x && GREEN_1.y == green_1_default_y)  ||  (GREEN_1.x==green_all[56].x && GREEN_1.y == green_all[56].y)) && 
						( (GREEN_2.x==green_2_default_x && GREEN_2.y == green_2_default_y)  ||  (GREEN_2.x==green_all[56].x && GREEN_2.y == green_all[56].y)) &&
						( (GREEN_3.x==green_3_default_x && GREEN_3.y == green_3_default_y)  ||  (GREEN_3.x==green_all[56].x && GREEN_3.y == green_all[56].y)) &&
						( (GREEN_4.x==green_4_default_x && GREEN_4.y == green_4_default_y)  ||  (GREEN_4.x==green_all[56].x && GREEN_4.y == green_all[56].y)) &&
						(dice_value_play!=6)
						){
						    sleep(1);
							break;
						}else if(six_count>2){
							cout << "Turn expired." << endl;
							G1=false;
							G2=false;
							G3=false;
							G4=false;
							GREEN_1.x = temp_pos_1_x;
							GREEN_1.y = temp_pos_1_y;
							GREEN_2.x = temp_pos_2_x;
							GREEN_2.y = temp_pos_2_y;
							GREEN_3.x = temp_pos_3_x;
							GREEN_3.y = temp_pos_3_y;
							GREEN_4.x = temp_pos_4_x;
							GREEN_4.y = temp_pos_4_y;
							six_count=0;
							sleep(1);
							break;









						}else{
						not_six_green=0;
					Choose_token=true;
				}
			}

			///////////////////////////////conditions/////////////////////////////////


			if(G1==true){
				if(dice_value_play==6 && GREEN_1.x==green_1_default_x && GREEN_1.y==green_1_default_y){
					GREEN_1.x = green_all[0].x;
					GREEN_1.y = green_all[0].y;
					G1=false;
					Choose_token=false;
					

				}else if(dice_value_play==6 && GREEN_1.x!=green_1_default_x && GREEN_1.y!=green_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_1.x==green_all[i].x && GREEN_1.y==green_all[i].y){
							break;
						} 
						

					}
					if((i+6)<57){
						GREEN_1.x = green_all[i+6].x;
						GREEN_1.y = green_all[i+6].y;
						G1=false;
						Choose_token=false;
					}
					G_CHECK(GREEN_1);

				}else if(dice_value_play==5 && GREEN_1.x!=green_1_default_x && GREEN_1.y!=green_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_1.x==green_all[i].x && GREEN_1.y==green_all[i].y){
							break;
						} 

					}
					if((i+5)<57){
						GREEN_1.x = green_all[i+5].x;
						GREEN_1.y = green_all[i+5].y;
						G1=false;
						Choose_token=false;
						G_CHECK(GREEN_1);
						break;
					}

				}else if(dice_value_play==4 && GREEN_1.x!=green_1_default_x && GREEN_1.y!=green_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_1.x==green_all[i].x && GREEN_1.y==green_all[i].y){
							break;
						} 

					}
					if((i+4)<57){
						GREEN_1.x = green_all[i+4].x;
						GREEN_1.y = green_all[i+4].y;
						G1=false;
						Choose_token=false;
					G_CHECK(GREEN_1);
						break;
					}

				}else if(dice_value_play==3 && GREEN_1.x!=green_1_default_x && GREEN_1.y!=green_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_1.x==green_all[i].x && GREEN_1.y==green_all[i].y){
							break;
						} 

					}
					if((i+3)<57){
						GREEN_1.x = green_all[i+3].x;
						GREEN_1.y = green_all[i+3].y;
						G1=false;
						Choose_token=false;
						G_CHECK(GREEN_1);
						break;
					}

				}else if(dice_value_play==2 && GREEN_1.x!=green_1_default_x && GREEN_1.y!=green_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_1.x==green_all[i].x && GREEN_1.y==green_all[i].y){
							break;
						} 

					}
					if((i+2)<57){
						GREEN_1.x = green_all[i+2].x;
						GREEN_1.y = green_all[i+2].y;
						G1=false;
						Choose_token=false;
						G_CHECK(GREEN_1);
						break;
					}

				}else if(dice_value_play==1 && GREEN_1.x!=green_1_default_x && GREEN_1.y!=green_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_1.x==green_all[i].x && GREEN_1.y==green_all[i].y){
							break;
						} 

					}
					if((i+1)<57){
						GREEN_1.x = green_all[i+1].x;
						GREEN_1.y = green_all[i+1].y;
						G1=false;
						Choose_token=false;
						G_CHECK(GREEN_1);
						break;
					}

				}
				
			}else if(G2==true){
				if(dice_value_play==6 && GREEN_2.x==green_2_default_x && GREEN_2.y==green_2_default_y){
					GREEN_2.x = green_all[0].x;
					GREEN_2.y = green_all[0].y;
					G2=false;
					Choose_token=false;
					

				}else if(dice_value_play==6 && GREEN_2.x!=green_2_default_x && GREEN_2.y!=green_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_2.x==green_all[i].x && GREEN_2.y==green_all[i].y){
							break;
						} 
						

					}
					if((i+6)<57){
						GREEN_2.x = green_all[i+6].x;
						GREEN_2.y = green_all[i+6].y;
						G2=false;
						Choose_token=false;
					}
					G_CHECK(GREEN_2);

				}else if(dice_value_play==5 && GREEN_2.x!=green_2_default_x && GREEN_2.y!=green_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_2.x==green_all[i].x && GREEN_2.y==green_all[i].y){
							break;
						} 

					}
					if((i+5)<57){
						GREEN_2.x = green_all[i+5].x;
						GREEN_2.y = green_all[i+5].y;
						G2=false;
						Choose_token=false;
							G_CHECK(GREEN_2);
						break;
					}

				}else if(dice_value_play==4 && GREEN_2.x!=green_2_default_x && GREEN_2.y!=green_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_2.x==green_all[i].x && GREEN_2.y==green_all[i].y){
							break;
						} 

					}
					if((i+4)<57){
						GREEN_2.x = green_all[i+4].x;
						GREEN_2.y = green_all[i+4].y;
						G2=false;
						Choose_token=false;
							G_CHECK(GREEN_2);
						break;
					}

				}else if(dice_value_play==3 && GREEN_2.x!=green_2_default_x && GREEN_2.y!=green_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_2.x==green_all[i].x && GREEN_2.y==green_all[i].y){
							break;
						} 

					}
					if((i+3)<57){
						GREEN_2.x = green_all[i+3].x;
						GREEN_2.y = green_all[i+3].y;
						G2=false;
						Choose_token=false;
							G_CHECK(GREEN_2);
						break;
					}

				}else if(dice_value_play==2 && GREEN_2.x!=green_2_default_x && GREEN_2.y!=green_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_2.x==green_all[i].x && GREEN_2.y==green_all[i].y){
							break;
						} 

					}
					if((i+2)<57){
						GREEN_2.x = green_all[i+2].x;
						GREEN_2.y = green_all[i+2].y;
						G2=false;
						Choose_token=false;
							G_CHECK(GREEN_2);
						break;
					}

				}else if(dice_value_play==1 && GREEN_2.x!=green_2_default_x && GREEN_2.y!=green_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_2.x==green_all[i].x && GREEN_2.y==green_all[i].y){
							break;
						} 

					}
					if((i+1)<57){
						GREEN_2.x = green_all[i+1].x;
						GREEN_2.y = green_all[i+1].y;
						G2=false;
						Choose_token=false;
							G_CHECK(GREEN_2);
						break;
					}

				}
				
			}else if(G3==true){
				if(dice_value_play==6 && GREEN_3.x==green_3_default_x && GREEN_3.y==green_3_default_y){
					GREEN_3.x = green_all[0].x;
					GREEN_3.y = green_all[0].y;
					G3=false;
					Choose_token=false;
					

				}else if(dice_value_play==6 && GREEN_3.x!=green_3_default_x && GREEN_3.y!=green_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_3.x==green_all[i].x && GREEN_3.y==green_all[i].y){
							break;
						} 
						

					}
					if((i+6)<57){
						GREEN_3.x = green_all[i+6].x;
						GREEN_3.y = green_all[i+6].y;
						G3=false;
						Choose_token=false;
					}
					G_CHECK(GREEN_3);

				}else if(dice_value_play==5 && GREEN_3.x!=green_3_default_x && GREEN_3.y!=green_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_3.x==green_all[i].x && GREEN_3.y==green_all[i].y){
							break;
						} 

					}
					if((i+5)<57){
						GREEN_3.x = green_all[i+5].x;
						GREEN_3.y = green_all[i+5].y;
						G3=false;
						Choose_token=false;
						G_CHECK(GREEN_3);
						break;
					}

				}else if(dice_value_play==4 && GREEN_3.x!=green_3_default_x && GREEN_3.y!=green_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_3.x==green_all[i].x && GREEN_3.y==green_all[i].y){
							break;
						} 

					}
					if((i+4)<57){
						GREEN_3.x = green_all[i+4].x;
						GREEN_3.y = green_all[i+4].y;
						G3=false;
						Choose_token=false;
						G_CHECK(GREEN_3);
						break;
					}

				}else if(dice_value_play==3 && GREEN_3.x!=green_3_default_x && GREEN_3.y!=green_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_3.x==green_all[i].x && GREEN_3.y==green_all[i].y){
							break;
						} 

					}
					if((i+3)<57){
						GREEN_3.x = green_all[i+3].x;
						GREEN_3.y = green_all[i+3].y;
						G3=false;
						Choose_token=false;
						G_CHECK(GREEN_3);
						break;
					}

				}else if(dice_value_play==2 && GREEN_3.x!=green_3_default_x && GREEN_3.y!=green_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_3.x==green_all[i].x && GREEN_3.y==green_all[i].y){
							break;
						} 

					}
					if((i+2)<57){
						GREEN_3.x = green_all[i+2].x;
						GREEN_3.y = green_all[i+2].y;
						G3=false;
						Choose_token=false;
						G_CHECK(GREEN_3);
						break;
					}

				}else if(dice_value_play==1 && GREEN_3.x!=green_3_default_x && GREEN_3.y!=green_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_3.x==green_all[i].x && GREEN_3.y==green_all[i].y){
							break;
						} 

					}
					if((i+1)<57){
						GREEN_3.x = green_all[i+1].x;
						GREEN_3.y = green_all[i+1].y;
						G3=false;
						Choose_token=false;
						G_CHECK(GREEN_3);
						break;
					}

				}
				
			}else if(G4==true){
				if(dice_value_play==6 && GREEN_4.x==green_4_default_x && GREEN_4.y==green_4_default_y){
					GREEN_4.x = green_all[0].x;
					GREEN_4.y = green_all[0].y;
					G4=false;
					Choose_token=false;
					

				}else if(dice_value_play==6 && GREEN_4.x!=green_4_default_x && GREEN_4.y!=green_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_4.x==green_all[i].x && GREEN_4.y==green_all[i].y){
							break;
						} 
						

					}
					if((i+6)<57){
						GREEN_4.x = green_all[i+6].x;
						GREEN_4.y = green_all[i+6].y;
						G4=false;
						Choose_token=false;
					}
					G_CHECK(GREEN_4);

				}else if(dice_value_play==5 && GREEN_4.x!=green_4_default_x && GREEN_4.y!=green_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_4.x==green_all[i].x && GREEN_4.y==green_all[i].y){
							break;
						} 

					}
					if((i+5)<57){
						GREEN_4.x = green_all[i+5].x;
						GREEN_4.y = green_all[i+5].y;
						G4=false;
						Choose_token=false;
						G_CHECK(GREEN_4);
						break;
					}

				}else if(dice_value_play==4 && GREEN_4.x!=green_4_default_x && GREEN_4.y!=green_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_4.x==green_all[i].x && GREEN_4.y==green_all[i].y){
							break;
						} 

					}
					if((i+4)<57){
						GREEN_4.x = green_all[i+4].x;
						GREEN_4.y = green_all[i+4].y;
						G4=false;
						Choose_token=false;
						G_CHECK(GREEN_4);
						break;
					}

				}else if(dice_value_play==3 && GREEN_4.x!=green_4_default_x && GREEN_4.y!=green_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_4.x==green_all[i].x && GREEN_4.y==green_all[i].y){
							break;
						} 

					}
					if((i+3)<57){
						GREEN_4.x = green_all[i+3].x;
						GREEN_4.y = green_all[i+3].y;
						G4=false;
						Choose_token=false;
						G_CHECK(GREEN_4);
						break;
					}

				}else if(dice_value_play==2 && GREEN_4.x!=green_4_default_x && GREEN_4.y!=green_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_4.x==green_all[i].x && GREEN_4.y==green_all[i].y){
							break;
						} 

					}
					if((i+2)<57){
						GREEN_4.x = green_all[i+2].x;
						GREEN_4.y = green_all[i+2].y;
						G4=false;
						Choose_token=false;
						G_CHECK(GREEN_4);
						break;
					}

				}else if(dice_value_play==1 && GREEN_4.x!=green_4_default_x && GREEN_4.y!=green_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(GREEN_4.x==green_all[i].x && GREEN_4.y==green_all[i].y){
							break;
						} 

					}
					if((i+1)<57){
						GREEN_4.x = green_all[i+1].x;
						GREEN_4.y = green_all[i+1].y;
						G4=false;
						Choose_token=false;
						G_CHECK(GREEN_4);
						break;
					}

				}
				
			}
		}
		sem_post(&lock1);
		SDL_RenderPresent(render);
		pthread_exit(NULL);

	
	
	
	}



void* YELLOW_Board (void * arg){
	temp_pos_1_x = YELLOW_1.x;
	temp_pos_1_y = YELLOW_1.y;
	temp_pos_2_x = YELLOW_2.x;
	temp_pos_2_y = YELLOW_2.y;
	temp_pos_3_x = YELLOW_3.x;
	temp_pos_3_y = YELLOW_3.y;
	temp_pos_4_x = YELLOW_4.x;
	temp_pos_4_y = YELLOW_4.y;
	dice_hit=false;
	sem_wait(&lock1);

	six_count=0;


	cout << "YELLOW HOUSE" << endl;
	bool yellow_turn=true;
	if(mega_close==true)
	while(yellow_turn){
		dice_value = ( rand() % 6 ) + 1;
		if (SDL_PollEvent(&sdl_event) != 0){
				if (sdl_event.type == SDL_QUIT)
				{
					isRunning = false;
					mega_close=false;
					break;
				}
				else if (sdl_event.type == SDL_KEYDOWN){
					if(sdl_event.key.keysym.sym==SDLK_ESCAPE){
						yellow_turn = false;
						isRunning = false;
						mega_close=false;
						break;
					}else if (sdl_event.key.keysym.sym==SDLK_RETURN) {
						dice_hit=true;
					
					pthread_create(&Locker,NULL,dice_locking,NULL);
					
							
					if(dice_value_play==6){
						six_count++;
					}else{
						six_count=0;
					}
			
					}else if(Choose_token==true && sdl_event.key.keysym.sym==SDLK_1){
						
						Y1=true;
						Y2=false;
						Y3=false;
						Y4=false;
					}else if(Choose_token==true && sdl_event.key.keysym.sym==SDLK_2){
						
						Y1=false;
						Y2=true;
						Y3=false;
						Y4=false;
					}else if(Choose_token==true && sdl_event.key.keysym.sym==SDLK_3){
						
						Y1=false;
						Y2=false;
						Y3=true;
						Y4=false;
					}else if(Choose_token==true && sdl_event.key.keysym.sym==SDLK_4){
						
						Y1=false;
						Y2=false;
						Y3=false;
						Y4=true;
					}
				}				
				
		}



		//Render texture to screen
			//Board
			SDL_RenderCopy(render, Texture, NULL, &destination);



			


			
			
			//RED	
			SDL_RenderCopy(render, Texture_RED_1, NULL, &RED_1);
			SDL_RenderCopy(render, Texture_RED_2, NULL, &RED_2);
			SDL_RenderCopy(render, Texture_RED_3, NULL, &RED_3);
			SDL_RenderCopy(render, Texture_RED_4, NULL, &RED_4);
			//BLUE
			
			if(number_of_players > 2){
			SDL_RenderCopy(render, Texture_BLUE_1, NULL, &BLUE_1);
			SDL_RenderCopy(render, Texture_BLUE_2, NULL, &BLUE_2);
			SDL_RenderCopy(render, Texture_BLUE_3, NULL, &BLUE_3);
			SDL_RenderCopy(render, Texture_BLUE_4, NULL, &BLUE_4);
			}
			//GREEN
			
			if(number_of_players > 3){
			SDL_RenderCopy(render, Texture_GREEN_1, NULL, &GREEN_1);
			SDL_RenderCopy(render, Texture_GREEN_2, NULL, &GREEN_2);
			SDL_RenderCopy(render, Texture_GREEN_3, NULL, &GREEN_3);
			SDL_RenderCopy(render, Texture_GREEN_4, NULL, &GREEN_4);
			}
			//YELLOW
			SDL_RenderCopy(render, Texture_YELLOW_1, NULL, &YELLOW_1);
			SDL_RenderCopy(render, Texture_YELLOW_2, NULL, &YELLOW_2);
			SDL_RenderCopy(render, Texture_YELLOW_3, NULL, &YELLOW_3);
			SDL_RenderCopy(render, Texture_YELLOW_4, NULL, &YELLOW_4);
			if(dice_hit==false && Choose_token==false){
				if(dice_value==1){
					SDL_RenderCopy(render, Texture_DICE_1, NULL, &DICE_1);
				}else if(dice_value==2){
					SDL_RenderCopy(render, Texture_DICE_2, NULL, &DICE_2);
				}else if(dice_value==3){
					SDL_RenderCopy(render, Texture_DICE_3, NULL, &DICE_3);
				}else if(dice_value==4){
					SDL_RenderCopy(render, Texture_DICE_4, NULL, &DICE_4);
				}else if(dice_value==5){
					SDL_RenderCopy(render, Texture_DICE_5, NULL, &DICE_5);
				}else if(dice_value==6){
					SDL_RenderCopy(render, Texture_DICE_6, NULL, &DICE_6);
				}
				SDL_RenderPresent(render);
			}else{
				
				if(dice_value_play==1){
					SDL_RenderCopy(render, Texture_DICE_1, NULL, &DICE_1);
				}else if(dice_value_play==2){
					SDL_RenderCopy(render, Texture_DICE_2, NULL, &DICE_2);
				}else if(dice_value_play==3){
					SDL_RenderCopy(render, Texture_DICE_3, NULL, &DICE_3);
				}else if(dice_value_play==4){
					SDL_RenderCopy(render, Texture_DICE_4, NULL, &DICE_4);
				}else if(dice_value_play==5){
					SDL_RenderCopy(render, Texture_DICE_5, NULL, &DICE_5);
				}else if(dice_value_play==6){
					SDL_RenderCopy(render, Texture_DICE_6, NULL, &DICE_6);
				}
				SDL_RenderPresent(render);
				dice_hit=false;
				

				if(dice_value_play!=6 &&  YELLOW_1.x==yellow_1_default_x && YELLOW_1.y == yellow_1_default_y && YELLOW_2.x==yellow_2_default_x && YELLOW_2.y == yellow_2_default_y && YELLOW_3.x==yellow_3_default_x && YELLOW_3.y == yellow_3_default_y && YELLOW_4.x==yellow_4_default_x && YELLOW_4.y == yellow_4_default_y){
					not_six_yellow++;
					sleep(1);
					break;
				}else if(
						( (YELLOW_1.x==yellow_1_default_x && YELLOW_1.y == yellow_1_default_y)  ||  (YELLOW_1.x==yellow_all[56].x && YELLOW_1.y == yellow_all[56].y)) && 
						( (YELLOW_2.x==yellow_2_default_x && YELLOW_2.y == yellow_2_default_y)  ||  (YELLOW_2.x==yellow_all[56].x && YELLOW_2.y == yellow_all[56].y)) &&
						( (YELLOW_3.x==yellow_3_default_x && YELLOW_3.y == yellow_3_default_y)  ||  (YELLOW_3.x==yellow_all[56].x && YELLOW_3.y == yellow_all[56].y)) &&
						( (YELLOW_4.x==yellow_4_default_x && YELLOW_4.y == yellow_4_default_y)  ||  (YELLOW_4.x==yellow_all[56].x && YELLOW_4.y == yellow_all[56].y)) &&
						(dice_value_play!=6)
						){
						    sleep(1);
							break;
						}else if(six_count>2){
							cout << "Turn expired." << endl;
							Y1=false;
							Y2=false;
							Y3=false;
							Y4=false;
							YELLOW_1.x = temp_pos_1_x;
							YELLOW_1.y = temp_pos_1_y;
							YELLOW_2.x = temp_pos_2_x;
							YELLOW_2.y = temp_pos_2_y;
							YELLOW_3.x = temp_pos_3_x;
							YELLOW_3.y = temp_pos_3_y;
							YELLOW_4.x = temp_pos_4_x;
							YELLOW_4.y = temp_pos_4_y;
							six_count=0;
							sleep(1);
							break;









						}else{
							not_six_green=0;
					Choose_token=true;
				}
			}

			///////////////////////////////conditions/////////////////////////////////


			if(Y1==true){
				if(dice_value_play==6 && YELLOW_1.x==yellow_1_default_x && YELLOW_1.y==yellow_1_default_y){
					YELLOW_1.x = yellow_all[0].x;
					YELLOW_1.y = yellow_all[0].y;
					Y1=false;
					Choose_token=false;
					

				}else if(dice_value_play==6 && YELLOW_1.x!=yellow_1_default_x && YELLOW_1.y!=yellow_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_1.x==yellow_all[i].x && YELLOW_1.y==yellow_all[i].y){
							break;
						} 
						

					}
					if((i+6)<57){
						YELLOW_1.x = yellow_all[i+6].x;
						YELLOW_1.y = yellow_all[i+6].y;
						Y1=false;
						Choose_token=false;
					}
					Y_CHECK(YELLOW_1);

				}else if(dice_value_play==5 && YELLOW_1.x!=yellow_1_default_x && YELLOW_1.y!=yellow_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_1.x==yellow_all[i].x && YELLOW_1.y==yellow_all[i].y){
							break;
						} 

					}
					if((i+5)<57){
						YELLOW_1.x = yellow_all[i+5].x;
						YELLOW_1.y = yellow_all[i+5].y;
						Y1=false;
						Choose_token=false;
						Y_CHECK(YELLOW_1);
						break;
					}

				}else if(dice_value_play==4 && YELLOW_1.x!=yellow_1_default_x && YELLOW_1.y!=yellow_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_1.x==yellow_all[i].x && YELLOW_1.y==yellow_all[i].y){
							break;
						} 

					}
					if((i+4)<57){
						YELLOW_1.x = yellow_all[i+4].x;
						YELLOW_1.y = yellow_all[i+4].y;
						Y1=false;
						Choose_token=false;
						Y_CHECK(YELLOW_1);
						break;
					}

				}else if(dice_value_play==3 && YELLOW_1.x!=yellow_1_default_x && YELLOW_1.y!=yellow_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_1.x==yellow_all[i].x && YELLOW_1.y==yellow_all[i].y){
							break;
						} 

					}
					if((i+3)<57){
						YELLOW_1.x = yellow_all[i+3].x;
						YELLOW_1.y = yellow_all[i+3].y;
						Y1=false;
						Choose_token=false;
						Y_CHECK(YELLOW_1);
						break;
					}

				}else if(dice_value_play==2 && YELLOW_1.x!=yellow_1_default_x && YELLOW_1.y!=yellow_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_1.x==yellow_all[i].x && YELLOW_1.y==yellow_all[i].y){
							break;
						} 

					}
					if((i+2)<57){
						YELLOW_1.x = yellow_all[i+2].x;
						YELLOW_1.y = yellow_all[i+2].y;
						Y1=false;
						Choose_token=false;
						Y_CHECK(YELLOW_1);
						break;
					}

				}else if(dice_value_play==1 && YELLOW_1.x!=yellow_1_default_x && YELLOW_1.y!=yellow_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_1.x==yellow_all[i].x && YELLOW_1.y==yellow_all[i].y){
							break;
						} 

					}
					if((i+1)<57){
						YELLOW_1.x = yellow_all[i+1].x;
						YELLOW_1.y = yellow_all[i+1].y;
						Y1=false;
						Choose_token=false;
						Y_CHECK(YELLOW_1);
						break;
					}

				}
				
			}else if(Y2==true){
				if(dice_value_play==6 && YELLOW_2.x==yellow_2_default_x && YELLOW_2.y==yellow_2_default_y){
					YELLOW_2.x = yellow_all[0].x;
					YELLOW_2.y = yellow_all[0].y;
					Y2=false;
					Choose_token=false;
					

				}else if(dice_value_play==6 && YELLOW_2.x!=yellow_2_default_x && YELLOW_2.y!=yellow_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_2.x==yellow_all[i].x && YELLOW_2.y==yellow_all[i].y){
							break;
						} 
						

					}
					if((i+6)<57){
						YELLOW_2.x = yellow_all[i+6].x;
						YELLOW_2.y = yellow_all[i+6].y;
						Y2=false;
						Choose_token=false;
					}
					Y_CHECK(YELLOW_2);

				}else if(dice_value_play==5 && YELLOW_2.x!=yellow_2_default_x && YELLOW_2.y!=yellow_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_2.x==yellow_all[i].x && YELLOW_2.y==yellow_all[i].y){
							break;
						} 

					}
					if((i+5)<57){
						YELLOW_2.x = yellow_all[i+5].x;
						YELLOW_2.y = yellow_all[i+5].y;
						Y2=false;
						Choose_token=false;
						Y_CHECK(YELLOW_2);
						break;
					}

				}else if(dice_value_play==4 && YELLOW_2.x!=yellow_2_default_x && YELLOW_2.y!=yellow_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_2.x==yellow_all[i].x && YELLOW_2.y==yellow_all[i].y){
							break;
						} 

					}
					if((i+4)<57){
						YELLOW_2.x = yellow_all[i+4].x;
						YELLOW_2.y = yellow_all[i+4].y;
						Y2=false;
						Choose_token=false;
						Y_CHECK(YELLOW_2);
						break;
					}

				}else if(dice_value_play==3 && YELLOW_2.x!=yellow_2_default_x && YELLOW_2.y!=yellow_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_2.x==yellow_all[i].x && YELLOW_2.y==yellow_all[i].y){
							break;
						} 

					}
					if((i+3)<57){
						YELLOW_2.x = yellow_all[i+3].x;
						YELLOW_2.y = yellow_all[i+3].y;
						Y2=false;
						Choose_token=false;
						Y_CHECK(YELLOW_2);
						break;
					}

				}else if(dice_value_play==2 && YELLOW_2.x!=yellow_2_default_x && YELLOW_2.y!=yellow_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_2.x==yellow_all[i].x && YELLOW_2.y==yellow_all[i].y){
							break;
						} 

					}
					if((i+2)<57){
						YELLOW_2.x = yellow_all[i+2].x;
						YELLOW_2.y = yellow_all[i+2].y;
						Y2=false;
						Choose_token=false;
						Y_CHECK(YELLOW_2);
						break;
					}

				}else if(dice_value_play==1 && YELLOW_2.x!=yellow_2_default_x && YELLOW_2.y!=yellow_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_2.x==yellow_all[i].x && YELLOW_2.y==yellow_all[i].y){
							break;
						} 

					}
					if((i+1)<57){
						YELLOW_2.x = yellow_all[i+1].x;
						YELLOW_2.y = yellow_all[i+1].y;
						Y2=false;
						Choose_token=false;
						Y_CHECK(YELLOW_2);
						break;
					}

				}
				
			}else if(Y3==true){
				if(dice_value_play==6 && YELLOW_3.x==yellow_3_default_x && YELLOW_3.y==yellow_3_default_y){
					YELLOW_3.x = yellow_all[0].x;
					YELLOW_3.y = yellow_all[0].y;
					Y3=false;
					Choose_token=false;
					

				}else if(dice_value_play==6 && YELLOW_3.x!=yellow_3_default_x && YELLOW_3.y!=yellow_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_3.x==yellow_all[i].x && YELLOW_3.y==yellow_all[i].y){
							break;
						} 
						

					}
					if((i+6)<57){
						YELLOW_3.x = yellow_all[i+6].x;
						YELLOW_3.y = yellow_all[i+6].y;
						Y3=false;
						Choose_token=false;
					}
					Y_CHECK(YELLOW_3);

				}else if(dice_value_play==5 && YELLOW_3.x!=yellow_3_default_x && YELLOW_3.y!=yellow_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_3.x==yellow_all[i].x && YELLOW_3.y==yellow_all[i].y){
							break;
						} 

					}
					if((i+5)<57){
						YELLOW_3.x = yellow_all[i+5].x;
						YELLOW_3.y = yellow_all[i+5].y;
						Y3=false;
						Choose_token=false;
						Y_CHECK(YELLOW_3);
						break;
					}

				}else if(dice_value_play==4 && YELLOW_3.x!=yellow_3_default_x && YELLOW_3.y!=yellow_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_3.x==yellow_all[i].x && YELLOW_3.y==yellow_all[i].y){
							break;
						} 

					}
					if((i+4)<57){
						YELLOW_3.x = yellow_all[i+4].x;
						YELLOW_3.y = yellow_all[i+4].y;
						Y3=false;
						Choose_token=false;
						Y_CHECK(YELLOW_3);
						break;
					}

				}else if(dice_value_play==3 && YELLOW_3.x!=yellow_3_default_x && YELLOW_3.y!=yellow_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_3.x==yellow_all[i].x && YELLOW_3.y==yellow_all[i].y){
							break;
						} 

					}
					if((i+3)<57){
						YELLOW_3.x = yellow_all[i+3].x;
						YELLOW_3.y = yellow_all[i+3].y;
						Y3=false;
						Choose_token=false;
						Y_CHECK(YELLOW_3);
						break;
					}

				}else if(dice_value_play==2 && YELLOW_3.x!=yellow_3_default_x && YELLOW_3.y!=yellow_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_3.x==yellow_all[i].x && YELLOW_3.y==yellow_all[i].y){
							break;
						} 

					}
					if((i+2)<57){
						YELLOW_3.x = yellow_all[i+2].x;
						YELLOW_3.y = yellow_all[i+2].y;
						Y3=false;
						Choose_token=false;
						Y_CHECK(YELLOW_3);
						break;
					}

				}else if(dice_value_play==1 && YELLOW_3.x!=yellow_3_default_x && YELLOW_3.y!=yellow_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_3.x==yellow_all[i].x && YELLOW_3.y==yellow_all[i].y){
							break;
						} 

					}
					if((i+1)<57){
						YELLOW_3.x = yellow_all[i+1].x;
						YELLOW_3.y = yellow_all[i+1].y;
						Y3=false;
						Choose_token=false;
						Y_CHECK(YELLOW_3);
						break;
					}

				}
				
			}else if(Y4==true){
				if(dice_value_play==6 && YELLOW_4.x==yellow_4_default_x && YELLOW_4.y==yellow_4_default_y){
					YELLOW_4.x = yellow_all[0].x;
					YELLOW_4.y = yellow_all[0].y;
					Y4=false;
					Choose_token=false;
					

				}else if(dice_value_play==6 && YELLOW_4.x!=yellow_4_default_x && YELLOW_4.y!=yellow_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_4.x==yellow_all[i].x && YELLOW_4.y==yellow_all[i].y){
							break;
						} 
						

					}
					if((i+6)<57){
						YELLOW_4.x = yellow_all[i+6].x;
						YELLOW_4.y = yellow_all[i+6].y;
						Y4=false;
						Choose_token=false;
					}
					Y_CHECK(YELLOW_4);

				}else if(dice_value_play==5 && YELLOW_4.x!=yellow_4_default_x && YELLOW_4.y!=yellow_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_4.x==yellow_all[i].x && YELLOW_4.y==yellow_all[i].y){
							break;
						} 

					}
					if((i+5)<57){
						YELLOW_4.x = yellow_all[i+5].x;
						YELLOW_4.y = yellow_all[i+5].y;
						Y4=false;
						Choose_token=false;
						Y_CHECK(YELLOW_4);
						break;
					}

				}else if(dice_value_play==4 && YELLOW_4.x!=yellow_4_default_x && YELLOW_4.y!=yellow_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_4.x==yellow_all[i].x && YELLOW_4.y==yellow_all[i].y){
							break;
						} 

					}
					if((i+4)<57){
						YELLOW_4.x = yellow_all[i+4].x;
						YELLOW_4.y = yellow_all[i+4].y;
						Y4=false;
						Choose_token=false;
						Y_CHECK(YELLOW_4);
						break;
					}

				}else if(dice_value_play==3 && YELLOW_4.x!=yellow_4_default_x && YELLOW_4.y!=yellow_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_4.x==yellow_all[i].x && YELLOW_4.y==yellow_all[i].y){
							break;
						} 

					}
					if((i+3)<57){
						YELLOW_4.x = yellow_all[i+3].x;
						YELLOW_4.y = yellow_all[i+3].y;
						Y4=false;
						Choose_token=false;
						Y_CHECK(YELLOW_4);
						break;
					}

				}else if(dice_value_play==2 && YELLOW_4.x!=yellow_4_default_x && YELLOW_4.y!=yellow_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_4.x==yellow_all[i].x && YELLOW_4.y==yellow_all[i].y){
							break;
						} 

					}
					if((i+2)<57){
						YELLOW_4.x = yellow_all[i+2].x;
						YELLOW_4.y = yellow_all[i+2].y;
						Y4=false;
						Choose_token=false;
						Y_CHECK(YELLOW_4);
						break;
					}

				}else if(dice_value_play==1 && YELLOW_4.x!=yellow_4_default_x && YELLOW_4.y!=yellow_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(YELLOW_4.x==yellow_all[i].x && YELLOW_4.y==yellow_all[i].y){
							break;
						} 

					}
					if((i+1)<57){
						YELLOW_4.x = yellow_all[i+1].x;
						YELLOW_4.y = yellow_all[i+1].y;
						Y4=false;
						Choose_token=false;
						Y_CHECK(YELLOW_4);
						break;
					}

				}
				
			}
		}
		sem_post(&lock1);
		SDL_RenderPresent(render);
	pthread_exit(NULL);

}
void* BLUE_Board (void * arg){

	temp_pos_1_x = BLUE_1.x;
	temp_pos_1_y = BLUE_1.y;
	temp_pos_2_x = BLUE_2.x;
	temp_pos_2_y = BLUE_2.y;
	temp_pos_3_x = BLUE_3.x;
	temp_pos_3_y = BLUE_3.y;
	temp_pos_4_x = BLUE_4.x;
	temp_pos_4_y = BLUE_4.y;
	dice_hit=false;

	sem_wait(&lock1);


	six_count=0;
	

	cout << "BLUE HOUSE" << endl;
	bool blue_turn=true;
	if(mega_close==true)
	while(blue_turn){
		
		dice_value = ( rand() % 6 ) + 1;
		if (SDL_PollEvent(&sdl_event) != 0){
				if (sdl_event.type == SDL_QUIT)
				{
					isRunning = false;
					mega_close=false;
					break;
				}
				else if (sdl_event.type == SDL_KEYDOWN){
					if(sdl_event.key.keysym.sym==SDLK_ESCAPE){
						blue_turn = false;
						isRunning = false;
						mega_close=false;
						break;
					}else if (sdl_event.key.keysym.sym==SDLK_RETURN) {
						dice_hit=true;
					pthread_create(&Locker,NULL,dice_locking,NULL);
					if(dice_value_play==6){
						six_count++;
					}else{
						six_count=0;
					}

					}else if(Choose_token==true && sdl_event.key.keysym.sym==SDLK_1){
						
						B1=true;
						B2=false;
						B3=false;
						B4=false;
					}else if(Choose_token==true && sdl_event.key.keysym.sym==SDLK_2){
						
						B1=false;
						B2=true;
						B3=false;
						B4=false;
					}else if(Choose_token==true && sdl_event.key.keysym.sym==SDLK_3){
						
						B1=false;
						B2=false;
						B3=true;
						B4=false;
					}else if(Choose_token==true && sdl_event.key.keysym.sym==SDLK_4){
						
						B1=false;
						B2=false;
						B3=false;
						B4=true;
					}
				}
				
				
		}


		//Render texture to screen
			//Board
			SDL_RenderCopy(render, Texture, NULL, &destination);



			


			
			
			//RED	
			SDL_RenderCopy(render, Texture_RED_1, NULL, &RED_1);
			SDL_RenderCopy(render, Texture_RED_2, NULL, &RED_2);
			SDL_RenderCopy(render, Texture_RED_3, NULL, &RED_3);
			SDL_RenderCopy(render, Texture_RED_4, NULL, &RED_4);
			//BLUE
			
			if(number_of_players > 2){
			SDL_RenderCopy(render, Texture_BLUE_1, NULL, &BLUE_1);
			SDL_RenderCopy(render, Texture_BLUE_2, NULL, &BLUE_2);
			SDL_RenderCopy(render, Texture_BLUE_3, NULL, &BLUE_3);
			SDL_RenderCopy(render, Texture_BLUE_4, NULL, &BLUE_4);
			}
			//GREEN
			
			if(number_of_players > 3){
			SDL_RenderCopy(render, Texture_GREEN_1, NULL, &GREEN_1);
			SDL_RenderCopy(render, Texture_GREEN_2, NULL, &GREEN_2);
			SDL_RenderCopy(render, Texture_GREEN_3, NULL, &GREEN_3);
			SDL_RenderCopy(render, Texture_GREEN_4, NULL, &GREEN_4);
			}
			//YELLOW
			SDL_RenderCopy(render, Texture_YELLOW_1, NULL, &YELLOW_1);
			SDL_RenderCopy(render, Texture_YELLOW_2, NULL, &YELLOW_2);
			SDL_RenderCopy(render, Texture_YELLOW_3, NULL, &YELLOW_3);
			SDL_RenderCopy(render, Texture_YELLOW_4, NULL, &YELLOW_4);
			if(dice_hit==false && Choose_token==false){
				if(dice_value==1){
					SDL_RenderCopy(render, Texture_DICE_1, NULL, &DICE_1);
				}else if(dice_value==2){
					SDL_RenderCopy(render, Texture_DICE_2, NULL, &DICE_2);
				}else if(dice_value==3){
					SDL_RenderCopy(render, Texture_DICE_3, NULL, &DICE_3);
				}else if(dice_value==4){
					SDL_RenderCopy(render, Texture_DICE_4, NULL, &DICE_4);
				}else if(dice_value==5){
					SDL_RenderCopy(render, Texture_DICE_5, NULL, &DICE_5);
				}else if(dice_value==6){
					SDL_RenderCopy(render, Texture_DICE_6, NULL, &DICE_6);
				}
				SDL_RenderPresent(render);
			}else{
				
				if(dice_value_play==1){
					SDL_RenderCopy(render, Texture_DICE_1, NULL, &DICE_1);
				}else if(dice_value_play==2){
					SDL_RenderCopy(render, Texture_DICE_2, NULL, &DICE_2);
				}else if(dice_value_play==3){
					SDL_RenderCopy(render, Texture_DICE_3, NULL, &DICE_3);
				}else if(dice_value_play==4){
					SDL_RenderCopy(render, Texture_DICE_4, NULL, &DICE_4);
				}else if(dice_value_play==5){
					SDL_RenderCopy(render, Texture_DICE_5, NULL, &DICE_5);
				}else if(dice_value_play==6){
					SDL_RenderCopy(render, Texture_DICE_6, NULL, &DICE_6);
				}
				SDL_RenderPresent(render);
				dice_hit=false;
				

				if(dice_value_play!=6 &&  BLUE_1.x==blue_1_default_x && BLUE_1.y == blue_1_default_y && BLUE_2.x==blue_2_default_x && BLUE_2.y == blue_2_default_y && BLUE_3.x==blue_3_default_x && BLUE_3.y == blue_3_default_y && BLUE_4.x==blue_4_default_x && BLUE_4.y == blue_4_default_y){
					not_six_blue++;
					sleep(1);
					break;
				}else if(
						( (BLUE_1.x==blue_1_default_x && BLUE_1.y == blue_1_default_y)  ||  (BLUE_1.x==blue_all[56].x && BLUE_1.y == blue_all[56].y)) && 
						( (BLUE_2.x==blue_2_default_x && BLUE_2.y == blue_2_default_y)  ||  (BLUE_2.x==blue_all[56].x && BLUE_2.y == blue_all[56].y)) &&
						( (BLUE_3.x==blue_3_default_x && BLUE_3.y == blue_3_default_y)  ||  (BLUE_3.x==blue_all[56].x && BLUE_3.y == blue_all[56].y)) &&
						( (BLUE_4.x==blue_4_default_x && BLUE_4.y == blue_4_default_y)  ||  (BLUE_4.x==blue_all[56].x && BLUE_4.y == blue_all[56].y)) &&
						(dice_value_play!=6)
						){
						    sleep(1);
							break;
						}else if(six_count>2){
							cout << "Turn expired." << endl;
							B1=false;
							B2=false;
							B3=false;
							B4=false;
							BLUE_1.x = temp_pos_1_x;
							BLUE_1.y = temp_pos_1_y;
							BLUE_2.x = temp_pos_2_x;
							BLUE_2.y = temp_pos_2_y;
							BLUE_3.x = temp_pos_3_x;
							BLUE_3.y = temp_pos_3_y;
							BLUE_4.x = temp_pos_4_x;
							BLUE_4.y = temp_pos_4_y;
							six_count=0;
							sleep(1);
							break;









						}else{
							not_six_blue=0;
					Choose_token=true;
				}
			}

			///////////////////////////////conditions/////////////////////////////////


			if(B1==true){
				if(dice_value_play==6 && BLUE_1.x==blue_1_default_x && BLUE_1.y==blue_1_default_y){
					BLUE_1.x = blue_all[0].x;
					BLUE_1.y = blue_all[0].y;
					B1=false;
					Choose_token=false;
					

				}else if(dice_value_play==6 && BLUE_1.x!=blue_1_default_x && BLUE_1.y!=blue_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_1.x==blue_all[i].x && BLUE_1.y==blue_all[i].y){
							break;
						} 
						

					}
					if((i+6)<57){
						BLUE_1.x = blue_all[i+6].x;
						BLUE_1.y = blue_all[i+6].y;
						B1=false;
						Choose_token=false;
					}
					B_CHECK(BLUE_1);

				}else if(dice_value_play==5 && BLUE_1.x!=blue_1_default_x && BLUE_1.y!=blue_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_1.x==blue_all[i].x && BLUE_1.y==blue_all[i].y){
							break;
						} 

					}
					if((i+5)<57){
						BLUE_1.x = blue_all[i+5].x;
						BLUE_1.y = blue_all[i+5].y;
						B1=false;
						Choose_token=false;
						B_CHECK(BLUE_1);
						break;
					}

				}else if(dice_value_play==4 && BLUE_1.x!=blue_1_default_x && BLUE_1.y!=blue_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_1.x==blue_all[i].x && BLUE_1.y==blue_all[i].y){
							break;
						} 

					}
					if((i+4)<57){
						BLUE_1.x = blue_all[i+4].x;
						BLUE_1.y = blue_all[i+4].y;
						B1=false;
						Choose_token=false;
						B_CHECK(BLUE_1);
						break;
					}

				}else if(dice_value_play==3 && BLUE_1.x!=blue_1_default_x && BLUE_1.y!=blue_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_1.x==blue_all[i].x && BLUE_1.y==blue_all[i].y){
							break;
						} 

					}
					if((i+3)<57){
						BLUE_1.x = blue_all[i+3].x;
						BLUE_1.y = blue_all[i+3].y;
						B1=false;
						Choose_token=false;
						B_CHECK(BLUE_1);
						break;
					}

				}else if(dice_value_play==2 && BLUE_1.x!=blue_1_default_x && BLUE_1.y!=blue_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_1.x==blue_all[i].x && BLUE_1.y==blue_all[i].y){
							break;
						} 

					}
					if((i+2)<57){
						BLUE_1.x = blue_all[i+2].x;
						BLUE_1.y = blue_all[i+2].y;
						B1=false;
						Choose_token=false;
						B_CHECK(BLUE_1);
						break;
					}

				}else if(dice_value_play==1 && BLUE_1.x!=blue_1_default_x && BLUE_1.y!=blue_1_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_1.x==blue_all[i].x && BLUE_1.y==blue_all[i].y){
							break;
						} 

					}
					if((i+1)<57){
						BLUE_1.x = blue_all[i+1].x;
						BLUE_1.y = blue_all[i+1].y;
						B1=false;
						Choose_token=false;
						B_CHECK(BLUE_1);
						break;
					}

				}
				
			}else if(B2==true){
				if(dice_value_play==6 && BLUE_2.x==blue_2_default_x && BLUE_2.y==blue_2_default_y){
					BLUE_2.x = blue_all[0].x;
					BLUE_2.y = blue_all[0].y;
					B2=false;
					Choose_token=false;
					

				}else if(dice_value_play==6 && BLUE_2.x!=blue_2_default_x && BLUE_2.y!=blue_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_2.x==blue_all[i].x && BLUE_2.y==blue_all[i].y){
							break;
						} 
						

					}
					if((i+6)<57){
						BLUE_2.x = blue_all[i+6].x;
						BLUE_2.y = blue_all[i+6].y;
						B2=false;
						Choose_token=false;
					}
					B_CHECK(BLUE_2);

				}else if(dice_value_play==5 && BLUE_2.x!=blue_2_default_x && BLUE_2.y!=blue_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_2.x==blue_all[i].x && BLUE_2.y==blue_all[i].y){
							break;
						} 

					}
					if((i+5)<57){
						BLUE_2.x = blue_all[i+5].x;
						BLUE_2.y = blue_all[i+5].y;
						B2=false;
						Choose_token=false;
						B_CHECK(BLUE_2);
						break;
					}

				}else if(dice_value_play==4 && BLUE_2.x!=blue_2_default_x && BLUE_2.y!=blue_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_2.x==blue_all[i].x && BLUE_2.y==blue_all[i].y){
							break;
						} 

					}
					if((i+4)<57){
						BLUE_2.x = blue_all[i+4].x;
						BLUE_2.y = blue_all[i+4].y;
						B2=false;
						Choose_token=false;
						B_CHECK(BLUE_2);
						break;
					}

				}else if(dice_value_play==3 && BLUE_2.x!=blue_2_default_x && BLUE_2.y!=blue_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_2.x==blue_all[i].x && BLUE_2.y==blue_all[i].y){
							break;
						} 

					}
					if((i+3)<57){
						BLUE_2.x = blue_all[i+3].x;
						BLUE_2.y = blue_all[i+3].y;
						B2=false;
						Choose_token=false;
						B_CHECK(BLUE_2);
						break;
					}

				}else if(dice_value_play==2 && BLUE_2.x!=blue_2_default_x && BLUE_2.y!=blue_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_2.x==blue_all[i].x && BLUE_2.y==blue_all[i].y){
							break;
						} 

					}
					if((i+2)<57){
						BLUE_2.x = blue_all[i+2].x;
						BLUE_2.y = blue_all[i+2].y;
						B2=false;
						Choose_token=false;
						B_CHECK(BLUE_2);
						break;
					}

				}else if(dice_value_play==1 && BLUE_2.x!=blue_2_default_x && BLUE_2.y!=blue_2_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_2.x==blue_all[i].x && BLUE_2.y==blue_all[i].y){
							break;
						} 

					}
					if((i+1)<57){
						BLUE_2.x = blue_all[i+1].x;
						BLUE_2.y = blue_all[i+1].y;
						B2=false;
						Choose_token=false;
						B_CHECK(BLUE_2);
						break;
					}

				}
				
			}else if(B3==true){
				if(dice_value_play==6 && BLUE_3.x==blue_3_default_x && BLUE_3.y==blue_3_default_y){
					BLUE_3.x = blue_all[0].x;
					BLUE_3.y = blue_all[0].y;
					B3=false;
					Choose_token=false;
					

				}else if(dice_value_play==6 && BLUE_3.x!=blue_3_default_x && BLUE_3.y!=blue_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_3.x==blue_all[i].x && BLUE_3.y==blue_all[i].y){
							break;
						} 
						

					}
					if((i+6)<57){
						BLUE_3.x = blue_all[i+6].x;
						BLUE_3.y = blue_all[i+6].y;
						B3=false;
						Choose_token=false;
					}
					B_CHECK(BLUE_3);

				}else if(dice_value_play==5 && BLUE_3.x!=blue_3_default_x && BLUE_3.y!=blue_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_3.x==blue_all[i].x && BLUE_3.y==blue_all[i].y){
							break;
						} 

					}
					if((i+5)<57){
						BLUE_3.x = blue_all[i+5].x;
						BLUE_3.y = blue_all[i+5].y;
						B3=false;
						Choose_token=false;
						B_CHECK(BLUE_3);
						break;
					}

				}else if(dice_value_play==4 && BLUE_3.x!=blue_3_default_x && BLUE_3.y!=blue_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_3.x==blue_all[i].x && BLUE_3.y==blue_all[i].y){
							break;
						} 

					}
					if((i+4)<57){
						BLUE_3.x = blue_all[i+4].x;
						BLUE_3.y = blue_all[i+4].y;
						B3=false;
						Choose_token=false;
						B_CHECK(BLUE_3);
						break;
					}

				}else if(dice_value_play==3 && BLUE_3.x!=blue_3_default_x && BLUE_3.y!=blue_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_3.x==blue_all[i].x && BLUE_3.y==blue_all[i].y){
							break;
						} 

					}
					if((i+3)<57){
						BLUE_3.x = blue_all[i+3].x;
						BLUE_3.y = blue_all[i+3].y;
						B3=false;
						Choose_token=false;
						B_CHECK(BLUE_3);
						break;
					}

				}else if(dice_value_play==2 && BLUE_3.x!=blue_3_default_x && BLUE_3.y!=blue_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_3.x==blue_all[i].x && BLUE_3.y==blue_all[i].y){
							break;
						} 

					}
					if((i+2)<57){
						BLUE_3.x = blue_all[i+2].x;
						BLUE_3.y = blue_all[i+2].y;
						B3=false;
						Choose_token=false;
						B_CHECK(BLUE_3);
						break;
					}

				}else if(dice_value_play==1 && BLUE_3.x!=blue_3_default_x && BLUE_3.y!=blue_3_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_3.x==blue_all[i].x && BLUE_3.y==blue_all[i].y){
							break;
						} 

					}
					if((i+1)<57){
						BLUE_3.x = blue_all[i+1].x;
						BLUE_3.y = blue_all[i+1].y;
						B3=false;
						Choose_token=false;
						B_CHECK(BLUE_3);
						break;
					}

				}
				
			}else if(B4==true){
				if(dice_value_play==6 && BLUE_4.x==blue_4_default_x && BLUE_4.y==blue_4_default_y){
					BLUE_4.x = blue_all[0].x;
					BLUE_4.y = blue_all[0].y;
					B4=false;
					Choose_token=false;
					

				}else if(dice_value_play==6 && BLUE_4.x!=blue_4_default_x && BLUE_4.y!=blue_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_4.x==blue_all[i].x && BLUE_4.y==blue_all[i].y){
							break;
						} 
						

					}
					if((i+6)<57){
						BLUE_4.x = blue_all[i+6].x;
						BLUE_4.y = blue_all[i+6].y;
						B4=false;
						Choose_token=false;
					}
					B_CHECK(BLUE_4);

				}else if(dice_value_play==5 && BLUE_4.x!=blue_4_default_x && BLUE_4.y!=blue_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_4.x==blue_all[i].x && BLUE_4.y==blue_all[i].y){
							break;
						} 

					}
					if((i+5)<57){
						BLUE_4.x = blue_all[i+5].x;
						BLUE_4.y = blue_all[i+5].y;
						B4=false;
						Choose_token=false;
						B_CHECK(BLUE_4);
						break;
					}

				}else if(dice_value_play==4 && BLUE_4.x!=blue_4_default_x && BLUE_4.y!=blue_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_4.x==blue_all[i].x && BLUE_4.y==blue_all[i].y){
							break;
						} 

					}
					if((i+4)<57){
						BLUE_4.x = blue_all[i+4].x;
						BLUE_4.y = blue_all[i+4].y;
						B4=false;
						Choose_token=false;
						B_CHECK(BLUE_4);
						break;
					}

				}else if(dice_value_play==3 && BLUE_4.x!=blue_4_default_x && BLUE_4.y!=blue_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_4.x==blue_all[i].x && BLUE_4.y==blue_all[i].y){
							break;
						} 

					}
					if((i+3)<57){
						BLUE_4.x = blue_all[i+3].x;
						BLUE_4.y = blue_all[i+3].y;
						B4=false;
						Choose_token=false;
						B_CHECK(BLUE_4);
						break;
					}

				}else if(dice_value_play==2 && BLUE_4.x!=blue_4_default_x && BLUE_4.y!=blue_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_4.x==blue_all[i].x && BLUE_4.y==blue_all[i].y){
							break;
						} 

					}
					if((i+2)<57){
						BLUE_4.x = blue_all[i+2].x;
						BLUE_4.y = blue_all[i+2].y;
						B4=false;
						Choose_token=false;
						B_CHECK(BLUE_4);
						break;
					}

				}else if(dice_value_play==1 && BLUE_4.x!=blue_4_default_x && BLUE_4.y!=blue_4_default_y){
					int i=0;
					for(;i<57;i++){
						if(BLUE_4.x==blue_all[i].x && BLUE_4.y==blue_all[i].y){
							break;
						} 

					}
					if((i+1)<57){
						BLUE_4.x = blue_all[i+1].x;
						BLUE_4.y = blue_all[i+1].y;
						B4=false;
						Choose_token=false;
						B_CHECK(BLUE_4);
						break;
					}

				}
				
			}
		}
		sem_post(&lock1);
		SDL_RenderPresent(render);

	pthread_exit(NULL);
}


void * master_thread(void * arg){
	if(number_of_players == 2){
		red_out=false;
		yellow_out=false;
		blue_out=true;
		green_out=true;
	} else if(number_of_players == 3){
		red_out=false;
		yellow_out=false;
		blue_out=false;
		green_out=true;
	}else if(number_of_players == 4){
		red_out=false;
		yellow_out=false;
		blue_out=false;
		green_out=false;
	}

	while (isRunning)
	{
		random_turn = (rand() % number_of_players) + 1;
		// 1. check events
		if (SDL_PollEvent(&sdl_event) != 0){
			if (sdl_event.type == SDL_QUIT)
			{
				isRunning = false;
			}
			else if (sdl_event.type == SDL_KEYDOWN)
			{
				switch (sdl_event.key.keysym.sym){
				case SDLK_ESCAPE:
					isRunning = false;
					break;
				}
			}
		}


		
			
			

			if(random_turn==1){
			

				if(yellow_out!=true){
				pthread_create(&yellow,NULL,YELLOW_Board,NULL);
				pthread_join(yellow,NULL);
				}
				if(blue_out!=true){
				if( number_of_players > 2 ){
					pthread_create(&blue,NULL,BLUE_Board,NULL);
					pthread_join(blue,NULL);
				}
				}
				if(red_out!=true){
				pthread_create(&red,NULL,RED_Board,NULL);
				pthread_join(red,NULL);
				}
				
				if(green_out!=true){
				if(number_of_players > 3){
					pthread_create(&green,NULL,GREEN_Board,NULL);
					pthread_join(green,NULL);
				}
				}
			
			
			


			}else if(random_turn==2){
				
			
				if(blue_out!=true){
				if( number_of_players > 2 ){
					pthread_create(&blue,NULL,BLUE_Board,NULL);
					pthread_join(blue,NULL);
				}
				}
				if(red_out!=true){
				pthread_create(&red,NULL,RED_Board,NULL);
				pthread_join(red,NULL);
			}
				
				if(green_out!=true){
				if(number_of_players > 3){
					pthread_create(&green,NULL,GREEN_Board,NULL);
					pthread_join(green,NULL);
				}
				}
				if(yellow_out!=true){
				pthread_create(&yellow,NULL,YELLOW_Board,NULL);
				pthread_join(yellow,NULL);
				}
				
			
				

			}else if(random_turn==3){
				
				if(red_out!=true){
				pthread_create(&red,NULL,RED_Board,NULL);
				pthread_join(red,NULL);
			}
				
				if(green_out!=true){
				if(number_of_players > 3){
					pthread_create(&green,NULL,GREEN_Board,NULL);
					pthread_join(green,NULL);
				}
				}
				if(yellow_out!=true){
				pthread_create(&yellow,NULL,YELLOW_Board,NULL);
				pthread_join(yellow,NULL);
				}
				
				if(blue_out!=true){
				pthread_create(&blue,NULL,BLUE_Board,NULL);
				pthread_join(blue,NULL);
				}

			}else if(random_turn==4){
				


			
			if(green_out!=true){
			pthread_create(&green,NULL,GREEN_Board,NULL);
			pthread_join(green,NULL);
			}
			
			if(yellow_out!=true){
			pthread_create(&yellow,NULL,YELLOW_Board,NULL);
			pthread_join(yellow,NULL);
			}
			if(blue_out!=true){
			pthread_create(&blue,NULL,BLUE_Board,NULL);
			pthread_join(blue,NULL);
			}
			if(red_out!=true){
				pthread_create(&red,NULL,RED_Board,NULL);
				pthread_join(red,NULL);
			}

		}



		if(not_six_red>=10){
			pthread_cancel(red);
			red_out = true;
			cout << "Red Thread Got Eleminated because it failed to get sixes." << endl;
		}
		if (number_of_players > 2){
		if(not_six_blue>=10){
			pthread_cancel(blue);
			blue_out = true;
			cout << "Blue Thread Got Eleminated because it failed to get sixes." << endl;
		}	
		}
		if (number_of_players > 3){
		if(not_six_green>=10){
			pthread_cancel(green);
			green_out = true;
			cout << "Green Thread Got Eleminated because it failed to get sixes." << endl;
		}
		}
		if(not_six_yellow>=10){
			pthread_cancel(yellow);
			yellow_out = true;
			cout << "Yellow Thread Got Eleminated because it failed to get sixes." << endl;
		}


		if(red_out==true && blue_out==true && green_out==true){
			cout << "Yellow Won." << endl;
			break;

		}
		if(red_out==true && yellow_out==true && green_out==true){
			cout << "Blue Won." << endl;
			break;

		}
		if(red_out==true && blue_out==true && yellow_out==true){
			cout << "Green Won." << endl;
			break;

		}
		if(yellow_out==true && blue_out==true && green_out==true){
			cout << "Red Won." << endl;
			break;

		}








		if(mega_close==false){
			break;
		}
		
	}

pthread_exit(NULL);
}



int main(int argc, char *argv[])
{
	srand(0);
	do{
		cout << "Enter no of players : " ;
		cin >> number_of_players;
	}while( number_of_players < 2   ||  number_of_players > 4) ;

	initializer();

	if (SDL_Init(SDL_INIT_VIDEO))
	{
		cout << "Failed to init SDL Video, error: %s" << SDL_GetError() << endl;
		return -1;
	}
	//Set texture filtering to linear
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
		cout << "Warning: Linear texture filtering not enabled!" << endl;
	}

	int win_width = 900;
	int win_height = 900;

	// Create an application window with the following settings:
	sdl_window = SDL_CreateWindow(
		"LUDO", // window title
		SDL_WINDOWPOS_UNDEFINED,					  // initial x position
		SDL_WINDOWPOS_UNDEFINED,					  // initial y position
		win_width,									  // width, in pixels
		win_height,									  // height, in pixels
		SDL_WINDOW_SHOWN	     					  // flags - see below
	);
	

	// Check that the window was successfully created
	if (sdl_window == nullptr)
	{
		cout << "Could not create window: %s" << SDL_GetError() << endl;
		return -1;
	}
	render=SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) ;
	SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0x00 );
	
	
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ){
		cout << "SDL_image could not initialize! SDL_image Error: %s\n" << IMG_GetError() << endl;
	}
	
	
	//Load PNG texture
	
	SDL_Surface* Surface = IMG_Load("3.png");
	Texture = SDL_CreateTextureFromSurface(render, Surface );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface);
	
	
	
	
	
	//RED1
	//Load PNG texture
	SDL_Surface* Surface_RED_1 = IMG_Load("red1.png");
	Texture_RED_1 = SDL_CreateTextureFromSurface(render, Surface_RED_1 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_RED_1);
	

	//RED2
	//Load PNG texture
	SDL_Surface* Surface_RED_2 = IMG_Load("red2.png");
	
	Texture_RED_2 = SDL_CreateTextureFromSurface(render, Surface_RED_2 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_RED_2);



	//RED3
	//Load PNG texture
	SDL_Surface* Surface_RED_3 = IMG_Load("red3.png");
	
	Texture_RED_3 = SDL_CreateTextureFromSurface(render, Surface_RED_3 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_RED_3);

	//RED4
	//Load PNG texture
	SDL_Surface* Surface_RED_4 = IMG_Load("red4.png");
	
	Texture_RED_4 = SDL_CreateTextureFromSurface(render, Surface_RED_4 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_RED_4);


	//GREEN1
	//Load PNG texture
	SDL_Surface* Surface_GREEN_1 = IMG_Load("green1.png");
	
	Texture_GREEN_1 = SDL_CreateTextureFromSurface(render, Surface_GREEN_1 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_GREEN_1);

	//GREEN2
	//Load PNG texture
	SDL_Surface* Surface_GREEN_2 = IMG_Load("green2.png");
	
	Texture_GREEN_2 = SDL_CreateTextureFromSurface(render, Surface_GREEN_2 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_GREEN_2);


	//GREEN3
	//Load PNG texture
	SDL_Surface* Surface_GREEN_3 = IMG_Load("green3.png");
	
	Texture_GREEN_3 = SDL_CreateTextureFromSurface(render, Surface_GREEN_3 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_GREEN_3);


	//GREEN4
	//Load PNG texture
	SDL_Surface* Surface_GREEN_4 = IMG_Load("green4.png");
	
	Texture_GREEN_4 = SDL_CreateTextureFromSurface(render, Surface_GREEN_4 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_GREEN_4);



	sem_init(&lock1,0,10);
    sem_init(&lock2,0,10);
    sem_init(&lock3,0,10);
    sem_init(&lock4,0,10);


	//BLUE1
	//Load PNG texture
	SDL_Surface* Surface_BLUE_1 = IMG_Load("blue1.png");
	
	Texture_BLUE_1 = SDL_CreateTextureFromSurface(render, Surface_BLUE_1 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_BLUE_1);
	
	//BLUE2
	//Load PNG texture
	SDL_Surface* Surface_BLUE_2 = IMG_Load("blue2.png");
	
	Texture_BLUE_2 = SDL_CreateTextureFromSurface(render, Surface_BLUE_2 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_BLUE_2);

	//BLUE3
	//Load PNG texture
	SDL_Surface* Surface_BLUE_3 = IMG_Load("blue3.png");
	
	Texture_BLUE_3 = SDL_CreateTextureFromSurface(render, Surface_BLUE_3 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_BLUE_3);


	//BLUE4
	//Load PNG texture
	SDL_Surface* Surface_BLUE_4 = IMG_Load("blue4.png");
	
	Texture_BLUE_4 = SDL_CreateTextureFromSurface(render, Surface_BLUE_4 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_BLUE_4);



	//YELLOW 1
	//Load PNG texture

	SDL_Surface* Surface_YELLOW_1 = IMG_Load("yellow1.png");
	
	Texture_YELLOW_1 = SDL_CreateTextureFromSurface(render, Surface_YELLOW_1 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_YELLOW_1);


	//YELLOW 2
	//Load PNG texture

	SDL_Surface* Surface_YELLOW_2 = IMG_Load("yellow2.png");
	
	Texture_YELLOW_2 = SDL_CreateTextureFromSurface(render, Surface_YELLOW_2 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_YELLOW_2);



	//YELLOW 3
	//Load PNG texture

	SDL_Surface* Surface_YELLOW_3 = IMG_Load("yellow3.png");
	
	Texture_YELLOW_3 = SDL_CreateTextureFromSurface(render, Surface_YELLOW_3 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_YELLOW_3);



	//YELLOW 4
	//Load PNG texture
	
	SDL_Surface* Surface_YELLOW_4 = IMG_Load("yellow4.png");
	
	Texture_YELLOW_4 = SDL_CreateTextureFromSurface(render, Surface_YELLOW_4 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_YELLOW_4);




	//DICE 1
	//Load PNG texture
	
	SDL_Surface* Surface_DICE_1 = IMG_Load("dice1.png");
	
	Texture_DICE_1 = SDL_CreateTextureFromSurface(render, Surface_DICE_1 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_DICE_1);
	
	
	//DICE 2
	//Load PNG texture
	SDL_Surface* Surface_DICE_2 = IMG_Load("dice2.png");
	
	Texture_DICE_2 = SDL_CreateTextureFromSurface(render, Surface_DICE_2 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_DICE_2);
	
	

	//DICE 3
	//Load PNG texture
	SDL_Surface* Surface_DICE_3 = IMG_Load("dice3.png");
	
	Texture_DICE_3 = SDL_CreateTextureFromSurface(render, Surface_DICE_3 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_DICE_3);
	
	


	//DICE 4
	//Load PNG texture
	SDL_Surface* Surface_DICE_4 = IMG_Load("dice4.png");
	
	Texture_DICE_4 = SDL_CreateTextureFromSurface(render, Surface_DICE_4 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_DICE_4);
	
	


	//DICE 5
	//Load PNG texture
	SDL_Surface* Surface_DICE_5 = IMG_Load("dice5.png");
	
	Texture_DICE_5 = SDL_CreateTextureFromSurface(render, Surface_DICE_5 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_DICE_5);
	
	



	//DICE 6
	//Load PNG texture
	SDL_Surface* Surface_DICE_6 = IMG_Load("dice6.png");
	
	Texture_DICE_6 = SDL_CreateTextureFromSurface(render, Surface_DICE_6 );
	//Get rid of old loaded surface
	SDL_FreeSurface(Surface_DICE_6);
	
	

	

    
	pthread_create(&master,NULL,master_thread,NULL);
	pthread_join(master,NULL);
	pthread_exit(NULL);
	//pthread_mutex_destroy(&dice_lock);

	// clean up
	SDL_DestroyWindow(sdl_window);
	SDL_Quit();

	return 0;
}