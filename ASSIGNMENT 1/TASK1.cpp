#include <iostream>
#include <string>
using namespace std;

class Mentor;
class Skill;
class Sport;

class Student{
    static int Total_Student;
    int StudentId;
    string Name;
    int Age;
    int InterestedSportNo;
    Sport *sportsInterests;
    Mentor *MentorAssigned;
    public:
    void registerForMentorship(Mentor &);
    void updateSportsInterest( );

    Student(int Id=0,string name="Unknown",int age=0):StudentId(Id),Name(name),Age(age){
        InterestedSportNo=0;
        sportsInterests=nullptr;
        MentorAssigned=nullptr;
    }

    void SetID(int id){StudentId=id;}
    void SetName(string Name){this->Name=Name;}
    void SetAge(int age){Age=age;}
    void SetMentor(Mentor &m){MentorAssigned=&m;}
    void IncreStudent(){Total_Student++;}
    void IncreISN(){InterestedSportNo++;}
    int GetTotalStudent(){return Total_Student;}
    int GetId(){return  StudentId;}
    string GetName(){ return Name;}
    int GetISN(){return InterestedSportNo;}
    Sport *GetSport(){return sportsInterests;}
    int GetAge(){return Age;}
    void viewMentorDetails();
    void deleteMentor(){
        MentorAssigned =nullptr;
    }
    void display();
    ~Student();
};

class Mentor{
    static int Total_mentor;
    int MentorId;
    string Name;
    string sportsExpertise;
    int maxLearners;
    int currentLearners;
    int ListRequestNo;
    string *assignedLearners;
    string *ListRequest;
    public:

    void assignLearner(Student &s){
        currentLearners++;
        string *temp=assignedLearners;
        assignedLearners=new string[currentLearners];
        for(int i=0;i<currentLearners-1;i++){
            assignedLearners[i]=temp[i];
        }
        assignedLearners[currentLearners-1]=s.GetName();
    }

    void removeLearner(Student &s){
        int removeNo;
        for(int i=0;i<currentLearners;i++){
            if(s.GetName()==assignedLearners[i]){
                removeNo=i;
                break;
            }
        }
        for(int i=removeNo;i<currentLearners;i++)
            assignedLearners[i]=assignedLearners[i+1];
        currentLearners--;
    }

    void viewLearners(){
        if(ListRequest){
        for(int i=0;i<ListRequestNo;i++)
            cout<<i+1<<":"<<ListRequest[i]<<endl;
        }
        else{
            cout<<"0 request"<<endl;
        }
    }

    void provideGuidance(){
        viewLearners();
        string guide;
        int index;
        cout<<"Select one of them:";
        cin>>index;
        viewLearners();
        if(index<ListRequestNo) {
        cout<<"Send Guidance to "<<assignedLearners[index]<<":";
        cin>>guide;
        }
        else
            cout<<"you entered a wrong index."<<endl;
        
    } 

    Mentor(int id=0,string name="unknown",int CL=0,int ML=0,string sportt="no sport"):MentorId(id),Name(name),currentLearners(CL),maxLearners(ML)
    {
        sportsExpertise =sportt;
        ListRequestNo=0;
        assignedLearners=nullptr;
        ListRequest=nullptr;
    }

    void SetId(int id){MentorId=id;}
    void SetName(string name){Name=name;}
    void SetCL(int CL){currentLearners=CL;}
    void SetML(int ML){maxLearners=ML;}
    void setsportsExpertise(string n){sportsExpertise=n;}
    string getsportsExpertise(){return sportsExpertise;}
    int getCL(){return currentLearners;}
    int getML(){return maxLearners;}
    int GetId(){return  MentorId;}
    int GetRN(){return ListRequestNo;}
    string GetName(){ return Name;}
    void IncreMentor(){Total_mentor++;}
    int GetMentorN(){return Total_mentor;}
    void IncreLR(){
        ListRequestNo++;
        string  *temp=ListRequest;
        ListRequest=new string[ListRequestNo];
        for(int  i=0;i<ListRequestNo-1;i++){
            ListRequest[i]=temp[i];
        }
    }
    
    void SetLR(string name){
        ListRequest[ListRequestNo-1]=name;
    }

    void display(){
        cout<<"Name:"<<Name<<"("<<MentorId<<")"<<endl;
        cout<<"Expertise in "<<sportsExpertise<<endl;
        cout<<"Capacity:"<<currentLearners<<"/"<<maxLearners<<endl;
    }

    ~Mentor(){
        delete[] assignedLearners;
        delete[] ListRequest;
    }
};

class Sport{
    int SportId;
    string Name;
    string description;
    int TotalSkill;
    Skill* requiredSkill;
    public:
    void addSkill(Skill s);
    void removeSkill(Skill s);

    Sport(int id=0,string name="unknown"):SportId(id),Name(name){
        requiredSkill=nullptr;
        TotalSkill=0;
    }
    void ShowAllSkill();

    void SetId(int id){SportId=id;}
    void SetName(string name){Name=name;}
    void SetDecription(string des){description=des;}
    int GetId(){return  SportId;}
    string GetName(){ return Name;}
    string GetDes(){return description;}

    Skill GetRequiredSkill(int n);
    ~Sport();
};

class Skill{
    int SkillId;
    string SkillName;
    string description;
    public:
    void showSkillDetails(){
        cout<<"SkillId:"<<SkillId<<endl<<"skillName:"<<SkillName<<endl<<"Description:"<<description<<endl;
    }

    void updateSkillDescription(string newDescription){
        description=newDescription;
    }
    Skill(int id=0,string name="unknown"):SkillId(id),SkillName(name){}
    void SetId(int id){SkillId=id;}
    void SetName(string name){SkillName=name;}
    void SetDecription(string des){description=des;}
    int GetId(){return  SkillId;}
    string GetName(){ return SkillName;}
    string GetDes(){return description;}
};

void Student::registerForMentorship(Mentor &m){
    if(m.getCL()!=m.getML()){
        m.IncreLR();
        m.SetLR(Name);
    }
} 

Skill detailsOfSkill(){
    Skill s;
    int id;
    string description;
    string name;
    cout<<"Enter the Skill  id:";
    cin>>id;
    cout<<"Enter the name of skill:";
    cin>>name;
    cout<<"Enter the description of the skill:";
    cin>>description;
    
    s.SetId(id);
    s.SetName(name);
    s.SetDecription(description);
    return s;
}

void Student::updateSportsInterest(){
    //updating sport 
    Sport s;
    int id;
    string name;
    string description;
    cout<<"Enter the sport id:";
    cin>>id;
    s.SetId(id);
    cout<<"Enter the sport name:";
    cin>>name;
    s.SetName(name);
    cout<<"Enter the Decription:";
    cin>>description;
    s.SetDecription(description);

    //adding skill or removing of skill
    int end=1;
    cout<<"do you want to add  or remove skill(0-NO):";
    cin>>end;
    int opt;
    while(end){
        cout<<"click 1 for adding any skill:"<<endl;
        cout<<"click 2 for removing any skill:"<<endl;
        cout<<"click 3 for display for skills:"<<endl;
        cin>>opt;
        switch (opt)
        {
        case 1:
            s.addSkill(detailsOfSkill());
            break;
        case 2:
            cout<<"Select one of them:"<<endl;
            s.ShowAllSkill();
            int opt;
            cin>>opt;
            if(InterestedSportNo)
                s.removeSkill(s.GetRequiredSkill(opt-1));
            break;
        case 3:
            s.ShowAllSkill();
            break;
        default:
            break;
        }
        cout<<"Do you want to continue?(0-NO)";
        cin>>end;
    }

    //increment in the size of the array 
    InterestedSportNo++;
    Sport *temp=sportsInterests;
    sportsInterests=new Sport[InterestedSportNo];

    for(int i=0;i<InterestedSportNo-1;i++){
        sportsInterests[i]=temp[i];
    }
    sportsInterests[InterestedSportNo-1]=s;
}
    Student::~Student(){
        if (sportsInterests){
            delete[] sportsInterests;
        }
    }

    Sport:: ~Sport(){
        if(requiredSkill)
            delete[] requiredSkill;
    }

    void Sport::ShowAllSkill(){
        if(requiredSkill){
        for(int i=0;i<TotalSkill;i++){
            cout<<"\t\tSkill:"<<i+1<<":"<<requiredSkill[i].GetId()<<endl;
            cout<<"\t\t\tDecription:"<<requiredSkill[i].GetDes()<<endl;
        }
    }
    }

    void Sport::addSkill(Skill s){
        TotalSkill++;
        Skill *temp=requiredSkill;
        requiredSkill=new Skill[TotalSkill];
        for(int i=0;i<TotalSkill-1;i++){
            requiredSkill[i]=temp[i];
        }
        requiredSkill[TotalSkill-1]=s;
    }
    void Sport::removeSkill(Skill s){
        int removeNo;
        for(int i=0;i<TotalSkill;i++){
            if(s.GetId()==requiredSkill[i].GetId())
                removeNo=i;
                break;
        }
           
        for(int i=removeNo;i<TotalSkill-1;i++)
            requiredSkill[i]=requiredSkill[i+1];
        TotalSkill--;
    }

    Skill Sport::GetRequiredSkill(int n){return requiredSkill[n];}

    
    void Student:: viewMentorDetails(){
        if(MentorAssigned){
           cout<<"ID:"<<MentorAssigned->GetId()<<endl;
            cout<<"Name:"<<MentorAssigned->GetName()<<endl;
            cout<<"Current learners:"<<MentorAssigned->getCL()<<endl;
            cout<<"Maximum learners:"<<MentorAssigned->getML()<<endl;
        }
        else{
            cout<<"Mentor does not exist"<<endl;
        }
   }

   int Student::Total_Student=0;
   int Mentor::Total_mentor=0;


void Student::display(){
    cout<<endl<<"Name:"<<Name<<"("<<StudentId<<")"<<endl;
    cout<<"Age:"<<Age<<endl;
    if(MentorAssigned){
        cout<<endl<<"Mentor:"<<MentorAssigned->GetName()<<endl;
    }
    if(sportsInterests){
        for(int i=0;i<InterestedSportNo;i++){
            cout<<"Sport :"<<sportsInterests[i].GetName()<<endl;
            cout<<"\tDescription:"<<sportsInterests[i].GetDes()<<endl;
            sportsInterests[i].ShowAllSkill();
        }      
    }
}

Student registerStudent(){
    int id,age;
    string name;
    cout<<"Enter the Id:";
    cin>>id;
    cout<<"Enter the Name:";
    cin>>name;
    cout<<"Enter the Age:";
    cin>>age;
    return Student(id,name,age);
}

Mentor registerMentor(){
    int id;
    string name;
    string sport;
    int maxCap;
    cout<<"Enter the Id:";
    cin>>id;
    cout<<"Enter the Name:";
    cin>>name;
    cout<<"Enter the Sport:";
    cin>>sport;
    cout<<"Maxterm capacity of student:";
    cin>>maxCap;
    return Mentor(id,name,0,maxCap,sport);
}

int GetIdOfStudent(Student *student ){
    int sel,j;
    cout<<"Enter id:";
    cin>>sel;
    for(j=0;j<student[0].GetTotalStudent();j++){
        if(sel==student[j].GetId()){
           break;
        }
    }
    if(j==student[0].GetTotalStudent()) {cout<<"Wrong ID"<<endl;}
    else return j;
    return -1;
}

int MentorView(Student *student,Mentor *mentor,int n){
    if(mentor){
    int i;
    int opt;
        for(i=0;i< mentor[0].GetMentorN();i++){
        cout<<i+1<<":"<<mentor[i].GetName()<<"\t"<<mentor[i].getsportsExpertise()<<"\t"<<mentor[i].getCL()<<"/"<<mentor[i].getML()<<endl;
        }  
        cin>>opt;
        int j;
        for(j=0;j<student[n].GetISN();j++){
            if(mentor[opt-1].getsportsExpertise()==student[n].GetSport()[j].GetName()) break;
        }
            if(student[n].GetISN() && j!=student[n].GetISN())
                return opt-1;
            else{
                cout<<"Mentor Sport expertise does not match with your Sport"<<endl;
            }
    }
    else{
        cout<<"Mentor is not available."<<endl;
    }
    return -1;
}

int main(){
    int stud;
    Mentor *mentor=nullptr;
    Student *student;
    int present=0;
    int end=1;
while(end){
    cout<<"Are you Mentor(1-No):";
    cin>>stud;
if(stud==1)
{
    int id,i;
    cout<<"Enter your Id:";
    cin>>id;
    for( i=0;i<student[0].GetTotalStudent();i++){
        if(student[i].GetId()==id) break;
    }
    if(student[0].GetTotalStudent()==i){
        int des;
        cout<<"Student id does not exit"<<endl;
        cout<<"Do you want to register?(1-yes):";
        cin>>des;
        if(des==1){
            student[0].IncreStudent();
            Student *temp=student;
            student=new Student[student[0].GetTotalStudent()];
            for(int i=0;i<student[0].GetTotalStudent()-1;i++) 
                student[i]=temp[i];
            student[student[0].GetTotalStudent()-1]= registerStudent();
        }
    }
    else{
        int opt;
        int end1=1;
        while(end1){
            cout<<"1.Register"<<endl;
            cout<<"2.Mentor Details"<<endl;
            cout<<"3.Display"<<endl;
            cout<<"4.Add sport"<<endl;
            cout<<"5.Exit"<<endl;
            cin>>opt;
            switch (opt)
            {
            case 1:
            int newNum;
                
                newNum=MentorView(student,mentor,i);
                if(newNum!=-1)
                    student[i].registerForMentorship(mentor[newNum]);
                    break;
            case 2:
                student[i].viewMentorDetails();
                break;
            case 3:
                student[i].display();
                break;
            case 4:
                student[i].updateSportsInterest();
                break;
            case 5:
               end1=0;
               break;
            default:
                break;
            }
        }
    }
}
else{
    int id,i;
    cout<<"Enter your Id:";
    cin>>id;
    for( i=0;i<mentor[0].GetMentorN();i++){
        if(mentor[i].GetId()==id) break;
    }
    if(mentor[0].GetMentorN()==i){
        int des;
        cout<<"Mentor id does not exit"<<endl;
        cout<<"Do you want to register?(1-yes):";
        cin>>des;
        if(des==1){
            mentor[0].IncreMentor();
            Mentor *temp=mentor;
            mentor=new Mentor[mentor[0].GetMentorN()];
            for(int i=0;i<mentor[0].GetMentorN()-1;i++) 
                mentor[i]=temp[i];
            mentor[mentor[0].GetMentorN()-1]= registerMentor();
        }
    }
    else{
        int opt;
        int end1=1;
        while(end1){
            cout<<"1.Add Learner"<<endl;
            cout<<"2.Request List"<<endl;
            cout<<"3.Display"<<endl;
            cout<<"4.Remove Learner"<<endl;
            cout<<"5.Provide Guidance"<<endl;
            cout<<"6.Exit"<<endl;
            cin>>opt;
            int k;
            switch (opt)
            {
                case 1:
                    k= GetIdOfStudent(student);
                    if(k!=-1) {
                        student[k].SetMentor(mentor[i]);
                        mentor[i].assignLearner(student[k]);
                    }
                    break;
                case 2:
                    mentor[i].viewLearners();
                    break;
                case 3:
                    mentor[i].display();
                    break;
                case 4:
                    k= GetIdOfStudent(student);
                    if(k!=-1){
                        student[k].deleteMentor();
                        mentor[i].removeLearner(student[k]);
                    }
                    break;
                case 5:
                    mentor[i].provideGuidance();
                    break;
                case 6:
                    end1=0;
                    break;
                default:
                    break;
            }
        }
    }
}
int con;
cout<<"Do you want to continue?(0-NO):";
cin>>con;
if(!con) end=0;
}
}
