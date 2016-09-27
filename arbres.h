# ifndef __ARBRES_H
# define __ARBRES_H

#include <stdbool.h>


/*!
 * \file
 * \brief Ce module permet de manipuler des arbre binaire de recherche.
 *
 * La stucture est à deux niveaux: 
 * \li une structure accessible par pointeur/référence de l'extérieur avec les pointeurs sur les bonnes fonctions, et
 * \li une structure complétement cachée qui fait l'arbre binaire. 
 *
 * Une fonction de comparaison prend deux valeurs en argument et renvoie
 * \li une valeur <= 0 si la première est avant la seconde,
 * \li 0 si les veleurs sont égales
 * \li sinon la première est après la seconde.
 * Ceci bien sûr au sens de la comparaison concernée.
 *
 * Selon la nature de cette fonction (et des valeurs insérées), les valeurs manipulées peuvent être simple ou des couples (clé,valeur) avec la comparaison sur les clés uniquement. 
 * On réalise alors un tableau associatif.
 *
 * \copyright PASD
 * \version 2016
 */


/*! Les structure sont manipulés par pointer/référence.
 */
typedef struct arbre_struct * arbre;



/*! 
 * Cette fonction retourne un arbre vide.
 * \param copier une fonction pour copier une valeur, un pointeur est indiqué pour la relier
 * \param detruire une fonction pour détruire une valeur, le pointeur est indiqué pour la mettre à jour
 * \param comparer une fonction utilisée pour ordonner les élements.
 * \pre ces fonctions doivent être définies
 * \return un arbre vide prêt à recevoir des valeurs.
 */
arbre arbre_creer ( void ( * copier ) ( void * val ,
					void * * pt ) ,
		    void ( * detruire ) ( void * * pt ) ,
		    int ( * comparer ) ( void * val1 ,
					 void * val2 ) ) ;

/*!
 * Cette fonction détruit entièrement un arbre.
 * Le pointeur indiqué est mis à NULL.
 */
void arbre_detruire ( arbre * a ) ;


/*!
 * Cette fonction permet de savoir si un arbre est vide (ne contient aucune valeur) ou non.
 * \param a arbre à tester
 * \return vrai ssi l'arbre ne contient pas de valeur.
 */
bool arbre_est_vide ( arbre a ) ;

/*!
 * Cette fonction insère (une copie) d'une valeur dans un arbre binaire de recherche.
 * Si val est déjà présent dans l'arbre on ne l'insère pas une deuxième fois.
 * \param 
 * \pre ¿ à compléter ?
 */
void arbre_insertion ( arbre a ,
		       void * val ) ;


/*!
 * Cette fonction affiche les valeurs contenues dans un arbre sur une ligne selon un parcours postfixe.
 * \param f flux où afficher
 * \param afficher fonction pour afficher une valeur.
 */
void arbre_afficher_postfixe ( arbre a ,
			       FILE * f ,
			       void ( * afficher ) ( void * val ,
						     FILE * f ) 
			       ) ; 


/*!
 * Cette fonction affiche les valeurs contenues dans un arbre sur une ligne selon un parcours prefixe.
 * \param f flux où afficher
 * \param afficher fonction pour afficher une valeur.
 */
void arbre_afficher_prefixe ( arbre a ,
			      FILE * f ,
			      void ( * afficher ) ( void * val ,
						    FILE * f ) ) ; 

/*!
 * Cette fonction affiche les valeurs contenues dans un arbre sur une ligne selon un parcours infixe.
 * \param f flux où afficher
 * \param afficher fonction pour afficher une valeur.
 */
void arbre_afficher_infixe ( arbre a ,
			     FILE * f ,
			     void ( * afficher ) ( void * val ,
						   FILE * f ) ) ; 


/*!
 * Cette fonction permet de connaître le nombre de valeurs dans l'arbre.
 * (cela se fait par un calcul récursif.)
 * \return le nombre de noeuds qui compose l'arbre.
 */
int arbre_taille ( arbre a ) ;




/*
 * Cette fonction permet de suppression une val dans l'arbre.
 * \param a arbre à modifier
 * \param val valeur à supprimer
 */

void arbre_supprimer ( arbre a ,
		       void * val ) ;

/*!
 * La fonction renvoie le champ val du noeud trouvé ou NULL si aucun noeud ne contient un champ val de même clé.
 * Aucune copie n'est faite.
 * \param a arbre où chercher
 * \param val valeur à chercher
 * \return val dans l'arbre, NULL si non présent.
 */
void * arbre_rechercher ( arbre a ,
			  void * val ) ;



#endif
