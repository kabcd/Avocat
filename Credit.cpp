#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;
class Credit{
protected:
	char banca[100];
	char platitor[100];
	float valoareCredit;
	int rataLunara;
	int perioada;
public:
	Credit()
	{
		strcpy(this->banca,"Anonim");
		strcpy(this->platitor,"Anonim");
		this->valoareCredit=0;
		this->rataLunara=0;
		this->perioada=0;
	}
	Credit(char* banca, char* platitor, float valoareCredit, int rataLunara, int perioada)
	{
		strcpy(this->banca,banca);
		strcpy(this->platitor,platitor);
		this->valoareCredit=valoareCredit;
		this->rataLunara=rataLunara;
		this->perioada=perioada;
	}
	Credit operator=(Credit c)
	{
		strcpy(this->banca,c.banca);
		strcpy(this->platitor,c.platitor);
		this->valoareCredit=c.valoareCredit;
		this->rataLunara=c.rataLunara;
		this->perioada=c.perioada;
		return *this;
	}
	~Credit(){}
	friend ostream &operator<<(ostream &out, Credit &c);
	char* get_platitor()
	{
		return this->platitor;
	}
	char *get_banca()
	{
		return this->banca;
	}
	float get_valoareCredit()
	{
		return this->valoareCredit;
	}
	virtual float valoareBun()
	{
		cout<<"Apel din clasa Credit"<<endl;
		return this->valoareCredit;
	}
	operator float()
	{
		return this->valoareCredit;
	}
	friend void operator+=(float &valoare, Credit c);
	Credit operator+=(Credit c)
	{
		if(strcmp(this->platitor,c.platitor)==0)
			this->valoareCredit+=c.valoareCredit;
		return *this;
	}
	bool operator<(Credit c)
	{
		if(this->valoareCredit<c.valoareCredit)
			return true;
		else
			return false;
	}
};
ostream &operator<<(ostream &out, Credit &c)
{
	out<<"Banca: "<<c.banca<<endl;
	out<<"Platitor: "<<c.platitor<<endl;
	out<<"Valoare credit: "<<c.valoareCredit<<endl;
	out<<"Rata lunara: "<<c.rataLunara<<endl;
	out<<"Perioada: "<<c.perioada<<endl;
	return out;
	}
void operator+=(float &valoare, Credit c)
{
	valoare+=c.rataLunara;
}
class CreditIpotecar:public Credit{
protected:
	float valoareIpoteca;
public:
	CreditIpotecar():Credit()
	{
		this->valoareIpoteca=0;
	}
	CreditIpotecar(char* banca, char* platitor, float valoareCredit, int rataLunara, int perioada, float valoareIpoteca)
		:Credit(banca,platitor,valoareCredit,rataLunara,perioada)
	{
		this->valoareIpoteca=valoareIpoteca;
	}
	~CreditIpotecar(){}
	float valoareBun()
	{
		cout<<"Apel din clasa CreditIpotecar"<<endl;
		return this->valoareIpoteca;
	}
};
void main()
{
	Credit c1;
	Credit c2("BCR","Popescu Ion",3000,110,36);
	c1=c2;
	cout<<c2.get_platitor()<<" are un credit in valoare de "<<c2.get_valoareCredit()<<endl;
	
	cout<<c1<<endl;
	c1+=c2;//aduna valoarea creditului c2 la valoarea creditului c1, daca platitorul este acelasi; in caz contrar adunarea nu se realizeaza
	cout<<c1<<endl;

	float valoareCredit;
	valoareCredit=c2;//cast-ul returneaza valoarea creditului
	cout<<valoareCredit<<endl;
	
	float datorie=30;
	datorie+=c2;//aduna la datorie rata lunara a creditului c2
	cout<<datorie<<endl;
	
	CreditIpotecar ci1("BRD","Popescu Ion",100000,400,360,110000);
	cout<<ci1.get_banca()<<endl;

	Credit c3;
	Credit *pc1;
	pc1=&ci1;
	cout<<c3.valoareBun()<<endl;
	cout<<ci1.valoareBun()<<endl;
	cout<<pc1->valoareBun()<<endl;

	//se adauga toate creditele intr-o structura STL de tip vector si se afiseaza vectorul sortat crescator dupa valoarea creditului folosind un iterator 
	vector<Credit> credite;
	credite.push_back(c1);
	credite.push_back(c2);
	credite.push_back(c3);
	sort(credite.begin(), credite.end());
	vector<Credit>::iterator it;
	for(it=credite.begin(); it!=credite.end();it++)
		cout<<*it<<endl;
}
