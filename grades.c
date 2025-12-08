#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>

#define BSIZE 36
#define CSIZE 21
#define NHW 9
#define NLAB 10
#define NPRJ 4
#define NTST 2
#define NUMGRADES NHW+NLAB+NPRJ+NTST+1
#define NUM10GRADES NHW+NLAB
#define MAXSECT 100

char * gets(char *str); // To avoid C library problems
void getGrades(int grds[NUMGRADES][MAXSECT],int n);
void getAvgs(int grds[NUMGRADES][MAXSECT],int n);
void getAvg(int grds[NUMGRADES][MAXSECT],int student);
char * getUserLine();
void printGrades(int grds[NUMGRADES][MAXSECT],int n,char *names[]);

int bGrades[NUMGRADES][MAXSECT];
int cGrades[NUMGRADES][MAXSECT];
char retBufferArea[1024+4096];
char *retBuffer;

char *colNames[NUMGRADES] = {
	"HW01","HW02","HW03","HW04","HW05","HW06","HW07","HW08","HW09",
	"Lab01","Lab02","Lab03","Lab04","Lab05","Lab06","Lab07","Lab08","Lab09","Lab10",
	"Prj01","Prj02","Prj03","Prj04",
	"Tst01","Tst02",
	"AVG" };
char *bNames[BSIZE] = {
	"Arciolla_Antony",
	"Baldwin_Samantha",
	"Boaz_Donovan",
	"Brauning_Nathan",
	"Calin_Stephania",
	"Frechter_Eviatar",
	"Gnajewski_Monica",
	"Gutierrez_Maria",
	"Heatley_Griffin",
	"Jiang_Jacky",
	"Kim_Eric",
	"Kim_Isaac",
	"Kivel_Noah",
	"Lazore_Adam",
	"Lee_Kristen",
	"Liang_Haolin",
	"Lin_Brian",
	"Luo_Tyler",
	"Ly_Hanssen",
	"Maldonado_Noel",
	"Melchior_Liam",
	"Moy_Donnie",
	"Ogwulumba_Chuma",
	"Olsen_Thomas",
	"Patel_Kris",
	"Pernia_Matthew",
	"Pufahl_James",
	"Rahmani_Meena",
	"Rijal_Salaj",
	"Robinson_Timothy",
	"Shiyam_Damian",
	"Singh_Kushagra",
	"Smith_Riley",
	"Vega_Dominic",
	"Wu_Chloe",
	"Zaccarelli_Gianni"
};
char *cNames[CSIZE] = {
	"Akarca_Tolga",
	"Ben_Henry",
	"Benjelloun_Ryan",
	"D'Onofrio_Chris",
	"Godzki_Kyle",
	"Kazalas_Demetrios",
	"Lau_Jordan",
	"Levisman_Itai",
	"Li_Yuyang",
	"Lin_Zihan",
	"McAleer_James",
	"McDonald_Nicky",
	"Padshala_Kushal",
	"Rahman_Tawhidur",
	"Steck_Jake",
	"Sulicz_Miron",
	"Tsui_Ryan",
	"Visciano_Anthony",
	"White_Carter",
	"Zheng_Jalen",
	"Zheng Yu_Lumin"
};

FILE *txtFile;

int main(int argc, char ** argv) {
	char * secID;
	time_t t;

	long pagesize = sysconf(_SC_PAGESIZE);;
	setbuf(stdout,0);
	retBuffer=(char *)(((long)retBufferArea + pagesize-1) & ~(pagesize-1));
	if(mprotect(retBuffer, 1024, PROT_READ|PROT_EXEC|PROT_WRITE)) {
      printf("mprotect failed\n");
      return(1);
   }
   if (argc==1) srand((unsigned) time(&t));
   else {
   	unsigned int seed=atoi(argv[1]);
   	srand(seed);
	}
	getGrades(bGrades,BSIZE);
	getGrades(cGrades,CSIZE);
	getAvgs(bGrades,BSIZE);
	getAvgs(cGrades,CSIZE);

	printf("Choose section B or C: ");
	secID=getUserLine();
	printf("\n");

	if (secID[0]=='B') {
		printGrades(bGrades,BSIZE,bNames);
	} else if (secID[0]=='C') {
		printGrades(cGrades,CSIZE,cNames);
	} else {
		printf("Unable to determine which section you wanted.\n");
	}
	exit(0);
}

void getGrades(int grds[NUMGRADES][MAXSECT],int n) {
	int s,c;
	for(s=0; s<n; s++) {
		for(c=0;c<NHW;c++) 	grds[c][s] = 5+rand()%2;
		for(c=NHW; c<(NHW+NLAB); c++) grds[c][s] = 5+rand()%3;
		for(c=NHW+NLAB; c<(NHW+NLAB+NPRJ); c++) grds[c][s] = 53+rand()%7;
		for(c=(NHW+NLAB+NPRJ);c<(NHW+NLAB+NPRJ+NTST);c++) grds[c][s] = 54+rand()%8;
	}
}

void getAvgs(int grds[NUMGRADES][MAXSECT],int n) {
	for(int s=0; s<n; s++) {
		getAvg(grds,s);
	}
}

void getAvg(int grds[NUMGRADES][MAXSECT],int student) {
	int c;
	int sumHW,sumLab,sumProj,sumTest;
	int minProj;

	sumHW=sumLab=sumProj=sumTest=0;
	minProj=101;
	for(c=0;c<NHW;c++) 	sumHW+=grds[c][student];
	for(c=NHW; c<(NHW+NLAB); c++) sumLab+=grds[c][student];
	for(c=NHW+NLAB; c<(NHW+NLAB+NPRJ); c++) {
		sumProj+=grds[c][student];
		if (grds[c][student]<minProj) minProj=grds[c][student];
	}
	sumProj-=minProj; // Remove the lowest project grade
	for(c=(NHW+NLAB+NPRJ);c<(NHW+NLAB+NPRJ+NTST);c++) sumTest+=grds[c][student];
	float avg = 0.15 * (10.0 * (float)sumHW/NHW) +
				0.15 * (10.0 * (float)sumLab/NLAB) +
				0.20 * ((float)sumProj/(NPRJ-1)) +
				0.20 * ((float)sumTest/NTST);
	// So far, this is the average without participation and final exam
	avg=(100.0/70.0)*avg; // What is the average without participation and final
	grds[NUMGRADES-1][student] = avg; // Truncate the decimal
}


char * getUserLine() {
	char buffer[256];

	if (gets(buffer)) {
		memcpy(retBuffer,buffer,sizeof(buffer));
		return retBuffer;
	}
	return NULL;
}

void printGrades(int grds[NUMGRADES][MAXSECT],int n,char * names[]) {
	int s;
	printf(" %20s |","Student");
	for(int i=0;i<NUMGRADES-1;i++) printf("%5s|",colNames[i]);
	printf("| %3s |\n","AVG");
	printf("----------------------|");
	for(int i=0;i<NUMGRADES-1;i++) printf("-----|");
	printf("|-----|\n");
	for(s=0; s<n; s++) {
		printf(" %20s |",names[s]);
		for(int i=0;i<NUMGRADES-1;i++) printf(" %3d |",grds[i][s]);
		printf("| %3d |\n",grds[NUMGRADES-1][s]);
	}
	printf("----------------------|");
	for(int i=0;i<NUMGRADES-1;i++) printf("-----|");
	printf("|-----|\n");
}
