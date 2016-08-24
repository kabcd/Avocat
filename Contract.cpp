#include<iostream>
#include<fstream>
#include<list>
using namespace std;
class Contract{
protected:
	const int nrContract;
	int an;
	char beneficiar[100];
	char furnizor[100];
	float valoare;
public:
	Contract():nrContract(0)
	{
		this->an=2016;
		strcpy(this->beneficiar,"Anonim");
		strcpy(this->furnizor,"Anonim");
		this->valoare=0;
	}
	Contract(const int NRCONTRACT, int an, char* beneficiar, char* furnizor,float valoare):nrContract(NRCONTRACT)
	{
		this->an=an;
		strcpy(this->beneficiar,beneficiar);
		strcpy(this->furnizor,furnizor);
		this->valoare=valoare;
	}
	Contract(const Contract &c):nrContract(c.nrContract)
	{
		this->an=c.an;
		strcpy(this->beneficiar,c.beneficiar);
		strcpy(this->furnizor,c.furnizor);
		this->valoare=c.valoare;
	}
	Contract operator=(Contract c)
	{
		this->an=c.an;
		strcpy(this->beneficiar,c.beneficiar);
		strcpy(this->furnizor,c.furnizor);
		this->valoare=c.valoare;
		return *this;
	}
	~Contract(){}
	const int get_nrContract()
	{
		return this->nrContract;
	}
	float get_valoare()
	{
		return this->valoare;
	}
	char* get_beneficiar()
	{
		return this->beneficiar;
	}
	friend ostream &operator<<( ostream& out, Contract &c);
	Contract operator++(int)
	{
		Contract aux=*this;
		this->valoare=this->valoare+100;
		return aux;
	}
	bool operator<(Contract c)
	{
		if(this->an<c.an)
			return true;
		else
			return false;
	}
	void salveazaFisier(char *numeFisier)
	{
		ofstream fisier;
		fisier.open(numeFisier,ofstream::out | ofstream::binary |ofstream::trunc);
		if (fisier.is_open())
		{
			fisier.write((char*)&this->nrContract, sizeof(int));
			fisier.write((char*)&this->an, sizeof(int));
			
			int nrCaractereBeneficiar = strlen(this->beneficiar) + 1;
			fisier.write((char*)&nrCaractereBeneficiar, sizeof(int));
			fisier.write(this->beneficiar, nrCaractereBeneficiar);
			
			int nrCaractereFurnizor = strlen(this->furnizor) + 1;
			fisier.write((char*)&nrCaractereFurnizor, sizeof(int));
			fisier.write(this->furnizor, nrCaractereFurnizor);
			
			fisier.write((char*)&this->valoare, sizeof(float));
		}
		fisier.close();
	}
	void citesteFisier(char *numeFisier)
	{
		ifstream fisier;
		fisier.open(numeFisier,ifstream::in | ifstream::binary);
		if(fisier.is_open())
		{
			fisier.read((char*)&this->nrContract,sizeof(int));
			fisier.read((char*)&this->an, sizeof(int));
			
			int nrCaractereBeneficiar;
			fisier.read((char*)&nrCaractereBeneficiar,sizeof(int));
			fisier.read(this->beneficiar,nrCaractereBeneficiar*sizeof(char));
			
			int nrCaractereFurnizor;
			fisier.read((char*)&nrCaractereFurnizor,sizeof(int));
			fisier.read(this->furnizor,nrCaractereFurnizor*sizeof(char));
			
			fisier.read((char*)&this->valoare, sizeof(float));	
		}
	}
};
ostream &operator<<( ostream& out, Contract &c)
{
	out<<"Nr contract:"<<c.nrContract<<endl;
	out<<"An:"<<c.an<<endl;
	out<<"Beneficiar:"<<c.beneficiar<<endl;
	out<<"Furnizor:"<<c.furnizor<<endl;
	out<<"Valoare:"<<c.valoare<<endl;
	return out;
}
class ContractInchiriere:public Contract{
protected:
	int perioada;
public:
	ContractInchiriere():Contract()
	{
		this->perioada=0;
	}
	ContractInchiriere(const int nrContract, int an, char* beneficiar, char* furnizor, float valoare, int perioada)
		:Contract(nrContract, an, beneficiar, furnizor,valoare)
	{
		this->perioada=perioada;
	}
	~ContractInchiriere(){}
	float get_tva()
	{
		return this->valoare*0.24;
	}
};
template<class T> class Dosar{
private:
	T *vector;
	int n;
public:
	Dosar(int n)
	{
		this->n=n;
		this->vector=new T[n];
	}
	~Dosar()
	{
		if(this->vector!=NULL)
			delete [] this->vector;
	}
	void setVector(int i, T valoare)
	{
		 vector[i] = valoare;
	} 
	float get_valoareDosar()
	{
		float s=0;
		for (int i=0;i<n;i++)
			s=s+vector[i].get_valoare();
		return s;
	}
};
void main()
{
	Contract c1;
	Contract c2(12,2014,"Popescu Ion","Ionescu Vasile",32000);
	c1=c2;
	cout<<"Contractul "<<c2.get_nrContract()<<" are valoarea de "<<c2.get_valoare()<<endl;
	
	c1=c2++;//se incrementeaza valoarea contractului c2 cu 100
	cout<<c1<<endl;
	cout<<c2<<endl;

	c1.salveazaFisier("contract.dat");
	Contract c3;
	c3.citesteFisier("contract.dat");
	cout<<c3<<endl;

	ContractInchiriere ci1(13,2015,"Chirias01","Vanzator01",300,24);
	cout<<ci1.get_beneficiar()<<endl;
	cout<<ci1.get_tva()<<endl;
	
	ContractInchiriere ci2(14,2015,"Chirias02","Vanzator02",600,36);
	ContractInchiriere ci3(15,2015,"Chirias03","Vanzator03",900,12);

	Dosar<ContractInchiriere> contracteInchiriere(3);//se instantiaza un dosar cu 3 contracte de inchiriere
	contracteInchiriere.setVector(0, ci1);
	contracteInchiriere.setVector(1, ci2);
	contracteInchiriere.setVector(2, ci3);
	cout<<"Valoarea tuturor contractelor: "<<contracteInchiriere.get_valoareDosar()<<endl;

	//se adauga toate contractele intr-o structura STL de tip lista si se afiseaza lista sortata crescator dupa anul semnarii contractului folosind un iterator 
	list<Contract> contracte;
	contracte.push_back(c1);
	contracte.push_back(c2);
	contracte.push_back(ci1);
	list<Contract>::iterator it;
	contracte.sort();
	for(it=contracte.begin(); it!=contracte.end();it++)
		cout<<*it<<endl;
}
	
