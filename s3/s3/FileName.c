#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

struct Masina {
	int id;
	char* producator;
	int nrUsi;
	float pret;
};

struct Masina* adaugareInVector(struct Masina* masini, struct Masina m, int* nrMasini) {
	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1));

	for (int i = 0; i < (*nrMasini); i++) {
		aux[i] = masini[i];
	}
	aux[(*nrMasini)] = m;
	(*nrMasini)++; //am adaugat o masina deci creste numarul 

	if (masini != NULL) free(masini);
	return aux;
}

struct Masina* citireFisier(const char* numeFisier, int* nrMasini) {
	FILE* f = fopen(numeFisier, "r"); //fopen returneaza un FILE*
	//fscanf citeste pana la spatiu => citesc intreaga linie si dupa o sparg la fiecare linie
	char buffer[100];
	const char delimitare[] = ",\n";
	struct Masina* masini = NULL;
	(*nrMasini) = 0;

	while (fgets(buffer, 100, f) != NULL) //fgets citeste o linie intreaga
	{
		char* element = strtok(buffer, delimitare);

		struct Masina m;

		m.id = atoi(element); //atoi=ascii to int (un fel de cast la int); strtoi=string to int
		element = strtok(NULL, delimitare);
		m.producator = malloc(strlen(element) + 1);
		strcpy(m.producator, element);
		element = strtok(NULL, delimitare);
		m.nrUsi = atoi(element);
		element = strtok(NULL, delimitare);
		m.pret = atof(element);

		masini = adaugareInVector(masini, m, nrMasini);
	}
	fclose(f);
	return masini;
}

void afiseazaMasina(struct Masina m) {
	printf("\nId: %i", m.id);
	if (m.producator != NULL)
		printf("\nProducator: %s", m.producator);
	
	printf("\nNr usi: %i", m.nrUsi);
	printf("\nPret: %f", m.pret);
	printf("\n");
}

void afisareMatrice(struct Masina** matrice, int nrLinii, int* nrCol) {
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < nrCol[i]; j++)
			afiseazaMasina(matrice[i][j]);
		printf("\n");
	}
}


void citireMatrice(const char* numeFisier, struct Masina** matrice ,int nrLinii, int* nrColoane) {
	FILE* f = fopen(numeFisier, "r"); //fopen returneaza un FILE*
	//fscanf citeste pana la spatiu => citesc intreaga linie si dupa o sparg la fiecare linie
	char buffer[100];
	const char delimitare[] = ",\n";

	while (fgets(buffer, 100, f) != NULL) //fgets citeste o linie intreaga
	{
		char* element = strtok(buffer, delimitare);

		struct Masina m;

		m.id = atoi(element); //atoi=ascii to int (un fel de cast la int); strtoi=string to int
		element = strtok(NULL, delimitare);
		m.producator = malloc(strlen(element) + 1);
		strcpy(m.producator, element);
		element = strtok(NULL, delimitare);
		m.nrUsi = atoi(element);
		element = strtok(NULL, delimitare);
		m.pret = atof(element);

		matrice[m.nrUsi-2] = adaugareInVector(matrice[m.nrUsi-2], m, & (nrColoane[m.nrUsi-2]));
	}
	fclose(f);
	
}

//pretul mediu al masinilor cu nr de usi dat ca parametru
float pretMediu(struct Masina** matrice, int nrLinii, int* nrColoane,int nrUsi) {
	if (nrUsi < 2 || nrUsi > 4) 
		return 0;
	float pret = 0;
	if (nrColoane[nrUsi - 2] != 0)
	for (int i = 0; i < nrColoane[nrUsi - 2]; i++) { //sau declaram un index=nrUsi-2;
		pret += matrice[nrUsi - 2][i].pret;
	}

	return pret / nrColoane[nrUsi-2];
}

//functie care sa returneze masina cu un id primit
struct Masina cautareMasinaID(struct Masina** matrice, int nrLinii, int* nrColoane, int id) {
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < nrColoane[i]; j++)
			if (matrice[i][j].id == id)
				return matrice[i][j];
	}

	struct Masina masina;
	masina.id = -1;
	masina.producator = NULL;
	masina.pret = -1;
	masina.nrUsi = -1;
	return masina;
}

void dezalocareMatrice(struct Masina*** matrice, int nrLinii, int** nrColoane) {
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < (*nrColoane[i]); j++)
			free ((*matrice)[i][j].producator);
		free((*matrice)[i]);
	}
	free((*nrColoane));
	(*nrColoane) = NULL;
	free((*matrice));
	(*matrice) = NULL;

}

int main() {
	//s4 MATRICEA ESTE UN VECTOR DE VECTORI
	struct Masina** matrice;
	int nrLinii = 3;
	int* nrCol;
	matrice = (struct Masina**)malloc(sizeof(struct Masina*)*nrLinii);
	nrCol = (int*)malloc(sizeof(int) * nrLinii); //vectorul de lungimi

	for (int i = 0; i < nrLinii; i++)
	{
		nrCol[i] = 0;
		matrice[i] = NULL;
	}

	afisareMatrice(matrice, nrLinii, nrCol);

	citireMatrice("masinibune.txt", matrice, nrLinii, nrCol);

	afisareMatrice(matrice, nrLinii, nrCol);

	printf("Pretul mediu este: %5.2f",pretMediu(matrice, nrLinii, nrCol, 2));

	printf("\n---------\n");
	struct Masina m;
	m=cautareMasinaID(matrice, nrLinii, nrCol, 2);
	printf(" %i %s %i %.2f", m.id, m.producator,m.nrUsi, m.pret);


	dezalocareMatrice(&matrice, nrLinii, &nrCol);
}