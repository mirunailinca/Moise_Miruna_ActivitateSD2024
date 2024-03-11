#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>


struct Masina {
	char* nume;
	int km;
	int anFabricatie;
};

void afiseazaMasina(struct Masina m) {
	if (m.nume != NULL)
		printf("\nNume: %s", m.nume);
	printf("\nKm: %i", m.km);
	printf("\nAn fabricatie: %i", m.anFabricatie);
	printf("\n");
}

struct Masina citireMasina(const char* nume, int km, int anFabricatie) {
	struct Masina m;
	m.nume = malloc(strlen(nume) + 1);
	strcpy(m.nume, nume);
	m.km = km;
	m.anFabricatie = anFabricatie;
	return m;
}

struct Masina citireMasinaTastatura() {
	struct Masina m;

	m.nume = (char*)malloc(100 * sizeof(char));
	printf("\nIntroducti numele: ");
	scanf("%s", m.nume);
	printf("\nIntroduceti numarul de km: ");
	scanf("%d", &m.km);
	printf("\nIntroduceti anul fabricatiei: ");
	scanf("%d", &m.anFabricatie);

	return m;
}

void modificareKm(struct Masina* m, int km) {
	m->km = km;
}

struct Masina comparatieAn(struct Masina m1, struct Masina m2) {
	if (m1.anFabricatie > m2.anFabricatie)
		return m1;
	else
		return m2;
}

void stergeMasina(struct Masina* m) {
	if (m->nume != NULL)
		free(m->nume);
}

void afisareVector(struct Masina* v, int nrMasini) {
	for (int i = 0; i < nrMasini; i++)
		afiseazaMasina(v[i]);
}

struct Masina* conditieAn(struct Masina* v, int nrMasini, int an, int* nrMasiniConditie) {
	*nrMasiniConditie = 0;
	int cnt = 0;
	struct Masina* vectorNou;

	for (int i = 0; i < nrMasini; i++)
		if (v[i].anFabricatie > an) (*nrMasiniConditie)++;

	vectorNou = (struct Masina*)malloc(sizeof(struct Masina) * (*nrMasiniConditie));

	for (int i = 0; i < nrMasini; i++)
		if (v[i].anFabricatie > an)
			vectorNou[cnt++] = citireMasina(v[i].nume, v[i].km, v[i].anFabricatie);

	return vectorNou;
}

struct Masina* concatenareVectori(struct Masina* v1, struct Masina* v2, int nrMasini1, int nrMasini2) {
	int cnt = 0;
	struct Masina* vectorNou = (struct Masina*)malloc(sizeof(struct Masina) * (nrMasini1 + nrMasini2));

	for (int i = 0; i < nrMasini1; i++)
		vectorNou[cnt++] = citireMasina(v1[i].nume, v1[i].km, v1[i].anFabricatie);

	for (int i = 0; i < nrMasini2; i++)
		vectorNou[cnt++] = citireMasina(v2[i].nume, v2[i].km, v2[i].anFabricatie);

	return vectorNou;
}

void dezalocareVectorMasini(struct Masina** v, int* nrMasini) {
	for (int i = 0;i < *nrMasini;i++)
		free((*v)[i].nume);

	free(*v);
	*nrMasini = 0;
	*v = NULL;
}

struct Masina* adaugareInVector(struct Masina* masini, struct Masina m, int* nrMasini) {
	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1));

	for (int i = 0;i < (*nrMasini);i++)
		aux[i] = masini[i];
	aux[(*nrMasini)] = m;

	if (masini != NULL) free(masini);
	return aux;
}

struct Masina* citireFisier(const char* numeFisier, int* nrMasini) {
	FILE* f = fopen(numeFisier, "r");
	const char delimitare[] = ",\n";
	char buffer[100];
	struct Masina* masini = NULL;
	(*nrMasini) = 0;

	while (fgets(buffer, 100, f) != NULL) {
		char* element = strtok(buffer, delimitare);

		struct Masina m;

		m.nume = malloc(strlen(element) + 1);
		strcpy(m.nume, element);
		element = strtok(NULL, delimitare);
		m.km = atoi(element);
		element = strtok(NULL, delimitare);
		m.anFabricatie = atoi(element);

		masini = adaugareInVector(masini, m, nrMasini);
	}
	fclose(f);
	return masini;
}

int main() 
{
	int nrMasini = 0;
	struct Masina* masini = citireFisier("masinibune.txt", &nrMasini);

	afisareVector(masini, nrMasini);

	return 0;
}