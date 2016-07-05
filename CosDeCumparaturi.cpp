#include<iostream>
using namespace std;
#include<fstream>
#include<list>
#define NMAX 100
class Articol{
public:
	int idArticol;
	char denumire[30];
	double pu;
	double cantitate;
public:
	Articol()
	{
		this->idArticol=0;
		strcpy(this->denumire,"Nedefinit");
		this->pu=0;
		this->cantitate=0;
	}
	Articol(int idArticol, char* denumire, double pu, double cantitate)
	{
		this->idArticol=idArticol;
		strcpy(this->denumire,denumire);
		this->pu=pu;
		this->cantitate=cantitate;
	}
	~Articol(){}
	friend ostream &operator<<(ostream &out, Articol &a);
	friend istream &operator>>(istream &in, Articol &a);
	friend ofstream &operator<<(ofstream &out, Articol &a);
	friend ifstream &operator>>(ifstream &in, Articol &a);
};
ostream &operator<<(ostream &out, Articol &a)
{
	out<<" Articol: "<<endl;
	out<<"  Id articol:"<<a.idArticol<<endl;
	out<<"  Denumire articol:"<<a.denumire<<endl;
	out<<"  Cantitate:"<<a.cantitate<<endl;
	out<<"  Pret unitar:"<<a.pu<<endl;
	return out;
}
istream &operator>>(istream &in, Articol &a)
{
	cout<<"Dati id articol:"<<endl;
	in>>a.idArticol;
	cout<<"Dati denumire articol:"<<endl;
	in>>a.denumire;
	cout<<"Dati cantitate:"<<endl;
	in>>a.cantitate;
	cout<<"Dati pret unitar:"<<endl;
	in>>a.pu;
	return in;
}
ofstream &operator<<(ofstream &out, Articol &a)
{
	out<<a.idArticol<<endl;
	out<<a.denumire<<endl;
	out<<a.cantitate<<endl;
	out<<a.pu<<endl;
	return out;
}
ifstream &operator>>(ifstream &in, Articol &a)
{
	in>>a.idArticol;
	in>>a.denumire;
	in>>a.cantitate;
	in>>a.pu;
	return in;
}
class CosDeCumparaturi{
public:
	int numarCurentDeArticole;
	Articol produse[NMAX];
public:
	CosDeCumparaturi()
	{
		this->numarCurentDeArticole=0;
		for (int i = 0; i < numarCurentDeArticole; i++)
		{
			this->produse[i].idArticol = 0;
			this->produse[i].cantitate = 0;
			this->produse[i].pu = 0;
			strcpy(this->produse[i].denumire, "Nedefinit");
		}
	}
	CosDeCumparaturi(Articol *produse, int numarCurentDeArticole)
	{
		this->numarCurentDeArticole=numarCurentDeArticole;
		for (int i = 0; i < numarCurentDeArticole; i++)
		{
			this->produse[i].idArticol = produse[i].idArticol;
			this->produse[i].cantitate = produse[i].cantitate;
			this->produse[i].pu = produse[i].pu;
			strcpy(this->produse[i].denumire, produse[i].denumire);
		}
	}
	~CosDeCumparaturi(){}
	CosDeCumparaturi(Articol &a)
	{
		this->numarCurentDeArticole=1;
		for (int i = 0; i < numarCurentDeArticole; i++)
		{
			this->produse[i].idArticol = a.idArticol;
			this->produse[i].cantitate = a.cantitate;
			this->produse[i].pu = a.pu;
			strcpy(this->produse[i].denumire, a.denumire);
		}
	}
	friend ostream &operator<<(ostream &out, CosDeCumparaturi &cc);
	friend istream &operator>>(istream &in, CosDeCumparaturi &cc);
	friend ofstream &operator<<(ofstream &out, CosDeCumparaturi &cc);
	friend ifstream &operator>>(ifstream &in, CosDeCumparaturi &cc);
	char* operator[](int index)
	{
		static char* err="Necunoscut";
		int i=0;
		while(i<numarCurentDeArticole)
		{
			if(produse[i].idArticol==index)
				return produse[i].denumire;
			i++;
		}
		return err;
	}
	operator double()
	{
		double s = 0;
		for (int i = 0; i < numarCurentDeArticole; i++)
			s = s + produse[i].pu*produse[i].cantitate;
		return s;
	}
	CosDeCumparaturi operator-=(int valoare)
	{
		for(int i=0;i<this->numarCurentDeArticole;i++)
		{
			if (this->produse[i].idArticol==valoare)
			{
				for(int j=i;j<numarCurentDeArticole-1;j++)
				{
					this->produse[j].idArticol = this->produse[j+1].idArticol;
					strcpy(this->produse[j].denumire, this->produse[j+1].denumire);
					this->produse[j].cantitate = this->produse[j+1].cantitate;
					this->produse[j].pu = this->produse[j+1].pu;
				}
				this->numarCurentDeArticole--;
			}
		}
		return *this;
	}
	CosDeCumparaturi operator-=(Articol a)
	{
		for(int i=0;i <this->numarCurentDeArticole;i++)
		{
			if(this->produse[i].idArticol==a.idArticol && a.cantitate==1)
			{
				for(int j=i;j<numarCurentDeArticole-1;j++)
				{
					this->produse[j].idArticol = this->produse[j+1].idArticol;
					strcpy(this->produse[j].denumire, this->produse[j+1].denumire);
					this->produse[j].cantitate = this->produse[j+1].cantitate;
					this->produse[j].pu = this->produse[j+1].pu;
				}
				this->numarCurentDeArticole--;	
			}
			else if(this->produse[i].idArticol==a.idArticol && a.cantitate!=1)
				this->produse[i].cantitate--;
		}
		return *this;
	}
	CosDeCumparaturi operator+=(Articol a)
	{
		int ok=0;
		for(int i=0;i<this->numarCurentDeArticole;i++)
		{
			if (this->produse[i].idArticol==a.idArticol)
			{
				this->produse[i].cantitate++;
				ok=1;
			}
		}
		if(ok==0)
		{
			int i = this->numarCurentDeArticole;
			if (i < NMAX)
			{
				this->produse[i].idArticol = a.idArticol;
				strcpy(this->produse[i].denumire, a.denumire);
				this->produse[i].cantitate = a.cantitate;
				this->produse[i].pu = a.pu;
			}
			this->numarCurentDeArticole++;
		}
		return *this;
	}
	bool operator>(CosDeCumparaturi cc)
	{
		if(this->numarCurentDeArticole>cc.numarCurentDeArticole)
			return true;
		else
			return false;
	}
};
ostream &operator<<(ostream &out, CosDeCumparaturi &cc)
{
	out<<"Nr articole:"<<cc.numarCurentDeArticole<<endl;
	for(int i=0;i<cc.numarCurentDeArticole;i++)
		out<<cc.produse[i];
	return out;
}
istream &operator>>(istream &in, CosDeCumparaturi &cc)
{
	cout<<"Dati nr articole:"<<endl;
	in>>cc.numarCurentDeArticole;
	cout<<"Dati articole:"<<endl;
	for(int i=0;i<cc.numarCurentDeArticole;i++)
		in>>cc.produse[i];
	return in;
}
ofstream &operator<<(ofstream &out, CosDeCumparaturi &cc)
{
	out<<cc.numarCurentDeArticole<<endl;
	for(int i=0;i<cc.numarCurentDeArticole;i++)
		out<<cc.produse[i];
	return out;
}
ifstream &operator>>(ifstream &in, CosDeCumparaturi &cc)
{
	in>>cc.numarCurentDeArticole;
	for(int i=0;i<cc.numarCurentDeArticole;i++)
		in>>cc.produse[i];
	return in;
}
template <typename T>
void sorteaza(T vector[], int dimensiune) 
{
	for (int i = 0; i < dimensiune-1; i++)
	{
		for (int j = i + 1; j < dimensiune; j++)
		{
			if (vector[i] > vector[j])
			{
				T temp = vector[i];
				vector[i] = vector[j];
				vector[j] = temp;
			}
		}
	}
	for (int i = 0; i < dimensiune; i++)
		cout<<vector[i];
}
void main()
{
	CosDeCumparaturi cc1;
	cin>>cc1;

	Articol a1;
	CosDeCumparaturi cc2(a1);

	Articol a2(101,"TV",2999.99,1);
	Articol a3(102,"Telecomanda",149.99,1);
	Articol a4(103,"Kit Wireless",119.99,1);
	Articol articole[]={a2,a3,a4};
	CosDeCumparaturi cc3(articole,3);

	cout<<cc1<<endl<<cc2<<endl<<cc3<<endl;
	
	CosDeCumparaturi cc4;
	cc4+=a1;//se adauga un articol in cos; daca exista articolul se incrementeaza cantitate
	cc4+=a2;
	cc4+=a3;
	cc4+=a4;
	cout<<cc4<<endl;
	
	cc4-=0;//se sterge articolul cu codul 0 din cos
	cout<<cc4<<endl;
	
	cc4-=a2;//se sterge articolul a2 din cos pentru cantitate=1; altfel se diminueaza cantitatea
	cout<<cc4<<endl;

	cout<<"Valoarea cosului este: "<<(double)cc4<<endl;
	cout<<"Articolul cu identificatorul 102 din cosul c4 este : "<<cc4[102]<<endl;
	
	ofstream fOut("iesire.txt");
	fOut<<cc2;//se salveaza datele despre cosul cc2 in fisier binar
	fOut.close();
	ifstream fIn("intrare.txt");	
	fIn>>cc2;//se restaureaza datele despre cosul cc2 din fisier binar
	cout<<cc2<<endl;
	fIn.close();

	CosDeCumparaturi listaCC[]={cc1, cc2, cc3, cc4};
	sorteaza(listaCC,4);// functie generica pentru sortarea crescatoare a elementelor masivului unidimensional
	
	//se adauga toate cosurile de cumparaturi si se calculeaza valoarea totala a tranzactiilor folosind un iterator 
	list<CosDeCumparaturi> comenziCurente;
	comenziCurente.push_back(cc1);
	comenziCurente.push_back(cc2);
	comenziCurente.push_back(cc3);
	comenziCurente.push_back(cc4);
	list<CosDeCumparaturi>::iterator it;
	double valoareTotala=0;
	for(it=comenziCurente.begin(); it!=comenziCurente.end();it++)
	{
		double valoareCos=(double)(*it);
		valoareTotala+=valoareCos;
	}
	cout<<"Valoarea totala a tranzactiilor este: "<<valoareTotala;
}