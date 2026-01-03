#include <assert.h> 
#include <stdlib.h> 
#include "Vecteur.h"

/**
 * @brief Conteneur stockant des éléments accessibles en
 * fonction de leur position (indice).
 */ 

int initVecteur(Vecteur* v, int capacite) {
	assert(capacite > 0);
	v->capacite = capacite;
	v->nbElements = 0;
	v->elements = (ItemV*)malloc(sizeof(ItemV) * capacite);
	return v->elements != NULL;
}

int taille(const Vecteur* v) {
	return v->nbElements;
}

int ajouter(Vecteur* v, ItemV it) {
	const int FACTEUR = 2;
	if (v->nbElements == v->capacite) {
		ItemV* tab = (ItemV*)realloc(v->elements, sizeof(ItemV) * v->capacite * FACTEUR);
		if (tab == NULL)
			return 0;
		v->capacite *= FACTEUR;
		v->elements = tab;
	}
	v->elements[v->nbElements++] = it;
	return 1;
}

ItemV obtenir(const Vecteur* v, int i) {
	assert(i >= 0 && i < v->nbElements);
	return v->elements[i];
}

void supprimer(Vecteur* v, int i) {
	assert(i >= 0 && i < v->nbElements);
	for (++i; i < v->nbElements; ++i)
		v->elements[i - 1] = v->elements[i];
	--v->nbElements;
}

void detruireVecteur(Vecteur* v) {
	free(v->elements);
}









