
//Impiccato in C!


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#define vite 6




                     //-------------------------------------\\
                            // *PAROLA RANDOM DA FILE* \\
                     //-------------------------------------\\


char **openfile(int *);
char *randomword(void);


char *randomword(void){  //individuazione posizione parola random 

    static int indexfile;  //dichiaro indice posizione parola nel file
    static char **file;

    if (indexfile == 0)  //se indice è uguale a 0 ne genero uno casuale
        file = openfile(&indexfile);
    srand(clock());
    return file[rand() % (indexfile-1)];
}




char **openfile(int *indexfile){  //lettura e allocazione memoria per la stringa
  
  
    FILE *fp;
    
    int irw=0;
    char word[50];  //lunghezza massima parola
    
    char **words = malloc(sizeof(char *));  //alloco abbastanza spazio per puntatore della parola
    char **tempword;
    
    fp = fopen("nomicomuni.txt", "r");  //apro file .txt in modo formattato
    
    
    
    while(fscanf(fp,"%s", word) == 1){  //mentre i caratteri letti sono = 1
    
        words[irw] = strdup(word); //alloco spazio per puntatore stringa parola copiata
        irw++;
        tempword = realloc(words, sizeof(char *)*(irw+1)); //incremento dimensione parola di 1
        words = tempword;
    }
    
    
    fclose(fp);  //chiudo file 
    *indexfile = irw;  //indice nel file = indice parola random
    
    return words;
}








            //Funzione per stampare dell'impiccato
void printBody(int errori, char* body){

	printf("\tErrori: %d\n", errori);

	switch(errori) {

		case 6: body[6] = '\\'; break;
		case 5: body[5] = '/'; break;
		case 4: body[4] = '\\'; break;
		case 3: body[3] = '|'; break;
		case 2: body[2] = '/'; break;
		case 1: body[1] = ')', body[0] = '('; break;
		default: break;

	}

	printf("\t _________\n"
	       "\t|         |\n"
	       "\t|        %c %c\n"
	       "\t|        %c%c%c\n"
	       "\t|        %c %c\n"
	       "\t|             \n"
	       "\t|             ", body[0], body[1], body[2],
	       body[3], body[4], body[5], body[6]);
}






int main(){
    
    
    int i; // -> Indice array lettere parola da indovinare
    int j; // -> Contatore per nascondere lettere da indovinare 
    int k; // -> Indice array da rendere vero se la lettera viene indovinata
    int m; // -> Indice array controllo vittoria
    int errori = 0; // -> Contatore errori
    int gameover = 0; // -> Variabile dicotomica per determinare vittoria
    int found = 0;  //Flag lettera trovata
    int flagerrlett;  //Flag per evitare ripetizione inserimento del tentativo
    int endmode; // -> Indica se il giocatore ha terminato vincendo o perdendo
    int ctwhile = 0;  //Contatore cicli di gioco
    
    
    
    char stop;  //stop nel ciclo

    char risposta;
    
    char *body = malloc(vite+1);
    
    char *parola;
    parola = randomword();
    
    int lenword= strlen(parola);
    
    char errlettere[vite];  //Array lettere sbagliate
    char tentantivitot[vite];  //Array lettere tentativi



    
    
    
    // arrword[i] è vero se il carattere di indice [i] viene indovinato
    //Inizializzo a falso l'array delle lettera della parola da indovinare
    int arrword[lenword];
  
    for (i=0; i < lenword; ++i) {
         arrword[i] = 0;
    }
    
    
    
    //printf("\t Parola da indovinare:%s", parola);  //stamp test
    
    
    printf("\n\n");
    
    
    printf("\t------------------------\n");
    printf("\t| Gioco dell'impiccato |\n");
    printf("\t------------------------");


    

    
            //Ripeto finché non vince*
    while (gameover == 0) {

    ctwhile += 1;


    printf("\n\n\n\n");
    
    
    
    
    printf("\tLettere sbagliate: ");  //Stampo lettere inseri errate
    
	if(errori == 0) printf("Nessuna\n");
	
	for (int u = 0; u < errori; u++){
		printf("%c", errlettere[u+1]);
	}
	
	
	
	printBody(errori, body);  //Stampo impiccato
    
    
    
    
        //Stampo una parola con "_ " a posto delle lettere non indovinate
    printf("\tLa parola è: ");
    
    for(j=0; j < lenword; j++){
      
      if (arrword[j])
        printf("%c", parola[j]);
      else 
        printf("_ ");
      
    }
        
        
        
        
    printf("\n\n\n");




        //Chiedo prossima lettera
    printf("\tProssima lettera > ");
    scanf("%c", &risposta);
    scanf("%c", &stop);
    
    


            //Controllo se la lettera è già stata inserita
    for(int u=0; u<vite; u++){
        if(errlettere[u+1] == risposta) flagerrlett = 1;
        if(tentantivitot[u+1] == risposta) flagerrlett = 1;
    }
    
    
    
    while(flagerrlett==1){
            
            printf("\n\n");

            printf("\t------------------------\n");
            printf("\t| Lettera già inserita |\n");
            printf("\t------------------------\n\n\n");

            printf("\tProssima lettera > ");

            scanf("%c", &risposta);
            scanf("%c", &stop);
            flagerrlett = 0;
            
            for(int u=0; u<vite; u++){
                if(errlettere[u+1] == risposta) flagerrlett = 1;
            if(tentantivitot[u+1] == risposta) flagerrlett = 1;
           }
            
    }
    
    
    risposta = tolower(risposta);
    

    tentantivitot[ctwhile-1] = risposta;

    

    
    


    found=0;
    

        //Definisco vere le posizioni arrword[i] se corrispondono alla lettera data
    for(k=0; k < lenword; k++){
        
      if (parola[k] == risposta){
        arrword[k] = 1;
        found=1;
 
      }
    }
    
    
    if(found==0){ //Se nessuna lettera è stata trovata incremento gli errori
        errori+=1;  
        errlettere[errori] = risposta;
    }    
    
    
    
    
    

        //Determino se il giocatore ha vinto controllando valori indici arrword
    gameover=1;
    
    for(m = 0; m < lenword; m++) {
    
      if(arrword[m]==0){
          gameover=0;
          endmode=0;
      }
    }
   
   if(errori>=6){
       gameover=1;
       endmode=1;
   }

   
  }
  
  
  
  
          //Determino la fine del gioco (vittoria o sconfitta)
  if(endmode==0){
        printf("\n\n");
        printf("\t-------------------------\n");
        printf("\tHai vinto! La parola è '%s'\n", parola);
        printf("\tHai indovinato con %d errori\n", errori);
        printf("\t-------------------------\n");
    }
        
    else if(endmode==1){
        printf("\n\n");
        printf("\t---------------------------------------------\n");
        printf("\t Impiccato! Hai superato i tentativi massimi.\n");
        printf("\t La parola era '%s'\n", parola);
        printf("\t---------------------------------------------\n");

  }

 
 
    
}
