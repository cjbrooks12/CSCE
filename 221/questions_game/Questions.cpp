#include "std_lib_facilities.h"
#include "Questions.h"
using namespace std;

//constructors
//------------------------------------------------------------------------------
    Questions::Questions() {
        question = "";
        correct_answer = 0;
        question_number = 0;
    }
        
    Questions::Questions(string q, vector<string> a, int c, int n) {
        if(a.size() <= 6) {
            question = q;
            possible_answers = a;
            correct_answer = c;
            question_number = n;
        }
        else error("maximum of 6 possible answers allowed");
    }

//setter functions
//------------------------------------------------------------------------------
    void Questions::set_question(string q) {
        question = q;
    }
    
    void Questions::add_answer(string a) {
        if(possible_answers.size() < 5) {
            possible_answers.push_back(a);
        }
        else error("maximum of 5 possible answers allowed");
    }
    
    void Questions::set_answers(vector<string> a) {
        if(a.size() < 5) {
            possible_answers = a;
        }
        else error("maximum of 5 possible answers allowed");
    }
    
    //{1=a, 2=b, 3=c, 4=d, 5=e}
    void Questions::set_correct_answer(int c) {
        correct_answer = c;
    }
    
    void Questions::set_question_number(int n) {
        question_number = n;
    }
    
//misc functions
//------------------------------------------------------------------------------
    void Questions::save_to_file() {
        ofstream ofs("sample_questions.txt");    
        if(!ofs) error("cannot open appointments file");
        
        ofs << "q: " << question << "; ";
        ofs << "c: " << correct_answer << "; a: ";
        for(int i = 0; i < possible_answers.size(); ++i) {
            ofs << possible_answers[i] << "; ";
        }
        ofs << endl;
        
        ofs.close();
    }
    
//operators
//------------------------------------------------------------------------------
ostream& operator<<(ostream& out, const Questions& q) {
    vector<string> a = q.get_possible_answers();
    out << "(" << q.get_question_number() << ") " << q.get_question() << endl;
    for(int i = 0; i < a.size(); ++i) {
        switch(i) {
            case 0: 
                out << "\t a. "; 
                break;
            case 1: 
                out << "\t b. ";
                break;
            case 2: 
                out << "\t c. ";
                break;
            case 3: 
                out << "\t d. ";
                break;
            case 4: 
                out << "\t e. ";
                break;
        }
        out << a[i] << endl;
    }
    return out;
}

istream& operator>>(istream& is, Questions& q) {
    char ch1, ch2, ch3;
    int correct;
    string question, answer;
    
    //reads in the question
    is >> ch1 >> ch2;
    if(ch1 != 'q' || ch2 != ':') { 
		cout << "formatting error\n";
		is.clear(ios_base::failbit);
		return is;
	}
	getline(is, question, ';');
	q.set_question(question);
	
	//reads in the correct answer
    is >> ch1 >> ch2 >> correct >> ch3;
    if(ch1 != 'c' || ch2 != ':' || ch3 != ';' || correct > 5 || correct < 1) { 
		cout << "formatting error\n";
		is.clear(ios_base::failbit);
		return is;
	}
	q.set_correct_answer(correct);
	
	//reads in the possible answers
	is >> ch1 >> ch2;
    if(ch1 != 'a' || ch2 != ':') { 
		cout << "formatting error\n";
		is.clear(ios_base::failbit);
		return is;
	}
	int i = 0;
	while(is.good() && i < 6) {
    	getline(is, answer, ';');
    	if(answer == "e") { 
    	    return is;
    	}
    	else {
    	    ++i;
    	    q.add_answer(answer);
    	}
	}
	is.clear(ios_base::goodbit);
	
	
	
	return is;
	
}


bool operator==(Questions& q1, Questions& q2) {
	return q1.get_question() == q1.get_question() 
	    && q2.get_possible_answers() == q2.get_possible_answers();
}


















