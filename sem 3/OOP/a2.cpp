#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class student
{
public:
	static int record_count;
	
	string name = "N/A";
    string rollno = "N/A";
    string cname = "N/A";
    string div = "N/A";
    string dob = "N/A";
    string blood = "N/A";
    string add = "N/A";
    string num = "N/A";
    string licence = "N/A";
    
	student(){
		record_count++;
	}
	
	static int getcount(){
		return record_count;
	}
	
	~student(){}
	
    friend class studentinfo;
};

int student::record_count = 0;

class studentinfo
{
public:
    void print_header()
    {
        cout << left << setw(20) << "Name"
             << setw(15) << "Roll No"
             << setw(10) << "Class"
             << setw(10) << "Division"
             << setw(15) << "Date of Birth"
             << setw(15) << "Blood Group"
             << setw(25) << "Address"
             << setw(15) << "Number"
             << setw(20) << "Licence" << endl;

        cout << string(165, '-') << endl;
    }

    void display(student *s)
    {
        cout << left << setw(20) << s->name
             << setw(15) << s->rollno
             << setw(10) << s->cname
             << setw(10) << s->div
             << setw(15) << s->dob
             << setw(15) << s->blood
             << setw(25) << s->add
             << setw(15) << s->num
             << setw(20) << s->licence << endl;

        cout << string(165, '-') << endl;
    }

    void get_data(student *s)
    {
        cout << "Enter name = ";
        cin >> s->name;
        cout << "Enter Roll no = ";
        cin >> s->rollno;
        cout << "Enter class name = ";
        cin >> s->cname;
        cout << "Enter Division = ";
        cin >> s->div;
        cout << "Enter Date of Birth = ";
        cin >> s->dob;
        cout << "Enter Blood Group = ";
        cin >> s->blood;
        cout << "Enter Address = ";
        cin >> s->add;
        cout << "Enter Number = ";
        cin >> s->num;
        cout << "Enter Licence = ";
        cin >> s->licence;
        cout << endl;
        
    }
    
    ~studentinfo(){}
};

int main()
{
    student *s[10];
    studentinfo *si;
    int count = 0;
    int choice;
    char ch;

    do
    {
        s[count] = new student;
        si->get_data(s[count]);
        count++;

        cout << "Add data for more students = ";
        cin >> ch;

        if (ch == 'n' || ch == 'N')
        {
            break;
        }

    } while (count < 10);

    cout << "printing the data" << endl
         << endl;
    si->print_header();
    if (count == 0)
    {
        si->display(new student);
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            si->display(s[i]);
        }
    }
    
    cout << "record count = " << s[0]->getcount() << endl;
    
    return 0;
}