#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//stiva LIFO pe un vector

typedef struct Stiva Stiva;
struct Stiva {
	int vector[100];
	int top; //indicele elementului curetn din varful stivei
};

void initializareStiva(Stiva* stiva) {
	stiva->top = -1; //e goala stiva
}

int esteGoala(Stiva stiva) {
	if (stiva.top == -1)
		return 1;
	else
		return 0;
}

int estePlina(Stiva stiva) {
	if (stiva.top == 99)
		return 1;
	else
		return 0;
}

void adaugaInStiva(Stiva* stiva, int valoare) {
	if (estePlina(*stiva) == 1)
	{
		printf("Stiva este plina\n");
	}
	else
	{
		stiva->vector[++(stiva->top)] = valoare;
	}
}

void eliminaDinStiva(Stiva* stiva) // elimina ultimul elem
{
	if (esteGoala(*stiva) == 1)
	{
		printf("Stiva este goala\n");
	}
	else
	{
		stiva->top--;
		//ar trb sa sterg elem de pe poz top?
	}
}

void afisareStivaLIFO(Stiva stiva) {
	//LIFO -> deci o sa afisez de la final la inceput
	for (int i = stiva.top; i >= 0;i--) {
		printf("%d ",stiva.vector[i]);
	}
	printf("\n");
}


//coada FIFO pe un vector
typedef	struct Coada Coada;
struct Coada {
	int vector[100];
	int primul;
	int ultimul;
};

void initializareCoada(Coada* coada) {
	coada->primul = -1;
	coada->ultimul = -1;
}

int esteGoalaCoada(Coada coada) {
	if (coada.primul == -1 && coada.ultimul == -1)
		return 1;
	else
		return 0;
}

int estePlinaCoada(Coada coada) {
	if (coada.ultimul == 99)
		return 1;
	else
		return 0;
}

void adaugaInCoada(Coada* coada, int valoare) {
	if (estePlinaCoada(*coada))
		printf("Coada este plina\n");
	else
	{
		if (esteGoalaCoada(*coada))
			coada->primul = 0;
		coada->vector[++(coada->ultimul)] = valoare;
	}
}

void stergeDinCoada(Coada* coada) {
	if (esteGoalaCoada(*coada))
		printf("Coada este goala\n");
	else
	{
		if (coada->primul == coada->ultimul == 1) 
		{
			coada->primul = -1;
			coada->ultimul = -1;
			printf("Exista un singur element, acum coada e goala\n");
		}
		else
		{
			coada->primul++;
		}
	}
}

void afisareCoadaFIFO(Coada coada) {
	if (esteGoalaCoada(coada))
		printf("Coada este goala");
	else
	{
		for (int i = coada.primul; i <= coada.ultimul; i++)
			printf("%d ", coada.vector[i]);
	}
	printf("\n");
}


//stiva LIFO simplu inlantuita
typedef struct Pisica Pisica;
struct Pisica {
	char* nume;
	int varsta;
};

typedef struct Nod Nod;
struct Nod {
	Pisica pisica;
	Nod* next; //adresa urm nod
};

typedef struct StivaListaSimpla StivaListaSimpla;
struct StivaListaSimpla {
	Nod* varf;
};

Pisica initializarePisica(char* nume, int varsta) {
	Pisica pisica;
	pisica.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(pisica.nume, nume);
	pisica.varsta = varsta;

	return pisica;
}

void initializareStivaListaSimpla(StivaListaSimpla* stiva) {
	stiva->varf = NULL;
}


int esteGoalaStivaListaSimpla(StivaListaSimpla stiva) {
	if (stiva.varf == NULL)
		return 1;
	else
		return 0;
}

void adaugaInStivaListaSimpla(StivaListaSimpla* stiva, Pisica p) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod)); //fac un nod nou

	nodNou->pisica.nume = (char*)malloc(sizeof(char) * strlen(p.nume) + 1); //ii dau ce valori trb
	strcpy(nodNou->pisica.nume, p.nume);
	nodNou->pisica.varsta = p.varsta;

	nodNou->next = stiva->varf; //nodNod next tine minte ce este inaintea lui (elementul care era ultimul inainte sa adaugam)
	stiva->varf = nodNou; //varful stivei devine ce am adaugat
}

void afisarePisica(Pisica pisica) {
	printf("Pisica %s are %d ani.\n", pisica.nume, pisica.varsta);
}

void afisareStivaListaSimpla(StivaListaSimpla stiva) {
	if (esteGoalaStivaListaSimpla(stiva)) {
		printf("Stiva lista simpla e goala");
	}
	else {
		Nod* nod = stiva.varf;
		while (nod != NULL) {
			afisarePisica(nod->pisica);
			nod = nod->next;
		}
		printf("\n");
	}
}

void stergeNodStivaListaSimpla(StivaListaSimpla* stiva) {
	if (esteGoalaStivaListaSimpla(*stiva)) {
		printf("Stiva lista simpla e goala");
	}
	else {
		Nod* nodSters = stiva->varf;
		stiva->varf = stiva->varf->next;
		free(nodSters);
	}

}
//nu prea merge cu lista simpla lifo
int main() {
	Stiva stiva1;
	initializareStiva(&stiva1);

	adaugaInStiva(&stiva1, 3);
	adaugaInStiva(&stiva1, 77);
	adaugaInStiva(&stiva1, 1);
	adaugaInStiva(&stiva1, 43);
	afisareStivaLIFO(stiva1);

	eliminaDinStiva(&stiva1);
	afisareStivaLIFO(stiva1);

	printf("\n------------------------------\n");

	Coada coada1;
	initializareCoada(&coada1);

	adaugaInCoada(&coada1, 1);
	adaugaInCoada(&coada1, 3);
	adaugaInCoada(&coada1, 5);
	adaugaInCoada(&coada1, 7);
	afisareCoadaFIFO(coada1);

	stergeDinCoada(&coada1);
	afisareCoadaFIFO(coada1);

	printf("\n------------------------------\n");

	StivaListaSimpla stivaListaSimpla;

	Pisica p1= initializarePisica("Ahek", 3);
	Pisica p2 = initializarePisica("Yuki", 2);
	Pisica p3 = initializarePisica("Zoro",4);
	Pisica p4 = initializarePisica("Mitu", 3);

	adaugaInStivaListaSimpla(&stivaListaSimpla, p1);
	adaugaInStivaListaSimpla(&stivaListaSimpla, p2);
	adaugaInStivaListaSimpla(&stivaListaSimpla, p3);
	adaugaInStivaListaSimpla(&stivaListaSimpla, p4);

	afisareStivaListaSimpla(stivaListaSimpla);

	stergeNodStivaListaSimpla(&stivaListaSimpla);

	afisareStivaListaSimpla(stivaListaSimpla);
}