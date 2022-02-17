//Maramotti Lorenzo 3^F 17/02/2022
//Il programma per funzionare necessita di un file chiamato "Agenda.txt" , "AgendaAggiornata.txt" e "cnt.txt"
//Nel file "Agenda.txt" è necessario indicare il numero dell'ID (es. 1,2,3 ecc...)
//Nel file "cnt.txt" è necessario indicare il numero di contatti presenti nell'agenda
//Il numero massimo di contatti è 20; per aumentare o diminuire cambiare la chiamata iniziale alla riga 14 e cambiare N 20

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>
#include <algorithm>

#define N 20
#define MAXSTR 15



typedef struct s_arch{
	int id;
	char cognome[MAXSTR];
	char nome[MAXSTR];  
	char prefisso[MAXSTR];
	char telefono[MAXSTR];
	
} s_arch;


s_arch archivio[N]={/* 
	{1,"Rossi", "Mario","+39","3334455666"},
	{2,"Verdi", "Ugo","+39","3441122333"},
	{3,"Gagliardi", "Giovanni","+39","3455566777"},
	{4,"Plutone", "Pippo","+39","3467788999"},*/
};

int MyIndex;
//indico il numero di elementi allocati nel vettore archivio

int saveFile(int pos)
{
	int i;
	FILE* tmpf;
	tmpf=fopen("Agenda.txt" , "w");
	
	for (i=0; i<pos; i++)
	{
		fwrite(&archivio[i],sizeof(struct s_arch),1,tmpf);
		//fputs("\n" , tmpf);
	}
	
	fclose (tmpf);
	FILE*tmp;
	tmp = fopen("cnt.txt","w");
	fprintf(tmp, "%d" , i);
	fclose(tmp);
}

void Visualizza(int pos)
{ 
int i=0;
while(i<pos)
{	
 	printf("\n\nID:%d", archivio[i].id);
 	printf("\nCOGNOME:%s ", archivio[i].cognome);
	printf("\nNOME:%s ", archivio[i].nome);
	printf("\nNUMERO DI TELEFONO:%s %s", archivio[i].prefisso , archivio[i].telefono);

	i++;
	
 }
	//saveFile(pos);
}


int saveFileUpdated(int pos)
{
	int i;
	FILE* tmpf;
	tmpf=fopen("AgendaAggiornata.txt" , "w");
	
	for (i=0; i<pos; i++)
	{
		fwrite(&archivio[i],sizeof(struct s_arch),1,tmpf);
		fputs("\n" , tmpf);
	}
	
	fclose (tmpf);
}

int readFile(int pos){
	int i;
	
	FILE*ftp;
	ftp = fopen("cnt.txt", "r");
	//fread(&pos,sizeof(pos),1,ftp);
	fscanf(ftp,"%d", &MyIndex);
	fclose(ftp);

	FILE* tp;
	tp = fopen("Agenda.txt" , "r");

	for (i=0; i<pos; i++){
		fread(&archivio[i],sizeof(struct s_arch),1,tp);
	}


	fclose(tp);
	
}
int Insert(int pos)
{
	char invio;
	char c;
	
	if(pos>=N) {
		printf("\n\nHai raggiunto il limite massimo di elementi ");
		
	scanf("%c", &invio);
	return(pos);
	}
	
	archivio[pos].id = pos+1;
	
	printf("\nNuovo utente:", pos);
	printf("\nCOGNOME:");
	scanf("%s",archivio[pos].cognome);
	printf("\nNOME:");
	scanf("%s",archivio[pos].nome);
	printf("\nPREFISSO:");
	scanf("%s", archivio[pos].prefisso);
	printf("\nNUMERO DI TELEFONO:");
	scanf("%s",archivio[pos].telefono);

	pos++;
	
	saveFile(pos);
	return(pos);
	
}

void VisualizzaByCognome(int pos)
{ 
	char cognome[MAXSTR];
	int i=0, trovato=0;
	
	printf("\nQuale cognome cerchi?:");
	scanf("%s", cognome);
	for (i=0; i<pos; i++){
	 	if(strcmp(archivio[i].cognome,cognome)==0) {
	 		printf("\n\nID: %d ", archivio[i].id);
	 		printf("\nCOGNOME: %s ", archivio[i].cognome);
	 		printf("\nNOME: %s ", archivio[i].nome);
	 		printf("\nNUMERO DI TELEFONO: %s %s", archivio[i].prefisso , archivio[i].telefono);
	 		trovato=1;
		 }
 	}
 	if (trovato==0) 
		 printf("\nNon e' presente il cognome cercato:");
}

void VisualizzaByNome(int pos)
{ 
	char nome[MAXSTR];
	int j=0, trovato=0;
	
	printf("\nQuale nome cerchi?:");
 	scanf("%s", nome);
 	
	for (j=0; j<pos; j++){
	 	if(strcmp(archivio[j].nome,nome)==0) {
	 		printf("\n\nID: %d ", archivio[j].id);
	 		printf("\nCOGNOME: %s ", archivio[j].cognome);
	 		printf("\nNOME: %s ", archivio[j].nome);
	 		printf("\nNUMERO DI TELEFONO: %s %s", archivio[j].prefisso, archivio[j].telefono);
	 		trovato=1;
		 }
 	}
 	if (trovato==0) 
		 printf("\nNon e' presente il nome cercato");
}

void VisualizzaByTelefono(int pos)
{ 
	char telefono[MAXSTR];
	int g=0, trovato=0;
	
	printf("\nQuale numero telefono cerchi?:");
 	scanf("%s", telefono);
 	
	for (g=0; g<pos; g++){
	 	if(strcmp(archivio[g].telefono,telefono)==0) {
	 		printf("\n\nID: %d ", archivio[g].id);
	 		printf("\nCOGNOME: %s ", archivio[g].cognome);
	 		printf("\nNOME: %s ", archivio[g].nome);
	 		printf("\nNUMERO DI TELEFONO: %s", archivio[g].prefisso ,archivio[g].telefono);
	 		trovato=1;
		 }
 	}
 	if (trovato==0) 
		 printf("\nNon e' presente il numero telefono cercato");
}

int ReorderByCognome(int pos)
{
	int j;
	int h; 
	s_arch temp;
	
	for(j=0; j<pos; j++)
	{
		for (h=0; h<pos; h++)
		{
			if(strcmp(archivio[j].cognome , archivio[h].cognome) < 0)
			{
				temp = archivio[j];
				archivio[j] = archivio[h];
				archivio [h] = temp;
			
			}
		}
	}	
	saveFileUpdated(pos);
}



int menu_scelta(void)
{
  int selezione = 0;
  do
    {
    printf("\n" );
    printf("\n0 -> Esci");
    printf("\n1 -> Visualizza Archivio" );
    printf("\n2 -> Inserisci");
    printf("\n3 -> Ricerca per cognome");
    printf("\n4 -> Ricerca per nome" );
    printf("\n5 -> Ricerca per telefono");
    printf("\n6 -> Riordina per cognome");
    printf("\n");
    printf("\nEffettua una scelta -> " );
    scanf("%d", &selezione );
    }
    while (selezione < 0 || selezione > 6);
  return selezione;
}

int main(void)
{
    int scelta;
    readFile(4);
    
    while((scelta=menu_scelta())!=0){
    switch(scelta){
        case 1: 
                Visualizza(MyIndex);
                break;
        case 2:
                MyIndex=Insert(MyIndex);
                break;
        case 3:
                VisualizzaByCognome(MyIndex);
                break;
        case 4:
				VisualizzaByNome(MyIndex);
				break;
		case 5:
				VisualizzaByTelefono(MyIndex);
				break;
		case 6:
				ReorderByCognome(MyIndex);
				break;
             }
    }             
    return 0;
}

