#include<iostream>
using namespace std;
#include<fstream>
#include<vector>
class Spectacol{
protected:
	int id;
	char* sala;
	int nr_spectatori;
	float pret_bilet;
	char* data;
public:
	Spectacol()
	{
		this->id=0;
		this->sala=new char[strlen("Anonim")+1];
		strcpy(this->sala, "Anonim");
		this->nr_spectatori=0;
		this->pret_bilet=0;
		this->data=new char[strlen("05/02/2016 10:00")+1];
		strcpy(this->data,"05/02/2016 10:00");
	}
	Spectacol(int id, char* sala, int nr_spectatori, float pret_bilet, char* data)
	{
		this->id=id;
		this->sala=new char[strlen(sala)+1];
		strcpy(this->sala, sala);
		this->nr_spectatori=nr_spectatori;
		this->pret_bilet=pret_bilet;
		this->data=new char[strlen(data)+1];
		strcpy(this->data,data);
	}
	Spectacol (const Spectacol &s)
	{
		this->id=s.id;
		this->sala=new char[strlen(s.sala)+1];
		strcpy(this->sala, s.sala);
		this->nr_spectatori=s.nr_spectatori;
		this->pret_bilet=s.pret_bilet;
		this->data=new char[strlen(s.data)+1];
		strcpy(this->data,s.data);
	}
	Spectacol operator=(Spectacol s)
	{
		if(this->sala!=NULL)
			delete [] this->sala;
		if(this->data!=NULL)
			delete [] this->data;
		this->id=s.id;
		this->sala=new char[strlen(s.sala)+1];
		strcpy(this->sala, s.sala);
		this->nr_spectatori=s.nr_spectatori;
		this->pret_bilet=s.pret_bilet;
		this->data=new char[strlen(s.data)+1];
		strcpy(this->data,s.data);
		return *this;
	}
	~Spectacol()
	{
		if(this->sala!=NULL)
			delete [] this->sala;
		if(this->data!=NULL)
			delete [] this->data;
	}
	char* getSala()
	{
		return this->sala;
	}
	void setSala(char* salaNou)
	{
		if(salaNou==NULL)
			throw new exception("Sala invalida!");
		else
		{
			if(this->sala!=NULL)
				delete [] this->sala;
			this->sala=new char[strlen(salaNou)+1];
			strcpy(this->sala, salaNou);
		}
	}
	int getId()
	{
		return this->id;
	}
	int getNr_spectatori()
	{
		return this->nr_spectatori;
	}
	int getPret_bilet()
	{
		return this->pret_bilet;
	}
	char* getData()
	{
		return this->data;
	}
	virtual float getValoare()
	{
		return this->pret_bilet*this->nr_spectatori;
	}
	friend ostream &operator<<(ostream &out, Spectacol &s);
	friend istream &operator>>(istream &in, Spectacol &s);
	friend ofstream &operator<<(ofstream &out, Spectacol &s);
	friend ifstream &operator>>(ifstream &in, Spectacol &s);
};
ostream &operator<<(ostream &out, Spectacol &s)
{
	out<<s.id<<" "<<s.sala<<" "<<s.pret_bilet<<" "<<s.nr_spectatori<<" "<<s.data<<endl;
	return out;
}
istream &operator>>(istream &in, Spectacol &s)
{
	cout<<"Dati id:";
	in>>s.id;
	cout<<"Dati sala:";
	char aux[50];
	in>>aux;
	if(s.sala!=NULL)
		delete [] s.sala;
	s.sala=new char[strlen(aux)+1];
	strcpy(s.sala,aux);
	cout<<"Dati pret bilet:";
	in>>s.pret_bilet;
	cout<<"Dati numar spectatori:";
	in>>s.nr_spectatori;
	cout<<"Dati data:";
	in.ignore(256,'\n');
	char tmp[256];
	in.getline(tmp, 256);
	if(s.data!=NULL)
		delete [] s.data;
	s.data=new char[strlen(tmp)+1];
	strcpy(s.data,tmp);
	return in;
}
ofstream &operator<<(ofstream &out, Spectacol &s)
{
	out<<s.id<<endl;
	out<<s.sala<<endl;
	out<<s.pret_bilet<<endl;
	out<<s.nr_spectatori<<endl;
	out<<s.data<<endl;
	return out;
}
ifstream &operator>>(ifstream &in, Spectacol &s)
{
	in>>s.id;
	char aux[50];
	in>>aux;
	if(s.sala!=NULL)
		delete [] s.sala;
	s.sala=new char[strlen(aux)+1];
	strcpy(s.sala,aux);
	in>>s.pret_bilet;
	in>>s.nr_spectatori;
	in.ignore(256,'\n');
	char tmp[256];
	in.getline(tmp, 256);
	if(s.data!=NULL)
		delete [] s.data;
	s.data=new char[strlen(tmp)+1];
	strcpy(s.data,tmp);
	return in;
}
class Spectacol3D:public Spectacol{
private:
	int numarOchelariVirtuali;
	float pretPereche;
public:
	Spectacol3D():Spectacol()
	{
		this->numarOchelariVirtuali=0;
		this->pretPereche=0;
	}
	Spectacol3D(int id, char* sala,int nr_spectatori,float pret_bilet, char* data,int numarOchelariVirtuali,float pretPereche)
		:Spectacol(id,sala,nr_spectatori,pret_bilet,data)
	{
		this->numarOchelariVirtuali=numarOchelariVirtuali;
		this->pretPereche=pretPereche;
	}
	friend ostream &operator<<(ostream &out, Spectacol3D &sd);
	float getValoare()
	{
		return this->getValoare()+this->numarOchelariVirtuali*this->pretPereche;
	}
};
ostream &operator<<(ostream &out, Spectacol3D &sd)
{
	out<<sd.id<<" "<<sd.sala<<" "<<sd.pret_bilet<<" "<<sd.nr_spectatori<<" "<<sd.data<<" "<<sd.pretPereche<<" "<<sd.numarOchelariVirtuali<<endl;
	return out;
}
class Cinematograf{
public:
	char denumire[30];
	int nr_spectacole;
	Spectacol *spectacole;
public:
	Cinematograf()
	{
		strcpy(this->denumire,"Anonim");
		this->nr_spectacole=0;
		this->spectacole=NULL;
	}
	Cinematograf(char* denumire, int nr_spectacole)
	{
		strcpy(this->denumire,denumire);
		this->nr_spectacole=nr_spectacole;
		this->spectacole=new Spectacol[this->nr_spectacole];
		Spectacol s;
		for(int i=0;i<this->nr_spectacole;i++)
			this->spectacole[i]=s;
	}
	Cinematograf(char* denumire, Spectacol spectacol)
	{
		strcpy(this->denumire,denumire);
		this->nr_spectacole=1;
		this->spectacole=new Spectacol[1];
		this->spectacole[0]=spectacol;
	}
	Cinematograf(Cinematograf &c)
	{
		strcpy(this->denumire,c.denumire);
		this->nr_spectacole=c.nr_spectacole;
		this->spectacole=new Spectacol[this->nr_spectacole];
		for(int i=0;i<this->nr_spectacole;i++)
			this->spectacole[i]=c.spectacole[i];
	}
	~Cinematograf()
	{
		if(this->spectacole!=NULL)
			delete [] this->spectacole;
	}
	friend ostream &operator<<(ostream &out, Cinematograf &c);
	friend istream &operator>>(istream &in, Cinematograf &c);
	Cinematograf operator+=(Spectacol s)
	{
		if(this->spectacole!=NULL)
		{
			Spectacol *v=new Spectacol[this->nr_spectacole+1];
			for(int i=0;i<this->nr_spectacole;i++)
				v[i]=spectacole[i];
			v[this->nr_spectacole]=s;
			
			delete [] this->spectacole;
			this->nr_spectacole++;
			this->spectacole=new Spectacol[this->nr_spectacole];
			for(int i=0;i<this->nr_spectacole;i++)
				this->spectacole[i]=v[i];	
		}
		else
		{
			this->nr_spectacole++;
			this->spectacole=new Spectacol[this->nr_spectacole];
			for(int i=0;i<this->nr_spectacole;i++)
				this->spectacole[i]=s;
		}
		return *this;
	}
	Cinematograf operator-=(Spectacol s)
	{
		for(int i=0;i<this->nr_spectacole;i++)
		{
			if(this->spectacole[i].getId()==s.getId())
			{
				for(int j=i;j<this->nr_spectacole-1;j++)
					this->spectacole[j]=this->spectacole[j+1];
				this->nr_spectacole--;
			}
		}
		return *this;
	}
	friend ofstream &operator<<(ofstream &out, Cinematograf &c);
	friend ifstream &operator>>(ifstream &in, Cinematograf &c);
	char* getDenumire()
	{
		return this->denumire;
	}
	operator double()
	{
		float s=0;
		for(int i=0;i<nr_spectacole;i++)
			s=s+this->spectacole[i].getValoare();
		return s;	
	}
	Spectacol &operator[](int index)
	{
		if(index>=0 && index<this->nr_spectacole)
			return this->spectacole[index];
		else
			throw index;
	}
};
ofstream &operator<<(ofstream &out, Cinematograf &c)
{
	out<<c.denumire<<endl;
	out<<c.nr_spectacole<<endl;
	for(int i=0;i<c.nr_spectacole;i++)
		out<<c.spectacole[i];
	return out;
}
ifstream &operator>>(ifstream &in, Cinematograf &c)
{
	in>>c.denumire;
	in>>c.nr_spectacole;
	if(c.spectacole!=NULL)
		delete [] c.spectacole;
	c.spectacole=new Spectacol[c.nr_spectacole];
	for(int i=0;i<c.nr_spectacole;i++)
		in>>c.spectacole[i];
	return in;
	}
ostream &operator<<(ostream &out, Cinematograf &c)
{
	out<<c.denumire<<endl;
	out<<c.nr_spectacole<<endl;
	for(int i=0;i<c.nr_spectacole;i++)
		out<<c.spectacole[i]<<endl;
	return out;
}
istream &operator>>(istream &in, Cinematograf &c)
{
	cout<<"Dati denumire: ";
	in>>c.denumire;
	cout<<"Dati nr spectacole: ";
	in>>c.nr_spectacole;
	if(c.spectacole!=NULL)
		delete [] c.spectacole;
	c.spectacole=new Spectacol[c.nr_spectacole];
	cout<<"Dati spectacole: ";
	for(int i=0;i<c.nr_spectacole;i++)
		in>>c.spectacole[i];
	return in;
}
void main()
{
	Spectacol s1;
	Spectacol s2(1,"VIP",13,75,"22/01/2016 10:00");
	Spectacol s3(2,"Ground",33,25,"22/01/2016 12:00");
	cout<<s1<<endl<<s2<<endl<<s3<<endl;

	s1.setSala("Gold");
	cout<<s1.getSala()<<endl;
	cout<<s2.getValoare()<<endl;//returneaza incasarile pentru s2

	Spectacol s4=s1;
	//cin>>s4;
	cout<<s4<<endl;
	
	Cinematograf c1;
	//cin>>c1;

	Cinematograf c2("Multiplex",2);//obiect initializat cu 2 spectacole cu valori implicite
	Cinematograf c3("Multiplex",s2);//obiect initializat cu 1 spectacol
	cout<<c1<<endl<<c2<<endl<<c3<<endl;
	
	Cinematograf c4;
	c4+=s1; c4+=s2; c4+=s3;//se adauga un spectacol
	cout<<c4<<endl;

	c4-=s1;//se elimina un  spectacol
	cout<<c4<<endl;
	
	cout<<"Valoarea incasarilor de la "<<c4.getDenumire()<<" este:"<<(double)c4<<endl;
	
	try{
		cout<<"Primul spectacol este: "<<c4[0];
		cout<<"Al cincilea spectacol este:"<<c4[10];
	}
	catch(int ex)
	{
		cout<<"Index invalid: "<<ex<<endl;
	}
	
	ofstream fisOut("cinema.txt");
	fisOut<<c4;
	fisOut.close();//se scriu datele despre cinematograful c4 in fisier;
	Cinematograf c5;
	ifstream fisIn("cinema.txt");
	fisIn>>c5;//se citesc datele despre cinematograful c5 in fisier
	cout<<c5<<endl;

	Spectacol3D sd(3,"Ground",32,35,"22/01/2016/12:00",20,5);
	cout<<sd<<endl;
	c4+=sd;
	cout<<(double)c4<<endl;
	
	// se adauga toate spectacole intr-o structura STL de tip vector si utilizand iteratori se parcurge multimea de spectacole si se afiseaza informatiile despre fiecare spectacol
	vector<Spectacol> spectacole;
	spectacole.push_back(s1);
	spectacole.push_back(s2);
	spectacole.push_back(sd);
	spectacole.push_back(s3);
	vector<Spectacol>::iterator it;
	for(it=spectacole.begin();it!=spectacole.end();it++)
		cout<<*it<<endl;
}