//********* kpSolver.cpp *********

#include "kpSolver.hpp"
#include <math.h>


long KpSolver::getRoundedUpperBound(){
	return (long) floor(upperBoundOPT);
}


double KpSolver::computeOptimalityGap(){
	long UB = getRoundedUpperBound();
	gapOptimality =  ((double) (UB - costSolution) * 100) /( (double)costSolution)  ;
	return gapOptimality;
}


//Import de données dans un fichier texte inclus
//L'import trie déjà le sac à dos selon les coûts marginaux décroissants, pour les algos glouton et B&B
void KpSolver::importInstance(const string& fileName) {
	clearInstance();
	ifstream infile;
	infile.exceptions(ifstream::failbit | ifstream::badbit);
	infile.open(fileName.c_str());
	infile >> nbItems;
	weights.resize(nbItems);
	for (int i = 0; i < nbItems; i++) infile >> weights[i];
	values.resize(nbItems);
	for (int i = 0; i < nbItems; i++) infile >> values[i];
	infile >> knapsackBound;
	sortKnapsack();
}


//Tri du sac à dos selon les coûts marginaux décroissants, pour les algos glouton et B&B
void KpSolver::sortKnapsack() {
	vector<std::pair<int,int>> newStruct;
	std::pair <int,int> item;

	for (int i = 0; i < nbItems; i++){
		item = make_pair (weights[i],values[i]);
		newStruct.push_back(item);
	}	

	std::sort(newStruct.begin(), newStruct.end(),
			[](std::pair<int,int> i, std::pair<int,int> j) {return i.second * j.first > j.second * i.first;}
	);

	for (int i = 0; i < nbItems; i++){
		weights[i] = newStruct[i].first;
		values[i] = newStruct[i].second;		
	}
	newStruct.clear();
}

void KpSolver::clearInstance() {
	values.clear();
	weights.clear();
	nbItems = -1;
	solution.clear();
	costSolution=0;
	upperBoundOPT=0;
}

void KpSolver::printKnapsackInstance() {
	cout << "Max capacity knapsack : " << knapsackBound  << endl;
	for (int i = 0; i < nbItems; i++){
		cout << "Item: " << i << " Weight : " << weights[i]  << " Value : " << values[i] << " Marginal Cost : " << (float) values[i] / ((float) weights[i])  << endl;
	}
	cout << endl;	
}

void KpSolver::printKnapsackSolution(bool printSol) {
	cout << "solution cost : " << costSolution << endl;
	cout << "proven upper bound  : " << upperBoundOPT << endl;
	cout << "proven upper bound  after rounding: " << getRoundedUpperBound() << endl;
	cout << "gap : " << computeOptimalityGap() << "%" << endl;
	if (printSol){
		cout << "knapsack composition  : ";
		for (std::vector<bool>::iterator it = solution.begin() ; it != solution.end(); ++it)
			std::cout << ' ' << *it;
		cout  << endl;
	}

}

// Fonction pour extraire des sous instances, pour pouvoir faire des expériences numériques de taille fixe
// On considère ici l'instance en prenant les objets indicés de idMin à idMax inclus
void KpSolver::extractSubInstance(int idMin, int idMax) {

	idMin= max(0,idMin);
	idMax= min(nbItems,idMax);

	float numerator = 0;
	for (int i = idMin; i< idMax; i++){
		numerator += weights[i];
	}
	float denominator = 0 ;
	for (int i = 0; i < nbItems ; i++){
		denominator += weights[i];
	}
	knapsackBound =  (int) (((float) knapsackBound) * numerator / denominator) ;

	nbItems = idMax - idMin+1;
	vector<int> oldweights = weights ;
	vector <int> oldvalues = values ;

	weights.resize(nbItems);
	values.resize(nbItems);

	for (int i = 0; i<nbItems; i++){
		weights[i] = oldweights[i+idMin];
		values[i] = oldvalues[i+idMin];
	}
}

//Fonction de tri pour les expériences de mémoïsation, tri selon les masses croissantes ou décroissantes
void KpSolver::reindexMemo(bool sortMode) {

	vector<std::pair<int,int>> newStruct;

	std::pair <int,int> item;
	std::pair<int,int> itemCost;

	for (int i = 0; i < nbItems; i++){
		item = make_pair (weights[i],values[i]);
		newStruct.push_back(item);
	}

	if (sortMode) 	std::sort(newStruct.begin(), newStruct.end(),
			[](std::pair<int,int> i, std::pair<int,int> j) { return i.first < j.first;  }
	);
	else std::sort(newStruct.begin(), newStruct.end(),
			[](std::pair<int,int> i, std::pair<int,int> j) { return i.first > j.first;  });

	for (int i = 0; i < nbItems; i++){
		weights[i] = newStruct[i].first;
		values[i] = newStruct[i].second;
	}
	newStruct.clear();
}

