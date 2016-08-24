#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<fstream>
class Produs{
protected:
	char* denumire;
	double pret;
	int cantitate;
public:
	Produs()
	{
		this->denumire=new char[strlen("Anonim")+1];
		strcpy(this->denumire,"Anonim");
		this->pret=0;
		this->cantitate=0;
	}
	Produs(char* denumire, double pret)
	{
		this->denumire=new char[strlen(denumire)+1];
		strcpy(this->denumire,denumire);
		this->pret=pret;
		this->cantitate=0;
	}
	~Produs()
	{
		if(this->denumire!=NULL)
			delete [] this->denumire;
	}
	Produs(Produs &p)
	{
		this->denumire=new char[strlen(p.denumire)+1];
		strcpy(this->denumire,p.denumire);
		this->pret=p.pret;
		this->cantitate=p.cantitate;
	}
	Produs operator=(Produs p)
	{
		if(this->denumire!=NULL)
			delete [] this->denumire;
		this->denumire=new char[strlen(p.denumire)+1];
		strcpy(this->denumire,p.denumire);
		this->pret=p.pret;
		this->cantitate=p.cantitate;
	}
	char* getDenumire()
	{
		return this->denumire;
	}
	friend ostream &operator<<(ostream &out, Produs &p);
	bool operator<(Produs p)
	{
		if(this->cantitate*this->pret < p.cantitate*p.pret)
			return true;
		else
			return false;
	}
	Produs operator++(int)
	{
		Produs aux=*this;
		this->cantitate++;
		return aux;
	}
	Produs operator+=(int valoare)
	{
		this->cantitate+=5;
		return *this;
	}
	virtual double getValoare()
	{
		return this->pret*this->cantitate;
	}
};
ostream &operator<<(ostream &out, Produs &p)
{
	out<<endl<<p.denumire<<" "<<p.cantitate<<" * "<<p.pret<<" RON";
	return out;
}
class ProdusDiscount: public Produs{
private:
	double valoareDiscount;
public:
	ProdusDiscount():Produs()
	{
		this->valoareDiscount=0;
	}
	ProdusDiscount(char* denumire, double pret, double valoareDiscount)
		:Produs(denumire, pret)
	{
		this->valoareDiscount=valoareDiscount;
	}
	ProdusDiscount(ProdusDiscount &pd):Produs(pd)
	{
		this->valoareDiscount=pd.valoareDiscount;
	}
	ProdusDiscount operator=(ProdusDiscount pd)
	{
		Produs::operator=(pd);
		this->valoareDiscount=pd.valoareDiscount;
	}
	~ProdusDiscount(){}
	double getValoare()
	{
		return Produs::getValoare()-valoareDiscount;
	}
	ProdusDiscount operator+=(int valoare)
	{
		this->cantitate+=10;
		return *this;
	}
	friend ostream &operator<<(ostream &out, ProdusDiscount &p);
};
ostream &operator<<(ostream &out, ProdusDiscount &p)
{
	out<<endl<<p.denumire<<" "<<p.cantitate<<" * "<<p.pret<<" - "<<p.valoareDiscount<<" RON";
	return out;
}
class Cos{
public:
	Produs* *produse;
	int n;
public:
	Cos()
	{
		this->n=0;
		this->produse=NULL;
	}
	Cos(Cos &c)
	{
		this->n=c.n;
		this->produse=new Produs*[c.n];
		for(int i=0;i<c.n;i++)
			this->produse[i]=c.produse[i];
	}
	Cos operator=(Cos c)
	{
		if(this->produse!=NULL)
			delete [] this->produse;
		this->n=c.n;
		this->produse=new Produs*[c.n];
		for(int i=0;i<c.n;i++)
			this->produse[i]=c.produse[i];
	}
	~Cos()
	{
		if(this->produse!=NULL)
			delete [] this->produse;
	}
	double total()
	{
		double suma=0;
		for(int i=0;i<this->n;i++)
			suma+=this->produse[i]->getValoare();
		return suma;
	}
	vector<string> obtineDenumiri()
	{
		vector<string> denumiri;
		for(int i=0;i<this->n;i++)
			denumiri.push_back(this->produse[i]->getDenumire());
		return denumiri;
	}
	void scrieInFisier(ofstream &fisier)
	{
		// lista de produse sortate in functie de valoare
		if (fisier.is_open())
		{
			for(int i=0;i<this->n-1;i++)
			{
				if(this->produse[i]->getValoare()>this->produse[i+1]->getValoare())
				{
					Produs* aux=this->produse[i];
					this->produse[i]=this->produse[i+1];
					this->produse[i+1]=aux;
				}
			}
			for(int i=0;i<this->n;i++)
				fisier<<this->produse[i]->getDenumire()<<" "<<this->produse[i]->getValoare()<<endl;
		}
		fisier.close();
	}
	Cos operator+=(Produs* p)
	{
		Produs* *vecprod=new Produs*[this->n+1];
		for(int i=0;i<this->n;i++)
			vecprod[i]=this->produse[i];
		vecprod[this->n]=p;
		if(this->produse!=NULL)
			delete [] this->produse;
		this->n++;
		this->produse=new Produs*[this->n];
		for(int i=0;i<this->n;i++)
			this->produse[i]=vecprod[i];
		return *this;
	}
};
void main()
{
	Produs mere("Mere",4.1);
	Produs pere("Pere",6.5);
	mere++; pere++;
	mere+=5;
	cout<<mere<<endl<<pere<<endl;

	if(mere<pere)
		cout<<"Valoarea merelor este mai mica"<<endl;
	else
		cout<<"Valoarea perelor este mai mica"<<endl;
	
	ProdusDiscount struguri("Struguri",8,15);
	struguri+=10;
	cout<<struguri<<endl;

	Cos cos;
	cos+=&struguri;
	cos+=&pere;
	cos+=&mere;
	cout<<"TOTAL:"<<cos.total()<<endl;
	ofstream fisier("date_cos.txt");
	cos.scrieInFisier(fisier);

	vector<string> denumiriProduse=cos.obtineDenumiri(); 
	vector<string>::iterator it;
	for(it=denumiriProduse.begin(); it!=denumiriProduse.end(); it++)
		cout<<*it<<endl;
}