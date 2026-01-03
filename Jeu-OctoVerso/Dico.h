#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Jeu.h"

/*Structures de données et fonctions permettant l'implémentation et la
vérification des mots*/

/**
* @brief Composant de dictionnaire contenant un tableau dynamique de mots.
* Elle inclut également un champ pour la gestion de la quantité totale de mots dans le dictionnaire.
*/
typedef struct {
	char** mots; // Pointeur vers un tableau de chaînes de caractères (tableau de mots)
	size_t qte; // Quantité de mot dans le dictionnaire
}Dico;

/**
 * @brief Initialise un dictionnaire vide.
 * En définissant la quantité de mots à 0
 * et le tableau de mots à NULL.
 * Après son utilisation, la mémoire occupée par l'enregistrement doit être libérée
 * en invoquant la fonction @ref libererDico.
 * @param[in,out] d Pointeur vers la structure Dico à initialiser.
 * La fonction modifie le contenu de cette structure en initialisant ses champs.
*/
void initDico(Dico* d);

/**
 * @brief Ajoute un mot au dictionnaire en allouant dynamiquement de la mémoire
 * pour le mot et en augmentant la quantité de mots dans la structure.
 * Elle vérifie également que le mot n'est pas vide et que les allocations mémoire réussissent.
 * @param[in, out] d Pointeur vers le dictionnaire.
 * La fonction modifie le dictionnaire en ajoutant un mot à la structure.
 * @param[in] mot Le mot à ajouter dans le dictionnaire.
 */
void ajouterMot(Dico* d, const char* mot);

/**
 * @brief Affiche le contenu du dictionnaire.
 * Cette fonction parcourt tous les mots du dictionnaire et les affiche
 * @param[in] d Pointeur vers le dictionnaire à afficher.
 * La fonction n'affecte pas la structure mais utilise ses données pour afficher les mots.
 */
void afficheDico(Dico* d);

/**
 * @brief Recherche un mot dans le dictionnaire.
 * @param[in] d Pointeur vers le dictionnaire dans lequel rechercher le mot.
 * La fonction n'affecte pas la structure, mais l'utilise pour rechercher le mot.
 * @param[in] mot Le mot à rechercher dans le dictionnaire.
 * La fonction compare ce mot aux mots du dictionnaire pour déterminer s'il est présent.
 * @return[out] 1 si le mot est trouvé, 0 si le mot n'est pas trouvé.
 */
int rechercheDico(Dico* d, const char* mot);

/**
 * @brief Libère la mémoire allouée pour le dictionnaire.
 * Cette fonction désalloue toute la mémoire utilisée pour stocker les mots du dictionnaire,
 * ainsi que le tableau de pointeurs lui-même. Elle réinitialise également la structure du
 * dictionnaire en mettant la quantité à 0 et le tableau à NULL.
 * @param[in, out] d Pointeur vers le dictionnaire à libérer.
 */
void libererDico(Dico* d);

/**
* @brief Validation du coup qui sera jouer par un joueur.
* Vérifiction de la saisie.
* @param[in,out] d L'adresse du dictionnaire.
* @param[in,ou] j L'adresse d'un vecteur. ( Joueur )
* @param[in] entree Une chaîne de caractère lors du saisi
* @param[in,out] r L'adresse d'un vecteur. ( Rail )
* @return 1 si le coup peut être joué par le joueur et 0 en cas d'échec.
*/
int jouerCoup(Dico* d, Vecteur* j, const ItemV* entree, Vecteur* r);