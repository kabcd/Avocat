#include<iostream>
using namespace std;
class AlergatorMaraton{
public:
	float *timpCursa;
	int nrPuncteVerificare;
	const int id;
	static int nrAlergatori;
public:
	AlergatorMaraton():id(1)
	{
		this->timpCursa=NULL;
		this->nrPuncteVerificare=0;
		AlergatorMaraton::nrAlergatori++;
	}
	AlergatorMaraton(float *timpCursa, int nrPuncteVerificare, const int ID):id(ID)
	{
		this->nrPuncteVerificare=nrPuncteVerificare;
		this->timpCursa=new float[nrPuncteVerificare];
		for(int i=0;i<nrPuncteVerificare;i++)
			this->timpCursa[i]=timpCursa[i];
		AlergatorMaraton::nrAlergatori++;	
	}
	~AlergatorMaraton()
	{
		if(this->timpCursa!=NULL)
			delete [] timpCursa;
		AlergatorMaraton::nrAlergatori--;
	}
	AlergatorMaraton(AlergatorMaraton &a):id(a.id)
	{
		this->nrPuncteVerificare=a.nrPuncteVerificare;
		this->timpCursa=new float[a.nrPuncteVerificare];
		for(int i=0;i<a.nrPuncteVerificare;i++)
			this->timpCursa[i]=a.timpCursa[i];
		AlergatorMaraton::nrAlergatori++;
	}
	AlergatorMaraton operator=(AlergatorMaraton a)
	{
		if(this->timpCursa!=NULL)
			delete [] timpCursa;
		this->nrPuncteVerificare=a.nrPuncteVerificare;
		this->timpCursa=new float[a.nrPuncteVerificare];
		for(int i=0;i<a.nrPuncteVerificare;i++)
			this->timpCursa[i]=a.timpCursa[i];
		return *this;
	}
	int getNrPuncteIntermediare()
	{
		return this->nrPuncteVerificare;
	}
	float getTotalRaceTime()
	{
		if(this->timpCursa==NULL)
			return 0;
		else
			return this->timpCursa[nrPuncteVerificare-1];
	}
	void setRaceTime(float *timpCursaNou, int nrPuncteVerificareNou)
	{
		if(timpCursaNou!=NULL)
		{
			if(this->timpCursa!=NULL)
				delete [] this->timpCursa;
			this->nrPuncteVerificare=nrPuncteVerificareNou;
			this->timpCursa=new float[nrPuncteVerificareNou];
			for(int i=0;i<nrPuncteVerificareNou;i++)
				this->timpCursa[i]=timpCursaNou[i];
		}
		else
			throw new exception("Timp cursa invalid!");
	}
	friend ostream &operator<<(ostream &out, AlergatorMaraton &a);
	AlergatorMaraton operator++()
	{
	    if(this->timpCursa!=NULL)
		{
			float *aux=new float[this->nrPuncteVerificare+1];
			for(int i=0;i<nrPuncteVerificare;i++)
				aux[i]=this->timpCursa[i];
			aux[this->nrPuncteVerificare]=100;

			this->nrPuncteVerificare++;
			delete [] this->timpCursa;
			this->timpCursa=new float[this->nrPuncteVerificare];
			for(int i=0;i<this->nrPuncteVerificare;i++)
				this->timpCursa[i]=aux[i];
		}
		return *this;
	}
    operator float()
	{
		return this->timpCursa[this->nrPuncteVerificare-1];
	}
	friend AlergatorMaraton operator+(double valoare, AlergatorMaraton a);
	bool operator<(AlergatorMaraton a)
	{
		if(this->nrPuncteVerificare>a.nrPuncteVerificare)
			return true;
		else
			return false;
	}
};
int AlergatorMaraton::nrAlergatori=0;
ostream &operator<<(ostream &out, AlergatorMaraton &a)
{
	out<<"Alergator "<<a.id<<", "<<a.getNrPuncteIntermediare()<<" puncte intermediare: ";
	for(int i=0;i<a.nrPuncteVerificare;i++)
		out<<a.timpCursa[i]<<" ";
	return out;
}
AlergatorMaraton operator+(double valoare, AlergatorMaraton a)
{
	AlergatorMaraton tmp=a;
	if(tmp.timpCursa!=NULL)
	{
		float *aux=new float[tmp.nrPuncteVerificare+1];
		for(int i=0;i<tmp.nrPuncteVerificare;i++)
			aux[i]=tmp.timpCursa[i];
		aux[tmp.nrPuncteVerificare]=valoare;

		tmp.nrPuncteVerificare++;
		delete [] tmp.timpCursa;
		tmp.timpCursa=new float[tmp.nrPuncteVerificare];
		for(int i=0;i<tmp.nrPuncteVerificare;i++)
			tmp.timpCursa[i]=aux[i];
	}
	return tmp;
}
void main()
{
	AlergatorMaraton m1;
	cout<<m1.getTotalRaceTime()<<endl; //intoarce 0 daca nu exista timpi intermediari, altfel intoarce ultima valoare
	cout<<m1.id<<endl; 

	float timp1[] = { 12.5, 34.6, 78.3 };
	AlergatorMaraton m2(timp1,3,104); 
	cout<<m2.getNrPuncteIntermediare()<<endl; 
	
	AlergatorMaraton m3 = m2;
	cout<<m3.getTotalRaceTime()<<endl;
	
	float timp2[]={11.2, 44.6, 78.3, 89.9};
	m2.setRaceTime(timp2,4);
	cout<<m2.getTotalRaceTime()<<endl;
	
	cout<<m1<<endl<<m2<<endl;
	
	AlergatorMaraton m4;
	m4 = m2;
	cout<<m4.getTotalRaceTime()<<endl;

	cout<<AlergatorMaraton:: nrAlergatori<<endl; 

	AlergatorMaraton * pm2 = new AlergatorMaraton (timp2,4,110);
	AlergatorMaraton m5 = ++(*pm2); //adauga un timp intermediar cu valoarea 100
	cout<<pm2->getNrPuncteIntermediare()<<" "<<m5.getNrPuncteIntermediare()<<endl; 
	
	delete pm2; //dezaloca spatiul ocupat de pm2
	
	float timp = (float)m5;
	cout<<timp<<endl; 
	
	AlergatorMaraton m6 = 110.6 + m5;
	cout<<m5<<endl;
	cout<<m6<<endl; 

	if(m5 < m2)
		cout<<"m5 are cursa cea mai rapida"<<endl;
	else
		cout<<"m2 are cursa cea mai rapida"<<endl; 
}
