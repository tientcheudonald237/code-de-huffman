#include"prototypelucie.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*------------------------------------------------------------------------------------------------------------*/

//recuperation du fichier dans une chaine de caractere : il prend en parametre un fichier et retourne une chaine de caractere contenant le fichier texte
char* recupere( FILE *fic ){
	char *chain = (char*)malloc(sizeof(char)*100) ;
	int i=0;
	/* (chain[i] = fgetc(fic)) != EOF veut dire que l'on parcoure toute les valeurs de notre fichier et a chaque fois on la stoque de suite en suite dans
																														 la chaine de caractere chain */
	while( (chain[i] = fgetc(fic)) != EOF ){
		i+=1;
	}
	return chain ;
}
/*----------------------------------------------------------------------------------*/

// cette fonction est la pour compter le nombre de carctere distincts 
int nombre_carc_dis(char *A,int n){
   	freq *D,*temp;
    int i,b,j,k=0;
	for(i=0;i<n;i++){
		if(D[i].occur != 0 ){
			temp[k]=D[i];
			k+=1;
		}
	}
	return k;
	
}
/*--------------------------------------------------------------------------------------*/

//recupere une chaine et determine la frequence de chaque caractere retourne une structure de frequences
freq* struct_frequence(char *A,int n)
{
	freq *D,*temp;
    int i,b,j,k=0,nbre_esp=0;
    float m;
	D=(freq*)malloc(sizeof(freq)*n);
	
	// je compte le nombre d'espace
	
	for(i=0;i<n-1;i++){
		if(A[i] == ' '){  
			nbre_esp +=1;
		}
	}
	/*-----------------------------------*/
	
	i=0;
	while(i<n-1){
		if(A[i] != ' '){
			j=i+1;
			m=1;
			while(j<n-1){
				if(A[j]==A[i] ){
					m=m+1;
					A[j]= ' ';	
				}
				j=j+1;
			}
			D[i].car[0]=A[i];
			D[i].occur = m;
			D[i].fre=m/(n-1-nbre_esp );// ici on soustrait a nbre_esp parceque on ne considere pas l'espace coe un caractere 
			A[i]=' ';
		}
		i=i+1;
	}
	/*--------------------------------------------------------*/
	
	//comme j'ai alloer la taille taille de ma structure grande , je la remet dans une autre en retirant les cases vides !!!!!
	temp=(freq*)malloc(sizeof(freq)*i);
	for(i=0;i<n;i++){
		if(D[i].occur != 0 ){
			temp[k]=D[i];
			k+=1;
		}
	}
	return temp;
	
}

/*---------------------------------------------------------------------------------------------*/
//tri notre structure de donnee par rapport aux frequeces

freq* tri(freq *b,int n){
	int i,j,min;
	freq temp;
		for(i=0;i<n-1;i++){ 
				min=i;
				for(j=i+1;j<=n-1;j++){
					if(b[j].fre > b[min].fre){
						min=j;
					}
					temp = b[j];
					b[j] = b[min];
					b[min] = temp;
				}
		}
	return b;
}

/*----------------------------------------------------------------------------------------------------*/

void affiche_struct_freq(freq *tab, int n){
	int i,val;
	printf("caractere\tcode_binaire\n");				
	for(i=0;i<n;i++){
		if(tab[i].car != " "){ 
		printf("%s\t\t",tab[i].car);
		printf("%f\n",tab[i].fre);
		}
	}
	printf("\n\n");
}


/*------------------------------------------------------------------------------------------------------*/

void affiche_struct_freq_binaire(freq *tab,binaire *b, int n){
	int i,val;
	printf("caractere \t\t frequence \t\t caractere \t\t code bin \n");				
	for(i=0;i<=n;i++){
		printf("%3s\t\t\t",tab[i].car);
		printf("%f\t\t",tab[i].fre);
		printf("%3s\t\t\t",b[i].car);
		printf("%s\t\n",b[i].bin);
		
	}
	printf("\n\n");
}

/*----------------------------------------------------------------------------------------------------*/

void affiche_tab_binaire(binaire *tab, int n){
	int i,val;
	printf("caractere \t   code_binaire\n");				
	for(i=0;i<n;i++){
		printf("%3s\t\t",tab[i].car);
		printf("%s\n",tab[i].bin);
	}
	printf("\n\n");
}

/*----------------------------------------------------------------------------------------------------*/
//permet de coder nos caractere a l'aide du codage d'huffman et la place dans une structure binaire et retourne une structure de donnee binaire
binaire* codage_carac(freq *tab ,int k,int n){
	binaire *tab2 = (binaire*)malloc(sizeof(binaire)*k);
	char *cok = (char*)malloc(sizeof(char)*10);//juste utiliser por recuperer une chaine et la concatener a une autre 
	int i,j,h;
	// copie dans la table binaire les carctere du fichier
	for(i=0;i<k;i++){
		tab2[i].car[0]=tab[i].car[0];
	}
	/*--------------------------------------------------------------------------------------------------------------------------*/
	/* --------------------ici nous sommes dans le principe de huffman proprement  dit !!!!!------------------------------------*/
	for(i=1;i<k;i++){
		int taille_i_1 = strlen(tab[i-1].car),taille_i = strlen(tab[i].car) ;
		cok = "1";
		for(h=0;h<taille_i;h++){
			for(j=0;j<k;j++){
				if(tab[i].car[h] == tab2[j].car[0])
					strncat(tab2[j].bin,cok,1);
			}
		}
		cok = "0";
		for(h=0;h<taille_i_1;h++){
			for(j=0;j<k;j++){
				if(tab[i-1].car[h] == tab2[j].car[0]){
					strncat(tab2[j].bin,cok,1);
				}
			}
		}
		affiche_struct_freq_binaire(tab,tab2,k-1);//meilleur vue et gestion de mon travail !!!!!
		tab[i].fre = tab[i].fre + tab[i-1].fre ;
		tab[i-1].fre = 0;
	 	strncat(tab[i].car,tab[i-1].car,taille_i_1);
 		tab = tri(tab,k);
 		/*-----------------------------------------------------------------------------------------------------------------------*/
 	}
 	
 	return tab2 ;
}

/*--------------------------------------------------------------------------------------------*/
//code notre fichier texte initialle en fichier binaire grace au codage d'huffman 
void codage_fichier(binaire *tab,int k,int n){
	FILE *fichier = fopen ("text.txt","r");
	FILE *fic_bin = fopen ("binaire.txt","w");
	int i,j;
	char* chain = (char*)malloc(sizeof(char)*100) ; 
	chain = recupere(fichier);
	printf("%s\n",chain);
	/*----------parcoure a chaque fois le fichier et remplace un caractere par son code d'huffman dans un nouveau fichier------------*/
	for(i=0;i<n;i++){
		for(j=0;j<k;j++){
			if( chain[i]  == tab[j].car[0] ){
				fputs(tab[j].bin,fic_bin);
			}
		}
	}
	/*---------------------------------------------------*/
	printf("merci le codage  marche __\n");
	fclose(fichier);
	fclose(fic_bin);
}

/*--------------------------------------------------------------*/
//le decodage qui est sensee nous redonnez notre message initiale 

void decodage_fichier(binaire *tab,int k,int n){
	FILE *fic_bin = fopen ("binaire.txt","r");
	FILE *fichier = fopen ("nouveau.txt","w");
	char *chain = (char*)malloc(sizeof(char)*100);
	chain = recupere(fic_bin);
	int min=1,z=0,taille_max_bin=strlen(tab[k-2].bin),i,j;
	while(min < taille_max_bin ){
		for(j=0;j<k;j++){
			for(i=0;i<min;i++){
				if(chain[z+i] == tab[j].bin[i] ){
					fputc(tab[j].car[0],fichier);
					z+=min;
				}
			}
		}
		min+=1;
	}
	printf(" le decodage ne marche pas !!!!! __\n");
	fclose(fichier);
	fclose(fic_bin);
}



