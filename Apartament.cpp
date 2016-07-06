#include<iostream>
using namespace std;
#include<fstream>
#include<vector>
class Apartament{
private:
	const int an_constructie;
	char* localitate;
	int pret;
	int numar_camere;
	int *suprafara_camere;
public:
	Apartament():an_constructie(0)
	{
		this->localitate=new char[strlen("Anonim")+1];
		strcpy(this->localitate,"Anonim");
		this->pret=0;
		this->numar_camere=0;
		this->suprafara_camere=NULL;
	}
	Apartament(const int AN_CONSTRUCTIE, char* localitate, int pret, int numar_camere, int *suprafara_camere):an_constructie(AN_CONSTRUCTIE)
	{
		this->localitate=new char[strlen(localitate)+1];
		strcpy(this->localitate,localitate);
		this->pret=pret;
		this->numar_camere=numar_camere;
		this->suprafara_camere=new int[this->numar_camere];
		for(int i=0;i<this->numar_camere;i++)
			this->suprafara_camere[i]=suprafara_camere[i];
	}
	Apartament(const Apartament &a):an_constructie(a.an_constructie)
	{
		this->localitate=new char[strlen(a.localitate)+1];
		strcpy(this->localitate,a.localitate);
		this->pret=a.pret;
		this->numar_camere=a.numar_camere;
		this->suprafara_camere=new int[this->numar_camere];
		for(int i=0;i<this->numar_camere;i++)
			this->suprafara_camere[i]=a.suprafara_camere[i];
	}
	Apartament operator=(Apartament a)
	{
		if(this->localitate!=NULL)
			delete [] this->localitate;
		if(this->suprafara_camere!=NULL)
			delete [] this->suprafara_camere;
		this->localitate=new char[strlen(a.localitate)+1];
		strcpy(this->localitate,a.localitate);
		this->pret=a.pret;
		this->numar_camere=a.numar_camere;
		this->suprafara_camere=new int[this->numar_camere];
		for(int i=0;i<this->numar_camere;i++)
			this->suprafara_camere[i]=a.suprafara_camere[i];
		return *this;
	}
	~Apartament()
	{
		if(this->localitate!=NULL)
			delete [] this->localitate;
		if(this->suprafara_camere!=NULL)
			delete [] this->suprafara_camere;
	}
	const int getAnConstr()
	{
		return this->an_constructie;
	}
	char* getLocalitate()
	{
		return this->localitate;
	}
	int *getVectorSupr()
	{
		return this->suprafara_camere;
	}
	int getPret()
	{
		return this->pret;
	}
	int getNumarCamere()
	{
		return this->numar_camere;
	}
	void setLocalitate(char* localitateNou)
	{
		if(this->localitate!=NULL)
		{
			delete [] this->localitate;
			this->localitate=new char[strlen(localitateNou)+1];
			strcpy(this->localitate,localitateNou);
		}
		else
			throw new exception("Localitate invalida!");
	}
	void setVectorSupr(int *vectorSuprafeteNou, int nrCamereNou)
	{
		if(this->suprafara_camere!=NULL)
		{
			delete [] this->suprafara_camere;
			this->numar_camere=nrCamereNou;
			this->suprafara_camere=new int[nrCamereNou];
			for(int i=0;i<nrCamereNou;i++)
				this->suprafara_camere[i]=vectorSuprafeteNou[i];
		}
		else
			throw new exception("Vector suprafete invalid!");
	}
	friend ostream &operator<<(ostream &out, Apartament &a);
	int suprTotala()
	{
		int s=0;
		for(int i=0;i<this->numar_camere;i++)
		s=s+this->suprafara_camere[i];
		return s;
	}
	bool operator>(Apartament a)
	{
		if(this->pret>a.pret)
			return true;
		else
			return false;		
	}
	bool operator<(Apartament a)
	{
		if(this->pret<a.pret)
			return true;
		else
			return false;
	}
	Apartament operator++(int)
	{
		Apartament aux=*this;
		int *v;
		v=new int[this->numar_camere+1];
		for(int i=0;i<this->numar_camere;i++)
			v[i]=this->suprafara_camere[i];
		v[this->numar_camere]=0;
		
		delete [] this->suprafara_camere;
		this->numar_camere++;
		this->suprafara_camere=new int[this->numar_camere];
		for(int i=0;i<this->numar_camere;i++)
			this->suprafara_camere[i]=v[i];
		return aux;
	}
	Apartament operator+(int valoare)
	{
		Apartament aux=*this;
		aux.pret=aux.pret+valoare;
		return aux;
	}
	operator double()
	{
		return (double)(this->suprTotala()/this->numar_camere);
	}
	friend ofstream &operator<<(ofstream &out, Apartament &a);
	friend ifstream &operator>>(ifstream &in, Apartament &a);
};
ostream &operator<<(ostream &out, Apartament &a)
{
	out<<a.an_constructie<<" "<<a.localitate<<" "<<a.pret<<" "<<a.numar_camere<<" Suprafata camere: ";
	for(int i=0;i<a.numar_camere;i++)
		out<<a.suprafara_camere[i]<<" ";
	return out;
}
ofstream &operator<<(ofstream &out, Apartament &a)
{
	out<<a.an_constructie<<endl;
	out<<a.localitate<<endl;
	out<<a.pret<<endl;
	out<<a.numar_camere<<endl;
	for(int i=0;i<a.numar_camere;i++)
		out<<a.suprafara_camere[i]<<endl;
	return out;
}
ifstream &operator>>(ifstream &in, Apartament &a)
{
	char aux[50];
	in.getline(aux, 50);
	delete [] a.localitate;
	a.localitate=new char[strlen(aux)+1];
	strcpy(a.localitate,aux);
	in>>a.pret;
	in>>a.numar_camere;
	for(int i=0;i<a.numar_camere;i++)
		in>>a.suprafara_camere[i];
	return in;
}
class ApartamentSocial:public Apartament{
private:
	char* locatar;
	int chirie;
public:
	ApartamentSocial():Apartament()
	{
		this->locatar=new char[strlen("Necunoscut")+1];
		strcpy(this->locatar,"Necunoscut");
		this->chirie=0;
	}
	ApartamentSocial(const int an_constructie, char* localitate, int pret, int numar_camere, int *suprafara_camere, char* locatar, int chirie)
		:Apartament(an_constructie,localitate,pret,numar_camere,suprafara_camere)
	{
		this->locatar=new char[strlen(locatar)+1];
		strcpy(this->locatar,locatar);
		this->chirie=chirie;
	}
	~ApartamentSocial()
	{
		if(this->locatar!=NULL)
			delete [] this->locatar;
	}
	friend ostream &operator<<(ostream &out, ApartamentSocial &as);
};
ostream &operator<<(ostream &out, ApartamentSocial &as)
{
	out<<as.getAnConstr()<<" "<<as.getLocalitate()<<" "<<as.getPret()<<" "<<as.getNumarCamere()<<" Suprafata camere: ";
	for(int i=0;i<as.getNumarCamere();i++)
		out<<as.getVectorSupr()[i]<<" ";
	out<<as.locatar<<" "<<as.chirie;
	return out;
	}
void main()
{
	Apartament a1;
	int *vectSupr1;
	vectSupr1=new int[3];
	vectSupr1[0]=200;
	vectSupr1[1]=100;
	vectSupr1[2]=800;
	Apartament a2(1978,"Bucuresti",79000,3,vectSupr1);
	
	cout<<a1.getAnConstr()<<endl;
	a2.setLocalitate("Cluj");
	for(int i=0;i<3;i++)
		cout<<a2.getVectorSupr()[i]<<" ";
	cout<<endl;
	int *vectSupr2;
	vectSupr2=new int[3];
	vectSupr2[0]=50;
	vectSupr2[1]=150;
	vectSupr2[2]=600;
	a2.setVectorSupr(vectSupr2,3);

	Apartament a3=a2;
	Apartament a4;
	a4=a3;
	cout<<a1<<endl<<a2<<endl<<a3<<endl<<a4<<endl;
	
	a3=a3+100;//se creste pretul apartamentului a3 cu 100 euro
	cout<<a3<<endl;
	a2++;//se incrementeaza numarul de camere pentru apartamentul a3
	cout<<a2<<endl;

	cout<<"Suprafata totala a aparatmentului este:"<<a3.suprTotala()<<endl;
	if(a3>a2)
		cout<<"Apartamentul a3 este mai scump ca a2"<<endl;
	else if(a3<a2)
		cout<<"Apartamentul a3 este mai ieftin ca a2"<<endl;
	else
		cout<<"Apartamentul a3 si a2 au acelasi pret"<<endl;
	
	ofstream fisOut("iesire.txt");
	fisOut<<a4;//se salveaza in fisier datele despre apartamentul a4
	fisOut.close();
	ifstream fisIn("intrare.txt",ios::in);
	fisIn>>a4;//se citesc din fisier datale despre apartamentul a4
	cout<<a4<<endl;
	fisIn.close();

	cout<<(double)a2<<endl;// se calculeaza suprafata medie a unei camere din apartamentul a2
	
	int *vectSupr3;
	vectSupr3=new int[2];
	vectSupr3[0]=300;
	vectSupr3[1]=900;
	ApartamentSocial as1(1999,"Bucuresti",57000,2,vectSupr3,"Popescu Ion",750);
	cout<<as1<<endl;

	//se adauga toate apartamentele intr-o structura STL de tip vector si se afiseaza folosind un iterator
	vector<Apartament> bloc;
	bloc.push_back(a1);
	bloc.push_back(a2);
	bloc.push_back(a3);
	bloc.push_back(a4);
	vector<Apartament>::iterator it;
	for(it=bloc.begin();it!=bloc.end();it++)
		cout<<*it<<endl;
}

