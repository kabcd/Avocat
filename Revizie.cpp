#include<iostream>
using namespace std;
#include<fstream>
#include<list>
class Operatie{
public:
	char denumire[50];
	float pret;
public:
	Operatie()
	{
		strcpy(this->denumire,"Anonim");
		this->pret=0;
	}
	Operatie(char* denumire, float pret)
	{
		strcpy(this->denumire,denumire);
		this->pret=pret;
	}
	Operatie(Operatie &o)
	{
		strcpy(this->denumire,o.denumire);
		this->pret=o.pret;
	}
	char* getDenumire()
	{
		return this->denumire;
	}
	int getPret()
	{
		return this->pret;
	}
	friend ostream &operator<<(ostream &out, Operatie &o);
};
ostream &operator<<(ostream &out, Operatie &o)
{
	out<<o.denumire<<" "<<o.pret<<endl;
	return out;
}
class Revizie{
protected:
	char numar_auto[15];
	int numar_revizie;
	long numar_kilometri;
	char data[11];
	int numar_operatii;
	Operatie *operatii;
public:
	Revizie()
	{
		strcpy(this->numar_auto,"Anonim");
		this->numar_revizie=0;
		this->numar_kilometri=0;
		strcpy(this->data,"00/00/0000");
		this->numar_operatii=0;
		this->operatii = NULL;
	}
	Revizie(char* numar_auto, int numar_revizie, long numar_kilometri)
	{
		strcpy(this->numar_auto,numar_auto);
		this->numar_revizie=numar_revizie;
		this->numar_kilometri=numar_kilometri;
		strcpy(this->data,"00/00/0000");
		this->numar_operatii=0;
		this->operatii = new Operatie[this->numar_operatii];
		Operatie o;
		for(int i=0;i<this->numar_operatii;i++)
			this->operatii[i]=o;
	}
	Revizie(char* numar_auto, int numar_revizie, long numar_kilometri, Operatie operatie)
	{
		strcpy(this->numar_auto,numar_auto);
		this->numar_revizie=numar_revizie;
		this->numar_kilometri=numar_kilometri;
		strcpy(this->data,"00/00/0000");
		this->numar_operatii=1;
		this->operatii = new Operatie[1];
		this->operatii[0]=operatie;
	}
	Revizie(char* numar_auto, Operatie *operatii, int numar_operatii)
	{
		strcpy(this->numar_auto,numar_auto);
		this->numar_revizie=0;
		this->numar_kilometri=0;
		strcpy(this->data,"00/00/0000");
		this->numar_operatii=numar_operatii;
		this->operatii = new Operatie[this->numar_operatii];
		for(int i=0;i<this->numar_operatii;i++)
			this->operatii[i]=operatii[i];
	}
	void setNumarAuto(char* numar_autoNou)
	{
		if(numar_autoNou!=NULL)
			strcpy(this->numar_auto,numar_autoNou);
		else
			throw new exception("Numar auto invalid!");
	}
	virtual double getCostRevizie()
	{
		double s=0;
		for(int i=0;i<this->numar_operatii;i++)
			s=s+this->operatii[i].getPret();
		return s;
	}
	friend istream &operator>>(istream &in, Revizie &r);
	friend ostream &operator<<(ostream &out, Revizie &r);
	Revizie operator+=(Operatie o)
	{
		int ok=0;
		for(int i=0;i<this->numar_operatii;i++)
		{
			if(strcmp(this->operatii[i].denumire,o.denumire)==0)
				ok=1;
		}
		if(ok==0)
		{
			Operatie *tmp= new Operatie[this->numar_operatii + 1];
			for (int i = 0; i < this->numar_operatii; i++)
				tmp[i]=this->operatii[i];
			tmp[this->numar_operatii]=o;
			if(this->operatii!=NULL)
				delete[] this->operatii;
			this->numar_operatii++;
			this->operatii = new Operatie[this->numar_operatii];
			for (int i = 0; i < this->numar_operatii; i++)
				this->operatii[i] = tmp[i];
		}
		return *this;
	}
	Revizie operator-=(char* valoare)
	{
		for(int i=0;i<this->numar_operatii;i++)
		{
			if(strcmp(this->operatii[i].denumire,valoare)==0)
			{
				for(int j=i;j<this->numar_operatii-1;j++)
					this->operatii[j]=this->operatii[j+1];
				this->numar_operatii--;
			}
		}
		return *this;
	}
	Revizie operator-=(Operatie o)
	{
		for(int i=0;i<this->numar_operatii;i++)
		{
			if(strcmp(this->operatii[i].denumire,o.denumire)==0)
			{
				for(int j=i;j<this->numar_operatii-1;j++)
					this->operatii[j]=this->operatii[j+1];
				this->numar_operatii--;
			}
		}
		return *this;
	}
	operator double()
	{
		return this->getCostRevizie();
	}
	bool operator<(Revizie r)
	{
		if(this->getCostRevizie()<r.getCostRevizie())
			return true;
		else
			return false;
	}
	Operatie &operator[](int index)
	{
		if(index>=0 && index<this->numar_operatii)
			return operatii[index];
		else
			throw "Index invalid!";
	}
	friend ofstream &operator<<(ofstream &out, Revizie &r);
	friend ifstream &operator>>(ifstream &in, Revizie &r);
};
ofstream &operator<<(ofstream &out, Revizie &r)
{
	out.write((char*)&r, sizeof(Revizie));
	return out;
}
ifstream &operator>>(ifstream &in, Revizie &r)
{
	in.read((char*)&r, sizeof(Revizie));
	return in;
}
istream &operator>>(istream &in, Revizie &r)
{
	cout<<endl<<"Dati numar auto:";
	in>>r.numar_auto;
	cout<<"Dati numar revizie:";
	in>>r.numar_revizie;
	cout<<"Dati numar kilometri:";
	in>>r.numar_kilometri;
	cout<<"Dati numar operatii:";
	in>>r.numar_operatii;
	r.operatii = new Operatie[r.numar_operatii];
	for(int i=0;i<r.numar_operatii;i++)
	{
		cout<<"Dati denumire operatie: ";
		in.ignore(256,'\n');
		char aux[50];
		in.getline(aux, 50);
		strcpy(r.operatii[i].denumire, aux);
		cout<<"Dati pret operatie: ";
		in>>r.operatii[i].pret;
	}
	return in;
}
ostream &operator<<(ostream &out, Revizie &r)
{
	out<<r.numar_auto<<" "<<r.numar_revizie<<" "<<r.numar_kilometri<<" "<<r.numar_operatii<<endl;
	for(int i=0;i<r.numar_operatii;i++)
		out<<r.operatii[i].getDenumire()<<" "<<r.operatii[i].getPret()<<endl;
	return out;
}
class RevizieSpeciala: public Revizie{
private:
	float reducere;
public:
	RevizieSpeciala(char *numar_auto, int numar_revizie, long numar_kilometri, Operatie operatie, float reducere)
		:Revizie(numar_auto, numar_revizie, numar_kilometri, operatie)
	{
		this->reducere=reducere;
	}
	double getCostRevizie()
	{
		return Revizie::getCostRevizie()*this->reducere;
	}
	operator double()
	{
		return this->getCostRevizie();
	}
	friend ostream &operator<<(ostream &out, RevizieSpeciala &rs);
};
ostream &operator<<(ostream &out, RevizieSpeciala &rs)
{
	out<<rs.numar_auto<<" "<<rs.numar_revizie<<" "<<rs.numar_kilometri<<" "<<rs.numar_operatii<<endl;
	for(int i=0;i<rs.numar_operatii;i++)
		out<<rs.operatii[i].getDenumire()<<" "<<rs.operatii[i].getPret()<<endl;
	out<<"Reducere:"<<rs.reducere<<endl;
	return out;
}
void main()
{
	Revizie r1;
	r1.setNumarAuto("TX11111A");

	Revizie r2("B99ABC",1,10000);
	cout<<r2.getCostRevizie()<<endl;

	Operatie o1("Schimbare ulei",150);
	Operatie o2("Inlocuire filtru aer",99);
	Operatie o3("Inlocuire filtru polen",55);
	Operatie o4=o1;
	Revizie r5("B88ABC",2,20000,o4);
	
	Operatie operatii[]={o1,o2,o3,o4};
	Revizie r3("B111XYZ",operatii,4);
	
	Revizie r4;
	cin>>r4;
	cout<<r1<<endl<<r2<<endl<<r3<<endl<<r4<<endl<<r5<<endl;

	r1+=o1; r1+=o2; r1+=o3; r1+=o4;// se adauga o operatie, daca exista operatia nu se adauga
	cout<<r1<<endl;

	r1-="Schimbare ulei";//se elimina operatia cu numele dat
	r1-=o2;// se elimina operatia o2
	cout<<r1<<endl;
	
	cout<<"Costul reviziei este:"<<(double)r2<<endl;
	if(r1<r2)
		cout<<"Revizia r2 este mai scumpa decat r1"<<endl;
	else
		cout<<"Revizia r2 este mai ieftina decat r1"<<endl;
	try{
		cout<<r2[2]<<endl;
	}
	catch(char* ex)
	{
		cout<<ex<<endl;
	}

	ofstream out("revizii.dat");
	out<<r2;//se scriu in fisier binar datele despre revizia r2
	out.close();
	ifstream in("revizii.dat");
	Revizie r6;
	in>>r6;//se citesc din fisier binar datele despre revizia r2
	cout<<r6<<endl;
	
	RevizieSpeciala rs("B123KLM",1,25000,o1,0.25);
	rs+=o3;
	cout<<rs<<endl;
	cout<<(double)rs<<endl;

	// se adauga toate reviziile intr-o structura STL de tip lista si utilizand iteratori se parcurge multimea de revizii si se calculeaza incasarile totale a service-ului auto
	list<Revizie> revizii;
	revizii.push_back(r1);
	revizii.push_back(r2);
	revizii.push_back(rs);
	revizii.push_back(r3);
	list<Revizie>::iterator it;
	double suma=0;
	for(it=revizii.begin(); it!=revizii.end(); it++)
		suma+=(*it).getCostRevizie();
	cout<<"Incasarea totala este: "<<suma<<endl;
}