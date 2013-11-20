#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "GestionMemoire.h"

typedef struct TNoeud {char etat;						// Ne faut il pas faire une Enumeration des valeur possibles ? v : Vide ; p : Plein ; h : Heterogene
					  struct TNoeud **TabP;				// Tableau dynamique de pointeurs pour les 8 fils.
				     } TNoeud, *TArbre;

//////////////////////////////
// CONSULTATION
//////////////////////////////


bool EstVide(TArbre A)
{//Renvoi true si l'arbre est vide
	return (A->etat == 'v');
}

bool EstPlein(TArbre A)
{//Renvoi true si l'arbre est plein
	return (A->etat == 'p');
}

TArbre EtatFilsHetero(TArbre A, int NiemeFils)													// FilsHetero renommé en EtatFilsHetero
{//Renvoi l'état du nième fils de l'arbre (attention seulement si l'arbre est hétérogène)
	return A->TabP[NiemeFils];
}

// On aura besoin d'une primitive pour connaitre l'etat de la racine en conaissant un des fils ?

//////////////////////////////
// CONSTRUCTION
//////////////////////////////

TArbre ConsVide()
{//retourne un arbre vide
	TArbre Fv;
	Fv = (TArbre)MonMalloc(sizeof(TNoeud));
	Fv->etat = 'v';
	Fv->TabP = NULL;
	return Fv;
}

TArbre ConsPlein()
{//retourne un arbre plein
	TArbre Fp;
	Fp = (TArbre)MonMalloc(sizeof(TNoeud));
	Fp->etat = 'p';
	Fp->TabP = NULL;
	return Fp;
}

TArbre ConsH(TArbre Fh, TArbre f1, TArbre f2, TArbre f3, TArbre f4, TArbre f5, TArbre f6, TArbre f7, TArbre f8)			//Fh en entree ? (mais aussi en sortie ?? faut passer un pointeur sur Fh non ?)
{//retourne un arbre hétérogène, c'est à dire un tableau dynamique de pointeurs vers des arbres
	Fh->etat = 'h';
	Fh->TabP = (TArbre*)MonMalloc(8*sizeof(TArbre));		//Peut être une méthode plus efficace que celle-ci;
	Fh->TabP[0] = f1;										//Boucle for pour assignation ?
	Fh->TabP[1] = f2;
	Fh->TabP[2] = f3;
	Fh->TabP[3] = f4;
	Fh->TabP[4] = f5;
	Fh->TabP[5] = f6;
	Fh->TabP[6] = f7;
	Fh->TabP[7] = f8;
	return Fh;
}

//////////////////////////////
// DESTRUCTION
//////////////////////////////

void Liberer(TArbre A)
{//Libère l'arbre A, et detruit les pointeurs
	switch(A->etat)													
	{
	case('v'):
		{
			MonFree(A->TabP);		//	Pas sur pour le moment 
			MonFree(A);
			break;
		}
	case('p'):
		{
			MonFree(A->TabP);		//	Pas sur pour le moment 
			MonFree(A);
			break;
		}
	case('h'):
		{
			for(int i = 0; i < 8; i++)
			{
				MonFree(A->TabP[i]);
			}
			MonFree(A);
			break;
		}
	}
}

//////////////////////////////
// MODIFICATION
//////////////////////////////


void ModifRacine(TArbre A, TArbre NouvA)							// Hum en fait tu copies l'etat de NouvA dans l'etat de A, ca ne remplace pas l'arbre, a renommer ou a chager le corps
{//remplace l'arbre A par un autre arbre, 
	A->etat = NouvA->etat;
}

void ModifEtatRacine(TArbre A, char c)								// Je pense que tu voulais faire un truc comme ca non ?
{// Affecte à l'arbre A, l'état c
	if (c!= ('p' || 'v' || 'h'))
		printf("Caractere invalide dans ModifEtatRacine\n");
	else A->etat = 'c';
}

void ModifFils(TArbre A, TArbre NouvA)
{//remplace l'arbre A par un autre arbre
	Liberer(A);					//ATTENTION PAS SUR QUE CA FONCTIONNE A TESTER; Si tu libere A tu ne peux plus acceder a A->etat et au reste
	A->etat = NouvA->etat;
	A->TabP = NouvA->TabP;	
}
sdgegdfdg