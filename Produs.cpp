#include<iostream>
using namespace std;
class Produs{
private:
	const int cod;
	static int nr_produse;
	char* nume;
	float pret;
	int nr_zile;
	float *cantitate;
public:
	Produs():cod(0)
	{
		this->nume=new char[strlen("Anonim")+1];
		strcpy(this->nume,"Anonim");
		this->pret=0;
		this->nr_zile=0;
		this->cantitate=NULL;
		Produs::nr_produse++;
	}
	Produs(const int COD,char *nume,float pret,int nr_zile,float *cantitate):cod(COD)
	{
		this->nume=new char[strlen(nume)+1];
		strcpy(this->nume,nume);
		this->pret=pret;
		this->nr_zile=nr_zile;
		this->cantitate=new float[nr_zile];
		for(int i=0;i<nr_zile;i++)
			this->cantitate[i]=cantitate[i];
		Produs::nr_produse++;
	}
	~Produs()
	{
		if(this->nume!=NULL)
			delete [] this->nume;
		if(this->cantitate!=NULL)
			delete [] this->cantitate;
	}
	Produs(Produs &p):cod(p.cod)
	{
		this->nume=new char[strlen(p.nume)+1];
		strcpy(this->nume,p.nume);
		this->pret=p.pret;
		this->nr_zile=p.nr_zile;
		this->cantitate=new float[p.nr_zile];
		for(int i=0;i<p.nr_zile;i++)
			this->cantitate[i]=p.cantitate[i];
		Produs::nr_produse++;
	}
	Produs operator=(Produs p)
	{
		this->nume=new char[strlen(p.nume)+1];
		strcpy(this->nume,p.nume);
		this->pret=p.pret;
		this->nr_zile=p.nr_zile;
		this->cantitate=new float[p.nr_zile];
		for(int i=0;i<p.nr_zile;i++)
			this->cantitate[i]=p.cantitate[i];
		return *this;
	}
	char* getNume()
	{
		return this->nume;
	}
	float getPret()
	{
		return this->pret;
	}
	int getNr_zile()
	{
		return this->nr_zile;
	}
	float *getCantitate()
	{
		return this->cantitate;
	}
	static int getNr_Produse()
	{
		return Produs::nr_produse;
	}
	const int getCod()
	{
		return this->cod;
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
			throw new exception("Nume invalid!");
	}
	void setCantitate(float *cantitateNou, int nr_zileNou)
	{
		if(this->cantitate!=NULL)
		{
			delete [] this->cantitate;
			this->nr_zile=nr_zileNou;
			this->cantitate=new float[nr_zileNou];
			for(int i=0;i<nr_zileNou;i++)
				this->cantitate[i]=cantitateNou[i];
		}
		else
			throw new exception("Vector cantitate invalid!");
	}
	void setPret(float pretNou)
	{
		if(this->pret>0)
			this->pret=pretNou;
		else
			throw new exception("Pret invalid!");
	}
	friend ostream &operator<<(ostream &out,Produs &p);
	friend istream &operator>>(istream &in, Produs &p);
	operator float()
	{
		return this->pret;
	}
	Produs operator--()
	{
		this->pret-=2.5;
		return *this;
	}
	Produs operator++(int)
	{
		Produs aux=*this;
	    this->pret+=2.5;
		return aux;
	}
	Produs operator-=(Produs p)
	{
		this->pret-=p.pret;
		return *this;
	}
	Produs operator*=(float x)
	{
		this->pret*=x;
		return *this;
	}
	bool operator==(Produs p)
	{
		if(this->pret!=p.pret)
			return true;
		else
			return false;
	}
	float &operator[](int index)
	{
		static float err;
		if(index>=0 && index<this->nr_zile)
			return this->cantitate[index];
		else
			return err;
	}
	Produs operator+(Produs p)
	{
		Produs aux=*this;
		aux.pret=this->pret+p.pret;
		return aux;
	}
	float operator+(float t)
	{
		return t + this->pret;
	}
    friend float operator+(float t, Produs p);
    Produs operator+=(float t)
	{
		float *v=new float[this->nr_zile+1];
		for(int i=0;i<this->nr_zile;i++)
			v[i]=this->cantitate[i];
		v[this->nr_zile]=t;
		this->nr_zile++;
		delete []this->cantitate;
		this->cantitate=new float[this->nr_zile];
		for(int i=0;i<this->nr_zile;i++)
			this->cantitate[i]=v[i];
		return *this;
	}
    Produs operator-=(float t)
	{
		float *v=new float[this->nr_zile-1];
		for(int i=0;i<t;i++)
			v[i]=cantitate[i];
		for(int i=t;i<this->nr_zile;i++)
			v[i]=this->cantitate[i+1];

		this->nr_zile--;
		delete []this->cantitate;
		this->cantitate=new float[this->nr_zile];
		for(int i=0;i<this->nr_zile;i++)
			this->cantitate[i]=v[i];
		return *this;
	}
};
int Produs::nr_produse=0;
float operator+(float t, Produs p)
{
	return t + p.pret;
}
ostream &operator<<(ostream &out,Produs &p)
{
	cout<<"Cod bar: "<<p.cod<<endl;
	cout<<"Nume produs: "<<p.nume<<endl;
	cout<<"Pret: "<<p.pret<<endl;
	cout<<"Nr zile: "<<p.nr_zile<<endl;
	cout<<"Produse: ";
	for(int i=0;i<p.nr_zile;i++)
		out<<p.cantitate[i]<<" ";
	return out;
}
istream &operator>>(istream &in, Produs &p)
{
	cout<<endl<<"Dati nume produs:";
	char aux[50];
	in>>aux;
	delete [] p.nume;
	p.nume=new char[strlen(aux)+1];
	strcpy(p.nume,aux);
	cout<<endl<<"Dati pret:";
	in>>p.pret;
	cout<<endl<<"Dati nr zile:";
	in>>p.nr_zile;
	cout<<endl<<"Dati produse:";
	delete [] p.cantitate;
	p.cantitate=new float[p.nr_zile];
	for(int i=0;i<p.nr_zile;i++)
		in>>p.cantitate[i];
	return in;
}
void main()
{
	float *x=new float[3];
	x[0]=88;
	x[1]=78;
	Produs p1(12,"Ardei",45,2,x);
	float *y=new float[3];
	y[0]=50;
	y[1]=55;
	y[2]=60;
	p1.setNume("Rosii");
	p1.setPret(30);
	p1.setCantitate(y,3);
	cout<<p1.getCod()<<endl;
	cout<<p1.getNume()<<endl;
	cout<<p1.getPret()<<endl;
	cout<<p1.getNr_zile()<<endl;
	for(int i=0;i<p1.getNr_zile();i++)
		cout<<p1.getCantitate()[i]<<" ";
	cout<<endl;

	cout<<p1[1]<<endl;
	p1[1]=100;
	cout<<p1[1]<<endl;

	Produs p2=p1;
	cout<<p2<<endl;

	Produs p3;
	p3=p1;
	cout<<p3<<endl;

	Produs p4;
	cin>>p4;
	cout<<p4<<endl;

	float pret=p4;
	cout<<pret<<endl;
		
	--p4;
	cout<<p4<<endl;
	p4++;
	cout<<p4<<endl;

	Produs p5;
	p5=p3+p4;
	cout<<p5<<endl;

	if(p4==p3)
		cout<<"Produsul p4 si p3 au acelasi pret"<<endl;
	else
		cout<<"Produsul p4 si p3 au preturi diferite"<<endl;

	p3*=0.25;
	cout<<p3.getPret()<<endl;

	p3-=p1;
	cout<<p3.getPret()<<endl;

	float nr=10;
	cout<<nr+p3<<" "<<p3+nr<<endl;

	p3+=15;
	cout<<p3<<endl;

	p3-=2;
	cout<<p3<<endl;
}