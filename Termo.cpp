#include<iostream>
using namespace std;
#include<fstream>
#include<map>
#include<string>
#define NMAX 12
class Termo{
protected:
	char* eticheta;
	float temperatura_citita;
	float temperatura_dorita;
public:
	Termo()
	{
		this->eticheta=new char[strlen("Anonim")+1];
		strcpy(this->eticheta,"Anonim");
		this->temperatura_citita=0;
		this->temperatura_dorita=0;
	}
	Termo(char* eticheta, float temperatura_citita, float temperatura_dorita)
	{
		this->eticheta=new char[strlen(eticheta)+1];
		strcpy(this->eticheta,eticheta);
		this->temperatura_citita=temperatura_citita;
		this->temperatura_dorita=temperatura_dorita;
	}
	~Termo()
	{
		if(this->eticheta!=NULL)
			delete [] this->eticheta;
	}
	Termo(Termo &t)
	{
		this->eticheta=new char[strlen(t.eticheta)+1];
		strcpy(this->eticheta,t.eticheta);
		this->temperatura_citita=t.temperatura_citita;
		this->temperatura_dorita=t.temperatura_dorita;
	}
	Termo operator=(Termo t)
	{
		if(this->eticheta!=NULL)
			delete [] this->eticheta;
		this->eticheta=new char[strlen(t.eticheta)+1];
		strcpy(this->eticheta,t.eticheta);
		this->temperatura_citita=t.temperatura_citita;
		this->temperatura_dorita=t.temperatura_dorita;
		return *this;
	}
	float getTemperatura_citita()
	{
		return this->temperatura_citita;
	}
	float getTemperatura_dorita()
	{
		return this->temperatura_dorita;
	}
	char* getEticheta()
	{
		return this->eticheta;
	}
	void setEticheta(char* etichetaNou)
	{
		if(etichetaNou==NULL)
			throw new exception("eticheta invalida");
		else
		{
			if(this->eticheta!=NULL)
				delete [] this->eticheta;
			this->eticheta=new char[strlen(etichetaNou)+1];
			strcpy(this->eticheta,etichetaNou);
		}
	}
	virtual float tempMedieCitita()
	{
		return this->temperatura_citita;
	}
	friend ostream &operator<<(ostream &out, Termo &t);
	friend istream &operator>>(istream &in, Termo &t);
	Termo operator--()
	{
		this->temperatura_dorita--;
		return *this;
	}
	friend ofstream &operator<<(ofstream &out, Termo &t);
	friend ifstream &operator>>(ifstream &in, Termo &t);
};
ostream &operator<<(ostream &out, Termo &t)
{
	out<<t.getEticheta()<<" "<< t.getTemperatura_citita()<<" "<<t.getTemperatura_dorita()<<endl;
	return out;
}
istream &operator>>(istream &in, Termo &t)
{
	cout<<"Dati eticheta:";
	char aux[50];
	in>>aux;
	if(t.eticheta!=NULL)
		delete [] t.eticheta;
	t.eticheta=new char[strlen(aux)+1];
	strcpy(t.eticheta,aux);
	cout<<"Dati temperatura citita:";
	in>>t.temperatura_citita;
	cout<<"Dati temperatura dorita:";
	in>>t.temperatura_dorita;
	return in;
}
ifstream &operator>>(ifstream &in, Termo &t)
{
	char aux[50];
	in>>aux;
	if(t.eticheta!=NULL)
		delete [] t.eticheta;
	t.eticheta=new char[strlen(aux)+1];
	strcpy(t.eticheta,aux);
	in>>t.temperatura_citita;
	in>>t.temperatura_dorita;
	return in;
}
ofstream &operator<<(ofstream &out, Termo &t)
{
	out<<t.getEticheta()<<endl;
	out<<t.getTemperatura_citita()<<endl;
	out<<t.getTemperatura_dorita()<<endl;
	return out;
}
class BiTermo:public Termo{
private:
	float temperatura_pardoseala_citita;
public:
	BiTermo():Termo()
	{
		this->temperatura_pardoseala_citita=0;
	}
	BiTermo(char* eticheta, float temperatura_citita, float temperatura_dorita, float temperatura_pardoseala_citita)
		:Termo(eticheta,temperatura_citita, temperatura_dorita)
	{
		this->temperatura_pardoseala_citita=temperatura_pardoseala_citita;
	}
	BiTermo(Termo &t):Termo(t)
	{
		this->temperatura_pardoseala_citita=0;
	}
	~BiTermo(){}
	float tempMedieCitita()
	{
		return (this->getTemperatura_citita()+this->getTemperatura_dorita())/2;
	}
	float getTemperatura_pardoseala_citita()
	{
		return this->temperatura_pardoseala_citita;
	}
	friend ostream &operator<<(ostream &out, BiTermo &bt);
	friend ifstream &operator>>(ifstream &in, BiTermo &bt);
};
ostream &operator<<(ostream &out, BiTermo &bt)
{
	out<< bt.getTemperatura_citita()<<" "<<bt.getTemperatura_dorita()<<" "<<bt.getTemperatura_pardoseala_citita()<<endl;
	return out;
}
ofstream &operator<<(ofstream &out, BiTermo &bt)
{
	out<<bt.getEticheta()<<endl;
	out<<bt.getTemperatura_citita()<<endl;
	out<<bt.getTemperatura_dorita()<<endl;
	out<<bt.getTemperatura_pardoseala_citita()<<endl;
	return out;
}
ifstream &operator>>(ifstream &in, BiTermo &bt)
{
	char aux[50];
	in>>aux;
	if(bt.eticheta!=NULL)
		delete [] bt.eticheta;
	bt.eticheta=new char[strlen(aux)+1];
	strcpy(bt.eticheta,aux);
	in>>bt.temperatura_citita;
	in>>bt.temperatura_dorita;
	in>>bt.temperatura_pardoseala_citita;
	return in;
}
class UCC{
private:
	char* locatie;
	int nr_termostate;
	Termo *termostate;
public:
	UCC()
	{
		this->locatie=new char[strlen("Anonim")+1];
		strcpy(this->locatie,"Anonim");
		this->nr_termostate=0;
		this->termostate=NULL;
	}
	UCC(char* locatie, int nr_termostate, Termo *termostate)
	{
		this->locatie=new char[strlen(locatie)+1];
		strcpy(this->locatie,locatie);
		this->nr_termostate=nr_termostate;
		this->termostate=new Termo[this->nr_termostate];
		for(int i=0;i<this->nr_termostate;i++)
			this->termostate[i]=termostate[i];
	}
	~UCC()
	{
		if(this->locatie!=NULL)
			delete [] this->locatie;
		if(this->termostate!=NULL)
			delete [] this->termostate;
	}
	UCC(const UCC &u)
	{
		this->locatie=new char[strlen(u.locatie)+1];
		strcpy(this->locatie,u.locatie);
		this->nr_termostate=u.nr_termostate;
		this->termostate=new Termo[u.nr_termostate];
		for(int i=0;i<this->nr_termostate;i++)
			this->termostate[i]=u.termostate[i];
	}
	UCC operator=(UCC u)
	{
		if(this->locatie!=NULL)
			delete [] this->locatie;
		this->locatie=new char[strlen(u.locatie)+1];
		strcpy(this->locatie,u.locatie);
		this->nr_termostate=u.nr_termostate;
		if(this->termostate!=NULL)
			delete [] this->termostate;
		this->termostate=new Termo[u.nr_termostate];
		for(int i=0;i<this->nr_termostate;i++)
			this->termostate[i]=u.termostate[i];
		return *this;
	}
	friend ostream &operator<<(ostream &out, UCC &u);
	friend istream &operator>>(istream &in, UCC &u);
	char* getLocatie()
	{
		return this->locatie;
	}
	int getNr_termostate()
	{
		return this->nr_termostate;
	}
	Termo* getTermostate()
	{
		return this->termostate;
	}
	UCC operator+=(int valoare)
	{
		Termo t;
		Termo *v=new Termo[this->nr_termostate+valoare];
		for(int i=0;i<this->nr_termostate;i++)
			v[i]=this->termostate[i];
		for(int i=this->nr_termostate;i<this->nr_termostate+valoare;i++)
			v[i]=t;
		this->nr_termostate+=valoare;
		if(this->termostate!=NULL)
			delete [] this->termostate;
		this->termostate=new Termo[this->nr_termostate];
		for(int i=0;i<this->nr_termostate;i++)
			this->termostate[i]=v[i];
		return *this;
	}
	friend ofstream &operator<<(ofstream &out, UCC &u);
	friend ifstream &operator>>(ifstream &in, UCC &u);
};
ofstream &operator<<(ofstream &out, UCC &u)
{
	out<<u.locatie<<endl;
	out<<u.nr_termostate<<endl;
	for(int i=0;i<u.nr_termostate;i++)
		out<<u.termostate[i]<<endl;
	return out;
}
ifstream &operator>>(ifstream &in, UCC &u)
{
	char aux[50];
	in.getline(aux,50);
	if(u.locatie!=NULL)
		delete [] u.locatie;
	u.locatie=new char[strlen(aux)+1];
	strcpy(u.locatie,aux);
	in>>u.nr_termostate;
	if(u.termostate!=NULL)
		delete [] u.termostate;
	u.termostate=new Termo[u.nr_termostate];
	for(int i=0;i<u.nr_termostate;i++)
		in>>u.termostate[i];
	return in;
}
ostream &operator<<(ostream &out, UCC &u)
{
	out<<u.locatie<<endl;
	out<<u.nr_termostate<<endl;
	out<<"Termostate:"<<endl;
	for(int i=0;i<u.nr_termostate;i++)
		out<<u.termostate[i]<<" ";
	return out;
}
istream &operator>>(istream &in, UCC &u)
{
	in.ignore(256,'\n');
	cout<<"Dati locatie:";
	char aux[50];
	in.getline(aux, 50);
	if(u.locatie!=NULL)
		delete [] u.locatie;
	u.locatie=new char[strlen(aux)+1];
	strcpy(u.locatie,aux);
	cout<<"Dati numar termostate:";
	in>>u.nr_termostate;
	cout<<"Dati termostate:";
	if(u.termostate!=NULL)
		delete [] u.termostate;
	u.termostate=new Termo[u.nr_termostate];
	for(int i=0;i<u.nr_termostate;i++)
		in>>u.termostate[i];
	return in;
}
void main()
{
	Termo t1("dormitor",22.5,23.5);
	Termo t2=t1;
	Termo t3; t3=t1;
	t3.setEticheta("bucatarie");
	cout<<t1<<endl<<t2<<endl<<t3<<endl;
	
	Termo t4;
	cin>>t4;
	cout<<t4<<endl;

	Termo tm1[]={t1,t2,t3,t4};
	UCC u1("etaj 1",4,tm1);
	Termo tm2[]={t1,t2, t4};
	UCC u2("etaj 2",3,tm2);

	UCC u3(u2);
	UCC u4; u4=u1;
	cin>>u4;
	cout<<u1<<endl<<u2<<endl<<u3<<endl<<u4<<endl;
	
	--t1;//se diminueaza cu 1 grad temperatura dorita
	cout<<t1<<endl;

	u2+=2;//se adauga 2 termostate la unitatea de comanda-control u2
	cout<<u2<<endl;

	ofstream fisierOut("ucc.txt");
	fisierOut<<u1;//se scrie in fisier unitatea de comanda-control u1
	fisierOut.close();
	ifstream fisierIn("ucc.txt");
	UCC u5;
	fisierIn>>u5;
	fisierIn.close();
	cout<<u5<<endl;
	
	Termo* pt=&t1;
	cout<<pt->tempMedieCitita()<<endl;
	
	BiTermo t5=t3;
	pt=&t5;
	cout<<t3<<endl;
	cout<<pt->tempMedieCitita()<<endl;

	map<string, BiTermo> btMap;//cheia este eticheta termostatului bivalent
	typedef pair<string, BiTermo> element;
	ifstream fisIn("biTermo.txt", ios::in);
	BiTermo bt;
	while(!fisIn.eof())
	{
		fisIn>>bt;//se citesc din fisier datele despre un termostat bivalent
		if(!fisIn)
			break;
		btMap.insert(element(bt.getEticheta(), bt));
	}
	fisIn.close();
	for(map<string, BiTermo>::iterator it=btMap.begin(); it!=btMap.end(); ++it)
	{
		cout << (*it).first << ": " << (*it).second.tempMedieCitita()<< endl;
	}
}
