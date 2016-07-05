#include<iostream>
using namespace std;
class Avion{
private:
	const int id;
	static int nr_avioane;
	char* nume;
	int seria;
	int nr_zile;
	int *combustibil;
public:
	Avion():id(Avion::nr_avioane)
	{
		this->nume=new char[strlen("Anonim")+1];
		strcpy(this->nume, "Anonim");
		this->seria=0;
		this->nr_zile=0;
		this->combustibil=new int[nr_zile];
		for(int i=0;i<nr_zile;i++)
			this->combustibil[i]=0;
		Avion::nr_avioane++;
	}
	Avion(char* nume, int seria):id(Avion::nr_avioane)
	{
		this->nume=new char[strlen(nume)+1];
		strcpy(this->nume, nume);
		this->seria=seria;
		this->nr_zile=0;
		this->combustibil=new int[nr_zile];
		for(int i=0;i<nr_zile;i++)
			this->combustibil[i]=0;
		Avion::nr_avioane++;
	}
	~Avion()
	{
		if(this->nume!=NULL)
			delete [] this->nume;
		if(this->combustibil!=NULL)
			delete [] this->combustibil;
		Avion::nr_avioane--;
	}
	Avion(Avion &a):id(Avion::nr_avioane)
	{
		this->nume=new char[strlen(a.nume)+1];
		strcpy(this->nume,a.nume);
		this->seria=a.seria;
		this->nr_zile=a.nr_zile;
		this->combustibil=new int[a.nr_zile];
		for(int i=0;i<a.nr_zile;i++)
			this->combustibil[i]=a.combustibil[i];
		Avion::nr_avioane++;
	}
	Avion operator=(Avion a)
	{
		if(this->nume!=NULL)
			delete [] this->nume;
		if(this->combustibil!=NULL)
			delete [] this->combustibil;
		this->nume=new char[strlen(a.nume)+1];
		strcpy(this->nume,a.nume);
		this->seria=a.seria;
		this->nr_zile=a.nr_zile;
		this->combustibil=new int[a.nr_zile];
		for(int i=0;i<a.nr_zile;i++)
			this->combustibil[i]=a.combustibil[i];
		return *this;
	}
	int getSeria()
	{
		return this->seria;
	}
	friend ostream &operator<<(ostream &out,Avion &a);
	friend istream &operator>>(istream &in, Avion &a);
	Avion operator++()
	{
		this->seria++;
		return *this;
	}
	Avion operator++(int)
	{
		Avion aux=*this;
		this->seria++;
		return aux;
	}
	operator int()
	{
		return this->seria;
	}
	int &operator[](int index)
	{
		static int err;
		if(index>=0 && index<nr_zile)
			return combustibil[index];
		else
			return err;
	}
	Avion operator!()
	{
	    this->seria*=-1;
		return *this;
	}
	int operator+(int val)
	{   
		return this->seria+val;
	}
	int operator+(Avion a)
	{
		return this->seria+a.seria;
	}
	Avion operator*=(int val)
	{
		this->seria*=val;
		return *this;
	}
	Avion operator+=(Avion a)
	{
		this->seria+=a.seria;
		return *this;
	}
	friend void operator+=(int &val,Avion a);
};
int Avion::nr_avioane=0;
ostream &operator<<(ostream &out,Avion &a)
{
	out<<"Id: "<<a.id<<endl;
	out<<"Nume: "<<a.nume<<endl;
	out<<"Seria: "<<a.seria<<endl;
	out<<"Nr zile: "<<a.nr_zile<<endl;
	out<<"Combustibil: ";
	for(int i=0;i<a.nr_zile;i++)
		out<<a.combustibil[i]<<" ";
	return out;
}
istream &operator>>(istream &in,Avion &a)
{
	cout<<"dati  nume:";
	char aux[100];
	in>>aux;
	if(a.nume!=NULL)
		delete [] a.nume;
	a.nume=new char[strlen(aux)+1];
	strcpy(a.nume,aux);
	cout<<"dati seria:";
	in>>a.seria;
	cout<<"dati nr_zile:";
	in>>a.nr_zile;
	cout<<"dati combustibil:";
	if(a.combustibil!=NULL)
		delete [] a.combustibil;
	a.combustibil=new int[a.nr_zile];
	for(int i=0;i<a.nr_zile;i++)
		in>>a.combustibil[i];
	return in;
}
void operator+=(int &val,Avion a)
{
	val-=a.seria;
}
void main()
{
	
	Avion a1("Avion01",100);
	cout<<a1<<endl;

    Avion a2;
	cout<<a2<<endl;
	
	Avion a3=a1;
	cout<<a3<<endl;

	Avion a4;
	a4=a1;
	cout<<a4<<endl;

	Avion a5;
	cin>>a5;
	cout<<a5<<endl;

	Avion a6;
	a6=++a5;
	cout<<a6.getSeria()<<endl;

	Avion a7;
	a7=a5++;
	cout<<a7.getSeria()<<endl;

	int t=a5;
	cout<<t<<endl;

	a2=!a5;
	cout<<a2<<endl;

	cout<<a5[2]<<endl;

	Avion a8("Avion08", 108);
	cout<<a8+10<<endl;
	cout<<a1+a8<<endl;

	Avion a9("Avion09", 109);
	a9*=2;
	cout<<a9.getSeria()<<endl;

	Avion a10;
	a10+=a9;
	cout<<a10.getSeria()<<endl;
}