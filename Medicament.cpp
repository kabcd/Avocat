#include<iostream>
using namespace std;
#include<fstream>
#include<list>
class Medicament{
private:
	char* denumire;
	float pret;
public:
	//constructor default
	Medicament()
	{
		this->denumire=new char[strlen("Anonim")+1];
		strcpy(this->denumire,"Anonim");
		this->pret=0;
	}
	//constructor cu 2 parametri
	Medicament(char* denumire, float pret)
	{
		this->denumire=new char[strlen(denumire)+1];
		strcpy(this->denumire,denumire);
		this->pret=pret;
	}
	//constructor de copiere
	Medicament(Medicament &m)
	{
		this->denumire=new char[strlen(m.denumire)+1];
		strcpy(this->denumire,m.denumire);
		this->pret=m.pret;
	}
	//supraincarcare operator =
	Medicament operator=(Medicament m)
	{
		if(this->denumire!=NULL)
			delete [] this->denumire;
		this->denumire=new char[strlen(m.denumire)+1];
		strcpy(this->denumire,m.denumire);
		this->pret=m.pret;
		return *this;
	}
	//destructor
	~Medicament()
	{
		if(this->denumire!=NULL)
			delete [] this->denumire;
	}
	//getterii si setterii
	char* getDenumire()
	{
		return this->denumire;
	}
	float getPret()
	{
		return this->pret;
	}
	void setPret(float pretNou)
	{
		if(pretNou>0)
			this->pret=pretNou;
		else
			throw new exception("Pret invalid!");	
	}
	void setDenumire(char *denumireNou)
	{
		if(denumireNou!=NULL)
		{
			delete [] this->denumire;
			this->denumire=new char[strlen(denumireNou)+1];
			strcpy(this->denumire,denumireNou);
		}
		else
			throw new exception("Denumire invalida!");
	}
	//supraincarcare operator <<
	friend ostream &operator<<(ostream &out, Medicament &m);
	//supraincarcare operator >>
	friend ifstream &operator>>(ifstream &in, Medicament &m);
};
ostream &operator<<(ostream &out, Medicament &m)
{
	out<<m.denumire<<" "<<m.pret<<endl;
	return out;
}
ifstream &operator>>(ifstream &in, Medicament &m)
{
	char aux[50];
	in>>aux;
	if(m.denumire!=NULL)
		delete [] m.denumire;
	m.denumire=new char[strlen(aux)+1];
	strcpy(m.denumire,aux);
	in>>m.pret;
	return in;
}
class Reteta{
protected:
	Medicament *medicamente;
	int n;
public:
	//constructor default
	Reteta()
	{
		this->n=0;
		this->medicamente=NULL;
	}
	//constructor cu 2 parametri
	Reteta(Medicament *medicamente, int n)
	{
		this->n=n;
		this->medicamente= new Medicament[this->n];
		for (int i = 0; i <this->n; i++)
			this->medicamente[i] =medicamente[i];
	}
	//destructor
	/*~Reteta()
	{
		if(this->medicamente!=NULL)
			delete [] this->medicamente;
	}*/
	//metoda virtuala
	virtual float getValoare()
	{
		float s=0;;
		for(int i=0;i<this->n;i++)
			s=s+this->medicamente[i].getPret();
		return s;
	}
	//supraincarcare operator <<
	friend ostream &operator<<(ostream &out, Reteta &t);
	//supraincarcare operator >>
	friend ifstream &operator>>(ifstream &in, Reteta &t);
	//getterii
	Medicament *getMedicamente()
	{
		return this->medicamente;
	}
	int getN()
	{
		return this->n;
	}
	//metoda membra
	void adaugaMedicament(Medicament m)
	{
		if(this->medicamente!=NULL)
		{
			Medicament *tmp= new Medicament[this->n + 1];
			for (int i = 0; i < this->n; i++)
				tmp[i]=this->medicamente[i];
			tmp[this->n]=m;
			delete[] this->medicamente;
			this->n++;
			this->medicamente= new Medicament[this->n];
			for (int i = 0; i <this->n; i++)
				this->medicamente[i] = tmp[i];
		}
		else
		{
			this->n++;
			this->medicamente= new Medicament[this->n];
			for (int i = 0; i <this->n; i++)
				this->medicamente[i] = m;
		}
	}
	//supraincarcare operator []
	Medicament &operator[](int index)
	{
		if(index>=0 && index<this->n)
			return this->medicamente[index];
		else
			throw "Index invalid!";
	}	
};
ostream &operator<<(ostream &out, Reteta &t)
{
	out<<endl<<"Nr medicamente: "<<t.n<<" "<<"Medicamente:"<<endl;
	for(int i=0;i<t.n;i++)
		out<<t.medicamente[i]<<endl;
	return out;
}
ifstream &operator>>(ifstream &in, Reteta &t)
{
	in>>t.n;
	t.medicamente=new Medicament[t.n];
	for(int i=0;i<t.n;i++)
		in>>t.medicamente[i];
	return in;
}
class RetetaCompensata:public Reteta{
private:
	float procentCompensat;
public:
	//constructor default
	RetetaCompensata():Reteta()
	{
		this->procentCompensat=0;
	}
	//constructor cu 1 parametru
	RetetaCompensata(float procentCompensat):Reteta()
	{
		this->procentCompensat=procentCompensat;
	}
	//constructor cu 2 parametri
	RetetaCompensata(Reteta r, float procentCompensat):Reteta()
	{
		this->procentCompensat=procentCompensat;
	}
	//destructor
	~RetetaCompensata(){}
	//redefinire metoda virtuala
	float getValoare()
	{
		return Reteta::getValoare()*this->procentCompensat;
	}
	//supraincarcare operator <<
	friend ostream &operator<<(ostream &out, RetetaCompensata &rc);
};
ostream &operator<<(ostream &out, RetetaCompensata &rc)
{
	out<<endl<<"Nr medicamente: "<<rc.n<<" "<<"Medicamente:"<<endl;
	for(int i=0;i<rc.n;i++)
		out<<rc.medicamente[i]<<endl;
	out<<"Reducere: "<<rc.procentCompensat;
	return out;
}
void main()
{
	Medicament nurofen("nurofen",11.25);
	cout<<nurofen<<endl;

	Medicament aspirina=nurofen;
	aspirina.setDenumire("aspirina");
	aspirina.setPret(4.5);
	cout<<aspirina<<endl;

	Medicament bixtonim("bixtonim",8.2);
	cout<<bixtonim<<endl;

	Medicament medicamente[]={aspirina, nurofen};
	Reteta r0(medicamente,2);
	cout<<r0<<endl;

	Reteta r1;
	r1.adaugaMedicament(nurofen);
	r1.adaugaMedicament(aspirina);
	for(int i=0;i<r1.getN();i++)
		cout<<r1[i]<<endl;
	
	RetetaCompensata r2(0.5);
	r2.adaugaMedicament(bixtonim);
	r2.adaugaMedicament(aspirina);
	cout<<r2<<endl;

	RetetaCompensata r3(r1,0.2);
	Reteta* p=&r1;
	cout<<p->getValoare()<<endl;
	p=&r3;
	cout<<p->getValoare()<<endl;
	
	Reteta r4;
	ifstream fisier("retete.txt");
	fisier>>r4;
	cout<<r4<<endl;

	cout<<"----------------"<<endl;
	//se sa utilizeze o structura STL de tip list pentru a construi o lista de pointeri la obiecte Reteta, apoi sa se parcurga lista si sa se afiseze lista si valoarea fiecarei retete
	Reteta* p0=&r0; Reteta* p1=&r1; Reteta* p2=&r2; Reteta* p3=&r3; Reteta* p4=&r4;
	list<Reteta*> retete;
	retete.push_back(p0);
	retete.push_back(p1);
	retete.push_back(p2);
	retete.push_back(p3);
	retete.push_back(p4);
	list<Reteta*>::iterator it;
	for(it=retete.begin(); it!=retete.end(); it++)
		cout<<*(*it)<<" Valoare totala reteta: "<< (*it)->getValoare()<<endl;
}