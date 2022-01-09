/*===PROGETTO DI RETI 1 DI LORENZO ROSSI, matr. 20031485 - SERVER===*/
#include "library.h"

/*===BUFFER DEL SERVER===*/
char buffer[BUFFER_DIM];

/*===MAIN===*/
int main(int argc, char *argv[]) {
	int simpleSocket = 0;
	int simplePort = 0;
	int returnStatus = 0;
	struct sockaddr_in simpleServer;

	if(2 != argc){
		fprintf(stderr, "Usage: %s <port>\n", argv[0]);
		exit(1);
	}

	simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(simpleSocket == -1){
		fprintf(stderr, "Impossibile creare un socket!\n");
		exit(1);
	}else{
		fprintf(stderr, "Socket creato!\n");
	}

	//recupero il numero di porta su cui ascoltare richieste di connessione
	simplePort = atoi(argv[1]);

	//costruisco la struttura di un indirizzo
	//uso INADDR_ANY per fare bind con tutti gli indirizzi locali
	memset(&simpleServer, 0, sizeof(simpleServer));
	simpleServer.sin_family = AF_INET;
	simpleServer.sin_addr.s_addr = htonl(INADDR_ANY);
	simpleServer.sin_port = htons(simplePort);

	//faccio bind tra indirizzo e porta con il socket
	returnStatus = bind(simpleSocket,(struct sockaddr *)&simpleServer,sizeof(simpleServer));

	if(returnStatus == 0){
		fprintf(stderr, "Bind effettuato!\n");
	}else{
		fprintf(stderr, "Impossibile effettuare il bind!\nSUGGERIMENTO: provare con un'altra porta tra 10000 e 20000\n");
		close(simpleSocket);
		exit(1);
	}

	//ascolto richieste di connessione
	returnStatus = listen(simpleSocket, 5);

	if(returnStatus == -1){
		fprintf(stderr, "Impossibile ricevere dati sul socket!\n");
		close(simpleSocket);
		exit(1);
	}

	while(1){
		struct sockaddr_in clientName = { 0 };
		int simpleChildSocket = 0;
		int clientNameLength = sizeof(clientName);

		//rimango in attesa di connessioni
		simpleChildSocket = accept(simpleSocket,(struct sockaddr *)&clientName, &clientNameLength);

		if(simpleChildSocket == -1){
			fprintf(stderr, "Impossibile accettare connessioni!\n");
			close(simpleSocket);
			exit(1);
		}
		else{
			printf("Un client si è connesso.\n");
		}

		//messaggio da inviare al client
		snprintf(buffer, sizeof(buffer), "%s %s %s\n", OK, START, WELCOME_MSG);
		write(simpleChildSocket, buffer, strlen(buffer));
		//svuoto il buffer
		memset(buffer, 0, sizeof(buffer));
		//array con le quantità per ogni carattere alnum - per HIST
		int hist[HIST_DIM] = { 0 };

		//while interno per leggere-elaborare-scrivere
		while(1){
			//leggo il messaggio del client
			int returnStatus = read(simpleChildSocket, buffer, sizeof(buffer));
			if(returnStatus > 0){
				//flag per la validità del contatore
				int valid_counter_flag = 0;
				//flag per accodare il comando EXIT al comando HIST
				int exit_flag = 0;
				//copio il buffer su una stringa ausiliaria
				char *ex_buffer = malloc(512*sizeof(char));
				strcpy(ex_buffer, buffer);
				//prendo il primo token, che sintatticamente dovrebbe essere il comando
				char *command = strtok(ex_buffer, " \n");
				//inizializzo il numero del comando
				int command_no;
				//assegno il numero del comando corrispondente al token command
				if(strcmp(command, TEXT) == 0) command_no = COMMAND_TEXT;
				else if(strcmp(command, HIST) == 0) command_no = COMMAND_HIST;
				else if(strcmp(command, EXIT) == 0){
					command_no = COMMAND_HIST;
					exit_flag = 1;
				}
				else if(strcmp(command, QUIT) == 0) command_no = COMMAND_QUIT;
				else command_no = COMMAND_INVALID;
				switch(command_no){
					case COMMAND_TEXT:
						if(1);
						//inizializzo una stringa su cui caricare i valori alnum ricevuti
						char string[2048] = "";
						//inizializzo una stringa che punti al contatore (compreso il carattere '\n')
						char *count_nl;
						//cerco l'ultima occorrenza dello spazio " " (0x20)
						count_nl = strrchr(buffer, 0x20);
						//tolgo lo spazio dalla stringa contatore (rimane con '\n')
						count_nl = strtok(count_nl, " ");
						//se il token count_nl è NULL
						if(count_nl == NULL){
							//svuoto il buffer
							memset(buffer, 0, sizeof(buffer));
							//creo un messaggio di errore
							snprintf(buffer, sizeof(buffer), "%s %s %s\n", ERR, SYNTAX, ERR_INVALID_COUNTER);
							//invio il messaggio
							write(simpleChildSocket, buffer, strlen(buffer));
							break;
						}
						//altrimenti
						else{
							//alloco memoria per 7 caratteri (posso ospitare contatori fino a 9'999'999)
							char *count = malloc(7*sizeof(char));
							//copio il contatore sulla stringa count, che considero da qui in poi
							strcpy(count, count_nl);
							//tolgo il carattere "\n" dalla stringa contatore
							count = strtok(count, "\n");
							//controllo che il contatore sia esclusivamente numerico (solo caratteri digit)
							for(int i = 0; i < strlen(count); i++){
								//se trovo un carattere non-digit nel contatore
								if(isdigit(count[i]) <= 0){
									valid_counter_flag = 0;
									break;
								}
								//altrimenti
								else{
									valid_counter_flag = 1;
								}
							}
							//se il contatore è interamente numerico
							if(valid_counter_flag){
								//tolgo il comando dal buffer
								command = strtok(buffer, " ");
								//definisco una stringa d'appoggio per memorizzare i token
								char *temp;
								//confronto la lunghezza del testo con il contatore
								while((temp = strtok(NULL, " ")) != NULL){
									//se il token è diverso dal contatore con '\n'
									if(strcmp(count_nl, temp) != 0){
										//inizializzo un contatore per l'indice dei caratteri di temp
										int j = 0;
										//finchè non arrivo alla fine di temp
										while(temp[j] != '\0'){
											//se temp[j] è alfanumerico
											if(isalnum(temp[j]) > 0){
												//lo concateno alla stringa d'appoggio string
												strncat(string, &temp[j], 1);
											}
											//incremento l'indice
											j++;
										}
									}
								}
								//se la lunghezza della stringa d'appoggio corrisponde al contatore ricevuto dal client
								if(strlen(string) == atoi(count)){
									//svuoto il buffer
									memset(buffer, 0, sizeof(buffer));
									//creo la stringa di accettazione del testo
									snprintf(buffer, sizeof(buffer), "%s %s %s\n", OK, TEXT, count);
									//invio il messaggio
									write(simpleChildSocket, buffer, strlen(buffer));
									//memorizzo i caratteri accettati sull'array hist
									string_to_hist(string, hist, HIST_DIM);
								}
								//altrimenti
								else{
									//svuoto il buffer
									memset(buffer, 0, sizeof(buffer));
									//creo la stringa di errore sintattico (contatore errato)
									snprintf(buffer, sizeof(buffer), "%s %s %s\n", ERR, SYNTAX, ERR_WRONG_COUNTER);
									//invio il messaggio
									write(simpleChildSocket, buffer, strlen(buffer));
								}
							}
							//se il contatore non è interamente numerico
							else{
								//svuoto il buffer
								memset(buffer, 0, sizeof(buffer));
								//creo la stringa di errore sintattico (contatore non presente o non valido)
								snprintf(buffer, sizeof(buffer), "%s %s %s\n", ERR, SYNTAX, ERR_INVALID_COUNTER);
								//invio il messaggio
								write(simpleChildSocket, buffer, strlen(buffer));
							}
						}
						break;

					case COMMAND_HIST:
						//svuoto il buffer
						memset(buffer, 0, sizeof(buffer));
						//creo una stringa su cui caricare l'istogramma
						char hist_string[2048] = "";
						//carico l'istogramma su exit_string
						print_hist(hist_string, hist, HIST_DIM);
						//tokenizzo hist_string
						char *hist_temp = strtok(hist_string, " ");
						//se l'istogramma non contiene coppie "lettera:quantità"
						if(hist_temp == NULL){
							//creo la stringa di fine istogramma
							snprintf(buffer, sizeof(buffer), "%s %s %s\n", OK, HIST, END);
							//invio il messaggio
							write(simpleChildSocket, buffer, sizeof(buffer));
							//esco dal ciclo
							break;
						}
						//se l'istogramma non è vuoto lo carico sul buffer e lo mando
						else{
							snprintf(buffer, sizeof(buffer), "%s %s %s ", OK, HIST, hist_temp);
							//finchè non sono alla fine di exit_string
							while((hist_temp = strtok(NULL, " ")) != NULL){
								//se la dimensione attuale del buffer + quella del token superano BUFFER_DIM
								if(strlen(buffer) + strlen(hist_temp) > BUFFER_DIM - 1){
									strcat(buffer, "\n");
									//invio il messaggio
									write(simpleChildSocket, buffer, strlen(buffer));
									//svuoto il buffer
									memset(buffer, 0, sizeof(buffer));
									//creo un nuovo messaggio con il token che non ho inserito nel precedente
									snprintf(buffer, sizeof(buffer), "%s %s %s ", OK, HIST, hist_temp);
								}
								//altrimenti concateno il token al buffer
								else{
									strcat(buffer, hist_temp);
									strcat(buffer, " ");
								}
							}
							//invio tutto quello che è rimasto sul buffer
							strcat(buffer, "\n");
							write(simpleChildSocket, buffer, sizeof(buffer));
							//svuoto il buffer
							memset(buffer, 0, sizeof(buffer));
							//carico il messaggio di fine istogramma
							snprintf(buffer, sizeof(buffer), "%s %s %s\n", OK, HIST, END);
							//invio il messaggio
							write(simpleChildSocket, buffer, strlen(buffer));
						}
						//se ho ricevuto il comando HIST eseguo il break, altrimenti proseguo con EXIT
						if(!exit_flag) break;

					case COMMAND_EXIT:
						//svuoto il buffer
						memset(buffer, 0, sizeof(buffer));
						//carico il messaggio con END
						snprintf(buffer, sizeof(buffer), "%s %s %s\n", OK, EXIT, GOODBYE_MSG);
						//invio il messaggio
						write(simpleChildSocket, buffer, sizeof(buffer));
						//chiudo la connessione
						close(simpleChildSocket);
						break;

					case COMMAND_QUIT:
						//svuoto il buffer
						memset(buffer, 0, sizeof(buffer));
						//creo la stringa di commiato da inviare
						snprintf(buffer, sizeof(buffer), "%s %s %s\n", OK, QUIT, GOODBYE_MSG);
						//invio il messaggio
						write(simpleChildSocket, buffer, sizeof(buffer));
						//chiudo la connessione
						close(simpleChildSocket);
						break;

					case COMMAND_INVALID:
						//svuoto il buffer
						memset(buffer, 0, sizeof(buffer));
						//creo la stringa di errore
						snprintf(buffer, sizeof(buffer), "%s %s\n", ERR, ERR_INVALID_COMMAND);
						//invio il messaggio
						write(simpleChildSocket, buffer, strlen(buffer));
						//chiudo la connessione
						close(simpleChildSocket);
						break;
				}
			}
			else if(returnStatus == -1){
				fprintf(stderr, "Client disconnesso.\n");
				break;
			}
			else{
				fprintf(stderr, "Client disconnesso forzatamente.\nReturn Status: %d\n", returnStatus);
				break;
			}
		}
		close(simpleChildSocket);
	}
	close(simpleSocket);

	return 0;
}
