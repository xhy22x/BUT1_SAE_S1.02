#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Dico.h"

/**
* @file Dico.h
* @brief Composant de dictionnaire contenant un tableau dynamique de mots.
* Elle inclut également un champ pour la gestion de la quantité totale de mots dans le dictionnaire.
*/

void initDico(Dico* d) {
	d->qte = 0;
	d->mots = NULL;
}

void ajouterMot(Dico* d, const char* mot) {       
	if (mot == NULL || strlen(mot) == 0) {
		printf("Mot invalide.\n");
		return;
	}

	d->mots = (char**)realloc(d->mots, (d->qte + 1) * sizeof(char*));
	if (d->mots == NULL) {
		printf("Erreur d'allocations mémoire dico\n");
		return;
	}
	d->mots[d->qte] = (char*)malloc((strlen(mot) + 1) * sizeof(char));
	if (d->mots[d->qte] == NULL) {
		printf("Erreur d'allocations mémoire pour le mot\n");
		return;
	}
	
	if (strcpy_s(d->mots[d->qte], strlen(mot) + 1, mot) != 0) {
		printf("Erreur de copie du mot\n");
		return;
	}
	d->qte++;
}

void afficheDico(Dico* d) {
	for (size_t i = 0; i < d->qte; ++i) {
		printf("%zu: %s\n", i + 1, d->mots[i]);
	}
}

int rechercheDico(Dico* d, const char* mot) {     
	if (mot == NULL || strlen(mot) == 0) {        
		printf("erreur (rechercheDico) \n");
		return 0;
	}
	for (size_t i = 0; i < d->qte; ++i) {      //Recherche du mot dans le dictionnaire
		if (strcmp(d->mots[i], mot) == 0) {    //On regarde dans dico si y'a le mot 
			return 1;                          //retourne 1 si le mot est trouvé
		}
	}
	return 0;      //retourne 0 si le mot n'est pas trouvé
}

// Fonction pour désallouer la mémoire du dictionnaire
void libererDico(Dico* d) {
	// Libérer la mémoire pour chaque mot dans le dictionnaire
	for (size_t i = 0; i < d->qte; ++i) {
		free(d->mots[i]);
	}

	// Libère le tableau de pointeurs vers les mots
	free(d->mots);

	// Réinitialiser les champs du dictionnaire
	d->qte = 0;
	d->mots = NULL;
}

int jouerCoup(Dico* d, Vecteur* j, const ItemV* entree, Vecteur* r) {
	ItemV mot[MAX_SAISI] = "";
	ItemV rail[MAX_SAISI] = "";
	ItemV chevalet[MAX_SAISI] = "";


	dansParentheses(entree, rail);  //Ce qui est dans la parentheses puis le comparer au Rail
	lireMotSansParentheses(entree, mot, DEBUT_MOT);
	HorsParentheses(entree, chevalet, DEBUT_MOT);

	//printf("r: %s\n", rail);         //ce qui est dans la parenthese
	//printf("mot: %s\n", mot);   //Le mot former
	//printf("c: %s\n", chevalet); //affiche les chevalets jouer par le joueur

	if (strlen(mot) <= MAX_MOT && strlen(rail) >= DEBUT_MOT && strlen(mot) > strlen(rail)) {
		int a = rechercheJoueur(j, chevalet);
		if (a == 1) {
			int b = DansRail(r, rail);
			if (b == 1) {
				//printf("dansR\n");   //Pour vérifier s'il est dans Rail
				int c = rechercheDico(d, mot);
				if (c == 1) {
					return 1;
				}
			}
		}
	}
	return 0;
}