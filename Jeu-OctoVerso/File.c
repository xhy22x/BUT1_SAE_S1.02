#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "File.h"

/**
@file File.h
@brief Composant de file à capacité fixée.
*/

// Initialiser une file vide
void initFile(File* f, int capacite) {
	initVecteur(f, capacite);  // Initialiser la file comme un vecteur
}

// Vérifier si la file est vide
int estVide(File f) {
    return f.nbElements == 0;
}


ItemF premier(const File* f) {
    return obtenir(f, 0);
}

void entrer(File* f, ItemF it) {
    ajouter(f, it);
}

ItemF sortir(File* f) {
    ItemF it = premier(f);
    supprimer(f, 0);
    return it;
}

void detruireFile(File* f) {
    detruireVecteur(f);
}

// Fonction pour afficher la file
void afficherPioche(File f) {
    for (int i = 0; i < f.nbElements; i++) {
        printf("%c", f.elements[i]);  // Afficher chaque lettre dans la file
    }
    printf("\n");
}

// Fonction pour créer le deck de chevalets
void creerDeck(File* f) {
    // Vérifier si la file est vide
    assert(estVide(*f));

    // Liste des lettres disponibles et leur quantité
    const char lettres[LETTRES] = "ABCDEFGHIJLMNOPQRSTUV";
    const unsigned int quantites[LETTRES] = {
        9, 1, 2, 3, 14, 1, 1, 1, 7, 1, 5, 3, 6, 5, 2, 1, 6, 7, 6, 5, 2
    };

    // Remplir la file avec les lettres
    for (unsigned int i = 0; i < LETTRES; i++) {
        for (unsigned int y = 0; y < quantites[i]; y++) {
            entrer(f, lettres[i]);  // Ajouter chaque lettre en fonction de sa quantité
        }
    }
}

void melange(File* f) {
	srand((unsigned int)time(NULL));  // Initialiser le générateur de nombres aléatoires

	for (int i = f->nbElements - 1; i > 0; i--) {
		int j = rand() % (i + 1);  // Générer un nombre aléatoire entre 0 et i

		// Échanger les lettres aux indices i et j
		char temp = f->elements[i];
		f->elements[i] = f->elements[j];
		f->elements[j] = temp;
	}
}

void ajout(Vecteur* v, File* f) {
    for (int i = 0; i < MAX_C; i++) {
        if (!ajouter(v, f->elements[i])) {
            printf("Erreur d'ajout\n");
            break;
        }
    }
}

void distribution(Vecteur* v, File* f) {
	if (f->nbElements > 0) {
		ajouter(v, sortir(f));
	}
	else {
		printf("Plus de lettres disponibles\n");
	}
}

void ajoutPioche(File* f, ItemV c) {
    for (int i = 0; i < 1; i++) {
        if (!ajouter(f, c)) {
            printf("Erreur d'ajout\n");
            break;
        }
    }
}




