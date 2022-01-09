/*===PROGETTO DI RETI 1 DI LORENZO ROSSI, matr. 20031485 - FUNZIONI===*/
#include "library.h"

/*===DATA UNA STRINGA, INCREMENTA L'ELEMENTO DELL'ARRAY hist[] CORRISPONDENTE AL CARATTERE alnum===*/
void string_to_hist(char *string, int hist[], int dim){
	for(int i=0; i<strlen(string); i++){
		if(isalnum(string[i])>0){
			switch(string[i]){
				case 'A':
					hist[0]++;
					break;
				case 'B':
					hist[1]++;
					break;
				case 'C':
					hist[2]++;
					break;
				case 'D':
					hist[3]++;
					break;
				case 'E':
					hist[4]++;
					break;
				case 'F':
					hist[5]++;
					break;
				case 'G':
					hist[6]++;
					break;
				case 'H':
					hist[7]++;
					break;
				case 'I':
					hist[8]++;
					break;
				case 'J':
					hist[9]++;
					break;
				case 'K':
					hist[10]++;
					break;
				case 'L':
					hist[11]++;
					break;
				case 'M':
					hist[12]++;
					break;
				case 'N':
					hist[13]++;
					break;
				case 'O':
					hist[14]++;
					break;
				case 'P':
					hist[15]++;
					break;
				case 'Q':
					hist[16]++;
					break;
				case 'R':
					hist[17]++;
					break;
				case 'S':
					hist[18]++;
					break;
				case 'T':
					hist[19]++;
					break;
				case 'U':
					hist[20]++;
					break;
				case 'V':
					hist[21]++;
					break;
				case 'W':
					hist[22]++;
					break;
				case 'X':
					hist[23]++;
					break;
				case 'Y':
					hist[24]++;
					break;
				case 'Z':
					hist[25]++;
					break;
				case 'a':
					hist[26]++;
					break;
				case 'b':
					hist[27]++;
					break;
				case 'c':
					hist[28]++;
					break;
				case 'd':
					hist[29]++;
					break;
				case 'e':
					hist[30]++;
					break;
				case 'f':
					hist[31]++;
					break;
				case 'g':
					hist[32]++;
					break;
				case 'h':
					hist[33]++;
					break;
				case 'i':
					hist[34]++;
					break;
				case 'j':
					hist[35]++;
					break;
				case 'k':
					hist[36]++;
					break;
				case 'l':
					hist[37]++;
					break;
				case 'm':
					hist[38]++;
					break;
				case 'n':
					hist[39]++;
					break;
				case 'o':
					hist[40]++;
					break;
				case 'p':
					hist[41]++;
					break;
				case 'q':
					hist[42]++;
					break;
				case 'r':
					hist[43]++;
					break;
				case 's':
					hist[44]++;
					break;
				case 't':
					hist[45]++;
					break;
				case 'u':
					hist[46]++;
					break;
				case 'v':
					hist[47]++;
					break;
				case 'w':
					hist[48]++;
					break;
				case 'x':
					hist[49]++;
					break;
				case 'y':
					hist[50]++;
					break;
				case 'z':
					hist[51]++;
					break;
				case '0':
					hist[52]++;
					break;
				case '1':
					hist[53]++;
					break;
				case '2':
					hist[54]++;
					break;
				case '3':
					hist[55]++;
					break;
				case '4':
					hist[56]++;
					break;
				case '5':
					hist[57]++;
					break;
				case '6':
					hist[58]++;
					break;
				case '7':
					hist[59]++;
					break;
				case '8':
					hist[60]++;
					break;
				case '9':
					hist[61]++;
					break;
			}
		}
	}
}

/*===STAMPA SULLA STRINGA string L'ISTOGRAMMA===*/
void print_hist(char *string, int hist[], int dim){
	int i = 0;
	while(i < dim){
		switch(i){
			case 0:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "A:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 1:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "B:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 2:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "C:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 3:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "D:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 4:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "E:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 5:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "F:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 6:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "G:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 7:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "H:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 8:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "I:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 9:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "J:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 10:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "K:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 11:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "L:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 12:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "M:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 13:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "N:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 14:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "O:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 15:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "P:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 16:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "Q:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 17:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "R:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 18:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "S:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 19:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "T:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 20:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "U:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 21:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "V:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 22:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "W:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 23:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "X:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 24:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "Y:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 25:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "Z:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 26:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "a:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 27:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "b:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 28:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "c:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 29:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "d:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 30:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "e:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 31:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "f:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 32:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "g:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 33:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "h:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 34:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "i:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 35:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "j:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 36:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "k:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 37:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "l:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 38:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "m:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 39:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "n:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 40:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "o:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 41:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "p:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 42:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "q:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 43:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "r:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 44:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "s:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 45:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "t:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 46:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "u:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 47:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "v:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 48:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "w:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 49:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "x:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 50:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "y:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 51:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "z:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 52:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "0:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 53:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "1:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 54:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "2:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 55:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "3:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 56:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "4:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 57:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "5:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 58:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "6:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 59:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "7:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 60:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "8:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
			case 61:
				if(hist[i] > 0){
					char data_str[10] = "";
					snprintf(data_str, sizeof(data_str), "9:%d", hist[i]);
					strcat(string, data_str); strcat(string, " ");
				}
				break;
		}
		i++;
	}
	//strcat(string, END);
	//strcat(string, "\n");
}

/*===FUNZIONI CLIENT===*/
/*Stampa a schermo un file di testo*/
void print_file(char *filename){
	FILE *fp = fopen(filename, "r");
	if(fp != NULL){
		char c;
		while((c = fgetc(fp)) != EOF){
			printf("%c", c);
		}
		puts("");
	}
	else{
		fprintf(stderr, "Errore nell'apertura del file %s\n", filename);
	}

	fclose(fp);
}

/*Conta i caratteri alnum in una stringa*/
int valid_chars(char *string){
	int count = 0;
	int i = 0;
	while(string[i] != '\0'){
		if(isalnum(string[i]) > 0) count++;
		i++;
	}
	return count;
}

/*Memorizza e stampa la stringa HIST, passata senza delimitatori*/
void print_hashtogram(char *string){
	int size = HIST_DIM;
	int hist_qty[size];
	char *end_str;
	char *token = strtok_r(string, " ", &end_str);
	int i = 0;
	char charstring[64] = "";
	while(token != NULL){
		char *end_token;
		char *token2 = strtok_r(token, ":", &end_token);
		strcat(charstring, token2);
		token2 = strtok_r(NULL, ":", &end_token);/
		hist_qty[i] = atoi(token2);
		token = strtok_r(NULL, " ", &end_str);
		i++;
	}
	size = strlen(charstring);

	//trovo max per scalare
	int max = 0;
	for(int j=0; j<size-1; j++){
		if(max < hist_qty[j]) max = hist_qty[j];
	}
	//assegno fattore di scala
	int scaling;
	if(1 <= max && max < 50) scaling = 1;
	else if(50 <= max && max < 100) scaling = 10;
	else if(100 <= max && max < 500) scaling = 25;
	else if(500 <= max && max < 1000) scaling = 50;
	else if(1000 <= max && max < 5000) scaling = 100;
	else if(5000 <= max && max < 10000) scaling = 500;
	else if(10000 <= max && max < 50000) scaling = 1000;
	else if(50000 <= max && max < 100000) scaling = 5000;
	else scaling = 10000;

	i = 0;
	while(i < strlen(charstring)){
		printf("%c: ", charstring[i]);
		for(int j=0; j<hist_qty[i]; j++){
			if(j%scaling == 0) printf("#");
		}
		printf("(%d)\n", hist_qty[i]);
		i++;
	}
}
