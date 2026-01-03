#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dico.h"

int main() {
	// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX OUVERTURE DU DICTIONNAIRE XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	FILE* f = fopen("ods4.txt", "r");
	if (f == NULL) {
		printf("Erreur d'ouverture du fichier\n");
		return;
	}
	size_t nbm = 0, nbc = 0;
	char mot[MAX_SAISI] = { 0 };
	int n;
	n = fscanf(f, "%29s", mot);

	Dico d;
	initDico(&d);

	Dico e;        //enregistre mot utilisées
	initDico(&e);

	while (n == 1) {
		++nbm;
		nbc += strlen(mot);
		ajouterMot(&d, mot);
		n = fscanf(f, "%29s", mot);

	}
	if (ferror(f))
		printf("erreur - %s\n", strerror(errno));

	// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX DEBUT DE LA PARTIE XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	// Initialiser la file avec une capacité suffisante
	File p;
	initFile(&p, MAX_CHEVALETS);
	creerDeck(&p);
	//afficherPioche(p);
	melange(&p);
	//afficherPioche(p);

	Vecteur j1;
	initVecteur(&j1, MAX_C);
	Vecteur j2;
	initVecteur(&j2, MAX_C);

	for (int i = 0; i < MAX_C; i++) {
		distribution(&j1, &p);
		distribution(&j2, &p);
	}

	//afficherDeckJoueur(j1);
	//afficherDeckJoueur(j2);

	trier(j1.elements, j1.nbElements);
	trier(j2.elements, j2.nbElements);

	printf("1 : ");
	afficherDeckJoueur(j1);
	//afficherPioche(p);
	printf("2 : ");
	afficherDeckJoueur(j2);
	//afficherPioche(p);
	printf("\n");


	//JEU
	ItemV entree[MAX_SAISI];
	Vecteur m1;
	Vecteur m2;
	initVecteur(&m1, MOT_DE_QUATRE);
	initVecteur(&m2, MOT_DE_QUATRE);

	while (1) {
		printf("1> ");
		if (fgets(entree, sizeof(entree), stdin) == NULL) {
			continue;  // En cas d'erreur ou d'entrée vide, redemander une saisie
		}

		// Supprimer le retour à la ligne si présent
		ItemV len = strlen(entree);                    
		if (len > 0 && entree[len - 1] == '\n') {
			entree[len - 1] = '\0';
		}

		// Vérifier si l'utilisateur a appuyé sur Entrée sans rien saisir
		if (strlen(entree) == 0) {
			continue;  // Redemander une saisie
		}

		if (strlen(entree) == MOT_DE_QUATRE) {
			int a = rechercheJoueur(&j1, entree);
			if (a == 1) {
				int b = rechercheDico(&d, entree);
				if (b == 1 && !rechercheDico(&e, entree)) {
					supprimerLettre(&j1, entree);
					ajoutMot(&m1, entree);
					ajouterMot(&e, entree);  //enregistre mot utilisée
					break;
				}
			}
		}
	}
	while (1) {
		printf("2> ");
		if (fgets(entree, sizeof(entree), stdin) == NULL) {
			continue;  // En cas d'erreur ou d'entrée vide, redemander une saisie
		}

		// Supprimer le retour à la ligne si présent
		ItemV len = strlen(entree);
		if (len > 0 && entree[len - 1] == '\n') {
			entree[len - 1] = '\0';
		}

		// Vérifier si l'utilisateur a appuyé sur Entrée sans rien saisir
		if (strlen(entree) == 0) {
			continue;  // Redemander une saisie
		}

		if (strlen(entree) == MOT_DE_QUATRE) {
			int a = rechercheJoueur(&j2, entree);
			if (a == 1) {
				int b = rechercheDico(&d, entree);
				if (b == 1 && !rechercheDico(&e, entree)) {
					supprimerLettre(&j2, entree);
					ajoutMot(&m2, entree);
					ajouterMot(&e, entree);
					break;
				}
			}
		}
	}
	printf("\n");
	//afficheDico(&e);

	// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX AFFICHAGE SITUATION COURANTE DU DEBUT XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	Numero num1; //Joueur
	Numero num2; //Joueur
	num1.chiffre = 1;
	num2.chiffre = 2;

	printf("%d : ", num1.chiffre);
	//afficherDeckJoueur(j1);
	afficherDeckJoueur(j1);
	printf("%d : ", num2.chiffre);
	afficherDeckJoueur(j2);

	Vecteur Rail;
	initVecteur(&Rail, MAX_R);
	MisEnPlaceRail(&Rail, &m1, &m2);
	printf("R : ");
	afficheRail(&Rail);

	Vecteur InverseRail;
	initVecteur(&InverseRail, MAX_R);
	//copieRail(&InverseRail, &Rail);
	//swap(&InverseRail);
	printf("V : ");
	copieRail(&InverseRail, &Rail);
	swap(&InverseRail);
	afficheRail(&InverseRail);

	// XXXXXXXXXXXXXXXXXXXXXXXX CHANGE CELUI QUI COMMENCE EN FONCTION DU MOT DE 4 LETTRES LE PLUS PETIT XXXXXXXXXXXXXXXXXXXXX
	ChangeNb(&num1, &num2, &m1, &m2);  //Modification du courant avant le vrai jeu
	AlternerJoueur(&j1, &j2, &m1, &m2); //alterner joueur aussi
	
	//afficherDeckJoueur(j1);
	//afficherDeckJoueur(j2);
	//afficherPioche(p);


	//Cas échéant
	Vecteur j1s;
	Vecteur j2s;
	Vecteur Rs;
	Vecteur Vs;
	ItemV MotPrecedent[MAX_SAISI] = "";
	initVecteur(&j1s, MAX_C);  //Ca peut être plus
	initVecteur(&j2s, MAX_C);
	initVecteur(&Rs, MAX_R);
	initVecteur(&Vs, MAX_R);
	AlternerJoueur(&j1s, &j2s, &m1, &m2);      //alterner joueur pour précédent aussi
	copie(&j1s, &j1);
	copie(&j2s, &j2);
	copie(&Rs, &Rail);
	copie(&Vs, &InverseRail);

	// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX JEU AVEC DIFFERENTS CAS XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	printf("\n");
	while (taille(&j1) > 0 && taille(&j2) > 0) {
		// AU TOUR DU PREMIER JOUEUR QUI JOUE
		while (1) {
			ItemV saisi[MAX_SAISI];
			ItemV sansP[MAX_SAISI] = "";
			ItemV dansP[MAX_SAISI] = "";
			ItemV horsP[MAX_SAISI] = "";
			printf("%d> ", num1.chiffre);
			fgets(saisi, sizeof(saisi), stdin);  // Utilisation de fgets pour lire toute la ligne
			// Supprimer le retour à la ligne si présent à la fin de la chaîne
			ItemV len = strlen(saisi);
			if (len > 0 && saisi[len - 1] == '\n') {
				saisi[len - 1] = '\0';  // Retirer le '\n' qui reste après fgets
			}
			if (strcmp(saisi, "exit") == 0) {
				break;  // Sort de la boucle si "exit" est saisi
			}
			if (strlen(saisi) == 0) {
				continue;  // Redemander une saisie
			}
			// JOUEUR FORME MOT À UNE EXTRÉMITÉ DU RAIL RECTO R
			if (saisi[0] == 'R' && saisi[1] == ' ') {
				int a = jouerCoup(&d, &j1, saisi, &Rail);  //Vérifie s'il le joueur peut jouer
				if (a == 1) {
					lireMotSansParentheses(saisi, sansP, DEBUT_MOT);
					HorsParentheses(saisi, horsP, DEBUT_MOT);
					Init(&j1s, &j2s, &Rs, &Vs);
					copie(&j1s, &j1);                       //Stocke les valeurs
					copie(&j2s, &j2);
					copie(&Rs, &Rail);
					copie(&Vs, &InverseRail);
					int b = editRail(&Rail, saisi, &j2);     //On modifie les valeurs
					if (b == 1 && !rechercheDico(&e, sansP)) {
						ajouterMot(&e, sansP);
						supprimerLettre(&j1, horsP);
						strcpy(MotPrecedent, sansP);
						updRail(&InverseRail, &Rail);
						if (strlen(sansP) == MAX_MOT) {
							printf("\n");
							situationActu(&j1, &j2, &Rail, &InverseRail, &num1, &num2); 
							// CAS SI MOT DE 8 LETTRES : JOUEUR ENLÈVE UN DE SES CHEVALETS
							char L[MAX_LETTRE];  
							int x = 0;
							do {
								// Demander une saisie utilisateur
								printf("-%d> ", num1.chiffre);
								fgets(L, sizeof(L), stdin);
								char lon = strlen(L);
								if (lon > 0 && L[lon - 1] == '\n') {
									L[lon - 1] = '\0';  // Retirer le '\n' qui reste après fgets
								}
								// Vérifier si la saisie est correcte
								if (strlen(L) == 1) {
									x = rechercheJoueur(&j1, L);
								}
								// Si l'entrée est invalide, on redemande la saisie
							} while (strlen(L) == 0 || x != 1);
							// Si le joueur existe, on ajoute la lettre à la pioche et on la retire du joueur
							if (x == 1) {
								ajoutPioche(&p, L);  // Fonction remet dans pioche
								supprimerLettre(&j1, L);
							}
							break;
						}
						break;
					}
				}
			}
			// CAS JOUEUR FORME MOT À UNE EXTRÉMITÉ DU RAIL RECTO V
			else if (saisi[0] == 'V' && saisi[1] == ' ') {
				int b = jouerCoup(&d, &j1, saisi, &InverseRail);
				if (b == 1) {
					lireMotSansParentheses(saisi, sansP, DEBUT_MOT);
					Init(&j1s, &j2s, &Rs, &Vs);
					copie(&j1s, &j1);                       //Stocke les valeurs
					copie(&j2s, &j2);
					copie(&Rs, &Rail);
					copie(&Vs, &InverseRail);
					HorsParentheses(saisi, horsP, DEBUT_MOT);
					int b = editRail(&InverseRail, saisi, &j2);
					if (b == 1 && !rechercheDico(&e, sansP)) {
						ajouterMot(&e, sansP);
						supprimerLettre(&j1, horsP);
						strcpy(MotPrecedent, sansP);
						updRail(&Rail, &InverseRail);
						if (strlen(sansP) == MAX_MOT) {
							printf("\n");
							situationActu(&j1, &j2, &Rail, &InverseRail, &num1, &num2);
							// SI MOT DE 8 LETTRES : JOUEUR ENLÈVE UN DE SES CHEVALETS
							char L[MAX_LETTRE];  
							int x = 0;
							do {
								// Demander une saisie utilisateur
								printf("-%d> ", num1.chiffre);
								fgets(L, sizeof(L), stdin);
								char lon = strlen(L);
								if (lon > 0 && L[lon - 1] == '\n') {
									L[lon - 1] = '\0';  // Retirer le '\n' qui reste après fgets
								}
								// Vérifier si la saisie est correcte
								if (strlen(L) == 1) {
									x = rechercheJoueur(&j1, L);
								}
								// Si l'entrée est invalide, on redemande la saisie
							} while (strlen(L) == 0 || x != 1);
							// Si le joueur existe, on ajoute la lettre à la pioche et on la retire du joueur
							if (x == 1) {
								ajoutPioche(&p, L);  // Fonction remet dans pioche
								supprimerLettre(&j1, L);
							}
							break;
						}
						break;
					}
				}
			}
			// CAS SIGNALER UN MOT QUI AURAIT PU ÊTRE JOUÉ PRÉCÉDEMMENT PAR L'ADVERSAIRE 
			if (strlen(MotPrecedent) < MAX_MOT) {
				if ((saisi[0] == 'r' || saisi[0] == 'v') && saisi[1] == ' ') {
					// SUR LE RAIL RECTO R
					if (saisi[0] == 'r') {
						lireMotSansParentheses(saisi, sansP, DEBUT_MOT);
						if (strlen(sansP) == MAX_MOT) {
							int a = jouerCoup(&d, &j2s, saisi, &Rs);
							if (a == 1) {
								int b = VerifRail(&Rs, saisi);
								if (b == 1 && !rechercheDico(&e, sansP)) {
									printf("\n");
									situationActu(&j1, &j2, &Rail, &InverseRail, &num1, &num2);
									// SI MOT DE 8 LETTRES : JOUEUR AYANT SIGNALÉ ENLÈVE UN DE SES CHEVALETS
									char L[MAX_LETTRE];  // Taille 2 pour un caractère + '\0'
									int x = 0;
									do {
										// Demander une saisie utilisateur
										printf("-%d> ", num1.chiffre);
										fgets(L, sizeof(L), stdin);
										char lon = strlen(L);
										if (lon > 0 && L[lon - 1] == '\n') {
											L[lon - 1] = '\0';  // Retirer le '\n' qui reste après fgets
										}
										// Vérifier si la saisie est correcte
										if (strlen(L) == 1) {
											x = rechercheJoueur(&j1, L);
										}
										// Si l'entrée est invalide, on redemande la saisie
									} while (strlen(L) == 0 || x != 1);
									// Si le joueur existe, on ajoute la lettre à la pioche et on la retire du joueur
									if (x == 1) {
										ajoutPioche(&p, L);  // Fonction remet dans pioche
										supprimerLettre(&j1, L);
									}
									ajouterMot(&e, sansP);
									printf("\n");
									updRail(&InverseRail, &Rail);
									situationActu(&j1, &j2, &Rail, &InverseRail, &num1, &num2);
								}
							}
						}
					}
					// SUR LE RAIL VERSO V
					else {   //Cas de 'v'
						lireMotSansParentheses(saisi, sansP, DEBUT_MOT);
						if (strlen(sansP) == MAX_MOT) {
							int a = jouerCoup(&d, &j2s, saisi, &Vs);
							if (a == 1) {
								int b = VerifRail(&Vs, saisi);
								if (b == 1 && !rechercheDico(&e, sansP)) {
									printf("\n");
									situationActu(&j1, &j2, &Rail, &InverseRail, &num1, &num2);
									// SI MOT DE 8 LETTRES : JOUEUR AYANT SIGNALÉ ENLÈVE UN DE SES CHEVALETS
									char L[MAX_LETTRE];  
									int x = 0;
									do {
										// Demander une saisie utilisateur
										printf("-%d> ", num1.chiffre);
										fgets(L, sizeof(L), stdin);
										char lon = strlen(L);
										if (lon > 0 && L[lon - 1] == '\n') {
											L[lon - 1] = '\0';  // Retirer le '\n' qui reste après fgets
										}
										// Vérifier si la saisie est correcte
										if (strlen(L) == 1) {
											x = rechercheJoueur(&j1, L);
										}
										// Si l'entrée est invalide, on redemande la saisie
									} while (strlen(L) == 0 || x != 1);
									// Si le joueur existe, on ajoute la lettre à la pioche et on la retire du joueur
									if (x == 1) {
										ajoutPioche(&p, L);  // Fonction remet dans pioche
										supprimerLettre(&j1, L);
									}
									ajouterMot(&e, sansP);
									printf("\n");
									updRail(&Rail, &InverseRail);
									situationActu(&j1, &j2, &Rail, &InverseRail, &num1, &num2);
								}
							}
						}
					}
				}
			}
			// CAS OÙ JOUEUR VEUT ÉCHANGER UN DE SES CHEVALETS AVEC UN DE LA PIOCHE
			ItemV echgL[MAX_SAISI] = "";
			if (saisi[0] == '-' && saisi[1] == ' ') {
				if (strlen(saisi) == NB_CARACTERES_STOCKE) {
					traiterLettre(echgL, saisi, DEBUT_MOT);
					int a = rechercheJoueur(&j1, echgL);
					if (a == 1) {
						echgChevalet(&p, &j1, echgL);  
						//afficherPioche(p);
						strcpy(MotPrecedent, " ");
						break;
					}
				}
			}
		}
		printf("\n");
		if (j1.nbElements == 0 || j2.nbElements == 0) {
			break;
		}
		trier(j1.elements, j1.nbElements);
		trier(j2.elements, j2.nbElements);
		situationActu(&j1, &j2, &Rail, &InverseRail, &num1, &num2);


		//printf("Précédent:\n");
		//afficherDeckJoueur(j1s);
		//afficherDeckJoueur(j2s);
		//afficheRail(&Rs);
		//afficheRail(&Vs);

		// AU TOUR DU SECOND JOUEUR QUI JOUE
		while (1) {
			ItemV saisi[MAX_SAISI];
			ItemV sansP[MAX_SAISI] = "";
			ItemV dansP[MAX_SAISI] = "";
			ItemV horsP[MAX_SAISI] = "";
			printf("%d> ", num2.chiffre);
			fgets(saisi, sizeof(saisi), stdin);  
			
			ItemV len = strlen(saisi);
			if (len > 0 && saisi[len - 1] == '\n') {
				saisi[len - 1] = '\0';  // Retirer le '\n' qui reste après fgets
			}
			if (strcmp(saisi, "exit") == 0) {
				break;  // Sort de la boucle si "exit" est saisi
			}
			if (strlen(saisi) == 0) {
				continue;  // Redemander une saisie
			}
			// JOUEUR FORME MOT À UNE EXTRÉMITÉ DU RAIL RECTO R
			if (saisi[0] == 'R' && saisi[1] == ' ') {
				int a = jouerCoup(&d, &j2, saisi, &Rail);
				if (a == 1) {
					lireMotSansParentheses(saisi, sansP, DEBUT_MOT);
					HorsParentheses(saisi, horsP, DEBUT_MOT);
					Init(&j1s, &j2s, &Rs, &Vs);
					copie(&j1s, &j1);
					copie(&j2s, &j2);
					copie(&Rs, &Rail);
					copie(&Vs, &InverseRail);
					int b = editRail(&Rail, saisi, &j1);
					if (b == 1 && !rechercheDico(&e, sansP)) {
						ajouterMot(&e, sansP);
						supprimerLettre(&j2, horsP);
						strcpy(MotPrecedent, sansP);
						updRail(&InverseRail, &Rail);
						if (strlen(sansP) == MAX_MOT) {
							printf("\n");
							situationActu(&j1, &j2, &Rail, &InverseRail, &num1, &num2);
							// CAS SI MOT DE 8 LETTRES : JOUEUR ENLÈVE UN DE SES CHEVALETS
							char L[MAX_LETTRE];  
							int x = 0;
							do {
								// Demander une saisie utilisateur
								printf("-%d> ", num2.chiffre);
								fgets(L, sizeof(L), stdin);
								char lon = strlen(L);
								if (lon > 0 && L[lon - 1] == '\n') {
									L[lon - 1] = '\0';  // Retirer le '\n' qui reste après fgets
								}
								// Vérifier si la saisie est correcte
								if (strlen(L) == 1) {
									x = rechercheJoueur(&j2, L);
								}
								// Si l'entrée est invalide, on redemande la saisie
							} while (strlen(L) == 0 || x != 1);
							// Si le joueur existe, on ajoute la lettre à la pioche et on la retire du joueur
							if (x == 1) {
								ajoutPioche(&p, L);  // Fonction remet dans pioche
								supprimerLettre(&j2, L);
							}
							break;
						}
						break;
					}
				}
			}
			// JOUEUR FORME MOT À UNE EXTRÉMITÉ DU RAIL VERSO V
			else if (saisi[0] == 'V' && saisi[1] == ' ') {           //Inversé les Rails
				int b = jouerCoup(&d, &j2, saisi, &InverseRail);
				if (b == 1) {
					lireMotSansParentheses(saisi, sansP, DEBUT_MOT);
					HorsParentheses(saisi, horsP, DEBUT_MOT);
					Init(&j1s, &j2s, &Rs, &Vs);
					copie(&j1s, &j1);
					copie(&j2s, &j2);
					copie(&Rs, &Rail);
					copie(&Vs, &InverseRail);
					int b = editRail(&InverseRail, saisi, &j1);  ///booléen  INT!!!!
					if (b == 1 && !rechercheDico(&e, sansP)) {
						ajouterMot(&e, sansP);
						supprimerLettre(&j2, horsP);
						strcpy(MotPrecedent, sansP);
						updRail(&Rail, &InverseRail);
						if (strlen(sansP) == MAX_MOT) {
							printf("\n");
							situationActu(&j1, &j2, &Rail, &InverseRail, &num1, &num2);
							// CAS SI MOT DE 8 LETTRES : JOUEUR ENLÈVE UN DE SES CHEVALETS
							char L[MAX_LETTRE];
							int x = 0;
							do {
								// Demander une saisie utilisateur
								printf("-%d> ", num2.chiffre);
								fgets(L, sizeof(L), stdin);
								char lon = strlen(L);
								if (lon > 0 && L[lon - 1] == '\n') {
									L[lon - 1] = '\0';  // Retirer le '\n' qui reste après fgets
								}
								// Vérifier si la saisie est correcte
								if (strlen(L) == 1) {
									x = rechercheJoueur(&j2, L);
								}
								// Si l'entrée est invalide, on redemande la saisie
							} while (strlen(L) == 0 || x != 1);
							// Si le joueur existe, on ajoute la lettre à la pioche et on la retire du joueur
							if (x == 1) {
								ajoutPioche(&p, L);  // Fonction remet dans pioche
								supprimerLettre(&j2, L);
							}
							break;
						}
						break;
					}
				}
			}
			// CAS SIGNALER UN MOT QUI AURAIT PU ÊTRE JOUÉ PRÉCÉDEMMENT PAR L'ADVERSAIRE 
			if (strlen(MotPrecedent) < MAX_MOT) {
				if ((saisi[0] == 'r' || saisi[0] == 'v') && saisi[1] == ' ') {
					// SUR LE RAIL RECTO R
					if (saisi[0] == 'r') {
						lireMotSansParentheses(saisi, sansP, DEBUT_MOT);
						if (strlen(sansP) == MAX_MOT) {
							int a = jouerCoup(&d, &j1s, saisi, &Rs);
							if (a == 1) {
								int b = VerifRail(&Rs, saisi);
								if (b == 1 && !rechercheDico(&e, sansP)) {
									printf("\n");
									situationActu(&j1, &j2, &Rail, &InverseRail, &num1, &num2);
									// SI MOT DE 8 LETTRES : JOUEUR AYANT SIGNALÉ ENLÈVE UN DE SES CHEVALETS
									char L[MAX_LETTRE];  
									int x = 0;
									do {
										// Demander une saisie utilisateur
										printf("-%d> ", num2.chiffre);
										fgets(L, sizeof(L), stdin);
										char lon = strlen(L);
										if (lon > 0 && L[lon - 1] == '\n') {
											L[lon - 1] = '\0';  // Retirer le '\n' qui reste après fgets
										}
										// Vérifier si la saisie est correcte
										if (strlen(L) == 1) {
											x = rechercheJoueur(&j2, L);
										}
										// Si l'entrée est invalide, on redemande la saisie
									} while (strlen(L) == 0 || x != 1);
									// Si le joueur existe, on ajoute la lettre à la pioche et on la retire du joueur
									if (x == 1) {
										ajoutPioche(&p, L);  // Fonction remet dans pioche
										supprimerLettre(&j2, L);
									}
									ajouterMot(&e, sansP);
									printf("\n");
									updRail(&InverseRail, &Rail);
									situationActu(&j1, &j2, &Rail, &InverseRail, &num1, &num2);
								}
							}
						}
					}
					// SUR LE RAIL RECTO R
					else {   //Cas de 'v'
						lireMotSansParentheses(saisi, sansP, DEBUT_MOT);
						if (strlen(sansP) == MAX_MOT) {
							int a = jouerCoup(&d, &j1s, saisi, &Vs);
							if (a == 1) {
								int b = VerifRail(&Vs, saisi);
								if (b == 1 && !rechercheDico(&e, sansP)) {
									printf("\n");
									situationActu(&j1, &j2, &Rail, &InverseRail, &num1, &num2);
									// SI MOT DE 8 LETTRES : JOUEUR AYANT SIGNALÉ ENLÈVE UN DE SES CHEVALETS
									char L[MAX_LETTRE];  // Taille 2 pour un caractère + '\0'
									int x = 0;
									do {
										// Demander une saisie utilisateur
										printf("-%d> ", num2.chiffre);
										fgets(L, sizeof(L), stdin);
										char lon = strlen(L);
										if (lon > 0 && L[lon - 1] == '\n') {
											L[lon - 1] = '\0';  // Retirer le '\n' qui reste après fgets
										}
										// Vérifier si la saisie est correcte
										if (strlen(L) == 1) {
											x = rechercheJoueur(&j2, L);
										}
										// Si l'entrée est invalide, on redemande la saisie
									} while (strlen(L) == 0 || x != 1);
									// Si le joueur existe, on ajoute la lettre à la pioche et on la retire du joueur
									if (x == 1) {
										ajoutPioche(&p, L);  // Fonction remet dans pioche
										supprimerLettre(&j2, L);
									}
									ajouterMot(&e, sansP);
									printf("\n");
									updRail(&Rail, &InverseRail);
									situationActu(&j1, &j2, &Rail, &InverseRail, &num1, &num2);
								}
							}
						}
					}
				}
			}
			// CAS OÙ JOUEUR VEUT ÉCHANGER UN DE SES CHEVALETS AVEC UN DE LA PIOCHE
			ItemV echgL[MAX_SAISI] = "";
			if (saisi[0] == '-' && saisi[1] == ' ') {
				if (strlen(saisi) == NB_CARACTERES_STOCKE) {
					traiterLettre(echgL, saisi, DEBUT_MOT);
					int a = rechercheJoueur(&j2, echgL);
					if (a == 1) {
						echgChevalet(&p, &j2, echgL);
						//afficherPioche(p);
						strcpy(MotPrecedent, " ");
						break;
					}
				}
			}

		}
		printf("\n");
		if (j1.nbElements == 0 || j2.nbElements == 0) {
			break;
		}

		trier(j1.elements, j1.nbElements);
		trier(j2.elements, j2.nbElements);
		situationActu(&j1, &j2, &Rail, &InverseRail, &num1, &num2);

	}  
	//Fin de la boucle while principale

	//Affiche résultat
	//printf("---------------");



	// XXXXXXXXXXXXXXXXXXXXXXXXX LIBÉRATION DE LA MÉMOIRE ALLOUÉE XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	detruireVecteur(&j1);
	detruireVecteur(&j2);
	detruireVecteur(&j1s);
	detruireVecteur(&j2s);
	detruireVecteur(&Rail);
	detruireVecteur(&InverseRail);
	detruireVecteur(&Rs);
	detruireVecteur(&Vs);
	detruireVecteur(&m2);
	detruireVecteur(&m1);
	detruireFile(&p);
	libererDico(&d);
	libererDico(&e);
	// XXXXXXXXXXXXXXXXXXXXXXXXXXXX FERMETURE DU DICTIONNAIRE XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	fclose(f);
	return 0;
}
