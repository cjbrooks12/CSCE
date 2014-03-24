#include "std_lib_facilities.h"
#include "My_vec.h"
using namespace std;

//Constructor
//------------------------------------------------------------------------------
My_vec::My_vec(My_vec& vec) {
    size = vec.size;
    capacity = vec.capacity;
    ptr = new char[capacity];
    for(int i = 0; i < vec.get_size(); ++i) {
        ptr[i] = vec.ptr[i];
    }
}

//Public Getter Functions
//------------------------------------------------------------------------------
char& My_vec::elem_at_rank(int r) {
    if(r < size) {
        return ptr[r];  
    }
    else {
        throw string("index out of range");
    }
}

//Public Setter Functions
//------------------------------------------------------------------------------
void My_vec::insert_at_rank(int r, const char& elem) {
    if(r > 9) {
        throw string("index out of range");
    }
    if(capacity <= 0) {
        throw string("array at capacity");
    }
    for(int i = 9; i >= r; --i) {
        ptr[i] = ptr[i-1];
    }
    ptr[r] = elem;
    for(int i = 0; i < r; ++i) {
        if(ptr[i] == 0) {
            ptr[i] = '0';
            ++size;
            --capacity;
        }
    }
    ++size;
    --capacity;
}

void My_vec::replace_at_rank(int r, const char& elem) {
    if(ptr[r] == 0) {
        throw string("index out of range");   
    }
    else {
        ptr[r] = elem;
    }
}

void My_vec::remove_at_rank(int r) {
    if(r > size) {
        throw string("index out of range");
    }
    else {
        for(int i = r; i <= 9; ++i) {
            ptr[i] = ptr[i+1];
        }
        ptr[9] = 0;
        --size;
        ++capacity;
    }
}

//Overloaded Operators
//------------------------------------------------------------------------------
ostream& operator<<(ostream& out, My_vec& vec) {
    char c;
    for(int i = 0; i < vec.get_size(); ++i) {
        c = vec.elem_at_rank(i);
        out << '(' << i << ',' << c << ')';
    }
    return out;
}

My_vec& My_vec::operator=(My_vec& vec) {
    size = vec.size;
    capacity = vec.capacity;
    ptr = new char[capacity];
    for(int i = 0; i < vec.get_size(); ++i) {
        ptr[i] = vec.ptr[i];
    }
}
//------------------------------------------------------------------------------