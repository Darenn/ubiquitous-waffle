#include <assert.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#undef NDEBUG

#include "arbres.h"

#define T_SIGLE 10 // taille de la chaîne de caractères pour le sigle
#define T_DETAILS                                                              \
  100 // taille de la chaîne de caractères pour la signification du sigle

typedef struct sigle_struct *sigle;

struct sigle_struct {
  char *court;   /* le sigle */
  char *details; /* la description du sigle */
};

/* retourne une copie.
 * La mémoire nécessaire a été allouée.
*/
char *string_produce_copy(char const *const st) { return NULL; }

/* Les trois fonctions suivantes manipulent la structure directement */

/* Création d'un struct sigle à partir de 2 chaînes de caractères*/
sigle sigle_creer(char *court, char *details) {
  assert(court != NULL);
  assert(details != NULL);
  sigle s = (sigle)malloc(sizeof(struct sigle_struct));
  s->court = (char *)malloc(sizeof(char) * strlen(court) + 1);
  strcpy(s->court, court);
  s->details = (char *)malloc(sizeof(char) * strlen(details) + 1);
  strcpy(s->details, details);
  return s;
}

/* Destruction d'un sigle */
void sigle_detruire(sigle *s) {
  assert(s != NULL);
  if (*s != NULL) {
    free((*s)->court);
    free((*s)->details);
    free(*s);
    *s = NULL;
  }
}

/* Pour l'arbre les fonctions copier - afficher - detruire */
/* Attention à la signature */
void copier_sigle(void *val, void **pt) {
  assert(NULL != val);
  assert(NULL != pt);
  *pt = sigle_creer(((sigle)val)->court, ((sigle)val)->details);
  assert(NULL != *pt);
}

void sigle_afficher(void *val, FILE *f) {
  assert(val != NULL);
  assert(f != NULL);
  fprintf(f, "(%s, %s)\n", ((sigle)val)->court, ((sigle)val)->details);
}

void detruire_sigle(void **pt) {
  assert(NULL != pt);
  if (*pt != NULL) {
    sigle_detruire((sigle *)pt);
    (*pt) = NULL;
  }
}

/* la fonction de comparaison qui définit l'ordre lexicographique */
/* sur le sigle ( le champs court de la structure ) */

int sigle_comparer(void *val1, void *val2) {
  assert(val1 != NULL);
  assert(val2 != NULL);
  return strcmp(((sigle)val1)->court, ((sigle)val2)->court);
}

int main(void) {
  FILE *f_in = fopen("test_arbres_sigle_in.txt", "r");
  FILE *f_out = fopen("test_arbres_sigle_out.txt", "w");
  arbre abr = arbre_creer(copier_sigle, detruire_sigle, sigle_comparer);
  char s[T_SIGLE];
  char d[T_DETAILS];

  fgets(s, T_SIGLE, f_in);
  while (!feof(f_in)) {
    s[strlen(s) - 1] = '\0';
    fgets(d, T_DETAILS, f_in);
    d[strlen(d) - 1] = '\0';
    sigle a1 = sigle_creer(s, d);
    arbre_insertion(abr, a1);
    sigle_detruire(&a1);
    fgets(s, T_SIGLE, f_in);
  }

  fprintf(f_out, "Arbre des sigles\n");
  arbre_afficher_infixe(abr, f_out, sigle_afficher);
  fprintf(f_out, "\n");

  fprintf(f_out, "recherche de ");
  sigle ref = sigle_creer("OTAN", "");
  sigle_afficher(ref, f_out);
  sigle res = arbre_rechercher(abr, ref);

  if (res != NULL) {
    fprintf(f_out, "le résultat est :");
    sigle_afficher(res, f_out);
  }

  arbre_supprimer(abr, ref);
  fprintf(f_out, "Le résultat de la suppression\n");
  arbre_afficher_infixe(abr, f_out, sigle_afficher);
  fprintf(f_out, "\n");
  int taille = arbre_taille(abr);
  fprintf(f_out, "taille = %d \n", taille);

  sigle_detruire(&ref);

  arbre_detruire(&abr);

  fclose(f_in);
  fclose(f_out);

  return 0;
}
