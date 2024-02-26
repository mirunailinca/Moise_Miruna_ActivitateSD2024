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

struct Masina* creareVector(struct Masina* vm, int marime) { //vector cu masini mai noi de 2018
	struct Masina* vectorNou;
	int nr = 0, cont = 0;
	for (int i = 0; i < marime; i++)
		if (vm[i].anFabricatie >= 2018)
			nr++;
	vectorNou = (struct Masina*)malloc(sizeof(struct Masina) * nr);
	for (int i = 0; i < nr; i++)
	{
		if (vm[i].anFabricatie >= 2018)
		{
			vectorNou[cont].nume = (char*)malloc(sizeof(vm[i].nume));
			strcpy(vectorNou[cont].nume, vm[i].nume);
			vectorNou[cont].km = vm[i].km;
			vectorNou[cont].anFabricatie = vm[i].anFabricatie;
			cont++;
		}
	}

	return vectorNou;
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

	//struct Masina m5;
	//m5 = citireMasinaTastatura();
	//afiseazaMasina(m5);

	//afiseazaMasina(comparatieAn(m1, m2));

	struct Masina m4, m3;
	m4.nume = (char*)malloc(strlen("Papuc") + 1);
	strcpy(m4.nume, "Papuc");
	m4.km = 230000;
	m4.anFabricatie = 1990;

	m3.nume = (char*)malloc(strlen("Cielo") + 1);
	strcpy(m3.nume, "Cielo");
	m3.km = 23000;
	m3.anFabricatie = 2018;



	/*struct Masina vmasini[4] ;
	vmasini[0] = m1;
	vmasini[1] = m2;
	vmasini[2] = m3;
	vmasini[3] = m4;

	creareVector(vmasini, 4);*/

	int nr;
	printf("Introduceti numarul de masini: ");
	scanf("%d", &nr);

	struct Masina* vectorMasini;
	vectorMasini = (struct Masina*)malloc(nr * sizeof(struct Masina));

	vectorMasini[0] = m1;
	vectorMasini[1] = m2;
	vectorMasini[2] = m3;
	vectorMasini[3] = m4;

	creareVector(vectorMasini, 4);

	free(m1.nume);
	free(m2.nume);
	free(m3.nume);
	free(m4.nume);
	//free(m5.nume);
	return 0;
}