#include <iostream>
#include <fstream>
using namespace std;

struct tTriangulos{
  int l1;
  int l2;
  int l3;
};

struct tNo{
  tTriangulos tn;
  tNo* proximo;
};

tNo* criaNo(tTriangulos tri){
  tNo* no = new tNo;
  no -> tn = tri;
  no -> proximo = NULL;
  return no;
}

struct tLista{
  tNo* primeiro;
  tNo* ultimo;
  tNo* marcador;
  int tamanho;
};

void inicializaLista(tLista* pLista){
    pLista -> primeiro = NULL;
    pLista -> ultimo = NULL;
    pLista -> marcador = NULL;
    pLista -> tamanho = 0;
}

int obterTamanho(tLista* pLista){
    return (pLista -> tamanho);
}

bool listaVazia(tLista* pLista){
  return (pLista -> tamanho==0);
}

bool finalLista(tLista* pLista){
  return (pLista -> marcador == NULL);
}

void incluirNoFim(tLista* pLista, tTriangulos t){
  tNo* no;
  no = criaNo(t);

  if(listaVazia(pLista)){
    pLista -> primeiro = no; 
  } else {
      pLista -> ultimo -> proximo = no;
  } 
    pLista -> ultimo = no;
    pLista -> marcador = no;
    pLista -> tamanho ++;
}

void imprimirLista(tLista* pLista){
  pLista -> marcador = pLista -> primeiro;
    
    while(!finalLista(pLista)){
      tTriangulos t;
      t = pLista -> marcador -> tn; 

      cout << "\nOs lados do triangulo são:\n " << t.l1 << " " << t.l2 << " " << t.l3;

      pLista -> marcador = pLista -> marcador -> proximo; 
    }
}

void poeNoArquivo(tLista* pLista);

int main(){   

    tTriangulos tri; 
    int a, num;
    tLista* trilista = new tLista; 

do
  {
    cout << "\nPressione 0 para gravar, 1 para ler:\n";
    cin >> a;
        if(a==0)
        {
            cout << "\nInforme o número de triângulos: \n";
            cin >> num; 
            for (int i = 0; i<num; i++){
              cout << "\nInforme os lados\n";

              cin >> tri.l1;
              cin >> tri.l2; 
              cin >> tri.l3;

              incluirNoFim(trilista, tri);
             }
              poeNoArquivo(trilista);
        }
           else if(a==1)
           { 
              ifstream abre;
              tTriangulos tri;
              abre.open("Triangulos.txt", ios::in);
      
              inicializaLista(trilista);

              while(abre >> tri.l1 && abre >> tri.l2 && abre >> tri.l3){
                incluirNoFim(trilista, tri);
              }

              abre.close();              
              imprimirLista(trilista);
           }

   } while ((a!=0)||(a!=1));

}

void poeNoArquivo(tLista* pLista)
{ 
  ofstream poe;
  tTriangulos tri;
  pLista -> marcador = pLista -> primeiro; 
  poe.open("Triangulos.txt", ios::out);

  while(pLista->marcador!=NULL)
   {
      tri = pLista -> marcador -> tn;

      poe << pLista -> marcador -> tn.l1 << " ";
      poe << pLista -> marcador -> tn.l2 << " ";
      poe << pLista -> marcador -> tn.l3 << endl;

      pLista -> marcador = pLista -> marcador -> proximo;
   }

  pLista -> marcador = pLista -> primeiro;
  poe.close();
}