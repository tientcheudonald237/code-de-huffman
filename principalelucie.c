/* DECLARATION DES BIBLIOTHEQUES */
#include"prototypelucie.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*FONCTION PRINCIPALE*/
int main(int argc ,char *argv[]){
	freq *tab =(freq*)malloc(sizeof(freq)*50);// allocation d'espace mmemoire pour notre structure de donnee sur les frequences
	FILE *fichier = fopen ("text.txt","r");//ouverture du fichier contenant le texte a coder 
	char *chain=(char*)malloc(sizeof(char)*100);//allocation de la memoire en machine pou recuperer notre notre fichier dans une chaine de caractere
	int n,h,i,j,k;
	if (fichier == NULL) exit(1);// si le fichier est null on sort du programme !!!!
	chain = recupere(fichier);//recuperation du fichier dans une chaine de caractere 
	printf("%s\n\n",chain);//affiche la chainne 
	n=strlen(chain) -1;// n ressois la taille de la chaine de caractere 
	tab = struct_frequence( chain,n);//recupere notre chaine et determine la frequence de chaque caractere 
	k = nombre_carc_dis(chain,n);// cette fonction est la pour compter le nombre de carctere distincts 
	affiche_struct_freq(tab,k);//affiche notre structure de frequences
	tab = tri(tab,k);//tri notre structure de donnee par rapport aux frequeces
	printf("nouveau trier\n");
	affiche_struct_freq(tab,k);//affiche notre structure de frequeces deja trier 
	binaire	*tab_bin = (binaire*)malloc(sizeof(binaire)*k);//allocation d'espace mmemoire pour notre structure de donnee sur les code binaires des caractere
	tab_bin = codage_carac(tab,k,n);//permet de coder nos caractere a l'aide du codage d'huffman et la place dans une structure binaire
	printf("tableau complet\n");
	affiche_tab_binaire(tab_bin,k);//affiche notre structure de donnee binaire
	codage_fichier(tab_bin,k,n);//code notre fichier texte initialle en fichier binaire grace au codage d'huffman 
	decodage_fichier(tab_bin,k,n);//decode notre fihier binaire en fichier texte initiale 
	/*fermeture des fichier et on vide les allocations memoires */ 
	fclose(fichier);
	free(tab);
	free(chain);
	free(tab_bin);
	return 0;
}
