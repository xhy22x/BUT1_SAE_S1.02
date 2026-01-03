#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "Rail.h"

/*Fonctions permettant de gérer et vérifier les chevalets sur le rail*/

void ajoutRail(Vecteur* r, const Vecteur* m1, const Vecteur* m2) {
	for (int i = 0; i < m1->nbElements; i++) {
		if (!ajouter(r, m1->elements[i])) {
			printf("Erreur d'ajout 1er mot dans Rail\n");
			break;
		}
	}
	for (int i = 0; i < m2->nbElements; i++) {
		if (!ajouter(r, m2->elements[i])) {
			printf("Erreur d'ajout 2eme mot dans Rail\n");
			break;
		}
	}
}

void MisEnPlaceRail(Vecteur* r, const Vecteur* m1, const Vecteur* m2) {
	int result = strcmp(m1->elements, m2->elements);
	if (result < 0) {
		ajoutRail(r, m1, m2);
	}
	else if (result > 0) {
		ajoutRail(r, m2, m1);
	}
	else {
		ajoutRail(r, m1, m2);
	}
}

void afficheRail(Vecteur* r) {
	for (int i = 0; i < r->nbElements; i++) {
		printf("%c", r->elements[i]);
	}
	printf("\n");
}

void copieRail(Vecteur* v1, Vecteur* v2) {
	for (int i = 0; i < v2->nbElements; i++) {
		if (!ajouter(v1, v2->elements[i])) {
			printf("Erreur d'ajout\n");
			break;
		}
	}
}

void swap(Vecteur* r) {
	assert(r != NULL);
	for (int i = 0; i < r->nbElements / 2; i++) {
		ItemV temp = r->elements[i];
		r->elements[i] = r->elements[r->nbElements - i - 1];
		r->elements[r->nbElements - i - 1] = temp;
	}
}

int DansRail(const Vecteur* r, const ItemV* mot) {
	int i = 0;
	int m = 0;

	if (strncmp(r->elements, mot, strlen(mot)) == 0) {
		return 1;
	}
	else if (strncmp(r->elements + MAX_R - strlen(mot), mot, strlen(mot)) == 0) {
		return 1;
	}
	return 0; // Mot pas au début ou vers la fin du rail
}

void dansParentheses(const ItemV* saisi, ItemV* r) {
	int idx = 0;
	int dansParentheses = 0;

	for (int i = 0; saisi[i] != '\0'; i++) {  //copie à partir du 3ème.
		if (saisi[i] == '(') {
			dansParentheses = 1;
		}
		else if (saisi[i] == ')') {
			dansParentheses = 0;
		}
		else {
			if (dansParentheses) {
				r[idx++] = saisi[i];
			}
		}
	}
	r[idx] = '\0';
}

void lireMotSansParentheses(const ItemV* saisi, ItemV* mot, int debut) {
	int idx = 0;  //Indice remplissage

	for (int i = debut; saisi[i] != '\0'; i++) {
		if (saisi[i] != '(' && saisi[i] != ')') {
			mot[idx++] = saisi[i];
		}
	}

	mot[idx] = '\0'; //termine chaîne
}

void HorsParentheses(const ItemV* mot, ItemV* c, int debut) {
	int dansP = 0;
	int idx = 0;

	for (int i = debut; mot[i] != '\0'; i++) {
		if (mot[i] == '(') {
			dansP = 1;
		}
		else if (mot[i] == ')') {
			dansP = 0;
		}
		else if (!dansP) {
			c[idx++] = mot[i];
		}
	}
	c[idx] = '\0';
}

int editRail(Vecteur* r, const ItemV* mot, Vecteur* j) {
	int d = 0;
	int f = 0;
	ItemV horsP[MAX_SAISI] = "";
	ItemV dansP[MAX_SAISI] = "";
	ItemV sansP[MAX_SAISI] = "";
	ItemV reste[MAX_SAISI] = "";
	dansParentheses(mot, dansP);
	HorsParentheses(mot, horsP, DEBUT_MOT);
	lireMotSansParentheses(mot, sansP, DEBUT_MOT);
	int taille = strlen(horsP);

	while (1) {
		if (strncmp(r->elements, dansP, strlen(dansP)) == 0) { //si dansP trouvé au début rail
			if (strncmp(sansP, horsP, strlen(horsP)) == 0) { //si horsP trouvé au début mot
				d = 1;
				break;
			}
			else {
				return 0;
			}
		}
		else if (strncmp(r->elements + MAX_R - strlen(dansP), dansP, strlen(dansP)) == 0) { //fin Rail
			if (strncmp(sansP + strlen(sansP) - strlen(horsP), horsP, strlen(horsP)) == 0) { //si horsP trouvé au début
				f = 1;
				break;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}

	}

	if (d == 1) {
		ajoutAvant(r, horsP);
		extraireRail(r, &reste, taille);
		for (int x = 0; x < strlen(horsP); x++) {
			ajustD(r, j, reste[x]);    //probleme ici je pense 
			//suppDerniereL(r);
			//supp lettre situé à la fin de rail
		}       //rail ou lettre dans rail non supp 
		return 1;
	}

	else if (f == 1) {
		ajoutArr(r, horsP); //Ajouter dans Rail

		for (int k = 0; k < strlen(horsP); ++k) {
			ajustAvant(r, j);
		}
		return 1;

	}
	else {
		printf("erreur");
		return 0;
	}

	return 0;
}

void extraireRail(Vecteur* r, ItemV* c, int x) {
	int idx = 0;  //Indice remplissage
	for (int i = MAX_R; r->elements[i] != '\0'; i++) {
		c[idx++] = r->elements[i];
	}
	c[idx] = '\0'; //termine chaîne
}

void ajoutArr(Vecteur* r, const ItemV* m) {
	size_t tailleM = strlen(m);

	if (r->nbElements + tailleM >= r->capacite) {
		r->capacite = (r->nbElements + tailleM);
		r->elements = realloc(r->elements, r->capacite * sizeof(ItemV));
		if (r->elements == NULL) {
			printf("Erreur : allocation (ajoutArr) \n");
			exit(EXIT_FAILURE);
		}
	}
	ajoutMot(r, m);
}

void ajoutAvant(Vecteur* r, const ItemV* m) {
	size_t tailleM = strlen(m);

	if (r->nbElements + tailleM >= r->capacite) {
		r->capacite = r->nbElements + tailleM; // Ajuste la capacité avec une marge (+1)
		r->elements = realloc(r->elements, r->capacite * sizeof(ItemV));
		if (r->elements == NULL) {
			printf("Erreur : allocation (ajoutAvant)\n");
			exit(EXIT_FAILURE);
		}
	}

	memmove(r->elements + tailleM, r->elements, r->nbElements + 1); //Inclure '\0'
	memcpy(r->elements, m, tailleM);

	r->nbElements += tailleM;

}

void ajustAvant(Vecteur* r, Vecteur* j) {
	int FACTEUR = 2;
	if (r->nbElements > 0) {

		if (j->nbElements == j->capacite) {
			// Réallocation pour agrandir j->elements
			j->capacite = (j->capacite == 0) ? 1 : j->capacite * FACTEUR;  // Double la capacité (si la capacité était 0, initialisez-la à 1)
			j->elements = (ItemV*)realloc(j->elements, sizeof(ItemV) * j->capacite);
			if (j->elements == NULL) {
				printf("Erreur (ajustAvant) \n");
				exit(EXIT_FAILURE);
			}
		}

		// Ajoute le premier élément du rail au joueur
		j->elements[j->nbElements] = r->elements[0];
		j->nbElements++;

		// Décale les éléments restants dans le rail
		memmove(r->elements, r->elements + 1, r->nbElements - 1);
		r->nbElements--;

		// Réallocation pour r->elements
		r->elements = (ItemV*)realloc(r->elements, sizeof(ItemV) * r->nbElements);
		if (r->nbElements > 0 && r->elements == NULL) {
			printf("Erreur : allocation mémoire échouée\n");
			exit(EXIT_FAILURE);
		}
	}
	else {
		printf("Erreur : rail vide.\n");
	}
}


void ajustD(Vecteur* r, Vecteur* j, ItemV c) {
	int FACTEUR = 2;
	if (r->nbElements > 0 && c > 0) {

		if (j->nbElements == j->capacite) {
			// Réallocation pour agrandir j->elements
			j->capacite = (j->capacite == 0) ? 1 : j->capacite * FACTEUR;  // Double la capacité (si la capacité était 0, initialisez-la à 1)
			j->elements = (ItemV*)realloc(j->elements, sizeof(ItemV) * j->capacite);
			if (j->elements == NULL) {
				printf("Erreur (ajustAvant) \n");
				exit(EXIT_FAILURE);
			}
		}

		// Ajoute l'élément à la fin de j->elements
		j->elements[j->nbElements] = c;
		j->nbElements++;

		// Supprime le dernier élément du rail (r)
		r->nbElements--;
		r->elements = (ItemV*)realloc(r->elements, sizeof(ItemV) * r->nbElements);
		if (r->nbElements > 0 && r->elements == NULL) {
			printf("Erreur : allocation mémoire échouée\n");
		}
	}
	else {
		printf("Pas assez de lettres dans le rail ou caractère invalide.\n");
	}
}

int VerifRail(Vecteur* r, const ItemV* mot) {   //enlever vecteur j
	int d = 0;
	int f = 0;
	ItemV horsP[MAX_SAISI] = "";
	ItemV dansP[MAX_SAISI] = "";
	ItemV sansP[MAX_SAISI] = "";
	ItemV reste[MAX_SAISI] = "";
	dansParentheses(mot, dansP);
	HorsParentheses(mot, horsP, DEBUT_MOT);
	lireMotSansParentheses(mot, sansP, DEBUT_MOT);
	int taille = strlen(horsP);

	while (1) {
		if (strncmp(r->elements, dansP, strlen(dansP)) == 0) { //si dansP trouvé au début rail
			if (strncmp(sansP, horsP, strlen(horsP)) == 0) { //si horsP trouvé au début mot
				d = 1;
				return 1;
			}
			else {
				return 0;
			}
		}
		else if (strncmp(r->elements + MAX_R - strlen(dansP), dansP, strlen(dansP)) == 0) { //fin Rail
			if (strncmp(sansP + strlen(sansP) - strlen(horsP), horsP, strlen(horsP)) == 0) { //si horsP trouvé au début
				f = 1;
				return 1;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}

	}
}

void updRail(Vecteur* r1, Vecteur* r2) {
	detruireVecteur(r1);
	initVecteur(r1, MAX_R);
	copieRail(r1, r2);
	swap(r1);
}