#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arbres.h"

typedef struct noeud_struct *noeud;

/*!
* Cette struct représente un noeud d'un arbre binaire.
* Elle contient une valeur, un fils gauche (plus petit) et un fils droit. (plus
* grand)
*/
struct noeud_struct {
  void *val;
  noeud fils_gauche;
  noeud fils_droit;
};

struct arbre_struct {
  noeud racine;
  void (*copier)(void *val, void **pt);
  void (*detruire)(void **pt);
  int (*comparer)(void *val1, void *val2);
};

/*!
* \brief Créer un noeud sans enfant et avec pour valeur val.
* \param val Un pointeur vers la valeur à copier dans le noeud.
* \param copier Un pointeur vers une fonction pour copier une valeur, un
* pointeur est indiquer pour la relier
* \return Un noeud sans enfant et avec pour valeur val.
*/
static noeud noeud_creer(void *val, void (*copier)(void *val, void **pt)) {
  assert(val != NULL);
  assert(copier != NULL);
  noeud n = (noeud)malloc(sizeof(struct noeud_struct));
  copier(val, &(n->val));
  n->fils_droit = n->fils_gauche = NULL;
}

/*!
* \brief Détruit un noeud et tous les noeuds se trouvant en dessous.
* \param n_pt Un pointeur vers le noeud à détruire.
* \param detruire Un pointeur vers une fonction pour détruire une valeur.
*/
static void noeud_detruire_recursivement(noeud *n_pt,
                                         void (*detruire)(void **pt)) {
  assert(detruire != NULL);
  if (n_pt != NULL && *n_pt != NULL) {
    // Je détruis d'abord tout les noeuds en dessous
    if ((*n_pt)->fils_gauche != NULL) {
      noeud_detruire_recursivement(&((*n_pt)->fils_gauche), detruire);
    }
    if ((*n_pt)->fils_droit != NULL) {
      noeud_detruire_recursivement(&((*n_pt)->fils_droit), detruire);
    }
    // Ensuite je me détruis
    detruire((*n_pt)->val);
    free(*n_pt);
    free(n_pt);
    n_pt = NULL;
  }
}

/* Détruit un noeud sans détruire les noeuds se trouvant en dessous.
 * Il faut donc assurer la correcte structure de l'arbre de recherche après
 * suppression.
 */
static void noeud_detruire_simple(noeud *const n_pt,
                                  void (*detruire)(void **pt)) {}

static void noeud_afficher_prefixe(noeud n, FILE *f,
                                   void (*afficher)(void *val, FILE *f)) {}

static void noeud_afficher_infixe(noeud n, FILE *f,
                                  void (*afficher)(void *val, FILE *f)) {}

static void noeud_afficher_postfixe(noeud n, FILE *f,
                                    void (*afficher)(void *val, FILE *f)) {}

int noeud_taille(noeud n) {}

arbre arbre_creer(void (*copier)(void *val, void **pt),
                  void (*detruire)(void **pt),
                  int (*comparer)(void *val1, void *val2)) {}

void arbre_detruire(arbre *a) {}

/*
 * Simplifier largement insertion, recherche et suppression
 * (factorisation de code !)
 */
static noeud *arbre_chercher_position(arbre a, void *val) {}

void arbre_insertion(arbre a, void *val) {}

void arbre_afficher_prefixe(arbre a, FILE *f,
                            void (*afficher)(void *val, FILE *f)) {}

void arbre_afficher_infixe(arbre a, FILE *f,
                           void (*afficher)(void *val, FILE *f)) {}

void arbre_afficher_postfixe(arbre a, FILE *f,
                             void (*afficher)(void *val, FILE *f)) {}

bool arbre_est_vide(arbre a) {}

int arbre_taille(arbre a) {}

void *arbre_rechercher(arbre a, void *val) {}

void arbre_supprimer(arbre a, void *val) {}
