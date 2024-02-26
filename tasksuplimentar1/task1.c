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

int main() {
	struct Masina m1;
	m1.nume = (char*)malloc(strlen("Mazda") + 1);
	strcpy(m1.nume, "Mazda");
	m1.km = 23000;
	m1.anFabricatie = 2018;
	afiseazaMasina(m1);

	struct Masina m2;
	m2 = citireMasina("Sandero", 10000, 2022);
	afiseazaMasina(m2);

	modificareKm(&m2, 13013);
	afiseazaMasina(m2);

	struct Masina m3;
	m3 = citireMasinaTastatura();
	afiseazaMasina(m3);

	afiseazaMasina(comparatieAn(m1, m2));

	free(m1.nume);
	free(m2.nume);
	free(m3.nume);
	return 0;
}