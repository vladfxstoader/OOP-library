#include <iostream>
#include <cstring>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <set>
#include <iterator>
#include <vector>
#include <fstream>
#include <map>
#include <list>
using namespace std;

ifstream f ("import.txt");
ofstream g ("export.txt");
/**
TOADER VLAD MARIAN, GRUPA 1421

TEMA: gestiunea mai multor biblioteci
CLASE: autor, carte (contine un obiect de tip autor), impozit (interfata),
angajat (clasa abstracta),angajat_bibliotecar, angajat_paznic, biblioteca
(contine 2 vectori, unul de angajati_bibliotecari si altul de angajati_paznici),
biblioteca_scolara (derivata din biblioteca), manual (derivata din carte),
elev (contine un vector de carti)
**/

//sursa pentru aceasta functie: http://www.cplusplus.com/articles/LvbCpfjN/
void setcolor (unsigned short color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon,color);
}

///CLASA AUTOR
class autor
{
private:

    char* prenume;
    string nume;
    int nr_carti_publicate;
    string* nume_carti_publicate;
    int* ani_publicari;

public:

    autor();
    autor(char* prenume, string nume);
    autor(char* prenume, string nume, int nr_carti_publicate,
          string* nume_carti_publicate, int* ani_publicari);
    ~autor();
    autor (const autor& a);

    autor& operator=(const autor& a);
    friend ostream& operator<<(ostream& out,const autor& a);
    friend istream& operator>>(istream& in, autor& a);
    friend ofstream& operator<<(ofstream& out,const autor& a);
    friend ifstream& operator>>(ifstream& in, autor& a);
    bool operator==(const autor& a);
    bool operator >= (const autor& a);
    int operator[](int index);
    explicit operator string();

    string get_nume();
    void set_nume(string nume);
    char* get_prenume();
    void set_prenume(char* prenume);
    int get_nr_carti_publicate();
    void set_nr_carti_publicate(int nr_carti_publicate);
    string* get_nume_carti_publicate();
    void set_nume_carti_publicate(string* nume_carti_publicate, int nr_carti);
    int* get_ani_publicari();
    void set_ani_publicari(int* ani_publicari, int nr_carti);

    void numar_carti_perioada(int an1,int an2);
};

/**functionalitate: functie care afiseaza numarul de carti
scrise de un autor intr-o perioada de timp (determinata de 2 ani)**/
void autor::numar_carti_perioada (int an1,int an2)
{
    cout<<"In perioada "<<an1<<"-"<<an2;
    int nr=0;
    for (int j=0; j<this->nr_carti_publicate; ++j)
        if (this->ani_publicari[j]>=an1&&this->ani_publicari[j]<=an2)
            ++nr;
    cout<<", autorul "<<this->prenume<<" "<<this->nume<<" a scris "<<nr<<" carti\n";
}

///OPERATORI
autor::operator string()
{
    return this->nume;
}

bool autor::operator==(const autor& a)
{
    if (strcmp(this->prenume,a.prenume)==0 && this->nume==a.nume)
        return 1;
    return 0;
}

bool autor::operator >= (const autor& a)
{
    if (this->nr_carti_publicate>=a.nr_carti_publicate)
        return 1;
    return 0;
}

int autor::operator[](int index)
{
    if (0<=index && index<this->nr_carti_publicate)
        return this->ani_publicari[index];
    else
        return -1;
}

ostream& operator<<(ostream& out,const autor& a)
{
    out<<"Prenume: "<<a.prenume<<'\n';
    out<<'\n';
    out<<"Nume: "<<a.nume<<'\n';
    out<<'\n';
    out<<"Numar carti publicate: "<<a.nr_carti_publicate<<'\n';
    out<<'\n';
    out<<"Carti publicate:\n";
    for (int i=0; i<a.nr_carti_publicate; ++i)
        out<<a.nume_carti_publicate[i]<<" - "<<a.ani_publicari[i]<<'\n';
    return out;
}

istream& operator>>(istream& in, autor& a)
{
    cout<<"Introduceti prenumele:\n";
    char aux[100];
    in.getline(aux,100);
    if (a.prenume!=NULL)
        delete[] a.prenume;
    a.prenume=new char[strlen(aux)+1];
    strcpy(a.prenume,aux);
    cout<<"Introduceti numele:\n";
    in>>a.nume;
    cout<<"Introduceti numarul de carti publicate:\n";
    in>>a.nr_carti_publicate;
    cout<<"Introduceti numele cartilor publicate:\n";
    if (a.nume_carti_publicate!=NULL)
        delete[] a.nume_carti_publicate;
    a.nume_carti_publicate=new string[a.nr_carti_publicate];
    in.get();
    for (int i=0; i<a.nr_carti_publicate; ++i)
    {
        in.getline(aux,100);
        string s(aux);
        a.nume_carti_publicate[i]=s;
    }
    cout<<"Introduceti anii publicarii cartilor:\n";
    if (a.ani_publicari!=NULL)
        delete[] a.ani_publicari;
    a.ani_publicari=new int[a.nr_carti_publicate];
    for (int i=0; i<a.nr_carti_publicate; ++i)
        in>>a.ani_publicari[i];
    return in;
}

ofstream& operator<<(ofstream& out,const autor& a)
{
    out<<"Prenume: "<<a.prenume<<'\n';
    out<<'\n';
    out<<"Nume: "<<a.nume<<'\n';
    out<<'\n';
    out<<"Numar carti publicate: "<<a.nr_carti_publicate<<'\n';
    out<<'\n';
    out<<"Carti publicate:\n";
    for (int i=0; i<a.nr_carti_publicate; ++i)
        out<<a.nume_carti_publicate[i]<<" - "<<a.ani_publicari[i]<<'\n';
    return out;
}

ifstream& operator>>(ifstream& in, autor& a)
{
    char aux[100];
    in.getline(aux,100);
    if (a.prenume!=NULL)
        delete[] a.prenume;
    a.prenume=new char[strlen(aux)+1];
    strcpy(a.prenume,aux);
    in>>a.nume;
    in>>a.nr_carti_publicate;
    if (a.nume_carti_publicate!=NULL)
        delete[] a.nume_carti_publicate;
    a.nume_carti_publicate=new string[a.nr_carti_publicate];
    in.get();
    for (int i=0; i<a.nr_carti_publicate; ++i)
    {
        in.getline(aux,100);
        string s(aux);
        a.nume_carti_publicate[i]=s;
    }
    if (a.ani_publicari!=NULL)
        delete[] a.ani_publicari;
    a.ani_publicari=new int[a.nr_carti_publicate];
    for (int i=0; i<a.nr_carti_publicate; ++i)
        in>>a.ani_publicari[i];
    return in;
}
autor& autor ::operator=(const autor& a)
{
    if (this!=&a)
    {
        if (this->prenume!=NULL)
            delete[] this->prenume;
        if (this->nume_carti_publicate!=NULL)
            delete[] this->nume_carti_publicate;
        if (this->ani_publicari!=NULL)
            delete[] this->ani_publicari;
        this->prenume=new char[strlen(a.prenume)+1];
        strcpy(this->prenume, a.prenume);
        this->nume=a.nume;
        this->nr_carti_publicate=a.nr_carti_publicate;
        this->nume_carti_publicate=new string[a.nr_carti_publicate];
        for (int i=0; i<a.nr_carti_publicate; ++i)
            this->nume_carti_publicate[i]=a.nume_carti_publicate[i];
        this->ani_publicari=new int[a.nr_carti_publicate];
        for (int i=0; i<a.nr_carti_publicate; ++i)
            this->ani_publicari[i]=a.ani_publicari[i];
    }
    return *this;
}

///CONSTRUCTORI, DESTRUCTORI
autor::autor()
{
    this->prenume=new char[2];
    strcpy(this->prenume,"-");
    this->nume="-";
    this->nr_carti_publicate=0;
    this->nume_carti_publicate=NULL;
    this->ani_publicari=NULL;
}

autor::autor(char* prenume, string nume)
{
    this->prenume=new char[strlen(prenume)+1];
    strcpy(this->prenume, prenume);
    this->nume=nume;
    this->nr_carti_publicate=0;
    this->nume_carti_publicate=NULL;
    this->ani_publicari=NULL;
}

autor::autor(char* prenume, string nume, int nr_carti_publicate,
             string* nume_carti_publicate,int* ani_publicari)
{
    this->prenume=new char[strlen(prenume)+1];
    strcpy(this->prenume, prenume);
    this->nume=nume;
    this->nr_carti_publicate=nr_carti_publicate;
    this->nume_carti_publicate=new string[nr_carti_publicate];
    for (int i=0; i<nr_carti_publicate; ++i)
        this->nume_carti_publicate[i]=nume_carti_publicate[i];
    this->ani_publicari=new int[nr_carti_publicate];
    for (int i=0; i<nr_carti_publicate; ++i)
        this->ani_publicari[i]=ani_publicari[i];
}

autor::~autor()
{
    if (this->prenume!=NULL)
        delete[] this->prenume;
    if (this->nume_carti_publicate!=NULL)
        delete[] this->nume_carti_publicate;
    if (this->ani_publicari!=NULL)
        delete[] this->ani_publicari;
}

autor::autor(const autor& a)
{
    this->prenume=new char[strlen(a.prenume)+1];
    strcpy(this->prenume, a.prenume);
    this->nume=a.nume;
    this->nr_carti_publicate=a.nr_carti_publicate;
    this->nume_carti_publicate=new string[a.nr_carti_publicate];
    for (int i=0; i<a.nr_carti_publicate; ++i)
        this->nume_carti_publicate[i]=a.nume_carti_publicate[i];
    this->ani_publicari=new int[a.nr_carti_publicate];
    for (int i=0; i<a.nr_carti_publicate; ++i)
        this->ani_publicari[i]=a.ani_publicari[i];
}

///SETTERS, GETTERS
string autor::get_nume()
{
    return this->nume;
}

void autor::set_nume(string nume)
{
    this->nume=nume;
}

char* autor::get_prenume()
{
    return this->prenume;
}

void autor::set_prenume(char* prenume)
{
    if (this->prenume!=NULL)
        delete[] this->prenume;
    this->prenume=new char[strlen(prenume)+1];
    strcpy(this->prenume,prenume);
}

int autor::get_nr_carti_publicate()
{
    return this->nr_carti_publicate;
}

void autor::set_nr_carti_publicate(int nr_carti_publicate)
{
    this->nr_carti_publicate=nr_carti_publicate;
}

string* autor::get_nume_carti_publicate()
{
    return this->nume_carti_publicate;
}

void autor::set_nume_carti_publicate(string* nume_carti_publicate,int nr_carti)
{
    if (this->nume_carti_publicate!=NULL)
        delete[] this->nume_carti_publicate;
    this->nr_carti_publicate=nr_carti;
    this->nume_carti_publicate=new string[nr_carti];
    for (int i=0; i<nr_carti; ++i)
        this->nume_carti_publicate[i]=nume_carti_publicate[i];
}

int* autor::get_ani_publicari()
{
    return this->ani_publicari;
}

void autor::set_ani_publicari(int* ani_publicari, int nr_carti)
{
    if (this->ani_publicari!=NULL)
        delete[] this->ani_publicari;
    this->nr_carti_publicate=nr_carti;
    this->ani_publicari=new int[nr_carti];
    for (int i=0; i<nr_carti; ++i)
        this->ani_publicari[i]=ani_publicari[i];
}



///CLASA CARTE (relatie has a - obiect de tip autor)
class carte
{
protected:

    string nume;
    autor autor_carte;
    int nr_exemplare;
    float pret;
    string* conditie_exemplare;
    bool* imprumuturi;
    string editura;

public:

    carte();
    carte(string nume, autor autor_carte,string editura, float pret);
    carte(string nume, autor autor_carte, string editura, float pret,
          int nr_exemplare, string* conditie_exemplare, bool* imprumuturi);
    ~carte();
    carte(const carte& c);

    carte& operator=(const carte& c);
    friend ostream& operator<<(ostream& out,const carte& c);
    friend istream& operator>>(istream& in, carte& c);
    friend ofstream& operator<<(ofstream& out,const carte& c);
    friend ifstream& operator>>(ifstream& in, carte& c);
    const carte& operator++();//pre
    const carte operator++(int);//post
    bool operator==(const carte& c);
    bool operator<(const carte& c);
    string operator[](int index);
    explicit operator int();
    carte operator-(int x);

    string get_nume();
    void set_nume(string nume);
    autor get_autor_carte();
    void set_autor_carte(autor autor_carte);
    int get_nr_exemplare();
    void set_nr_exemplare(int nr_exemplare);
    float get_pret();
    void set_pret(float pret);
    string* get_conditie_exemplare();
    void set_conditie_exemplare(string* conditie_exemplare, int nr_exemplare);
    bool* get_imprumuturi();
    void set_imprumuturi(bool* imprumuturi, int nr_exemplare);
    string get_editura();
    void set_editura(string editura);

    void disponibilitate();

};

/**functionalitate: functie care afiseaza pentru o carte
numarul de exemplare disponibile si numarul de exemplare imprumutate**/
void carte::disponibilitate ()
{
    int nrimp=0,nrdis=0;
    for (int j=0; j<this->nr_exemplare; ++j)
        if (this->imprumuturi[j]==1)
            nrimp++;
        else
            nrdis++;
    cout<<"Pentru cartea "<<this->nume;
    if (nrdis==0)
        cout<<" nu este disponibil niciun volum si ";
    else
        if (nrdis==1)
            cout<<" este disponibil un volum si ";
        else
            cout<<" sunt disponibile "<<nrdis<<" volume si ";
    if (nrimp==0)
        cout<<"nu este imprumutat niciunul.\n";
    else
        if (nrimp==1)
            cout<<"este imprumutat un volum.\n";
        else
            cout<<"sunt imprumutate "<<nrimp<<" volume.\n";
}

///OPERATORI
carte carte::operator-(int x)
{
    carte aux(*this);
    if (x<=aux.pret)
        aux.pret=aux.pret-x;
    else
        aux.pret=0;
    return aux;

}
carte::operator int()
{
    return this->pret;
}

bool carte::operator==(const carte& c)
{
    if (this->autor_carte==c.autor_carte && this->nume==c.nume)
        return 1;
    return 0;
}

bool carte::operator<(const carte& c)
{
    if (this->pret<c.pret)
        return 1;
    return 0;
}
string carte::operator[](int index)
{
    if (0<=index && index<this->nr_exemplare)
        return this->conditie_exemplare[index];
    else
        return "gresit";
}

const carte& carte::operator++()
{
    this->pret=this->pret+1;
    return *this;
}

const carte carte::operator++(int)
{
    carte aux(*this);
    this->pret=this->pret+1;
    return aux;
}

ostream& operator<<(ostream& out,const carte& c)
{
    out<<"Numele cartii: "<<c.nume<<'\n';
    out<<"Autorul cartii:";
    autor a;
    a=c.autor_carte;
    out<<a.get_prenume()<<" "<<a.get_nume();
    out<<"\nPret: "<<c.pret<<'\n';
    out<<"Editura: "<<c.editura<<'\n';
    out<<"Numar exemplare: "<<c.nr_exemplare<<'\n';
    out<<"Conditia exemplalelor:\n";
    for (int i=0; i<c.nr_exemplare; ++i)
        out<<i+1<<". "<<c.conditie_exemplare[i]<<'\n';
    out<<"Exemplarele imprumutate\n";
    for (int i=0; i<c.nr_exemplare; ++i)
    {
        out<<i+1<<". ";
        if (c.imprumuturi[i]==1)
            out<<"imprumutat\n";
        else
            out<<"neimprumutat\n";
    }
    return out;
}

istream& operator>>(istream& in, carte& c)
{
    char aux1[100];
    char aux[100];
    cout<<"Introduceti numele autorului:\n";
    in>>aux1;
    in.get();
    string s1(aux1);
    cout<<"Introduceti prenumele autorului:\n";
    cin.getline(aux,100);
    autor a(aux,s1);
    c.autor_carte=a;
    cout<<"Introduceti numele cartii:\n";
    in.getline(aux,100);
    string s(aux);
    c.nume=s;
    cout<<"Introduceti pretul:\n";
    in>>c.pret;
    in.get();
    cout<<"Introduceti editura:\n";
    in.getline(aux,100);
    string s2(aux);
    c.editura=s2;
    cout<<"Intoduceti numarul de exemplare:\n";
    in>>c.nr_exemplare;
    cout<<"Introduceti starea cartii pentru fiecare exemplar (noua, uzata):\n";
    if (c.conditie_exemplare!=NULL)
        delete[] c.conditie_exemplare;
    c.conditie_exemplare=new string[c.nr_exemplare];
    for (int i=0; i<c.nr_exemplare; ++i)
        in>>c.conditie_exemplare[i];
    cout<<"Introduceti pentru fiecare exemplar daca este imprumutat (1-da/0-nu):\n";
    if (c.imprumuturi!=NULL)
        delete[] c.imprumuturi;
    c.imprumuturi=new bool[c.nr_exemplare];
    for (int i=0; i<c.nr_exemplare; ++i)
        in>>c.imprumuturi[i];
    return in;
}

ofstream& operator<<(ofstream& out,const carte& c)
{
    out<<"Numele cartii: "<<c.nume<<'\n';
    out<<"Autorul cartii:";
    autor a;
    a=c.autor_carte;
    out<<a.get_prenume()<<" "<<a.get_nume();
    out<<"\nPret: "<<c.pret<<'\n';
    out<<"Editura: "<<c.editura<<'\n';
    out<<"Numar exemplare: "<<c.nr_exemplare<<'\n';
    out<<"Conditia exemplalelor:\n";
    for (int i=0; i<c.nr_exemplare; ++i)
        out<<i+1<<". "<<c.conditie_exemplare[i]<<'\n';
    out<<"Exemplarele imprumutate\n";
    for (int i=0; i<c.nr_exemplare; ++i)
    {
        out<<i+1<<". ";
        if (c.imprumuturi[i]==1)
            out<<"imprumutat\n";
        else
            out<<"neimprumutat\n";
    }
    return out;
}

ifstream& operator>>(ifstream& in, carte& c)
{
    char aux[100];
    in.getline(aux,100);
    string s(aux);
    c.nume=s;
    in.getline(aux,100);
    char aux1[100];
    in.getline(aux1,100);
    string s1(aux1);
    autor a(aux,s1);
    c.autor_carte=a;
    in>>c.pret;
    in.get();
    in.getline(aux,100);
    string s2(aux);
    c.editura=s2;
    in>>c.nr_exemplare;
    if (c.conditie_exemplare!=NULL)
        delete[] c.conditie_exemplare;
    c.conditie_exemplare=new string[c.nr_exemplare];
    for (int i=0; i<c.nr_exemplare; ++i)
        in>>c.conditie_exemplare[i];
    if (c.imprumuturi!=NULL)
        delete[] c.imprumuturi;
    c.imprumuturi=new bool[c.nr_exemplare];
    for (int i=0; i<c.nr_exemplare; ++i)
        in>>c.imprumuturi[i];
    in.get();
    return in;
}

carte& carte::operator=(const carte& c)
{
    if (this!=&c)
    {
        if (this->imprumuturi!=NULL)
            delete[] this->imprumuturi;
        if (this->conditie_exemplare!=NULL)
            delete[] this->conditie_exemplare;
        this->nume=c.nume;
        this->autor_carte=c.autor_carte;
        this->editura=c.editura;
        this->pret=c.pret;
        this->nr_exemplare=c.nr_exemplare;
        this->conditie_exemplare=new string[c.nr_exemplare];
        for (int i=0; i<c.nr_exemplare; ++i)
            this->conditie_exemplare[i]=c.conditie_exemplare[i];
        this->imprumuturi=new bool[c.nr_exemplare];
        for (int i=0; i<c.nr_exemplare; ++i)
            this->imprumuturi[i]=c.imprumuturi[i];
    }
    return *this;
}

///CONSTRUCTORI, DESTRUCTORI
carte::carte()
{
    autor a;
    this->autor_carte=a;
    this->nume="-";
    this->nr_exemplare=0;
    this->pret=0;
    this->conditie_exemplare=NULL;
    this->imprumuturi=NULL;
    this->editura="-";
}

carte::carte(string nume, autor autor_carte, string editura, float pret)
{
    this->nume=nume;
    this->autor_carte=autor_carte;
    this->editura=editura;
    this->nr_exemplare=0;
    this->pret=pret;
    this->conditie_exemplare=NULL;
    this->imprumuturi=NULL;
}

carte::carte(string nume,autor autor_carte,string editura,float pret,
             int nr_exemplare, string* conditie_exemplare, bool* imprumuturi)
{
    this->nume=nume;
    this->autor_carte=autor_carte;
    this->editura=editura;
    this->pret=pret;
    this->nr_exemplare=nr_exemplare;
    this->conditie_exemplare=new string[nr_exemplare];
    for (int i=0; i<nr_exemplare; ++i)
        this->conditie_exemplare[i]=conditie_exemplare[i];
    this->imprumuturi=new bool[nr_exemplare];
    for (int i=0; i<nr_exemplare; ++i)
        this->imprumuturi[i]=imprumuturi[i];
}

carte::~carte()
{
    if (this->imprumuturi!=NULL)
        delete[] this->imprumuturi;
    if (this->conditie_exemplare!=NULL)
        delete[] this->conditie_exemplare;
}
carte::carte(const carte& c)
{
    this->nume=c.nume;
    this->autor_carte=c.autor_carte;
    this->editura=c.editura;
    this->pret=c.pret;
    this->nr_exemplare=c.nr_exemplare;
    this->conditie_exemplare=new string[c.nr_exemplare];
    for (int i=0; i<c.nr_exemplare; ++i)
        this->conditie_exemplare[i]=c.conditie_exemplare[i];
    this->imprumuturi=new bool[c.nr_exemplare];
    for (int i=0; i<c.nr_exemplare; ++i)
        this->imprumuturi[i]=c.imprumuturi[i];
}

///SETTERS, GETTERS
string carte::get_nume()
{
    return this->nume;
}

void carte::set_nume(string nume)
{
    this->nume=nume;
}

autor carte::get_autor_carte()
{
    return this->autor_carte;
}

void carte::set_autor_carte(autor autor_carte)
{
    this->autor_carte=autor_carte;
}

int carte::get_nr_exemplare()
{
    return this->nr_exemplare;
}

void carte::set_nr_exemplare(int nr_exemplare)
{
    this->nr_exemplare=nr_exemplare;
}

float carte::get_pret()
{
    return this->pret;
}

void carte::set_pret(float pret)
{
    this->pret=pret;
}

string* carte::get_conditie_exemplare()
{
    return this->conditie_exemplare;
}

void carte::set_conditie_exemplare(string* conditie_exemplare, int nr_exemplare)
{
    if (this->conditie_exemplare!=NULL)
        delete[] this->conditie_exemplare;
    this->nr_exemplare=nr_exemplare;
    this->conditie_exemplare=new string[nr_exemplare];
    for (int i=0; i<nr_exemplare; ++i)
        this->conditie_exemplare[i]=conditie_exemplare[i];
}

bool* carte::get_imprumuturi()
{
    return this->imprumuturi;
}

void carte::set_imprumuturi(bool* imprumuturi, int nr_exemplare)
{
    if (this->imprumuturi!=NULL)
        delete[] this->imprumuturi;
    this->nr_exemplare=nr_exemplare;
    this->imprumuturi=new bool[nr_exemplare];
    for (int i=0; i<nr_exemplare; ++i)
        this->imprumuturi[i]=imprumuturi[i];
}

string carte::get_editura()
{
    return this->editura;
}

void carte::set_editura(string editura)
{
    this->editura=editura;
}



///CLASA MANUAL (derivata din clasa carte)
class manual: public carte
{
private:
    string materie;
public:
    manual();
    manual(string nume,autor autor_carte,string editura,float pret,
           int nr_exemplare, string* conditie_exemplare, bool* imprumuturi, string materie);
    manual (const manual& man);
    manual& operator=(const manual&man);
    ~manual();
    string get_materie(){return this->materie;}
    void set_materie(string materie){this->materie=materie;}

    friend istream& operator>>(istream& in, manual&man);
    friend ostream& operator<<(ostream& out, const manual&man);

    friend ifstream& operator>>(ifstream& in, manual&man);
    friend ofstream& operator<<(ofstream& out, const manual&man);

    void nevoie_inlocuire();
};

/**FUNCTIONALITATE: afiseaza pentru un manual cate exemplare
trebuie inlocuite (sunt uzate)**/
void manual::nevoie_inlocuire()
{
    int nr=0;
    for (int i=0; i<this->nr_exemplare; ++i)
        if (this->conditie_exemplare[i]=="uzata")
            ++nr;
    cout<<"Dintr-un total de "<<this->nr_exemplare<<" exemplare din manualul pentru materia "<<this->materie<<", ";
    if (nr==1)
        cout<<"trebuie inlocuit unul.\n";
    else if (nr==0)
        cout<<"nu trebuie inlocuit niciunul.\n";
    else
        cout<<"trebuie inlocuite "<<nr<<".\n";

}

///OPERATORI
istream& operator>>(istream& in, manual&man)
{
    in>>(carte&)man;
    cout<<"Introduceti materia:\n";
    in>>man.materie;
    in.get();
    return in;
}

ostream& operator<<(ostream& out, const manual&man)
{
    out<<(carte&)man;
    out<<"Materia: "<<man.materie<<"\n";
    return out;
}

ifstream& operator>>(ifstream& in, manual&man)
{
    in>>(carte&)man;
    in>>man.materie;
    return in;
}

ofstream& operator<<(ofstream& out, const manual&man)
{
    out<<(carte&)man;
    out<<"Materia: "<<man.materie<<'\n';
    return out;
}

manual& manual::operator=(const manual&man)
{
    if (this!=&man)
    {
        carte::operator=(man);
        this->materie=man.materie;
    }
    return *this;
}

///CONSTRUCTORI, DESTRUCTOR
manual::manual():carte()
{
    this->materie="-";
}

manual::manual(string nume,autor autor_carte,string editura,float pret,
               int nr_exemplare, string* conditie_exemplare, bool* imprumuturi, string materie):
    carte(nume,autor_carte,editura,pret,nr_exemplare,conditie_exemplare,imprumuturi)
{
    this->materie=materie;
}

manual::manual(const manual& man): carte(man)
{
    this->materie=man.materie;
}

manual::~manual() {}



///INTERFATA
class impozit
{
public:
    virtual float calculeaza_impozit()=0;
};



///CLASA ABSTRACTA
class angajat: public impozit
{
protected:
    string nume;
    string prenume;
    float salariu;
    float impozit;
public:
    angajat();
    angajat(string nume,string prenume,float salariu, float impozit);
    angajat& operator=(const angajat& ang);
    angajat(const angajat& ang);
    ~angajat();

    virtual ostream& afisare_virtuala(ostream& out)const;
    virtual istream& citire_virtuala (istream& in);
    friend istream& operator>>(istream & in,angajat& ang);
    friend ostream& operator<<(ostream & out,const angajat& ang);

    virtual ofstream& afisare_virtuala(ofstream& out)const;
    virtual ifstream& citire_virtuala (ifstream& in);
    friend ifstream& operator>>(ifstream & in,angajat& ang);
    friend ofstream& operator<<(ofstream & out,const angajat& ang);

    virtual void calculeaza_salariu_impozit()=0;
    string get_nume()
    {
        return this->nume;
    }
    string get_prenume()
    {
        return this->prenume;
    }
    float get_salariu()
    {
        return this->salariu;
    }
};

///OPERATORI
ostream& angajat::afisare_virtuala(ostream& out) const
{
    out<<"\nNumele angajatului este: "<<this->nume;
    out<<"\nPrenumele angajatului este: "<<this->prenume;
    out<<"\nSalariul angajatului este: "<<this->salariu;
    out<<"\nImpozitul din salariu este de: "<<this->impozit<<"%";
    return out;
}

istream& angajat::citire_virtuala(istream& in)
{
    cout<<"Numele angajatului este:\n";
    in>>this->nume;
    char aux[100];
    cout<<"Prenumele angajatului este:\n";
    in.get();
    in.getline(aux,100);
    string s1(aux);
    this->prenume=s1;
    cout<<"Salariul angajatului este:\n";
    in>>this->salariu;
    cout<<"Impozitul din salariu este de (%):\n";
    in>>this->impozit;
    return in;
}

istream& operator>> (istream& in, angajat& ang)
{
    return ang.citire_virtuala(in);
}

ostream& operator<< (ostream& out, const angajat& ang)
{
    return ang.afisare_virtuala(out);
}

ofstream& angajat::afisare_virtuala(ofstream& out) const
{
    out<<"\nNumele angajatului este: "<<this->nume;
    out<<"\nPrenumele angajatului este: "<<this->prenume;
    out<<"\nSalariul angajatului este: "<<this->salariu;
    out<<"\nImpozitul din salariu este de: "<<this->impozit<<"%";
    return out;
}

ifstream& angajat::citire_virtuala(ifstream& in)
{
    in>>this->nume;
    char aux[100];
    in.get();
    in.getline(aux,100);
    string s1(aux);
    this->prenume=s1;
    in>>this->salariu;
    in>>this->impozit;
    return in;
}

ifstream& operator>> (ifstream& in, angajat& ang)
{
    return ang.citire_virtuala(in);
}

ofstream& operator<< (ofstream& out, const angajat& ang)
{
    return ang.afisare_virtuala(out);
}

angajat& angajat::operator=(const angajat& ang)
{
    if (this!=&ang)
    {
        this->nume=ang.nume;
        this->prenume=ang.prenume;
        this->salariu=ang.salariu;
        this->impozit=ang.impozit;
    }
    return *this;
}

///CONSTRUCTORI, DESTRUCTOR
angajat::angajat()
{
    this->nume="-";
    this->prenume="-";
    this->salariu=0;
    this->impozit=0;
}

angajat::angajat(string nume,string prenume,float salariu, float impozit)
{
    this->nume=nume;
    this->prenume=prenume;
    this->salariu=salariu;
    this->impozit=impozit;
}

angajat::angajat (const angajat& ang)
{
    this->nume=ang.nume;
    this->prenume=ang.prenume;
    this->salariu=ang.salariu;
    this->impozit=ang.impozit;
}

angajat::~angajat() {}



///CLASA ANGAJAT_BIBLIOTECAR (derivata din angajat)
class angajat_bibliotecar: public angajat
{
private:
    string data_absolvirii_facultate;
public:
    angajat_bibliotecar();
    angajat_bibliotecar(string nume, string prenume, float salariu, float impozit,
                        string data_absolvirii_facultate);
    angajat_bibliotecar(const angajat_bibliotecar& bibl);
    angajat_bibliotecar& operator= (const angajat_bibliotecar& bibl);
    ~angajat_bibliotecar();

    virtual ostream& afisare_virtuala(ostream& out) const;
    virtual istream& citire_virtuala(istream& in);

    virtual ofstream& afisare_virtuala(ofstream& out) const;
    virtual ifstream& citire_virtuala(ifstream& in);

    float calculeaza_impozit()
    {
        return this->salariu*(this->impozit/100);
    }
    void calculeaza_salariu_impozit()
    {
        ///bibliotecarii primesc inapoi 10% din impozit
        cout<<"Salariul dupa plata impozitului este: "<<this->salariu-this->calculeaza_impozit()*0.9<<'\n';
    }
};

///OPERATORI
istream& angajat_bibliotecar::citire_virtuala(istream& in)
{
    angajat::citire_virtuala(in);
    cout<<"Data absolvirii facultatii este:\n";
    in>>this->data_absolvirii_facultate;
    return in;
}

ostream& angajat_bibliotecar::afisare_virtuala(ostream& out) const
{
    angajat::afisare_virtuala(out);
    out<<"\nData absolvirii facultatii este: "<<this->data_absolvirii_facultate;
    return out;
}

ifstream& angajat_bibliotecar::citire_virtuala(ifstream& in)
{
    angajat::citire_virtuala(in);
    in>>this->data_absolvirii_facultate;
    return in;
}

ofstream& angajat_bibliotecar::afisare_virtuala(ofstream& out) const
{
    angajat::afisare_virtuala(out);
    out<<"\nData absolvirii facultatii este: "<<this->data_absolvirii_facultate;
    return out;
}

angajat_bibliotecar& angajat_bibliotecar::operator=(const angajat_bibliotecar& bibl)
{
    if (this!=&bibl)
    {
        angajat::operator=(bibl);
        this->data_absolvirii_facultate=bibl.data_absolvirii_facultate;
    }
    return *this;
}

///CONSTRUCTORI, DESTRUCTOR
angajat_bibliotecar::angajat_bibliotecar():angajat()
{
    this->data_absolvirii_facultate="ZZ/LL/AAAA";
}

angajat_bibliotecar::angajat_bibliotecar(string nume, string prenume, float salariu,
        float impozit, string data_absolvirii_facultate): angajat(nume,prenume,salariu,impozit)
{
    this->data_absolvirii_facultate=data_absolvirii_facultate;
}

angajat_bibliotecar::angajat_bibliotecar(const angajat_bibliotecar& bibl):angajat(bibl)
{
    this->data_absolvirii_facultate=bibl.data_absolvirii_facultate;
}

angajat_bibliotecar::~angajat_bibliotecar() {}



///CLASA ANGAJAT_PAZNIC (derivata din angajat)
class angajat_paznic: public angajat
{
private:
    string data_obtinere_atestat;
    string data_expirare_atestat;
public:
    angajat_paznic();
    angajat_paznic(string nume, string prenume, float salariu, float impozit,
                   string data_obtinere_atestat, string data_expirare_atestat);
    angajat_paznic(const angajat_paznic& paz);
    angajat_paznic& operator= (const angajat_paznic& paz);
    ~angajat_paznic();

    virtual ostream& afisare_virtuala(ostream& out) const;
    virtual istream& citire_virtuala(istream& in);

    virtual ofstream& afisare_virtuala(ofstream& out) const;
    virtual ifstream& citire_virtuala(ifstream& in);

    float calculeaza_impozit()
    {
        return this->salariu*(this->impozit/100);
    }
    void calculeaza_salariu_impozit()
    {
        ///paznicii primesc inapoi 5% din impozit
        cout<<"Salariul dupa plata impozitului este: "<<this->salariu-this->calculeaza_impozit()*0.95;
    }
};

///OPERATORI
istream& angajat_paznic::citire_virtuala(istream& in)
{
    angajat::citire_virtuala(in);
    cout<<"Data obtinerii atesatului de paza este:\n";
    in>>this->data_obtinere_atestat;
    cout<<"Data expirarii atesatului de paza este:\n";
    in>>this->data_expirare_atestat;
    return in;
}

ostream& angajat_paznic::afisare_virtuala(ostream& out) const
{
    angajat::afisare_virtuala(out);
    cout<<"\nData obtinerii atesatului de paza este: "<<this->data_obtinere_atestat;
    cout<<"\nData expirarii atesatului de paza este: "<<this->data_expirare_atestat;
    return out;
}

ifstream& angajat_paznic::citire_virtuala(ifstream& in)
{
    angajat::citire_virtuala(in);
    in>>this->data_obtinere_atestat;
    in>>this->data_expirare_atestat;
    return in;
}

ofstream& angajat_paznic::afisare_virtuala(ofstream& out) const
{
    angajat::afisare_virtuala(out);
    out<<"\nData obtinerii atesatului de paza este: "<<this->data_obtinere_atestat;
    out<<"\nData expirarii atesatului de paza este: "<<this->data_expirare_atestat;
    return out;
}


angajat_paznic& angajat_paznic::operator=(const angajat_paznic& paz)
{
    if (this!=&paz)
    {
        angajat::operator=(paz);
        this->data_obtinere_atestat=paz.data_obtinere_atestat;
        this->data_expirare_atestat=paz.data_expirare_atestat;
    }
    return *this;
}

///CONSTRUCTORI, DESTRUCTOR
angajat_paznic::angajat_paznic():angajat()
{
    this->data_obtinere_atestat="ZZ/LL/AAAA";
    this->data_expirare_atestat="ZZ/LL/AAAA";
}

angajat_paznic::angajat_paznic(string nume, string prenume, float salariu,
                               float impozit, string data_obtinere_atestat, string data_expirare_atestat): angajat(nume,prenume,salariu,impozit)
{
    this->data_obtinere_atestat=data_obtinere_atestat;
    this->data_expirare_atestat=data_expirare_atestat;
}

angajat_paznic::angajat_paznic(const angajat_paznic& paz):angajat(paz)
{
    this->data_obtinere_atestat=paz.data_obtinere_atestat;
    this->data_expirare_atestat=paz.data_expirare_atestat;
}

angajat_paznic::~angajat_paznic() {}


///CLASA BIBLIOTECA
class biblioteca
{
protected:

    string nume;
    int nr_bibliotecari;
    angajat_bibliotecar* bibliotecari;
    int nr_paznici;
    angajat_paznic* paznici;
    int nr_abonati;
    int nr_carti;

public:

    biblioteca();
    biblioteca(string nume, int nr_carti);
    biblioteca(string nume, int nr_bibliotecari, angajat_bibliotecar* bibliotecari,
               int nr_paznici,angajat_paznic* paznici, int nr_abonati, int nr_carti);
    ~biblioteca();
    biblioteca (const biblioteca& b);

    biblioteca& operator=(const biblioteca& b);
    friend ostream& operator<<(ostream& out,const biblioteca& b);
    friend istream& operator>>(istream& in, biblioteca& b);
    friend ofstream& operator<<(ofstream& out,const biblioteca& b);
    friend ifstream& operator>>(ifstream& in, biblioteca& b);
    const biblioteca& operator++();//pre
    const biblioteca operator++(int);//post
    bool operator==(const biblioteca& b);
    bool operator<(const biblioteca& b);
    angajat_bibliotecar operator[](int index);
    biblioteca operator+(int x);
    biblioteca operator+(biblioteca b);
    biblioteca operator*(int x);

    string get_nume();
    void set_nume(string nume);
    int get_nr_bibliotecari();
    void set_nr_bibliotecari (int nr_bibliotecari);
    int get_nr_paznici();
    void set_nr_paznici (int nr_paznici);
    int get_nr_abonati();
    void set_nr_abonati(int nr_abonati);
    int get_nr_carti();
    void set_nr_carti(int nr_carti);
    angajat_bibliotecar* get_bibliotecari();
    void set_bibliotecari(angajat_bibliotecar* bibliotecari, int nr_bibliotecari);
    angajat_paznic* get_paznici();
    void set_paznici(angajat_paznic* paznici, int nr_paznici);

    int verifica_angajat (string nume, string prenume);
    void afisare_angajati();
};

///AFISARE TOTI ANGAJATII (vector din clasa de baza - angajat in care se pot pune obiecte din derivata)
void biblioteca::afisare_angajati()
{
    angajat* angajati[this->nr_paznici+this->nr_bibliotecari];
    int i=0;
    for (int j=0; j<this->nr_bibliotecari; ++j)
    {
        angajati[i]=new angajat_bibliotecar(bibliotecari[j]);
        ++i;
    }
    for (int j=0; j<this->nr_paznici; ++j)
    {
        angajati[i]=new angajat_paznic(paznici[j]);
        ++i;
    }
    for (int j=0; j<i; ++j)
        cout<<*angajati[j];

}

/**functionalitate: functie care verifica daca o persoana
este angajata la biblioteca (o cauta in lista de angajati)**/
int biblioteca::verifica_angajat (string nume, string prenume)
{
    for (int i=0; i<this->nr_bibliotecari; ++i)
        if (this->bibliotecari[i].get_nume()==nume&&this->bibliotecari[i].get_prenume()==prenume)
            return 1;
    for (int i=0; i<this->nr_paznici; ++i)
        if (this->paznici[i].get_nume()==nume&&this->paznici[i].get_prenume()==prenume)
            return 1;
    return 0;
}

///OPERATORI
biblioteca biblioteca::operator+ (biblioteca b)
{
    b.nr_abonati=b.nr_abonati+this->nr_abonati;
    b.nr_carti=b.nr_carti+this->nr_carti;
    return b;
}

biblioteca biblioteca::operator+(int x)
{
    biblioteca aux(*this);
    aux.nr_carti=aux.nr_carti+x;
    return aux;
}

biblioteca biblioteca::operator*(int x)
{
    biblioteca aux(*this);
    aux.nr_abonati=aux.nr_abonati*x;
    return aux;
}

angajat_bibliotecar biblioteca::operator[](int index)
{
    angajat_bibliotecar b;
    if (0<=index && index<this->nr_bibliotecari)
        return this->bibliotecari[index];
    else
        return b;
}

bool biblioteca::operator==(const biblioteca& b)
{
    if (this->nume==b.nume && this->nr_carti==b.nr_carti)
        return 1;
    return 0;
}

bool biblioteca::operator<(const biblioteca& b)
{
    if (this->nr_carti<b.nr_carti)
        return 1;
    return 0;
}

const biblioteca& biblioteca::operator++()
{
    this->nr_abonati=this->nr_abonati+1;
    return *this;
}

const biblioteca biblioteca::operator++(int)
{
    biblioteca aux(*this);
    this->nr_abonati=this->nr_abonati+1;
    return aux;
}

ostream& operator<<(ostream& out,const biblioteca& b)
{
    out<<"Nume: "<<b.nume<<'\n';
    out<<"\nNumar bibliotecari: "<<b.nr_bibliotecari<<'\n';
    out<<"Bibliotecari:";
    for (int i=0; i<b.nr_bibliotecari; ++i)
        out<<b.bibliotecari[i];
    out<<"\n\nNumar paznici: "<<b.nr_paznici<<'\n';
    out<<"Paznici:";
    for (int i=0; i<b.nr_paznici; ++i)
        out<<b.paznici[i];
    out<<"\n\nNumar abonati: "<<b.nr_abonati<<'\n';
    out<<"Numar carti: "<<b.nr_carti<<'\n';
    return out;
}

istream& operator>>(istream& in, biblioteca& b)
{
    cout<<"Introduceti numele bibliotecii:\n";
    char aux[100];
    in.getline(aux,100);
    string s(aux);
    b.nume=s;
    cout<<"Introduceti numarul de bibliotecari:\n";
    in>>b.nr_bibliotecari;
    cout<<"Introduceti date despre bibliotecari:\n";
    if (b.bibliotecari!=NULL)
        delete[] b.bibliotecari;
    b.bibliotecari=new angajat_bibliotecar[b.nr_bibliotecari];
    for (int i=0; i<b.nr_bibliotecari; ++i)
        in>>b.bibliotecari[i];
    cout<<"Introduceti numarul de paznici:\n";
    in>>b.nr_paznici;
    cout<<"Introduceti date despre paznici:\n";
    if (b.paznici!=NULL)
        delete[] b.paznici;
    b.paznici=new angajat_paznic[b.nr_paznici];
    for (int i=0; i<b.nr_paznici; ++i)
        in>>b.paznici[i];
    cout<<"Introduceti numarul de abonati:\n";
    in>>b.nr_abonati;
    cout<<"Introduceti numarul de carti:\n";
    in>>b.nr_carti;
    in.get();
    return in;
}

ofstream& operator<<(ofstream& out,const biblioteca& b)
{
    out<<"Nume: "<<b.nume<<'\n';
    out<<"\nNumar bibliotecari: "<<b.nr_bibliotecari<<'\n';
    out<<"Bibliotecari:";
    for (int i=0; i<b.nr_bibliotecari; ++i)
        out<<b.bibliotecari[i];
    out<<"\n\nNumar paznici: "<<b.nr_paznici<<'\n';
    out<<"Paznici:";
    for (int i=0; i<b.nr_paznici; ++i)
        out<<b.paznici[i];
    out<<"\n\nNumar abonati: "<<b.nr_abonati<<'\n';
    out<<"Numar carti: "<<b.nr_carti<<'\n';
    return out;
}

ifstream& operator>>(ifstream& in, biblioteca& b)
{
    char aux[100];
    in.getline(aux,100);
    string s(aux);
    b.nume=s;
    in>>b.nr_bibliotecari;
    if (b.bibliotecari!=NULL)
        delete[] b.bibliotecari;
    b.bibliotecari=new angajat_bibliotecar[b.nr_bibliotecari];
    for (int i=0; i<b.nr_bibliotecari; ++i)
        in>>b.bibliotecari[i];
    in>>b.nr_paznici;
    if (b.paznici!=NULL)
        delete[] b.paznici;
    b.paznici=new angajat_paznic[b.nr_paznici];
    for (int i=0; i<b.nr_paznici; ++i)
        in>>b.paznici[i];
    in>>b.nr_abonati;
    in>>b.nr_carti;
    in.get();
    return in;
}

biblioteca& biblioteca::operator=(const biblioteca& b)
{
    if (this!=&b)
    {
        if (this->bibliotecari!=NULL)
            delete[] this->bibliotecari;
        if (this->paznici!=NULL)
            delete[] this->paznici;
        this->nume=b.nume;
        this->nr_abonati=b.nr_abonati;
        this->nr_bibliotecari=b.nr_bibliotecari;
        this->nr_paznici=b.nr_paznici;
        this->nr_carti=b.nr_carti;
        this->bibliotecari=new angajat_bibliotecar[b.nr_bibliotecari];
        this->paznici=new angajat_paznic[b.nr_paznici];
        for (int i=0; i<b.nr_bibliotecari; ++i)
            this->bibliotecari[i]=b.bibliotecari[i];
        for (int i=0; i<b.nr_paznici; ++i)
            this->paznici[i]=b.paznici[i];
    }
    return *this;
}

///CONSTRUCTORI, DESTRUCTORI
biblioteca::biblioteca()
{
    this->nume="-";
    this->nr_abonati=0;
    this->nr_bibliotecari=0;
    this->nr_paznici=0;
    this->nr_carti=0;
    this->bibliotecari=NULL;
    this->paznici=NULL;
}

biblioteca::biblioteca(string nume, int nr_carti)
{
    this->nume=nume;
    this->nr_carti=nr_carti;
    this->nr_abonati=0;
    this->nr_bibliotecari=0;
    this->nr_paznici=0;
    this->bibliotecari=NULL;
    this->paznici=NULL;
}

biblioteca::biblioteca(string nume, int nr_bibliotecari, angajat_bibliotecar* bibliotecari,
                       int nr_paznici,angajat_paznic* paznici, int nr_abonati, int nr_carti)
{
    this->nume=nume;
    this->nr_abonati=nr_abonati;
    this->nr_bibliotecari=nr_bibliotecari;
    this->nr_paznici=nr_paznici;
    this->nr_carti=nr_carti;
    this->bibliotecari=new angajat_bibliotecar[nr_bibliotecari];
    this->paznici=new angajat_paznic[nr_paznici];
    for (int i=0; i<nr_bibliotecari; ++i)
        this->bibliotecari[i]=bibliotecari[i];
    for (int i=0; i<nr_paznici; ++i)
        this->paznici[i]=paznici[i];
}

biblioteca::~biblioteca()
{
    if (this->bibliotecari!=NULL)
        delete[] this->bibliotecari;
    if (this->paznici!=NULL)
        delete[] this->paznici;
}

biblioteca::biblioteca(const biblioteca& b)
{
    this->nume=b.nume;
    this->nr_abonati=b.nr_abonati;
    this->nr_bibliotecari=b.nr_bibliotecari;
    this->nr_paznici=b.nr_paznici;
    this->nr_carti=b.nr_carti;
    this->bibliotecari=new angajat_bibliotecar[b.nr_bibliotecari];
    this->paznici=new angajat_paznic[b.nr_paznici];
    for (int i=0; i<b.nr_bibliotecari; ++i)
        this->bibliotecari[i]=b.bibliotecari[i];
    for (int i=0; i<b.nr_paznici; ++i)
        this->paznici[i]=b.paznici[i];
}

///SETTERS, GETTERS
string biblioteca::get_nume()
{
    return this->nume;
}

void biblioteca::set_nume(string nume)
{
    this->nume=nume;
}

int biblioteca::get_nr_abonati()
{
    return this->nr_abonati;
}

void biblioteca::set_nr_abonati(int nr_abonati)
{
    this->nr_abonati=nr_abonati;
}

int biblioteca::get_nr_bibliotecari()
{
    return this->nr_bibliotecari;
}

void biblioteca::set_nr_bibliotecari(int nr_bibliotecari)
{
    this->nr_bibliotecari=nr_bibliotecari;
}

int biblioteca::get_nr_paznici()
{
    return this->nr_paznici;
}

void biblioteca::set_nr_paznici(int nr_paznici)
{
    this->nr_paznici=nr_paznici;
}

int biblioteca::get_nr_carti()
{
    return this->nr_carti;
}

void biblioteca::set_nr_carti(int nr_carti)
{
    this->nr_carti=nr_carti;
}

angajat_bibliotecar* biblioteca::get_bibliotecari()
{
    return this->bibliotecari;
}

void biblioteca::set_bibliotecari(angajat_bibliotecar* bibliotecari, int nr_bibliotecari)
{
    if (this->bibliotecari!=NULL)
        delete[] this->bibliotecari;
    this->bibliotecari=new angajat_bibliotecar[nr_bibliotecari];
    this->nr_bibliotecari=nr_bibliotecari;
    for (int i=0; i<nr_bibliotecari; ++i)
        this->bibliotecari[i]=bibliotecari[i];
}

angajat_paznic* biblioteca::get_paznici()
{
    return this->paznici;
}

void biblioteca::set_paznici(angajat_paznic* paznici, int nr_paznici)
{
    if (this->paznici!=NULL)
        delete[] this->paznici;
    this->paznici=new angajat_paznic[nr_paznici];
    this->nr_paznici=nr_paznici;
    for (int i=0; i<nr_paznici; ++i)
        this->paznici[i]=paznici[i];
}



///CLASA BIBLIOTECA_SCOLARA (derivata din biblioteca)
class biblioteca_scolara: public biblioteca
{
private:
    string scoala;
public:
    biblioteca_scolara();
    biblioteca_scolara(string nume, int nr_bibliotecari, angajat_bibliotecar* bibliotecari,
                       int nr_paznici,angajat_paznic* paznici, int nr_abonati, int nr_carti, string scoala);
    biblioteca_scolara (const biblioteca_scolara& b);
    biblioteca_scolara& operator=(const biblioteca_scolara& b);
    ~biblioteca_scolara();

    string get_scoala(){return this->scoala;}
    void set_scoala(string scoala){this->scoala=scoala;}

    friend ostream& operator<<(ostream& out, const biblioteca_scolara& b);
    friend istream& operator>>(istream& in, biblioteca_scolara& b);

    friend ofstream& operator<<(ofstream& out, const biblioteca_scolara& b);
    friend ifstream& operator>>(ifstream& in, biblioteca_scolara& b);

    void calcul_salariu();
};

/**functionalitate: calculeaza cat plateste o scoala pentru a plati salariile
angajatilor de la bibllioteca intr-o luna**/
void biblioteca_scolara::calcul_salariu()
{
    float s=0;
    for (int i=0; i<this->nr_bibliotecari; ++i)
        s=s+this->bibliotecari[i].get_salariu();
    for (int i=0; i<this->nr_paznici; ++i)
        s=s+this->paznici[i].get_salariu();
    cout<<"La biblioteca din cadrul scolii "<<this->scoala<<", salariile angajatilor pe o luna insumeaza "<<s<<" lei.\n";
}

///OPERATORI
ostream& operator<<(ostream& out, const biblioteca_scolara& b)
{
    out<<(biblioteca&)b;
    out<<"Scoala in care se afla biblioteca: "<<b.scoala<<'\n';
    return out;
}

istream& operator>>(istream& in, biblioteca_scolara& b)
{
    in>>(biblioteca&)b;
    cout<<"Introduceti scoala in care se afla biblioteca:\n";
    char aux[100];
    in.getline(aux,100);
    string s(aux);
    b.scoala=s;
    return in;
}

ofstream& operator<<(ofstream& out, const biblioteca_scolara& b)
{
    out<<(biblioteca&)b;
    out<<"Scoala in care se afla biblioteca: "<<b.scoala<<'\n';
    return out;
}

ifstream& operator>>(ifstream& in, biblioteca_scolara& b)
{
    in>>(biblioteca&)b;
    char aux[100];
    in.getline(aux,100);
    string s(aux);
    b.scoala=s;
    return in;
}

biblioteca_scolara& biblioteca_scolara::operator=(const biblioteca_scolara& b)
{
    if (this!=&b)
    {
        biblioteca::operator=(b);
        this->scoala=b.scoala;
    }
    return *this;
}

///CONSTRUCTORI, DESTRUCTOR
biblioteca_scolara::biblioteca_scolara():biblioteca()
{
    this->scoala="-";
}

biblioteca_scolara::biblioteca_scolara(string nume, int nr_bibliotecari, angajat_bibliotecar* bibliotecari,
                                       int nr_paznici,angajat_paznic* paznici, int nr_abonati, int nr_carti, string scoala):
    biblioteca(nume,nr_bibliotecari,bibliotecari,nr_paznici,paznici,nr_abonati,nr_carti)
{
    this->scoala=scoala;
}

biblioteca_scolara::biblioteca_scolara(const biblioteca_scolara& b):biblioteca(b)
{
    this->scoala=b.scoala;

}

biblioteca_scolara::~biblioteca_scolara() {}



///CLASA ELEV
class elev
{
private:

    char *nume;
    int varsta;
    double media_anuala;
    const int id_elev;
    bool bursier;
    char initiala_tata;
    string prenume;
    int perioada;
    int nr_carti_imprumutate;
    carte * carti_imprumutate;

public:

    static int contor_id;

    elev();
    elev (char *nume, string prenume);
    elev (char *nume, int varsta, double media_anuala, bool bursier, char initiala_tata,
          string prenume, int perioada, int nr_carti_imprumutate, carte *carti_imprumutate);
    ~elev();
    elev (const elev& e);

    elev& operator=(const elev& e);
    friend ostream& operator<<(ostream& out,const elev& e);
    friend istream& operator>>(istream& in, elev& e);
    friend ofstream& operator<<(ofstream& out,const elev& e);
    friend ifstream& operator>>(ifstream& in, elev& e);
    const elev& operator++();//pre
    const elev operator++(int);//post
    bool operator==(const elev& e);
    bool operator<(const elev&e) const;
    bool operator<=(const elev& e);
    carte operator[](int index);
    explicit operator double();
    elev operator/(float x);
    elev operator+(float x);

    char * get_nume();
    void set_nume(char *nume);
    int get_varsta();
    void set_varsta(int varsta);
    double get_media_anuala();
    void set_media_anuala(double media);
    int get_id_elev ();
    bool get_bursier();
    void set_bursier (bool bursier);
    string get_prenume();
    void set_prenume(string prenume);
    int get_perioada();
    void set_perioada(int perioada);
    int get_nr_carti_imprumutate();
    void set_nr_carti_imprumutate (int nr);
    carte* get_carti_imprumutate();
    void set_carti_imprumutate(carte* carti_imprumutate, int nr);

    void total_pret_carti_imprumutate();
};

int elev::contor_id=1;

/**functionalitate: functie care calculeaza si afiseaza
costul total al cartilor imprumutate de un elev**/
void elev::total_pret_carti_imprumutate()
{
    float suma=0;
    for (int i=0; i<this->nr_carti_imprumutate; ++i)
        suma=suma+this->carti_imprumutate[i].get_pret();
    cout<<"Pe o perioada de ";
    if (this->perioada==1)
        cout<<"o luna";
    else
        cout<<this->perioada<<" luni";
    cout<<", elevul "<<this->nume<<" "<<this->initiala_tata<<". "<<this->prenume;
    if (this->nr_carti_imprumutate!=0)
    {
        cout<<" a imprumutat ";
        if (this->nr_carti_imprumutate==1)
            cout<<"o carte cu o valoare totala de "<<suma<< " lei.\n";
        else
            cout<<this->nr_carti_imprumutate<<" carti cu o valoare totala de "<<suma<< " lei.\n";
    }
    else
        cout<<" nu a imprumutat nicio carte.\n";
}

///OPERATORI
elev elev::operator+(float x)
{
    elev aux(*this);
    aux.media_anuala=aux.media_anuala+x;
    return aux;
}

elev elev::operator/(float x)
{
    elev aux(*this);
    aux.media_anuala=aux.media_anuala/x;
    return aux;
}

elev::operator double()
{
    return this->media_anuala;
}

bool elev::operator==(const elev& e)
{
    if (strcmp(this->nume,e.nume)==0 && this->prenume==e.prenume && this->initiala_tata==e.initiala_tata)
        return 1;
    return 0;
}

bool elev::operator<=(const elev& e)
{
    if (this->media_anuala<=e.media_anuala)
        return 1;
    return 0;
}

bool elev::operator< (const elev&e) const
{
    if (this->id_elev<e.id_elev)
        return 1;
    return 0;
}

carte elev::operator[](int index)
{
    carte c;
    if (0<=index && index<this->nr_carti_imprumutate)
        return this->carti_imprumutate[index];
    else
        return c;
}

const elev& elev::operator++()
{
    if (this->media_anuala<10)
        this->media_anuala=this->media_anuala+0.01;
    return *this;
}

const elev elev::operator++(int)
{
    elev aux(*this);
    if (this->media_anuala<10)
        this->media_anuala=this->media_anuala+0.01;
    return aux;
}

ostream& operator<<(ostream& out,const elev& e)
{
    out<<"Id persoana: "<<e.id_elev<<'\n';
    out<<"Nume: "<<e.nume<<'\n';
    out<<"Prenume: "<<e.prenume<<'\n';
    out<<"Varsta: "<<e.varsta<<'\n';
    out<<"Initiala tata: "<<e.initiala_tata<<'\n';
    out<<"Media anuala: "<<e.media_anuala<<'\n';
    out<<"Bursier: ";
    if (e.bursier==1)
        out<<"DA"<<'\n';
    else
        out<<"NU"<<'\n';
    out<<"Pe o perioada de "<<e.perioada;
    if (e.perioada==1)
        out<<" luna, ";
    else
        out<<" luni, ";
    if (e.nr_carti_imprumutate==0)
        out<<"nu a imprumutat nicio carte\n";
    else if (e.nr_carti_imprumutate==1)
        out<<"a imprumutat o carte:\n";
    else
        out<<"a imprumutat "<<e.nr_carti_imprumutate<<" carti:\n";
    for (int i=0; i<e.nr_carti_imprumutate; ++i)
    {
        out<<e.carti_imprumutate[i].get_nume()<<" - ";
        autor x;
        x=e.carti_imprumutate[i].get_autor_carte();
        out<<x.get_prenume()<<" "<<x.get_nume();
        out<<" (Editura "<<e.carti_imprumutate[i].get_editura()<<", pret "<<e.carti_imprumutate[i].get_pret()<<")\n";
    }
    return out;
}

istream& operator>>(istream& in, elev& e)
{
    cout<<"Introduceti nume:\n";
    char aux[100];
    in>>aux;
    in.get();
    if (e.nume!=NULL)
        delete[] e.nume;
    e.nume=new char[strlen(aux)+1];
    strcpy(e.nume,aux);
    cout<<"Introduceti prenume:\n";
    in.getline(aux,100);
    string s(aux);
    e.prenume=s;
    cout<<"Introduceti varsta:\n";
    in>>e.varsta;
    cout<<"Introduceti initiala tatalui:\n";
    in>>e.initiala_tata;
    cout<<"Introduceti media anuala:\n";
    in>>e.media_anuala;
    cout<<"Introduceti daca este bursier (1-da/0-nu):\n";
    in>>e.bursier;
    cout<<"Introduceti numarul de luni pentru care se retin date:\n";
    in>>e.perioada;
    cout<<"Introduceti numarul de carti imprumutate:\n";
    in>>e.nr_carti_imprumutate;
    if (e.carti_imprumutate!=NULL)
        delete[] e.carti_imprumutate;
    e.carti_imprumutate=new carte[e.nr_carti_imprumutate];
    in.get();
    cout<<"Introduceti cartile imprumutate:\n";
    for (int i=0; i<e.nr_carti_imprumutate; ++i)
    {
        cout<<"\nCartea cu numarul "<<i+1<<'\n';
        cout<<"Numele cartii:\n";
        char aux1[100];
        in.getline(aux1,100);
        string s1(aux1);
        cout<<"Prenumele autorului:\n";
        in.getline(aux1,100);
        char aux2[100];
        cout<<"Numele autorului:\n";
        in.getline(aux2,100);
        string s2(aux2);
        float pret;
        cout<<"Pretul cartii:\n";
        in>>pret;
        in.get();
        cout<<"Editura:\n";
        in.getline(aux2,100);
        string s3(aux2);
        autor aaux(aux1,s2);
        carte caux(s1,aaux,s3,pret);
        e.carti_imprumutate[i]=caux;
        cout<<"\n";
    }
    return in;
}

ofstream& operator<<(ofstream& out,const elev& e)
{
    out<<"Id persoana: "<<e.id_elev<<'\n';
    out<<"Nume: "<<e.nume<<'\n';
    out<<"Prenume: "<<e.prenume<<'\n';
    out<<"Varsta: "<<e.varsta<<'\n';
    out<<"Initiala tata: "<<e.initiala_tata<<'\n';
    out<<"Media anuala: "<<e.media_anuala<<'\n';
    out<<"Bursier: ";
    if (e.bursier==1)
        out<<"DA"<<'\n';
    else
        out<<"NU"<<'\n';
    out<<"Pe o perioada de "<<e.perioada;
    if (e.perioada==1)
        out<<" luna, ";
    else
        out<<" luni, ";
    if (e.nr_carti_imprumutate==0)
        out<<"nu a imprumutat nicio carte\n";
    else if (e.nr_carti_imprumutate==1)
        out<<"a imprumutat o carte:\n";
    else
        out<<"a imprumutat "<<e.nr_carti_imprumutate<<" carti:\n";
    for (int i=0; i<e.nr_carti_imprumutate; ++i)
    {
        out<<e.carti_imprumutate[i].get_nume()<<" - ";
        autor x;
        x=e.carti_imprumutate[i].get_autor_carte();
        out<<x.get_prenume()<<" "<<x.get_nume();
        out<<" (Editura "<<e.carti_imprumutate[i].get_editura()<<", pret "<<e.carti_imprumutate[i].get_pret()<<")\n";
    }
    return out;
}

ifstream& operator>>(ifstream& in, elev& e)
{
    char aux[100];
    in>>aux;
    in.get();
    if (e.nume!=NULL)
        delete[] e.nume;
    e.nume=new char[strlen(aux)+1];
    strcpy(e.nume,aux);
    in.getline(aux,100);
    string s(aux);
    e.prenume=s;
    in>>e.varsta;
    in>>e.initiala_tata;
    in>>e.media_anuala;
    in>>e.bursier;
    in>>e.perioada;
    in>>e.nr_carti_imprumutate;
    if (e.carti_imprumutate!=NULL)
        delete[] e.carti_imprumutate;
    e.carti_imprumutate=new carte[e.nr_carti_imprumutate];
    in.get();
    for (int i=0; i<e.nr_carti_imprumutate; ++i)
    {
        char aux1[100];
        in.getline(aux1,100);
        string s1(aux1);
        in.getline(aux1,100);
        char aux2[100];
        in.getline(aux2,100);
        string s2(aux2);
        float pret;
        in>>pret;
        in.get();
        in.getline(aux2,100);
        string s3(aux2);
        autor aaux(aux1,s2);
        carte caux(s1,aaux,s3,pret);
        e.carti_imprumutate[i]=caux;
    }
    return in;
}

elev& elev::operator=(const elev& e)
{
    if (this!=&e)
    {
        if (this->nume!=NULL)
            delete[] this->nume;
        if (this->carti_imprumutate!=NULL)
            delete[] this->carti_imprumutate;
        this->nume=new char[strlen(e.nume)+1];
        strcpy(this->nume,e.nume);
        this->varsta=e.varsta;
        this->media_anuala=e.media_anuala;
        this->bursier=e.bursier;
        this->initiala_tata=e.initiala_tata;
        this->prenume=e.prenume;
        this->perioada=e.perioada;
        this->nr_carti_imprumutate=e.nr_carti_imprumutate;
        this->carti_imprumutate=new carte[e.nr_carti_imprumutate];
        for (int i=0; i<e.nr_carti_imprumutate; ++i)
            this->carti_imprumutate[i]=e.carti_imprumutate[i];
    }
    return *this;
}

///CONSTRUCTORI, DESTRUCTORI
elev::elev(): id_elev(contor_id++)
{
    this->nume=new char(strlen("-")+1);
    strcpy(this->nume,"-");
    this->varsta=0;
    this->bursier=false;
    this->media_anuala=0;
    this->initiala_tata='-';
    this->perioada=0;
    this->nr_carti_imprumutate=0;
    this->carti_imprumutate=NULL;
    this->prenume="-";
}

elev::elev (char *nume, string prenume): id_elev(contor_id++)
{
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->prenume=prenume;
    this->varsta=0;
    this->bursier=false;
    this->media_anuala=0;
    this->initiala_tata='-';
    this->perioada=0;
    this->nr_carti_imprumutate=0;
    this->carti_imprumutate=NULL;
}

elev::elev (char *nume, int varsta, double media_anuala, bool bursier, char initiala_tata,
            string prenume, int perioada, int nr_carti_imprumutate, carte* carti_imprumutate): id_elev(contor_id++)
{
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->varsta=varsta;
    this->media_anuala=media_anuala;
    this->bursier=bursier;
    this->initiala_tata=initiala_tata;
    this->prenume=prenume;
    this->perioada=perioada;
    this->nr_carti_imprumutate=nr_carti_imprumutate;
    this->carti_imprumutate=new carte[nr_carti_imprumutate];
    for (int i=0; i<nr_carti_imprumutate; ++i)
        this->carti_imprumutate[i]=carti_imprumutate[i];
}

elev::~elev()
{
    if (this->nume!=NULL)
        delete[] this->nume;
    if (this->carti_imprumutate!=NULL)
        delete[] this->carti_imprumutate;
}

elev::elev (const elev& e): id_elev(e.id_elev)
{
    this->nume=new char[strlen(e.nume)+1];
    strcpy(this->nume,e.nume);
    this->varsta=e.varsta;
    this->media_anuala=e.media_anuala;
    this->bursier=e.bursier;
    this->initiala_tata=e.initiala_tata;
    this->prenume=e.prenume;
    this->perioada=e.perioada;
    this->nr_carti_imprumutate=e.nr_carti_imprumutate;
    this->carti_imprumutate=new carte[e.nr_carti_imprumutate];
    for (int i=0; i<e.nr_carti_imprumutate; ++i)
        this->carti_imprumutate[i]=e.carti_imprumutate[i];
}

///SETTERS, GETTERS
char * elev::get_nume()
{
    return this->nume;
}

void elev::set_nume(char *nume)
{
    if (this->nume!=NULL)
        delete[] this->nume;
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
}

int elev::get_varsta()
{
    return this->varsta;
}

void elev::set_varsta(int varsta)
{
    this->varsta=varsta;
}

double elev::get_media_anuala()
{
    return this->media_anuala;
}

void elev::set_media_anuala(double media)
{
    this->media_anuala=media;
}

int elev::get_id_elev()
{
    return this->id_elev;
}

bool elev::get_bursier()
{
    return this->bursier;
}

void elev::set_bursier(bool bursier)
{
    this->bursier=bursier;
}

string elev::get_prenume()
{
    return this->prenume;
}

void elev::set_prenume(string prenume)
{
    this->prenume=prenume;
}

int elev::get_perioada()
{
    return this->perioada;
}

void elev::set_perioada(int perioada)
{
    this->perioada=perioada;
}

int elev::get_nr_carti_imprumutate()
{
    return this->nr_carti_imprumutate;
}

void elev::set_nr_carti_imprumutate(int nr_carti_imprumutate)
{
    this->nr_carti_imprumutate=nr_carti_imprumutate;
}

carte* elev::get_carti_imprumutate()
{
    return this->carti_imprumutate;
}

void elev::set_carti_imprumutate(carte* carti_imprumutate, int nr)
{
    if (this->carti_imprumutate!=NULL)
        delete[] this->carti_imprumutate;
    this->carti_imprumutate=new carte[nr];
    this->nr_carti_imprumutate=nr;
    for (int i=0; i<nr; ++i)
        this->carti_imprumutate[i]=carti_imprumutate[i];
}



void test_elev() //testez clasa elev
{
    char prenume[]="Liviu";
    autor a(prenume,"Rebreanu");
    carte c("Ion",a,"Litera",20.5);
    carte c1("Carte",a,"Humanitas",34);
    carte v[]= {c,c1};
    carte v1[]= {c,c1,c};
    elev e(prenume,19,9.96,1,'M',"Guta",2,2,v);
    cout<<"--- OBIECT CREAT CU CONSTRUCTORUL CU PARAMETRI:\n"<<e;
    elev e2(e);
    e2.set_bursier(1); //setter pt variabila bool bursier
    e2.set_media_anuala(9.97); //setter pt media anuala
    char nume2[]="Pop";
    e2.set_nume(nume2); //setter pt nume
    e2.set_prenume("Andrei"); //setter pt prenume
    e2.set_varsta(18); //setter pt varsta
    e2.set_perioada(2); //setter pt perioada pt care se retin date
    e2.set_nr_carti_imprumutate(3); //setter pt nr de carti imprumutate
    e2.set_carti_imprumutate(v1,3);
    cout<<"\n--- GETTERI:\n";
    cout<<e2.get_nume()<<'\n'; //getter pt nume
    cout<<e2.get_prenume()<<'\n'; //getter pt prenume
    cout<<e2.get_media_anuala()<<'\n'; //getter pt media anuala
    cout<<e2.get_id_elev()<<'\n'; //getter pt id elev
    cout<<e2.get_bursier()<<'\n'; //getter pt bursier
    cout<<e2.get_perioada()<<'\n'; //getter pt perioada pt care se retin date
    cout<<e2.get_varsta()<<'\n'; //getter pt varsta
    cout<<e2.get_nr_carti_imprumutate()<<'\n';  //getter pt nr carti imprumutate
    carte* v2=e2.get_carti_imprumutate();
    for (int i=0; i<e2.get_nr_carti_imprumutate(); ++i)
        cout<<v2[i];
    cout<<"--- OPERATORUL ++\n";
    cout<<++e; //op ++
    cout<<e++; //op ++
    cout<<e;
    elev e3;
    cout<<"\n\n--- OPERATORUL >>\n";
    cin.get();
    cin>>e3; //op >>
    cout<<e3;
    cout<<"\n\n--- FUNCTIONALITATE\n";
    e.total_pret_carti_imprumutate(); //functionalitate
    elev e5(e);
    cout<<"\n\n--- OPERATORUL ==\n";
    cout<<"e5==e "<<(e5==e)<<'\n'; //op ==
    cout<<"\n--- OPERATORUL <=\n";
    cout<<"e2<=e "<<(e2<=e)<<'\n'; //op <=
    cout<<"\n--- OPERATORUL []\n";
    cout<<"e[1] "<<e[1]<<'\n'; //op []
    cout<<"\n--- OPERATORUL cast\n";
    cout<<"(double)e "<<(double)e<<'\n'; //op cast explicit
    e=e/2;
    cout<<"\n--- OPERATORUL /\n";
    cout<<e;
    e=e+3.75;
    cout<<"\n--- OPERATORUL +\n";
    cout<<e;
    cout<<"\n\n\n";
}

void test_autor() //testez clasa autor
{
    char nume5[]="Ion";
    string carti5[]= {"Amintiri din copilarie","Poezii"};
    int ani[]= {1945,1944};
    autor a(nume5,"Creanga",2,carti5,ani); //constructor cu toti param
    cout<<"\n--- OBIECT CREAT CU CONSTRUCTORUL CU TOTI PARAM\n";
    cout<<a;
    autor a1(nume5,"Luca Caragiale"); //constructor cu 2 param
    cout<<"\n--- OBIECT CREAT CU CONSTRUCTORUL CU 2 PARAM\n";
    cout<<a1;
    autor a2(a); //copy constructor
    autor a4=a; //op =
    cout<<"\n--- TESTE PENTRU GETTERI\n";
    cout<<a.get_nume()<<'\n'; //getter
    cout<<a.get_prenume()<<'\n'; //getter
    cout<<a.get_nr_carti_publicate()<<'\n'; //getter
    int* ani1=a.get_ani_publicari(); //getter
    string* carti7=a.get_nume_carti_publicate();
    for (int i=0; i<a.get_nr_carti_publicate(); ++i)
        cout<<carti7[i]<<" "<<ani1[i]<<'\n';
    cout<<'\n';
    autor a3; //constructor fara param
    char nume10[]="ION";
    a.set_prenume(nume10); //setter pentru prenume
    a.set_nume("CREANGA"); //setter pentru nume
    a.set_nr_carti_publicate(3); //setter pentru nr. de carti publicate
    string carti25[]= {"Amintiri din copilarie","Poezii","Proza"};
    int ani2[]= {1945,1944,1926};
    a.set_ani_publicari(ani2,3); //setter pt vectorul de int ani_publicari
    a.set_nume_carti_publicate(carti25,3); //setter pt vectorul de string nume_publicari
    cout<<"\n--- FUNCTIONALITATE\n";
    a.numar_carti_perioada(1940,1950); //functionalitate
    cout<<'\n';
    autor a5;
    cout<<"\n--- OPERATORUL >>\n";
    cin.get();
    cin>>a5;
    cout<<a5;
    autor a6(a);
    cout<<"\n--- OPERATORUL ==\n";
    cout<<"a6==a "<<(a6==a)<<'\n'; //op ==
    cout<<"\n--- OPERATORUL >=\n";
    cout<<"a>=a1 "<<(a>=a1)<<'\n'; //op >=
    cout<<"\n--- OPERATORUL []\n";
    cout<<"a[0] "<<a[0]<<'\n'; //op []
    cout<<"\n--- OPERATORUL cast\n";
    cout<<"(string)a "<<(string)a; //op cast explicit
    cout<<"\n\n\n";
}

void test_carte() //testez clasa carte
{
    char prenume[]="Liviu";
    autor a(prenume,"Rebreanu");
    string conditie[]= {"noua","uzata","noua"};
    bool imprumut[]= {1,0,1};
    carte c("Ion",a,"Litera",20.5,3,conditie,imprumut);
    cout<<c;
    carte c1(c);
    char prenume1[]="J.K.";
    autor a1(prenume1,"Rowling");
    c1.set_autor_carte(a1); //setter pt autor
    c1.set_nume("Harry Potter si piatra filozofala"); //setter pt nume
    c1.set_editura("Corint"); //setter pt editura
    c1.set_nr_exemplare(4); //setter pt nr_exemplare
    c1.set_pret(35.4); //setter pt pret
    string conditie1[]= {"noua","noua","uzata","uzata"};
    bool imprumuturi1[]= {1,1,0,0};
    c1.set_conditie_exemplare(conditie1,4); //setter pt vectorul de stringuri conditia_exemplarelor
    c1.set_imprumuturi(imprumuturi1,4); //seter pt vectorul bool imprumuturi
    cout<<"\n--- TESTE PENTRU GETTERI\n";
    cout<<c1.get_nume()<<'\n'; //getter pt nume
    cout<<c1.get_autor_carte()<<'\n'; //getter pt autor
    cout<<c1.get_editura()<<'\n'; //getter pt editura
    cout<<c1.get_nr_exemplare()<<'\n'; //getter pt nr_exemplare
    string* cond1=c1.get_conditie_exemplare(); //getter pt conditie_exemplare
    bool* imp1=c1.get_imprumuturi(); //getter pt imprumuturi
    for (int i=0; i<c1.get_nr_exemplare(); ++i)
        cout<<cond1[i]<<" "<<imp1[i]<<'\n';
    cout<<"\n--- OPERATORUL ++\n";
    cout<<++c; //op ++
    cout<<c++; //op ++
    cout<<c;
    cout<<"\n--- FUNCTIONALITATE\n";
    c.disponibilitate(); //functionalitate
    cout<<'\n';
    carte c5;
    cout<<"\n--- OPERATORUL >>\n";
    cin.get();
    cin>>c5; //op >>
    cout<<c5;
    carte c6(c1);
    cout<<"\n--- OPERATORUL ==\n";
    cout<<"c6==c "<<(c6==c)<<'\n'; //op ==
    cout<<"\n--- OPERATORUL <\n";
    cout<<"c<c1 "<<(c<c1)<<'\n'; //op <
    cout<<"\n--- OPERATORUL []\n";
    cout<<"c[1] "<<c[1]<<'\n'; //op []
    cout<<"\n--- OPERATORUL cast\n";
    cout<<"(int)c "<<(int)c<<'\n'; //op cast explicit
    c=c-5; //op -
    cout<<"\n--- OPERATORUL -\n";
    cout<<c;
    cout<<"\n\n\n";
}

void test_manual() //testez clasa manual
{
    char prenume[]="Manuela";
    autor a(prenume,"Cerchez");
    string conditie[]= {"noua","uzata","noua"};
    bool imprumut[]= {1,0,1};
    manual m("Manual de informatica",a,"Humanitas",31.5,3,conditie,imprumut,"informatica");
    cout<<m;
    cout<<"\n\n--- FUNCTIONALITATE\n";
    m.nevoie_inlocuire();
    manual m2(m);
    manual m3;
    m3=m;
    manual m4;
    cin.get();
    cin>>m4;
    cout<<m4;
}

void test_angajat() //testez clasa angajat
{
    angajat *angajati[100];
    int i=0;
    cout<<"\n1 bibliotecar";
    cout<<"\n2 paznic";
    cout<<"\n3 afiseaza salariu dupa plata impozitului";
    cout<<"\n4 afiseaza angajati";
    cout<<"\n5 stop\n";
    int comanda;
    cin>>comanda;
    while (comanda!=5)
    {
        if (comanda==1)
        {
            angajati[i]=new angajat_bibliotecar();
            cin>>*angajati[i];
            ++i;
        }
        else if (comanda==2)
        {
            angajati[i]=new angajat_paznic();
            cin>>*angajati[i];
            ++i;
        }
        else if (comanda==3)
            for (int j=0; j<i; ++j)
            {
                angajati[j]->calculeaza_salariu_impozit();
                cout<<'\n';
            }
        else if (comanda==4)
            for (int j=0; j<i; ++j)
                cout<<*angajati[j];
        cout<<"\n1 bibliotecar";
        cout<<"\n2 paznic";
        cout<<"\n3 afiseaza salariu dupa plata impozitului";
        cout<<"\n4 afiseaza angajati";
        cout<<"\n5 stop\n";
        cin>>comanda;
    }
}

void test_biblioteca() //testez clasa biblioteca
{
    angajat_bibliotecar b("Toader", "Vlad", 3000, 15, "30.03.2020");
    angajat_paznic p("Toader","Vlad",3000,15,"30.04.2019","30.05.2021");
    angajat_bibliotecar* bibl;
    bibl=new angajat_bibliotecar[3];
    angajat_paznic* paz;
    paz=new angajat_paznic[3];
    for (int i=0; i<3; ++i)
        bibl[i]=b;
    for (int i=0; i<3; ++i)
        paz[i]=p;
    angajat_bibliotecar* bibl1;
    bibl1=new angajat_bibliotecar[7];
    for (int i=0; i<7; ++i)
        bibl1[i]=b;
    angajat_paznic* paz1;
    paz1=new angajat_paznic[4];
    for (int i=0; i<4; ++i)
        paz1[i]=p;
    biblioteca b1("eminescu",3,bibl,3,paz,300,400);
    biblioteca b2(b1);
    cout<<b1;
    b2.set_bibliotecari(bibl1,7);
    b2.set_nr_abonati(450);
    b2.set_nr_carti(500);
    b2.set_paznici(paz1,4);
    b2.set_nume("Ion Barbu");
    cout<<"\n---GETTERI:\n";
    cout<<b2.get_nume()<<'\n';
    cout<<b2.get_nr_abonati()<<" "<<b2.get_nr_carti()<<'\n';
    cout<<b2.get_nr_paznici()<<'\n';
    angajat_paznic* paz2=b2.get_paznici();
    for (int i=0; i<b2.get_nr_paznici(); ++i)
        cout<<paz2[i];
    cout<<b2.get_nr_bibliotecari()<<'\n';
    angajat_bibliotecar* bibl2=b2.get_bibliotecari();
    for (int i=0; i<b2.get_nr_bibliotecari(); ++i)
        cout<<bibl2[i];
    cout<<"\n--- OPERATORUL ==\n";
    cout<<"b9==b "<<(b2==b1)<<'\n'; //op ==
    cout<<"\n--- OPERATORUL <\n";
    cout<<"b1<b "<<(b1<b1)<<'\n'; //op <
    cout<<"\n--- OPERATORUL []\n";
    cout<<"b[1] "<<b1[1]<<'\n'; //op []
    b1=b1+30; //op +
    cout<<"\n--- OPERATORUL + (int)\n";
    cout<<b1;
    b1=b1+b2; //op + intre 2 obiecte
    cout<<"\n--- OPERATORUL + (intre 2 obiecte)\n";
    cout<<b1;
    cout<<"\n--- OPERATORUL *\n";
    b1=b1*2; //op *
    cout<<b1;
    biblioteca b4;
    cout<<"\n--- OPERATORUL >>\n";
    //cin>>b4;
    //cout<<b4;
    //functionalitate
    cout<<"\n--- FUNCTIONALITATE\n";
    cout<<"AFISARE LISTA TOTI ANGAJATII\n";
    b1.afisare_angajati();
    cout<<"Introduceti numele si prenumele angajatului care trebuie cautat la biblioteca "<<b1.get_nume()<<"(cate unul pe linie):\n";
    char aux[100];
    cin.getline(aux,100);
    string aux1(aux);
    cin.getline(aux,100);
    string aux2(aux);
    if (b1.verifica_angajat(aux1,aux2))
        cout<<"\nAngajatul "<<aux1<<" "<<aux2<<" este angajat la biblioteca";
    else
        cout<<"\nAngajatul "<<aux1<<" "<<aux2<<" nu este angajat la biblioteca";
    biblioteca b7;
    cin.get();
    cin>>b7;
    cout<<b7;
    cout<<"\n\n\n";
}

void test_biblioteca_scolara() //testez clasa biblioteca_scolara
{
    angajat_bibliotecar b("Toader", "Vlad", 3000, 15, "30.03.2020");
    angajat_paznic p("Toader","Vlad",3000,15,"30.04.2019","30.05.2021");
    angajat_bibliotecar* bibl;
    bibl=new angajat_bibliotecar[3];
    angajat_paznic* paz;
    paz=new angajat_paznic[3];
    for (int i=0; i<3; ++i)
        bibl[i]=b;
    for (int i=0; i<3; ++i)
        paz[i]=p;
    biblioteca_scolara bs("eminescu",3,bibl,3,paz,300,400,"dinicu");
    cout<<bs;
    cout<<"--- FUNCTIONALITATE\n";
    bs.calcul_salariu();
    biblioteca_scolara bs1;
    cin.get();
    cin>>bs1;
    cout<<bs1;
}

void meniu_teste()
{
    cout<<"1 - TESTATI CLASA ELEV\n";
    cout<<"2 - TESTATI CLASA AUTOR\n";
    cout<<"3 - TESTATI CLASA CARTE\n";
    cout<<"4 - TESTATI CLASA MANUAL (derivata din carte)\n";
    cout<<"5 - TESTATI CLASA ANGAJAT (vector - clasa abstracta in care se pun obiecte din derivata)\n";
    cout<<"6 - TESTATI CLASA BIBLIOTECA\n";
    cout<<"7 - TESTATI CLASA BIBLIOTECA SCOLARA (derivata din biblioteca)\n";
    cout<<"8 - STOP\n";
    int comanda;
    cin>>comanda;
    while (comanda!=8)
    {
        if (comanda==1)
            test_elev();
        else if (comanda==2)
            test_autor();
        else if (comanda==3)
            test_carte();
        else if (comanda==4)
            test_manual();
        else if (comanda==5)
            test_angajat();
        else if (comanda==6)
            test_biblioteca();
        else if (comanda==7)
            test_biblioteca_scolara();
        cout<<"1 - TESTATI CLASA ELEV\n";
        cout<<"2 - TESTATI CLASA AUTOR\n";
        cout<<"3 - TESTATI CLASA CARTE\n";
        cout<<"4 - TESTATI CLASA MANUAL (derivata din carte)\n";
        cout<<"5 - TESTATI CLASA ANGAJAT (vector - clasa abstracta in care se pun obiecte din derivata)\n";
        cout<<"6 - TESTATI CLASA BIBLIOTECA\n";
        cout<<"7 - TESTATI CLASA BIBLIOTECA SCOLARA (derivata din biblioteca)\n";
        cout<<"8 - STOP\n";
        cin>>comanda;
    }
}

void meniu_principal()
{
    setcolor(14);
    cout<<"SISTEMUL DE GESTIUNE AL BIBLIOTECILOR\n\n";
    setcolor(7);
    cout<<"\nSelectati optiunea de logare dorita:\n";
    cout<<"\t1 - ADMIN\n";
    cout<<"\t2 - UTILIZATOR\n";
    cout<<"\nIntroduceti optiunea dorita!\n";
    setcolor(4);
    cout<<"\nIntroduceti valoarea 0 pentru a iesi din program!\n";
    setcolor(7);

}

void meniu_admin_biblioteca()
{
    cout<<"Ati ales meniul:";
    setcolor(3);
    cout<<" BIBLIOTECI\n\n";
    setcolor(7);
    cout<<"Optiuni disponibile:\n";
    cout<<"1. afisarea bibliotecilor existente;\n";
    cout<<"2. introducerea unei biblioteci noi;\n";
    cout<<"3. modificarea datelor unei biblioteci;\n";
    cout<<"4. afisarea angajatilor fiecarei biblioteci;\n";
    cout<<"5. cautarea unei persoane in lista de angajati a unei biblioteci;\n";
    cout<<"6. afisarea, pentru fiecare biblioteca scolara, costul salariilor angajatilor;\n";
    setcolor(14);
    cout<<"7. intoarcere la meniul principal;\n";
    setcolor(7);
    cout<<"\tIntroduceti optiunea dorita!\n";
}

void meniu_admin_elev()
{
    cout<<"Ati ales meniul:";
    setcolor(3);
    cout<<" ELEVI\n\n";
    setcolor(7);
    cout<<"Optiuni disponibile:\n";
    cout<<"1. afisarea elevilor existenti;\n";
    cout<<"2. introducerea unui elev nou;\n";
    cout<<"3. modificarea datelor unui elev;\n";
    cout<<"4. afisarea costului cartilor imprumutate de un elev;\n";
    cout<<"5. adaugarea unei carti in lista de carti a unui elev;\n";
    setcolor(14);
    cout<<"6. intoarcere la meniul principal;\n";
    setcolor(7);
    cout<<"\tIntroduceti optiunea dorita!\n";
}

void meniu_admin_carti()
{
    cout<<"Ati ales meniul:";
    setcolor(3);
    cout<<" CARTI\n\n";
    setcolor(7);
    cout<<"Optiuni disponibile:\n";
    cout<<"1. afisarea cartilor existente;\n";
    cout<<"2. introducerea unei carti noi;\n";
    cout<<"3. modificarea datelor unei carti;\n";
    cout<<"4. afisarea, pentru fiecare carte, numarul exemplarelor disponibile si imprumutate;\n";
    setcolor(14);
    cout<<"5. intoarcere la meniul principal;\n";
    setcolor(7);
    cout<<"\tIntroduceti optiunea dorita!\n";
}

void meniu_admin_manuale()
{
    cout<<"Ati ales meniul:";
    setcolor(3);
    cout<<" MANUALE\n\n";
    setcolor(7);
    cout<<"Optiuni disponibile:\n";
    cout<<"1. afisarea manualelor existente;\n";
    cout<<"2. introducerea unui manual nou;\n";
    cout<<"3. modificarea datelor unui manual;\n";
    cout<<"4. afisarea, pentru fiecare manual, numarul exemplarelor disponibile si imprumutate;\n";
    cout<<"5. afisarea, pentru fiecare manual, numarul exemplarelor ce necesita a fi inlocuite;\n";
    setcolor(14);
    cout<<"6. intoarcere la meniul principal;\n";
    setcolor(7);
    cout<<"\tIntroduceti optiunea dorita!\n";
}

int main()
{
    int n;
    char comanda,comanda_admin,comanda_admin_biblioteca,comanda_admin_elev;
    char comanda_admin_carti, comanda_admin_manuale,comanda_elev, comanda_elev_carti;
    char comanda_elev_exemplare, comanda_elev_imprumuta, comanda_elev_cost;
    char comanda_useless, comanda_schimbare_carte,comanda_schimbare_elev, comanda_schimbare_manual;\
    char comanda_schimbare_biblioteca;
    int nr_bibl, nr_bibl_scolare;
    vector <carte> carti;
    set <elev> elevi;
    map <int, biblioteca> biblioteci;
    map <int, biblioteca_scolara> biblioteci_scolare;
    list <manual> manuale;
    while (true)
    {
        meniu_principal();
        comanda=getch();
        system("CLS");
        if (comanda=='1')
        {
            cout<<"Sunteti logat ca: ";
            setcolor(10);
            cout<<"ADMIN\n\n";
            setcolor(7);
            cout<<"Optiuni disponibile:\n";
            cout<<"1 - import date;\n";
            cout<<"2 - export date;\n";
            cout<<"3 - accesare meniu biblioteci;\n";
            cout<<"4 - accesare meniu elevi;\n";
            cout<<"5 - accesare meniu carti;\n";
            cout<<"6 - accesare meniu manuale;\n";
            setcolor(14);
            cout<<"7 - intoarcere la meniul principal;\n";
            setcolor(4);
            cout<<"0 - iesire din program;\n\n";
            setcolor(7);
            cout<<"\tIntroduceti optiunea dorita!\n";
            comanda_admin=getch();
            system("CLS");
            if (comanda_admin=='0')
                break;
            else if (comanda_admin=='1') //import
            {
                f>>n;
                f.get();
                biblioteca b;
                for (int i=0;i<n;++i)
                {
                    f>>b;
                    biblioteci.insert(pair<int,biblioteca>(i+1,b));
                    nr_bibl=i+1;
                }
                f>>n;
                f.get();
                biblioteca_scolara b1;
                for (int i=0;i<n;++i)
                {
                    f>>b1;
                    biblioteci_scolare.insert(pair<int,biblioteca_scolara>(i+1,b1));
                    nr_bibl_scolare=i+1;
                }
                f>>n;
                f.get();
                carte c;
                for (int i=0;i<n;++i)
                {
                    f>>c;
                    carti.push_back(c);
                }
                f>>n;
                f.get();
                manual m;
                for (int i=0;i<n;++i)
                {
                    f>>m;
                    f.get();
                    manuale.push_back(m);
                }
                f>>n;
                f.get();
                for (int i=0;i<n;++i)
                {
                    elev e;
                    f>>e;
                    elevi.insert(e);
                }
                setcolor(10);
                cout<<"Import date cu succes!\n";
                setcolor(7);
                cout<<"\nApasati orice tasta pentru a continua!\n";
                comanda_useless=getch();
                system("CLS");
            }
            else if (comanda_admin=='2') //export
            {
                g<<"BIBLIOTECI\n";
                for (auto i=biblioteci.begin();i!=biblioteci.end();++i)
                    g<<i->second<<"----------------------------\n";
                g<<"BIBLIOTECI SCOLARE\n";
                for (auto i=biblioteci_scolare.begin();i!=biblioteci_scolare.end();++i)
                    g<<i->second<<"----------------------------\n";
                g<<"CARTI\n";
                for (int i=0;i<carti.size();++i)
                    g<<carti[i]<<"----------------------------\n";
                g<<"MANUALE\n";
                for (auto i=manuale.begin();i!=manuale.end();++i)
                    g<<(*i)<<"----------------------------\n";
                g<<"ELEVI\n";
                for (auto i=elevi.begin();i!=elevi.end();++i)
                    g<<(*i)<<"----------------------------\n";
                setcolor(10);
                cout<<"Export date cu succes!\n";
                setcolor(7);
                cout<<"\nApasati orice tasta pentru a continua!\n";
                comanda_useless=getch();
                system("CLS");
            }
            else if (comanda_admin=='3') //biblioteci
                while (true)
                {
                    meniu_admin_biblioteca();
                    comanda_admin_biblioteca=getch();
                    system("CLS");
                    if (comanda_admin_biblioteca=='7')
                        break;
                    else if (comanda_admin_biblioteca=='1')
                        if (biblioteci.empty() != 0 && biblioteci_scolare.empty() !=0)
                        {
                            setcolor(4);
                            cout<<"Nu exista biblioteci in baza de date!\n";
                            setcolor(7);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                        else
                        {
                           for (auto i=biblioteci.begin();i!=biblioteci.end();++i)
                                cout<<i->second<<"----------------------------\n";
                            for (auto i=biblioteci_scolare.begin();i!=biblioteci_scolare.end();++i)
                                cout<<i->second<<"----------------------------\n";
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                    else if (comanda_admin_biblioteca=='2')
                    {
                        cout<<"Introduceti valoarea 1 daca biblioteca este de tip scolar sau 0 daca nu este!\n";
                        char bibl_comanda;
                        bibl_comanda=getch();
                        system("CLS");
                        if (bibl_comanda=='1')
                        {
                            biblioteca_scolara b1;
                            cin>>b1;
                            int ok=1;
                            for (auto i=biblioteci_scolare.begin();i!=biblioteci_scolare.end();++i)
                                if (i->second==b1)
                                {
                                    setcolor(4);
                                    cout<<"Elementul se afla deja in baza de date!\n";
                                    setcolor(7);
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                    ok=0;
                                }
                            if (ok==1)
                            {
                                biblioteci_scolare.insert(pair<int,biblioteca_scolara>(nr_bibl_scolare+1,b1));
                                nr_bibl_scolare++;
                                setcolor(10);
                                cout<<"Elementul a fost introdus cu succes!\n\n";
                                setcolor(7);
                                cout<<"Apasati orice tasta pentru a continua!\n";
                                comanda_useless=getch();
                                system("CLS");
                            }
                        }
                        else if (bibl_comanda=='0')
                        {
                            biblioteca b1;
                            cin>>b1;
                            int ok=1;
                            for (auto i=biblioteci.begin();i!=biblioteci.end();++i)
                                if (i->second==b1)
                                {
                                    setcolor(4);
                                    cout<<"Elementul se afla deja in baza de date!\n";
                                    setcolor(7);
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                    ok=0;
                                }
                            if (ok==1)
                            {
                                biblioteci.insert(pair<int,biblioteca>(nr_bibl+1,b1));
                                nr_bibl++;
                                setcolor(10);
                                cout<<"Elementul a fost introdus cu succes!\n\n";
                                setcolor(7);
                                cout<<"Apasati orice tasta pentru a continua!\n";
                                comanda_useless=getch();
                                system("CLS");
                            }
                        }

                    }
                    else if (comanda_admin_biblioteca=='3')
                        if (biblioteci.empty() != 0 && biblioteci_scolare.empty() != 0)
                            {setcolor(4);
                            cout<<"Nu exista biblioteci in baza de date!\n";
                            setcolor(7);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                            }
                        else
                        {
                            if (biblioteci.empty()==0)
                                cout<<"Biblioteci existente in baza de date:\n";
                            for (auto i=biblioteci.begin();i!=biblioteci.end();++i)
                            {
                                biblioteca b1;
                                b1=i->second;
                                cout<<b1.get_nume()<<'\n';
                            }
                            if (biblioteci_scolare.empty()==0)
                                cout<<"\nBiblioteci scolare existente in baza de date:\n";
                            for (auto i=biblioteci_scolare.begin();i!=biblioteci_scolare.end();++i)
                            {
                                biblioteca_scolara b1;
                                b1=i->second;
                                cout<<b1.get_nume()<<"("<<b1.get_scoala()<<")"<<'\n';
                            }
                            cout<<"\nIntroduceti numele bibliotecii pe care doriti sa o modificati!\n";
                            char aux[100];
                            cin.getline(aux,100);
                            string s(aux);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                            int ok=0;
                            biblioteca b_sch;
                            biblioteca_scolara bs_sch;
                            map <int, biblioteca>::iterator i1;
                            map <int, biblioteca_scolara>::iterator i2;
                            int nr1=0;
                            int nr2=0;
                            for (i1=biblioteci.begin();i1!=biblioteci.end();++i1)
                            {
                                biblioteca b1;
                                b1=i1->second;
                                if (b1.get_nume()==s)
                                {
                                    ok=1;
                                    b_sch=b1;
                                    nr1=i1->first;
                                    break;
                                }
                            }
                            for (i2=biblioteci_scolare.begin();i2!=biblioteci_scolare.end();++i2)
                            {
                                biblioteca_scolara b1;
                                b1=i2->second;
                                if (b1.get_nume()==s)
                                {
                                    ok=2;
                                    bs_sch=b1;
                                    nr2=i2->first;
                                    break;
                                }
                            }
                            if (ok==0)
                            {
                                setcolor(4);
                                cout<<"Biblioteca nu exista in baza de date!\n";
                                setcolor(7);
                                cout<<"\nApasati orice tasta pentru a continua!\n";
                                comanda_useless=getch();
                                system("CLS");
                            }
                            else
                            {
                                cout<<"Alegeti optiunea pentru a selecta ce doriti sa modificati!\n";
                                cout<<"1. numele bibliotecii;\n";
                                cout<<"2. bibliotecarii angajati;\n";
                                cout<<"3. paznicii angajati;\n";
                                cout<<"4. numarul de carti;\n";
                                cout<<"5. numarul de abonati;\n";
                                if (ok==2)
                                    cout<<"6. scoala in care se afla biblioteca;\n";
                                cout<<"\tIntroduceti optiunea dorita!\n";
                                comanda_schimbare_biblioteca=getch();
                                system("CLS");
                                if (comanda_schimbare_biblioteca=='1')
                                {
                                    char aux[100];
                                    cout<<"Introduceti noul nume al bibliotecii!\n";
                                    cin.getline(aux,100);
                                    string s(aux);
                                    if (ok==1)
                                    {
                                        biblioteci.erase(i1);
                                        string nume_vechi=b_sch.get_nume();
                                        b_sch.set_nume(s);
                                        biblioteci.insert(pair<int,biblioteca>(nr1,b_sch));
                                        cout<<"Numele bibliotecii a fost schimbat din "<<nume_vechi<<" in "<<s<<"!\n";
                                        cout<<"\nApasati orice tasta pentru a continua!\n";
                                        comanda_useless=getch();
                                        system("CLS");
                                    }
                                    else
                                    {
                                        biblioteci_scolare.erase(i2);
                                        string nume_vechi=bs_sch.get_nume();
                                        bs_sch.set_nume(s);
                                        biblioteci_scolare.insert(pair<int,biblioteca_scolara>(nr2,bs_sch));
                                        cout<<"Numele bibliotecii a fost schimbat din "<<nume_vechi<<" in "<<s<<"!\n";
                                        cout<<"\nApasati orice tasta pentru a continua!\n";
                                        comanda_useless=getch();
                                        system("CLS");
                                    }
                                }
                                else if (comanda_schimbare_biblioteca=='2')
                                {//bibliotecari
                                    cout<<"Introduceti noul numar de bibliotecari!\n";
                                    int nr_bibliotecari;
                                    cin>>nr_bibliotecari;
                                    cin.get();
                                    cout<<"Introduceti noii bibliotecari!\n";
                                    angajat_bibliotecar *bibl_nou=new angajat_bibliotecar[nr_bibliotecari];
                                    for (int i=0;i<nr_bibliotecari;++i)
                                        cin>>bibl_nou[i];
                                    if (ok==1)
                                    {
                                        biblioteci.erase(i1);
                                        b_sch.set_bibliotecari(bibl_nou,nr_bibliotecari);
                                        biblioteci.insert(pair<int,biblioteca>(nr1,b_sch));
                                        cout<<"Bibliotecarii au fost schimbati cu succes!\n";
                                        cout<<"\nApasati orice tasta pentru a continua!\n";
                                        comanda_useless=getch();
                                        system("CLS");
                                    }
                                    else
                                    {
                                        biblioteci_scolare.erase(i2);
                                        bs_sch.set_bibliotecari(bibl_nou,nr_bibliotecari);
                                        biblioteci_scolare.insert(pair<int,biblioteca_scolara>(nr2,bs_sch));
                                        cout<<"Bibliotecarii au fost schimbati cu succes!\n";
                                        cout<<"\nApasati orice tasta pentru a continua!\n";
                                        comanda_useless=getch();
                                        system("CLS");
                                    }
                                }
                                else if (comanda_schimbare_biblioteca=='3')
                                {//paznici
                                    cout<<"Introduceti noul numar de paznici!\n";
                                    int nr_paznici;
                                    cin>>nr_paznici;
                                    cin.get();
                                    cout<<"Introduceti noii paznici!\n";
                                    angajat_paznic *paz_nou=new angajat_paznic[nr_paznici];
                                    for (int i=0;i<nr_paznici;++i)
                                        cin>>paz_nou[i];
                                    if (ok==1)
                                    {
                                        biblioteci.erase(i1);
                                        b_sch.set_paznici(paz_nou,nr_paznici);
                                        biblioteci.insert(pair<int,biblioteca>(nr1,b_sch));
                                        cout<<"Paznicii au fost schimbati cu succes!\n";
                                        cout<<"\nApasati orice tasta pentru a continua!\n";
                                        comanda_useless=getch();
                                        system("CLS");
                                    }
                                    else
                                    {
                                        biblioteci_scolare.erase(i2);
                                        bs_sch.set_paznici(paz_nou,nr_paznici);
                                        biblioteci_scolare.insert(pair<int,biblioteca_scolara>(nr2,bs_sch));
                                        cout<<"Paznicii au fost schimbati cu succes!\n";
                                        cout<<"\nApasati orice tasta pentru a continua!\n";
                                        comanda_useless=getch();
                                        system("CLS");
                                    }
                                }
                                else if (comanda_schimbare_biblioteca=='4')
                                {
                                    cout<<"Introduceti noul numar de carti al bibliotecii!\n";
                                    int nr;
                                    cin>>nr;
                                    if (ok==1)
                                    {
                                        biblioteci.erase(i1);
                                        int nr_vechi=b_sch.get_nr_carti();
                                        b_sch.set_nr_carti(nr);
                                        biblioteci.insert(pair<int,biblioteca>(nr1,b_sch));
                                        cout<<"Numarul de carti ale bibliotecii a fost schimbat din "<<nr_vechi<<" in "<<nr<<"!\n";
                                        cout<<"\nApasati orice tasta pentru a continua!\n";
                                        comanda_useless=getch();
                                        system("CLS");
                                    }
                                    else
                                    {
                                        biblioteci_scolare.erase(i2);
                                        int nr_vechi=bs_sch.get_nr_carti();
                                        bs_sch.set_nr_carti(nr);
                                        biblioteci_scolare.insert(pair<int,biblioteca_scolara>(nr1,bs_sch));
                                        cout<<"Numarul de carti al bibliotecii a fost schimbat din "<<nr_vechi<<" in "<<nr<<"!\n";
                                        cout<<"\nApasati orice tasta pentru a continua!\n";
                                        comanda_useless=getch();
                                        system("CLS");
                                    }
                                }
                                else if (comanda_schimbare_biblioteca=='5')
                                {
                                    cout<<"Introduceti noul numar de abonati al bibliotecii!\n";
                                    int nr;
                                    cin>>nr;
                                    if (ok==1)
                                    {
                                        biblioteci.erase(i1);
                                        int nr_vechi=b_sch.get_nr_abonati();
                                        b_sch.set_nr_abonati(nr);
                                        biblioteci.insert(pair<int,biblioteca>(nr1,b_sch));
                                        cout<<"Numarul de abonati al bibliotecii a fost schimbat din "<<nr_vechi<<" in "<<nr<<"!\n";
                                        cout<<"\nApasati orice tasta pentru a continua!\n";
                                        comanda_useless=getch();
                                        system("CLS");
                                    }
                                    else
                                    {
                                        biblioteci_scolare.erase(i2);
                                        int nr_vechi=bs_sch.get_nr_abonati();
                                        bs_sch.set_nr_abonati(nr);
                                        biblioteci_scolare.insert(pair<int,biblioteca_scolara>(nr1,bs_sch));
                                        cout<<"Numarul de carti ale bibliotecii a fost schimbat din "<<nr_vechi<<" in "<<nr<<"!\n";
                                        cout<<"\nApasati orice tasta pentru a continua!\n";
                                        comanda_useless=getch();
                                        system("CLS");
                                    }
                                }
                                else if (ok==2&&comanda_schimbare_biblioteca=='6')
                                {
                                    char aux[100];
                                    cout<<"Introduceti noua scoala in care se afla biblioteca!\n";
                                    cin.getline(aux,100);
                                    string s(aux);
                                    biblioteci_scolare.erase(i2);
                                    string nume_vechi=bs_sch.get_scoala();
                                    bs_sch.set_scoala(s);
                                    biblioteci_scolare.insert(pair<int,biblioteca_scolara>(nr2,bs_sch));
                                    cout<<"Scoala in care se afla biblioteca a fost schimbata din "<<nume_vechi<<" in "<<s<<"!\n";
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                }
                            }
                        }
                    else if (comanda_admin_biblioteca=='4')
                        if (biblioteci.empty() != 0 && biblioteci_scolare.empty() !=0)
                        {
                            setcolor(4);
                            cout<<"Nu exista biblioteci in baza de date!\n";
                            setcolor(7);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                        else
                        {
                           for (auto i=biblioteci.begin();i!=biblioteci.end();++i)
                                {
                                    biblioteca b1;
                                    b1=i->second;
                                    cout<<b1.get_nume()<<" are ca angajati:\n";
                                    b1.afisare_angajati();
                                    cout<<"\n----------------------------\n";
                                }
                            for (auto i=biblioteci_scolare.begin();i!=biblioteci_scolare.end();++i)
                                {
                                    biblioteca_scolara b1;
                                    b1=i->second;
                                    cout<<b1.get_nume()<<" are ca angajati:\n";
                                    b1.afisare_angajati();
                                    cout<<"\n----------------------------\n";
                                }
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                    else if (comanda_admin_biblioteca=='5')
                        if (biblioteci.empty() != 0 && biblioteci_scolare.empty() !=0)
                        {
                            setcolor(4);
                            cout<<"Nu exista biblioteci in baza de date!\n";
                            setcolor(7);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                        else
                        {
                            cout<<"Introduceti numele persoanei pe care doriti sa o cautati in lista de angajati a bibliotecilor!\n";
                            char aux[100];
                            cin>>aux;
                            string s1(aux);
                            cin.get();
                            cout<<"Introduceti prenumele persoanei pe care doriti sa o cautati in lista de angajati a bibliotecilor!\n";
                            cin.getline(aux,100);
                            string s2(aux);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                            int ok=1;
                            for (auto i=biblioteci.begin();i!=biblioteci.end();++i)
                                {
                                    biblioteca b1;
                                    b1=i->second;
                                    if (b1.verifica_angajat(s1,s2))
                                    {
                                        cout<<s2<<" "<<s1<<" lucreaza la "<<b1.get_nume()<<"!\n";
                                        ok=0;
                                    }
                                }
                            for (auto i=biblioteci_scolare.begin();i!=biblioteci_scolare.end();++i)
                                {
                                    biblioteca_scolara b1;
                                    b1=i->second;
                                    if (b1.verifica_angajat(s1,s2))
                                    {
                                        cout<<s2<<" "<<s1<<" lucreaza la "<<b1.get_nume()<<"!\n";
                                        ok=0;
                                    }
                                }
                            if (ok==1)
                                cout<<s2<<" "<<s1<<" nu lucreaza la nicio biblioteca existenta!\n";
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                    else if (comanda_admin_biblioteca=='6')
                        if (biblioteci.empty() != 0 && biblioteci_scolare.empty() !=0)
                        {
                            setcolor(4);
                            cout<<"Nu exista biblioteci in baza de date!\n";
                            setcolor(7);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                        else
                        {
                           for (auto i=biblioteci_scolare.begin();i!=biblioteci_scolare.end();++i)
                                {
                                    biblioteca_scolara b1;
                                    b1=i->second;
                                    b1.calcul_salariu();
                                    cout<<"----------------------------\n";
                                }
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }

                }
            else if (comanda_admin=='4') //elevi
                while (true)
                {
                    meniu_admin_elev();
                    comanda_admin_elev=getch();
                    system("CLS");
                    if (comanda_admin_elev=='6')
                        break;
                    else if (comanda_admin_elev=='1')
                        if (elevi.empty() !=0)
                        {
                            setcolor(4);
                            cout<<"Nu exista elevi in baza de date!\n";
                            setcolor(7);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                        else
                        {
                            for (auto i=elevi.begin();i!=elevi.end();++i)
                                cout<<(*i)<<"----------------------------\n";
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                    else if (comanda_admin_elev=='2')
                    {
                        elev *e;
                        e=new elev;
                        cin>>*e;
                        cout<<"\nApasati orice tasta pentru a continua!\n";
                        comanda_useless=getch();
                        system("CLS");
                        int ok=1;
                        for (auto it=elevi.begin();it!=elevi.end();++it)
                        {
                            elev e1;
                            e1=(*it);
                            if (e1==*e)
                                ok=0;
                        }
                        if (ok==0)
                        {
                            setcolor(4);
                            cout<<"Elementul se afla deja in baza de date!\n";
                            setcolor(7);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                        else
                        {
                            elevi.insert(*e);
                            setcolor(10);
                            cout<<"Elementul a fost introdus cu succes!\n\n";
                            setcolor(7);
                            cout<<"Apasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                        delete e;
                    }
                    else if (comanda_admin_elev=='4')
                        if (elevi.empty() !=0)
                        {
                            setcolor(4);
                            cout<<"Nu exista elevi in baza de date!\n";
                            setcolor(7);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                        else
                        {
                            for (auto i=elevi.begin();i!=elevi.end();++i)
                                {
                                    elev e=(*i);
                                    e.total_pret_carti_imprumutate();
                                    cout<<"----------------------------\n";
                                }
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                    else if (comanda_admin_elev=='3')
                    {
                        if (elevi.empty() != 0)
                            {setcolor(4);
                            cout<<"Nu exista elevi in baza de date!\n";
                            setcolor(7);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                            }
                        else
                        {
                            cout<<"Elevi existenti in baza de date:\n\n";
                            for (auto i=elevi.begin();i!=elevi.end();++i)
                            {
                                elev e;
                                e=(*i);
                                cout<<e.get_nume()<<" "<<e.get_prenume()<<'\n';
                            }
                            cout<<"\nIntroduceti numele elevului pe care doriti sa il modificati!\n";
                            char aux1[100];
                            cin>>aux1;
                            cout<<"\nIntroduceti prenumele elevului pe care doriti sa il modificati!\n";
                            char aux[100];
                            cin.get();
                            cin.getline(aux,100);
                            string s(aux);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                            set <elev>::iterator it;
                            for (it=elevi.begin();it!=elevi.end();++it)
                            {
                                elev e;
                                e=(*it);
                                if (strcmp(e.get_nume(),aux1)==0&&e.get_prenume()==s)
                                    break;
                            }
                            if (it==elevi.end())
                            {
                                setcolor(4);
                                cout<<"Elevul nu exista in baza de date!\n";
                                setcolor(7);
                                cout<<"\nApasati orice tasta pentru a continua!\n";
                                comanda_useless=getch();
                                system("CLS");
                            }
                            else
                            {
                                cout<<"Alegeti optiunea pentru a selecta ce doriti sa modificati!\n";
                                cout<<"1. numele elevului;\n";
                                cout<<"2. prenumele elevului;\n";
                                cout<<"3. media anuala a elevului;\n";
                                cout<<"4. starea de bursier;\n";
                                cout<<"5. cartile imprumutate;\n";
                                cout<<"\tIntroduceti optiunea dorita!\n";
                                comanda_schimbare_elev=getch();
                                system("CLS");
                                if (comanda_schimbare_elev=='1')
                                {
                                    elev e=(*it);
                                    string nume_vechi=e.get_nume();
                                    cout<<"Introduceti noul nume!\n";
                                    char nume[100];
                                    cin.getline(nume,100);
                                    elevi.erase(e);
                                    e.set_nume(nume);
                                    elevi.insert(e);
                                    cout<<"Numele elevului a fost schimbat din "<<nume_vechi<<" in "<<nume<<"!\n";
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                }
                                else if (comanda_schimbare_elev=='2')
                                {
                                    elev e=(*it);
                                    string nume_vechi=e.get_prenume();
                                    cout<<"Introduceti noul prenume!\n";
                                    char nume[100];
                                    cin.getline(nume,100);
                                    string s(nume);
                                    elevi.erase(e);
                                    e.set_prenume(s);
                                    elevi.insert(e);
                                    cout<<"Preumele elevului a fost schimbat din "<<nume_vechi<<" in "<<s<<"!\n";
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                }
                                else if (comanda_schimbare_elev=='3')
                                {
                                    elev e=(*it);
                                    float medie_veche=e.get_media_anuala();
                                    cout<<"Introduceti noua medie!\n";
                                    float medie;
                                    cin>>medie;
                                    elevi.erase(e);
                                    e.set_media_anuala(medie);
                                    elevi.insert(e);
                                    cout<<"Media elevului a fost schimbata din "<<medie_veche<<" in "<<medie<<"!\n";
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                }
                                else if (comanda_schimbare_elev=='4')
                                {
                                    elev e=(*it);
                                    cout<<"Introduceti noua stare de bursier (1-DA/0-NU)!\n";
                                    bool bursa;
                                    cin>>bursa;
                                    elevi.erase(e);
                                    e.set_bursier(bursa);
                                    elevi.insert(e);
                                    cout<<"Starea de bursier a elevului a fost schimbata!\n";
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                }
                                else if (comanda_schimbare_elev=='5')
                                {
                                    elev e=(*it);
                                    cout<<"Introduceti noul numar de carti imprumutate!\n";
                                    int nr_carti;
                                    cin>>nr_carti;
                                    elevi.erase(e);
                                    carte* carti_noi=new carte[nr_carti];
                                    cin.get();
                                    cout<<"Introduceti noile carti imprumutate!\n";
                                    for (int i=0;i<nr_carti;++i)
                                        {
                                            cout<<"Numele cartii:\n";
                                            char aux1[100];
                                            cin.getline(aux1,100);
                                            string s1(aux1);
                                            cout<<"Prenumele autorului:\n";
                                            cin.getline(aux1,100);
                                            char aux2[100];
                                            cout<<"Numele autorului:\n";
                                            cin.getline(aux2,100);
                                            string s2(aux2);
                                            float pret;
                                            cout<<"Pretul cartii:\n";
                                            cin>>pret;
                                            cin.get();
                                            cout<<"Editura:\n";
                                            cin.getline(aux2,100);
                                            string s3(aux2);
                                            autor aaux(aux1,s2);
                                            carte caux(s1,aaux,s3,pret);
                                            carti_noi[i]=caux;
                                            cout<<"\n";
                                        }
                                    e.set_carti_imprumutate(carti_noi,nr_carti);
                                    elevi.insert(e);
                                    cout<<"Cartile imprumutate ale elevului au fost schimbate!\n";
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                }
                    }
                    }
                    }
                    else if (comanda_admin_elev=='5')
                    {
                        if (elevi.empty() != 0)
                            {setcolor(4);
                            cout<<"Nu exista elevi in baza de date!\n";
                            setcolor(7);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                            }
                        else
                        {
                            cout<<"Elevi existenti in baza de date:\n\n";
                            for (auto i=elevi.begin();i!=elevi.end();++i)
                            {
                                elev e;
                                e=(*i);
                                cout<<e.get_nume()<<" "<<e.get_prenume()<<'\n';
                            }
                            cout<<"\nIntroduceti numele elevului caruia doriti sa ii adaugati o carte!\n";
                            char aux1[100];
                            cin>>aux1;
                            cout<<"\nIntroduceti prenumele elevului caruia doriti sa ii adaugati o carte!\n";
                            char aux[100];
                            cin.get();
                            cin.getline(aux,100);
                            string s(aux);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                            set <elev>::iterator it;
                            for (it=elevi.begin();it!=elevi.end();++it)
                            {
                                elev e;
                                e=(*it);
                                if (strcmp(e.get_nume(),aux1)==0&&e.get_prenume()==s)
                                    break;
                            }
                            if (it==elevi.end())
                            {
                                setcolor(4);
                                cout<<"Elevul nu exista in baza de date!\n";
                                setcolor(7);
                                cout<<"\nApasati orice tasta pentru a continua!\n";
                                comanda_useless=getch();
                                system("CLS");
                            }
                            else
                            {
                                cout<<"Introduceti cartea pe care doriti sa o adaugati!\n";
                                cout<<"Numele cartii:\n";
                                char aux1[100];
                                cin.getline(aux1,100);
                                string s1(aux1);
                                cout<<"Prenumele autorului:\n";
                                cin.getline(aux1,100);
                                char aux2[100];
                                cout<<"Numele autorului:\n";
                                cin.getline(aux2,100);
                                string s2(aux2);
                                float pret;
                                cout<<"Pretul cartii:\n";
                                cin>>pret;
                                cin.get();
                                cout<<"Editura:\n";
                                cin.getline(aux2,100);
                                string s3(aux2);
                                autor aaux(aux1,s2);
                                carte caux(s1,aaux,s3,pret);
                                elev e=(*it);
                                int nr_carti=e.get_nr_carti_imprumutate();
                                nr_carti++;
                                carte* carti_vechi=e.get_carti_imprumutate();
                                carte* carti_noi=new carte[nr_carti];
                                for (int i=0;i<nr_carti-1;++i)
                                    carti_noi[i]=carti_vechi[i];
                                carti_noi[nr_carti-1]=caux;
                                elevi.erase(e);
                                e.set_carti_imprumutate(carti_noi,nr_carti);
                                elevi.insert(e);
                                cout<<"Cartea a fost introdusa cu succes!\n";
                                cout<<"\nApasati orice tasta pentru a continua!\n";
                                comanda_useless=getch();
                                system("CLS");

                            }
                    }
                    }
                }
            else if (comanda_admin=='5') //carti
                while (true)
                {
                    meniu_admin_carti();
                    comanda_admin_carti=getch();
                    system("CLS");
                    if (comanda_admin_carti=='5')
                        break;
                    else if (comanda_admin_carti=='1')
                        if (carti.empty() != 0)
                            {setcolor(4);
                            cout<<"Nu exista carti in baza de date!\n";
                            setcolor(7);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                            }
                        else
                        {
                            for (int i=0;i<carti.size();++i)
                                cout<<carti[i]<<"----------------------------\n";
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                    else if (comanda_admin_carti=='2')
                    {
                        carte c_aux;
                        cin>>c_aux;
                        cout<<"\nApasati orice tasta pentru a continua!\n";
                        comanda_useless=getch();
                        system("CLS");
                        int ok=1;
                        for (int i=0;i<carti.size();++i)
                            if (carti[i]==c_aux)
                            {
                                setcolor(4);
                                cout<<"Elementul se afla deja in baza de date!\n";
                                setcolor(7);
                                cout<<"\nApasati orice tasta pentru a continua!\n";
                                ok=0;
                                comanda_useless=getch();
                                system("CLS");
                                break;
                            }
                        if (ok==1)
                        {
                            carti.push_back(c_aux);
                            setcolor(10);
                            cout<<"Elementul a fost introdus cu succes!\n\n";
                            setcolor(7);
                            cout<<"Apasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                    }
                    else if (comanda_admin_carti=='4')
                        if (carti.empty() != 0)
                            {setcolor(4);
                            cout<<"Nu exista carti in baza de date!\n";
                            setcolor(7);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                            }
                        else
                        {
                            for (int i=0;i<carti.size();++i)
                            {
                                carti[i].disponibilitate();
                                cout<<"----------------------------\n";
                            }
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                    else if (comanda_admin_carti=='3')
                        if (carti.empty() != 0)
                            {setcolor(4);
                            cout<<"Nu exista carti in baza de date!\n";
                            setcolor(7);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                            }
                        else
                        {
                            cout<<"Carti existente in baza de date:\n";
                            for (int i=0;i<carti.size();++i)
                                cout<<carti[i].get_nume()<<'\n';
                            cout<<"\nIntroduceti numele cartii pe care doriti sa o modificati!\n";
                            char aux[100];
                            cin.getline(aux,100);
                            string s(aux);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                            int poz=-1;
                            for (int i=0;i<carti.size();++i)
                                if (carti[i].get_nume()==s)
                                    poz=i;
                            if (poz==-1)
                            {
                                setcolor(4);
                                cout<<"Cartea nu exista in baza de date!\n";
                                setcolor(7);
                                cout<<"\nApasati orice tasta pentru a continua!\n";
                                comanda_useless=getch();
                                system("CLS");
                            }
                            else
                            {
                                cout<<"Alegeti optiunea pentru a selecta ce doriti sa modificati!\n";
                                cout<<"1. numele cartii;\n";
                                cout<<"2. autorul cartii;\n";
                                cout<<"3. pretul cartii;\n";
                                cout<<"4. editura cartii;\n";
                                cout<<"5. conditia exemplarelor cartii;\n";
                                cout<<"6. starea de imprumut a exemplarelor cartii;\n";
                                cout<<"\tIntroduceti optiunea dorita!\n";
                                comanda_schimbare_carte=getch();
                                system("CLS");
                                if (comanda_schimbare_carte=='1')
                                {
                                    string nume_vechi=carti[poz].get_nume();
                                    cout<<"Introduceti noul nume!\n";
                                    char nume[100];
                                    cin.getline(nume,100);
                                    string s1(nume);
                                    carti[poz].set_nume(s1);
                                    cout<<"\nNumele cartii a fost schimbat din "<<nume_vechi<<" in "<<s1<<"!\n";
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                }
                                else if (comanda_schimbare_carte=='2')
                                {
                                    autor a_vechi=carti[poz].get_autor_carte();
                                    cout<<"Introduceti noul prenume al autorului!\n";
                                    char nume[100];
                                    cin.getline(nume,100);
                                    char prenume[100];
                                    cout<<"Introduceti noul nume al autorului!\n";
                                    cin.getline(prenume,100);
                                    string s2(prenume);
                                    autor a2(nume,prenume);
                                    carti[poz].set_autor_carte(a2);
                                    cout<<"\nAutorul a fost schimbat din "<<a_vechi.get_prenume()<<" "<<a_vechi.get_nume()<<" in "<<nume<<" "<<prenume<<"!\n";
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                }
                                else if (comanda_schimbare_carte=='3')
                                {
                                    float pret_vechi=carti[poz].get_pret();
                                    cout<<"Introduceti noul pret al cartii!\n";
                                    float pret;
                                    cin>>pret;
                                    carti[poz].set_pret(pret);
                                    cout<<"\nPretul cartii a fost schimbat din "<<pret_vechi<<" lei in "<<pret<<" lei!\n";
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                }
                                else if (comanda_schimbare_carte=='5')
                                {
                                    cout<<"Introduceti noul numar de exemplare al cartii!\n";
                                    int nr_ex;
                                    cin>>nr_ex;
                                    string cond[100];
                                    cout<<"Introduceti, pentru fiecare exemplar, noua conditie (noua, uzata)!\n";
                                    for (int i=0;i<nr_ex;++i)
                                        cin>>cond[i];
                                    carti[poz].set_conditie_exemplare(cond,nr_ex);
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                }
                                else if (comanda_schimbare_carte=='6')
                                {
                                    cout<<"Introduceti noul numar de exemplare al cartii!\n";
                                    int nr_ex;
                                    cin>>nr_ex;
                                    bool imp[100];
                                    cout<<"Introduceti, pentru fiecare exemplar, daca este imprumutat sau nu (1/0)!\n";
                                    for (int i=0;i<nr_ex;++i)
                                        cin>>imp[i];
                                    carti[poz].set_imprumuturi(imp,nr_ex);
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                }
                                else if (comanda_schimbare_carte=='4')
                                {
                                    cout<<"Introduceti noua editura a cartii!\n";
                                    char nume[100];
                                    cin.getline(nume,100);
                                    string s3(nume);
                                    string editura_veche=carti[poz].get_editura();
                                    carti[poz].set_editura(s3);
                                    cout<<"\nEditura cartii a fost schimbata din "<<editura_veche<<" in "<<nume<<"!\n";
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                }

                            }
                }
                }
            else if (comanda_admin=='6') //manuale
                while (true)
                {
                    meniu_admin_manuale();
                    comanda_admin_manuale=getch();
                    system("CLS");
                    if (comanda_admin_manuale=='6')
                        break;
                    else if (comanda_admin_manuale=='1')
                        if (manuale.empty()!=0)
                        {
                            setcolor(4);
                            cout<<"Nu exista carti in baza de date!\n";
                            setcolor(7);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                        else
                        {
                            for (auto it=manuale.begin();it!=manuale.end();++it)
                                cout<<(*it)<<"----------------------------\n";
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                    else if (comanda_admin_manuale=='4')
                        if (manuale.empty() != 0)
                            {setcolor(4);
                            cout<<"Nu exista manuale in baza de date!\n";
                            setcolor(7);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                            }
                        else
                        {
                            for (auto it=manuale.begin();it!=manuale.end();++it)
                            {
                                manual m1;
                                m1=(*it);
                                m1.disponibilitate();
                                cout<<"----------------------------\n";
                            }
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                    else if (comanda_admin_manuale=='5')
                        if (manuale.empty() != 0)
                            {setcolor(4);
                            cout<<"Nu exista manuale in baza de date!\n";
                            setcolor(7);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                            }
                        else
                        {
                            for (auto it=manuale.begin();it!=manuale.end();++it)
                            {
                                manual m1;
                                m1=(*it);
                                m1.nevoie_inlocuire();
                                cout<<"----------------------------\n";
                            }
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                    else if (comanda_admin_manuale=='2')
                    {
                        manual m_aux;
                        cin>>m_aux;
                        cout<<"\nApasati orice tasta pentru a continua!\n";
                        comanda_useless=getch();
                        system("CLS");
                        int ok=1;
                        for (auto it=manuale.begin();it!=manuale.end();++it)
                            {
                                manual m1;
                                m1=(*it);
                                if (m1==m_aux)
                                {
                                    setcolor(4);
                                    cout<<"Elementul se afla deja in baza de date!\n";
                                    setcolor(7);
                                    cout<<"Apasati orice tasta pentru a continua!\n";
                                    ok=0;
                                    comanda_useless=getch();
                                    system("CLS");
                                    break;
                                }
                            }
                        if (ok==1)
                        {
                            manuale.push_back(m_aux);
                            setcolor(10);
                            cout<<"Elementul a fost introdus cu succes!\n\n";
                            setcolor(7);
                            cout<<"Apasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                        }
                    }
                    else if (comanda_admin_manuale=='3')
                        if (manuale.empty() != 0)
                            {setcolor(4);
                            cout<<"Nu exista manuale in baza de date!\n";
                            setcolor(7);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                            }
                        else
                        {
                            cout<<"Manuale existente in baza de date:\n";
                            for (auto it=manuale.begin();it!=manuale.end();++it)
                            {
                                manual m1;
                                m1=(*it);
                                cout<<m1.get_nume()<<'\n';
                            }
                            cout<<"\nIntroduceti numele manualului pe care doriti sa il modificati!\n";
                            char aux[100];
                            cin.getline(aux,100);
                            string s(aux);
                            cout<<"\nApasati orice tasta pentru a continua!\n";
                            comanda_useless=getch();
                            system("CLS");
                            int poz=-1;
                            list<manual>::iterator it;
                            for (it=manuale.begin();it!=manuale.end();++it)
                            {
                                manual m1;
                                m1=(*it);
                                if (m1.get_nume()==s)
                                    break;
                            }
                            if (it==manuale.end())
                            {
                                setcolor(4);
                                cout<<"Manualul nu exista in baza de date!\n";
                                setcolor(7);
                                cout<<"\nApasati orice tasta pentru a continua!\n";
                                comanda_useless=getch();
                                system("CLS");
                            }
                            else
                            {
                                manual m_sch=(*it);
                                manuale.remove(m_sch);
                                cout<<"Alegeti optiunea pentru a selecta ce doriti sa modificati!\n";
                                cout<<"1. numele manualului;\n";
                                cout<<"2. autorul manualului;\n";
                                cout<<"3. pretul manualului;\n";
                                cout<<"4. editura manualului;\n";
                                cout<<"5. conditia exemplarelor manualului;\n";
                                cout<<"6. starea de imprumut a exemplarelor manualului;\n";
                                cout<<"7. materia manualului.\n";
                                cout<<"\tIntroduceti optiunea dorita!\n";
                                comanda_schimbare_manual=getch();
                                system("CLS");
                                if (comanda_schimbare_manual=='1')
                                {
                                    string nume_vechi=m_sch.get_nume();
                                    cout<<"Introduceti noul nume!\n";
                                    char nume[100];
                                    cin.getline(nume,100);
                                    string s1(nume);
                                    m_sch.set_nume(s1);
                                    manuale.push_back(m_sch);
                                    cout<<"\nNumele manualului a fost schimbat din "<<nume_vechi<<" in "<<s1<<"!\n";
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                }
                                else if (comanda_schimbare_manual=='2')
                                {
                                    autor a_vechi=m_sch.get_autor_carte();
                                    cout<<"Introduceti noul prenume al autorului!\n";
                                    char nume[100];
                                    cin.getline(nume,100);
                                    char prenume[100];
                                    cout<<"Introduceti noul nume al autorului!\n";
                                    cin.getline(prenume,100);
                                    string s2(prenume);
                                    autor a2(nume,prenume);
                                    m_sch.set_autor_carte(a2);
                                    manuale.push_back(m_sch);
                                    cout<<"\nAutorul a fost schimbat din "<<a_vechi.get_prenume()<<" "<<a_vechi.get_nume()<<" in "<<nume<<" "<<prenume<<"!\n";
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                }
                                else if (comanda_schimbare_manual=='3')
                                {
                                    float pret_vechi=m_sch.get_pret();
                                    cout<<"Introduceti noul pret al manualului!\n";
                                    float pret;
                                    cin>>pret;
                                    m_sch.set_pret(pret);
                                    manuale.push_back(m_sch);
                                    cout<<"\nPretul manualului a fost schimbat din "<<pret_vechi<<" lei in "<<pret<<" lei!\n";
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                }
                                else if (comanda_schimbare_manual=='5')
                                {
                                    cout<<"Introduceti noul numar de exemplare al manualului!\n";
                                    int nr_ex;
                                    cin>>nr_ex;
                                    string cond[100];
                                    cout<<"Introduceti, pentru fiecare exemplar, noua conditie (noua, uzata)!\n";
                                    for (int i=0;i<nr_ex;++i)
                                        cin>>cond[i];
                                    m_sch.set_conditie_exemplare(cond,nr_ex);
                                    manuale.push_back(m_sch);
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                }
                                else if (comanda_schimbare_manual=='6')
                                {
                                    cout<<"Introduceti noul numar de exemplare al manualului!\n";
                                    int nr_ex;
                                    cin>>nr_ex;
                                    bool imp[100];
                                    cout<<"Introduceti, pentru fiecare exemplar, daca este imprumutat sau nu (1/0)!\n";
                                    for (int i=0;i<nr_ex;++i)
                                        cin>>imp[i];
                                    m_sch.set_imprumuturi(imp,nr_ex);
                                    manuale.push_back(m_sch);
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                }
                                else if (comanda_schimbare_manual=='4')
                                {
                                    cout<<"Introduceti noua editura a manualului!\n";
                                    char nume[100];
                                    cin.getline(nume,100);
                                    string s3(nume);
                                    string editura_veche=m_sch.get_editura();
                                    m_sch.set_editura(s3);
                                    manuale.push_back(m_sch);
                                    cout<<"\nEditura manualului a fost schimbata din "<<editura_veche<<" in "<<nume<<"!\n";
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                }
                                else if (comanda_schimbare_manual=='7')
                                {
                                    cout<<"Introduceti noua materie a manualului!\n";
                                    char nume[100];
                                    cin.getline(nume,100);
                                    string s3(nume);
                                    string materie_veche=m_sch.get_materie();
                                    m_sch.set_materie(s3);
                                    manuale.push_back(m_sch);
                                    cout<<"\nMateria manualului a fost schimbata din "<<materie_veche<<" in "<<nume<<"!\n";
                                    cout<<"\nApasati orice tasta pentru a continua!\n";
                                    comanda_useless=getch();
                                    system("CLS");
                                }

                            }
                }

                }
        }
        else if (comanda=='2')
        {
            while(true){
            cout<<"Sunteti logat ca: ";
            setcolor(10);
            cout<<"UTILIZATOR\n\n";
            setcolor(7);
            cout<<"Optiuni disponibile:\n";
            cout<<"1. vizualizarea cartilor existente;\n";
            cout<<"2. afisarea, pentru fiecare carte, a numarului de exemplare disponibile;\n";
            cout<<"3. imprumutarea unei carti;\n";
            cout<<"4. afisarea costului total al cartilor imprumutate pana acum (de un elev);\n";
            setcolor(14);
            cout<<"5. intoarcere la meniul principal;\n";
            setcolor(7);
            cout<<"\tIntroduceti optiunea dorita!\n";
            comanda_elev=getch();
            system("CLS");
            if (comanda_elev=='1')
                {
                    if (carti.empty()==0)
                    {
                        cout<<"Carti existente:\n\n";
                        for (int i=0;i<carti.size();++i)
                        {
                            cout<<i+1<<". ";
                            cout<<carti[i].get_nume()<<" - ";
                            autor a_aux=carti[i].get_autor_carte();
                            cout<<a_aux.get_prenume()<<" "<<a_aux.get_nume();
                            cout<<" ("<<carti[i].get_editura()<<", "<<carti[i].get_pret()<<" lei)\n";
                        }
                        cout<<"\nApasati orice tasta pentru a continua!\n";
                        comanda_useless=getch();
                        system("CLS");
                    }
                    else
                    {
                        setcolor(4);
                        cout<<"Nu exista carti introduse! Contactati administratorul.\n";
                        setcolor(7);
                        cout<<"\nApasati orice tasta pentru a continua!\n";
                        comanda_useless=getch();
                        system("CLS");
                    }
                }
            else if (comanda_elev=='2')
                if (carti.empty() != 0)
                    {setcolor(4);
                    cout<<"Nu exista carti in baza de date!\n";
                    setcolor(7);
                    cout<<"\nApasati orice tasta pentru a continua!\n";
                    comanda_useless=getch();
                    system("CLS");
                    }
                else
                    {
                    for (int i=0;i<carti.size();++i)
                    {
                        carti[i].disponibilitate();
                        cout<<"----------------------------\n";
                    }
                    cout<<"\nApasati orice tasta pentru a continua!\n";
                    comanda_useless=getch();
                    system("CLS");
                    }
            else if (comanda_elev=='3')
                {
                    cout<<"Introduceti numele elevului!\n";
                    char aux1_nume[100];
                    cin>>aux1_nume;
                    cout<<"\nIntroduceti prenumele elevului!\n";
                    char aux[100];
                    cin.get();
                    cin.getline(aux,100);
                    string s(aux);
                    set <elev>::iterator it;
                    for (it=elevi.begin();it!=elevi.end();++it)
                    {
                        elev e;
                        e=(*it);
                        if (strcmp(e.get_nume(),aux1_nume)==0&&e.get_prenume()==s)
                            break;
                    }
                    if (it==elevi.end())
                    {
                        cout<<"\nIntroduceti initiala tatalui a elevului!\n";
                        char init;
                        cin>>init;
                        cout<<"\nIntroduceti varsta elevului!\n";
                        int varsta;
                        cin>>varsta;
                        cout<<"\nIntroduceti media anuala a elevului!\n";
                        float medie;
                        cin>>medie;
                        cout<<"\nIntroduceti starea de bursier a elevlului! (1-DA/0-NU)\n";
                        bool bursa;
                        cin>>bursa;
                        cout<<"\nApasati orice tasta pentru a continua!\n";
                        comanda_useless=getch();
                        system("CLS");
                        cin.get();
                        cout<<"Introduceti cartea pe care doriti sa o adaugati!\n";
                        cout<<"Numele cartii:\n";
                        char aux1[100];
                        cin.getline(aux1,100);
                        string s1(aux1);
                        cout<<"Prenumele autorului:\n";
                        cin.getline(aux1,100);
                        char aux2[100];
                        cout<<"Numele autorului:\n";
                        cin.getline(aux2,100);
                        string s2(aux2);
                        float pret;
                        cout<<"Pretul cartii:\n";
                        cin>>pret;
                        cin.get();
                        cout<<"Editura:\n";
                        cin.getline(aux2,100);
                        string s3(aux2);
                        autor aaux(aux1,s2);
                        carte caux(s1,aaux,s3,pret);
                        carte *c_aux=new carte[1];
                        c_aux[0]=caux;
                        elev e(aux1_nume,varsta,medie,bursa,init,s,1,1,c_aux);
                        elevi.insert(e);
                        setcolor(10);
                        cout<<"\nCartea a fost introdusa cu succes!\n";
                        setcolor(7);
                        cout<<"\nApasati orice tasta pentru a continua!\n";
                        comanda_useless=getch();
                        system("CLS");
                    }
                    else
                    {
                        cout<<"\nApasati orice tasta pentru a continua!\n";
                        comanda_useless=getch();
                        system("CLS");
                        cout<<"Introduceti cartea pe care doriti sa o adaugati!\n";
                        cout<<"Numele cartii:\n";
                        char aux1[100];
                        cin.getline(aux1,100);
                        string s1(aux1);
                        cout<<"Prenumele autorului:\n";
                        cin.getline(aux1,100);
                        char aux2[100];
                        cout<<"Numele autorului:\n";
                        cin.getline(aux2,100);
                        string s2(aux2);
                        float pret;
                        cout<<"Pretul cartii:\n";
                        cin>>pret;
                        cin.get();
                        cout<<"Editura:\n";
                        cin.getline(aux2,100);
                        string s3(aux2);
                        autor aaux(aux1,s2);
                        carte caux(s1,aaux,s3,pret);
                        elev e=(*it);
                        int nr_carti=e.get_nr_carti_imprumutate();
                        nr_carti++;
                        carte* carti_vechi=e.get_carti_imprumutate();
                        carte* carti_noi=new carte[nr_carti];
                        for (int i=0;i<nr_carti-1;++i)
                            carti_noi[i]=carti_vechi[i];
                        carti_noi[nr_carti-1]=caux;
                        elevi.erase(e);
                        e.set_carti_imprumutate(carti_noi,nr_carti);
                        elevi.insert(e);
                        setcolor(10);
                        cout<<"\nCartea a fost introdusa cu succes!\n";
                        setcolor(7);
                        cout<<"\nApasati orice tasta pentru a continua!\n";
                        comanda_useless=getch();
                        system("CLS");
                }
                }
            else if (comanda_elev=='4')
                {
                    cout<<"Introduceti numele elevului!\n";
                    char aux1_nume[100];
                    cin>>aux1_nume;
                    cout<<"\nIntroduceti prenumele elevului!\n";
                    char aux[100];
                    cin.get();
                    cin.getline(aux,100);
                    string s(aux);
                    cout<<"\nApasati orice tasta pentru a continua!\n";
                    comanda_useless=getch();
                    system("CLS");
                    set <elev>::iterator it;
                    for (it=elevi.begin();it!=elevi.end();++it)
                    {
                        elev e;
                        e=(*it);
                        if (strcmp(e.get_nume(),aux1_nume)==0&&e.get_prenume()==s)
                            break;
                    }
                    if (it==elevi.end())
                    {
                        setcolor(4);
                        cout<<"Elevul nu exista in baza de date!\n";
                        setcolor(7);
                        cout<<"\nApasati orice tasta pentru a continua!\n";
                        comanda_useless=getch();
                        system("CLS");
                    }
                    else
                    {
                        elev e=(*it);
                        e.total_pret_carti_imprumutate();
                        cout<<"\nApasati orice tasta pentru a continua!\n";
                        comanda_useless=getch();
                        system("CLS");
                    }
                }
            else if (comanda_elev=='5')
                break;
            }
        }
        else if (comanda=='0')
            break;
    }
    return 0;
}
