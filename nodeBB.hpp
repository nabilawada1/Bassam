//********* nodeBB.hpp *********

#ifndef NODEBB_HPP
#define NODEBB_HPP

#include <vector>

using namespace std;


//Classe pour définir ce qu'est un noeud de l'arbre de B&B
class  NodeBB {

private:
    vector<bool> isFixed; // vector de taille  nbItems, indique avec TRUE les objets imposés dans le sac à dos du noeud courant (et donc de ses fils)
    vector<bool> isRemoved; // vector de taille  nbItems, indique avec TRUE les objets non compris dans le sac à dos du noeud (et donc de ses fils)
    vector<bool> primalSolution; // vector indiquant la composition du sac à dos par appelk à l'heuristique gloutonne au noeud. 
    //N.B: primalSolution est non vide et en mémoire uniquement quand on en a besoin, on appelle clearSolution() pour l'effacer au plus vite
    
    int criticalIndex; // indice critique, indice fractionnaire
    double fractionalVariable; // valeur de la varaible fractionnaire
    double localUpperBound; // borne supérieure obtenue par algorithme glouton (sur le sac à dos continu)
    long localLowerBound; // borne inférieure obtenue par heuristique gloutonne  (sur le sac à dos discret du noeud)
    bool overCapacitated; // indique si l'ensemble des masses des objets fixés dépasse la masse du sac à dos

public:

    //pour réinitialiser un noeud de size objets, alors avec que des false et des 0 et  
    void init(int size);

    // pour pouvoir supprimer le noeud dans KpSolverBB, ici ce sera juste un getter pour le dépassement de capacité, marqué par overCapacitated
    bool canBeRemoved();

    
    //Fonctions de remise à jour des bornes inférieures et supérieures au noeud courant
    // int kpBound, int nbItems, vector<int> & weights,  vector<int> & values définissent le sac à dos de l'instance, vectors passés apr référence, pas de copie de l'instance
    // N.B:NodeBB n'hérite pas de KpSolver, pour être un objet plus léger, qui sera présent potentiellement en grand nombre en mémoire

    // solveUpperBound vérifie tout d'abord par un parcours que la capacité des noeuds fixés n'excède pas la masse maximale du sac à dos, 
    //calcule la masse restante pouvant être utilisée pour els objets restants
    // nouveau parcours des objets, en évitant ceux qui ont été fixés ou enlevés, calcule et stocke  criticalIndex, fractionalVariable et localUpperBound.
    void solveUpperBound(int kpBound, int nbItems, vector<int> & weights,  vector<int> & values);

    //primalHeuristic est l'équivalent de solveUpperBound() sur un sac à dos discret, mets à jour primalSolution et localLowerBound
    void primalHeuristic(int kpBound, int nbItems, vector<int> & weights,  vector<int> & values);
    
    // Fonctions pour remettre à jour isFixed et isRemoved arpès des branchements
    // updateAfterbranching0, après avoir branché sur l'indice critique id, impose que l'objet if est enlevé
    void updateAfterbranching0(int id);
    // updateAfterbranching1 apliqué à un noeud qque, le fait devenir est le noeud fils  de nod après avoir branché à 1 l'indice id
    void updateAfterbranching1(NodeBB* nod, int id);


    // pour effacer la solution courante trouvée par hjeurisitque une fois qu'on n'en a plus besoin (par exemple une fois qu'elle a été copiée dans KpSolverBB 
    //ou qu'on sait qu'elle n'améliore pas la meilleure solution trouvée dans  KpSolverBB )
    //N.B: primalSolution est non vide et en mémoire uniquement quand on en a besoin, on appelle clearSolution() pour l'effacer au plus vite
    void clearSolution(){primalSolution.clear();};
    
    // pour copier la solution trouvée, dans un vector externe sol, sol sera la solution courante de  KpSolverBB si la soluition locale l'améliore
    void copyPrimalSolution(vector<bool> *sol) {sol->clear();*sol = primalSolution;}
    
    // getters et setters pour être utilisés dans KpSolverBB
    double getNodeUpperBound(){return localUpperBound;};
    long getNodePrimalBound(){return localLowerBound;};
    int getCriticalIndex() const {return criticalIndex;};
    float getFractionalVariable() const {return fractionalVariable;};

};

#endif
