#include<iostream>
using namespace std;
class Bucatar{
private:
	const int cod;
	char* nume;
	int greutate;
	int nr_ore;
	int *prajituri;
	static int nr_restaurante;
public:
	Bucatar():cod(0)
	{
		this->nume=new char[strlen("Anonim")+1];
		strcpy(this->nume, "Anonim");
		this->greutate=0;
		this->nr_ore=0;
		this->prajituri=NULL;
		Bucatar::nr_restaurante++;
	}
	Bucatar(const int c, char* nume, int greutate, int nr_ore, int *prajituri):cod(c)
	{
		this->nume=new char[strlen(nume)+1];
		strcpy(this->nume, nume);
		this->greutate=greutate;
		this->nr_ore=nr_ore;
		this->prajituri=new int[nr_ore];
		for(int i=0;i<nr_ore;i++)
			this->prajituri[i]=prajituri[i];
		Bucatar::nr_restaurante++;
	}
	~Bucatar()
	{
		if(this->nume!=NULL)
			delete [] this->nume;
		if(this->prajituri!=NULL)
			delete [] this->prajituri;
		Bucatar::nr_restaurante--;
	}
	Bucatar(Bucatar &b):cod(b.cod)
	{
		this->nume=new char[strlen(b.nume)+1];
		strcpy(this->nume, b.nume);
		this->greutate=b.greutate;
		this->nr_ore=b.nr_ore;
		this->prajituri=new int[b.nr_ore];
		for(int i=0;i<b.nr_ore;i++)
			this->prajituri[i]=b.prajituri[i];
		Bucatar::nr_restaurante++;
	}
	Bucatar operator=(Bucatar b)
	{
		if(this->nume!=NULL)
			delete [] this->nume;
		if(this->prajituri!=NULL)
			delete [] this->prajituri;
		this->nume=new char[strlen(b.nume)+1];
		strcpy(this->nume, b.nume);
		this->greutate=b.greutate;
		this->nr_ore=b.nr_ore;
		this->prajituri=new int[b.nr_ore];
		for(int i=0;i<b.nr_ore;i++)
			this->prajituri[i]=b.prajituri[i];
		return *this;
	}
	static int getNr_restaurante()
	{
		return Bucatar::nr_restaurante;
	}
	int getGreutate()
	{
		return this->greutate;
	}
	friend ostream &operator<<(ostream &out, Bucatar &b);
	friend istream &operator>>(istream &in, Bucatar &b);
	Bucatar operator+(int val)
	{
		Bucatar copie=*this;
		copie.greutate=this->greutate+val;
		return copie;
	}
	Bucatar operator+(Bucatar b)
	{
		Bucatar copie=*this;
		copie.greutate=this->greutate+b.greutate;
		return copie;
	}
	Bucatar operator++()
	{
		this->greutate++;
		return *this;
	}
	Bucatar operator++(int)
	{
		Bucatar copie=*this;
		this->greutate++;
		return copie;
	}
};
int Bucatar::nr_restaurante=0; 
ostream &operator<<(ostream &out, Bucatar &b)
{
	out<<"Cod: "<<b.cod<<endl;
	out<<"Nume: "<<b.nume<<endl;
	out<<"Greutate: "<<b.greutate<<endl;
	out<<"Nr ore: "<<b.nr_ore<<endl;
	out<<"Prajituri: ";
	for(int i=0;i<b.nr_ore;i++)
		out<<b.prajituri[i]<<" ";
	return out;
}
istream &operator>>(istream &in, Bucatar &b)
{
	cout<<endl<<"dati nume:";
	char aux[100];
	in>>aux;
	if(b.nume!=NULL)
		delete [] b.nume;
	b.nume=new char[strlen(aux)+1];
	strcpy(b.nume, aux);
	cout<<endl<<"dati greutate:";
	in>>b.greutate;
	cout<<endl<<"dati nr ore:";
	in>>b.nr_ore;
	cout<<endl<<"dati prajituri:";
	if(b.prajituri!=NULL)
		delete [] b.prajituri;
	b.prajituri=new int[b.nr_ore];
	for(int i=0;i<b.nr_ore;i++)
		in>>b.prajituri[i];
	return in;
}

void main()
{
	Bucatar b1;
	cout<<b1<<endl;

	int x[]={5,24,0,68};
	Bucatar b2(123,"Ion",80,4,x);
	cout<<b2<<endl;

	Bucatar b3=b1;
	cout<<b3<<endl;

	Bucatar b4;
	b4=b1;
	cout<<b4<<endl;

	Bucatar b5;
	cin>>b5;
	cout<<b5<<endl;

	Bucatar b6;
	b6=++b1;
	cout<<b6.getGreutate()<<endl;

	Bucatar b7;
	b7=b1++;
	cout<<b7.getGreutate()<<endl;

	Bucatar b8(124,"Mihai",50,4,x);
	b8=b1+10;
	cout<<b8.getGreutate()<<endl;
	cout<<b1.getGreutate()<<endl;

	Bucatar b9;
	b9=b1+b8;
	cout<<b9.getGreutate()<<endl;
	cout<<b1.getGreutate()<<endl;
}
