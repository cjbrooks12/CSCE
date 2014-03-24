#include "Questions.cpp"

namespace questions_game {
    vector<Questions> vec_questions;
    list<Questions> list_questions;
    int q_correct, q_missed;
    bool vec = true;
    
    
    void determine_structure() {
        Questions structure;
        structure.set_question("Do you want to use a vector or linked list?");
        structure.add_answer("Vector");
        structure.add_answer("Linked List");
        cout << structure;
        
        char selection;
        if(cin >> selection) {
            switch(selection) {
            case 'A':
            case 'a':
                vec = true;
                cout << "You will now use a vector\n";
                break;
            case 'B':
            case 'b':
                vec = false;
                cout << "You will now use a linked list\n";
                break;
            default:
                error("please select an answer from the options given");
            }
        }
    }
    
//Vector implementation
//------------------------------------------------------------------------------
    void populate_vector_questions() {
        q_correct = 0;
        q_missed = 0;
        Questions q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13, q14, q15;
        
        ifstream ifs("sample_questions.txt");    
        if(!ifs) error("cannot open appointments file");
        
        ifs >> q1 >> q2 >> q3 >> q4 >> q5 >> q6 >> q7>> q8 >> q9 >> q10 >> q11 >> q12>> q13>> q14>> q15;
        vec_questions.push_back(q1);
        vec_questions.push_back(q2);
        vec_questions.push_back(q3);
        vec_questions.push_back(q4);
        vec_questions.push_back(q5);
        vec_questions.push_back(q6);
        vec_questions.push_back(q7);
        vec_questions.push_back(q8);
        vec_questions.push_back(q9);
        vec_questions.push_back(q10);
        vec_questions.push_back(q11);
        vec_questions.push_back(q12);
        vec_questions.push_back(q13);
        vec_questions.push_back(q14);
        vec_questions.push_back(q15);
        
        
        
        ifs.close();
    }
    
    void ask_vector_question() {
        if(vec_questions.size() <= 0) {
            q_missed = -1; //to set condition to terminate loop
            error("No more questions to ask");
        }
        
        char guess;
        int question_number = rand() % vec_questions.size();
        int num_answers = vec_questions[question_number].get_possible_answers().size();
        if(num_answers < 2) {
            cout << "Question " << question_number << " had too few possible "
                << "answers and was removed from the list.\n";
            vec_questions.erase(vec_questions.begin() + question_number);
        }
        vec_questions[question_number].set_question_number(q_missed + q_correct + 1);
        cout << vec_questions[question_number];
        
        if(cin >> guess) {
            switch(guess) {
            case 'A':
            case 'a':
                if(num_answers >= 1) {
                    if(vec_questions[question_number].get_correct_answer() == 1) {
                        ++q_correct;
                        vec_questions.erase(vec_questions.begin() + question_number);
                        cout << "a is correct " << endl;
                    }
                    else {
                        ++q_missed;
                        cout << "a is incorrect, you have missed " << q_missed << " questions\n";
                    }
                }
                else {
                    error("please select an answer from the options given");
                }
                break;
            case 'B':
            case 'b':
                if(num_answers >= 2) {
                    if(vec_questions[question_number].get_correct_answer() == 2) {
                        ++q_correct;
                        vec_questions.erase(vec_questions.begin() + question_number);
                        cout << "b is correct\n";
                    }
                    else {
                        ++q_missed;
                        cout << "b is incorrect, you have missed " << q_missed << " questions\n";
                    }
                }
                else {
                    error("please select an answer from the options given");
                }
                break;
            case 'C':
            case 'c':
                if(num_answers >= 3) {
                    if(vec_questions[question_number].get_correct_answer() == 3) {
                        ++q_correct;
                        vec_questions.erase(vec_questions.begin() + question_number);
                        cout << "c is correct\n";
                    }
                    else {
                        ++q_missed;
                        cout << "c is incorrect, you have missed " << q_missed << " questions\n";
                    }
                }
                else {
                    error("please select an answer from the options given");
                }
                break;
            case 'D':
            case 'd':
                if(num_answers >= 4) {
                    if(vec_questions[question_number].get_correct_answer() == 4) {
                        ++q_correct;
                        vec_questions.erase(vec_questions.begin() + question_number);
                        cout << "d is correct\n";
                    }
                    else {
                        ++q_missed;
                        cout << "d is incorrect, you have missed " << q_missed << " questions\n";
                    }
                }
                else {
                    error("please select an answer from the options given");
                }
                break;
            case 'E':
            case 'e':
                if(num_answers >= 5) {
                    if(vec_questions[question_number].get_correct_answer() == 5) {
                        ++q_correct;
                        vec_questions.erase(vec_questions.begin() + question_number);
                        cout << "e is correct\n";
                    }
                    else {
                        ++q_missed;
                        cout << "e is incorrect, you have missed " << q_missed << " questions\n";
                    }
                }
                else {
                    error("please select an answer from the options given");
                }
                break;
            default:
                error("please select an answer from the options given");
            }
        }
        cout << endl;
    }
    
//Linked List Implementation
//------------------------------------------------------------------------------
    void populate_list_questions() {
        q_correct = 0;
        q_missed = 0;
        Questions q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13, q14, q15;
        
        ifstream ifs("sample_questions.txt");    
        if(!ifs) error("cannot open appointments file");
        
        ifs >> q1 >> q2 >> q3 >> q4 >> q5 >> q6 >> q7>> q8 >> q9 >> q10 >> q11 >> q12>> q13>> q14>> q15;
        list_questions.push_back(q1);
        list_questions.push_back(q2);
        list_questions.push_back(q3);
        list_questions.push_back(q4);
        list_questions.push_back(q5);
        list_questions.push_back(q6);
        list_questions.push_back(q7);
        list_questions.push_back(q8);
        list_questions.push_back(q9);
        list_questions.push_back(q10);
        list_questions.push_back(q11);
        list_questions.push_back(q12);
        list_questions.push_back(q13);
        list_questions.push_back(q14);
        list_questions.push_back(q15);
        
        
        
        ifs.close();
    }
    
    void ask_list_question() {
        if(list_questions.size() <= 0) {
            q_missed = -1; //to set condition to terminate loop
            error("No more questions to ask");
        }
        
        char guess;
        int question_number = rand() % list_questions.size();
        list<Questions>::iterator it = std::next(list_questions.begin(), question_number);
        Questions &my_question = *it;
        int num_answers = my_question.get_possible_answers().size();
        
        if(num_answers < 2) {
            cout << "Question " << question_number << " had too few possible "
                << "answers and was removed from the list.\n";
            list_questions.erase(it);
        }
        my_question.set_question_number(q_missed + q_correct + 1);
        cout << my_question;
        
        if(cin >> guess) {
            switch(guess) {
            case 'A':
            case 'a':
                if(num_answers >= 1) {
                    if(my_question.get_correct_answer() == 1) {
                        ++q_correct;
                        list_questions.erase(it);
                        cout << "a is correct " << endl;
                    }
                    else {
                        ++q_missed;
                        cout << "a is incorrect, you have missed " << q_missed << " questions\n";
                    }
                }
                else {
                    error("please select an answer from the options given");
                }
                break;
            case 'B':
            case 'b':
                if(num_answers >= 2) {
                    if(my_question.get_correct_answer() == 2) {
                        ++q_correct;
                        list_questions.erase(it);
                        cout << "b is correct " << q_correct << endl;
                    }
                    else {
                        ++q_missed;
                        cout << "b is incorrect, you have missed " << q_missed << " questions\n";
                    }
                }
                else {
                    error("please select an answer from the options given");
                }
                break;
            case 'C':
            case 'c':
                if(num_answers >= 3) {
                    if(my_question.get_correct_answer() == 3) {
                        ++q_correct;
                        list_questions.erase(it);
                        cout << "c is correct " << q_correct << endl;
                    }
                    else {
                        ++q_missed;
                        cout << "c is incorrect, you have missed " << q_missed << " questions\n";
                    }
                }
                else {
                    error("please select an answer from the options given");
                }
                break;
            case 'D':
            case 'd':
                if(num_answers >= 4) {
                    if(my_question.get_correct_answer() == 4) {
                        ++q_correct;
                        list_questions.erase(it);
                        cout << "d is correct " << q_correct << endl;
                    }
                    else {
                        ++q_missed;
                        cout << "d is incorrect, you have missed " << q_missed << " questions\n";
                    }
                }
                else {
                    error("please select an answer from the options given");
                }
                break;
            case 'E':
            case 'e':
                if(num_answers >= 5) {
                    if(my_question.get_correct_answer() == 5) {
                        ++q_correct;
                        list_questions.erase(it);
                        cout << "e is correct " << q_correct << endl;
                    }
                    else {
                        ++q_missed;
                        cout << "e is incorrect, you have missed " << q_missed << " questions\n";
                    }
                }
                else {
                    error("please select an answer from the options given");
                }
                break;
            default:
                error("please select an answer from the options given");
            }
        }
        cout << endl;
    }
    
    void begin() {
        cout << "Welcome to SmartyPants C++ Trivia Game! You will be asked 10 questions, "
            << "and you must answer at least 7 correctly to pass. To select an answer, "
            << "simply type the character corresponding to your choice and hit enter."
            << "\n\n Are you ready to begin?\n\n";
        
        determine_structure();
    
        if(vec) {
            populate_vector_questions();
            while(q_missed + q_correct < 10) {
                if(q_missed > 3) {
                    error("You have missed too many questions and have failed");
                }
                if(q_missed == -1) {
                    error("");
                }
                else {
                    try {
                        ask_vector_question();
                    }
                    catch(exception& e) {
                        cerr << "error: " << e.what() << endl;
                    }
                }
                if(q_missed + q_correct == 10) {
                    cout << "You passed with a total score of " << q_correct 
                        << " correct out of 10!\n";
                }
            }
        }
        else {
            populate_list_questions();
            while(q_missed + q_correct < 10) {
                if(q_missed > 3) {
                    error("You have missed too many questions and have failed");
                }
                if(q_missed == -1) {
                    error("");
                }
                else {
                    try {
                        ask_list_question();
                    }
                    catch(exception& e) {
                        cerr << "error: " << e.what() << endl;
                    }
                }
                if(q_missed + q_correct == 10) {
                    cout << "You passed with a total score of " << q_correct 
                        << " correct out of 10!\n";
                }
            }
        }
    }
}
//end of questions_game namespace
//------------------------------------------------------------------------------