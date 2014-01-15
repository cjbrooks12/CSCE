#include "PriorityQueueHeap.h"

//From Class "PriorityQueueHeap"
//------------------------------------------------------------------------------
void PriorityQueueHeap::createPriorityQueue(std::string filename, Locator locs[]) {
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
			
			checkSize();
			
			Item* i = new Item(key, elem);
			Locator* loc = i->getLocator();
			locs[index] = *loc;
			
			insert(key, elem, loc);
			
            ++index;
		}
	}
	ifs.close();
	//buildHeap();
}

Locator* PriorityQueueHeap::insert(int k, int e, Locator* loc) {
	Item* i = new Item(k, e);
	loc->setItem(i);
	
	if(!orderOK) {
		toss(loc);
		return NULL;
	}
	checkSize();
	
	int hole = curSize++;
	for( ; hole > 0 && &(elemList[(hole-1)/2]) < loc; hole = (hole-1)/2) {
		elemList[hole] = elemList[((hole-1)/2)];
	}
	elemList[hole] = *loc;
	
	return loc;
}

void PriorityQueueHeap::checkSize( ) {
	if(curSize == length) {
		Locator* oldArray = elemList;
		getNewArray(2*curSize);
		for (int i = 0; i < curSize; i++) {
			elemList[i] = oldArray[i];
		}
		//delete oldArray;
	}
}

void PriorityQueueHeap::toss(Locator* loc) {
	checkSize( );
	elemList[curSize++] = loc[0];
	if((&elemList[(curSize-1)/2]) < loc) {
		orderOK = false;
	}
}

void PriorityQueueHeap::remove(Locator* loc) {
	//elemList.remove(loc);
}

void PriorityQueueHeap::walkdown(int hole) {
	int child, key = elemList[hole].getItem()->getKey();
	for( ; 2*hole+1 < curSize; hole = child) {
		child = 2*hole+1;
		if(child != curSize-1 && &elemList[child] < &elemList[child+1]) child++;
		if(key < elemList[child].getItem()->getKey()) elemList[hole] = elemList[child];
		else break;
	}
	elemList[hole].getItem()->setKey(key);
}

void PriorityQueueHeap::decreaseKey(Locator& loc, int k) {
    int e = loc.getItem()->getElem();
    
    Item* i = new Item(k, e);
    
    loc.setItem(i);
    
}

int PriorityQueueHeap::getElement(Locator& loc) {
    int e = loc.getItem()->getKey();
    
    return e;
}

std::ostream& operator<<(std::ostream& os, const PriorityQueueHeap& pq) {
	Locator* list = pq.getList();
	
	for(int i = 0; i < pq.size(); ++i) {
		os << list[i] << "\n";
	}
	
	
	//for(Locator* i:pq.getList()){
		//os << *i << "\n"; 
	//}
	   
	return os;
}