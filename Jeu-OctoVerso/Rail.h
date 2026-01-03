#pragma once

#include "File.h"

/*Fonctions permettant de gérer et vérifier les chevalets sur le rail*/

enum {
	DEBUT_MOT = 2,  // Extraire l'élément à partir du 3 caractère 

	MAX_SAISI = 30,      // Maximum pour la saisi
	MAX_LETTRE = 10,      // Taille pour la saisi d'une lettre ( si jamais y'a des saisis de plusieurs lettres )
	NB_CARACTERES_STOCKE = 3    // Cas échange un chevalet avec la pioche ( une lettre ). Pour extraire la lettre à la 3ème position.
};

/**
 * @brief Ajoute les éléments de deux vecteurs dans un vecteur. ( Rail )
 * @param[in,out] v L'adresse d'un vecteur. ( Rail )
 * @param[in] m1 L'adresse d'un vecteur.
 * @param[in] m2 L'adresse d'un vecteur.
 */
void ajoutRail(Vecteur* r, const Vecteur* m1, const Vecteur* m2);

/**
* @brief Met en place les éléments d'un vecteur ( Rail ) à partir de deux vecteurs.
* Les deux vecteurs sont les mots formés par chacunes des joueurs.
* @param[in,out] r L'adresse d'un vecteur. ( Rail )
* @param[in] m1 L'adresse d'un vecteur. ( Mot formé par joueur 1 )
* @param[in] m2 L'adresse d'un vecteur. ( Mot formé par joueur 2 )
*/
void MisEnPlaceRail(Vecteur* r, const Vecteur* m1, const Vecteur* m2);

/**
* @brief Affiche les éléments dans un vecteur.
* Les éléments contenus dans rail.
* @param[in,out] r L'adresse d'un vecteur.
*/
void afficheRail(Vecteur* r);

/**
* @brief Copie les éléments d'un vecteur dans un autre vecteur.
* @param[out] v1 L'adresse du vecteur cible.
* @param[in] v2 L'adresse du vecteur source.
*/
void copieRail(Vecteur* v1, Vecteur* v2);

/**
* @brief Inverse les éléments d'un vecteur.
* Ce au début se trouve à la fin et inversement.
* @param[in,out] r L'adresse du vecteur.
*/
void swap(Vecteur* r);

/**
* @brief Vérification d'élément présents dans le vecteur.
* @param[in,out] r L'adresse d'un vecteur.
* @param[in] mot Chaîne de caractère à rechercher.
* @return 1 si le mot est trouvée et 0 en cas d'échec.
*/
int DansRail(const Vecteur* r, const ItemV* mot);

/**
* @brief Contenu de l'élément dans la parenthèse
* @param[in] saisi Une chaîne de caractères lors de la saisi.
* @param[out] r L'élément contenant uniquement dans la parenthèse.
*/
void dansParentheses(const ItemV* saisi, ItemV* r);

/**
* @brief Lit le contenu sans la parenthèse.
* @param[in] saisi Une chaîne de caractères lors de la saisi.
* @param[out] mot L'élément sans les parenthèses.
* @param[in] debut La position initiale pour extraire le mot.
*/
void lireMotSansParentheses(const ItemV* saisi, ItemV* mot, int debut);

/**
* @brief Contenu de l'élément en dehors des parenthèses.
* @param[in] mot Chaîne de caractères
* @param[out] c L'élément hors parenthèses.
* @param[int] debut La position initiale pour extraire l'élément.
*/
void HorsParentheses(const ItemV* mot, ItemV* c, int debut);

/**
* @brief Changement apportés au vecteur.
* Modification du Rail
* @param[in,out] r L'adresse d'un vecteur.
* @param[in] mot Chaîne de caractère
* @param[in,out] j L'adresse d'un vecteur.
* @return 1 modification apporté et 0 en cas d'échec.
*/
int editRail(Vecteur* r, const ItemV* mot, Vecteur* j);

/**
* @brief Extraire un élément d'un vecteur. ( Rail )
* @param[in,out] r L'adresse d'un vecteur.
* @param[out] c L'élément extrait.
* @param[in] x La position initiale pour extraire l'élément.
*/
void extraireRail(Vecteur* r, ItemV* c, int x);

/**
* @brief Ajout d'un ou des élément(s) à la fin d'un vecteur. ( Rail )
* @param[in,out] r L'adresse d'un vecteur.
* @param[in] m L'élément à ajouter.
*/
void ajoutArr(Vecteur* r, const ItemV* m);

/**
* @brief Ajout d'un ou des élément(s) au début d'un vecteur. ( Rail )
* @param[in,out] r L'adresse d'un vecteur.
* @param[in] m L'élément à ajouter.
*/
void ajoutAvant(Vecteur* r, const ItemV* m);

/**
* @brief Ajustement d'un ou des élément(s) au début d'un vecteur.
* Opération rail lié à celle du joueur. Ajout de l'élément enlever du rail au joueur.
* @param[in,out] r L'adresse d'un vecteur.
* @param[in,out] j L'adresse d'un vecteur.
*/
void ajustAvant(Vecteur* r, Vecteur* j);

/**
* @brief Ajustement d'un ou des élément(s) à la fin d'un vecteur.
* Opération rail lié à celle du joueur. Ajout de l'élément enlever du rail au joueur.
* @param[in,out] r L'adresse d'un vecteur.
* @param[in,out] j L'adresse d'un vecteur.
* @param[in] c L'élément utile à la modification.
*/
void ajustD(Vecteur* r, Vecteur* j, ItemV c);

/**
* @brief Vérifie des éléments dans un vecteur.
* Si l'élément est dans les deux vecteurs. ( Rail et Joueur )
* @param[in,out] r L'adresse d'un vecteur.
* @param[in] mot L'élément à vérifier.
* @param[in] j L'adresse d'un vecteur.
* @return 1 si l'élément est trouvé et 0 en cas d'échec
*/
int VerifRail(Vecteur* r, const ItemV* mot);

/**
* @brief Met à jour les éléments d'un vecteur.
* On réinitialise et on ajoute les éléments dans ces vecteurs.
* @param[in,out] r1 L'adresse d'un vecteur.
* @param[in,out] r2 L'adresse d'un vecteur.
*/
void updRail(Vecteur* r1, Vecteur* r2);

