#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

static int feld[9][9];
static int control[9][9];
static int ux[50] = {0};
static int uy[50] = {0};
static int un[50]; // = { 0 };
static int i = 0;
int DAU_Eingabe(char* prompt, int min, int max, int versuche) {
	int i;
	if (versuche < 1) {
		printf(">>> Programmabbruch: DAU erkannt!!! <<<\n\n");
		return 0;
	}
	// prompt ausgeben
	printf(prompt);
	// int-Wert einlesen und Buchstaben abfangen
	fflush(stdin);
	if (scanf("%d", &i) != 1) {
		printf(">>> Fehlermeldung: Bitte ganzzahligen Wert eingeben.<<<\n");
		return DAU_Eingabe(prompt, min, max, versuche - 1);
	}
	// Wertebereich prüfen
	if ((i<min) || (i>max)) {
		printf(">>> Fehlermeldung: Bitte Wertebereich [%d,%d] beachten.<<<\n", min, max);
		return DAU_Eingabe(prompt, min, max, versuche - 1);
	}
	return i;
}
int Menu(){
	system("cls");
	char choice;
	printf("\t\t\t##########_SuDoKu_##########\n\n\n");
	int i = DAU_Eingabe("\tMENU\n1 - Spielstand Laden\n2 - Zufallsspiel\n3 - Infos\n4 - Beenden\n>>>", 1, 4, 3);
	switch(i){
		case 1:{
			int c,i,j;
			system("cls");
			printf("\t\t\t##########_SuDoKu_##########\n\n\n");
			printf("Schwierigkeitsgrad:\n1 - Easy\n2 - Medium\n3 - Hard");
			printf("\n---------\n\tSaveGames\n---------\n4 - SAVE-Easy\n5 - SAVE-Medium\n6 - SAVE-Hard\n\n7 - BACK\n>>>");
			int s = DAU_Eingabe("",1,7,3);
			dateiSudoku(s);
			Ausgabe();
			Cursor(s);
			break;}
		case 2:printf("\n\nZufall\n"); break;
		case 3:{
			system("cls");
			printf("Sudoku-Game created by Thomas-David Griedel\nfor the HTW-Dresden.\n\nType \"back\" to return or \"exit\" to Exit.\n>>>");
			INFO:scanf("%s",&choice);
			if (strcmp(&choice,"back")==0){
				system("cls");
				Menu();
			}else if (strcmp(&choice,"exit")==0){
				exit(1);
			}
			else {printf("BACK or EXIT?\n>>>"); goto INFO;}
			break;
		}
		case 4:exit(1); break;
	}
}
int Color(){
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 112);
    return 0;
}
void gotoXY(int x, int y) {
   HANDLE  hConsoleOutput; COORD koords;
   koords.X=x; koords.Y=y;
   hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleCursorPosition(hConsoleOutput,koords);
}
int Cursor(int s){
	char c;
	int n;
	gotoXY(20, 3); printf("S - Save");
	gotoXY(20, 4); printf("B - Back");
	gotoXY(20, 5); printf("U - Undo");
	int x=1, y=1,k=1;gotoXY(y, x);
   while (k) {
		 while (!kbhit());
	   switch (c = getch()) {
			case 75: {//left
			   if (y >= 2)
				   y -= 2; gotoXY(y, x);
			   break; }
			case 72: {//up
			   if (x >= 2) {
				   x--; gotoXY(y, x);
			   }
			   if (x == 4 || x == 8) {
				   x--; gotoXY(y, x);
			   }
			   break; }
			case 77: {//right
			   if (y <= 16)
				   y += 2; gotoXY(y, x);
			   break; }
			case 80: {//down
					if (x <= 10)
						x++; gotoXY(y, x);
					if ((x == 4) || (x == 8))
						x++; gotoXY(y, x);
					break; }
		    }
		if ((c <= 57)&&(c >= 48)){
					n = atoi(&c);
					 printf("%d",n);
					 Edit(x,y,n);
					 system("cls");
					 Ausgabe();
					 gotoXY(20, 3); printf("S - Save");
					 gotoXY(20, 4); printf("B - Back");
					 gotoXY(20, 5); printf("U - Undo");
					 gotoXY(y,x);

		}else if (c == 115 ){
					speichern(s);

		}else if ( c == 98 ){
					Menu();
		}else if ( c == 117 ){
					Undo_Load();
					gotoXY(x, y);
		}
	 }
}
int dateiSudoku(int s) {
	FILE *fp;
	char fname1[] = "Easy.txt";
	char fname2[] = "Medium.txt";
	char fname3[] = "Hard.txt";
	char fname4[] = "SAVE_E.txt";
	char fname5[] = "SAVE_M.txt";
	char fname6[] = "SAVE_H.txt";
	switch (s) {
	case 1: {//Easy
		if ((fp = fopen(fname1, "rt")) == 0) {
			printf("Datei nicht vorhanden!\n");
			fclose(fp);
			return 0;
		}break; }
	case 2: {//Medium
		if ((fp = fopen(fname2, "rt")) == 0) {
			printf("Datei nicht vorhanden!\n");
			fclose(fp);
			return 0;
		}break; }
	case 3: {//Hard
		if ((fp = fopen(fname3, "rt")) == 0) {
			printf("Datei nicht vorhanden!\n");
			fclose(fp);
			return 0;
		} break; }
	case 4: {//SAVEE
		if ((fp = fopen(fname4, "rt")) == 0) {
			printf("Datei nicht vorhanden!\n");
			fclose(fp);
			return 0;
		}break; }
	case 5: {//SAVEM
		if ((fp = fopen(fname5, "rt")) == 0) {
			printf("Datei nicht vorhanden!\n");
			fclose(fp);
			return 0;
		}break; }
	case 6: {//SAVEH
		if ((fp = fopen(fname6, "rt")) == 0) {
			printf("Datei nicht vorhanden!\n");
			fclose(fp);
			return 0;
		}break; }
		case 7: Menu();
	}
	system("cls");
	char puffer[20];
	int y = 0, x = 0;
	char delimiter[] = " \n";
	char *ptr;
	//Files in Array
	while (fgets(puffer, 20, fp)) {
		ptr = strtok(puffer, delimiter);
		while (ptr != NULL) {
			feld[y][x] = atoi(ptr);
			ptr = strtok(NULL, delimiter);
			x++;
		}
		x = 0;
		y += 1;
	}
	if ( s >= 4 ){
		switch ((s - 3)) {
		case 1: {//Easy
			if ((fp = fopen(fname1, "rt")) == 0) {
				printf("Datei nicht vorhanden!\n");
				fclose(fp);
				return 0;
			}break; }
		case 2: {//Medium
			if ((fp = fopen(fname2, "rt")) == 0) {
				printf("Datei nicht vorhanden!\n");
				fclose(fp);
				return 0;
			}break; }
		case 3: {//Hard
			if ((fp = fopen(fname3, "rt")) == 0) {
				printf("Datei nicht vorhanden!\n");
				fclose(fp);
				return 0;
			} break; }
		}
		y = 0, x = 0;
		while (fgets(puffer, 20, fp)) {
			ptr = strtok(puffer, delimiter);
			while (ptr != NULL) {
				control[y][x] = atoi(ptr);
				ptr = strtok(NULL, delimiter);
				x++;
			}
			x = 0;
			y += 1;
		}
	}else{
	memcpy(control, feld, sizeof(feld));
	}
	return s;
}
int Ausgabe() {
	Rahmen();
	int y, x;
	for (y = 0; y < 9; y++) {
		for (x = 0; x < 9; x++) {
			gotoXY(2 * x + 1,y+1+y/3);
			printf("%d", feld[y][x]);
		}
		printf("\n");
	}
}
int Rahmen(){
	int i,j,n;
	for (i=0;i<12;i+=4){
		printf("+- - -+- - -+- - -+\n");
		for(n=0;n<3;n++){
			for(j=0;j<19;j+=6){
				printf("|     ");}
			printf("\n");}
	}
	printf("+- - -+- - -+- - -+\n");
}
int speichern(int s) {
	int i, j;
	FILE *fp;
	char fname1[] = "SAVE_E.txt";
	char fname2[] = "SAVE_M.txt";
	char fname3[] = "SAVE_H.txt";
	if (s <= 4){
		(s = (s - 3));
	}
	switch (s) {
		case 1: {
			if ((fp = fopen(fname1, "w+t")) == 0) {
			printf("Datei nicht vorhanden!\n");
			fclose(fp);
			return 0;
		}break; }
		case 2: {
		if ((fp = fopen(fname2, "w+t")) == 0) {
			printf("Datei nicht vorhanden!\n");
			fclose(fp);
			return 0;
		}break; }
		case 3: {
		if ((fp = fopen(fname3, "w+t")) == 0) {
			printf("Datei nicht vorhanden!\n");
			fclose(fp);
			return 0;
		} break; }}
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			fprintf(fp, "%d ", feld[i][j]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	gotoXY(2,15); printf("Speichern erfolgreich!!");
	return 1;
	}
int Edit(int x, int y, int n) {
//Umrechnen Ausgabe zu Array[Feld]
	y = (y / 2);
	if ( x < 4 ) {
		x = x - 1;
	}else if (( x < 8 ) && ( x > 4 )) {
		x = x - 2;
	}else if ( x > 8 ) {
		x = x - 3;
	}
	Undo_Save(x,y);
	if ((control[x][y])==0){
		feld[x][y] = n;
	}else return 0;
}
int Undo_Save(int x,int y){

	//i -> Step
	// koordinaten
	ux[i] = x;
	uy[i] = y;
	//Ausgangsnummer
	un[i] = feld[x][y];
	i++;

}
int Undo_Load(){
	int x, y;
	if (i > 0) {
		i--;
		x = ux[i];
		y = uy[i];
		feld[x][y] = un[i];
		un[i] = 0;
		system("cls");
		Ausgabe();
		gotoXY(20, 3); printf("S - Save");
		gotoXY(20, 4); printf("B - Back");
		gotoXY(20, 5); printf("U - Undo");
	}
	else return 0;
}
int main() {
	Color();
	Menu();
}
