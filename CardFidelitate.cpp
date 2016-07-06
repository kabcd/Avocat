#include <iostream>
using namespace std;
class CardFidelitate{
private:
	int puncte_disponibile;
	char* posesor;
	int nr_luni;
	float *puncte_pe_luna;//puncte primite pt vechime in fiecare luna
	const int cod_card;
public:
	//constructor fara parametri
	CardFidelitate():cod_card(0)
	{
		this->puncte_disponibile=0;
		this->posesor=new char[strlen("Anonim")+1];
		strcpy(this->posesor,"Anonim");
		this->nr_luni=0;
		puncte_pe_luna=NULL;
	}
	//constructor cu parametri
	CardFidelitate(int puncte_disponibile, char* posesor,int nr_luni, float *puncte_pe_luna, const int COD_CARD):cod_card(COD_CARD)
	{
		this->puncte_disponibile=puncte_disponibile;
		this->posesor=new char[strlen(posesor)+1];
		strcpy(this->posesor,posesor);
		this->nr_luni=nr_luni;
		this->puncte_pe_luna=new float[nr_luni];
		for(int i=0;i<nr_luni;i++)
			this->puncte_pe_luna[i]=puncte_pe_luna[i];
	}
	//destructor
	~CardFidelitate()
	{
		if(this->posesor!=NULL)
			delete [] posesor;
		if(this->puncte_pe_luna!=NULL)
			delete [] puncte_pe_luna;
	}
	//constructor de copiere
	CardFidelitate(CardFidelitate &c):cod_card(c.cod_card)
	{
		this->puncte_disponibile=c.puncte_disponibile;
		this->posesor=new char[strlen(c.posesor)+1];
		strcpy(this->posesor,c.posesor);
		this->nr_luni=c.nr_luni;
		this->puncte_pe_luna=new float[c.nr_luni];
		for(int i=0;i<c.nr_luni;i++)
			this->puncte_pe_luna[i]=c.puncte_pe_luna[i];
	}
	//operator =
	CardFidelitate operator=(CardFidelitate c)
	{
		if(this->posesor != NULL)
			delete[] this->posesor;
		if(this->puncte_pe_luna!= NULL)
			delete[] this->puncte_pe_luna;
		this->puncte_disponibile=c.puncte_disponibile;
		this->posesor=new char[strlen(c.posesor)+1];
		strcpy(this->posesor,c.posesor);
		this->nr_luni=c.nr_luni;
		this->puncte_pe_luna=new float[c.nr_luni];
		for(int i=0;i<c.nr_luni;i++)
			this->puncte_pe_luna[i]=c.puncte_pe_luna[i];
		return *this;
	}
	//geterii si setterii
	char* getPosesor()
	{ 
		return this->posesor;
	}
	void setPosesor(char* posesorNou)
	{
		if(this->posesor!=NULL)
		{
			delete [] this->posesor;
			this->posesor=new char[strlen(posesorNou)+1];
			strcpy(this->posesor,posesorNou);
		}
		else
			throw new exception("Posesor invalid!");
	}
	const int getCod_card()
	{
		return this->cod_card;
	}
	float TotalPuncteVechime(float *puncte_pe_luna, int nr_luni)
	{
		float t=0;
		for(int i=0;i<this->nr_luni;i++)
			t=t+this->puncte_pe_luna[i];
		return t;
	}
	//supraincarcare <<
	friend ostream &operator<<(ostream &out,CardFidelitate &c);
	//supraincarcare -=
	CardFidelitate operator-=(int pct)
	{
	   this->puncte_disponibile-=pct;
	   return *this;
	}
	//supraincarcare cast
	operator int()
	{ 
		return this->puncte_disponibile;
	}
	//supraincarcare >>
	friend istream &operator>>(istream &in, CardFidelitate &c);
	//supraincarcare += 
	CardFidelitate operator+=(float x)	
	{
		if(this->puncte_pe_luna!= NULL)
		{
			float *aux = new float[this->nr_luni+1];
			for(int i=0;i<this->nr_luni;i++)
				aux[i] = this->puncte_pe_luna[i];
			aux[nr_luni] = x;

			this->nr_luni ++;
			delete	[] this->puncte_pe_luna;
			this->puncte_pe_luna = new float[this->nr_luni];
			for(int i=0;i<this->nr_luni;i++)
				puncte_pe_luna[i] = aux[i];
		}
		return *this;
	}
};
ostream &operator<<(ostream &out,CardFidelitate &c)
{
		cout<<"Cod card: "<<c.cod_card<<endl;
		cout<<"Posesor: "<<c.posesor<<endl;
		cout<<"Puncte disponibile: "<<c.puncte_disponibile<<endl;
		cout<<"Nr luni: "<<c.nr_luni<<endl;
		cout<<"Puncte pe luna: ";
		for(int i=0;i<c.nr_luni;i++)
			out<<c.puncte_pe_luna[i]<<" ";
		out<<endl;
		return out;
}
istream &operator>>(istream &in, CardFidelitate &c)
{	
		char aux[50];
	    cout<<"Dati posesor: ";
		in.getline(aux, 50);
		if(c.posesor != NULL)
			delete[] c.posesor;
		c.posesor = new char[strlen(aux)+1];
		strcpy(c.posesor,aux);
		cout<<endl<<"Dati puncte disponibile:";
		in>>c.puncte_disponibile;
		cout<<endl<<"Dati nr luni:";
		in>>c.nr_luni;
		if(c.puncte_pe_luna!= NULL)
			delete[] c.puncte_pe_luna;
		c.puncte_pe_luna = new float[c.nr_luni];
		cout<<endl<<"Dati puncte pe luna:";
		for(int i=0;i<c.nr_luni;i++)
			in>>c.puncte_pe_luna[i];
		return in;
}
void main()
{
	CardFidelitate cf1;
	cout<<cf1.getCod_card()<<endl;

	cf1.setPosesor("Cristea Mihai");
	cout<<cf1.getPosesor()<<endl;
	
	float *x=new float[4];
	x[0]=10;
	x[1]=20;
	x[2]=30;
	x[3]=40;
	CardFidelitate cf2(25,"Georgescu Ion",4,x,12);
	cout<<cf2<<endl;

	cout<<"Total puncte vechime:"<<cf2.TotalPuncteVechime(x,4)<<endl; //calculeaza numarul total de puncte primite de posesor pentru vechimea cardului

	CardFidelitate cf3=cf2;
	cout<<cf3<<endl;

	CardFidelitate cf4;
	cf4=cf2;
	cout<<cf4<<endl;

	CardFidelitate cf5;
	cin>>cf5;
	cout<<cf5<<endl;
	
	cf3-=20;// se diminueaza numarul de puncte disponibile pe card cu 20
	cout<<cf3<<endl;

	cf3+=20.5; // se adauga o nou luna cu un nr de puncte pentru vechime
	cout<<cf3<<endl;

	CardFidelitate cf6(25,"Anghel Andrei",4,x,32);
	int t=cf6;// cast-ul returneaza numarul de puncte disponibile pe card
	cout<<t<<endl;
}
