#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <assert.h>

#undef NDEBUG

#include "arbres.h"

#define T_SIGLE 10 // taille de la chaîne de caractères pour le sigle
#define T_DETAILS 100 // taille de la chaîne de caractères pour la signification du sigle



typedef struct sigle_struct * sigle ; 

struct sigle_struct {
  char * court ; /* le sigle */
  char * details ; /* la description du sigle */
} ; 

/* Les trois fonctions suivantes manipulent la structure directement */

/* Création d'un struct sigle à partir de 2 chaînes de caractères*/
sigle sigle_creer ( char * court , 
		    char * details ) {
}

/* Destruction d'un sigle */
void sigle_detruire ( sigle * s ) {
}

/* Pour l'arbre les fonctions copier - afficher - detruire */
/* Attention à la signature */
void copier_sigle ( void * val , 
		    void * * pt ) {
}

void sigle_afficher ( void * val ,
		      FILE * f ) {
}

void detruire_sigle ( void * * pt ) {
}


/* la fonction de comparaison qui définit l'ordre lexicographique */
/* sur le sigle ( le champs court de la structure ) */

int sigle_comparer ( void * val1 , 
		     void * val2 ) {
}



int main ( void ) {
  FILE * f_in = fopen ( "test_arbres_sigle_in.txt" , "r" ) ; 
  FILE * f_out = fopen ( "test_arbres_sigle_out.txt" , "w" ) ; 
  arbre abr = arbre_creer ( copier_sigle , detruire_sigle , sigle_comparer ) ; 
  char s [ T_SIGLE ] ; 
  char d [ T_DETAILS ] ; 
 
  fgets ( s , T_SIGLE , f_in ) ; 
  while ( ! feof ( f_in ) ) {
    s [ strlen ( s ) - 1 ] = '\0' ; 
    fgets ( d , T_DETAILS , f_in ) ; 
    d [ strlen ( d ) - 1 ] = '\0' ; 
    sigle a1 = sigle_creer ( s , d ) ; 
    arbre_insertion ( abr , a1 ) ; 
    sigle_detruire ( & a1 ) ; 
    fgets ( s , T_SIGLE , f_in ) ; 
  } 
 
  fprintf ( f_out , "Arbre des sigles\n" ) ; 
  arbre_afficher_infixe ( abr , f_out , sigle_afficher ) ; 
  fprintf ( f_out , "\n" ) ; 
 
  fprintf ( f_out , "recherche de " ) ; 
  sigle ref = sigle_creer ( "OTAN" , "" ) ; 
  sigle_afficher ( ref , f_out ) ; 
  sigle res = arbre_rechercher ( abr , ref ) ; 
 
  if ( res!=NULL ) {
    fprintf ( f_out , "le résultat est :" ) ; 
    sigle_afficher ( res , f_out ) ; 
  }
 
  arbre_supprimer ( abr , ref ) ; 
  fprintf ( f_out , "Le résultat de la suppression\n" ) ; 
  arbre_afficher_infixe ( abr , f_out , sigle_afficher ) ; 
  fprintf ( f_out , "\n" ) ; 
  int taille = arbre_taille ( abr ) ; 
  fprintf ( f_out , "taille = %d \n" , taille ) ; 

  sigle_detruire ( &ref ) ; 
  sigle_detruire ( &res ) ; 
 
  arbre_detruire ( &abr ) ; 
 
  fclose ( f_in ) ; 
  fclose ( f_out ) ; 
 
  return 0 ; 
}
