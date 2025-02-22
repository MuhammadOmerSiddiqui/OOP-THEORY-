#include <iostream>
#include <string>
using  namespace std;

class Bus;

class student{
    static int student_no;
    int id;
    string name;
    int Transport_card;
    string pick_up;
    Bus *assignedBus;
    int attendence[30];
    public:
    student(){
        Transport_card=0;
        for(int i=0;i<30;i++)
            attendence[i]=0;
    }
    void PayForTransportion(){Transport_card=1;}
    SetValue(){
        cout<<"Enter id:";
        cin>>id;
        cout<<"Enter name:";
        cin>>name;
        cout<<"Enter pick_up place:";
        cin>>pick_up;
    }
    void SetBus(Bus &b);
    int getId() const {return id;}
    int GetTransportCard() const{return Transport_card;}
    string Getpick_up() const {return pick_up;}
    Bus *GetBus() const {return assignedBus;}
    int GetAttendence() const;
    void SetAttendence();
    ~student();
};

class Bus{
    static int day;
    string *Stops;
    int NumberOfStops;
    public:
    Bus(){}
    Bus(int size,string *ptr):NumberOfStops(size){
        Stops=new string[size];
        for(int i=0;i<size;i++){
            Stops[i]=ptr[i];
        }
    }
    bool TabCard(){return true;}
    int GetSize(){return NumberOfStops;}
    string GetsStops(int n){return Stops[n];}
    void increDay(){
        day++;
    }
    int getDay(){return day;}
    ~Bus(){delete[] Stops;}
};
void student::SetBus(Bus &b) {assignedBus=&b;}
int student::GetAttendence() const {return attendence[assignedBus->getDay()];}
void student::SetAttendence() {attendence[assignedBus->getDay()]=1;}
student::~student(){delete[] assignedBus;}
int Bus::day = 0;

int main(){
int total_student=0;
Bus b[3];
student *s=nullptr;

string r1[7]={
    "Nazimabad",  
    "Liaqtabad",       
    "Hasan square",
    "Dalmia"          
    "Johar more"   
    "Natha Khan"  
    "University" 
}; 

string r2[7]={
    "Garden",          
    "Jamat Khana", 
    "Guru mandir",   
    "Tariq route",        
    "Shaheedemillat",  
    "Baloch pull",      
    "University",       
};

string r3[8]={
    "Teen talwar ",    
    "Askari 3",          
    "Kala pull",       
    "Akhtar colony",
    "Kpt bridge",     
    "Korangi",          
    "Landhi",          
    "University",      
};

b[0]=Bus(7,r1);
b[1]=Bus(7,r2);
b[2]=Bus(8,r3);

int end1=1,end2=1;
int opt;

while(end1){
cout<<"Enter id(9009 for new Student):";
int id;
cin>>id;
if(id==9009){
    total_student++;
    student *temp=s;
    s=new student[total_student];
    for(int  i=0;i<total_student-1;i++){
        s[i]=temp[i];
    }

    s[total_student-1].SetValue();
}
else{
    int i;
    for( i=0;i<total_student;i++){
        if(id==s[i].getId())
            break;
    }
    if(total_student!=i){
       if(s[i].GetTransportCard()){
        int a;
            cout<<"click any button for attendence:";
            cin>>a;
            if(s[i].GetAttendence())
                s[i].GetBus()->TabCard();
            else{
                s[i].GetBus()->increDay();
                s[i].GetBus()->TabCard();
            }
       }
       else{
        int pay;
            cout<<"Pay Your Transport fees otherwise you don't get card(1-for paying fees): ";
            cin>>pay;
            if(pay==1){
                int over=1;
                s[i].PayForTransportion(); 
                for(int k=0;k<3 && over;k++){
                    for(int j=0;j<b[k].GetSize() && over;j++){
                        if(s[i].Getpick_up()==b[k].GetsStops(j)){
                            s[i].SetBus(b[k]);
                            over=0;
                        }
                    }
                }
                if(over) cout<<"Wrong bus stop"<<endl;
            }
       }
    }
    else{
        cout<<"Wrong Id"<<endl;
    }
}
cout<<"Do you want to close this program(0-Yes):";
cin>>end1;
}

}

