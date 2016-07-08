#include <iostream>
using namespace std;
class Ferma{
private:
	const long id_ferma;
	char* denumire_ferma;
	int suprafata;
	int nr_luni;
	float *produse;
	static int nr_ferme;
public: 
	//constructor fara parametri
	Ferma():id_ferma(Ferma::nr_ferme)
	{
		this->denumire_ferma=new char[strlen("Anonim")+1];
		strcpy(this->denumire_ferma, "Anonim");
		this->suprafata=0;
		this->nr_luni=0;
		this->produse=NULL;
		nr_ferme++;
	}
	//constructor cu parametri
	Ferma(char* denumire_ferma, int suprafata,int nr_luni,float *produse):id_ferma(Ferma::nr_ferme)
	{
		this->denumire_ferma=new char[strlen(denumire_ferma)+1];
		strcpy(this->denumire_ferma,denumire_ferma);
		this->suprafata=suprafata;
		this->nr_luni=nr_luni;
		this->produse=new float[nr_luni];
		for(int i=0;i<nr_luni;i++)
			this->produse[i]=produse[i];
		Ferma::nr_ferme++;
	}
	//destructor
    ~Ferma()
	{
		if(this->denumire_ferma!=NULL)
			delete [] this->denumire_ferma;
		if(this->produse!=NULL)
			delete [] this->produse;
		Ferma::nr_ferme--;
	}
	//constructor de copiere
	Ferma(Ferma &f):id_ferma(Ferma::nr_ferme)
	{
		this->denumire_ferma=new char[strlen(f.denumire_ferma)+1];
		strcpy(this->denumire_ferma,f.denumire_ferma);
		this->suprafata=f.suprafata;
		this->nr_luni=f.nr_luni;
		this->produse=new float[f.nr_luni];
		for(int i=0;i<f.nr_luni;i++)
			this->produse[i]=f.produse[i];
		Ferma::nr_ferme++;
	}
	//supraincarcare =
	Ferma operator=(Ferma &f)
	{
		if(this->denumire_ferma!=NULL)
			delete [] this->denumire_ferma;
		if(this->produse!=NULL)
			delete [] this->produse;
		this->denumire_ferma=new char[strlen(f.denumire_ferma)+1];
		strcpy(this->denumire_ferma,f.denumire_ferma);
		this->suprafata=f.suprafata;
		this->nr_luni=f.nr_luni;
		this->produse=new float[f.nr_luni];
		for(int i=0;i<f.nr_luni;i++)
			this->produse[i]=f.produse[i];
		return *this;
	}
	friend ostream &operator<<(ostream &out, Ferma &f);
	friend istream &operator>>(istream &in, Ferma &f);
	//getterii
	char* getDenumire_ferma()
	{
		return this->denumire_ferma;
	}
	int getSuprafata()
	{
		return this->suprafata;
	}
	int getNr_luni()
	{
		return this->nr_luni;
	}
	float *getProduse()
	{
		return this->produse;
	}
	const long getId_ferma()
	{
		return this->id_ferma;
	}
	static int getNr_ferme()
	{
		return Ferma::nr_ferme;
	}
	//setterii
	void setDenumire_ferma(char *denumire_fermaNou)
	{
		if(this->denumire_ferma!=NULL)
		{
			delete [] this->denumire_ferma;
			this->denumire_ferma=new char[strlen(denumire_fermaNou)+1];
			strcpy(this->denumire_ferma,denumire_fermaNou);
		}
		else
			throw new exception("Denumire invalida!");
	}
	void setProduse(float *produseNou,int nr_luniNou)
	{
		if(this->produse!=NULL)
		{
			delete [] this->produse;
			this->nr_luni=nr_luniNou;
			this->produse=new float[nr_luniNou];
			for(int i=0;i<nr_luniNou;i++)
				this->produse[i]=produseNou[i];
		}
		else
			throw new exception("Vector produse invalid!");
	}
	//supraincarcare cast
	operator int()
	{
		return this->suprafata;
	}
	//supraincarcare +=
	Ferma operator+=(int s)
	{
		this->suprafata+=s;
		return *this;
	}
	Ferma operator+=(Ferma f)
	{
		this->suprafata+=f.suprafata;
		return *this;
	}
	//supraincarcare ++
	Ferma operator++(int)
	{
		Ferma aux=*this;
		this->suprafata+=10;
		return aux;
	}
	Ferma operator--()
	{
		this->suprafata-=10;
		return *this;
	}
	bool operator<=(Ferma f)
	{
		if(this->suprafata<=f.suprafata)
			return true;
		else
			return false;
	}

};
int Ferma::nr_ferme=0;
ostream &operator<<(ostream &out, Ferma &f)
{
	cout<<"Id ferma: "<<f.id_ferma<<endl;
	cout<<"Denumire ferma: "<<f.denumire_ferma<<endl;
	cout<<"Suprafata: "<<f.suprafata<<endl;
	cout<<"Nr. luni: "<<f.nr_luni<<endl;
	cout<<"Produse: ";
	for(int i=0;i<f.nr_luni;i++)
		out<<f.produse[i]<<" ";
	return out;
}
istream &operator>>(istream &in, Ferma &f)
{
	cout<<endl<<"Dati denumire ferma:";
	char aux[50];
	in>>aux;
	delete [] f.denumire_ferma;
	f.denumire_ferma=new char[strlen(aux)+1];
	strcpy(f.denumire_ferma,aux);
	cout<<endl<<"Dati suprafata:";
	in>>f.suprafata;
	cout<<endl<<"dati nr luni:";
	in>>f.nr_luni;
	cout<<endl<<"Dati produse:";
	delete [] f.produse;
	f.produse=new float[f.nr_luni];
	for(int i=0;i<f.nr_luni;i++)
	in>>f.produse[i];
	return in;
}
void main()
{
	float *x=new float[3];
	x[0]=15;
	x[1]=20;
	x[2]=25;
	Ferma f1("Ferma00",100,3,x);
	float *y=new float[4];
	y[0]=55;
	y[1]=56;
	y[2]=57;
	y[3]=58;
	f1.setDenumire_ferma("Ferma01");
	f1.setProduse(y,4);
	cout<<f1.getId_ferma()<<endl;
	cout<<f1.getDenumire_ferma()<<endl;
	cout<<f1.getSuprafata()<<endl;
	cout<<f1.getNr_luni()<<endl;
	for(int i=0;i<f1.getNr_luni();i++)
		cout<<f1.getProduse()[i]<<" ";
	cout<<endl;

	Ferma f2=f1;
	cout<<f2<<endl;

	Ferma f3;
	f3=f1;
	cout<<f3<<endl;

	Ferma f4;
	cin>>f4;
	cout<<f4<<endl;

	int f=f1;
	cout<<f<<endl;

	Ferma f5("Ferma05",120,0, NULL);
	f5++;
	cout<<f5<<endl;
	--f5;
	cout<<f5<<endl;

	Ferma f6("Ferma06",125,0, NULL);
	f6+=12;
	cout<<f6.getSuprafata()<<endl;

	Ferma f7("Ferma07",130,0, NULL);
	f7+=f6;
	cout<<f7.getSuprafata()<<endl;

	cout<<"Nr ferme:"<<Ferma::getNr_ferme()<<endl;

	if(f6<=f7)
		cout<<"Ferma f7 are o suprafata mai mare decat ferma f6";
	else
		cout<<"Ferma f6 are o suprafata mai mare decat ferma f7";
}
