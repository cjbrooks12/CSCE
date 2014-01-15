#include "BinarySearchTree.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void readFromFile(string fileName, bool print) {
    ifstream ifs(fileName);    
    if(!ifs){
        cout << "cannot open file";
        return;
    }
    
    int x;
    ifs >> x;
    
    BinaryNode *mRoot = new BinaryNode(x);
    mRoot->setSearchCost(0);
    
    BinarySearchTree *fileTree = new BinarySearchTree(mRoot);
    
    while(ifs) {
        ifs >> x;
        fileTree->insert(x,  fileTree->getRoot(), 0);
    }
    ifs.close();
	
    ofstream ofs;
    ofs.open ("results.csv", std::ofstream::app);
    
	//to output to a .csv file to read into excel, use this block
    /*ofs << fileName << ", "
         << fileTree->size() << ", "
         << fileTree->height() << ", "
         << fileTree->totalSearchCost(0, fileTree->getRoot()) << ", "
         << fileTree->averageSearchCost(fileTree->getRoot()) << "\n"; */
		 fileTree->print();
		fileTree->remove(12, fileTree->getRoot());
		fileTree->print();
    //to output to a .csv file to read as a text file, use this block
    /*ofs << "\nName of input file: " << fileName << "\n"
         << "Number of Nodes in Tree: " << fileTree->size() << "\n"
         << "Height of Tree: " << fileTree->height() << "\n"
         << "Total Search Cost of Tree: " << fileTree->totalSearchCost(0, fileTree->getRoot()) << "\n"
         << "Average Search Cost of Tree: " << fileTree->averageSearchCost(fileTree->getRoot()) << "\n"; */ 
    ofs.close();
    
    /*if(print) {
        fileTree->print();
        cout << "\n";
    }
    fileTree->printToFile(fileName + "_tree.txt"); */
}

int main() {
    ofstream ofs;
    ofs.open ("results.csv");
    ofs << "file name, size, height, total cost, avg cost\n";
    ofs.close();
    
    //Reads all the files into trees and outputs the results to "Results.txt"
    /*readFromFile("1p", true);
    readFromFile("2p", true);
    readFromFile("3p", true);
    readFromFile("4p", true);
    readFromFile("5p", false);
    readFromFile("6p", false);
    readFromFile("7p", false);
    readFromFile("8p", false);
    readFromFile("9p", false);
    readFromFile("10p", false);
    readFromFile("11p", false);
    readFromFile("12p", false);
    
    readFromFile("1r", true);
    readFromFile("2r", true);
    readFromFile("3r", true);
    readFromFile("4r", true);
    readFromFile("5r", false);
    readFromFile("6r", false);
    readFromFile("7r", false);
    readFromFile("8r", false);
    readFromFile("9r", false);
    readFromFile("10r", false);
    readFromFile("11r", false);
    readFromFile("12r", false);
    
    readFromFile("1l", true);
    readFromFile("2l", true);
    readFromFile("3l", true);
    readFromFile("4l", true);
    readFromFile("5l", false);
    readFromFile("6l", false);
    readFromFile("7l", false);
    readFromFile("8l", false);
    readFromFile("9l", false);
    readFromFile("10l", false);
    readFromFile("11l", false);
    readFromFile("12l", false); */
	
    readFromFile("4r", true);
    return 0;
}