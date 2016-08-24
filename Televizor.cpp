#include<iostream>
using namespace std;
class Televizor{
private:
	char* firma;
	int nr_canale;
	float *canale;
	const float diagonala;
	static int nr_televizoare;
public:
	//constructor fara parametri
	Televizor():diagonala(0)
	{
		this->firma=new char[strlen("Anonim")+1];
		strcpy(this->firma,"Anonim");
		this->nr_canale=0;
		this->canale=NULL;
		Televizor::nr_televizoare++;
	}
	//constructor cu parametri
	Televizor(char* firma,int nr_canale,float *canale,const float DIAGONALA):diagonala(DIAGONALA)
	{
		this->firma=new char[strlen(firma)+1];
		strcpy(this->firma,firma);
		this->nr_canale=nr_canale;
		this->canale=new float[nr_canale];
		for(int i=0;i<nr_canale;i++)
			this->canale[i]=canale[i];
		Televizor::nr_televizoare++;
	}
	//destructor
	~Televizor()
	{
		if(this->firma!=NULL)
			delete [] this->firma;
		if(this->canale!=NULL)
			delete [] this->canale;
		Televizor::nr_televizoare--;
	}
	//constructor de copiere
	Televizor(Televizor &t):diagonala(t.diagonala)
	{
		this->firma=new char[strlen(t.firma)+1];
		strcpy(this->firma,t.firma);
		this->nr_canale=t.nr_canale;
		this->canale=new float[t.nr_canale];
		for(int i=0;i<t.nr_canale;i++)
			this->canale[i]=t.canale[i];
		Televizor::nr_televizoare++;
	}
	//supraincarcare =
	Televizor operator=(Televizor t)
	{
		if(this->firma!=NULL)
			delete [] this->firma;
		if(this->canale!=NULL)
			delete [] this->canale;
		this->firma=new char[strlen(t.firma)+1];
		strcpy(this->firma,t.firma);
		this->nr_canale=t.nr_canale;
		this->canale=new float[t.nr_canale];
		for(int i=0;i<t.nr_canale;i++)
			this->canale[i]=t.canale[i];
		return *this;
	}
	//setterii si getteri 
	char* getFirma()
	{
		return this->firma;
	}
	int getNrCanale()
	{
		return this->nr_canale;
	}
	float *getCanale()
	{
		return this->canale;
	}
	static int getNrTelevizoare()
	{
		return Televizor::nr_televizoare;
	}
	void setFirma(char* firmaNou)
	{
		if(firmaNou!=NULL)
		{
			if(this->firma!=NULL)
				delete [] this->firma;
			this->firma=new char[strlen(firmaNou)+1];
			strcpy(this->firma,firmaNou);
		}
		else
			throw new exception("Firma invalida!");
	}
	void setCanale(float *canaleNou, int nr_canaleNou)
	{
		if(canaleNou!=NULL)
		{
			if(this->canale!=NULL)
				delete [] this->canale;
			this->nr_canale=nr_canaleNou;
			this->canale=new float[nr_canaleNou];
			for(int i=0;i<nr_canaleNou;i++)
				this->canale[i]=canaleNou[i];
		}
		else
			throw new exception("Vector canale invalid!");
	}
	//supraincarcare <<
	friend ostream &operator<<(ostream &out, Televizor &t);
	//supraincarcare >>
	friend istream &operator>>(istream &in, Televizor &t);
	//supraincarcare cast
	operator int()
	{
		return this->nr_canale;
	}
	Televizor operator ++()
	{
		if(this->canale!=NULL)
		{
			float *aux = new float[this->nr_canale+10];
			for(int i=0;i<=this->nr_canale;i++)
				aux[i] = this->canale[i];
			for(int i=this->nr_canale;i<this->nr_canale+10;i++)
				aux[i]=0;
			this->nr_canale+=10;
			delete[] this->canale;
			this->canale = new float[this->nr_canale];
			for(int i=0;i<this->nr_canale;i++)
				this->canale[i] = aux[i];
		}
		return *this;
	}
    Televizor operator+=(Televizor t)
    {
		 if(this->canale!=NULL)
		{
			float *aux = new float[this->nr_canale+t.nr_canale];
			for(int i=0;i<=this->nr_canale;i++)
				aux[i] = this->canale[i];
			for(int i=this->nr_canale;i<this->nr_canale+t.nr_canale;i++)
				aux[i]=0;
			this->nr_canale+=t.nr_canale;
			delete[] this->canale;
			this->canale = new float[this->nr_canale];
			for(int i=0;i<this->nr_canale;i++)
				this->canale[i] = aux[i];
		}
	     return *this;
	}
	bool operator>(Televizor t)
	{
		if(this->nr_canale>t.nr_canale)
			return true;
		else
			return false;
	}
    float &operator[](int index)
	{ 
		static float err;
		if( index>=0 && index<this->nr_canale)
			return canale[index];
		else
			return err;
	}
};
int Televizor::nr_televizoare=0;
ostream &operator<<(ostream &out, Televizor &t)
{
	cout<<"Diagonala: "<<t.diagonala<<endl;
	cout<<"Firma: "<<t.firma<<endl;
	cout<<"Nr canale: "<<t.nr_canale<<endl;
	cout<<"Canale: ";
	for(int i=0;i<t.nr_canale;i++)
		out<<t.canale[i]<<" ";
	out<<endl;
	return out;
}
istream &operator>>(istream &in, Televizor &t)
{
	cout<<endl<<"dati firma:";
	char aux[50];
	in>>aux;
	delete [] t.firma;
	t.firma=new char[strlen(aux)+1];
	strcpy(t.firma,aux);
	cout<<endl<<"dati nr canale:";
	in>>t.nr_canale;
	cout<<endl<<"dati canale:";
	delete [] t.canale;
	t.canale=new float[t.nr_canale];
	for(int i=0;i<t.nr_canale;i++)
		in>>t.canale[i];
	return in;
}
void main()
{
	Televizor t1;
	t1.setFirma("Nokia");
	cout<<t1.getFirma()<<endl;

	float *x=new float[4];
	x[0]=5;
	x[1]=6;
	x[2]=7;
	x[3]=8;
	Televizor t2("Apple",4,x,12);
	cout<<t2.getNrCanale()<<endl;
	for(int i=0;i<4;i++)
		cout<<t2.getCanale()[i]<<" ";
	cout<<endl;

	Televizor t3=t2;
	cout<<t3<<endl;

	Televizor t4;
	t4=t2;
	cout<<t4<<endl;

	int nr=t2;
	cout<<nr<<endl;

	Televizor t5;
	cin>>t5;
	cout<<t5<<endl;

	cout<<t2[0]<<endl;

	if(t1>t2)
		cout<<"Nr de canale ale lui t1 este mai mare decat nr de canale ale lui t2"<<endl;

	else
		cout<<"Nr de canale ale lui t2 este mai mare decat nr de canale ale lui t1"<<endl;

	cout<<"Nr televizoare:"<<Televizor::getNrTelevizoare()<<endl;

	++t2;
	cout<<t2<<endl;

	t3+=t2;
	cout<<t3<<endl;
}

