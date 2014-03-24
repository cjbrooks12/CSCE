class Questions {
private:
    string question;
    vector<string> possible_answers;
    int question_number, correct_answer;

public:
    //constructors
    Questions();
    Questions(string q, vector<string> a, int c, int n);

    //setter functions
    void set_question(string q);
    void add_answer(string a);
    void set_answers(vector<string> a);
    void set_correct_answer(int c);
    void set_question_number(int n);

    //getter functions
    string get_question() const {return question; }
    vector<string> get_possible_answers() const {return possible_answers; }
    int get_correct_answer() const {return correct_answer; }
    int get_question_number() const {return question_number; }
    
    //misc functions
    void save_to_file();
};
    
//nonmember operators
ostream& operator<<(ostream& out, const Questions& vec);
istream& operator>>(istream& in, Questions& q);
bool operator==(const Questions& a, const Questions& b);






