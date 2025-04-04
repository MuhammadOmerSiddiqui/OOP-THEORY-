#include <iostream>

using namespace std;

unsigned long hash_passcode(string password) 
{
    unsigned long hash_value = 5381;
    for (char ch : password) 
    {
        hash_value = (hash_value * 33) + ch;
    }
    return hash_value;
}

class User {
public:
    string user_name;
    int user_id;
    string user_email;
    unsigned long hashed_password;
    string user_permissions[3];

    User(string name, int id, string email, string password, string perm1 = "", string perm2 = "", string perm3 = "") 
        : user_name(name), user_id(id), user_email(email), hashed_password(hash_passcode(password)) 
    {
        user_permissions[0] = perm1;
        user_permissions[1] = perm2;
        user_permissions[2] = perm3;
    }

    virtual void display() 
    {
        cout << "Name: " << user_name << endl << "ID: " << user_id << endl << "Email: " << user_email << endl;
    }

    bool validate_password(string password) 
    {
        return hash_passcode(password) == hashed_password;
    }

    bool has_permission(string permission) 
    {
        for (int i = 0; i < 3; i++) 
        {
            if (user_permissions[i] == permission) 
                return true;
        }
        return false;
    }

    virtual bool has_lab_access()
    {
        if (has_permission("full_lab_access")) 
        {
            cout << user_name << " has full access to the lab." << endl;
            return true;
        } 
        else 
        {
            cout << user_name << " does not have lab access." << endl;
            return false;
        }
    }
};

class Student : public User 
{
public:
    int assignments[5];

    Student(string name, int id, string email, string password) 
        : User(name, id, email, password, "submit_assignment") 
    {
        for (int i = 0; i < 5; i++) 
        {
            assignments[i] = 0;
        }
    }

    void submit_assignment(int index) 
    {
        if (index >= 0 && index < 5) 
        {
            assignments[index] = 1;
            cout << "Assignment " << index + 1 << " submitted by " << user_name << "." << endl;
        } 
        else 
        {
            cout << "Invalid assignment index." << endl;
        }
    }

    void display() override 
    {
        User::display();
        cout << "Assignments: ";
        for (int i = 0; i < 5; i++) 
        {
            cout << assignments[i] << " ";
        }
        cout << endl;
    }
};

class Teaching_Assistant : public Student 
{
public:
    string assigned_students[10];
    int student_counter;
    string assigned_projects[2];
    int project_counter;

    Teaching_Assistant(string name, int id, string email, string password) 
        : Student(name, id, email, password) 
    {
        user_permissions[1] = "view_projects";
        user_permissions[2] = "manage_students";
        student_counter = 0;
        project_counter = 0;
    }

    void assign_student(string student_name) 
    {
        if (student_counter < 10) 
        {
            assigned_students[student_counter++] = student_name;
            cout << student_name << " assigned to TA " << user_name << endl;
        } 
        else 
        {
            cout << "TA " << user_name << " cannot manage more than 10 students." << endl;
        }
    }

    void add_project(string project_name) 
    {
        if (project_counter < 2) 
        {
            assigned_projects[project_counter++] = project_name;
            cout << "TA " << user_name << " started working on project: " << project_name << endl;
        } 
        else 
        {
            cout << "TA " << user_name << " is already working on 2 projects." << endl;
        }
    }

    void display() override 
    {
        Student::display();
        cout << "Assigned Students: ";
        for (int i = 0; i < student_counter; i++) 
        {
            cout << i + 1 << ". " << assigned_students[i] << endl;
        }
        cout << "Projects: ";
        for (int i = 0; i < project_counter; i++) 
        {
            cout << assigned_projects[i] << " ";
        }
        cout << endl;
    }
};

class Professor : public User 
{
public:
    Professor(string name, int id, string email, string password) 
        : User(name, id, email, password, "assign_projects", "full_lab_access") {}

    void assign_project(Teaching_Assistant& ta, string project_name) 
    {
        ta.add_project(project_name);
    }

    void display() override 
    {
        User::display();
        cout << "Professor with full lab access." << endl;
    }
};

void validate_and_perform_action(User* user, string password, string action) 
{
    if (user->validate_password(password)) 
    {
        cout << "Authentication successful for " << user->user_name << "." << endl;
        if (user->has_permission(action)) 
        {
            cout << "Action permitted: " << action << "." << endl;
        } 
        else 
        {
            cout << "Action denied: " << action << "." << endl;
        }
    } 
    else 
    {
        cout << "Authentication failed for " << user->user_name << "." << endl;
    }
}

int main() 
{
    Student student_1("Omer", 240022, "omer@university.edu", "password123");
    Teaching_Assistant ta_1("Mr_TA", 249807, "ta@university.edu", "securepass");
    Professor professor_1("Dr_Khalid", 224567, "khalid@university.edu", "professorpass");
    
    student_1.display();
    validate_and_perform_action(&student_1, "password123", "submit_assignment");
    validate_and_perform_action(&ta_1, "securepass", "manage_students");
    validate_and_perform_action(&professor_1, "professorpass", "assign_projects");
    
    student_1.submit_assignment(1);
    student_1.display();
    
    ta_1.assign_student("Omer");
    ta_1.add_project("AI Research");
    ta_1.display();
    
    return 0;
}
