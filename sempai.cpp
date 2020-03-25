#include <iostream>
using namespace std;

typedef int Dado;

enum posicao {dir, esq};

class noh {
	friend class abb;
	private:
		Dado valor;
		noh* esq;
		noh* dir;
	public:
		noh (Dado d )
		{
			valor=d;
			esq=NULL;
			dir=NULL;
		}
		~noh()
		{
			//não precisa checar se é nulo
			delete esq;
			delete dir;
		}
};
class abb{
	private:
		noh* raiz;
		void percorreEmOrdemAux(noh* atual,int nivel)
		{
			if(atual!=NULL)
			{
				percorreEmOrdemAux(atual->esq,nivel+1);
				cout<<atual->valor<< "/" <<nivel<<" ";
				percorreEmOrdemAux(atual->dir,nivel+1);
			}
		};
		void percorrePreOrdemAux(noh* atual)
		{
			if(atual!=NULL)
			{
				cout<<atual->valor<<" ";
				percorrePreOrdemAux(atual->esq);
				percorrePreOrdemAux(atual->dir);
			}
		};
		void percorrePosOrdemAux(noh* atual)
		{
			if(atual!=NULL)
			{
				percorrePosOrdemAux(atual->esq);
				percorrePosOrdemAux(atual->dir);
				cout<<atual->valor<<" ";
			}
		};
		//menor e maior raiz da subárvore com pai em raizSub
		noh* minimoAux(noh* raizSub)
		{
			while(raizSub->esq != NULL)
			{
				raizSub= raizSub->esq;
			}
			return raizSub;
		};
		noh* maximoAux(noh* raizSub)
		{
			while(raizSub->dir != NULL)
			{
				raizSub= raizSub->dir;
			}
			return raizSub;
		};
		//transplanta o nó novo para o local onde estava o nó antigo
		void transplanta(noh* antigo, noh* novo)
		{
			noh* trans=raiz;
			if(antigo!=raiz)
			{
				while(trans->esq!=antigo and trans->dir!=antigo)
				{
							if(trans->valor > antigo->valor)
							{
								trans = trans->esq;
							}
							else
							{
								trans = trans->dir;
							}
				 }
			}
			else
			{
				trans=NULL;
			}
			if(raiz==antigo)
			{
				raiz=novo;
			}
			 else if (antigo == trans->esq) 
			 {
				  trans->esq = novo;
			 } 
			 else 
			 {
		    	  trans->dir = novo;
			 }
			 if(novo!=NULL )
			 {
				noh* tras=raiz;
				if(novo!=raiz)
				{
					while(tras->esq!=novo and tras->dir!=novo)
					{
								if(tras->valor > novo->valor)
								{
									tras = tras->esq;
								}
								else
								{
									tras = tras->dir;
								}
					 }
				}
				else
				{
					tras=NULL;
				}
				tras=trans;
			 }
		};
	public:
		abb()
		{
			raiz=NULL;
		}
		~abb()
		{
			delete raiz;
		};
		void insere(Dado d)
		{
			noh* novo =new noh(d);
			posicao posInsercao;
			//verifica se a raiz esta vazia
			if(raiz==NULL)
			{
				raiz=novo;
			}
			else
			{
				noh* atual=raiz;
				noh* anterior;
				
				//encontrando ponto de inserção
				while(atual!=NULL)
				{
					anterior = atual;
					if(atual->valor > d)
					{
						atual = atual->esq;
						posInsercao=esq;
					}
					else
					{
						atual = atual->dir;
						posInsercao=dir;
					}
				}
				if(posInsercao==dir)
				{
					anterior->dir = novo;
				}
				else
				{
					anterior->esq = novo;
				}
			}
		};
		void remove(Dado dado)
		{
			noh* nohRemover = busca(dado);
			if(nohRemover!=NULL)
			{
				if(nohRemover->esq==NULL)
				{
					transplanta(nohRemover,nohRemover->dir);
				}
				else if(nohRemover->dir ==NULL)
				{
					transplanta(nohRemover,nohRemover->esq);
				}
				else
				{
					noh* sucessor = minimoAux(nohRemover->dir);
					noh* pseudo=raiz;
					while(pseudo->esq!=sucessor and pseudo->dir!=sucessor)
					{
						if(pseudo->valor > sucessor->valor)
						{
							pseudo = pseudo->esq;
						}
						else
						{
							pseudo = pseudo->dir;
				
						}
					}
					if(pseudo!=nohRemover)
					{
						transplanta(sucessor,sucessor->dir);
						sucessor->dir=nohRemover->dir;
						noh* tenta=raiz;
						while(tenta->esq!=sucessor->dir and tenta->dir!=sucessor->dir)
						{
							if(tenta->valor > sucessor->dir->valor)
							{
								tenta = tenta->esq;
							}
							else
							{
								tenta = tenta->dir;
							}
						}
						tenta=sucessor;
					}
					transplanta(nohRemover,sucessor);
					sucessor->esq=nohRemover->esq;
					noh* remo=raiz;
					while(remo->esq!=sucessor->esq and remo->dir!=sucessor->esq)
					{
						if(remo->valor > sucessor->dir->valor)
						{
							remo = remo->esq;
						}
						else
						{
							remo = remo->dir;
						}
					}
					remo = sucessor;
				}
				nohRemover->esq = NULL;
				nohRemover->dir = NULL;
				delete nohRemover;
			}
		};
		noh* busca(Dado d)
		{
			noh* atual = raiz;
			while (atual != NULL)
			{
				if(atual->valor==d)
				{
					return atual;
				}
				else if(atual->valor > d)
				{
					atual = atual->esq;
				}
				else
				{
					atual = atual->dir;
				}
			}
			return atual;	
		};
		Dado minimo()
		{
			if(raiz!= NULL)
			{
				noh* nohMin=minimoAux(raiz);
				return nohMin->valor;
			}
		};
		Dado maximo()
		{
			if(raiz!= NULL)
			{
				noh* nohMax=maximoAux(raiz);
				return nohMax->valor;
			}
		};
		void percorreEmOrdem()
		{
			percorreEmOrdemAux(raiz,0);
			cout<<endl;
		};
		void percorrePreOrdem()
		{
			percorrePreOrdemAux(raiz);
			cout<<endl;
		};
		void percorrePosOrdem()
		{
			percorrePosOrdemAux(raiz);
			cout<<endl;
		};
};
int main(){
	abb arv;
	int n;
	for (int i = 0; i <5 ; i++)
	{
		cin>>n;
		arv.insere(n);
	}
	arv.percorreEmOrdem();
	arv.remove(4);
	arv.percorreEmOrdem();
	
}
