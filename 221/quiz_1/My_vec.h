class My_vec {
private:
    //Data Members
    int size, capacity;
    char *ptr;
public:
    //Constructors
    My_vec(): size(0), capacity(10), ptr(new char[capacity]) {}
    My_vec(My_vec& vec);
    ~My_vec() { delete ptr; }
    
    //Public Getter Functions
    int get_size() const { return size; }
    bool is_empty() const { return size==0; }
    char& elem_at_rank(int r);
    
    //Public Setter Functions
    void insert_at_rank(int r, const char& elem);
    void replace_at_rank(int r, const char& elem);
    void remove_at_rank(int r);
    
    //Member Operators
    My_vec& operator=(My_vec& vec);
    
};

//Nonmember Operators
ostream& operator<<(ostream& out, My_vec& vec);
