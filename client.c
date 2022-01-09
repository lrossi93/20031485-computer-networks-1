/*===PROGETTO DI RETI 1 DI LORENZO ROSSI, matr. 20031485 - CLIENT===*/
#include "library.h"

/*===BUFFER DEL CLIENT===*/
char buffer[BUFFER_DIM] = "";

/*===MAIN===*/
int main(int argc, char *argv[]) {
	int simpleSocket = 0;
	int simplePort = 0;
	int returnStatus = 0;

	struct sockaddr_in simpleServer;

	if(3 != argc){
		fprintf(stderr, "Utilizzo: %s <server> <port>\n", argv[0]);
		exit(1);
	}
	//creazione del socket per il traffico dati
	simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(simpleSocket == -1){
		fprintf(stderr, "Impossibile creare un socket!\n");
		exit(1);
	}
	else{
		fprintf(stderr, "Socket creato!\n");
	}

	//recupero del numero della porta per la connessione
	simplePort = atoi(argv[2]);

	//creazione dell'indirizzo (l'IP viene inviato al server come argomento dell'indirizzo del server)
	memset(&simpleServer, 0, sizeof(simpleServer));
	simpleServer.sin_family = AF_INET;
	//inet_addr(argv[2], &simpleServer.sin_addr.s_addr);
	simpleServer.sin_addr.s_addr = inet_addr(argv[1]);
	simpleServer.sin_port = htons(simplePort);

	//connessione ad IP e numero porta tramite socket
	returnStatus = connect(simpleSocket, (struct sockaddr *)&simpleServer, sizeof(simpleServer));

	if(returnStatus == 0){
		fprintf(stderr, "Connessione riuscita!\n");
	}
	else{
		fprintf(stderr, "Impossibile connettersi all'indirizzo!\n");
		close(simpleSocket);
		exit(1);
	}

	while(1){
		//leggo cosa mi invia il server - il server è il PRIMO ad inviare una stringa
		//svuoto il buffer
		memset(buffer, 0, sizeof(buffer));
		//leggo il messaggio del server
		returnStatus = read(simpleSocket, buffer, sizeof(buffer));
		//se la lettura da socket è stata eseguita correttamente
		if(returnStatus > 0){
			//memorizzo il risultato (OK o ERR) su una stringa
			char *result = strtok(buffer, " ");
			//se l'esito del precedente comando è positivo (se ho ricevuto OK)
			if(strcmp(result, OK) == 0){
				//guardo qual è il prossimo token per identificare il tipo di comando
				char *type = strtok(NULL, " \n");
				//se è START ho appena iniziato la conversazione client-server
				if(strcmp(type, START) == 0){
					//mi aspetto che dopo START ci sia il messaggio di benvenuto
					system("clear");
					//stampo due testi, uno di benvenuto ed uno con i comandi per l'utente
					print_file("welcome.txt");
					print_file("options.txt");
					//inizializzo una stringa per tokenizzare ulteriormente il buffer
					char *welcome;
					//stampo, pezzo per pezzo, il messaggio di benvenuto del server
					while((welcome = strtok(NULL, " \n")) != NULL){
						printf("%s ", welcome);
					}
					puts("\n");

				}

				//se è TEXT mi aspetto il contatore
				else if(strcmp(type, TEXT) == 0){
					puts("Richiesta di analisi del testo accettata.\n");
					char *count = strtok(NULL, " \n");
					puts("");
					printf("Sono stati analizzati %s caratteri.\n\n", count);
					puts("");

				}

				//se era EXIT o QUIT mi aspetto il messaggio di commiato
				else if(strcmp(type, EXIT) == 0 || strcmp(type, QUIT) == 0){
					puts("Richiesta di disconnessione accettata.\n");
					char *goodbye;
					//stampo, pezzo per pezzo, il messaggio di commiato
					while((goodbye = strtok(NULL, " \n")) != NULL){
						printf("%s ", goodbye);
					}
					puts("");

					//chiudo la connessione
					close(simpleSocket);
					break;
				}

				//inizializzo un flag per uscire o restare nel seguente while
				int done = 0;
				while(!done){
					//variabile per scegliere il comando
					int option = 0;
					//flag per la disconnessione
					int exit_flag = 0;
					//stringa su cui caricare il numero dell'opzione
					char cmd[32] = "";
					while(1){
						printf("Selezionare un'opzione da 1 a 7: ");
						if(fgets(cmd, sizeof(cmd), stdin)){
							if(1 == sscanf(cmd, "%d", &option)){
								if(1 <= option && option <= 7) break;
								else printf("Opzione non valida!\n");
							}
							else printf("Opzione non valida!\n");
						}
					}
					//se ho scelto EXIT
					if(option == 5){
						//entro in GET_HIST
						option = 4;
						//imposto a 1 la exit_flag per permettere la disconnessione
						exit_flag = 1;
					}
					switch(option){
						case TEXT_BY_STRING:
							printf("Hai selezionato l'inserimento una stringa alla volta.\n");
							//inizializzo una stringa che conterrà l'input manuale
							char line[2048] = "";
							//inizializzo il suo indice a zero
							int line_index = 0;
							//inizializzo una stringa d'appoggio di dimensione BUFFER_DIM-9
							//9 = 3 (caratteri del contatore) + 4 (caratteri di TEXT) + 2 (spazi del protocollo)
							char string[BUFFER_DIM - 9] = "";
							//inizializzo il suo indice a zero
							int string_index = 0;
							printf("Inserire una stringa da inviare al server: ");
							//digito la stringa da analizzare
							fgets(line, sizeof(line), stdin);
							puts("");
							while(1){
								//se non ho riempito string e non ho letto tutti i caratteri di line
								if(string_index < sizeof(string)-1 && line_index < strlen(line)-1){
									//concateno a string il carattere di line all'indice line_index
									strncat(string, &line[line_index], 1);
									//incremento parallelamente entrambi gli indici
									line_index++;
									string_index++;
								}
								//se ho riempito string ma non ho letto tutti i caratteri di line
								else if(string_index == sizeof(string)-1 && line_index < strlen(line)-1){
									//copio string sul buffer;
									strncpy(buffer, string, sizeof(string));
									//creo la stringa da mandare al server
									snprintf(buffer, sizeof(buffer), "%s %s %d\n", TEXT, string, valid_chars(string));
									//invio il messaggio
									write(simpleSocket, buffer, sizeof(buffer));
									//svuoto il buffer
									memset(buffer, 0, sizeof(buffer));
									//leggo il messaggio dal server (mi aspetto OK TEXT contatore)
									returnStatus = read(simpleSocket, buffer, sizeof(buffer));
									//se la read ha successo
									if(returnStatus > 0){
										//tokenizzo il buffer - come primo token mi aspetto un OK
										char *result = strtok(buffer, " ");
										//se l'esito del precedente comando è positivo (se ho ricevuto OK)
										if(strcmp(result, OK) == 0){
											//guardo qual è il prossimo token per identificare il tipo di comando
											char *type = strtok(NULL, " \n");
											//se è TEXT
											if(strcmp(type, TEXT) == 0){
												//allora mi aspetto il contatore come ultimo token
												char *count = strtok(NULL, " \n");
												printf("Sono stati analizzati %s caratteri.\n", count);

											}
											//altrimenti il server ha fatto un errore
											else{
												fprintf(stderr, "ERRORE A LATO SERVER: MESSAGGIO DI TIPO ERRATO!\n");
											}
										}
										//se invece ricevo ERR
										else if(strcmp(result, ERR) == 0){
											fprintf(stderr, "Errore nell'azione compiuta. La connessione verrà chiusa.\n");
											//chiudo la connessione
											close(simpleSocket);
											fprintf(stderr, "Connessione chiusa.\n");

											break;
										}
									}
									//se la read fallisce
									else{
										printf("Errore di lettura dal server.\n");
										//chiudo la connessione
										close(simpleSocket);
										break;
									}

									//svuoto string
									memset(string, 0, sizeof(string));
									//azzero il suo indice per poter leggere altri caratteri da line
									string_index = 0;
								}
								//se ho letto tutti i caratteri di line (posso non aver finito di riempire string)
								else if(string_index <= sizeof(string)-1 && line_index == strlen(line)-1){
									//copio string sul buffer;
									memset(buffer, 0, sizeof(buffer));
									strncpy(buffer, string, sizeof(string));
									//creo il messaggio da mandare al server
									snprintf(buffer, sizeof(buffer), "%s %s %d\n", TEXT, string, valid_chars(string));
									//invio il messaggio
									write(simpleSocket, buffer, sizeof(buffer));
									//svuoto il buffer
									memset(buffer, 0, sizeof(buffer));
									//leggo il messaggio del server (mi aspetto OK TEXT contatore)
									returnStatus = read(simpleSocket, buffer, sizeof(buffer));
									//se la read ha successo
									if(returnStatus > 0){
										//tokenizzo il buffer - mi aspetto un OK
										char *result = strtok(buffer, " ");
										//se l'esito del precedente comando è positivo (se ho ricevuto OK)
										if(strcmp(result, OK) == 0){
											//guardo qual è il prossimo token per identificare il tipo di comando
											char *type = strtok(NULL, " \n");
											//se è TEXT, mi aspetto che il prossimo token sia il contatore
											if(strcmp(type, TEXT) == 0){
												char *count = strtok(NULL, " \n");
												printf("Sono stati analizzati %s caratteri.\n", count);

											}
											//altrimenti il server ha fatto un errore
											else{
												printf("ERRORE A LATO SERVER: MESSAGGIO DI TIPO ERRATO!\n");
											}
										}
										//se ho ricevuto ERR
										else if(strcmp(result, ERR) == 0){
											puts("Errore nell'azione compiuta. La connessione verrà chiusa.");
											//chiudo la connessione
											close(simpleSocket);
											puts("Connessione chiusa.");

											break;
										}
									}
									//se la read fallisce
									else{
										printf("Errore di lettura dal server.\n");
										close(simpleSocket);
										break;
									}
									//svuoto il buffer
									memset(string, 0, sizeof(string));
									//azzero l'indice di string
									string_index = 0;
									break;
								}
							}
							puts("");
							break;

						case TEXT_BY_FILE:
							printf("Digitare il nome del file: ");
							//inizializzo una stringa che conterrà il nome del file
							char filename_string[512];
							//inizializzo una stringa che conterrà, pezzo per pezzo, il file
							char file_string[BUFFER_DIM - 10] = "";
							//inizializzo a zero il suo indice
							int file_string_index = 0;
							//leggo una stringa da linea di comando
							fgets(filename_string, sizeof(filename_string), stdin);
							//prendo la prima parte della stringa filename_string
							char *filename = strtok(filename_string, " \n");
							//apro il file corrispondente in lettura
							FILE *fp = fopen(filename, "r");
							//se l'apertura del file ha successo
							if(fp != NULL){
								//inizializzo un carattere definito come int
								int c;
								//inizializzo un contatore di caratteri
								int tot_chars = 0;
								//ciclo di lettura da file
								while(1){
									//leggo un carattere alla volta
									c = fgetc(fp);
									//se non ho riempito file_string
									if(file_string_index < sizeof(file_string) - 1){
										//aggiungo il carattere letto a file_string
										if(c == EOF){
											//svuoto il buffer
											memset(buffer, 0, sizeof(buffer));
											//creo il messaggio da mandare al server
											snprintf(buffer, sizeof(buffer), "%s %s %d\n", TEXT, file_string, valid_chars(file_string));
											//invio il messaggio
											write(simpleSocket, buffer, sizeof(buffer));
											//svuoto il buffer
											memset(buffer, 0, sizeof(buffer));
											//leggo il messaggio del server
											returnStatus = read(simpleSocket, buffer, sizeof(buffer));
											//se la read ha successo
											if(returnStatus > 0){
												//inizializzo una stringa per tokenizzare il buffer
												char *result = strtok(buffer, " ");
												//se l'esito del precedente comando è positivo - se ho ricevuto OK
												if(strcmp(result, OK) == 0){
													//guardo qual è il prossimo token per identificare il tipo di comando
													char *type = strtok(NULL, " \n");
													//se è TEXT
													if(strcmp(type, TEXT) == 0){
														//mi aspetto il contatore
														char *count = strtok(NULL, " \n");
														//incremento il numero di caratteri totali del contatore
														tot_chars += atoi(count);
													}
													//se non è text
													else{
														fprintf(stderr, "ERRORE A LATO SERVER: MESSAGGIO DI TIPO ERRATO!\n");
													}
												}
												//se ho ricevuto ERR
												else if(strcmp(result, ERR) == 0){
													char *tok;
													while((tok = strtok(NULL, " \n")) != NULL){
														printf("tok: %s", tok);
													}
													fprintf(stderr, "Errore nell'azione compiuta. La connessione verrà chiusa.\n");
													//chiudo la connessione
													close(simpleSocket);
													fprintf(stderr, "Connessione chiusa.\n");
													break;
												}
											}
											//se la read fallisce
											else{
												fprintf(stderr, "Errore di lettura dal server.\n");
												//chiudo la connessione
												close(simpleSocket);
												break;
											}
											break;
										}
										else{
											file_string[file_string_index] = c;
											//incremento l'indice
											file_string_index++;
										}
									}
									//se ho riempito file_string oppure se ho letto EOF
									else if(file_string_index == sizeof(file_string) -1 || c == EOF){
										//svuoto il buffer
										memset(buffer, 0, sizeof(buffer));
										//creo il messaggio da mandare al server
										snprintf(buffer, sizeof(buffer), "%s %s %d\n", TEXT, file_string, valid_chars(file_string));
										//invio il messaggio
										write(simpleSocket, buffer, sizeof(buffer));
										//svuoto il buffer
										memset(buffer, 0, sizeof(buffer));
										//leggo il messaggio del server
										returnStatus = read(simpleSocket, buffer, sizeof(buffer));
										//se la read ha successo
										if(returnStatus > 0){
											//inizializzo una stringa per tokenizzare il buffer
											char *result = strtok(buffer, " ");
											//se l'esito del precedente comando è positivo - se ho ricevuto OK
											if(strcmp(result, OK) == 0){
												//guardo qual è il prossimo token per identificare il tipo di comando
												char *type = strtok(NULL, " \n");
												//se è TEXT
												if(strcmp(type, TEXT) == 0){
													//mi aspetto il contatore
													char *count = strtok(NULL, " \n");
													//incremento il numero di caratteri totali del contatore
													tot_chars += atoi(count);
												}
												//se non è text
												else{
													fprintf(stderr, "ERRORE A LATO SERVER: MESSAGGIO DI TIPO ERRATO!\n");
												}
											}
											//se ho ricevuto ERR
											else if(strcmp(result, ERR) == 0){
												char *tok;
												while((tok = strtok(NULL, " \n")) != NULL){
													printf("tok: %s", tok);
												}
												fprintf(stderr, "Errore nell'azione compiuta. La connessione verrà chiusa.\n");
												//chiudo la connessione
												close(simpleSocket);
												fprintf(stderr, "Connessione chiusa.\n");
												break;
											}
										}
										//se la read fallisce
										else{
											fprintf(stderr, "Errore di lettura dal server.\n");
											//chiudo la connessione
											close(simpleSocket);
											break;
										}
										//svuoto file_string
										memset(file_string, 0, sizeof(file_string));
										//azzero il suo indice
										file_string_index = 0;
										//metto il carattere che non entrava nel buffer precedente in file_string
										file_string[file_string_index] = c;
										//incremento l'indice, così posso riempire la prossima posizione
										file_string_index++;
										//se ho letto EOF esco dal ciclo
										if(c == EOF) break;
									}
								}
								puts("");
								printf("Sono stati analizzati %d caratteri.\n", tot_chars);
								puts("");
								fclose(fp);
							}
							//se la open fallisce
							else{
								fprintf(stderr, "Errore nell'apertura del file '%s'.\n", filename);
							}
							//imposto done a zero per rimanere nel while più interno
							done = 0;
							break;

						case TEXT_BY_WORD:
							printf("Hai selezionato l'inserimento word-by-word.\n");
							//inizializzo una stringa che possa contenere una parola
							char wbw_string[500];
							//creo un puntatore per tokenizzare la wbw_string (prendo la prima parola se ce ne sono più di una)
							char *word;
							//flag per restare/uscire dal ciclo
							int again = 1;
							//ciclo di inserimento word-by-word
							while(again){
								printf("Inserire una parola da inviare al server: ");
								//inserisco la stringa da analizzare
								fgets(wbw_string, sizeof(wbw_string), stdin);
								word = strtok(wbw_string, " ");
								//resetta buffer
								memset(buffer, 0, sizeof(buffer));
								//metto sul buffer i messaggi di protocollo e la stringa
								snprintf(buffer, sizeof(buffer), "%s %s %d\n", TEXT, word, valid_chars(word));
								//invio il buffer al server
								write(simpleSocket, buffer, sizeof(buffer));
								memset(buffer, 0, sizeof(buffer));
								returnStatus = read(simpleSocket, buffer, sizeof(buffer));
								if(returnStatus > 0){
									char *result = strtok(buffer, " ");
									//se l'esito del precedente comando è positivo (se ho ricevuto OK)
									if(strcmp(result, OK) == 0){
										//guardo qual è il prossimo token per identificare il tipo di comando
										char *type = strtok(NULL, " \n");
										//se è TEXT mi aspetto il contatore
										if(strcmp(type, TEXT) == 0){
											char *count = strtok(NULL, " \n");
											puts("");
											printf("Sono stati analizzati %s caratteri.\n", count);
											puts("");
										}
										//se non è TEXT
										else{
											fprintf(stderr, "ERRORE A LATO SERVER: MESSAGGIO DI TIPO ERRATO!\n");
										}
									}
									//se ricevo un ERR
									else if(strcmp(result, ERR) == 0){
										fprintf(stderr, "Errore nell'azione compiuta. La connessione verrà chiusa.\n");
										//chiudo la connessione
										close(simpleSocket);
										fprintf(stderr, "Connessione chiusa.\n");
										break;
									}
								}
								//se la read fallisce
								else{
									printf("Errore di lettura dal server.\n");
									//chiudo la connessione
									close(simpleSocket);
									break;
								}
								//intero che mi permette di rimanere nel ciclo di inserimento precedente
								int answer;
								//inizializzo una linea di comando tarata sulla parola più lunga in italiano, di 29 lettere
								char line[32];
								while(1){
									printf("Inserire un'altra parola? (1 = sì, 0 = no) ");
									//se voglio inserire un'altra parola, leggo la risposta corrispondente
									if(fgets(line, sizeof(line), stdin)){
										if(1 == sscanf(line, "%d", &answer)){
											if(answer == 1){
												printf("Hai scelto di continuare.\n");
												again = 1;
												break;
											}
											else if(answer == 0){
												printf("Hai scelto di uscire.\n");
												again = 0;
												break;
											}
										}
									}
								}
							}
							//imposto done a zero per rimanere nel ciclo di invio comandi
							done = 0;
							break;

						case GET_HIST:
							//svuoto il buffer
							memset(buffer, 0, sizeof(buffer));
							//creo il messaggio da mandare al server, a seconda del comando inserito dall'utente
							if(!exit_flag){
								puts("Hai richiesto l'istogramma.");
								snprintf(buffer, sizeof(buffer), "%s\n", HIST);
							}
							else{
								puts("Hai richiesto l'istogramma e la disconnessione.");
								snprintf(buffer, sizeof(buffer), "%s\n", EXIT);
							}
							//invio il messaggio
							write(simpleSocket, buffer, sizeof(buffer));
							//inizializzo una stringa su cui caricare tutti i messaggi del server
							char hist_string[2048] = "";
							//svuoto il buffer
							memset(buffer, 0, sizeof(buffer));
							//leggo dal buffer 1 carattere alla volta
							while(read(simpleSocket, buffer, 1)){
								//concateno il carattere letto su hist_string
								strcat(hist_string, buffer);
								//se ho letto un '\n'
								if(strcmp(buffer, "\n") == 0){
									//guardo se ho ricevuto una stringa " END\n"
									char *last = strrchr(hist_string, 0x20);
									//se sì, esco dal ciclo di lettura
									if(strcmp(" END\n", last) == 0) break;
								}
							}
							puts("");
							printf("Ecco l'istogramma richiesto:");
							//tokenizzo exit_string, che contiene tutto quello che è stato inviato dal server
							char *hist_temp = strtok(hist_string, " \n");
							//inizializzo una stringa su cui scrivere il messaggio senza delimitatori
							char hist_for_user[2048] = "";
							//finchè non sono alla fine di hist_string
							while(hist_temp != NULL){
								//se ho ricevuto OK (nel caso anche di più stringhe ricevute dal server) vado a capo
								if(strcmp(hist_temp, OK) == 0) puts("");
								//se ho ricevuto HIST non compio azioni
								else if(strcmp(hist_temp, HIST) == 0);
								//se ho ricevuto END sono alla fine dell'istogramma, quindi esco dal ciclo di stampa
								else if(strcmp(hist_temp, END) == 0){
									//puts("");
									break;
								}
								//altrimenti stampo il token
								else{
									//printf("%s ", hist_temp);
									//creo hist_for_user, da passare alla funzione print_hashtogram
									strcat(hist_for_user, hist_temp);
									strcat(hist_for_user, " ");
								}
								hist_temp = strtok(NULL, " \n");
							}
							//puts("Istogramma per l'utente:");
							hist_for_user[strlen(hist_for_user)+1] = '\0';
							print_hashtogram(hist_for_user);
							puts("");
							//svuoto il buffer
							memset(buffer, 0, sizeof(buffer));
							//se exit_flag è 0 rimango nel ciclo, altrimenti esco e leggo il messaggio del server
							if(!exit_flag) done = 0;
							else done = 1;
							break;

						case EXIT_NO_HIST:
							puts("Hai richiesto la chiusura della connessione.");
							//svuoto il buffer
							memset(buffer, 0, sizeof(buffer));
							//creo la stringa da mandare al server
							snprintf(buffer, sizeof(buffer), "%s\n", QUIT);
							//invio il messaggio
							write(simpleSocket, buffer, sizeof(buffer));
							//setto done a uno per leggere il messaggio di accettazione e commiato del server
							done = 1;
							break;

						case OPTIONS_AGAIN:
							puts("Hai chiesto di rivedere le opzioni.\n");
							//stampo a schermo il file con le regole
							print_file("options.txt");
							//setto done a zero per rimanere nel ciclo più interno
							done = 0;
							break;

						default:
							fprintf(stderr, "Opzione non valida!\n");
							//setto done a zero per rimanere nel ciclo più interno
							done = 0;
					}
				}
			}
			//se ho ricevuto ERR
			else if(strcmp(result, ERR) == 0){
				fprintf(stderr, "Errore nell'azione compiuta. La connessione verrà chiusa.\n");
				//chiudo la connessione
				close(simpleSocket);
				fprintf(stderr, "Connessione chiusa.\n");
				break;
			}
		}
		//se la read fallisce
		else{
			fprintf(stderr, "Impossibile leggere dal socket.\n");
			//chiudo la connessione
			close(simpleSocket);
			fprintf(stderr, "Connessione chiusa.\n");
			break;
		}
	}
	return 0;
}
