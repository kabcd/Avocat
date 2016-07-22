#include<iostream>
using namespace std;
#include<fstream>
#include<string>
#include<map>
class Sir{
protected:
	char* pe;
	int lg;
public:
	//construcor default
	Sir()
	{
		cout<<" Constructor default Sir: "<<endl;
		this->pe=NULL;
		this->lg=0;
	}
	//constructor cu parametri
	Sir(char* pe,int lg)
	{
		cout<<" Constructor cu 2 parametri Sir: "<<endl;
		this->lg=lg;
		this->pe=new char[this->lg+1];
		strcpy(this->pe,pe);
	}
	//constructor de copiere
	Sir(Sir &s)
	{
		cout<<" Constructor de copiere Sir: "<<endl;
		this->lg=s.lg;
		this->pe=new char[s.lg+1];
		strcpy(this->pe,s.pe);
	}
	//destructor
	~Sir()
	{
		cout<<" Destructor Sir: "<<endl;
		if(this->pe!=NULL)
			delete [] this->pe;
	}
	//supraincarcare operator =
	Sir &operator=(Sir &s)
	{
		cout<<" Operator = Sir: "<<endl;
		if(this->pe!=NULL)
			delete [] this->pe;
		this->lg = s.lg;
		this->pe = new char[s.lg+1];
		strcpy(this->pe, s.pe);
		return *this;
	}
	//geterii
	int getLg()
	{
		return this->lg;
	}
	char* getPe()
	{
		return this->pe;
	}
	//supraincarcare operator ! pentru a testa daca sirul este vid
	bool operator!()
	{
		cout<<" Operator ! Sir: "<<endl;
		if (this->pe!= NULL)
			return true;
		else
			return false;
	}
	//supraincarcare operator >>
	friend istream &operator>>(istream &in, Sir &s);
	//supraincarcare operator <<
	friend ostream &operator<<(ostream &out, Sir &s);
	//supraincarcare operator += pentru concatenarea unui obiect Sir cu char[] cu obtinerea unui obiect nou Sir
	friend Sir &operator+(Sir &s1, char* s2);
	//supraincarcare operator += pentru concatenarea unui obiect Sir la un obiect Sir existent
	Sir &operator+=(Sir &s)
	{
		cout<<" Operator += Sir: "<<endl;
		char* aux=new char[this->lg+s.lg+1];
		strcpy(aux, this->pe);
		strcat(aux, s.pe);
		this->lg+=s.lg;
		if(this->pe!=NULL)
			delete [] this->pe;
		this->pe = new char[this->lg+1];
		strcpy(this->pe, aux);
		return *this;
	}
	//supraincarcare operator [] pentru referirea unui caracter din sir
	char &operator[](int index)
	{
		cout<<" Operator [] Sir: "<<endl;
		static char err;
		if (index>=0 && index<this->lg)
			return this->pe[index];
		else
			return err;
	}
	//supraincarcare opearator ==
	bool operator==(Sir &s)
	{
		cout<<" Operator == Sir: "<<endl;
		if(strcmp(this->pe,s.pe)==0)
			return true;
		else
			return false;
	}
	//supraincarcare operator !=
	bool operator!=(Sir &s)
	{
		cout<<" Operator != Sir: "<<endl;
		if(strcmp(this->pe,s.pe)!=0)
			return 1;
		else
			return 0;		
	}
	//supraincarcare operator <
	bool operator<(Sir &s)
	{
		cout<<" Operator < Sir: "<<endl;
		if(strcmp(this->pe,s.pe)<0)
			return true;
		else
			return false;
	}
	//supraincarcare cast la char
	operator char()
	{
		cout<<" Operator cast Sir: "<<endl;
		return this->pe[0];
	}
};
istream &operator >>(istream &in, Sir &s)
{
	cout<<" Operator >> Sir: "<<endl;
	cout << "Dati lungimea:";
	in >> s.lg;
	cout << "Dati sir:";
	char buffer[50];
	in >> buffer;
	if(s.pe!=NULL)
		delete [] s.pe;
	s.pe = new char[s.lg + 1];
	strcpy(s.pe, buffer);
	return in;
}
ostream &operator<<(ostream &out, Sir &s)
{
	cout<<" Operator << Sir: "<<endl;
	out<<s.pe<<endl;
	return out;
}
Sir &operator+(Sir &s1, char* s2)
{
	cout<<" Operator + Sir: "<<endl;
	Sir *s=new Sir();
	s->lg=s1.lg+strlen(s2);
	s->pe=new char[s->lg+1];
	if(s1.pe!=NULL)
	{
		if (s2!=NULL)
		{
			strcpy(s->pe, s1.pe);
			strcat(s->pe, s2);
		}
	}
	else
	{
		if (s2!=NULL)
			strcpy(s->pe, s2);
	}
	return *s;
}
class SirNumeric :public Sir{
public:
	//constructor default
	SirNumeric():Sir()
	{
		cout<<" Constructor default SirNumeric: "<<endl;
	}
	//constructor cu 2 parametri
	SirNumeric(char* pe, int lg):Sir(pe, lg)
	{
		cout<<" Constructor cu 2 parametri SirNumeric: "<<endl;
	}
	//destructor
	~SirNumeric()
	{
		cout<<" Destructor SirNumeric: "<<endl;
	}
	//metoda membra
	bool test()
	{
		if(strstr(this->pe,"0123456789")==0)
			return true;
		else
			return false;
	}
	//supraincarcare operator+
	long operator+(SirNumeric &s)
	{
		cout<<" Operator+ SirNumeric: "<<endl;
		return atol(this->pe)+atol(s.pe);
	}
};
void main()
{
	Sir a("abcdef",6);
	Sir b = a;
	cout<<a<<endl<<b<<endl;
	
	cout <<!a<<endl;

	Sir c;
	c = a;
	cout<<c<<endl;

	char sir[20]="ABCDEF";
	a = b + sir;
	cout <<a<<endl;
	
	a += b;
	cout <<a<<endl;
	
	cout <<a[2]<<endl;
	a[3]='a';
	cout<<a<<endl;

	Sir d;
	cin>>d;
	cout <<(char)d<<endl;
	
	if( a == b) 
		cout<<"Sirul a este egal cu sirul b"<<endl;
	else 
		cout <<"Sirul a nu este egal cu sirul b"<<endl;
	
	SirNumeric sn1("157890",15);
	SirNumeric sn2("123450", 16);
	if(sn1.test()!=0)
		cout<<"Sirul contine doar cifre 0-9"<<endl;
	else
		cout<<"Sirul nu contine doar cifre 0-9"<<endl;
	
	long nr; nr=sn1+sn2;
	cout<<nr<<endl;

	//se implementeaza un dictionar care permite cautarea unui cuvant din limba engleza si furnizarea unui obiect de tip Sir continand traducarea acestuia in limba romana, folosind o structura map STL
	cin.ignore(256,'\n');
	string cuvant;
	map<string, Sir> dictionar;
	map<string,	Sir>::iterator it;
	typedef pair<string, Sir> element;
	Sir s1("caine", 5); Sir s2("mare", 4); Sir s3("profesor", 8);
	dictionar.insert(element("dog",s1));
	dictionar.insert(element("sea",s2));
	dictionar.insert(element("teacher",s3));
	while(cout<<"Dati cuvant in limba engleza sau CTRL/Z: ", getline(cin, cuvant))
	{
		it=dictionar.find(cuvant);
		if(it!=dictionar.end())
			cout<< cuvant << "= " << (*it).second<< endl;
		else
			cout<<"cuvant inexistent"<<endl;
	}
}
