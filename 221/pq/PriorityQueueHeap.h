#include "PriorityQueueList.h"

//Class "PriorityQueueHeap" based on a binary heap
//------------------------------------------------------------------------------
class PriorityQueueHeap {
private:
	Locator* elemList;
	int curSize, length;
	static const int DEF_SIZE = 8;
    bool orderOK;
	
	void getNewArray(int newSize) {
		elemList = new Locator[newSize];
		length = newSize;
	}

public:
	PriorityQueueHeap(int size = DEF_SIZE) {
		curSize = 0;
		orderOK = true;
		getNewArray(size);
	}
	
	Locator* min() {
		if( isEmpty() ) return NULL;
		if(! orderOK) buildHeap();
		return &elemList[0];
	}
	
	void buildHeap() {
		for(int i = (curSize-2)/2; i >= 0; i--) {
			walkdown(i);
		}
		orderOK = true;
	}
	
	void createPriorityQueue(std::string filename, Locator locs[]);
	Locator* insert(int k, int e, Locator* loc);
	void checkSize();
    void walkdown(int hole);
	void toss(Locator* loc);
	
	Locator* getList() const {return elemList;}
	bool isEmpty( ) const { return curSize == 0; }	
	int size( ) const { return curSize; }	
	void incrementSize() {++curSize;}
	void remove(Locator* loc);
    void decreaseKey(Locator& loc, int k);
    int getElement(Locator& loc);
	
	friend std::ostream& operator<<(std::ostream& os, const PriorityQueueHeap& pq);
};
//------------------------------------------------------------------------------