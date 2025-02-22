#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>  
#include <chrono>
#include <thread>
using  namespace std;



void delay(int milliseconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds * (CLOCKS_PER_SEC / 1000));
}

class Ball;
class Robot{
    string Name;
    int Hits;
    public:
    Robot(string name="unknown"):Name(name),Hits(0){}
    void increHits(){Hits++;}
    void hitBall(Ball &ball ,string direction);
    int getHits(){return Hits;}
    string getName(){return Name;}
};

class Ball{
    int X,Y;
    public:
    Ball():X(0),Y(0){}
    int GetX(){return X;}
    int GetY(){return Y;}
   
    void move(int dx,int dy){
        X+=dx;
        Y+=dy;
    }
    
   void getPosition(){
        cout<<"X:"<<X<<" and "<<"Y:"<<Y;
    }
    void reset(){
        X=0;
        Y=0;
    }
};

class Team{
    string TeamName;
    Robot *r;
    public:
    Team(string name ,Robot *r=nullptr):TeamName(name){
        this->r=r;
    }
    string GetName(){
        return TeamName;
    }

    Robot *GetPTR(){
        return r;
    }
};

class Goal{
    int X,Y;
    public:
    Goal():X(3),Y(3){}
    int GetX(){return X;}
    int GetY(){return Y;}
    bool isGoalReached(int ballX, int ballY){
        if(ballX==X && ballY==Y){
            return true;
        }
        return false;
    }
};


class Game{
    Ball b;
    Goal goal;
    Team team1,team2;
    public:
        Game(Team t1,Team t2):team1(t1),team2(t2){
            srand(time(0));
        }

        void Display(Goal &g,Ball &b ,Team &t){
            delay(100);
            system("cls");
            cout<<"    Hit="<<(t.GetPTR())->getHits()<<endl;
            cout<<"  "<<t.GetName()<<"("<<(t.GetPTR())->getName()<<")"<<endl;
            for(int i=0;i<7;i++){
                if(i==0 || i==6)
                    cout<<"==============";
                for(int j=0;j<7;j++){
                    if(j!=0 && j!=6){
                        if(g.GetX()==i-1 && g.GetY()==j-1)
                            cout<<"X";
                        else   
                            cout<<" ";
                        if(b.GetX()==i-1 && b.GetY()==j-1)
                            cout<<"*";
                        else 
                            cout<<" ";
                    }
                    else if(i!=0 && i!=6) cout<<"||";
                    }
                    cout<<endl;
                }
            }

       
            void Play(Team *team){
                while (!(goal.isGoalReached(b.GetX(),b.GetY())))
                {
                int random = rand()%5;
                Display(goal,b,*team);
                switch (random)
                {
                case 1:
                   if(b.GetX()!=3)
                       team->GetPTR()->hitBall(b,"up");
                   break;
                case 2:
                   if(b.GetX()!=0)
                       team->GetPTR()->hitBall(b,"down");
                   break;
               case 3:
                   if(b.GetY()!=3)
                       team->GetPTR()->hitBall(b,"left");
                   break;
               case 4:
                   if(b.GetY()!=0)
                       team->GetPTR()->hitBall(b,"right");
                   break;
                default:
                   break;
                }
                (team->GetPTR())->increHits();
           }
        }
        
     
        void startGame(){
            cout<<"turn of "<<team1.GetName()<<endl;
            Play(&team1);
            b.reset();
            cout<<"turn of "<<team2.GetName()<<endl;
            delay(2000);
            Play(&team2);

            if((team1.GetPTR())->getHits()==(team2.GetPTR())->getHits()){
                cout<<"Draw between team "<<team1.GetName()<<" and "<<team2.GetName();
            }
            else if((team1.GetPTR())->getHits()<(team2.GetPTR())->getHits()){
                cout<<team1.GetName()<<" is winner"<<endl;
            }
            else{
                cout<<team2.GetName()<<" is winner"<<endl;
            }
        }
    
       
};


    void Robot::hitBall(Ball &ball ,string direction){
        if(direction=="UP" || direction=="up" || direction=="Up")
            ball.move(1,0);
        else if(direction=="DOWN" || direction=="down" || direction=="Down")
            ball.move(-1,0);
        else if(direction=="LEFT" || direction=="left" || direction=="Left")
            ball.move(0,1);
        else 
            ball.move(0,-1);
    }



int  main(){
    Robot r1("steve");
    Robot r2("DeepSeek");
    Team t1("blue",&r1);
    Team t2("red",&r2);
    Game g(t1,t2);
    g.startGame();
}



