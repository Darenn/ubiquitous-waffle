# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <assert.h>

# undef NDEBUG

# include "arbres.h"

# define LG 10
# define IDX 5



void copier_int ( void * val ,
		  void * * pt ) {
  assert ( NULL != val ) ;
  assert ( NULL != pt ) ;
  * pt = ( int * ) malloc ( sizeof ( int ) ) ;
  assert ( NULL != * pt ) ;
  memcpy ( * pt , val , sizeof ( int ) ) ;
}


void detruire_int ( void * * pt ) {
  assert ( NULL != pt ) ;
  if ( * pt != NULL ) {
    free ( * pt ) ;
    ( * pt ) = NULL ;
  }
}


int comparer_int ( void * val1 ,
		   void * val2 ) {
  assert ( NULL != val1 ) ;
  assert ( NULL != val2 ) ;
  int a = * ( int * ) val1 ;
  int b = * ( int * ) val2 ;
  return a - b ;
}



void afficher_int ( void * val ,
		    FILE * f ) {
  fprintf ( f , "%d " , * ( ( int * ) ( val ) ) ) ;
}



int main ( void ) {
  FILE * f_out = fopen ( "test_arbres_int_out.txt" , "w" ) ;
  arbre abr = arbre_creer ( copier_int , detruire_int , comparer_int ) ;
  int tab [ LG ] ;

  /* Test pour l'insertion et l'affichage */
  srand ( 7845 ) ;
  for ( int i=0 ; i<10 ; i++ ) { 
    tab[i] = rand ( ) %50 ;
    fprintf ( f_out , "valeur insérée : %d \n" , tab[i] ) ;
    arbre_insertion ( abr , tab+i ) ;
  }
  fprintf ( f_out , "Arbre binaire de recherche : " ) ;
  arbre_afficher_infixe ( abr , f_out , afficher_int ) ;
  fprintf ( f_out , "\n" ) ;


 
  /* Test pour la recherche */
  int ref = tab[IDX] ;
  fprintf ( f_out , "recherche de %d dans abr : " , ref ) ; 
  void * res = arbre_rechercher ( abr , ( void * ) &ref ) ;
 
  if ( res!=NULL ) {
    if ( * ( int * ) res==ref ) 
      fprintf ( f_out , "Trouvé\n" ) ;
    else
      fprintf ( f_out , "Echec\n" ) ;
  }
  else
    fprintf ( f_out , "Elément non présent\n" ) ;

  /* Test pour la suppression */
  for ( int i=0 ; i<IDX ; i++ ) {
    int pos = tab [ rand ( ) % IDX ] ;
    fprintf ( f_out , "valeur à supprimer : %d \n" , pos ) ;
    arbre_supprimer ( abr , ( void * ) & pos  ) ; 
  }


  fprintf ( f_out , "Résultat après la suppression : " ) ;
  arbre_afficher_infixe ( abr , f_out , afficher_int ) ;
  fprintf ( f_out , "\n" ) ;
  int taille = arbre_taille ( abr ) ;
  fprintf ( f_out , "sa taille : %d \n" , taille ) ;
 
  arbre_detruire ( &abr ) ;

  fclose ( f_out ) ;

  return 0 ;
}
