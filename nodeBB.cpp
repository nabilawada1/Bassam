//********* nodeBB.cpp *********

#include "nodeBB.hpp"
//#include <iostream>
//#include <fstream>

bool NodeBB::canBeRemoved() {
	return overCapacitated;
}

void NodeBB::init(int size){
	isFixed.clear();
	isRemoved.clear();
	overCapacitated= false;
	isFixed.resize(size);
	isRemoved.resize(size);

    criticalIndex=-1;
    fractionalVariable=0;
    localLowerBound=0;
}

void NodeBB::primalHeuristic(int kpBound, int nbItems, vector<int> & weights,  vector<int> & values) {

//TODO
 }

void NodeBB::solveUpperBound(int kpBound, int nbItems, vector<int> & weights,  vector<int> & values) {
//TODO
 }

void NodeBB::updateAfterbranching0(int id) {
	isRemoved[id]=true;

}

void NodeBB::updateAfterbranching1(NodeBB *nod, int id) {
	isFixed.clear();
	isFixed=nod->isFixed;
	isRemoved.clear();
	isRemoved=nod->isRemoved;
	isFixed[id]=true;
	localUpperBound = nod->getNodeUpperBound();
}
