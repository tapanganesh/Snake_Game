#include<iostream>
#include<conio.h>
#include<windows.h>
#include <unistd.h>
#include<stdlib.h>
#include<time.h>

using namespace std;

#define nl '\n'

bool gameover=false;
const int boardwidth=75,boardheight=20;
int headx=boardwidth/2,heady=boardheight/2;
int fruitx,fruity;
int x[100],y[100];
int  direction;
int taillength=1;
int score=0,speed=250;
clock_t gametime;

class game{

    private:
    public:
    void createboard();
    bool gamestatus();
    void input();
    void logic();
};
void game::createboard(){
    Sleep(15);
    system("cls");
    for(int i=0;i<boardwidth+2;i++){
        cout<<"*";
    }
    cout<<nl;
    for(int j=0;j<boardheight;j++){
        for(int i=0;i<boardwidth;i++){
            if(i==0){
                cout<<"|";
            }
                // if(i==boardwidth-1){
                //     cout<<"|";
                // }
           if(i==fruitx && j==fruity){
               if(score%50!=0)
                cout<<"+";
                else
                cout<<"=";
            }
            
            else{
                if(i<boardwidth&&j<boardheight)
                cout<<" ";
            }
            for(int n=1;n<taillength;n++){
                    if(i==x[n]&&j==y[n]){
                        cout<<n;
                    }
                }
            if(i==headx&&j==heady){
                cout<<"O";
            }
        }
        cout<<"|";
        cout<<nl;
    }
    for(int i=0;i<boardwidth+2;i++){
        cout<<"*";
    }
    cout<<"\nYOUR CURRENT SCORE: "<<score<<nl;
    cout<<"TIME:"<<(clock()-gametime)/CLOCKS_PER_SEC<<nl;

}
void game::input(){
    if(_kbhit()){
        char choice=_getch();
        switch (choice)
        {
        case 'w':
            direction=1;
            break;

        case 's':
            direction=2;
            break;

        case 'a':
            direction=3;
            break;

        case 'd':
            direction=4;
            break;
        case 'x':
            Sleep(1);
            cout<<"\n-YOU CHOOSE TO EXIT THE GAME-\n";
            gameover=true;
        default:
            break;
        }
    }
}
void game::logic(){
    x[0]=headx,y[0]=heady;
    int tailx=headx,taily=heady,prevx,prevy;
    prevx=x[0],prevy=y[0];
   int i;
   for( i=1;i<=taillength;i++){
       prevx=x[i];
       prevy=y[i];
       x[i]=tailx;
       y[i]=taily;
       tailx=prevx;
       taily=prevy;
   }
    switch(direction){
        case 1:
            heady--;
            break;
        case 2:
            heady++;
            break;
        case 3:
            headx--;
            break;
        case 4:
            headx++;
            break;
        default:
            break;
    }
    if(headx==fruitx&&heady==fruity){
            fruitx=rand()%boardwidth;
            fruity=rand()%boardheight;
            if(fruitx==0)fruitx+=2;
            if(fruity==0)fruity+=2;
            score=score+10;
            speed-=25;
            if(speed<100)speed=100;
            taillength++;
            prevx=headx;
            prevy=heady;
   }
   if(headx>boardwidth-taillength)headx=0;
   if(heady>boardheight)heady=0;
   if(heady<0)heady=boardheight;
   if(headx<0)headx=boardwidth-taillength;
   for(int j=1;j<=taillength;j++){
       if(headx==x[j]&&heady==y[j]){
           gameover=true;
           cout<<"\n-GAME OVER-\n";
           return;
       }
   }


}

game snakegame;

int main(){
    fruitx=rand()%boardwidth;
    fruity=rand()%boardheight;
    snakegame.createboard();
    cout<<nl<<"         \t\t --WELCOME TO SNAKE GAME--\n";
    sleep(2);
    gametime=clock();
    while(!gameover){
        snakegame.input();
        snakegame.logic();
        if(!gameover)
        snakegame.createboard();
        Sleep(speed);

    }
    return 0;
}

