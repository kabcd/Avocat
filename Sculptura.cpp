#include<iostream>
using namespace std;
#include<fstream>
#include<map>
#include<string>
class Art{
protected:
	char* autor;
	char* denumire;
	int an_aparitie;
	float pretBiletAcces;
public:
	//constructor default
	Art()
	{
		this->autor=new char[strlen("Anonim")+1];
		strcpy(this->autor,"Anonim");
		this->denumire=new char[strlen("Anonim")+1];
		strcpy(this->denumire,"Anonim");
		this->an_aparitie=0;
		this->pretBiletAcces=0;
	}
	//constructor cu 4 parametri
	Art(char* autor, char* denumire, int an_aparitie, float pretBiletAcces)
	{
		this->autor=new char[strlen(autor)+1];
		strcpy(this->autor,autor);
		this->denumire=new char[strlen(denumire)+1];
		strcpy(this->denumire,denumire);
		this->an_aparitie=an_aparitie;
		this->pretBiletAcces=pretBiletAcces;
	}
	//constructor de copiere
	Art(Art &a)
	{
		this->autor=new char[strlen(a.autor)+1];
		strcpy(this->autor,a.autor);
		this->denumire=new char[strlen(a.denumire)+1];
		strcpy(this->denumire,a.denumire);
		this->an_aparitie=a.an_aparitie;
		this->pretBiletAcces=a.pretBiletAcces;	
	}
	//destructorr
	~Art()
	{
		if(this->autor!=NULL)
			delete [] this->autor;
		if(this->denumire!=NULL)
			delete [] this->denumire;	
	}
	//supraincarcare operator =
	void operator=(Art &a)
	{
		if(this->autor!=NULL)
			delete [] this->autor;
		this->autor=new char[strlen(a.autor)+1];
		strcpy(this->autor,a.autor);
		if(this->denumire!=NULL)
			delete [] this->denumire;
		this->denumire=new char[strlen(a.denumire)+1];
		strcpy(this->denumire,a.denumire);
		this->an_aparitie=a.an_aparitie;
		this->pretBiletAcces=a.pretBiletAcces;
	}
	//getterii
	float getPretBiletAcces()
	{
		return this->pretBiletAcces;
	}
	char* getAutor()
	{
		return this->autor;
	}
	char* getDenumire()
	{
		return this->denumire;
	}
	int getAnAparitie()
	{
		return this->an_aparitie;
	}
	//metoda virtuala
	virtual double valoareDinVizionari()=0;
};
class Sculptura:public Art{
private:
	char* CurentArtistic;
	int materialSuport;
	int nrVizitatori;
public:
	//constructor default
	Sculptura():Art()
	{
		this->CurentArtistic=new char[strlen("Anonim")+1];
		strcpy(this->CurentArtistic,"Anonim");
		this->materialSuport=0;
		this->nrVizitatori=0;
	}
	//constructor cu 7 parametri
	Sculptura(char* CurentArtistic, int materialSuport, int nrVizitatori,char* autor, char* denumire,int an_aparitie, float pretBiletAcces)
		:Art(autor,denumire,an_aparitie,pretBiletAcces)
	{
		this->CurentArtistic=new char[strlen(CurentArtistic)+1];
		strcpy(this->CurentArtistic,CurentArtistic);
		this->materialSuport=materialSuport;
		this->nrVizitatori=nrVizitatori;
	}
	//destructor
	~Sculptura()
	{
		if(this->CurentArtistic!=NULL)
			delete [] this->CurentArtistic;
	}
	//constructor de copiere
	Sculptura(Sculptura &s):Art(s)
	{
		this->CurentArtistic=new char[strlen(s.CurentArtistic)+1];
		strcpy(this->CurentArtistic,s.CurentArtistic);
		this->materialSuport=s.materialSuport;
		this->nrVizitatori=s.nrVizitatori;
	}
	//geterii si setterii
	char* getCurentArtistic()
	{
		return this->CurentArtistic;
	}
	void setCurentArtistic(char *CurentArtisticNou)
	{
		if(CurentArtisticNou==NULL)
			throw new exception("curent invalid");
		else
		{
			if(this->CurentArtistic!=NULL)
				delete [] this->CurentArtistic;
			this->CurentArtistic=new char[strlen(CurentArtisticNou)+1];
			strcpy(this->CurentArtistic,CurentArtisticNou);
		}
	}
	int getMaterialSuport()
	{
		return this->materialSuport;
	}
	int getNumarVizitatori()
	{
		return this->nrVizitatori;
	}
	//redefinire metoda virtuala
	double valoareDinVizionari()
	{
		return this->nrVizitatori*this->getPretBiletAcces();
	}
	//supraincarcare operator =
	void operator=(Sculptura s)
	{
		this->materialSuport=s.materialSuport;
		this->nrVizitatori=s.nrVizitatori;
		if(this->CurentArtistic!=NULL)
			delete [] this->CurentArtistic;
		this->CurentArtistic=new char[strlen(s.CurentArtistic)+1];
		strcpy(this->CurentArtistic,s.CurentArtistic);
		Art::operator=(s);	
	}
	//supraincarcare operator <<
	friend ostream &operator<<(ostream &out, Sculptura &s);
	friend ofstream &operator<<(ofstream &out, Sculptura &s);
	//supraincarcare operator >>
	friend istream &operator>>(istream &in, Sculptura &s);
	friend ifstream &operator>>(ifstream &in, Sculptura &s);
	//supraincarcare operator ++ forma postfixata
	Sculptura operator++(int)
	{
		Sculptura aux=*this;
		this->pretBiletAcces+=5;
		return aux;
	}
	//supraincarcare operator <
	char* operator<(Sculptura s)
	{
		if(this->nrVizitatori<s.nrVizitatori)
			return "mai mic";
		else
			return "mai mare";
	}
};
istream &operator>>(istream &in, Sculptura &s)
{
	cout<<"Dati curent artistic:";
	char aux[50];
	in>>aux;
	if(s.CurentArtistic!=NULL)
		delete [] s.CurentArtistic;
	s.CurentArtistic=new char[strlen(aux)+1];
	strcpy(s.CurentArtistic,aux);
	cout<<"Dati material suport:";
	in>>s.materialSuport;
	cout<<"Dati numar vizitatori:";
	in>>s.nrVizitatori;
	cout<<"Dati autor:";
	in>>aux;
	if(s.autor!=NULL)
		delete [] s.autor;
	s.autor=new char[strlen(aux)+1];
	strcpy(s.autor,aux);
	cout<<"Dati denumire:";
	in>>aux;
	if(s.denumire!=NULL)
		delete [] s.denumire;
	s.denumire=new char[strlen(aux)+1];
	strcpy(s.denumire,aux);
	cout<<"Dati an aparitie:";
	in>>s.an_aparitie;
	cout<<"Dati pret bilet:";
	in>>s.pretBiletAcces;
	return in;
}
ostream &operator<<(ostream &out, Sculptura &s)
{
	out<<s.CurentArtistic<<" "<<s.materialSuport<<" "<<s.nrVizitatori<<" "<<s.getAutor()<<" "<<s.getDenumire()<<" "<<s.getAnAparitie()<<" "<<s.getPretBiletAcces()<<endl;
	return out;
}
ifstream &operator>>(ifstream &in, Sculptura &s)
{
	char aux[150];
	in>>aux;
	if(s.CurentArtistic!=NULL)
		delete [] s.CurentArtistic;
	s.CurentArtistic=new char[strlen(aux)+1];
	strcpy(s.CurentArtistic,aux);
	in>>s.materialSuport;
	in>>s.nrVizitatori;

	char buff[150];
	in>>buff;
	if(s.autor!=NULL)
		delete [] s.autor;
	s.autor=new char[strlen(buff)+1];
	strcpy(s.autor,buff);

	in.ignore(256,'\n');
	char tmp[256];
	in.getline(tmp, 256);
	if(s.denumire!=NULL)
		delete [] s.denumire;
	s.denumire=new char[strlen(tmp)+1];
	strcpy(s.denumire,tmp);
	
	in>>s.an_aparitie;
	in>>s.pretBiletAcces;
	return in;
}
ofstream &operator<<(ofstream &out, Sculptura &s)
{
	out<<s.CurentArtistic<<endl;
	out<<s.materialSuport<<endl;
	out<<s.nrVizitatori<<endl;
	out<<s.autor<<endl;
	out<<s.denumire<<endl;
	out<<s.an_aparitie<<endl;
	out<<s.pretBiletAcces<<endl;
	return out;
}
class Muzeu{
private:
	int nr_sculpturi;
	Sculptura *sculpturi;
public:
	//constructor default
	Muzeu()
	{
		this->nr_sculpturi=0;
		this->sculpturi=NULL;
	}
	//constructor cu 2 parametri
	Muzeu(Sculptura *sculpturi,int nr_sculpturi)
	{
		this->nr_sculpturi=nr_sculpturi;
		this->sculpturi=new Sculptura[this->nr_sculpturi];
		for(int i=0;i<this->nr_sculpturi;i++)
			this->sculpturi[i]=sculpturi[i];
	}
	//constructor de copiere
	Muzeu(Muzeu &m)
	{
		this->nr_sculpturi=m.nr_sculpturi;
		this->sculpturi=new Sculptura[this->nr_sculpturi];
		for(int i=0;i<this->nr_sculpturi;i++)
			this->sculpturi[i]=m.sculpturi[i];
	}
	//destructor
	~Muzeu()
	{
		if(this->sculpturi!=NULL)
			delete [] this->sculpturi;
	}
	//supraincarcare operator =
	void operator=(Muzeu m)
	{
		this->nr_sculpturi=m.nr_sculpturi;
		if(this->sculpturi!=NULL)
			delete [] this->sculpturi;
		this->sculpturi=new Sculptura[this->nr_sculpturi];
		for(int i=0;i<this->nr_sculpturi;i++)
			this->sculpturi[i]=m.sculpturi[i];
	}
	//getterii
	int getNr_sculpturi()
	{
		return this->nr_sculpturi;
	}
	Sculptura *getSculpturi()
	{
		return this->sculpturi;
	}
	//supraincarcare operator <<
	friend ostream &operator<<(ostream &out, Muzeu &m);
	friend ofstream &operator<<(ofstream &out, Muzeu &m);
	//supraincarcare operator >>
	friend ifstream &operator>>(ifstream &in, Muzeu &m);
	//supraincarcare operator +=
	Muzeu operator+=(Sculptura s)
	{
		Sculptura *aux=new Sculptura[this->nr_sculpturi+1];
		for(int i=0;i<this->nr_sculpturi;i++)
			aux[i]=this->sculpturi[i];
		aux[this->nr_sculpturi]=s;
		this->nr_sculpturi++;
		if(this->sculpturi!=NULL)
			delete [] this->sculpturi;
		this->sculpturi=new Sculptura[this->nr_sculpturi];
		for(int i=0;i<this->nr_sculpturi;i++)
			this->sculpturi[i]=aux[i];
		return *this;
	}
	int NrSculpturi(char* curentArtistic)
	{
		int nr=0;
		for(int i=0;i<this->nr_sculpturi;i++)
			if((strcmp(this->sculpturi[i].getCurentArtistic(),curentArtistic)==0))
				nr++;
		return nr;
	}
	Sculptura *getCurentArtistic(char* curentArtistic)
	{
		int nr=NrSculpturi(curentArtistic);
		Sculptura *aux=new Sculptura[nr];
		for(int i=0;i<nr;i++)
			if((strcmp(this->sculpturi[i].getCurentArtistic(),curentArtistic)==0))
				aux[i]=this->sculpturi[i];
		return aux;
	}
};
ifstream &operator>>(ifstream &in, Muzeu &m)
{
	in>>m.nr_sculpturi;
	if(m.sculpturi!=NULL)
		delete [] m.sculpturi;
	m.sculpturi=new Sculptura[m.nr_sculpturi];
	for(int i=0;i<m.nr_sculpturi;i++)
		in>>m.sculpturi[i];
	return in;
}
ostream &operator<<(ostream &out, Muzeu &m)
{
	out<<m.nr_sculpturi<<endl;
	for(int i=0;i<m.nr_sculpturi;i++)
		out<<m.sculpturi[i]<<endl;
	return out;	
}
ofstream &operator<<(ofstream &out, Muzeu &m)
{
	out<<m.nr_sculpturi<<endl;
	for(int i=0;i<m.nr_sculpturi;i++)
		out<<m.sculpturi[i];
	return out;
}
void main()
{
	Sculptura s1("postmodernism",3,200,"Banut","oul de aur",1936,15.0f);
	Sculptura s2=s1;
	Sculptura s3; s3=s1;
	s3.setCurentArtistic("impresionism");
	
	Sculptura ms1[]={s1,s2,s3};
	Muzeu m1(ms1,sizeof(ms1)/sizeof(Sculptura));
	Muzeu m2(m1);
	Muzeu m3; m3=m1;
	
	s1++;//se mareste cu 5 lei pretul biletului
	m2+=s3;//se adauga sculptura s3 
	
	cout<<m1<<endl<<m2<<endl<<m3<<endl;
	cout<<s1<<s2<<s3<<endl;
	
	Sculptura s4;
	cin>>s4;
	cout<<s4<<endl;

	cout<<"Numar de vizitatori la "<<s3.getDenumire()<<" este "<<(s3<s4)<<" decat la "<<s4.getDenumire()<<endl;
	
	ofstream fisierOut("iesire.txt");
	fisierOut<<m1;
	fisierOut.close();
	ifstream fisierIn("iesire.txt");
	Muzeu m4;
	fisierIn>>m4;
	fisierIn.close();
	cout<<m4<<endl;

	cout<<s2.valoareDinVizionari()<<endl;
	Sculptura *s=m1.getCurentArtistic("postmodernism");
	for(int i=0;i<m1.NrSculpturi("postmodernism");i++)
		cout<<s[i]<<endl;

	cin.ignore(256,'\n');
	string denumire;
	map<string, Sculptura> sculpturi;// cheia este denumirea operei de arta
	map<string, Sculptura>::iterator it;
	typedef pair<string, Sculptura> element;	
	sculpturi.insert(element(s1.getDenumire(),s1));
	sculpturi.insert(element(s4.getDenumire(),s4));
	while(cout<<"Dati denumire sculptura sau CTRL/Z: ", getline(cin, denumire))
	{
		it=sculpturi.find(denumire);
		if(it!=sculpturi.end())
			cout<< denumire << ": " << (*it).second<< endl;
		else
			cout<<"opera inexistenta"<<endl;
	}
}
