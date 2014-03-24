#include "My_vec.cpp"

int main() try {
    My_vec m, v;
    
    m.insert_at_rank(0, 'b');
    m.insert_at_rank(0, 'a');
    m.insert_at_rank(0, 'c');
    
    My_vec mv = m;
    v = m;
    
    mv.replace_at_rank(0, 'q');
    mv.remove_at_rank(1);
    
    //to show that copy constructor and assignment create new objects correctly
    cout << "m: " << m << endl << "v: " << vv << "mv: " << mv << endl; 
    
    //to show that errors are thrown correctly
    cout << v.elem_at_rank(4) << endl; 
}
catch(string s) {
    cerr << "error: " << s << endl;
}