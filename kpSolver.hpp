//********* kpSolver.hpp *********

#ifndef KPSOLVER_HPP
#define KPSOLVER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

//classe solveur de sac à dos, les différents solveurs seront des classes filles de KpSolver
//classe continent les données et foncitons communes aux solveurs relatives à une instance de sac à dos et au débogage
//N.B: pas de constructeur et pas de destructeur, les constructeurs et destructeurs par défaut seront appelés et conviendrotn très bien

class KpSolver {

private:
	//Tri du sac à dos selon les coûts marginaux décroissants, pour les algos glouton et B&B
	void sortKnapsack();

protected:

	// Items and knapsack properties.
	int nbItems; // nombre d' objets
	vector<int> weights; // masses des objets
	vector<int> values;  // valeurs des objets
	int knapsackBound;   // masse maximale du sac à dos

	// Solution (items in the knapsack).
	vector<bool> solution;
	long costSolution; // cout de solution, c'est un entier borne inférieure de l'optimum
	double upperBoundOPT; //borne supérieure, continue, c'est un flottant avec précision 64bits pour éviter des erreurs d'arrondius numériques sur des grandes instances
	long roundedUpperBoundOPT; //borne supérieure arrondie, format entier pour l'affichage sur de grandes instances
	double gapOptimality;
	
public:

	//Import de données dans un fichier texte inclus
	//L'import trie déjà le sac à dos selon les coûts marginaux décroissants, pour les algos glouton et B&B
	void importInstance(const string& fileName);

	// Fonction pour extraire des sous instances, pour pouvoir faire des expériences numériques de taille fixe
	// On considère ici l'instance en prenant les objets indicés de idMin à idMax inclus de l'instance en mémoire
	void extractSubInstance(int idMin, int idMax);

	//Fonctions pour effacer l'instance en mémoire, permet de réinitaliser et d'importer par après une nouvelle instance avec  importInstance
	void clearInstance();


	//Fonctions d'affichage bour déboguer: composition de l'instance et compositions du sac à dos de la meilleure solution trouvée
	void printKnapsackInstance();
	void printKnapsackSolution(bool printSol);

	//Tri du sac à dos selon les masses décroissantes ou croissantes, pour les expérimentations de memoisation
	void reindexMemo(bool sortMode);

	
	//Fonctions "getters" pour récupérer les bornes et la composition du sac à dos
	long getRoundedUpperBound();
	long getSolutionCost(){return costSolution;};
	bool isSelected(int item){return solution[item];};
	int getNbItems() const {return nbItems;	};

	double computeOptimalityGap(); 

	
};

#endif


