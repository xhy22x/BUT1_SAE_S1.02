#pragma once

#include "Rail.h"

/*Fonctions et structures de données gérant la mise en route d'une partie de
RECTO-VERSO*/

typedef struct {
	unsigned int chiffre;  // Chiffre entier non signé.
}Numero;

/**
 * @brief Trie les chevalets, c'est-à-dire les lettres d'un joueur.
 * @param[in,out] chevalet Le chevalet à trier.
 * @param[in] taille Le nombre de lettres que possède le joueur.
 */
void trier(char* chevalet, int taille);

/**
 * @brief Affiche le contenu des chevalets du joueur.
 * @param[in] v Le vecteur contenant les lettres, c'est-à-dire les chevalets du joueur.
 */
void afficherDeckJoueur(Vecteur v);

/**
* @brief Recherche d'une chaîne de caractère dans le vecteur.
* Vérifie qu'un joueur a toutes les lettres composants le mot
* @param[in,out] j L'adresse du vecteur.
* @param[in] c Une chaîne d'élément qui est le mot formé par le joueur
* @return 1 si le mot est trouvée et 0 cas d'échec.
*/
int rechercheJoueur(Vecteur* j, const char* c);

/**
* @brief Supprimer un élément dans un vecteur.
* @param[in,out] j L'adresse d'un vecteur
* @param[in] c L'élément à retiré.
*/
void supprimerLettre(Vecteur* j, const ItemV* c);

/**
* @brief Ajout d'un élément dans un vecteur. ( une chaîne de caractère )
* @param[in,out] v L'adresse d'un vecteur
* @param[in] m L'élément à ajouter.
*/
void ajoutMot(Vecteur* v, const ItemV* m);

/**
* @brief Copie les éléments d'un vecteur dans un autre vecteur.
* @param[out] v1 L'adresse du vecteur cible.
* @param[in] v2 L'adresse du vecteur source.
*/
void copie(Vecteur* v1, Vecteur* v2);

/**
* @brief Met à jour le numéro courant du joueur.
* Modifie les numéros en fonctions du mot créer au début du jeu.
* @param[out] n1 Numéro à modifier
* @param[out] n2 Numéro à modifier
* @param[in] m1 L'élement du vecteur à comparer.
* @param[in] m2 L'élément du vecteur à comparer.
*/
void ChangeNb(Numero* n1, Numero* n2, const Vecteur* m1, const Vecteur* m2);

/**
* @brief Alterne les éléments de deux vecteurs.
* Alterne les joueurs en fonction du mot créer au début. 
* @param[in,out] j1 L'adresse d'un vecteur.
* @param[in,out] j2 L'adresse d'un vecteur.
* @param[in] m1 L'adresse d'un vecteur contenant l'élément à comparer.
* @param[in] m2 L'adresse d'un vecteur contenant l'élément à comparer.
*/
void AlternerJoueur(Vecteur* j1, Vecteur* j2, const Vecteur* m1, const Vecteur* m2);

/**
* @brief Affiche les éléments des vecteurs.
* Affiche la situation actuelle du Jeu. ( Joueurs et rails )
* @param[in,out] j1 L'adresse d'un vecteur.
* @param[in,out] j2 L'adresse d'un vecteur.
* @param[in,out] r L'adresse d'un vecteur.
* @param[in,out] v L'adresse d'un vecteur.
* @param[in,out] n1 L'adresse d'un numéro.
* @param[in,out] n2 L'adresse d'un numéro.
*/
void situationActu(Vecteur* j1, Vecteur* j2, Vecteur* r, Vecteur* v, Numero* n1, Numero* n2);

/**
* @brief Traite l'élément fait lors de la saisi.
* Supprime les caractères inutiles.
* @param[in,out] lettres Lettres sont traités.
* @param[in] saisi L'élément de la saisi.
* @param[in] debut La position initiale pour le traitement.
*/
void traiterLettre(ItemV* lettres, ItemV* saisi, int debut);

/**
* @brief Echange d'élément d'une file et d'un vecteur.
* Echange d'une lettre dans le chevalet du joueur avec la pioche.
* @param[in,out] f L'adresse d'une file. ( Pioche )
* @param[in,out] j L'adresse d'un vecteur. ( Joueur )
* @param[in] lettre L'élément à échanger avec une file. 
*/
void echgChevalet(File* f, Vecteur* j, ItemV* lettre);

/**
* @brief Initialisation des vecteurs.
* On réinitialise les vecteurs et on va stocker les éléments précédents.
* @param[in,out] j1 L'adresse d'un vecteur.
* @param[in,out] j2 L'adresse d'un vecteur.
* @param[in,out] r L'adresse d'un vecteur.
* @param[in,out] v L'adresse d'un vecteur.
*/
void Init(Vecteur* j1, Vecteur* j2, Vecteur* r, Vecteur* v);