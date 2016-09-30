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

/*!
* Cette struct représente un arbre binaire.
* Elle contient une racine (le premier noeud), un pointeur vers une fonction de
* copie de la valeur, un pointeur vers une fonction de destruction de la valeur,
* et un pointeur vers une fonction de comparaison de la valeur
*/
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
* \pre val et copier doivent être définis
* \return Un noeud sans enfant et avec pour valeur val.
*/
static noeud noeud_creer(void *val, void (*copier)(void *val, void **pt)) {
  assert(val != NULL);
  assert(copier != NULL);
  noeud n = (noeud)malloc(sizeof(struct noeud_struct));
  copier(val, &(n->val));
  n->fils_droit = n->fils_gauche = NULL;
  return n;
}

/*!
* \brief Détruit un noeud et tous les noeuds se trouvant en dessous.
* \param n_pt Un pointeur vers le noeud à détruire.
* \param detruire Un pointeur vers une fonction pour détruire une valeur.
* \pre detruire doit être défini.
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
    detruire(&(*n_pt)->val);
    free(*n_pt);
    *n_pt = NULL;
  }
}

/*
 * \brief Détruit un noeud sans détruire les noeuds se trouvant en dessous.
 * Il faut donc assurer la correcte structure de l'arbre de recherche après
 * suppression.
 * \param n_pt Un pointeur vers le noeud à détruire. (le pointeur ne sera pas
 * changé)
 * \param detruire Un pointeur vers une fonction pour détruire une valeur.
 * \pre detruire et n_pt doivent être définis.
 */
static void noeud_detruire_simple(noeud *const n_pt,
                                  void (*detruire)(void **pt)) {
  assert(detruire != NULL);
  assert(n_pt != NULL);
  if (*n_pt != NULL) {
    // Si j'ai pas de fils droit
    if ((*n_pt)->fils_droit == NULL) {
      // Je garde l'adresse de mon fils gauche qui me remplacera dans l'arbre
      noeud p_fils = (*n_pt)->fils_gauche;
      // Je me détruis
      detruire(&(*n_pt)->val);
      free((*n_pt));
      // Je remplace
      *n_pt = p_fils;
    } else {
      noeud p_fils_gauche = (*n_pt)->fils_gauche;
      noeud p_fils_droit = (*n_pt)->fils_droit;
      // je me détruis
      detruire(&(*n_pt)->val);
      free((*n_pt));
      // Je remplace par le fils le plus à gauche de mon fils droit
      noeud courant = p_fils_droit;
      noeud suivant = courant->fils_gauche;
      if (suivant != NULL) {
        while (suivant->fils_gauche != NULL) {
          courant = suivant;
          suivant = courant->fils_gauche;
        }
        *n_pt = suivant;
        courant->fils_gauche = NULL;
        (*n_pt)->fils_gauche = p_fils_gauche;
        (*n_pt)->fils_droit = p_fils_droit;
      } else {
        *n_pt = p_fils_droit;
        (*n_pt)->fils_gauche = p_fils_gauche;
      }
    }
  }
}

/*!
 * \brief Affiche le sous-arbre ayant pour racine le noeud n de manière prefixe.
 * \param n Le noeud à afficher.
 * \param f Le fichier de sortie.
 * \param afficher Un pointeur vers une fonction pour afficher la valeur.
 * \pre f et afficher doivent être définis.
 */
static void noeud_afficher_prefixe(noeud n, FILE *f,
                                   void (*afficher)(void *val, FILE *f)) {
  assert(f != NULL);
  assert(afficher != NULL);
  if (n != NULL) {
    afficher(n->val, f);
    noeud_afficher_prefixe(n->fils_gauche, f, afficher);
    noeud_afficher_prefixe(n->fils_droit, f, afficher);
  }
}

/*!
 * \brief Affiche le sous-arbre ayant pour racine le noeud n de manière infixe.
 * \param n Le noeud à afficher.
 * \param f Le fichier de sortie.
 * \param afficher Un pointeur vers une fonction pour afficher la valeur.
 * \pre f et afficher doivent être définis.
 */
static void noeud_afficher_infixe(noeud n, FILE *f,
                                  void (*afficher)(void *val, FILE *f)) {
  assert(f != NULL);
  assert(afficher != NULL);
  if (n != NULL) {
    noeud_afficher_infixe(n->fils_gauche, f, afficher);
    afficher(n->val, f);
    noeud_afficher_infixe(n->fils_droit, f, afficher);
  }
}

/*!
 * \brief Affiche le sous-arbre ayant pour racine le noeud n de manière postfixe
 * \param n Le noeud à afficher.
 * \param f Le fichier de sortie.
 * \param afficher Un pointeur vers une fonction pour afficher la valeur.
 * \pre f et afficher doivent être définis.
 */
static void noeud_afficher_postfixe(noeud n, FILE *f,
                                    void (*afficher)(void *val, FILE *f)) {
  assert(f != NULL);
  assert(afficher != NULL);
  if (n != NULL) {
    noeud_afficher_postfixe(n->fils_gauche, f, afficher);
    noeud_afficher_postfixe(n->fils_droit, f, afficher);
    afficher(n->val, f);
  }
}

/*!
 * \brief Renvoie la taille du sous-arbre ayant le noeud n pour racine.
 * \param n Le noeud racine.
 * \return La taille du sous-arbre ayant le noeud n pour racine.
 */
int noeud_taille(noeud n) {
  if (n != NULL) {
    return noeud_taille(n->fils_gauche) + noeud_taille(n->fils_droit) + 1;
  }
  return 0;
}

arbre arbre_creer(void (*copier)(void *val, void **pt),
                  void (*detruire)(void **pt),
                  int (*comparer)(void *val1, void *val2)) {
  assert(copier != NULL);
  assert(detruire != NULL);
  assert(comparer != NULL);
  arbre a = (arbre)malloc(sizeof(struct arbre_struct));
  a->racine = NULL;
  a->copier = copier;
  a->detruire = detruire;
  a->comparer = comparer;
  return a;
}

void arbre_detruire(arbre *a) {
  if (a != NULL) {
    noeud_detruire_recursivement(&(*a)->racine, (*a)->detruire);
    free(*a);
    *a = NULL;
  }
}

/*
 * Simplifier largement insertion, recherche et suppression
 * (factorisation de code !)
 */
static noeud *arbre_chercher_position(arbre a, void *val) {
  assert(a != NULL);
  assert(val != NULL);
  noeud *resultat = NULL;
  noeud *courant = &a->racine;
  if (!arbre_est_vide(a)) {
    while (resultat == NULL && *courant != NULL) {
      int comp = a->comparer((*courant)->val, val);
      if (comp > 0) {
        courant = &(*courant)->fils_gauche;
      } else if (comp < 0) {
        courant = &(*courant)->fils_droit;
      } else {
        resultat = courant;
      }
    }
  }
  if (*courant == NULL) {
    return courant;
  } else {
    return resultat;
  }
}

void arbre_insertion(arbre a, void *val) {
  assert(val != NULL);
  noeud *position = arbre_chercher_position(a, val);
  if (*position == NULL) {
    *position = noeud_creer(val, a->copier);
  }
}

void arbre_afficher_prefixe(arbre a, FILE *f,
                            void (*afficher)(void *val, FILE *f)) {
  assert(a != NULL);
  assert(f != NULL);
  assert(afficher != NULL);
  noeud_afficher_prefixe(a->racine, f, afficher);
}

void arbre_afficher_infixe(arbre a, FILE *f,
                           void (*afficher)(void *val, FILE *f)) {
  assert(a != NULL);
  assert(f != NULL);
  assert(afficher != NULL);
  noeud_afficher_infixe(a->racine, f, afficher);
}

void arbre_afficher_postfixe(arbre a, FILE *f,
                             void (*afficher)(void *val, FILE *f)) {
  assert(a != NULL);
  assert(f != NULL);
  assert(afficher != NULL);
  noeud_afficher_postfixe(a->racine, f, afficher);
}

bool arbre_est_vide(arbre a) {
  assert(a != NULL);
  return a->racine == NULL;
}

int arbre_taille(arbre a) {
  assert(a != NULL);
  return noeud_taille(a->racine);
}

void *arbre_rechercher(arbre a, void *val) {
  assert(a != NULL);
  assert(val != NULL);
  noeud *n = arbre_chercher_position(a, val);
  if (*n != NULL) {
    return (*n)->val;
  }
  return NULL;
}

void arbre_supprimer(arbre a, void *val) {
  assert(a != NULL);
  assert(val != NULL);
  noeud_detruire_simple(arbre_chercher_position(a, val), a->detruire);
}
