#include <iostream>
#include <string>
using namespace std;

class Users{
    int Age;
    string License_type;
    string contact_information;
    int user_id;
    public:
        users(){};
        Users(int age,string lt,string ci,int ui):Age(age),License_type(lt),contact_information(ci),user_id(ui){}
        void setAge(int a){this->Age=a;}
        void setLT(string L){this->License_type=L;}
        void setCI(string c){this->contact_information=c;}
        void setUI(int u){this->user_id=u;}
        string GetLT(){return License_type;}
};

class vehicle{
    string model;
    float RentalPerDay;
    string Eligibility;
    public:
        vehicle(){}
        vehicle(string m,float RPD,string Elt):model(m),RentalPerDay(RPD),Eligibility(Elt){}
        float getRPD(){return RentalPerDay;}
        string getModel(){return model;}
        string getEligibility(){return  Eligibility;}
};

void update(Users &user){
    int opt,end;
    while (end)
    {
    cout<<"1.For Changing Age:"<<endl;
    cout<<"2.For Changing License type:"<<endl;
    cout<<"3.For changing contact information:"<<endl;
    cout<<"4.For Changing User id:"<<endl;
    cin>>opt;
    switch(opt){
        case 1:{
            cout<<"Enter the new age:";
            int age;
            cin>>age;
            user.setAge(age);
            break;
        }
        case 2:{
            cout<<"Enter the updated License type((Learner,Intermediate,Full-License)):";
            string LT;
            cin>>LT;
            user.setLT(LT);
            break;
        }
        case 3:{
            cout<<"Enter the new contact information:";
            string CI;
            cin>>CI;
            user.setCI(CI);
            break;
        }
        case 4:{
            cout<<"Enter the new User Id:";
            int id;
            cin>>id;
            user.setUI(id);
            break;
        }
        default :
            break;
    }
    cout<<"Do you want to continue(0-No):";
    cin>>end;
}
}

void rent(vehicle *v,int &size,Users &u){
    int  select;
    for(int i=0;i<size;i++){
        cout<<i+1<<". Model:"<<v[i].getModel()<<endl<<"   Rent per Day:"<<v[i].getRPD()<<endl<<endl;
    }
    cin>>select;
    if(u.GetLT()=="Full-License" || (u.GetLT()=="Intermediate" && v[select].getEligibility()!="Full-License") 
    || u.GetLT()==v[select].getEligibility()){
        cout<<v[select].getModel()<<" was selected"<<endl;
        size--;
        for(int j=select;j<size-1;j++){
            v[j]=v[j+1];
        }
    }
    else{
        cout<<"Not Eligible"<<endl;
    }
};

int main(){
    vehicle *v=nullptr;
    int size=5;
    v=new vehicle[size];
    v[0]=vehicle("Toyota Corolla",19.4,"Learner");
    v[1]=vehicle("Honda Civic",30.2,"Learner");
    v[2]=vehicle("Ford Mustang",50.2,"Intermediate");
    v[3]=vehicle("BMW X5",101,"Full-License");
    v[4]=vehicle("Tesla Model S",84.5,"Full-License");
    int age,id;
    string Lt,Ci;
    cout<<"Enter the age:";
    cin>>age;
    cout<<"Enter the Contact information:";
    cin>>Ci;
    cout<<"Enter the License information(Learner,Intermediate,Full-License):";
    cin>>Lt;
    cout<<"Enter the user id:";
    cin>>id;
    Users  user(age,Lt,Ci,id);

    int end=1;
    int opt;
    while(end){
        cout<<"Enter 1 for update user detail:"<<endl;
        cout<<"Enter 2 for Renting car:"<<endl;
        cout<<"Enter 3 for close:"<<endl;
        cin>>opt;
        switch (opt)
        {
        case 1:
            update(user);
            break;
        case 2:
            rent(v,size,user);
            break;
        case 3:
            return 0;
            break;
        default:
            break;
        }
    }
}