//********* kpSolverBB.hpp *********

#ifndef KPSOLVERBB_HPP
#define KPSOLVERBB_HPP

#include "kpSolver.hpp"
#include "nodeBB.hpp"
#include <deque>

// type énuméré pour définir les différentes stratégies de branchement
enum BranchingStrategies { BestBound,  DFS10, DFS01, BFS, Random, End};


//classe solveur exact par l'algorithme de Branch&Bound, classe fille de KpSolver
// KpSolverBB utilise une liste de NodeBB: le snoeuds courants

class  KpSolverBB : public KpSolver {

private:
    deque<NodeBB*> nodes; // ensemble des noeuds de l'algo B&B actifs
    int nbNodes; // nombre de noeuds parcourus par l'algo de B&B
    int nbMaxNodeBB; // nombre maximal de noeuds a parcourir 
    bool withPrimalHeuristics; // pour activer les heuristiques gloutonnes de recherche de solutions discrètes à chaque noeud
    bool verboseMode; // mode verbeux pour de l'affichage pour déboguer ou comprendre l'algorithme
    bool withDPinitPrimalHeuristic; //Vrai pour initialiser le B&B avec une solution obtenue par Kernel Search
    int sizeDPheur; //Paramètre (unique ici) pour le rayon de la Kernel Search

    float tolerance; //tolerance pour critère d'arrêt, 0 par défaut ici, avec Cplex c'est 0.01%
    
    BranchingStrategies branchingStrategy; // type énuméré pour les différentes stratégies de branchement

    void printStatus(); // affiche le statut courant de l'algo de B&B: nombre de neouds parcours/restants, bornes
    
    double getUpperBound(); // pour calculer la borne supérieure en parcourant les bornes locales de tous les noeuds

    //Fonctions pour sélectionner un noeud à traiter suivant la stratégie de branchement
    NodeBB* selectNode();
    NodeBB* selectNodeRandom();
    
    //Fonctions d'insertion de nouveaux noeuds, dépendent de la stratégie de branchement
    void insertNode(NodeBB* nod);
    void insertNodes(NodeBB* nod1, NodeBB* nod2);

    void init(); //initialisation de  l'algo de Branch&Bound

public:

    void solve(); //la fonction principale, poour résoudre par l'algo de Branch&Bound

    //void solveRecursiveDFS(); peut être fait facilement par récursivité pour DFS10 ou DFS01

    // getters et setters pouvant être appelés dans les fichiers de test
    
    void setTolerance(float tol){ if (tol>=0) tolerance =tol;}; // pour changer la tolérance de 0 par défaut 0.01 donne la tolérance par défaut de Cplex : 0.01%
	void setNbMaxNodeBb(int nbMaxNodeBb) {	nbMaxNodeBB = nbMaxNodeBb;};
	void setVerboseMode(bool vMode){verboseMode = vMode;};
	void setWithPrimalHeuristics(bool withHeuristics) {withPrimalHeuristics = withHeuristics;};
	void setWithDPinitPrimalHeuristic(bool withHeuristic) {withDPinitPrimalHeuristic = withHeuristic;};
	void setSizeDPheur(int siz) {sizeDPheur = siz;};
	void setBranchingStrategy(BranchingStrategies bStrategy) {branchingStrategy = bStrategy;};
	int getNbNodes() const {return nbNodes;};

};

#endif
