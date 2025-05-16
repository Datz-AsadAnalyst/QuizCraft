#include <iostream>
#include <fstream>
#include <sstream>
#include<string>
#include <vector>
#include <set>
#include <regex>
#include <algorithm>


using namespace std;

string currentUser;

void checkLibraryIncludes(const  string& code,  vector< string>& errors);
void checkSemicolons(const  string& code,  vector< string>& errors);
void checkVariableNames(const  string& code,  vector< string>& errors);

class Leaderboard {
private:
    vector<pair<string, int>> scores;
    string currentUser;
public:
    void writeScoresToFile() const;
    void display() const;
    void addScore(const string& user, int score);
    void saveToFile() const;
    void loadFromFile();
    int getUserScore(const string& user) const;
};

void Leaderboard::writeScoresToFile() const {
    fstream file("leaderboard.txt", ios::out);
    if (!file.is_open()) {
        cout << "Error opening file for writing leaderboard!" << endl;
        return;
    }
    for (const auto& entry : scores) {
        file << entry.first << " " << entry.second << endl;
    }
    file.close();
}

void Leaderboard::display() const {
    cout << "\t\t\t Leaderboard \n";
    cout << "\t\t\t ------------ \n";
    for (const auto& entry : scores) {
        if (entry.first == currentUser) {
            cout << "* User: " << entry.first << ", Score: " << entry.second << " *" << endl; // Highlight current user
        } else {
            cout << "User: " << entry.first << ", Score: " << entry.second << endl;
        }
    }
}

void Leaderboard::addScore(const string& user, int score) {
    bool userFound = false;
    for (auto& entry : scores) {
        if (entry.first == user) {
            entry.second += score;
            userFound = true;
            break;
        }
    }
    if (!userFound) {
        scores.push_back(make_pair(user, score));
    }
    cout << endl << "Added Score: User=" << user << ", Score= " << score << endl;
}

void Leaderboard::saveToFile() const {
    writeScoresToFile();
}

void Leaderboard::loadFromFile() {
    fstream file("leaderboard.txt", ios::in);
    if (!file.is_open()) {
        cout << "Error opening leaderboard file!" << endl;
        return;
    }
    scores.clear();
    string user;
    int score;
    while (file >> user >> score) {
        scores.push_back(make_pair(user, score));
    }
    file.close();
}

int Leaderboard::getUserScore(const string& user) const {
    for (const auto& entry : scores) {
        if (entry.first == user) {
            return entry.second;
        }
    }
    return 0; // Default score if user is not found
}

Leaderboard leaderboard;

class User {
public:
    string userID, password;
    
    void registerUser() {
        system("cls");
        cout << "\t\t\t Please Register Yourself: "<<endl;
        cout << "\t\t\t USERNAME: ";
        cin >> userID;
        cout << "\t\t\t PASSWORD: ";
        cin >> password;

        ofstream f1("records.txt", ios::app);
        f1 << userID << ' ' << password << endl;
        system("cls");
        f1.close();
        cout << "\t\t\t Successfully Registered!\n";
        loginUser();
    }

    bool loginUser() {
        string id, pass;
        system("cls");
        cout << "\t\t\t Please Login Your Account"<<endl;;
        cout << "\t\t\t USERNAME: ";
        cin >> userID;
        cout << "\t\t\t PASSWORD: ";
        cin >> password;

        ifstream input("records.txt");
        while (input >> id >> pass) {
            if (userID == id && password == pass) {
            	currentUser = id;
                input.close();
                system("cls");
                cout << "\t\t\t Successfully Logged In! \n\n";
                return true;
            }
        }
        input.close();
        cout << "\t\t\t INVALID USERNAME OR PASSWORD! \n\n";
        return false;
    }
};

class Quiz {
public:
    char quizLevel;

    void startQuiz() {
        cout << "\t| Press B for Beginner     level |\n";
        cout << "\t| Press I for Intermediate level |\n";
        cout << "\t| Press A for Advanced     level |\n";
        cout << "\t\t\t Enter Your Choice : ";
        cin >> quizLevel;

        switch (quizLevel) {
            case 'B':
			case 'b': {
                beginner();
                break;
            }
            case 'I':
			case 'i': {
                intermediate();
                break;
            }
            case 'A':
			case 'a': {
                advance();
                break;
            }
            default: {
                system("cls");
                cout << "\t\t\t Please select a valid option: \n\n";
                startQuiz();
            }
        }
    }

private:
    struct Question {
        string question;
        string answer;
    };

    void beginner() {
    	quizLevel= 'B';
        const int numQuestions = 5;
        Question questions[numQuestions] = {
            {"How many Types of Programming Language are there?", "Two"},
            {"Name any one type of Programming Language.", "High level or Low level"},
            {"C++ is Developed by?", "Bjarne"},
            {"C++ is Developed at?", "Bell lab"},
            {"C++ is Developed in?", "1980"}
        };
        
        int indexes[numQuestions] = {0, 1, 2, 3, 4};

		srand(time(0));
        for (int i = 0; i < numQuestions; ++i) {
            int randIndex = rand() % numQuestions;
            swap(indexes[i], indexes[randIndex]);
        }

        string ans;
        for (int i = 0; i < numQuestions; ++i) {
            int qIndex = indexes[i];
            
            if(i==0){
            cout << "\t\t\t Welcome to C++ Beginner QUIZZZZZ " << endl;
			cin.ignore();	
			}
            cout << questions[qIndex].question << endl;
            getline(cin,ans);
            
            cout << "You answered: '" << ans << "'" << endl;
            
            if (questions[qIndex].question == "Name any one type of Programming Language.") {
                if (ans != "High level" && ans != "Low level") {
                    cout << "Expected 'High level' or 'Low level'" << endl;
					retake();
                    return;
                }
            } else {
                if (ans != questions[qIndex].answer) {
                    cout << "Expected: '" << questions[qIndex].answer << "'" << endl;
					retake();
                    return;
                }
                
            }
        }

        system("cls");
        leaderboard.addScore(currentUser, 5); 
       	leaderboard.saveToFile();
        cout << "\n\n \t\t\t!!!!!Congratulations!!!!! \n\n";
        intermediate();
    }

    void intermediate() {
    	quizLevel='I';
        string ans;
        cout << "\t\t\t Welcome to C++ Intermediate  QUIZZZZZ " << endl;
        cout << "Question NO 1:" << endl;
        cout << "How to declare a variable in C++...........?" << endl;
        cin >> ans;
        if (ans == "datatype_variablename_=_value;") {
            system("cls");
            cout << "Question NO 2" << endl;
            cout << "In How many ways can we initialize Variable in C++......" << endl;
            cin >> ans;
            if (ans == "Two") {
                cout << "Question No 3" << endl;
                cout << "Increments Type" << endl;
                cin >> ans;
                if (ans == "Two") {
                    cout << "\n\n \t\t!!!!!Congratulations!!!!!\n\n";
                    leaderboard.addScore(currentUser, 5);
       				leaderboard.saveToFile();
                    advance();
                } else {
                    retake();
                }
            } else {
                retake();
            }
        } else {
            retake();
        }
    }

    void advance() {
    	quizLevel='A';
    	
    	string userProgramPath;
    cout << "\t\t\t Welcome to C++ Advanced  QUIZZZ" << endl;
	cout << "Enter the path to the user's program file: ";
    cin.ignore(); 
    getline(cin, userProgramPath);
    	
    ifstream file(userProgramPath);

    if (!file.is_open()) {
         cerr << "Error: Could not open the file!" <<  endl;
    }

     string code(( istreambuf_iterator<char>(file)),  istreambuf_iterator<char>());
    file.close();

     vector< string> errors;

    checkVariableNames(code, errors);
checkSemicolons(code, errors);
    checkLibraryIncludes(code, errors);

    if (errors.empty()) {
        cout << "Your program is great!" <<  endl;
    	leaderboard.addScore(currentUser, 10);
    	leaderboard.saveToFile();
    } else {
        for (const auto& error : errors) {
             cout << error <<  endl;
        }
    }
    
}

    void retake() {
        char ch;
        cout << "\t\t\t  ohhhhhhhh Wrong Answer !!!\n\n";
        cout << "\t| Press R for Retake Quiz        |\n";
        cout << "\t| Press L for Learning Path      |\n";
        cin >> ch;
        if (ch == 'R' || ch== 'r') {
        cout << "\t| Which Level you want to retake"<<endl ;
        cout << "\t| Press B for Beginner     level |\n";
        cout << "\t| Press I for Intermediate level |\n";
        cout << "\t| Press A for Advanced     level |\n";
        cout << "\t\t\t Enter Your Choice : ";
        cin >> quizLevel;
            if (quizLevel == 'B') {
                beginner();
            } else if (quizLevel == 'I') {
                intermediate();
            } else {
                advance();
            }
        } else {
            cout << "https://www.w3schools.com/cpp/";
        }
    }
};

class QuizApp {
public:
    void run() {
        int choice;
        while (true) {
            showMenu();
            cin >> choice;
            switch (choice) {
                case 1: {
                    if (user.loginUser()) {
                        quiz.startQuiz();
                    }
                    break;
                }
                case 2: {
                    user.registerUser();
                    quiz.startQuiz();
                    break;
                }
                case 3: {
                    system("cls");
                    cout << "\t\t\t   THANK YOU! \n\n ";
                    return;
            	}
            	case 4: {
    				leaderboard.loadFromFile();
    	 			leaderboard.display();
        			break;
    			}
                default: {
                    system("cls");
                    cout << "\t\t\t Please select a valid option: \n\n";
                }
            }
        }
    }

private:
    User user;
    Quiz quiz;

    void showMenu() {
        cout << "\t\t\t_____________________________________________________\n\n\n";
        cout << "\t\t\t            Welcome to the Login Page                \n\n\n";
        cout << "\t\t\t________________     MENU   _________________________\n\n\n";
        cout << "                                                             \n\n";
        cout << "\t| Press 1 to LOGIN            |\n";
        cout << "\t| Press 2 to REGISTER         |\n";
        cout << "\t| Press 3 to EXIT             |\n";
   		cout << "\t| Press 4 to VIEW LEADERBOARD |\n";
        cout << "\n\t\t\t Please Enter your Choice : ";
    }
};

void checkVariableNames(const string& code, vector<string>& errors) {
    istringstream stream(code);
    string word;
    int lineNumber = 1;
    regex variablePattern(R"((int|float|double|char|string)\s+([a-zA-Z_]\w*))");

    while ( getline(stream, word)) {
         smatch matches;
        if ( regex_search(word, matches, variablePattern)) {
             string variableName = matches[2];
            if (! isalpha(variableName[0])) {
                errors.push_back("Error on line " +  to_string(lineNumber) + ": Variable '" + variableName + "' does not start with an alphabetic letter.");
            }
        }
        lineNumber++;
    }
};

void checkSemicolons(const  string& code,  vector< string>& errors) {
     istringstream stream(code);
     string word;
    int lineNumber = 1;

    while ( getline(stream, word)) {
         string trimmed = word;
        trimmed.erase(trimmed.find_last_not_of(" \n\r\t") + 1); // Trim trailing whitespace
        if (!trimmed.empty() && trimmed.back() != ';' && 
            (trimmed.find("int ") !=  string::npos || 
             trimmed.find("float ") !=  string::npos || 
             trimmed.find("double ") !=  string::npos || 
             trimmed.find("char ") !=  string::npos || 
             trimmed.find(" string ") !=  string::npos || 
             trimmed.find("return") !=  string::npos)) {
            errors.push_back("Error on line " +  to_string(lineNumber) + ": Missing semicolon.");
        }
        lineNumber++;
    }
};

void checkLibraryIncludes(const  string& code,  vector< string>& errors) {
     set< string> requiredLibraries = {"<iostream>", "<vector>", "<string>"};
     istringstream stream(code);
     string line;
     set< string> includedLibraries;
    int lineNumber = 1;

    while ( getline(stream, line)) {
         regex includePattern(R"(^\s*#include\s*(<[^>]+>|"[^"]+")\s*)");
         smatch matches;
        if ( regex_search(line, matches, includePattern)) {
            includedLibraries.insert(matches[1]);
        }
        lineNumber++;
    }

    for (const auto& lib : requiredLibraries) {
        if (includedLibraries.find(lib) == includedLibraries.end()) {
            errors.push_back("Error: Missing required library " + lib);
        }
    }
};


int main() {
    QuizApp app;
    app.run();
    return 0;
}
