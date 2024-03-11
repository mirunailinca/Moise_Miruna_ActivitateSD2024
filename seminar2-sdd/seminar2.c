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

	for(int i = 0; i < nrMasini1; i++)
		vectorNou[cnt++]=citireMasina(v1[i].nume, v1[i].km, v1[i].anFabricatie);

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

int main() {
	struct Masina m1;
	m1.nume = (char*)malloc(strlen("Mazda") + 1);
	strcpy(m1.nume, "Mazda");
	m1.km = 23000;
	m1.anFabricatie = 2018;
	afiseazaMasina(m1);

	struct Masina m2;
	m2 = citireMasina("Sandero", 10000, 2022);
	//afiseazaMasina(m2);

	modificareKm(&m2, 13013);
	afiseazaMasina(m2);

	//struct Masina m5;
	//m5 = citireMasinaTastatura();
	//afiseazaMasina(m5);

	//afiseazaMasina(comparatieAn(m1, m2));

	struct Masina m4, m3;

	m3.nume = (char*)malloc(strlen("Cielo") + 1);
	strcpy(m3.nume, "Cielo");
	m3.km = 53400;
	m3.anFabricatie = 2003;
	afiseazaMasina(m3);

	m4.nume = (char*)malloc(strlen("Papuc") + 1);
	strcpy(m4.nume, "Papuc");
	m4.km = 230000;
	m4.anFabricatie = 1990;
	afiseazaMasina(m4);


	int nrMasini = 4;
	struct Masina* vectorMasini = (struct Masina*)malloc(sizeof(struct Masina) * nrMasini);

	vectorMasini[0] = m1;
	vectorMasini[1] = m2;
	vectorMasini[2] = m3;
	vectorMasini[3] = m4;

	printf("----------------1-");

	afisareVector(vectorMasini, nrMasini);


	int nrMasiniConditie = 0;
	struct Masina* vectorMasiniConditie = conditieAn(vectorMasini, nrMasini, 2010, &nrMasiniConditie);

	printf("----------------2-");
	afisareVector(vectorMasiniConditie, nrMasiniConditie);


	struct Masini* vectorConcatenat = concatenareVectori(vectorMasini, vectorMasiniConditie, nrMasini, nrMasiniConditie);
	printf("----------------3-");
	afisareVector(vectorConcatenat, nrMasini+nrMasiniConditie);

	free(m1.nume);
	free(m2.nume);
	free(m3.nume);
	free(m4.nume);
	//free(m5.nume);
	int z = nrMasini + nrMasiniConditie;
	dezalocareVectorMasini(&vectorConcatenat, &z);
	dezalocareVectorMasini(&vectorMasini, &nrMasini);
	dezalocareVectorMasini(&vectorMasiniConditie, &nrMasiniConditie);
	return 0;
}
