#include "Item.h"

//From class "Item"
//------------------------------------------------------------------------------
Item::Item() {
	key = 0;
	elem = 0;
	loc = new Locator(this);
}

Item::Item(int k, int e) {
	key = k;
	elem = e;
	loc = new Locator(this);
}

Item::~Item() {
    delete loc;
}

bool operator<(const Item& a, const Item& b) {
	if(a.getKey() < b.getKey()) return true;
	else return false;
}

bool operator==(const Item& a, const Item& b) {
	if(a.getKey() == b.getKey()) return true;
	else return false;
}

std::ostream& operator<<(std::ostream& os, const Item& item) {
	os	<< item.getKey() << " " << item.getElem(); 
	return os;
}	

Item& Item::operator=(const Item& it) {
    setKey(it.getKey());
    setElem(it.getElem());
    
    return *this;
}

//From class "Locator"
//------------------------------------------------------------------------------
bool operator<(const Locator& a, Locator& b) {
	if( *(a.getItem()) < *(b.getItem())) return true;
	else return false;
	
	return true;
}

Locator::~Locator() {
    delete i;
}

bool operator==(const Locator& a, Locator& b) {
	if( *(a.getItem()) == *(b.getItem())) return true;
	else return false;
	
	return true;
}

std::ostream& operator<<(std::ostream& os, const Locator& loc) {
	os << *(loc.getItem());
	   
	return os;
}	

Locator& Locator::operator=(const Locator& l) {
    setItem(l.getItem());
    
    return *this;
}
//------------------------------------------------------------------------------