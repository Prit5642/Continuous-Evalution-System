// PRIT SHAH
#include <bits/stdc++.h>
#include <math.h>
#define jaldi_kar ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

#define aavade(a, n)            \
    for (int i = 0; i < n; i++) \
    cin >> a[i]
#define aavade2(a, b, n)        \
    for (int i = 0; i < n; i++) \
    cin >> a[i] >> b[i]
#define Vaavade(a, n)           \
    for (int i = 0; i < n; i++) \
    {                           \
        int x;                  \
        cin >> x;               \
        a.emplace_back(x);      \
    }
#define aavadeM(a, n, m)            \
    for (int i = 0; i < n; i++)     \
        for (int j = 0; j < m; j++) \
    cin >> a[i][j]
#define jawade(a, n)            \
    for (int i = 0; i < n; i++) \
    cout << a[i] << ' '

#define IO                            \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout)

#define laile cin >>
#define daide cout <<
#define MAX 1000000007
#define ll long long int
#define f(i, x, n) for (int i = x; i < n; i++)
#define fl(i, x, n) for (ll i = x; i < n; i++)
#define all(v) v.begin(), v.end()
#define eb emplace_back
#define pb push_back
#define nodgt(n) (int)log10(n) + 1
#define lcm(a, b) (a * b) / __gcd(a, b)
using namespace std;

class Student
{
public:
    string roll;
    string name;
    string course;
    int classTest;
    int sessional;
    int innovative;
    int sem;
    float gpa;
    int tgpa;

    Student() : classTest(0), sessional(0), innovative(0), sem(0) {}

    Student(string roll, string name, string course, int classTest, int sessional, int innovative, int sem)
    {
        this->roll = roll;
        this->name = name;
        this->course = course;
        this->classTest = classTest;
        this->sessional = sessional;
        this->innovative = innovative;
        this->sem = sem;
    }
    friend ostream &operator<<(ostream &os, const Student &s)
    {
        return os << "    Name : " << s.name << "\n    Roll No. : " << s.roll << '\n';
    }
};

class CESystem
{
private:
    map<string, vector<Student>> coursesmpp;
    map<string, Student> students;
    priority_queue<pair<string, int>> pq;
    double calculateStandardDeviation(const vector<int> &marks)
    {
        double mean = static_cast<double>(accumulate(marks.begin(), marks.end(), 0)) / marks.size();
        double variance = 0.0;
        for (int mark : marks)
        {
            variance += pow(mark - mean, 2);
        }
        return sqrt(variance / marks.size());
    }
    int calculate(float total)
    {
        if (total >= 90)
        {
            return 10;
        }
        else if (total >= 80 && total < 90)
        {
            return 9;
        }
        else if (total >= 70 && total < 80)
        {
            return 8;
        }
        else if (total >= 60 && total < 70)
        {
            return 7;
        }
        else if (total >= 50 && total < 60)
        {
            return 6;
        }
        else if (total >= 40 && total < 50)
        {
            return 5;
        }
        else if (total >= 30 && total < 40)
        {
            return 4;
        }
        else if (total >= 20 && total < 30)
        {
            return 3;
        }
        else if (total >= 10 && total < 20)
        {
            return 2;
        }
        return 1;
    }

public:
    void addStudent(string roll, string name, string course, int classTest, int sessional, int innovative, int sem)
    {
        Student s(roll, name, course, classTest, sessional, innovative, sem);
        students[s.roll] = s;
        coursesmpp[s.course].push_back(s);
    }

    void calculateGPA(string roll)
    {
        bool f = false;
        float gpa;
        for (auto it : coursesmpp)
        {
            float total = 0;
            for (int i = 0; i < it.second.size(); i++)
            {
                if (it.second[i].roll == roll)
                {
                    f = true;
                    cout << "Enter the SEE marks for " << it.second[i].course << " : ";
                    int semend;
                    cin >> semend;
                    cout << "Enter the Total LPW marks for " << it.second[i].course << " : ";
                    int lpw;
                    cin >> lpw;
                    total += (semend * 0.4 + lpw * 0.3);
                    total += ((it.second[i].classTest + it.second[i].sessional * 0.6 + it.second[i].innovative) * 0.3);
                    cout << total << '\n';
                    int sub = calculate(total);
                    gpa += sub;
                    it.second[i].gpa = sub;
                }
            }
        }

        if (f == false)
        {
            cout << "Details of Student with Roll No. " << roll << " does not exist";
        }
        else
        {
            gpa = gpa / 6;
            students[roll].tgpa = gpa;
            cout << students[roll];
            cout << "\n    GPA: " << gpa << '\n';
            pq.emplace(roll, gpa);
        }
    }

    void rankStudents()
    {
        cout << "Ranking of Students based on GPA :\n";
        if (pq.size() >= 5)
        {
            cout << "Showing Top 5 Students :\n";
        }
        else
        {
            cout << "Showing Top " << pq.size() << " Students :\n";
        }
        int rank = 1;
        while (!pq.empty() && rank <= 5)
        {
            Student student = students[pq.top().first];
            cout << "Rank " << rank << ": \n";
            cout << student;
            cout << "   GPA : " << pq.top().second;
            pq.pop();
            cout << '\n';
            rank++;
        }
    }
    void dispStudDetails(string rollNo)
    {

        bool f = false;
        float a = students[rollNo].tgpa;
        for (auto course : coursesmpp)
        {
            vector<Student> v = course.second;

            for (auto st : v)
            {
                if (st.roll == rollNo)
                {
                    f = true;
                    cout << "\n----------------------x x x x x x x x x x x x-----------------------\n";
                    cout << st;
                    cout << "    Class Test marks for " << course.first << " : " << st.classTest << '\n';
                    cout << "    Sessional Test marks for " << course.first << " : " << st.sessional << '\n';
                    cout << "    Innovative Assignment marks for " << course.first << " : " << st.innovative << '\n';

                    cout << "\n----------------------x x x x x x x x x x x x-----------------------\n";
                }
            }
        }

        if (f == false)
        {
            cout << "Student with Roll No " << rollNo << " not found."
                 << "\n";
        }
        else
        {
            cout << "\n   Overall GPA : " << a << '\n';
            cout << "\n\n----------------------x x x x x x x x x x x x-----------------------\n\n";
        }
    }
    void dispCourseStats(string course)
    {
        if (coursesmpp.find(course) != coursesmpp.end())
        {
            vector<Student> &studInC = coursesmpp[course];
            cout << "\nStatistics for Course " << course << ":\n";
            vector<int> classTestMarks, sessionalMarks, innovativeAssignmentMarks;

            for (const Student &student : studInC)
            {
                classTestMarks.push_back(student.classTest);
                sessionalMarks.push_back(student.sessional);
                innovativeAssignmentMarks.push_back(student.innovative);
            }

            double classTestAverage = static_cast<double>(accumulate(classTestMarks.begin(), classTestMarks.end(), 0)) / studInC.size();
            double sessionalAverage = static_cast<double>(accumulate(sessionalMarks.begin(), sessionalMarks.end(), 0)) / studInC.size();
            double innovativeAssignmentAverage = static_cast<double>(accumulate(innovativeAssignmentMarks.begin(), innovativeAssignmentMarks.end(), 0)) / studInC.size();

            double classTestMin = *min_element(classTestMarks.begin(), classTestMarks.end());
            double classTestMax = *max_element(classTestMarks.begin(), classTestMarks.end());

            double sessionalMin = *min_element(sessionalMarks.begin(), sessionalMarks.end());
            double sessionalMax = *max_element(sessionalMarks.begin(), sessionalMarks.end());

            double innovativeAssignmentMin = *min_element(innovativeAssignmentMarks.begin(), innovativeAssignmentMarks.end());
            double innovativeAssignmentMax = *max_element(innovativeAssignmentMarks.begin(), innovativeAssignmentMarks.end());

            double classTestStdDev = calculateStandardDeviation(classTestMarks);
            double sessionalStdDev = calculateStandardDeviation(sessionalMarks);
            double innovativeAssignmentStdDev = calculateStandardDeviation(innovativeAssignmentMarks);

            cout << fixed << setprecision(2);
            cout << "Class Test: Avg: " << classTestAverage << ", Min: " << classTestMin << ", Max: " << classTestMax << ", Std Dev: " << classTestStdDev << "\n";
            cout << "Sessional: Avg: " << sessionalAverage << ", Min: " << sessionalMin << ", Max: " << sessionalMax << ", Std Dev: " << sessionalStdDev << "\n";
            cout << "Innovative Assignment: Avg: " << innovativeAssignmentAverage << ", Min: " << innovativeAssignmentMin << ", Max: " << innovativeAssignmentMax << ", Std Dev: " << innovativeAssignmentStdDev << "\n";
        }
        else
        {
            cout << "Course " << course << " not found."
                 << "\n";
        }
    }

    void generateFailCour(string course)
    {
        string s = course + "fail.csv";
        ofstream file(s);
        vector<Student> v = coursesmpp[course];
        file << "Roll No,Name,Remarks,Course Code,Class Test Marks,Sessional Marks,Innovative Assignment Marks,Semester\n";
        for (auto st : v)
        {
            if (st.classTest < 8 && st.sessional < 20 && st.innovative < 20)
            {
                file << st.roll << "," << st.name << ",Failed in continuous evaluation," << st.course << "," << st.classTest << "," << st.sessional << "," << st.innovative << "," << st.sem << "\n";
            }
            else if (st.classTest < 8)
            {
                file << st.roll << "," << st.name << ",Failed in Class Test," << st.course << "," << st.classTest << "," << st.sessional << "," << st.innovative << "," << st.sem << "\n";
            }
            else if (st.sessional < 20)
            {
                file << st.roll << "," << st.name << ",Failed in Sessional Test," << st.course << "," << st.classTest << "," << st.sessional << "," << st.innovative << "," << st.sem << "\n";
            }
            else if (st.innovative < 20)
            {
                file << st.roll << "," << st.name << ",Failed in Innovative Assignment Test," << st.course << "," << st.classTest << "," << st.sessional << "," << st.innovative << "," << st.sem << "\n";
            }
        }
    }

    void generateFailSem(string course, int sem)
    {
        string s = course + "semfail.csv";
        ofstream file(s);
        vector<Student> v = coursesmpp[course];
        file << "Roll No,Name,Remarks,Course Code,Class Test Marks,Sessional Marks,Innovative Assignment Marks,Semester\n";
        for (auto st : v)
        {
            if (st.sem == sem)
            {
                if (st.classTest < 8 && st.sessional < 20 && st.innovative < 20)
                {
                    file << st.roll << "," << st.name << ",Failed in continuous evaluation," << st.course << "," << st.classTest << "," << st.sessional << "," << st.innovative << "," << st.sem << "\n";
                }
                else if (st.classTest < 8)
                {
                    file << st.roll << "," << st.name << ",Failed in Class Test," << st.course << "," << st.classTest << "," << st.sessional << "," << st.innovative << "," << st.sem << "\n";
                }
                else if (st.sessional < 20)
                {
                    file << st.roll << "," << st.name << ",Failed in Sessional Test," << st.course << "," << st.classTest << "," << st.sessional << "," << st.innovative << "," << st.sem << "\n";
                }
                else if (st.innovative < 20)
                {
                    file << st.roll << "," << st.name << ",Failed in Innovative Assignment Test," << st.course << "," << st.classTest << "," << st.sessional << "," << st.innovative << "," << st.sem << "\n";
                }
            }
        }
    }

    void updateMarks(string course, string rollNo)
    {
        for (int i = 0; i < coursesmpp[course].size(); i++)
        {
            if (coursesmpp[course][i].roll == rollNo)
            {
                int m1, m2, m3;
                cout << "Enter the Class Test marks for updation : ";
                cin >> m1;
                cout << "Enter the Sessional Test marks for updation : ";
                cin >> m2;
                cout << "Enter the Innovative Assignment marks for updation : ";
                cin >> m3;
                coursesmpp[course][i].classTest = m1;
                coursesmpp[course][i].sessional = m2;
                coursesmpp[course][i].innovative = m3;
                break;
            }
        }
    }
    void deleteMarks(string course, string rollNo)
    {
        for (int i = 0; i < coursesmpp[course].size(); i++)
        {
            if (coursesmpp[course][i].roll == rollNo)
            {
                coursesmpp.erase(course);
                break;
            }
        }
    }
};

int main()
{
    CESystem cesystem;
    cout << "Enter the number of entries: ";
    int n;
    cin >> n;

    vector<string> courses = {"1MU803", "2HS302", "2CS501", "2CS502", "2CS507", "2CS802"};
    ofstream file("StudentDatabase.csv");
    ofstream file1("2CS501.csv");
    ofstream file2("2CS502.csv");
    ofstream file3("2CS507.csv");
    ofstream file4("2CS802.csv");
    ofstream file5("1MU803.csv");
    ofstream file6("2HS302.csv");

    file << "Roll No,Name,Course Code,Class Test Marks,Sessional Marks,Innovative Assignment Marks,Semester\n";
    file1 << "Roll No,Name,Class Test Marks,Sessional Marks,Innovative Assignment Marks,Semester\n";
    file2 << "Roll No,Name,Class Test Marks,Sessional Marks,Innovative Assignment Marks,Semester\n";
    file3 << "Roll No,Name,Class Test Marks,Sessional Marks,Innovative Assignment Marks,Semester\n";
    file4 << "Roll No,Name,Class Test Marks,Sessional Marks,Innovative Assignment Marks,Semester\n";
    file5 << "Roll No,Name,Class Test Marks,Sessional Marks,Innovative Assignment Marks,Semester\n";
    file6 << "Roll No,Name,Class Test Marks,Sessional Marks,Innovative Assignment Marks,Semester\n";
    for (int i = 0; i < n; i++)
    {
        string roll, name;
        int classTest, sessional, innovative, sem;
        cout << "Enter the Roll Number: ";
        cin >> roll;
        cout << "Enter the Name of " << roll << ": ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter the semester for " << roll << ": ";
        cin >> sem;
        for (int i = 0; i < 6; i++)
        {
            string course;
            cout << "Enter course code : ";
            cin >> course;
            cout << "Enter the Marks of Class Test for " << roll << " in " << course << ": ";
            cin >> classTest;
            cout << "Enter the Marks of Sessional Exam for " << roll << " in " << course << ": ";
            cin >> sessional;
            cout << "Enter the Marks of Innovative Assignment for " << roll << " in " << course << ": ";
            cin >> innovative;

            cesystem.addStudent(roll, name, course, classTest, sessional, innovative, sem);

            file << roll << "," << name << "," << course << "," << classTest << "," << sessional << "," << innovative << "," << sem << "\n";

            if (course == "2CS501")
            {
                file1 << roll << "," << name << "," << classTest << "," << sessional << "," << innovative << "," << sem << "\n";
            }
            else if (course == "2CS502")
            {
                file2 << roll << "," << name << "," << classTest << "," << sessional << "," << innovative << "," << sem << "\n";
            }
            else if (course == "2CS507")
            {
                file3 << roll << "," << name << "," << classTest << "," << sessional << "," << innovative << "," << sem << "\n";
            }
            else if (course == "2CS802")
            {
                file4 << roll << "," << name << "," << classTest << "," << sessional << "," << innovative << "," << sem << "\n";
            }
            else if (course == "1MU803")
            {
                file5 << roll << "," << name << "," << classTest << "," << sessional << "," << innovative << "," << sem << "\n";
            }
            else if (course == "2HS302")
            {
                file6 << roll << "," << name << "," << classTest << "," << sessional << "," << innovative << "," << sem << "\n";
            }
            else
            {
                ofstream fi(course + ".csv");
                fi << roll << "," << name << "," << course << "," << classTest << "," << sessional << "," << innovative << "," << sem << "\n";
            }
        }
        cesystem.calculateGPA(roll);
    }
    file.close();
    file1.close();
    file2.close();
    file3.close();
    file4.close();
    file5.close();
    file6.close();
    // cesystem.dispCourseStats("2CS502");
    cesystem.dispStudDetails("22BCE284");

    cesystem.generateFailCour("2CS501");
    cesystem.generateFailSem("2CS502", 3);
    // cesystem.rankStudents();
    return 0;
}
