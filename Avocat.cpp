#include<iostream>
using namespace std;
#include<fstream>
#include<list>
class Avocat{
private:
	const int cod;
	char* nume;
	int onorariu;
	int nr_procese;
	int *valori_procese;
public:
	Avocat():cod(0)
	{
		this->nume=new char[strlen("Anonim")+1];
		strcpy(this->nume,"Anonim");
		this->onorariu=0;
		this->nr_procese=0;
		this->valori_procese=new int[nr_procese];
		for(int i=0;i<nr_procese;i++)
			this->valori_procese=0;	
	}
	Avocat(const int c, char* nume, int onorariu, int nr_procese, int *valori_procese):cod(c)
	{
		this->nume=new char[strlen(nume)+1];
		strcpy(this->nume,nume);
		this->onorariu=onorariu;
		this->nr_procese=nr_procese;
		this->valori_procese=new int[nr_procese];
		for(int i=0;i<nr_procese;i++)
			this->valori_procese[i]=valori_procese[i];
	}
	Avocat(const Avocat &a):cod(a.cod)
	{
		this->nume=new char[strlen(a.nume)+1];
		strcpy(this->nume,a.nume);
		this->onorariu=a.onorariu;
		this->nr_procese=a.nr_procese;
		this->valori_procese=new int[a.nr_procese];
		for(int i=0;i<a.nr_procese;i++)
			this->valori_procese[i]=a.valori_procese[i];
	}
	void operator=(Avocat a)
	{
		if(this->nume!=NULL)
			delete [] this->nume;
		if(this->valori_procese!=NULL)
			delete [] this->valori_procese;
		this->nume=new char[strlen(a.nume)+1];
		strcpy(this->nume,a.nume);
		this->onorariu=a.onorariu;
		this->nr_procese=a.nr_procese;
		this->valori_procese=new int[a.nr_procese];
		for(int i=0;i<a.nr_procese;i++)
			this->valori_procese[i]=a.valori_procese[i];
	}
	~Avocat()
	{
		if(this->nume!=NULL)
			delete [] this->nume;
		if(this->valori_procese!=NULL)
			delete [] this->valori_procese;
	}
	char* getNume()
	{
		return this->nume;
	}
	int getNumarProcese()
	{
		return this->nr_procese;
	}
	int getOnorariu()
	{
		return this->onorariu;
	}
	const int getCod()
	{
		return this->cod;
	}
	int *getVectorProcese()
	{
		return this->valori_procese;
	}
	void setNume(char* numeNou)
	{
		if(this->nume!=NULL)
		{
			delete [] this->nume;
			this->nume=new char[strlen(numeNou)+1];
			strcpy(this->nume,numeNou);
		}
		else
			throw new exception("nume invalid!");
	}
	void setVectorProcese(int *valoriProceseNou, int nrProceseNou)
	{
		if(this->valori_procese!=NULL)
		{
			delete [] this->valori_procese;
			this->nr_procese=nrProceseNou;
			this->valori_procese=new int[nrProceseNou];
			for(int i=0;i<nrProceseNou;i++)
				this->valori_procese[i]=valoriProceseNou[i];
		}
		else
			throw new exception("vecctor procese invalid!");
	}
	friend ostream &operator<<(ostream &out, Avocat a);
	int &operator[](int index)
	{
		static int err;
		if(index>=0 && index<this->nr_procese)
			return valori_procese[index];
		else
			return err;
	}
	bool operator>(Avocat a)
	{
		if(this->nr_procese>a.nr_procese)
			return true;
		else
			return false;
	}
	bool operator<(Avocat a)
	{
		if(this->nr_procese<a.nr_procese)
			return true;
		else
			return false;
	}
	bool operator==(Avocat a)
	{
		if(this->nr_procese==a.nr_procese)
			return true;
		else
			return false;
	}
	Avocat operator+(int valoare)
	{
		Avocat aux=*this;
		int *v;
		v=new int[aux.nr_procese+1];
		for(int i=0;i<aux.nr_procese;i++)
			v[i]=aux.valori_procese[i];
		v[aux.nr_procese]=2000;
		
		delete [] aux.valori_procese;
		aux.nr_procese++;
		aux.valori_procese=new int[aux.nr_procese];
		for(int i=0;i<aux.nr_procese;i++)
			aux.valori_procese[i]=v[i];
		return aux;
	}
	Avocat operator-=(int valoare)
	{
		this->onorariu-=valoare;
		return *this;
	}
	int valMedieProcese()
	{
		int s=0;
		for(int i=0;i<this->nr_procese;i++)
			s=s+this->valori_procese[i];
		return s/this->nr_procese;	
	}
	friend ofstream &operator<<(ofstream &out,Avocat a);
	friend ifstream &operator>>(ifstream &in,Avocat &a);
};
ostream &operator<<(ostream &out, Avocat a)
{
	out<<a.cod<<" "<<a.nume<<" "<<a.onorariu<<" "<<a.nr_procese<<" "<<"Valori_procese: ";
	for(int i=0;i<a.nr_procese;i++)
		out<<a.valori_procese[i]<<" ";
	return out;
}
ofstream &operator<<(ofstream &out,Avocat a)
{
	out<<a.cod<<endl;
	out<<a.nume<<endl;
	out<<a.onorariu<<endl;
	out<<a.nr_procese<<endl;
	for(int i=0;i<a.nr_procese;i++)
		out<<a.valori_procese[i]<<endl;
	return out;
}
ifstream &operator>>(ifstream &in,Avocat &a)
{
	char aux[50];
	in.getline(aux,50);
	delete [] a.nume;
	a.nume=new char[strlen(aux)+1];
	strcpy(a.nume,aux);
	in>>a.onorariu;
	in>>a.nr_procese;
	a.valori_procese=new int[a.nr_procese];
	for(int i=0;i<a.nr_procese;i++)
		in>>a.valori_procese[i];
	return in;
}
class AvocatOficiu:public Avocat{
private:
	char* client;
	int durata_proces;
public:
	AvocatOficiu():Avocat(0,"Anonim",0,0,0)
	{
		this->client=new char[strlen("Necunoscut")+1];
		strcpy(this->client, "Necunoscut");
		this->durata_proces=0;
	}
	AvocatOficiu(const int cod, char* nume, int onorariu, int nr_procese, int *valori_procese,char* client, int durata_proces)
		:Avocat(cod, nume,onorariu, nr_procese, valori_procese)
	{
		this->client=new char[strlen(client)+1];
		strcpy(this->client, client);
		this->durata_proces=durata_proces;
	}
	friend ostream &operator<<(ostream &out, AvocatOficiu a);
};
ostream &operator<<(ostream &out, AvocatOficiu a)
{
	out<<a.getCod()<<" "<<a.getNume()<<" "<<a.getOnorariu()<<" "<<a.getNumarProcese()<<" "<<"Valori_procese: ";
	for(int i=0;i<a.getNumarProcese();i++)
		out<<a.getVectorProcese()[i]<<" ";
	out<<a.client<<" "<<a.durata_proces;
	return out;
}
void main()
{
	Avocat a1;
	int *vectProc1;
	vectProc1=new int[3];
	vectProc1[0]=2000;
	vectProc1[1]=1500;
	vectProc1[2]=8000;
	Avocat a2(123,"Georgescu Vasile",120,3,vectProc1);
	
	cout<<a2.getNume()<<endl;
	a2.setNume("Paraschivescu Gigel");
	cout<<a1.getCod()<<endl;
	for(int i=0;i<a2.getNumarProcese();i++)
		cout<<a2.getVectorProcese()[i]<<" ";
	cout<<endl;
	int *vectProc2;
	vectProc2=new int[4];
	vectProc2[0]=8000;
	vectProc2[1]=1500;
	vectProc2[2]=2000;
	vectProc2[3]=5000;
	a2.setVectorProcese(vectProc2,4);

	Avocat a3=a2;
	Avocat a4;
	a4=a3;

	cout<<a1<<endl<<a2<<endl<<a3<<endl<<a4<<endl;

	a3=a3+2000;//se adauga un proces nou in valoare de 2000 euro avocatului a3
	a2-=30;//se diminueaza onorariul avocatului a2 cu 30 euro
	cout<<a2<<endl<<a3<<endl;

	cout<<"Valoarea medie a unui proces este:"<<a3.valMedieProcese()<<endl;

	if(a3>a2)
		cout<<"Avocatul a3 are mai multe procese ca a2"<<endl;
	else if(a3<a2)
		cout<<"Avocatul a3 are mai putine procese ca a2"<<endl;
	else if(a3==a2)
		cout<<"Avocatul a3 are acelasi numar de procese ca a2"<<endl;

	cout<<a2[2]<<endl;//se afiseaza valoarea celui de-al 3-lea proces al avocatului a2
	
	ofstream fisOut("iesire.txt");
	fisOut<<a4;//se salveaza in fisier datele despre avocatul a4
	fisOut.close();
	ifstream fisIn("intrare.txt",ios::in);
	fisIn>>a4;//se citesc din fisier datele despre avocatul a4
	cout<<a4<<endl;
	fisIn.close();

	int *vectProc3;
	vectProc3=new int[3];
	vectProc3[0]=7000;
	vectProc3[1]=3500;
	vectProc3[2]=200;
	AvocatOficiu ao1(123,"Georgescu Vasile",120,3,vectProc3,"Popescu Ion",4);
	cout<<ao1<<endl;

	// se adauga toti avocatii  intr-o structura STL de tip lista, se sorteaza si apoi se afiseaza folosind un iterator
	list<Avocat> barou;
	barou.push_back(a1);
	barou.push_back(a2);
	barou.push_back(a3);
	barou.push_back(a4);
	barou.sort();
	list<Avocat>::iterator it;
	for(it=barou.begin(); it!=barou.end(); it++)
		cout<<*it<<endl;
}
