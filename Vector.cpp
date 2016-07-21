#include<iostream>
using namespace std;
#include<fstream>
class MaiMare{
public:
	bool operator ()(int i, int j) 
	{
		return i>j;
	}
};
template<typename T>
class Vector{
protected:
	T *pe;
	int dim;
public:
	Vector<T>()
	{
		this->dim=0;
		this->pe=NULL;
	}
	Vector<T>(int dim)
	{
		this->dim=dim;
		this->pe=new T[this->dim];
		for(int i=0;i<this->dim;i++)
			this->pe[i]=0;
	}
	Vector<T>(int dim, T *pe)
	{
		this->dim=dim;
		this->pe=new T[this->dim];
		for(int i=0;i<this->dim;i++)
			this->pe[i]=pe[i];
	}
	Vector<T>(int dim, T pe)
	{
		this->dim=dim;
		this->pe=new T[this->dim];
		for(int i=0;i<this->dim;i++)
			this->pe[i]=pe;
	}
	~Vector<T>()
	{
		if(this->pe!=NULL)
			delete [] this->pe;	
	}
	Vector<T>(Vector<T> &v)
	{
		this->dim=v.dim;
		this->pe=new T[this->dim];
		for(int i=0;i<this->dim;i++)
			this->pe[i]=v.pe[i];
	}
	Vector<T> operator=(Vector<T> v)
	{
		this->dim=v.dim;
		this->pe=new T[this->dim];
		for(int i=0;i<this->dim;i++)
			this->pe[i]=v.pe[i];
		return *this;
	}
	friend ostream &operator<< <>(ostream &out, Vector<T> &v);
	friend ifstream &operator>> <>(ifstream &in, Vector<T> &v);
	int getDim()
	{
		return this->dim;
	}
	T *getPe()
	{
		return this->pe;
	}
	T operator*(Vector<T> v)
	{
		T s=0;
		for(int i=0;i<dim;i++)
			s=s+this->pe[i]*v.pe[i];
		return s;
	}
	//o metoda sort() pentru sortarea vectorului dupa o directie primita ca obiect de clasa MaiMare avand supraincarcat operatorul functie a.i.compara cu >"mai mare"
	void sort(MaiMare mm)
	{
		for (int i = 0; i < this->dim-1; i++)
			for (int j = i + 1; j < dim; j++)
				if (mm(this->pe[i], this->pe[j])==true)
				{
					T temp = this->pe[i];
					this->pe[i] = this->pe[j];
					this->pe[j] = temp;
				}
	} 
};
template<typename T> ifstream &operator>> <>(ifstream &in, Vector<T> &v)
{
	in>>v.dim;
	delete [] v.pe;
	v.pe=new T[v.dim];
	for(int i=0;i<v.dim;i++)
		in>>v.pe[i];
	return in;
}
template<typename T> ostream &operator<< <>(ostream &out, Vector<T> &v)
{
	out<<v.dim<<endl;
	for(int i=0;i<v.dim;i++)
		out<<v.pe[i]<<" ";
	return out;
}
template<typename T>
class Cantitati:public Vector<T>{
private:
	char denumireProd[30];
	char umProd[20];
public:
	Cantitati(char* denumireProd, char* umProd, int dim, T *pe)
		:Vector<T>(dim, pe)
	{
		strcpy(this->denumireProd,denumireProd);
		strcpy(this->umProd,umProd);
	}
};
template<typename T>
class Preturi:public Vector<T>{
private:
	char valuta[10];//usd, eur, yen
	float curs;//curs de schimb al valutei, exprimat in lei
public:
	Preturi(char* valuta, float curs, int dim, T *pe)
		:Vector<T>(dim, pe)
	{
		strcpy(this->valuta,valuta);
		this->curs=curs;
	}
	float getCurs()
	{
		return this->curs;
	}
};
template<typename T>
T operator*(Cantitati<T> c, Preturi<T> p)
{
	T s=0;
	for(int i=0;i<p.getDim();i++)
		s=s+c.getPe()[i]*p.getPe()[i];
	return s;
}
void main()
{
	Vector<float> v1(5,1);//vector cu 5 elemente fiecare avand valoarea 1
	
	Vector<float> v2(7);//vector cu 7 elemente fiecare avend valoarea 0
	
	float vf[5]={1,2,3,4,5};
	Vector<float> v3(5,vf);//vector cu 5 elemente preluate din vectorul vf
	
	Vector<float> v4;
	ifstream fisIn("vector.txt");
	fisIn>>v4;
	fisIn.close();
	
	cout<<v1<<endl<<v2<<endl<<v3<<endl<<v4<<endl;

	cout<<"Media elementelor lui v3:"<<v1*v3/v1.getDim()<<endl;

	float vq[3]={2,7,4};
	Cantitati<float> q1("Auto","buc",3,vq);//cantitati din 3 tipuri de autoturisme preluate din vectorul vq
	
	float vp[3]={5900,7000,7500};
	Preturi<float> p1("eur",4.5,3,vp);//3 preturi in euro la curs 4.5 preluate din vectorul vp
	
	cout<<"Valoarea autoturismelor in lei:"<<q1*p1*p1.getCurs()<<endl;

}