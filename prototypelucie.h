#include<stdio.h>
#ifndef PROTOTYPE_H
#define PROTOTYPE_H

struct freq_carac
{
	char car[8];
	int occur;
	float fre;
};
typedef struct freq_carac freq;

typedef struct binaire
{
	char car[8];
	char bin[8];
}binaire;

freq* struct_frequence(char *A,int n);

int nombre_carc_dis(char *A,int n);

char* recupere( FILE *fic );

void affiche_struct_freq(freq *tab, int n);

freq* tri(freq *b,int n);

void affiche_struct_freq_binaire(freq *tab,binaire *b, int n);

binaire* codage_carac(freq *tab ,int k,int n);


void codage_fichier(binaire *tab,int k,int n);


void decodage_fichier(binaire *tab,int k,int n);


#endif 
