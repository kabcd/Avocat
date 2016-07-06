#include <iostream>
using namespace std;
class Document{
private:
	char* nume_document;
	float dimensiune;
	int nr_pagini;
	int *cuvinte_pe_pagina;
	static int nr_documente;
public:
	//constructor fara parametri
	Document()
	{
		this->nume_document=new char[strlen("Anonim")+1];
		strcpy(this->nume_document,"Anonim");
		this->dimensiune=0;
		this->nr_pagini=0;
		this->cuvinte_pe_pagina=NULL;
		nr_documente++;
	}
	//constructor cu parametri
	Document(char* nume_document,float dimensiune,int nr_pagini,int *cuvinte_pe_pagina)
	{
		this->nume_document=new char[strlen(nume_document)+1];
		strcpy(this->nume_document,nume_document);
		this->dimensiune=dimensiune;
		this->nr_pagini=nr_pagini;
		this->cuvinte_pe_pagina=new int[nr_pagini];
		for(int i=0;i<nr_pagini;i++)
			this->cuvinte_pe_pagina[i]=cuvinte_pe_pagina[i];
		Document::nr_documente++;
	}
	//constructor de copiere
	Document(Document &d)
	{
		this->nume_document=new char[strlen(d.nume_document)+1];
		strcpy(this->nume_document,d.nume_document);
		this->dimensiune=d.dimensiune;
		this->nr_pagini=d.nr_pagini;
		this->cuvinte_pe_pagina=new int[d.nr_pagini];
		for(int i=0;i<d.nr_pagini;i++)
			this->cuvinte_pe_pagina[i]=d.cuvinte_pe_pagina[i];
		Document::nr_documente++;
	}
	//supraincarcare =
	Document operator=(Document d)
	{
        if(this->nume_document != NULL)
			delete[] nume_document;
		if(this->cuvinte_pe_pagina != NULL)
			delete[] cuvinte_pe_pagina;
		this->nume_document=new char[strlen(d.nume_document)+1];
		strcpy(this->nume_document,d.nume_document);
		this->dimensiune=d.dimensiune;
		this->nr_pagini=d.nr_pagini;
		this->cuvinte_pe_pagina=new int[d.nr_pagini];
		for(int i=0;i<d.nr_pagini;i++)
			this->cuvinte_pe_pagina[i]=d.cuvinte_pe_pagina[i];
		return *this;
	}
	//destructor
	~Document()
	{
		if(this->nume_document!=NULL)
			delete [] this->nume_document;
		if(this->cuvinte_pe_pagina!=NULL)
			delete [] this->cuvinte_pe_pagina;
		Document::nr_documente--;
	}
	//getterii si setterii
	char *getNume_document()
	{
		return this->nume_document;
	}
	void setNume_document(char *nume_documentNou)
	{
		if(this->nume_document!=NULL)
		{
			delete [] this->nume_document;
			this->nume_document=new char[strlen(nume_documentNou)+1];
			strcpy(this->nume_document,nume_documentNou);
		}
		else
			throw new exception("Nume document invalid!");
	}
	static int getNr_documente()
	{
		return Document::nr_documente;
	}
	int TotalCuvinte()
	{
		int t=0;
		for(int i=0;i<this->nr_pagini;i++)
			t=t+this->cuvinte_pe_pagina[i];
		return t;
	}
	//supraincarcare <<
	friend ostream &operator<<(ostream &out, Document &d);
	//supraincarcare +=
	Document operator+=(float dim)
	{
		this->dimensiune+=dim;
		return *this;
	}
	//supraincarcare cast
	operator float()
	{
		return this->dimensiune;
	}
	//supraincarcare >>
	friend istream &operator>>(istream &in, Document &d);
	//supraincaracre -= 
	Document operator-=(int x)
	{
		if(this->nr_pagini>=x)
		{
			int *aux = new int[this->nr_pagini];
			for(int i=0;i<=this->nr_pagini;i++)
				aux[i] = this->cuvinte_pe_pagina[i];

			for(int i=x-1;i<nr_pagini-1;i++)
				aux[i]=aux[i+1];
			
			this->nr_pagini --;
			delete[] this->cuvinte_pe_pagina;
			this->cuvinte_pe_pagina = new int[this->nr_pagini];
			for(int i=0;i<this->nr_pagini;i++)
				cuvinte_pe_pagina[i] = aux[i];
		}
		return *this;
	}
};
int Document::nr_documente=0;
ostream &operator<<(ostream &out, Document &d)
	{
		cout<<"Nume document: "<<d.nume_document<<endl;
		cout<<"Dimensiune document: "<<d.dimensiune<<endl;
		cout<<"Nr pagini: "<<d.nr_pagini<<endl;
		cout<<"Cuvinte pe pagina: ";
		for(int i=0;i<d.nr_pagini;i++)
			out<<d.cuvinte_pe_pagina[i]<<" ";
		out<<endl;
		return out;
	}
istream &operator>>(istream &in, Document &d);
{
	char aux[20];
	cout<<endl<<"Dati nume document:";
	in>>aux;
	if(d.nume_document!= NULL)
		delete [] d.nume_document;
	d.nume_document=new char[strlen(aux)+1];
	strcpy(d.nume_document,aux);
	cout<<endl<<"Dati dimensiune document:";
	in>>d.dimensiune;
	cout<<endl<<"Dati nr pagini:";
	in>>d.nr_pagini;
	cout<<endl<<"Dati cuvinte pe pagina:";
	if(d.cuvinte_pe_pagina != NULL)
		delete [] d.cuvinte_pe_pagina;
	d.cuvinte_pe_pagina=new int[d.nr_pagini];
	for(int i=0;i<d.nr_pagini;i++)
		in>>d.cuvinte_pe_pagina[i];
	return in;
}
void main()
{
		Document d1;
		d1.setNume_document("Document01");
		cout<<d1.getNume_document()<<endl;

		int *x=new int[3];
		x[0]=150;
		x[1]=300;
		x[2]=150;
		Document d2("Excel",15,3,x);
		cout<<d2<<endl;

		Document d3=d1;
		cout<<d3<<endl;

		Document d4;
		d4=d1;
		cout<<d4<<endl;

		cout<<d4.TotalCuvinte()<<endl; //se calculeaza numarul total de cuvinte din documentul d4

		Document d5;
		cin>>d5;
		cout<<d5<<endl;

		cout<<"Nr documente: "<<Document::getNr_documente()<<endl;

		d2+=2.3;// se mareste dimensiunea documentului d2 cu 2.3
		cout<<d2<<endl;

		float d=d2;
		cout<<d<<endl;

		int *y=new int[5];
		y[0]=250;
		y[1]=300;
		y[2]=150;
	    y[3]=0;
		y[4]=200;
		Document d8("PowerPoint",15,5,y);;
		d8-=2; // se sterge a doua pagina din documentul d8
		cout<<d8;
	}
