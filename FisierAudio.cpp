#include<iostream>
using namespace std;
class FisierAudio {
private:
	char* denumire;
	int durata;
public:
	const int id;
	static int nrFisiere;
	//constructor fara parametri
	FisierAudio():id(FisierAudio::nrFisiere)
	{
		this->denumire = new char[strlen("Necunoscut") + 1];
		strcpy(this->denumire, "Necunoscut");
		this->durata = 0;
		FisierAudio::nrFisiere++;
	}
	//constructor cu parametri
	FisierAudio(int durata, char* denumire):id(FisierAudio::nrFisiere)
	{
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->durata = durata;
		FisierAudio::nrFisiere++;
	}
	//destructor
	~FisierAudio()
	{
		if (this->denumire != NULL)
			delete [] this->denumire;
		FisierAudio::nrFisiere--;
	}
	char* getName()
	{
		return this->denumire;
	}
	void setName(char* denumireNou)
	{
		if (denumireNou!= NULL)
		{
			if(this->denumire!=NULL)
				delete [] this->denumire;
			this->denumire = new char[strlen(denumireNou) + 1];
			strcpy(this->denumire, denumireNou);
		}
		else
			throw new exception("Denumire invalida!");
	}
	int getDurata()
	{
		return this->durata;
	}
	//constructor de copiere
	FisierAudio(FisierAudio &f):id(FisierAudio::nrFisiere)
	{
		this->denumire = new char[strlen(f.denumire) + 1];
		strcpy(this->denumire,f.denumire);
		this->durata = f.durata;
		FisierAudio::nrFisiere++;
	}
	//supraincarcare =
	FisierAudio operator=(FisierAudio f)
	{
		if (this->denumire!= NULL)
			delete[] this->denumire;
		this->denumire = new char[strlen(f.denumire) + 1];
		strcpy(this->denumire, f.denumire);
		this->durata = f.durata;
		return *this;
	}
	//supraincarcare <<
	friend ostream &operator<<(ostream &out, FisierAudio &f);
	//supraincarcare ++ postfixat
	FisierAudio operator++(int)
	{
		FisierAudio aux = *this;
		this->durata++;
		return aux;
	}
	//supraincarcare cast
	operator int()
	{
		return this->durata;
	}
	//supraincarcare -  
	int operator-(FisierAudio f)
	{
		return this->durata - f.durata;
	}
	//supraincarcare >
        bool operator>(FisierAudio f)
	{
		 if (this->durata > f.durata)
			 return true;
		 else
			 return false;
	}
};
int FisierAudio::nrFisiere = 0;
ostream &operator<<(ostream &out, FisierAudio &f)
{
	out << f.id<<" - "<<f.denumire<<", "<<f.durata;
	return out;
}
void main()
{
	FisierAudio fa1;
	cout<<fa1.getName()<<endl;

	FisierAudio fa2(197, "Gangnam Style");
	cout << fa2.getDurata()<<endl;
	cout << fa2.id<<endl;

	cout << fa1 <<endl;
	cout << fa2 <<endl;
	FisierAudio fa3 = fa2;
	fa2.setName("Harlem Shake");
	cout << fa2.getName()<<endl;
	cout << fa3.getName()<<endl;
	
	FisierAudio fa4;
	fa4 = fa2;
	cout << fa4.getDurata()<<endl;

	cout << FisierAudio::nrFisiere<<endl;
	
	FisierAudio *pfa2 = new FisierAudio(275, "Queen - Show must go on");
	FisierAudio fa5 = (*pfa2)++;
	cout << pfa2->getDurata() << " " << fa5.getDurata()<<endl;
	delete pfa2;
	
	int durata = (int)fa5;
	cout<<durata<<endl;
	
	cout << fa2-fa5 << " "<<fa5-fa2<<endl;
	if (fa5 > fa2)
		cout << "fa5 are o durata mai mare"<<endl;
	else 
		cout << "fa2 are o durata mai mare"<<endl;
}
