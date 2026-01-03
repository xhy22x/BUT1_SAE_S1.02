#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Vecteur.h"

/**
@file File.h
@brief Composant de file à capacité fixée.
*/
enum {
    LETTRES = 21,  // Nombre de lettres différentes dans l'alphabet donné
    MAX_CHEVALETS = 88 // Nombre totale de chevalets dans une partie
};

typedef Vecteur File;  // File même structure que Vecteur (typedef struct)
typedef ItemV ItemF;  // pour la cohérence des noms

/**
* @brief Initialisation d'une file comme étant vide.
* Après son utilisation, la mémoire occupée par une file doit être libérée
* en invoquant la fonction @ref detruireFile.
* @param[in,out] f L'adresse du File. 
* @param[in] capacite La capacité initiale du vecteur.
*/
void initFile(File* f, int capacite);

/**
* @brief Vérifie file est vide.
* @param[in] f L'adresse de la file.
* @return 1 si la file est vide, sinon 0
*/
int estVide(File f);

/**
* @brief Retourne l'élément d'une file se trouvant au début.
* @param[in] f L'adresse de la file.
* @return Le prochain élément devant sortir d'une file ( non vide )
*/
ItemF premier(const File* f);

/**
* @brief Ajoute un élément dans une file. Celui si sortira de la file
* après tous les éléments déjà présents.
* @param[in,out] f L'adresse de la file.
* @param[in] it L'élément à ajouter.
*/
void entrer(File* f, ItemF it);

/**
* @brief Fait sortir un élément d'une file ( non vide ) et retourne sa valeur.
* @param[in] f L'adresse de la file.
* @return L'élément à retiré.
*/
ItemF sortir(File* f);

/**
* @brief Libère l'espace mémoire occupé par une file.
* @param[in,out] f L'adresse de la file.
*/
void detruireFile(File* f);

/**
* @brief Affiche les éléments de la file. ( Pioche )
* @param[in,out] f L'adresse de la file.
*/
void afficherPioche(File f);

/**
* @brief Création de la pioche.
* Cette fonction remplit la file avec des lettres 
* selon les quantités prédéfinies pour chaque lettre.
* @param[in,out] f L'adresse de la file.
* @pre La file f doit être vide
*/
void creerDeck(File* f);

/**
* @brief Mélange les éléments de la file de manière aléatoire.
* @param[in,out] f L'adresse de la file.
*/
void melange(File* f);

/**
 * @brief Ajoute les 12 premiers éléments de la file à un vecteur.
 * @param v [in, out] Pointeur vers le vecteur.
 *                   La fonction modifie le vecteur en y ajoutant des éléments depuis la file.
 * @param f [in, out] Pointeur vers la file.
 *                   La fonction modifie la file en retirant des éléments pour les ajouter au vecteur.
 */
void ajout(Vecteur* v, File* f);

/**
 * @brief retire un élément de la file et l'ajoute au vecteur.
 * @param[in,out] v L'adresse d'un vecteur. La fonction modifie le vecteur en y ajoutant un élément.
 * @param[in,out] f L'adresse d'une file. La fonction modifie la file en retirant un élément.
 */
void distribution(Vecteur* v, File* f);

/**
* @brief Ajoute les éléments dans une file.
* @param[in,out] f L'adresse d'une file. La fonction modifie la file en y ajoutant un élément.
* @param[in] c L'élément à ajouter dans la file. L'élément `c` est ajouté à la fin de la file.
*/
void ajoutPioche(File* f, ItemV c);

