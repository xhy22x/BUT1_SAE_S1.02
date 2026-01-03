#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "Jeu.h"

/*Fonctions et structures de données gérant la mise en route
d'une partie de RECTO-VERSO*/

void trier(char* chevalet, int taille) {
	for (int i = 0; i < taille - 1; ++i) {
		for (int j = i + 1; j < taille; ++j) {
			if (chevalet[i] > chevalet[j]) {
				char tmp = chevalet[i];
				chevalet[i] = chevalet[j];
				chevalet[j] = tmp;
			}
		}
	}
}

void afficherDeckJoueur(Vecteur v) {
	for (int i = 0; i < v.nbElements; i++) {
		printf("%c", v.elements[i]);  // Afficher chaque lettre dans la file
	}
	printf("\n");
}

int rechercheJoueur(Vecteur* j, const char* mot) {
	if (mot == NULL || strlen(mot) == 0) {
		printf("Mot invalide.\n");
		return 0;
		printf("N.\n");
	}

	// Crée un tableau temporaire pour marquer les lettres utilisées
	//int lettresUtilisees[MAX_C] = { 0 }; // MAX_C est la taille max des chevalets du joueur
	size_t motLength = strlen(mot);


	int* lettresUtilisees = (int*)calloc(j->nbElements, sizeof(int)); // Dynamique selon j->nbElements
	if (!lettresUtilisees) {
		printf("Erreur mémoire.\n");
		return 0;
	}

	// Parcourt chaque lettre du mot
	for (size_t k = 0; k < motLength; ++k) {
		int trouve = 0;


		// Parcourt les lettres du chevalet pour chercher une correspondance non utilisée
		for (int x = 0; x < j->nbElements; ++x) {
			if (!lettresUtilisees[x] && j->elements[x] == mot[k]) {
				lettresUtilisees[x] = 1; // Marque la lettre comme utilisée
				trouve = 1;             // Lettre trouvée
				break;                  // Sort de la boucle interne

			}
		}

		if (trouve == 0) {
			free(lettresUtilisees);
			return 0; // Lettre introuvable ou déjà utilisée
		}
	}

	free(lettresUtilisees); // Libère la mémoire après usage
	return 1;
}

void supprimerLettre(Vecteur* j, const ItemV* c) {
	if (c == NULL || strlen(c) == 0) {
		printf("Lettre invalide.\n");
		return;
	}

	for (int k = 0; k < strlen(c); k++) {
		for (int i = 0; i < j->nbElements; i++) {
			if (j->elements[i] == c[k]) {
				supprimer(j, i);
				break;
			}
		}
	}
}

void ajoutMot(Vecteur* v, const ItemV* m) {    
	for (int i = 0; i < strlen(m); i++) {
		if (!ajouter(v, m[i])) {             
			printf("Erreur d'ajout\n");
			break;
		}
	}
}

void copie(Vecteur* v1, Vecteur* v2) {
	for (int i = 0; i < v2->nbElements; i++) {
		if (!ajouter(v1, v2->elements[i])) {
			printf("Erreur d'ajout\n");
			break;
		}
	}
}

//Changement de courant pour Joueur
void ChangeNb(Numero* n1, Numero* n2, const Vecteur* m1, const Vecteur* m2) { 
	int result = strcmp(m1->elements, m2->elements);
	if (result > 0) {   //m1 avant m2, échanger
		int temp = n1->chiffre;
		n1->chiffre = n2->chiffre;
		n2->chiffre = temp;
	}
}

void AlternerJoueur(Vecteur* j1, Vecteur* j2, const Vecteur* m1, const Vecteur* m2) {
	int result = strcmp(m1->elements, m2->elements);
	if (result > 0) {   //m1 avant m2, échanger
		Vecteur temp = *j1;  //échanger les champs vecteurs j1 et j2
		*j1 = *j2;
		*j2 = temp;
	}
}

void situationActu(Vecteur* j1, Vecteur* j2, Vecteur* r, Vecteur* v, Numero* n1, Numero* n2) {
	//fonction compare num.chiffre lequel est plus petit et inverser afficheDeckJoueur

	int a = 0;
	int b = 0;
	unsigned int num1 = n1->chiffre;
	unsigned int num2 = n2->chiffre;

	if (num1 == 1) {
		printf("%d : ", n1->chiffre);
		a = 1;
	}
	else {
		printf("%d : ", n2->chiffre);
		a = 0;
	}

	if (a == 1) {
		//int result = taille(j1);
		//retailler(j1, result);
		afficherDeckJoueur(*j1);
	}
	else {
		//int result = taille(j2);
		//retailler(j2, result);
		afficherDeckJoueur(*j2);
	}

	if (num2 == 2) {
		printf("%d : ", n2->chiffre);
		b = 1;
	}
	else {
		printf("%d : ", n1->chiffre);
		b = 0;
	}

	if (b == 1) {
		//int result = taille(j2);
		//retailler(j2, result);
		afficherDeckJoueur(*j2);
	}
	else if (b == 0) {
		//int result = taille(j1);
		//retailler(j1, result);
		afficherDeckJoueur(*j1);
	}
	printf("R : ");
	afficheRail(r);
	printf("V : ");
	afficheRail(v);
	printf("\n");
}

void traiterLettre(ItemV* lettres, ItemV* saisi, int debut) {
	int idx = 0;

	for (int i = debut; saisi[i]!='\0'; i++) { //Parcours jusqu'à fin de chaîne
		lettres[idx++] = saisi[i];
	}
	lettres[idx] = '\0';

}

void echgChevalet(File* f, Vecteur* j, ItemV* lettre) {
	ajoutMot(f, lettre);
	supprimerLettre(j, lettre);
	distribution(j, f);
}

void Init(Vecteur* j1, Vecteur* j2, Vecteur* r, Vecteur* v) {
	detruireVecteur(j1);
	detruireVecteur(j2);
	detruireVecteur(r);
	detruireVecteur(v);
	initVecteur(j1, MAX_C);  //Ca peut être plus
	initVecteur(j2, MAX_C);
	initVecteur(r, MAX_R);
	initVecteur(v, MAX_R);
}