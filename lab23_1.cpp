#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades) {
    ifstream file(filename);
    string line;
    
    while(getline(file, line)) {
        
        int pos = line.find(":");
        string name = line.substr(0, pos);
        
        string score_str = line.substr(pos+1);
        
        
        int score1, score2, score3;
        sscanf(score_str.c_str(), "%d %d %d", &score1, &score2, &score3);
        
        
        int total_score = score1 + score2 + score3;
        
        
        names.push_back(name);
        scores.push_back(total_score);
        grades.push_back(score2grade(total_score));
    }
    
    file.close();
}

void getCommand(string &command, string &key) {
    cout << "Please input your command: "<<endl;
    string line;
    getline(cin, line);
    size_t pos = line.find(" ");
    if(pos != string::npos) {
        command = line.substr(0, pos);
        key = line.substr(pos+1);

        while(!key.empty() && isspace(key[0])) {
            key.erase(0, 1);
        }
    } else {
        command = line;
        key = "";
    }
}


void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key) {
    bool found = false;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < names.size(); i++) {
        if(toUpperStr(names[i]) == key) {
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            found = true;
            break;
        }
    }
    if(!found) {
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key) {
    bool found = false;
    cout << "---------------------------------\n";
    char grade_key = key[0];
    grade_key = toupper(grade_key);
    for(unsigned int i = 0; i < grades.size(); i++) {
        if(grades[i] == grade_key) {
            cout << names[i] << " (" << scores[i] << ")" << endl;
            found = true;
        }
    }
    if(!found) {
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
