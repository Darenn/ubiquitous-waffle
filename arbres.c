# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>

# undef NDEBUG

# include "arbres.h"


typedef struct noeud_struct * noeud ;


struct noeud_struct {
  void * val ; 
  noeud fils_gauche ; 
  noeud fils_droit ; 
} ; 


struct arbre_struct {
  noeud racine ;
  void ( * copier ) ( void * val ,
		      void * * pt )  ; 
  void ( * detruire ) ( void * * pt ) ; 
  int ( * comparer ) ( void * val1 ,
		       void * val2 ) ;
} ; 


static noeud noeud_creer ( void * val ,
			   void ( * copier ) ( void * val ,
					       void * * pt ) ) {
}


/* Détruit un noeud et tous les noeuds se trouvant en dessous. */
static void noeud_detruire_recursivement ( noeud * n_pt ,
					   void ( * detruire ) ( void * * pt ) ) {
}


/* Détruit un noeud sans détruire les noeuds se trouvant en dessous.
 * Il faut donc assurer la correcte structure de l'arbre de recherche après suppression.
 */
static void noeud_detruire_simple ( noeud * const n_pt ,
				    void ( * detruire ) ( void * * pt ) ) {
}



static void noeud_afficher_prefixe ( noeud n ,
				     FILE * f ,
				     void ( * afficher ) ( void * val ,
							   FILE * f ) ) {
}


static void noeud_afficher_infixe ( noeud n ,
				    FILE * f ,
				    void ( * afficher ) ( void * val ,
							  FILE * f ) ) {
}


static void noeud_afficher_postfixe ( noeud n ,
				      FILE * f ,
				      void ( * afficher ) ( void * val ,
							    FILE * f ) ) {
}


int noeud_taille ( noeud n ) {
}


arbre arbre_creer ( void ( * copier ) ( void * val ,
					void * * pt ) ,
		    void ( * detruire ) ( void * * pt ) ,
		    int ( * comparer ) ( void * val1 ,
					 void * val2 ) ) {
}


void arbre_detruire ( arbre * a ) {
}


/*
 * Simplifier largement insertion, recherche et suppression
 * (factorisation de code !)
 */
static noeud * arbre_chercher_position ( arbre a ,
					 void * val ) {
}


void arbre_insertion ( arbre a ,
		       void * val ) {
}


void arbre_afficher_prefixe ( arbre a ,
			      FILE * f ,
			      void ( * afficher ) ( void * val ,
						    FILE * f ) ) {
}

void arbre_afficher_infixe ( arbre a ,
			     FILE * f ,
			     void ( * afficher ) ( void * val ,
						   FILE * f ) ) {
}

void arbre_afficher_postfixe ( arbre a ,
			       FILE * f ,
			       void ( * afficher ) ( void * val ,
						     FILE * f ) ) {
}


bool arbre_est_vide ( arbre a ) {
}



int arbre_taille ( arbre a ) {
}



void * arbre_rechercher ( arbre a ,
			  void * val ) {
}


void arbre_supprimer ( arbre a ,
		       void * val ) {
}


