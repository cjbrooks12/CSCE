#include "PriorityQueueList.h"

//From Class "PriorityQueueList"
//------------------------------------------------------------------------------
void PriorityQueueList::createPriorityQueue(std::string filename, Locator locs[]) {
	std::ifstream ifs(filename);    
	if(!ifs){
		std::cout << "cannot open file\n";
	}
	else {
		int index = 0;
		while(!ifs.eof()) {
			int key;
			int elem;
			ifs >> key >> elem;
			
			Item* i = new Item(key, elem);
			locs[index].setItem(i);
			elemList.insert(elemList.begin(), &locs[index]);
            ++index;
			
		}
	}
	ifs.close();
}

Locator* PriorityQueueList::insert(int k, int e, Locator* loc) {
	Item* i = new Item(k, e);
	loc->setItem(i);
	elemList.insert(elemList.end(), loc);
	
	return loc;
}

bool PriorityQueueList::isEmpty() {
	if(getList().size() < 1) return true;
	else return false;

}	

Locator* PriorityQueueList::min() {
    Locator* min = *(elemList.begin());
    
	for(auto i:getList()){
		if(i->getItem()->getKey() < min->getItem()->getKey()) {
			min = i;
		}
	}
	return min;
}

void PriorityQueueList::remove(Locator* loc) {
	elemList.remove(loc);
}

void PriorityQueueList::decreaseKey(Locator& loc, int k) {
    int e = loc.getItem()->getElem();
    
    Item* i = new Item(k, e);
    
    loc.setItem(i);
    
}

int PriorityQueueList::getElement(Locator& loc) {
    int e = loc.getItem()->getKey();
    
    return e;
}

std::ostream& operator<<(std::ostream& os, const PriorityQueueList& pq) {
	for(auto i:pq.getList()){
		os << *i << "\n"; 
	}
	   
	return os;
}