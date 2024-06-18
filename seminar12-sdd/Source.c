//practic e seminarul 13 
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

//grafuri
typedef struct Autobuz Autobuz;
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

struct Autobuz {
	int linie;
	char* capatLinie;
};


struct NodPrincipal {
	Autobuz info;
	NodPrincipal* next;
	NodSecundar* vecini;
};


struct NodSecundar {
	NodPrincipal* nod;
	NodSecundar* next;
};

//functie de inserare la sfarsit in lista principala
//functie de cautare dupa linie (linia e unica)
void inserarePrincipala(NodPrincipal** graf, Autobuz a)
{
	//declaram, alocam spatiu si intializam nodul pe care il vom insera
	NodPrincipal* nod = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nod->info = a;
	nod->next = NULL;
	nod->vecini = NULL;

	if ((*graf) != NULL)
	{
		NodPrincipal* temp = (*graf);//facem o copie la graf ptc e transmis prin refrinta si nu vrem sa l modificam
		while (temp->next) {
			temp = temp->next;//parcurgem graful existent ca sa ajungem la sfarsit
		}
		//cand am ajuns la final legam nodul initializat mai sus
		temp->next = nod;
	}
	else {
		//
		(*graf) = nod;
	}

}

NodPrincipal* cautaLinie(NodPrincipal* graf, int linie) {
	while (graf && graf->info.linie != linie) {
		graf = graf->next;
	}
	return graf; //daca nu il gaseste o sa returneze null
}


//functie de inserare in lista secundara
//functie de inserare muchie
NodSecundar* inserareSecundara(NodSecundar* cap, NodPrincipal* info) {
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->next = NULL;
	nou->nod = info;
	if (cap) {
		NodSecundar* p = cap;
		while (p->next) {
			p->next;
		}
		p->next = nou;
		return cap;
	}
	else
	{
		return nou;
	}
}

void inserareMuchie(NodSecundar* graf, int linieStart, int linieStop) //linie start si linie stop adica de unde pana unde e muchia
{
	//cautam cele 2 noduri
	NodPrincipal* nodStart = cautaLinie(graf, linieStart);
	NodPrincipal* nodStop = cautaLinie(graf, linieStop);

	nodStart->vecini = inserareSecundara(nodStart->vecini, nodStop); // in vecinii lui start il adauga pe stop
	nodStop->vecini = inserareSecundara(nodStop->vecini, nodStart); // trebuie adaugat si in vecinii lui stop pe start
}

Autobuz initializareAutobuz(int linie, const char* capat) {
	Autobuz a;
	a.linie = linie;
	a.capatLinie = (char*)malloc(sizeof(char) * strlen(capat) + 1);
	strcpy(a.capatLinie, capat);
	return  a;
}
int main() {
	NodPrincipal* graf = NULL;

	inserarePrincipala(&graf, initializareAutobuz(0, "Romana"));
	inserarePrincipala(&graf, initializareAutobuz(1, "Victoriei"));
	inserarePrincipala(&graf, initializareAutobuz(2, "Militari"));
	inserarePrincipala(&graf, initializareAutobuz(3, "Voluntari"));
	inserarePrincipala(&graf, initializareAutobuz(4, "Pipera"));


	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 0, 4);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 2, 4);
	inserareMuchie(graf, 3, 4);


}