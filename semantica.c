


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


/*
	Esta � a struct que � utilizada na an�lise sint�tica e sem�ntica.
	Ela possui tr�s campos que s�o o token, o tipo e a linha ,podendo guardar esses tr�s elementosem sua estrutura
	que ser�o utilizados posteriormente no processo de backtracking.
*/
typedef struct an
{
	char token[100];
	char tipo [100];
	char linha[100];
}analise;

/*
	Estrutura que armazena a variavel e seu tipo
*/

typedef struct v
{
	char token[100];
	char tipo [100];
	char linha[100];
	char classificacao[100];
}var;


/*
	Estrutura que armazena a funcao e seu tipo
*/

typedef struct f
{
	char token[100];
	char tipo [100];
	char linha[100];
	char classificacao[100];
}funcao;


/*
	Prot�tipo das Fun��es
	- An�lise L�xica
	- An�lise Sint�tica
	- An�lise Semantica
*/

int analise_lexica(FILE *abrir,FILE *saida);
int analise_sintatica(FILE * saida);
void analise_semantica(FILE * saida);int main()
{


	FILE *abrir;
	FILE *saida;
	int flag=0;
	int flag1=0;

	flag = analise_lexica(abrir,saida);
	if(flag==0)
	{
		flag1 = analise_sintatica(saida);
//		printf("FLAG1:%d\n",flag1);

		if(flag1==0)
		{
			analise_semantica(saida);
		}
	}

	system("PAUSE");
	return 0;
}




/*
	ETAPA 04 - An�lise Sem�ntica
	
	
	Nesta etapa � realizada a checagem de tipos das v�ri�veis e comandos que utilizam express�es booleanas ou inteiras
	como � o caso dos comandos se,atribui��o e enquanto.
	
	
	No caso da atribui��o ela s� trata somente as atribui��es b�sicas n�o aceitando express�es, pois na minha vis�o
	n�o lhe caberia por n�o ter uma fun��o tern�ria, mas este processo de checagem de express�es � feito no comando se
	e enquanto.
	
	Caso seja necess�rio tamb�m para a atribui��o ele pode ser facilmente implementado.
	
	Como procedimentos n�o tem retorno eles n�o s�o aceitos nos comandos provocando erro sem�ntico.
	
	
	Como t�cnica criei duas estruturas que armazenam todas as vari�veis e seus tipos e conforme a �rvore � analisada
	ela checa se a vari�vel ou fun��o j� foram declaradas e caso seja afirmativo ela verifica a outra parte analisando se
	ambas s�o do mesmo tipo, caso sejam a linha com a cla�sula � impressa, caso contr�rio � impresso a linha com o erro 
	sem�ntico.
	
	
	A �nica exce��o � que quando eu tenho uma atribui��o, caso uma fun��o seja usada como ID recebendo algo, ele d� erro
	sem�ntico pois uma fun��o n�o pode receber valores, s� v�ri�veis.
	
	
	Existe uma pasta com todos os testes e erros feitos no corpo do arquivo, demonstrando a funcionalidade do mesmo.
	
	As tr�s partes funcionam em conjunto tanto � que para uma executar a anterior tem que ter sido bem-sucedida, ent�o caso
	teste algo que � capturado pela an�lise sint�tica o erro aparecer� e a an�lise sem�ntica n�o ser� executada.
	
	
	Projeto de Compiladores Conclu�do por Yuri Serrano
	
	ATTE Yuri Serrano
	
	
	
		

	
	
*/

void analise_semantica(FILE * saida)
{
	int i=0,j=0,contadorToken=0,flag=0,percorre=0,sentinela=0,imprime=0,k=0,auximprime=0;
	int contadorVar=0,contadorFuncao=0;
	int auxContadorVar=0,contVar=0;
	int auxContadorFuncao=0,contFuncao=0;
	int posVar=-1,posFuncao=-1;
	int flag1=-1,flag2=-1;
	int indicador = 0;
	char *entrada;
	char caracter,c;
	analise semantica[1000];
	var variaveis[1000];
	funcao funcoes[1000];
	char resposta[100]  ={};
	char aux[100]  ={};
	saida = fopen("saida.txt","r");

	if(saida == NULL)
		printf("Erro, nao foi possivel abrir o arquivo\n");


	entrada = malloc(sizeof(char)*2000);

	/*
		Aqui eu leio todos os caracteres do arquivo.
		T�cnica de buffering ,a mesma que foi utilizada na an�lise l�xica.
	*/
	while((caracter=fgetc(saida))!=EOF)
	{
		entrada[i]=caracter;
		i++;
	}
    entrada[i]='\0';


	/*
		Aqui todos os caracteres eu formo strings (representam os tokens, tipos e linhas)
		e vou adicionando no vetor de structs.
	*/
    while(j<strlen(entrada))
    {
		c=entrada[j];

        token:
		while(isalpha(c) || isdigit(c) || ispunct(c))
		{
			sprintf(aux, "%c", c);
            strcat(resposta,aux);
            j=j+1;
            c=entrada[j];
		}
        if(flag == 0)
        {
            strcpy(semantica[contadorToken].token,resposta);
            flag=1;
            memset(&resposta[0], 0, sizeof(resposta));
            memset(&aux[0], 0, sizeof(aux));
            goto avanca;
        }
        if(flag == 1)
        {
            strcpy(semantica[contadorToken].tipo,resposta);
            flag=2;
            memset(&resposta[0], 0, sizeof(resposta));
            memset(&aux[0], 0, sizeof(aux));
            goto avanca;
        }
        if(flag == 2)
        {
		    strcpy(semantica[contadorToken].linha,resposta);
            flag=0;
            memset(&resposta[0], 0, sizeof(resposta));
            memset(&aux[0], 0, sizeof(aux));
            contadorToken += 1;
            goto avanca;
        }
		avanca:
        while(c ==  32 || c == 9)
        {
            j = j+1;
            c = entrada[j];
        }
        if(c == 10)
        {
            j = j+1;
            c = entrada[j];
            goto token;
        }


		/*
			Aqui a �ltima posi��o do vetor de structs cont�m o "#"
			para indicar que o vetorde structs terminou.
		*/
        if(c == 0)
        {

            strcpy(semantica[contadorToken].token,"#");
            strcpy(semantica[contadorToken].tipo,"#");
            strcpy(semantica[contadorToken].linha,"#");
            break;
        }
        goto token;

    }
    
    
    
    /*
    
	
	  printf("Teste de Captura de Tokens\n\n\n");
    printf("Token:%s - Tipo:%s - Linha:%s\n",semantica[0].token,semantica[0].tipo,semantica[0].linha);
	printf("Token:%s - Tipo:%s - Linha:%s\n",semantica[1].token,semantica[1].tipo,semantica[1].linha);
    printf("Token:%s - Tipo:%s - Linha:%s\n",semantica[2].token,semantica[2].tipo,semantica[2].linha);
    printf("Token:%s - Tipo:%s - Linha:%s\n",semantica[3].token,semantica[3].tipo,semantica[3].linha);
	printf("Token:%s - Tipo:%s - Linha:%s\n",semantica[4].token,semantica[4].tipo,semantica[4].linha);
	printf("Token:%s - Tipo:%s - Linha:%s\n",semantica[5].token,semantica[5].tipo,semantica[5].linha);
	printf("\n\n Fim do Teste \n\n\n");
    inicio:
    	
    */	
    inicio:	
    posVar=-1;
    posFuncao=-1;
    flag1=-1;
    flag2 = -1;
    
    
    /*
    	Elimina o programa da leitura
    */
    if((strcmp(semantica[percorre].token,"programa") ==0) && (strcmp(semantica[percorre+1].tipo,"ID") ==0 )&& (strcmp(semantica[percorre+2].token,";") ==0))
	{
		
		percorre+=3;
		goto inicio;
		
	}
	
	/*
    	Elimina os procedimentos da leitura
    */
	if((strcmp(semantica[percorre].token,"procedimento") ==0) && (strcmp(semantica[percorre+1].tipo,"ID") ==0 )&& (strcmp(semantica[percorre+2].token,";") ==0))
	{
		
		percorre+=3;
		goto inicio;
	}   
	
	
  	
	
	
	
	/*
		Vai percorrendo e excluindo qualquer token que n�o seja var,funcao,se e enquanto e que n�o seja do tipo ID
	*/
    while(1)
    {
    	
    	if(((strcmp(semantica[percorre].token,"var") == 0) || (strcmp(semantica[percorre].token,"funcao") == 0) || (strcmp(semantica[percorre].token,"se") == 0) || (strcmp(semantica[percorre].token,"enquanto") == 0)
    		|| ((strcmp(semantica[percorre].tipo,"ID") == 0) && (strcmp(semantica[percorre+1].token,":=") == 0))))
    	{
    		//printf("While Saida:%s %s %s %s\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token);
    		break;
    	}
    	
    	if((strcmp(semantica[percorre].token,"#") == 0))
    		break;
    
    	percorre+=1;
    }
    
    //printf("Percorre:%d\n",percorre);



	/*
		Aqui s�o armazenadas as vari�veis na estrutura destinada as mesmas
	*/
    if((strcmp(semantica[percorre].token,"var") == 0))
    {
    	percorre+=1;
		ivar:
		var:
    	if((strcmp(semantica[percorre].tipo,"ID") == 0) && (strcmp(semantica[percorre+1].token,":") == 0)
    		&& ( (strcmp(semantica[percorre+2].token,"inteiro") == 0) || (strcmp(semantica[percorre+2].token,"booleano") == 0))
    		&& (strcmp(semantica[percorre+3].token,";") == 0))
    	{
    			strcpy(variaveis[contadorVar].token , semantica[percorre].token);
    			strcpy(variaveis[contadorVar].tipo , semantica[percorre].tipo);
    			strcpy(variaveis[contadorVar].linha ,  semantica[percorre].linha);
    			strcpy(variaveis[contadorVar].classificacao ,  semantica[percorre+2].token);
    			
    			
    		
    			contadorVar+=1;
    			percorre+=4;
    			goto var;

    	}
    	auxContadorVar = contadorVar;
    	var1:
    	if((strcmp(semantica[percorre].tipo,"ID") == 0)  )
    	{

    		
    		strcpy(variaveis[contadorVar].token , semantica[percorre].token);
    		strcpy(variaveis[contadorVar].tipo ,  semantica[percorre].tipo);
    		strcpy(variaveis[contadorVar].linha ,  semantica[percorre].linha);
	


    		if((strcmp(semantica[percorre+1].token,":") == 0))
    		{
    			if(((strcmp(semantica[percorre+2].token,"inteiro") == 0) || (strcmp(semantica[percorre+2].token,"booleano") == 0))  && ((strcmp(semantica[percorre+3].token,";") == 0)))
    			{

    				for(i = auxContadorVar;i <= contadorVar;i++)
    				{
    					strcpy(variaveis[i].classificacao , semantica[percorre+2].token);
					}
					percorre+=4;
					contadorVar+=1;
					goto ivar;
				}
			}

    		if((strcmp(semantica[percorre+1].token,",") == 0))
    		{

    			contadorVar+=1;
    			percorre+=2;
    			goto var1;
			}


    	}


    	goto inicio;
    }

	/*
		Aqui s�o armazenadas as fun��es na estrutura destinada as mesmas
	*/
    func:
     if((strcmp(semantica[percorre].token,"funcao") == 0))
    {
    	percorre+=1;


     	if((strcmp(semantica[percorre].tipo,"ID") == 0) && (strcmp(semantica[percorre+1].token,":") == 0)
    		&& ( (strcmp(semantica[percorre+2].token,"inteiro") == 0) || (strcmp(semantica[percorre+2].token,"booleano") == 0))
    		&& (strcmp(semantica[percorre+3].token,";") == 0))
    	{

    			strcpy(funcoes[contadorFuncao].token , semantica[percorre].token);
    			strcpy(funcoes[contadorFuncao].tipo ,  semantica[percorre].tipo);
    			strcpy(funcoes[contadorFuncao].linha ,  semantica[percorre].linha);
    			strcpy(funcoes[contadorFuncao].classificacao ,  semantica[percorre+2].token);
    			contadorVar+=1;
    			percorre+=4;
    			goto inicio;

		}

	}

	/*
		Aqui inicia-se a checagem das atribui��es.
	*/
	if((strcmp(semantica[percorre].tipo,"ID") == 0) && (strcmp(semantica[percorre+1].token,":=") == 0) && ((strcmp(semantica[percorre+2].tipo,"ID") == 0)
	|| (strcmp(semantica[percorre+2].token,"verdadeiro") == 0)   || (strcmp(semantica[percorre+2].token,"falso") == 0 ) || (strcmp(semantica[percorre+2].tipo,"NUM") == 0  ) ) )
	{
//			printf("IF\n");
				for(i=0;i<=contadorVar;i++)
				{
					if(strcmp(variaveis[i].token,semantica[percorre].token) == 0)
					{
//						printf("AV\n");
						posVar=i;


					}
				}


			
				if(posVar == -1)
				{
						posVar=-1;
						flag1 = -1;
						flag2 = -1;
						indicador = 1;
						printf("Linha: %s - ",semantica[percorre].linha);
						goto erro_semantico;
				}

				if((strcmp(variaveis[posVar].classificacao,"inteiro") ==0)  )
				{

					flag1 = 1;

				}

				if((strcmp(variaveis[posVar].classificacao,"booleano") ==0)  )
				{

					flag1 = 0;

				}
		


				if((strcmp(semantica[percorre+2].token,"falso") == 0 ) )
				{
					flag2=0;
				}

				if((strcmp(semantica[percorre+2].token,"verdadeiro") == 0 ) )
				{
					flag2=0;
				}

				if((strcmp(semantica[percorre+2].tipo,"NUM") == 0 ) )
				{
					flag2=1;
				}
				posVar=-1;
				posFuncao=-1;

				if((strcmp(semantica[percorre+2].tipo,"ID") == 0 ) )
				{
					for(i=0;i<=contadorVar;i++)
					{
						if(strcmp(variaveis[i].token,semantica[percorre+2].token) == 0)
						{
//							printf("YU\n");
							posVar=i;


						}
					}


					for(i=0;i<=contadorFuncao;i++)
					{
						if(strcmp(funcoes[i].token,semantica[percorre+2].token) == 0)
						{
//							printf("YD\n");
							posFuncao=i;


						}
					}

				}
				
				if(flag1 == 1 && flag2 == 1)
				{
//					printf("YR\n");
					posVar=-1;
					posFuncao=-1;
					flag1 = -1;
					flag2 = -1;
					printf("%s %s %s %s  - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token);
					percorre+=4;
					goto inicio;


				}
				if(flag1 == 0 && flag2 == 0)
				{
//					printf("YY\n");
					posVar=-1;
					posFuncao=-1;
					flag1 = -1;
					flag2 = -1;
					printf("%s %s %s %s  - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token);
					percorre+=4;
					goto inicio;


				}
				
				
				if(posVar != -1)
				{
//					printf("TT\n");
					if(strcmp(variaveis[posVar].classificacao,"inteiro")==0)
					{
						flag2=1;
					}

					if(strcmp(variaveis[posVar].classificacao,"booleano")==0)
					{
						flag2=0;
					}

				}
				if(posFuncao != -1)
				{
//					printf("TY\n");
					if(strcmp(funcoes[posFuncao].classificacao,"inteiro")==0)
					{
						flag2=1;
					}
					if(strcmp(funcoes[posFuncao].classificacao,"booleano")==0)
					{
						flag2=0;
					}

				}

				if(flag1 == 1 && flag2 == 1)
				{
//					printf("RR\n");
					posVar=-1;
					posFuncao=-1;
					flag1 = -1;
					flag2 = -1;
					printf("%s %s %s %s  - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token);
					percorre+=4;
					goto inicio;


				}
				if(flag1 == 0 && flag2 == 0)
				{
//					printf("RY\n");
					posVar=-1;
					posFuncao=-1;
					flag1 = -1;
					flag2 = -1;
					printf("%s %s %s %s  - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token);
					percorre+=4;
					goto inicio;


				}
				
				if(posVar == -1  && posFuncao == -1)
				{
					posVar=-1;
					posFuncao=-1;
					flag1 = -1;
					flag2 = -1;
					indicador = 1;
					printf("Linha: %s - ",semantica[percorre].linha);
					goto erro_semantico;
				}


				if(flag1 != flag2)
				{
					posVar=-1;
					posFuncao=-1;
					flag1 = -1;
					flag2 = -1;
					indicador=1;
					printf("Linha: %s - ",semantica[percorre].linha);
					goto erro_semantico;
				}


				
	}

	if((strcmp(semantica[percorre].tipo,"ID") == 0) && (strcmp(semantica[percorre+1].token,":=") == 0) && ((strcmp(semantica[percorre+2].token,"+")) || (strcmp(semantica[percorre+2].token,"-")) ) && ((strcmp(semantica[percorre+3].tipo,"ID") == 0)
	|| (strcmp(semantica[percorre+3].token,"verdadeiro") == 0)   || (strcmp(semantica[percorre+3].token,"falso") == 0 ) || (strcmp(semantica[percorre+3].tipo,"NUM") == 0  ) ) )
	{

				for(i=0;i<=contadorVar;i++)
				{
					if(strcmp(variaveis[i].token,semantica[percorre].token) == 0)
					{
						posVar=i;


					}
				}


				if(posVar == -1)
				{
						posVar=-1;
						posFuncao=-1;
						flag1 = -1;
						flag2 = -1;
						indicador=1;
						printf("Linha: %s - ",semantica[percorre].linha);
						goto erro_semantico;
				}

				if((strcmp(variaveis[posVar].classificacao,"inteiro") ==0)  )
				{

					flag1 = 1;

				}

				if((strcmp(variaveis[posVar].classificacao,"booleano") ==0) )
				{

					flag1 = 0;

				}

				if((strcmp(semantica[percorre+3].token,"falso") == 0 ) )
				{
					flag2=0;
				}

				if((strcmp(semantica[percorre+3].token,"verdadeiro") == 0 ) )
				{
					flag2=0;
				}

				if((strcmp(semantica[percorre+3].tipo,"NUM") == 0 ) )
				{
					flag2=1;
				}
				
					if(flag1 == 1 && flag2 == 1)
				{

					printf("%s %s %s %s %s  - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token);
					percorre+=5;
					posVar=-1;
					posFuncao=-1;
					flag1 = -1;
					flag2 = -1;
					goto inicio;


				}
				if(flag1 == 0 && flag2 == 0)
				{

					posVar=-1;
					posFuncao=-1;
					flag1 = -1;
					flag2 = -1;
					printf("%s %s %s %s %s  - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token);
					percorre+=5;
					goto inicio;


				}

				posVar=-1;
				posFuncao=-1;

				if((strcmp(semantica[percorre+3].tipo,"ID") == 0 ) )
				{
					for(i=0;i<=contadorVar;i++)
					{
						if(strcmp(variaveis[i].token,semantica[percorre+3].token) == 0)
						{
							posVar=i;


						}
					}


					for(i=0;i<=contadorFuncao;i++)
					{
						if(strcmp(funcoes[i].token,semantica[percorre+3].token) == 0)
						{
							posFuncao=i;


						}
					}
				}
				if(posVar == -1 && posFuncao == -1)
				{
					posVar=-1;
					posFuncao=-1;
					flag1 = -1;
					flag2 = -1;
					indicador=1;
					printf("Linha: %s - ",semantica[percorre].linha);
					goto erro_semantico;
				}

				if(posVar != -1)
				{
					if(strcmp(variaveis[posVar].classificacao,"inteiro")==0)
					{
						flag2=1;
					}
					if(strcmp(variaveis[posVar].classificacao,"booleano")==0)
					{
						flag2=0;
					}

				}
				if(posFuncao != -1)
				{
					if(strcmp(funcoes[posFuncao].classificacao,"inteiro")==0)
					{
						flag2=1;
					}
					if(strcmp(funcoes[posFuncao].classificacao,"booleano")==0)
					{
						flag2=0;
					}

				}

				if(flag1 == 1 && flag2 == 1)
				{

					printf("%s %s %s %s %s  - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token);
					percorre+=5;
					posVar=-1;
					posFuncao=-1;
					flag1 = -1;
					flag2 = -1;
					goto inicio;


				}
				if(flag1 == 0 && flag2 == 0)
				{

					posVar=-1;
					posFuncao=-1;
					flag1 = -1;
					flag2 = -1;
					printf("%s %s %s %s %s  - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token);
					percorre+=5;
					goto inicio;


				}

				if(flag1 != flag2)
				{
					posVar=-1;
					posFuncao=-1;
					flag1 = -1;
					flag2 = -1;
					indicador =1;
					printf("Linha: %s - ",semantica[percorre].linha);
					goto erro_semantico;
				}


	


	}


	/*
		Aqui inicia-se o processo de an�lise dos comandos se e enquanto
	*/
	

	if(strcmp(semantica[percorre].token,"se") == 0 && (strcmp(semantica[percorre+1].token,"(") == 0) && ((strcmp(semantica[percorre+2].tipo,"ID") == 0)
	|| (strcmp(semantica[percorre+2].tipo,"NUM") == 0) || (strcmp(semantica[percorre+2].token,"falso") == 0) || (strcmp(semantica[percorre+2].token,"verdadeiro") == 0))
	&& (strcmp(semantica[percorre+3].token,")") == 0))
	{
		for(i=0;i<=contadorVar;i++)
		{
			if(strcmp(variaveis[i].token,semantica[percorre+2].token) == 0)
			{
				posVar=i;


			}
		}


		for(i=0;i<=contadorFuncao;i++)
		{
			if(strcmp(funcoes[i].token,semantica[percorre+2].token) == 0)
			{
				posFuncao=i;


			}
		}
		if((strcmp(semantica[percorre+2].token,"falso") == 0 ) )
		{
			printf("%s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token);
			percorre+=4;
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			goto inicio;
		}

		if((strcmp(semantica[percorre+2].token,"verdadeiro") == 0 ) )
		{
			printf("%s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token);
			percorre+=4;
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			goto inicio;
		}

		if((strcmp(semantica[percorre+2].tipo,"NUM") == 0 ) )
		{
			printf("%s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token);
			percorre+=4;
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			goto inicio;
		}

		if(posVar == -1 && posFuncao == -1)
		{
				posVar=-1;
				posFuncao=-1;
				flag1 = -1;
				flag2 = -1;
				indicador=1;
				printf("Linha: %s - ",semantica[percorre].linha);
				goto erro_semantico;
		}
		else
		{
			printf("%s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token);
			percorre+=4;
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			goto inicio;
		}


	}



	if(strcmp(semantica[percorre].token,"enquanto") == 0 && (strcmp(semantica[percorre+1].token,"(") == 0) && ((strcmp(semantica[percorre+2].tipo,"ID") == 0)
	|| (strcmp(semantica[percorre+2].tipo,"NUM") == 0) || (strcmp(semantica[percorre+2].token,"falso") == 0) || (strcmp(semantica[percorre+2].token,"verdadeiro") == 0)
	) && (strcmp(semantica[percorre+3].token,")") == 0))
	{
		for(i=0;i<=contadorVar;i++)
		{
			if(strcmp(variaveis[i].token,semantica[percorre+2].token) == 0)
			{
				posVar=i;


			}
		}


		for(i=0;i<=contadorFuncao;i++)
		{
			if(strcmp(funcoes[i].token,semantica[percorre+2].token) == 0)
			{
				posFuncao=i;


			}
		}

		if((strcmp(semantica[percorre+2].token,"falso") == 0 ) )
		{
			printf("%s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token);
			percorre+=4;
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			goto inicio;
		}

		if((strcmp(semantica[percorre+2].token,"verdadeiro") == 0 ) )
		{
			printf("%s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token);
			percorre+=4;
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			goto inicio;
		}

		if((strcmp(semantica[percorre+2].tipo,"NUM") == 0 ) )
		{
			printf("%s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token);
			percorre+=4;
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			goto inicio;
		}

		if(posVar == -1 && posFuncao == -1)
		{
				posVar=-1;
				posFuncao=-1;
				flag1 = -1;
				flag2 = -1;
				indicador=1;
				printf("Linha: %s - ",semantica[percorre].linha);
				goto erro_semantico;
		}
		else
		{
			printf("%s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token);
			percorre+=4;
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			goto inicio;
		}


	}



if(strcmp(semantica[percorre].token,"se") == 0 && (strcmp(semantica[percorre+1].token,"(") == 0) && ((strcmp(semantica[percorre+2].token,"+") == 0) ||
  (strcmp(semantica[percorre+2].token,"-") == 0)) && ((strcmp(semantica[percorre+3].tipo,"ID") == 0) || (strcmp(semantica[percorre+3].tipo,"NUM") == 0) ||
  (strcmp(semantica[percorre+3].token,"falso") == 0) || (strcmp(semantica[percorre+3].token,"verdadeiro") == 0))&& (strcmp(semantica[percorre+4].token,")") == 0))
  {
  	for(i=0;i<=contadorVar;i++)
	{
		if(strcmp(variaveis[i].token,semantica[percorre+3].token) == 0)
		{
			posVar=i;


		}
	}


	for(i=0;i<=contadorFuncao;i++)
	{
		if(strcmp(funcoes[i].token,semantica[percorre+3].token) == 0)
		{
			posFuncao=i;


		}
	}

	if((strcmp(semantica[percorre+3].token,"falso") == 0 ) )
	{
		printf("%s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token);
		percorre+=5;
		posVar=-1;
		posFuncao=-1;
		flag1 = -1;
		flag2 = -1;
		goto inicio;
	}

	if((strcmp(semantica[percorre+3].token,"verdadeiro") == 0 ) )
	{
		printf("%s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token);
		percorre+=5;
		posVar=-1;
		posFuncao=-1;
		flag1 = -1;
		flag2 = -1;
		goto inicio;
	}

	if((strcmp(semantica[percorre+3].tipo,"NUM") == 0 ) )
	{
	printf("%s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token);
		percorre+=5;
		posVar=-1;
		posFuncao=-1;
		flag1 = -1;
		flag2 = -1;
		goto inicio;
	}

	if(posVar == -1 && posFuncao == -1)
	{
		posVar=-1;
		posFuncao=-1;
		flag1 = -1;
		flag2 = -1;
		indicador=1;
		printf("Linha: %s - ",semantica[percorre].linha);
		goto erro_semantico;
	}
	else
	{
		printf("%s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token);
		percorre+=5;
		posVar=-1;
		posFuncao=-1;
		flag1 = -1;
		flag2 = -1;
		goto inicio;
	}
  }

  if(strcmp(semantica[percorre].token,"enquanto") == 0 && (strcmp(semantica[percorre+1].token,"(") == 0) && ((strcmp(semantica[percorre+2].token,"+") == 0) ||
    (strcmp(semantica[percorre+2].token,"-") == 0)) && ((strcmp(semantica[percorre+3].tipo,"ID") == 0) || (strcmp(semantica[percorre+3].tipo,"NUM") == 0) ||
    (strcmp(semantica[percorre+3].token,"falso") == 0) || (strcmp(semantica[percorre+3].token,"verdadeiro") == 0))&& (strcmp(semantica[percorre+4].token,")") == 0))
    {
    	for(i=0;i<=contadorVar;i++)
		{
			if(strcmp(variaveis[i].token,semantica[percorre+3].token) == 0)
			{
				posVar=i;


			}
		}


		for(i=0;i<=contadorFuncao;i++)
		{
			if(strcmp(funcoes[i].token,semantica[percorre+3].token) == 0)
			{
				posFuncao=i;


			}
		}

		if((strcmp(semantica[percorre+3].token,"falso") == 0 ) )
		{
				printf("%s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token);
				percorre+=5;
				posVar=-1;
				posFuncao=-1;
				flag1 = -1;
				flag2 = -1;
				goto inicio;
		}

		if((strcmp(semantica[percorre+3].token,"verdadeiro") == 0 ) )
		{
			printf("%s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token);
			percorre+=5;
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			goto inicio;
		}

		if((strcmp(semantica[percorre+3].tipo,"NUM") == 0 ) )
		{
			printf("%s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token);
			percorre+=5;
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			goto inicio;
		}

		if(posVar == -1 && posFuncao == -1)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador=1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}
		else
		{
			printf("%s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token);
			percorre+=5;
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			goto inicio;
		}
    }

    if(strcmp(semantica[percorre].token,"se") == 0 && strcmp(semantica[percorre+1].token,"(") == 0 && (strcmp(semantica[percorre+2].tipo,"ID") == 0
	||strcmp(semantica[percorre+2].tipo,"NUM") == 0 || strcmp(semantica[percorre+2].token,"verdadeiro") == 0  || strcmp(semantica[percorre+2].token,"falso") == 0
    )&& strcmp(semantica[percorre+3].tipo,"ORL") == 0  && (strcmp(semantica[percorre+4].tipo,"ID") == 0 || strcmp(semantica[percorre+4].tipo,"NUM") == 0
    || strcmp(semantica[percorre+4].token,"verdadeiro") == 0  || strcmp(semantica[percorre+4].token,"falso") == 0 )&& strcmp(semantica[percorre+5].token,")") == 0)
    {
	//	printf("Entrei Aqui\n");

		for(i=0;i<=contadorVar;i++)
		{
			if(strcmp(variaveis[i].token,semantica[percorre+2].token) == 0)
			{
	//			printf("Achou\n");
				posVar=i;


			}
		}


		for(i=0;i<=contadorFuncao;i++)
		{
			if(strcmp(funcoes[i].token,semantica[percorre+2].token) == 0)
			{
				posFuncao=i;


			}
		}

		if(posVar == -1 && posFuncao == -1)
		{
			//printf("PosVar\n");
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador = 1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}

		if((strcmp(variaveis[posVar].classificacao,"inteiro") ==0)  )
		{
		//	printf("Inteiro1\n");
			flag1 = 1;

		}

		if((strcmp(variaveis[posVar].classificacao,"booleano") ==0)  )
		{
		//	printf("Booleano1\n");
			flag1 = 0;

		}


		if((strcmp(funcoes[posFuncao].classificacao,"inteiro") ==0)  )
		{

			flag1 = 1;

		}

		if((strcmp(funcoes[posFuncao].classificacao,"booleano") ==0)  )
		{

			flag1 = 0;

		}


		if((strcmp(semantica[percorre+2].token,"falso") == 0 ) )
		{
			flag1=0;
		}

		if((strcmp(semantica[percorre+2].token,"verdadeiro") == 0 ) )
		{
			flag1=0;
		}

		if((strcmp(semantica[percorre+2].tipo,"NUM") == 0 ) )
		{
			flag1=1;
		}



		if((strcmp(semantica[percorre+4].token,"falso") == 0 ) )
		{
		//	printf("Falso\n");
			flag2=0;
		}

		if((strcmp(semantica[percorre+4].token,"verdadeiro") == 0 ) )
		{
			flag2=0;
		}

		if((strcmp(semantica[percorre+4].tipo,"NUM") == 0 ) )
		{
			flag2=1;
		}

		if(flag1 == 1 && flag2 == 1)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token);
			percorre+=6;
			goto inicio;


		}
		if(flag1 == 0 && flag2 == 0)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token);
			percorre+=6;
			goto inicio;


		}

		posVar=-1;
		posFuncao=-1;

		if((strcmp(semantica[percorre+4].tipo,"ID") == 0 ) )
		{
			for(i=0;i<=contadorVar;i++)
			{
				if(strcmp(variaveis[i].token,semantica[percorre+4].token) == 0)
				{
					posVar=i;


				}
			}


			for(i=0;i<=contadorFuncao;i++)
			{
				if(strcmp(funcoes[i].token,semantica[percorre+4].token) == 0)
				{
					posFuncao=i;


				}
			}
		}

		if(posVar == -1  && posFuncao == -1)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador = 1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}

		if(posVar != -1)
		{
			if(strcmp(variaveis[posVar].classificacao,"inteiro")==0)
			{
				flag2=1;
			}

			if(strcmp(variaveis[posVar].classificacao,"booleano")==0)
			{
				flag2=0;
			}

		}



		if(posFuncao != -1)
		{
			if(strcmp(funcoes[posFuncao].classificacao,"inteiro")==0)
			{
				flag2=1;
			}

			if(strcmp(funcoes[posFuncao].classificacao,"booleano")==0)
			{
				flag2=0;
			}

		}

		if(flag1 == 1 && flag2 == 1)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token);
			percorre+=6;
			goto inicio;


		}
		if(flag1 == 0 && flag2 == 0)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token);
			percorre+=6;
			goto inicio;


		}

		if(flag1 != flag2)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador=1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}


		
    }

    if((strcmp(semantica[percorre].token,"enquanto") == 0) && (strcmp(semantica[percorre+1].token,"(") == 0) && ((strcmp(semantica[percorre+2].tipo,"ID") == 0) ||
    (strcmp(semantica[percorre+2].tipo,"NUM") == 0) || (strcmp(semantica[percorre+2].token,"verdadeiro") == 0 ) || (strcmp(semantica[percorre+2].token,"falso") == 0)
    )&& (strcmp(semantica[percorre+3].tipo,"ORL") == 0 ) && ((strcmp(semantica[percorre+4].tipo,"ID") == 0) || (strcmp(semantica[percorre+4].tipo,"NUM") == 0) ||
    (strcmp(semantica[percorre+4].token,"verdadeiro") == 0 ) || (strcmp(semantica[percorre+4].token,"falso") == 0))&& (strcmp(semantica[percorre+5].token,")") == 0))
    {
        for(i=0;i<=contadorVar;i++)
		{
			if(strcmp(variaveis[i].token,semantica[percorre+2].token) == 0)
			{
				posVar=i;

			}
		}


		for(i=0;i<=contadorFuncao;i++)
		{
			if(strcmp(funcoes[i].token,semantica[percorre+2].token) == 0)
			{
				posFuncao=i;

			}
		}

		if(posVar == -1 && posFuncao == -1)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador = 1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}

		if((strcmp(variaveis[posVar].classificacao,"inteiro") ==0)  )
		{

			flag1 = 1;

		}

		if((strcmp(variaveis[posVar].classificacao,"booleano") ==0)  )
		{

			flag1 = 0;

		}


		if((strcmp(funcoes[posFuncao].classificacao,"inteiro") ==0)  )
		{

			flag1 = 1;

		}

		if((strcmp(funcoes[posFuncao].classificacao,"booleano") ==0)  )
		{

			flag1 = 0;

		}


		if((strcmp(semantica[percorre+2].token,"falso") == 0 ) )
		{
			flag1=0;
		}

		if((strcmp(semantica[percorre+2].token,"verdadeiro") == 0 ) )
		{
			flag1=0;
		}

		if((strcmp(semantica[percorre+2].tipo,"NUM") == 0 ) )
		{
			flag1=1;
		}



		if((strcmp(semantica[percorre+4].token,"falso") == 0 ) )
		{
			flag2=0;
		}

		if((strcmp(semantica[percorre+4].token,"verdadeiro") == 0 ) )
		{
			flag2=0;
		}

		if((strcmp(semantica[percorre+4].tipo,"NUM") == 0 ) )
		{
			flag2=1;
		}
		
		if(flag1 == 1 && flag2 == 1)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token);
			percorre+=6;
			goto inicio;


		}
		if(flag1 == 0 && flag2 == 0)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token);
			percorre+=6;
			goto inicio;


		}

		posVar=-1;
		posFuncao=-1;

		if((strcmp(semantica[percorre+4].tipo,"ID") == 0 ) )
		{
			for(i=0;i<=contadorVar;i++)
			{
				if(strcmp(variaveis[i].token,semantica[percorre+4].token) == 0)
				{
					posVar=i;


				}
			}


			for(i=0;i<=contadorFuncao;i++)
			{
				if(strcmp(funcoes[i].token,semantica[percorre+4].token) == 0)
				{
					posFuncao=i;


				}
			}
		}

		if(posVar == -1  && posFuncao == -1)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador = 1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}

		if(posVar != -1)
		{
			if(strcmp(variaveis[posVar].classificacao,"inteiro")==0)
			{
				flag2=1;
			}

			if(strcmp(variaveis[posVar].classificacao,"booleano")==0)
			{
				flag2=0;
			}

		}



		if(posFuncao != -1)
		{
			if(strcmp(funcoes[posFuncao].classificacao,"inteiro")==0)
			{
				flag2=1;
			}

			if(strcmp(funcoes[posFuncao].classificacao,"booleano")==0)
			{
				flag2=0;
			}

		}

		if(flag1 == 1 && flag2 == 1)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token);
			percorre+=6;
			goto inicio;


		}
		if(flag1 == 0 && flag2 == 0)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token);
			percorre+=6;
			goto inicio;


		}

		if(flag1 != flag2)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador=1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}


		
    }



    if((strcmp(semantica[percorre].token,"se") == 0) && (strcmp(semantica[percorre+1].token,"(") == 0) && ((strcmp(semantica[percorre+2].token,"+") == 0)
    || (strcmp(semantica[percorre+2].token,"-") == 0))&& ((strcmp(semantica[percorre+3].tipo,"ID") == 0) || (strcmp(semantica[percorre+3].tipo,"NUM") == 0) ||
    (strcmp(semantica[percorre+3].token,"verdadeiro") == 0) || (strcmp(semantica[percorre+3].token,"falso") == 0))&& (strcmp(semantica[percorre+4].tipo,"ORL") == 0)
    && ((strcmp(semantica[percorre+5].token,"+") == 0) || (strcmp(semantica[percorre+5].token,"-") == 0))&& ((strcmp(semantica[percorre+6].tipo,"ID") == 0) ||
    (strcmp(semantica[percorre+6].tipo,"NUM") == 0) || (strcmp(semantica[percorre+6].token,"verdadeiro") == 0) || (strcmp(semantica[percorre+6].token,"falso") == 0) )
    && (strcmp(semantica[percorre+7].token,")") == 0) )
    {
    	for(i=0;i<=contadorVar;i++)
		{
			if(strcmp(variaveis[i].token,semantica[percorre+3].token) == 0)
			{
				posVar=i;


			}
		}


		for(i=0;i<=contadorFuncao;i++)
		{
			if(strcmp(funcoes[i].token,semantica[percorre+3].token) == 0)
			{
				posFuncao=i;


			}
		}

		if(posVar == -1 && posFuncao == -1)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador = 1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}

		if((strcmp(variaveis[posVar].classificacao,"inteiro") ==0)  )
		{

			flag1 = 1;

		}

		if((strcmp(variaveis[posVar].classificacao,"booleano") ==0)  )
		{

			flag1 = 0;

		}


		if((strcmp(funcoes[posFuncao].classificacao,"inteiro") ==0)  )
		{

			flag1 = 1;

		}

		if((strcmp(funcoes[posFuncao].classificacao,"booleano") ==0)  )
		{

			flag1 = 0;

		}


		if((strcmp(semantica[percorre+3].token,"falso") == 0 ) )
		{
			flag1=0;
		}

		if((strcmp(semantica[percorre+3].token,"verdadeiro") == 0 ) )
		{
			flag1=0;
		}

		if((strcmp(semantica[percorre+3].tipo,"NUM") == 0 ) )
		{
			flag1=1;
		}



		if((strcmp(semantica[percorre+6].token,"falso") == 0 ) )
		{
			flag2=0;
		}

		if((strcmp(semantica[percorre+6].token,"verdadeiro") == 0 ) )
		{
			flag2=0;
		}

		if((strcmp(semantica[percorre+6].tipo,"NUM") == 0 ) )
		{
			flag2=1;
		}

		if(flag1 == 1 && flag2 == 1)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token,semantica[percorre+7].token);
			percorre+=8;
			goto inicio;


		}
		if(flag1 == 0 && flag2 == 0)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token,semantica[percorre+7].token);
			percorre+=8;
			goto inicio;


		}

		posVar=-1;
		posFuncao=-1;

		if((strcmp(semantica[percorre+6].tipo,"ID") == 0 ) )
		{
			for(i=0;i<=contadorVar;i++)
			{
				if(strcmp(variaveis[i].token,semantica[percorre+6].token) == 0)
				{
					posVar=i;


				}
			}


			for(i=0;i<=contadorFuncao;i++)
			{
				if(strcmp(funcoes[i].token,semantica[percorre+6].token) == 0)
				{
					posFuncao=i;


				}
			}
		}

		if(posVar == -1  && posFuncao == -1)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador = 1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}

		if(posVar != -1)
		{
			if(strcmp(variaveis[posVar].classificacao,"inteiro")==0)
			{
				flag2=1;
			}

			if(strcmp(variaveis[posVar].classificacao,"booleano")==0)
			{
				flag2=0;
			}
		}

		if(posFuncao != -1)
		{
			if(strcmp(funcoes[posFuncao].classificacao,"inteiro")==0)
			{
				flag2=1;
			}

			if(strcmp(funcoes[posFuncao].classificacao,"booleano")==0)
			{
				flag2=0;
			}

		}

		if(flag1 == 1 && flag2 == 1)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token,semantica[percorre+7].token);
			percorre+=8;
			goto inicio;


		}
		if(flag1 == 0 && flag2 == 0)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token,semantica[percorre+7].token);
			percorre+=8;
			goto inicio;


		}

		if(flag1 != flag2)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador=1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}


		
    }

    if((strcmp(semantica[percorre].token,"enquanto") == 0) && (strcmp(semantica[percorre+1].token,"(") == 0) && ((strcmp(semantica[percorre+2].token,"+") == 0)
    || (strcmp(semantica[percorre+2].token,"-") == 0))&& ((strcmp(semantica[percorre+3].tipo,"ID") == 0) || (strcmp(semantica[percorre+3].tipo,"NUM") == 0) ||
    (strcmp(semantica[percorre+3].token,"verdadeiro") == 0) || (strcmp(semantica[percorre+3].token,"falso") == 0))&& (strcmp(semantica[percorre+4].tipo,"ORL") == 0)
    && ((strcmp(semantica[percorre+5].token,"+") == 0) || (strcmp(semantica[percorre+5].token,"-") == 0))&& ((strcmp(semantica[percorre+6].tipo,"ID") == 0) ||
    (strcmp(semantica[percorre+6].tipo,"NUM") == 0) || (strcmp(semantica[percorre+6].token,"verdadeiro") == 0) || (strcmp(semantica[percorre+6].token,"falso") == 0))
    && (strcmp(semantica[percorre+7].token,")") == 0) )
    {
        for(i=0;i<=contadorVar;i++)
		{
			if(strcmp(variaveis[i].token,semantica[percorre+3].token) == 0)
			{
				posVar=i;


			}
		}


		for(i=0;i<=contadorFuncao;i++)
		{
			if(strcmp(funcoes[i].token,semantica[percorre+3].token) == 0)
			{
				posFuncao=i;


			}
		}

		if(posVar == -1 && posFuncao == -1)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador = 1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}

		if((strcmp(variaveis[posVar].classificacao,"inteiro") ==0)  )
		{

			flag1 = 1;

		}

		if((strcmp(variaveis[posVar].classificacao,"booleano") ==0)  )
		{

			flag1 = 0;

		}


		if((strcmp(funcoes[posFuncao].classificacao,"inteiro") ==0)  )
		{

			flag1 = 1;

		}

		if((strcmp(funcoes[posFuncao].classificacao,"booleano") ==0)  )
		{

			flag1 = 0;

		}


		if((strcmp(semantica[percorre+3].token,"falso") == 0 ) )
		{
			flag1=0;
		}

		if((strcmp(semantica[percorre+3].token,"verdadeiro") == 0 ) )
		{
			flag1=0;
		}

		if((strcmp(semantica[percorre+3].tipo,"NUM") == 0 ) )
		{
			flag1=1;
		}



		if((strcmp(semantica[percorre+6].token,"falso") == 0 ) )
		{
			flag2=0;
		}

		if((strcmp(semantica[percorre+6].token,"verdadeiro") == 0 ) )
		{
			flag2=0;
		}

		if((strcmp(semantica[percorre+6].tipo,"NUM") == 0 ) )
		{
			flag2=1;
		}
		
		if(flag1 == 1 && flag2 == 1)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token,semantica[percorre+7].token);
			percorre+=8;
			goto inicio;

		}
		if(flag1 == 0 && flag2 == 0)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token,semantica[percorre+7].token);
			percorre+=8;
			goto inicio;


		}

		posVar=-1;
		posFuncao=-1;

		if((strcmp(semantica[percorre+6].tipo,"ID") == 0 ) )
		{
			for(i=0;i<=contadorVar;i++)
			{
				if(strcmp(variaveis[i].token,semantica[percorre+6].token) == 0)
				{
					posVar=i;


				}
			}


			for(i=0;i<=contadorFuncao;i++)
			{
				if(strcmp(funcoes[i].token,semantica[percorre+6].token) == 0)
				{
					posFuncao=i;


				}
			}
		}

		if(posVar == -1  && posFuncao == -1)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador = 1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}

		if(posVar != -1)
		{
			if(strcmp(variaveis[posVar].classificacao,"inteiro")==0)
			{
				flag2=1;
			}

			if(strcmp(variaveis[posVar].classificacao,"booleano")==0)
			{
				flag2=0;
			}

		}



		if(posFuncao != -1)
		{
			if(strcmp(funcoes[posFuncao].classificacao,"inteiro")==0)
			{
				flag2=1;
			}

			if(strcmp(funcoes[posFuncao].classificacao,"booleano")==0)
			{
				flag2=0;
			}

		}

		if(flag1 == 1 && flag2 == 1)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token,semantica[percorre+7].token);
			percorre+=8;
			goto inicio;

		}
		if(flag1 == 0 && flag2 == 0)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s %s- OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token,semantica[percorre+7].token);
			percorre+=8;
			goto inicio;


		}

		if(flag1 != flag2)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador=1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
			
		}


		

    }
    if((strcmp(semantica[percorre].token,"se") == 0) && (strcmp(semantica[percorre+1].token,"(") == 0) && ((strcmp(semantica[percorre+2].token,"+") == 0)
    || (strcmp(semantica[percorre+2].token,"-") == 0) )&&((strcmp(semantica[percorre+3].tipo,"ID") == 0) || (strcmp(semantica[percorre+3].tipo,"NUM") == 0) ||
    (strcmp(semantica[percorre+3].token,"verdadeiro") == 0) || (strcmp(semantica[percorre+3].token,"falso") == 0)) && (strcmp(semantica[percorre+4].tipo,"ORL") == 0)
    && ((strcmp(semantica[percorre+5].tipo,"ID") == 0) || (strcmp(semantica[percorre+5].tipo,"NUM") == 0) || (strcmp(semantica[percorre+5].token,"verdadeiro") == 0)
    || (strcmp(semantica[percorre+5].token,"falso") == 0))&& (strcmp(semantica[percorre+6].token,")") == 0) )
    {
        for(i=0;i<=contadorVar;i++)
		{
			if(strcmp(variaveis[i].token,semantica[percorre+3].token) == 0)
			{
				posVar=i;


			}
		}


		for(i=0;i<=contadorFuncao;i++)
		{
			if(strcmp(funcoes[i].token,semantica[percorre+3].token) == 0)
			{
				posFuncao=i;


			}
		}

		if(posVar == -1 && posFuncao == -1)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador = 1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}

		if((strcmp(variaveis[posVar].classificacao,"inteiro") ==0)  )
		{

			flag1 = 1;

		}

		if((strcmp(variaveis[posVar].classificacao,"booleano") ==0)  )
		{

			flag1 = 0;

		}


		if((strcmp(funcoes[posFuncao].classificacao,"inteiro") ==0)  )
		{

			flag1 = 1;

		}

		if((strcmp(funcoes[posFuncao].classificacao,"booleano") ==0)  )
		{

			flag1 = 0;

		}


		if((strcmp(semantica[percorre+3].token,"falso") == 0 ) )
		{
			flag1=0;
		}

		if((strcmp(semantica[percorre+3].token,"verdadeiro") == 0 ) )
		{
			flag1=0;
		}

		if((strcmp(semantica[percorre+3].tipo,"NUM") == 0 ) )
		{
			flag1=1;
		}



		if((strcmp(semantica[percorre+5].token,"falso") == 0 ) )
		{
			flag2=0;
		}

		if((strcmp(semantica[percorre+5].token,"verdadeiro") == 0 ) )
		{
			flag2=0;
		}

		if((strcmp(semantica[percorre+5].tipo,"NUM") == 0 ) )
		{
			flag2=1;
		}
		
		if(flag1 == 1 && flag2 == 1)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token);
			percorre+=7;
			goto inicio;


		}
		if(flag1 == 0 && flag2 == 0)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token);
			percorre+=7;
			goto inicio;


		}

		posVar=-1;
		posFuncao=-1;

		if((strcmp(semantica[percorre+5].tipo,"ID") == 0 ) )
		{
			for(i=0;i<=contadorVar;i++)
			{
				if(strcmp(variaveis[i].token,semantica[percorre+5].token) == 0)
				{
					posVar=i;


				}
			}


			for(i=0;i<=contadorFuncao;i++)
			{
				if(strcmp(funcoes[i].token,semantica[percorre+5].token) == 0)
				{
					posFuncao=i;


				}
			}
		}

		if(posVar == -1  && posFuncao == -1)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador = 1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}

		if(posVar != -1)
		{
			if(strcmp(variaveis[posVar].classificacao,"inteiro")==0)
			{
				flag2=1;
			}

			if(strcmp(variaveis[posVar].classificacao,"booleano")==0)
			{
				flag2=0;
			}

		}



		if(posFuncao != -1)
		{
			if(strcmp(funcoes[posFuncao].classificacao,"inteiro")==0)
			{
				flag2=1;
			}

			if(strcmp(funcoes[posFuncao].classificacao,"booleano")==0)
			{
				flag2=0;
			}

		}

		if(flag1 == 1 && flag2 == 1)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token);
			percorre+=7;
			goto inicio;


		}
		if(flag1 == 0 && flag2 == 0)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token);
			percorre+=7;
			goto inicio;


		}

		if(flag1 != flag2)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador=1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}


		

    }

    if((strcmp(semantica[percorre].token,"enquanto") == 0) && (strcmp(semantica[percorre+1].token,"(") == 0) && ((strcmp(semantica[percorre+2].token,"+") == 0)
    || (strcmp(semantica[percorre+2].token,"-") == 0)) && ((strcmp(semantica[percorre+3].tipo,"ID") == 0) || (strcmp(semantica[percorre+3].tipo,"NUM") == 0) ||
    (strcmp(semantica[percorre+3].token,"verdadeiro") == 0) || (strcmp(semantica[percorre+3].token,"falso") == 0))&& (strcmp(semantica[percorre+4].tipo,"ORL") == 0)
    &&  ((strcmp(semantica[percorre+5].tipo,"ID") == 0) || (strcmp(semantica[percorre+5].tipo,"NUM") == 0) || (strcmp(semantica[percorre+5].token,"verdadeiro") == 0)
    || (strcmp(semantica[percorre+5].token,"falso") == 0))&& (strcmp(semantica[percorre+6].token,")") == 0) )
    {
        for(i=0;i<=contadorVar;i++)
		{
			if(strcmp(variaveis[i].token,semantica[percorre+3].token) == 0)
			{
				posVar=i;


			}
		}


		for(i=0;i<=contadorFuncao;i++)
		{
			if(strcmp(funcoes[i].token,semantica[percorre+3].token) == 0)
			{
				posFuncao=i;


			}
		}

		if(posVar == -1 && posFuncao == -1)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador = 1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}

		if((strcmp(variaveis[posVar].classificacao,"inteiro") ==0)  )
		{

			flag1 = 1;

		}

		if((strcmp(variaveis[posVar].classificacao,"booleano") ==0)  )
		{

			flag1 = 0;

		}


		if((strcmp(funcoes[posFuncao].classificacao,"inteiro") ==0)  )
		{

			flag1 = 1;

		}

		if((strcmp(funcoes[posFuncao].classificacao,"booleano") ==0)  )
		{

			flag1 = 0;

		}


		if((strcmp(semantica[percorre+3].token,"falso") == 0 ) )
		{
			flag1=0;
		}

		if((strcmp(semantica[percorre+3].token,"verdadeiro") == 0 ) )
		{
			flag1=0;
		}

		if((strcmp(semantica[percorre+3].tipo,"NUM") == 0 ) )
		{
			flag1=1;
		}



		if((strcmp(semantica[percorre+5].token,"falso") == 0 ) )
		{
			flag2=0;
		}

		if((strcmp(semantica[percorre+5].token,"verdadeiro") == 0 ) )
		{
			flag2=0;
		}

		if((strcmp(semantica[percorre+5].tipo,"NUM") == 0 ) )
		{
			flag2=1;
		}
		
		if(flag1 == 1 && flag2 == 1)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token);
			percorre+=7;
			goto inicio;


		}
		if(flag1 == 0 && flag2 == 0)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token);
			percorre+=7;
			goto inicio;


		}
		posVar=-1;
		posFuncao=-1;

		if((strcmp(semantica[percorre+5].tipo,"ID") == 0 ) )
		{
			for(i=0;i<=contadorVar;i++)
			{
				if(strcmp(variaveis[i].token,semantica[percorre+5].token) == 0)
				{
					posVar=i;


				}
			}


			for(i=0;i<=contadorFuncao;i++)
			{
				if(strcmp(funcoes[i].token,semantica[percorre+5].token) == 0)
				{
					posFuncao=i;


				}
			}

		}
		if(posVar == -1  && posFuncao == -1)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador = 1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}

		if(posVar != -1)
		{
			if(strcmp(variaveis[posVar].classificacao,"inteiro")==0)
			{
				flag2=1;
			}

			if(strcmp(variaveis[posVar].classificacao,"booleano")==0)
			{
				flag2=0;
			}

		}



		if(posFuncao != -1)
		{
			if(strcmp(funcoes[posFuncao].classificacao,"inteiro")==0)
			{
				flag2=1;
			}

			if(strcmp(funcoes[posFuncao].classificacao,"booleano")==0)
			{
				flag2=0;
			}

		}

		if(flag1 == 1 && flag2 == 1)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token);
			percorre+=7;
			goto inicio;


		}
		if(flag1 == 0 && flag2 == 0)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token);
			percorre+=7;
			goto inicio;


		}

		if(flag1 != flag2)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador=1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}


		
    }

    if((strcmp(semantica[percorre].token,"se") == 0) && (strcmp(semantica[percorre+1].token,"(") == 0) &&( (strcmp(semantica[percorre+2].tipo,"ID") == 0) ||
	(strcmp(semantica[percorre+2].tipo,"NUM") == 0) ||(strcmp(semantica[percorre+2].token,"verdadeiro") == 0) || (strcmp(semantica[percorre+2].token,"falso") == 0))
    && (strcmp(semantica[percorre+3].tipo,"ORL") == 0) && ((strcmp(semantica[percorre+4].token,"+") == 0) || (strcmp(semantica[percorre+4].token,"-") == 0) )&&
    ((strcmp(semantica[percorre+5].tipo,"ID") == 0) || (strcmp(semantica[percorre+5].tipo,"NUM") == 0) || (strcmp(semantica[percorre+5].token,"verdadeiro") == 0)
    || (strcmp(semantica[percorre+5].token,"falso") == 0))&& (strcmp(semantica[percorre+6].token,")") == 0) )
    {
    	
        for(i=0;i<=contadorVar;i++)
		{
			if(strcmp(variaveis[i].token,semantica[percorre+2].token) == 0)
			{
				posVar=i;


			}
		}


		for(i=0;i<=contadorFuncao;i++)
		{
			if(strcmp(funcoes[i].token,semantica[percorre+2].token) == 0)
			{
				posFuncao=i;


			}
		}

		if(posVar == -1 && posFuncao == -1)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador = 1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}

		if((strcmp(variaveis[posVar].classificacao,"inteiro") ==0)  )
		{

			flag1 = 1;

		}

		if((strcmp(variaveis[posVar].classificacao,"booleano") ==0)  )
		{

			flag1 = 0;

		}


		if((strcmp(funcoes[posFuncao].classificacao,"inteiro") ==0)  )
		{

			flag1 = 1;

		}

		if((strcmp(funcoes[posFuncao].classificacao,"booleano") ==0)  )
		{

			flag1 = 0;

		}


		if((strcmp(semantica[percorre+2].token,"falso") == 0 ) )
		{
			flag1=0;
		}

		if((strcmp(semantica[percorre+2].token,"verdadeiro") == 0 ) )
		{
			flag1=0;
		}

		if((strcmp(semantica[percorre+2].tipo,"NUM") == 0 ) )
		{
			flag1=1;
		}



		if((strcmp(semantica[percorre+5].token,"falso") == 0 ) )
		{
			flag2=0;
		}

		if((strcmp(semantica[percorre+5].token,"verdadeiro") == 0 ) )
		{
			flag2=0;
		}

		if((strcmp(semantica[percorre+5].tipo,"NUM") == 0 ) )
		{
			flag2=1;
		}
		
		if(flag1 == 1 && flag2 == 1)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token);
			percorre+=7;
			goto inicio;


		}
		if(flag1 == 0 && flag2 == 0)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token);
			percorre+=7;
			goto inicio;


		}

		posVar=-1;
		posFuncao=-1;

		if((strcmp(semantica[percorre+5].tipo,"ID") == 0 ) )
		{
			for(i=0;i<=contadorVar;i++)
			{
				if(strcmp(variaveis[i].token,semantica[percorre+5].token) == 0)
				{
					posVar=i;


				}
			}


			for(i=0;i<=contadorFuncao;i++)
			{
				if(strcmp(funcoes[i].token,semantica[percorre+5].token) == 0)
				{
					posFuncao=i;


				}
			}

		}
		if(posVar == -1  && posFuncao == -1)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador = 1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}

		if(posVar != -1)
		{
			if(strcmp(variaveis[posVar].classificacao,"inteiro")==0)
			{
				flag2=1;
			}

			if(strcmp(variaveis[posVar].classificacao,"booleano")==0)
			{
				flag2=0;
			}

		}



		if(posFuncao != -1)
		{
			if(strcmp(funcoes[posFuncao].classificacao,"inteiro")==0)
			{
				flag2=1;
			}

			if(strcmp(funcoes[posFuncao].classificacao,"booleano")==0)
			{
				flag2=0;
			}

		}

		if(flag1 == 1 && flag2 == 1)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token);
			percorre+=7;
			goto inicio;


		}
		if(flag1 == 0 && flag2 == 0)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token);
			percorre+=7;
			goto inicio;


		}

		if(flag1 != flag2)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador=1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}


		
    }


	if((strcmp(semantica[percorre].token,"enquanto") == 0) && (strcmp(semantica[percorre+1].token,"(") == 0) && ((strcmp(semantica[percorre+2].tipo,"ID") == 0) ||
    (strcmp(semantica[percorre+2].tipo,"NUM") == 0) ||(strcmp(semantica[percorre+2].token,"verdadeiro") == 0) || (strcmp(semantica[percorre+2].token,"falso") == 0))
    && (strcmp(semantica[percorre+3].tipo,"ORL") == 0) && ((strcmp(semantica[percorre+4].token,"+") == 0) || (strcmp(semantica[percorre+4].token,"-") == 0) )&&
    ((strcmp(semantica[percorre+5].tipo,"ID") == 0) || (strcmp(semantica[percorre+5].tipo,"NUM") == 0) || (strcmp(semantica[percorre+5].token,"verdadeiro") == 0)
    || (strcmp(semantica[percorre+5].token,"falso") == 0) )&& (strcmp(semantica[percorre+6].token,")") == 0) )
    {
        for(i=0;i<=contadorVar;i++)
		{
			if(strcmp(variaveis[i].token,semantica[percorre+2].token) == 0)
			{
				posVar=i;


			}
		}


		for(i=0;i<=contadorFuncao;i++)
		{
			if(strcmp(funcoes[i].token,semantica[percorre+2].token) == 0)
			{
				posFuncao=i;


			}
		}

		if(posVar == -1 && posFuncao == -1)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador = 1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}

		if((strcmp(variaveis[posVar].classificacao,"inteiro") ==0)  )
		{

			flag1 = 1;

		}

		if((strcmp(variaveis[posVar].classificacao,"booleano") ==0)  )
		{

			flag1 = 0;

		}


		if((strcmp(funcoes[posFuncao].classificacao,"inteiro") ==0)  )
		{

			flag1 = 1;

		}

		if((strcmp(funcoes[posFuncao].classificacao,"booleano") ==0)  )
		{

			flag1 = 0;

		}


		if((strcmp(semantica[percorre+2].token,"falso") == 0 ) )
		{
			flag1=0;
		}

		if((strcmp(semantica[percorre+2].token,"verdadeiro") == 0 ) )
		{
			flag1=0;
		}

		if((strcmp(semantica[percorre+2].tipo,"NUM") == 0 ) )
		{
			flag1=1;
		}



		if((strcmp(semantica[percorre+5].token,"falso") == 0 ) )
		{
			flag2=0;
		}

		if((strcmp(semantica[percorre+5].token,"verdadeiro") == 0 ) )
		{
			flag2=0;
		}

		if((strcmp(semantica[percorre+5].tipo,"NUM") == 0 ) )
		{
			flag2=1;
		}
		
		if(flag1 == 1 && flag2 == 1)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token);
			percorre+=7;
			goto inicio;


		}
		if(flag1 == 0 && flag2 == 0)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token);
			percorre+=7;
			goto inicio;


		}

		posVar=-1;
		posFuncao=-1;

		if((strcmp(semantica[percorre+5].tipo,"ID") == 0 ) )
		{
			for(i=0;i<=contadorVar;i++)
			{
				if(strcmp(variaveis[i].token,semantica[percorre+5].token) == 0)
				{
					posVar=i;


				}
			}


			for(i=0;i<=contadorFuncao;i++)
			{
				if(strcmp(funcoes[i].token,semantica[percorre+5].token) == 0)
				{
					posFuncao=i;


				}
			}

		}
		if(posVar == -1  && posFuncao == -1)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador = 1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}

		if(posVar != -1)
		{
			if(strcmp(variaveis[posVar].classificacao,"inteiro")==0)
			{
				flag2=1;
			}

			if(strcmp(variaveis[posVar].classificacao,"booleano")==0)
			{
				flag2=0;
			}

		}



		if(posFuncao != -1)
		{
			if(strcmp(funcoes[posFuncao].classificacao,"inteiro")==0)
			{
				flag2=1;
			}

			if(strcmp(funcoes[posFuncao].classificacao,"booleano")==0)
			{
				flag2=0;
			}

		}

		if(flag1 == 1 && flag2 == 1)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token);
			percorre+=7;
			goto inicio;


		}
		if(flag1 == 0 && flag2 == 0)
		{

			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			printf("%s %s %s %s %s %s %s - OK\n",semantica[percorre].token,semantica[percorre+1].token,semantica[percorre+2].token,semantica[percorre+3].token,semantica[percorre+4].token,semantica[percorre+5].token,semantica[percorre+6].token);
			percorre+=7;
			goto inicio;


		}

		if(flag1 != flag2)
		{
			posVar=-1;
			posFuncao=-1;
			flag1 = -1;
			flag2 = -1;
			indicador=1;
			printf("Linha: %s - ",semantica[percorre].linha);
			goto erro_semantico;
		}


		

    }
    
    if(strcmp(semantica[percorre].token,"#") == 0)	
	{
		indicador=0;
		goto erro_semantico;
	}
    
    



	erro_semantico:
	if(indicador == 1)
		printf("ERRO SEMANTICO\n\n");

	if(indicador == 0)
		printf("SEM NENHUM ERRO SEMANTICO\n\n");

	fclose(saida);

}


/*

	PLP - ETAPA 03  - An�lise Sint�tica


	Aqui verificamos se todos os tokens foram colocados nas posi��es corretamente pelo usu�rio.
	Com rela��o a etapa anterior eu n�o modifiquei o token do ID, pois nesta etapan�o faria sentido
	visto que n�o iremos tratar o escopo e a duplica��o de vari�veis, mas na an�lise sem�ntica ser�
	feito para a verifica��o de tipos.
	Como haviam algumas incongru�ncias na gram�tica eu editei de modo a parecer com o exemplo que encontra-se
	no doc do projeto, a mesma editada encontra-selogo abaixo:

	Estrutura An�lise Sint�tica


	programa ID ;



	bloco


	la�o (Essa parte pode ocorrer mais de uma vez)

	var   ID : (inteiro|booleano);
	var   ID {,ID} : (inteiro|booleano);
	procedimento  ID;
	funcao ID : (inteiro|booleano);



	inicio


	comando atribuicao ->    ID := ID | NUM | verdadeiro | falso;
	chamada procedimento ->  ID;
	comando enquanto ->      enquanto ( [+|-](ID | NUM | verdadeiro | falso) )  faca (comando se| comando leia| comando escreva | comando retorne | comando enquanto)
	comando enquanto ->      enquanto ( [+|-](ID | NUM | verdadeiro | falso) (<> | = | < | <= | > | >= | e | ou)  [+|-](ID | NUM | verdadeiro | falso) )
	comando se -> 			 se([+|-] (ID|NUM|verdadeiro|falso) entao(comando se| comando leia|comando escreva| comando retorne| comando enquanto)
	comando leia ->          leia (ID);
	comando escreva ->       escreva(ID);
	comando escreva ->       escreva(LIT);
	comando retorno funcao -> retorne  ID;




	fim


	Todos os comandos exceto enquanto , se, faca, entao, inicio , fim, var e senao terminam com ; .

	O comando var do bloco s� pode ser usado uma vez por inicio - fim, pois sua produ��o coloca isso, mas
	ele pode ter dentro dele varias declara��es.

	Caso ap�s o fim eu tenha alguma estrutura do bloco ele leva para l� e o processo ocorre novamente.
	A estrutura do se e do enquanto s�o praticamente iguais mudando os comandos auxiliares que no enquanto � o faca
	e no se o ent�o e o sen�o.

	Ser� impresso as lnhas que est�o OK sintaticamente e caso apare�a algum erro surgir� a mensagem "ERRO SINT�TICO"
	juntamente com o n�mero da linha que esse problema ocorreu, parando a execu��o do problema.

	Observa��o: Os problemas relacionados a sintaxe do programa j� foram tratados na an�lise l�xica,ent�o caso seja
	testado ele ser� acusado como erro l�xico parando a execu��o do programa, n�o indo fazer a an�lise sint�tica.
	A mesma s� � poss�vel caso n�o haja nenhum erro l�xico.



*/

int analise_sintatica(FILE *saida)
{
	int i=0,j=0,contadorToken=0,flag=0,percorre=0,sentinela=0,imprime=0,k=0,auximprime=0,indicador=0;
	char *entrada;
	char caracter,c;
	analise sintatica[1000];
	char resposta[100]  ={};
	char aux[100]  ={};
	saida = fopen("saida.txt","r");

	if(saida == NULL)
		printf("Erro, nao foi possivel abrir o arquivo\n");


	entrada = malloc(sizeof(char)*2000);
	/*
		Aqui eu leio todos os caracteres do arquivo.
		T�cnica de buffering ,a mesma que foi utilizada na an�lise l�xica.
	*/
	while((caracter=fgetc(saida))!=EOF)
	{
		entrada[i]=caracter;
		i++;
	}
            entrada[i]='\0';


	/*
		Aqui todos os caracteres eu formo strings (representam os tokens, tipos e linhas)
		e vou adicionando no vetor de structs.
	*/
    while(j<strlen(entrada))
    {
		c=entrada[j];

        token:
		while(isalpha(c) || isdigit(c) || ispunct(c))
		{
			sprintf(aux, "%c", c);
            strcat(resposta,aux);
            j=j+1;
            c=entrada[j];
		}
        if(flag == 0)
        {
            strcpy(sintatica[contadorToken].token,resposta);
            flag=1;
            memset(&resposta[0], 0, sizeof(resposta));
            memset(&aux[0], 0, sizeof(aux));
            goto avanca;
        }
        if(flag == 1)
        {
            strcpy(sintatica[contadorToken].tipo,resposta);
            flag=2;
            memset(&resposta[0], 0, sizeof(resposta));
            memset(&aux[0], 0, sizeof(aux));
            goto avanca;
        }
        if(flag == 2)
        {
		    strcpy(sintatica[contadorToken].linha,resposta);
            flag=0;
            memset(&resposta[0], 0, sizeof(resposta));
            memset(&aux[0], 0, sizeof(aux));
            contadorToken += 1;
            goto avanca;
        }
		avanca:
        while(c ==  32 || c == 9)
        {
            j = j+1;
            c = entrada[j];
        }
        if(c == 10)
        {
            j = j+1;
            c = entrada[j];
            goto token;
        }


		/*
			Aqui a �ltima posi��o do vetor de structs cont�m o "#"
			para indicar que o vetorde structs terminou.
		*/
        if(c == 0)
        {

            strcpy(sintatica[contadorToken].token,"#");
            strcpy(sintatica[contadorToken].tipo,"#");
            strcpy(sintatica[contadorToken].linha,"#");
            break;
        }
        goto token;

    }


	/*

	//Teste de Captura de Tokens

    printf("Teste de Captura de Tokens\n\n\n");
    printf("Token:%s - Tipo:%s - Linha:%s\n",sintatica[0].token,sintatica[0].tipo,sintatica[0].linha);
	printf("Token:%s - Tipo:%s - Linha:%s\n",sintatica[1].token,sintatica[1].tipo,sintatica[1].linha);
    printf("Token:%s - Tipo:%s - Linha:%s\n",sintatica[2].token,sintatica[2].tipo,sintatica[2].linha);
    printf("Token:%s - Tipo:%s - Linha:%s\n",sintatica[3].token,sintatica[3].tipo,sintatica[3].linha);
	printf("Token:%s - Tipo:%s - Linha:%s\n",sintatica[4].token,sintatica[4].tipo,sintatica[4].linha);
	printf("Token:%s - Tipo:%s - Linha:%s\n",sintatica[5].token,sintatica[5].tipo,sintatica[5].linha);
	printf("\n\n Fim do Teste \n\n\n");

	*/



     /*
        Programa -OK
     */
     printf("PROGRAMA\n\n\n");
    if(strcmp(sintatica[percorre].token,"programa") == 0 )
    {
        percorre+=1;
        imprime+=1;
        if(strcmp(sintatica[percorre].tipo,"ID") == 0)
    	{
            imprime+=1;
            percorre+=1;
            if(strcmp(sintatica[percorre].token,";") == 0)
            {
                percorre+=1;
                imprime+=1;
                if(strcmp(sintatica[percorre].token,"#") == 0)
            	{
            		for(k=0;k<imprime;k++)
                    {
                        printf("%s ",sintatica[k].token);
                    }
                    printf(" -  OK\n");
                	auximprime = imprime;
                    sentinela=1;
					goto analisa;
                }
                if(strcmp(sintatica[percorre].token,"var") == 0 || strcmp(sintatica[percorre].token,"funcao") == 0  || strcmp(sintatica[percorre].token,"fun��o") == 0|| strcmp(sintatica[percorre].token,"procedimento") == 0)
                {

                	for(k=0;k<imprime;k++)
                    {
                        printf("%s ",sintatica[k].token);
                	}
                    printf(" -  OK\n");
                    auximprime = imprime;
                    goto bloco;

            	}
            	else
            	{
            		indicador=1;
            		//printf("1\n");
            		goto erro_sintatico;
				}

            }
            else
            {
            	indicador=1;
            	//printf("2\n");
            	goto erro_sintatico;
            }



        }
        else
    	{
    			indicador=1;
    			//printf("3\n");
            	goto erro_sintatico;
        }

    }
    else
    {
    	indicador=1;
     	//	printf("4\n");
        goto erro_sintatico;
    }


    /*
    	BLOCO
        Var
        Funcao
        Procedimento

        OK


    */

	bloco:
	/*
		Procedimento - OK
	*/
	printf("\n\nBLOCO\n\n");

	if(strcmp(sintatica[percorre].token,"procedimento") == 0)
    {
        imprime+=1;
        percorre+=1;

		if(strcmp(sintatica[percorre].tipo,"ID") == 0)
    	{
            imprime+=1;
            percorre+=1;
            if(strcmp(sintatica[percorre].token,";") == 0)
    		{
            	imprime+=1;
            	percorre+=1;
            	if(strcmp(sintatica[percorre].tipo,"#") == 0)
            	{
            		for(k=auximprime;k<imprime;k++)
                    {
                        printf("%s ",sintatica[k].token);
                    }
                    printf(" -  OK\n");
                	auximprime = imprime;
                    sentinela=1;
					goto analisa;
				}
				if(strcmp(sintatica[percorre].token,"var") == 0 || strcmp(sintatica[percorre].token,"funcao") == 0   || strcmp(sintatica[percorre].token,"fun��o") == 0 || strcmp(sintatica[percorre].token,"procedimento") ==0 )
                {

                	for(k=auximprime;k<imprime;k++)
                    {
                        printf("%s ",sintatica[k].token);
                	}
                    printf(" -  OK\n");
                    auximprime = imprime;
                    goto bloco;

            	}
            	if(strcmp(sintatica[percorre].token,"inicio") == 0)
    			{
            		for(k=auximprime;k<imprime;k++)
                    {
                        printf("%s ",sintatica[k].token);
                	}
                    printf(" -  OK\n");
                    auximprime = imprime;
                    goto comando;

				}
				else
				{
					indicador=1;
					//printf("1\n");
					goto erro_sintatico;
				}
			}
			else
			{
				indicador=1;
				//printf("2\n");
				goto erro_sintatico;
			}
		}
		else
		{
			indicador=1;
			//printf("3\n");
			goto erro_sintatico;
		}
	}



	/*
		Funcao ou Fun��o - OK
	*/
  printf("FUNCAO\n");
	if(strcmp(sintatica[percorre].token,"funcao") == 0 || strcmp(sintatica[percorre].token,"fun��o") == 0 )
	{
		    imprime+=1;
        	percorre+=1;

        	if(strcmp(sintatica[percorre].tipo,"ID") == 0)
    	  	{
    		  	imprime+=1;
        		percorre+=1;

        		if(strcmp(sintatica[percorre].token,":") == 0)
    		  	{
            		imprime+=1;
            		percorre+=1;

            		if(strcmp(sintatica[percorre].token,"inteiro") == 0 || strcmp(sintatica[percorre].token,"booleano") == 0  )
				    {
					    imprime+=1;
            			percorre+=1;

            		 	if(strcmp(sintatica[percorre].token,";") == 0)
    				    {
            			 	imprime+=1;
            			 	percorre+=1;

            			 	if(strcmp(sintatica[percorre].tipo,"#") == 0)
            			 	{
            					for(k=auximprime;k<imprime;k++)
                    			{
                        			printf("%s ",sintatica[k].token);
                    			}
                    			printf(" -  OK\n");
                				auximprime = imprime;
                    			sentinela=1;
								goto analisa;
							}
							if(strcmp(sintatica[percorre].token,"var") == 0 || strcmp(sintatica[percorre].token,"funcao") == 0  ||  strcmp(sintatica[percorre].token,"fun��o") == 0 || strcmp(sintatica[percorre].token,"procedimento") ==0 )
                			{

                				for(k=auximprime;k<imprime;k++)
                    			{
                        			printf("%s ",sintatica[k].token);
                				}
                    			printf(" -  OK\n");
                    			auximprime = imprime;
                    			goto bloco;

            				}
            				if(strcmp(sintatica[percorre].token,"inicio") == 0)
    						{
            					for(k=auximprime;k<imprime;k++)
                    			{
                        			printf("%s ",sintatica[k].token);
                				}
                    			printf(" -  OK\n");
                    			auximprime = imprime;
                    			goto comando;

							}
							else
							{
								indicador=1;
								goto erro_sintatico;
							}

					}
					else
					{
						indicador=1;
						goto erro_sintatico;
					}
				}
				else
				{
					indicador=1;
					goto erro_sintatico;
				}
			}
			else
			{
				indicador=1;
				goto erro_sintatico;
			}
		}
		else
		{
			indicador=1;
			goto erro_sintatico;
		}
	}



	/*
		Var - OK
	*/
	if(strcmp(sintatica[percorre].token,"var") == 0)
	{
		imprime+=1;
		percorre+=1;
		idi:
		if(strcmp(sintatica[percorre].tipo,"ID") == 0)
		{
			imprime+=1;
			percorre+=1;
			if(strcmp(sintatica[percorre].token,":") == 0)
			{
				imprime+=1;
				percorre+=1;
				if(strcmp(sintatica[percorre].token,"inteiro") == 0 || strcmp(sintatica[percorre].token,"booleano") == 0 )
				{
					imprime+=1;
					percorre+=1;
					if(strcmp(sintatica[percorre].token,";") == 0)
					{
						imprime+=1;
						percorre+=1;
						if(strcmp(sintatica[percorre].tipo,"ID") == 0)
            			{

								goto idi;
						}
						if(strcmp(sintatica[percorre].tipo,"#") == 0)
            			 	{
            					for(k=auximprime;k<imprime;k++)
                    			{
                        			printf("%s ",sintatica[k].token);
                    			}
                    			printf(" -  OK\n");
                				auximprime = imprime;
                    			sentinela=1;
								goto analisa;
							}
							if(strcmp(sintatica[percorre].token,"funcao") == 0  ||  strcmp(sintatica[percorre].token,"fun��o") == 0 || strcmp(sintatica[percorre].token,"procedimento") ==0 )
                			{

                				for(k=auximprime;k<imprime;k++)
                    			{
                        			printf("%s ",sintatica[k].token);
                				}
                    			printf(" -  OK\n");
                    			auximprime = imprime;
                    			goto bloco;

            				}
            				if(strcmp(sintatica[percorre].token,"inicio") == 0)
    						{
            					for(k=auximprime;k<imprime;k++)
                    			{
                        			printf("%s ",sintatica[k].token);
                				}
                    			printf(" -  OK\n");
                    			auximprime = imprime;
                    			goto comando;

							}
							else
							{
								indicador=1;
								goto erro_sintatico;
							}
					}
					else
					{
						indicador=1;
						goto erro_sintatico;
					}

				}
				else
				{
					indicador=1;
					goto erro_sintatico;
				}
			}
			virgula:
			if(strcmp(sintatica[percorre].token,",") == 0)
			{
				imprime+=1;
				percorre+=1;
				if(strcmp(sintatica[percorre].tipo,"ID") == 0)
				{
					imprime+=1;
					percorre+=1;

					if(strcmp(sintatica[percorre].token,",") == 0)
					{
						goto virgula;
					}
					if(strcmp(sintatica[percorre].token,":") == 0)
					{
						imprime+=1;
						percorre+=1;
						if(strcmp(sintatica[percorre].token,"inteiro") == 0 || strcmp(sintatica[percorre].token,"booleano") == 0)
						{
							imprime+=1;
							percorre+=1;
							if(strcmp(sintatica[percorre].token,";") == 0)
							{
									imprime+=1;
									percorre+=1;
									if(strcmp(sintatica[percorre].tipo,"ID") == 0)
            			 			{

										goto idi;
									}
									if(strcmp(sintatica[percorre].tipo,"#") == 0)
            			 			{
            							for(k=auximprime;k<imprime;k++)
                    					{
                        					printf("%s ",sintatica[k].token);
                    					}
                    					printf(" -  OK\n");
                						auximprime = imprime;
                    					sentinela=1;
										goto analisa;
									}
									if(strcmp(sintatica[percorre].token,"var") == 0 || strcmp(sintatica[percorre].token,"funcao") == 0  ||  strcmp(sintatica[percorre].token,"fun��o") == 0 || strcmp(sintatica[percorre].token,"procedimento") ==0 )
                					{

                						for(k=auximprime;k<imprime;k++)
                    					{
                        					printf("%s ",sintatica[k].token);
                						}
                    					printf(" -  OK\n");
                    					auximprime = imprime;
                    					goto bloco;

            					    }
            						if(strcmp(sintatica[percorre].token,"inicio") == 0)
    								{
            							for(k=auximprime;k<imprime;k++)
                    					{
                        					printf("%s ",sintatica[k].token);
                						}
                    					printf(" -  OK\n");
                    					auximprime = imprime;
                    					goto comando;

									}
									else
									{
										indicador=1;
										goto erro_sintatico;
									}
							}
							else
							{
								indicador=1;
								goto erro_sintatico;

							}
						}
						else
						{
							indicador=1;
							goto erro_sintatico;
						}
					}
					else
					{
						indicador=1;
						goto erro_sintatico;
					}
				}
				else
				{
					indicador=1;
					goto erro_sintatico;
				}
			}
			else
			{
				indicador=1;
				goto erro_sintatico;
			}

		}
		else
		{
			indicador=1;
			goto erro_sintatico;
		}
	}



	/*
		Comandos

	*/

	comando:
	printf("COMANDO\n\n\n");


	if(strcmp(sintatica[percorre].token,"inicio") == 0 )
	{
		imprime+=1;
		percorre+=1;

		comeco:

		/*
			Leia
		*/
		if(strcmp(sintatica[percorre].token,"leia") == 0 )
		{
			imprime+=1;
			percorre+=1;

			if(strcmp(sintatica[percorre].token,"(") == 0 )
			{
				imprime+=1;
				percorre+=1;

				if(strcmp(sintatica[percorre].tipo,"ID") == 0 )
				{
					imprime+=1;
					percorre+=1;
					if(strcmp(sintatica[percorre].token,")") == 0 )
					{
						imprime+=1;
						percorre+=1;
						if(strcmp(sintatica[percorre].token,";") == 0 )
						{
							imprime+=1;
							percorre+=1;
							if(strcmp(sintatica[percorre].token,"#") == 0)
            			 	{
            			 		indicador=1;
								goto erro_sintatico;
							}
							if(strcmp(sintatica[percorre].token,"se") == 0 || strcmp(sintatica[percorre].token,"enquanto") == 0 || strcmp(sintatica[percorre].token,"escreva") == 0 || strcmp(sintatica[percorre].token,"retorne") == 0 || strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].token,"leia") == 0)
							{
								for(k=auximprime;k<imprime;k++)
                    			{
                        			printf("%s ",sintatica[k].token);
                				}
                    			printf(" -  OK\n");
                    			auximprime = imprime;
								goto comeco;
							}
							if(strcmp(sintatica[percorre].token,"fim") == 0)
							{
								goto fim;
							}
							if(strcmp(sintatica[percorre].token,"senao") == 0 || strcmp(sintatica[percorre].token,"sen�o") == 0 )
							{
								goto comeco;
							}

						}
						else
						{
							indicador=1;
							goto erro_sintatico;
						}
					}
					else
					{
						indicador=1;
						goto erro_sintatico;
					}
				}
				else
				{
					indicador=1;
					goto erro_sintatico;
				}

			}
			else
			{
				indicador=1;
				goto erro_sintatico;
			}

		}


		/*
			Escreva
		*/

		if(strcmp(sintatica[percorre].token,"escreva") == 0 )
		{
			imprime+=1;
			percorre+=1;

			if(strcmp(sintatica[percorre].token,"(") == 0 )
			{
				imprime+=1;
				percorre+=1;
				if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"LIT") == 0)
				{
					imprime+=1;
					percorre+=1;
					if(strcmp(sintatica[percorre].token,")") == 0)
					{
						imprime+=1;
						percorre+=1;
						if(strcmp(sintatica[percorre].token,";") == 0)
						{
							//printf("YURI aqui2\n");
							imprime+=1;
							percorre+=1;
							//printf("%s\n",sintatica[percorre].token);
							if(strcmp(sintatica[percorre].token,"#") == 0)
            			 	{   //printf("Yuri aqui3\n");
            			 		indicador=1;
								goto erro_sintatico;
							}
							if((strcmp(sintatica[percorre].token,"se") == 0 || strcmp(sintatica[percorre].token,"enquanto") == 0 || strcmp(sintatica[percorre].token,"escreva") == 0 || strcmp(sintatica[percorre].token,"retorne") == 0 || strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].token,"leia") == 0))
							{
								//printf("Yuri aqui4\n");
								for(k=auximprime;k<imprime;k++)
                    			{
                        			printf("%s ",sintatica[k].token);
                				}
                    			printf(" -  OK\n");
                    			auximprime = imprime;
								goto comeco;
							}
							if(strcmp(sintatica[percorre].token,"fim") == 0)
							{
								//printf("Yuri aqui5\n");
								goto fim;
							}
							if((strcmp(sintatica[percorre].token,"senao") == 0 || strcmp(sintatica[percorre].token,"sen�o") == 0 ))
							{
								//printf("Yuri aqui\n");
								goto comeco;
							}
						}
						else
						{
							//printf("Yuri aqui6\n");
							indicador=1;
							goto erro_sintatico;
						}
					}
					else
					{
						//printf("Yuri aqui7\n");
						indicador=1;
						goto erro_sintatico;
					}

				}
				else
				{
					indicador=1;
					goto erro_sintatico;
				}
			}
			else
			{
				indicador=1;
				goto erro_sintatico;
			}
		}

		/*
			Retorne

		*/


		if(strcmp(sintatica[percorre].token,"retorne") == 0 )
		{
			imprime+=1;
			percorre+=1;

			if(strcmp(sintatica[percorre].tipo,"ID") == 0)
			{
				imprime+=1;
				percorre+=1;
				if(strcmp(sintatica[percorre].token,";") == 0)
				{
					imprime+=1;
					percorre+=1;
					if(strcmp(sintatica[percorre].token,"#") == 0)
            		{
						goto erro_sintatico;
					}
					if(strcmp(sintatica[percorre].token,"se") == 0 || strcmp(sintatica[percorre].token,"enquanto") == 0 || strcmp(sintatica[percorre].token,"escreva") == 0 || strcmp(sintatica[percorre].token,"retorne") == 0 || strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].token,"leia") == 0)
					{
						for(k=auximprime;k<imprime;k++)
                    	{
                        	printf("%s ",sintatica[k].token);
                		}
                    	printf(" -  OK\n");
                    	auximprime = imprime;
						goto comeco;
					}
					if(strcmp(sintatica[percorre].token,"fim") == 0)
					{
						goto fim;
					}
					if(strcmp(sintatica[percorre].token,"senao") == 0 || strcmp(sintatica[percorre].token,"sen�o") == 0 )
					{
						goto comeco;
					}
				}
				else
				{
					indicador=1;
					goto erro_sintatico;
				}
			}
			else
			{
				indicador=1;
				goto erro_sintatico;
			}
		}

		/*
			Chamada procedimento
		*/

		if(strcmp(sintatica[percorre].tipo,"ID") == 0  && strcmp(sintatica[percorre+1].token,";") == 0)
		{
			imprime+=1;
			percorre+=1;

			if(strcmp(sintatica[percorre].token,";") == 0)
			{
					imprime+=1;
					percorre+=1;
					if(strcmp(sintatica[percorre].token,"#") == 0)
            		{
						goto erro_sintatico;
					}
					if(strcmp(sintatica[percorre].token,"se") == 0 || strcmp(sintatica[percorre].token,"enquanto") == 0 || strcmp(sintatica[percorre].token,"escreva") == 0 || strcmp(sintatica[percorre].token,"retorne") == 0 || strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].token,"leia") == 0)
					{
						for(k=auximprime;k<imprime;k++)
                    	{
                        	printf("%s ",sintatica[k].token);
                		}
                    	printf(" -  OK\n");
                    	auximprime = imprime;
						goto comeco;
					}
					if(strcmp(sintatica[percorre].token,"fim") == 0)
					{
						goto fim;
					}
					if(strcmp(sintatica[percorre].token,"senao") == 0 || strcmp(sintatica[percorre].token,"sen�o") == 0 )
					{
						goto comeco;
					}
			}
			else
			{	indicador=1;
				goto erro_sintatico;
			}
		}


		/*
			Comando Atribui��o
		*/


		if(strcmp(sintatica[percorre].tipo,"ID") == 0 && strcmp(sintatica[percorre+1].token,":=") == 0 && strcmp(sintatica[percorre+2].token,"+") == 0
		|| strcmp(sintatica[percorre+2].token,"-") == 0)
		{
			imprime+=1;
			percorre+=1;

			if(strcmp(sintatica[percorre].token,":=") == 0)
			{
				imprime+=1;
				percorre+=1;

				if(strcmp(sintatica[percorre].token,"+") == 0 || strcmp(sintatica[percorre].token,"-") == 0)
				{
					imprime+=1;
					percorre+=1;

					if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
					||strcmp(sintatica[percorre].token,"verdadeiro") == 0 || strcmp(sintatica[percorre].token,"falso") == 0
					)
					{
						imprime+=1;
						percorre+=1;

						if(strcmp(sintatica[percorre].token,";") == 0)
						{
							imprime+=1;
							percorre+=1;

							if(strcmp(sintatica[percorre].token,"#") == 0)
            				{
								goto erro_sintatico;
							}
							if(strcmp(sintatica[percorre].token,"se") == 0 || strcmp(sintatica[percorre].token,"enquanto") == 0 || strcmp(sintatica[percorre].token,"escreva") == 0 || strcmp(sintatica[percorre].token,"retorne") == 0 || strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].token,"leia") == 0)
							{
								for(k=auximprime;k<imprime;k++)
                    			{
	                        		printf("%s ",sintatica[k].token);
	                			}
                    			printf(" -  OK\n");
                    			auximprime = imprime;
								goto comeco;
							}
							if(strcmp(sintatica[percorre].token,"fim") == 0)
							{
								goto fim;
							}

						}
						else
						{
							indicador=1;
							goto erro_sintatico;
						}
					}
					else
					{
						indicador=1;
						goto erro_sintatico;
					}
				}
				else
				{
					indicador=1;
					goto erro_sintatico;
				}
			}
			else
			{
				indicador=1;
				goto erro_sintatico;
			}

		}

		if(strcmp(sintatica[percorre].tipo,"ID") == 0)
		{
			imprime+=1;
			percorre+=1;

			if(strcmp(sintatica[percorre].token,":=") == 0)
			{
				imprime+=1;
				percorre+=1;
				if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0 || strcmp(sintatica[percorre].token,"verdadeiro") == 0 || strcmp(sintatica[percorre].token,"falso") == 0)
				{
					imprime+=1;
					percorre+=1;
					if(strcmp(sintatica[percorre].token,";") == 0)
					{
						imprime+=1;
						percorre+=1;
						if(strcmp(sintatica[percorre].token,"#") == 0)
            			{
            				indicador=1;
							goto erro_sintatico;
						}
						if(strcmp(sintatica[percorre].token,"se") == 0 || strcmp(sintatica[percorre].token,"enquanto") == 0 || strcmp(sintatica[percorre].token,"escreva") == 0 || strcmp(sintatica[percorre].token,"retorne") == 0 || strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].token,"leia") == 0)
						{
							for(k=auximprime;k<imprime;k++)
                    		{
	                        	printf("%s ",sintatica[k].token);
	                		}
                    		printf(" -  OK\n");
                    		auximprime = imprime;
							goto comeco;
						}
						if(strcmp(sintatica[percorre].token,"fim") == 0)
						{
							goto fim;
						}
					}
					else
					{
						indicador=1;
						goto erro_sintatico;
					}
				}
				else
				{
					indicador=1;
					goto erro_sintatico;
				}

			}
			else
			{
				indicador=1;
				goto erro_sintatico;
			}
		}


		/*
			Comando Enquanto
		*/


		if(strcmp(sintatica[percorre].token,"enquanto") == 0 && (strcmp(sintatica[percorre+1].token,"(") == 0) && ((strcmp(sintatica[percorre+2].tipo,"ID") == 0)
		|| (strcmp(sintatica[percorre+2].tipo,"NUM") == 0) || (strcmp(sintatica[percorre+2].token,"falso") == 0) || (strcmp(sintatica[percorre+2].token,"verdadeiro") == 0)
		)&& (strcmp(sintatica[percorre+3].token,")") == 0))
		{
			imprime+=1;
			percorre+=1;

			if(strcmp(sintatica[percorre].token,"(") == 0)
			{
				imprime+=1;
				percorre+=1;

				if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
				|| strcmp(sintatica[percorre].token,"falso") == 0 || strcmp(sintatica[percorre].token,"verdadeiro") == 0
				)
				{
					imprime+=1;
					percorre+=1;

					if(strcmp(sintatica[percorre].token,")") == 0)
					{
						imprime+=1;
						percorre+=1;

						if(strcmp(sintatica[percorre].token,"faca") == 0)
						{
							imprime+=1;
							percorre+=1;

							if(strcmp(sintatica[percorre].token,"#") == 0)
							{
								indicador=1;
								goto erro_sintatico;
							}
							if(strcmp(sintatica[percorre].token,"fim") == 0)
							{
								indicador=1;
								goto erro_sintatico;
							}
							if(strcmp(sintatica[percorre].token,"se") == 0 || strcmp(sintatica[percorre].token,"enquanto") == 0
							|| strcmp(sintatica[percorre].token,"leia") == 0 || strcmp(sintatica[percorre].token,"escreva") == 0
							|| strcmp(sintatica[percorre].token,"retorne") == 0 || strcmp(sintatica[percorre].tipo,"ID") == 0)
							{
								goto comeco;
							}
						}
						else
						{
							indicador=1;
							goto erro_sintatico;

						}
					}
					else
					{
						indicador=1;
						goto erro_sintatico;
					}
				}
				else
				{
					indicador=1;
					goto erro_sintatico;
				}
			}
			else
			{
				indicador=1;
				goto erro_sintatico;
			}
		}
		if(strcmp(sintatica[percorre].token,"enquanto") == 0 && (strcmp(sintatica[percorre+1].token,"(") == 0) && ((strcmp(sintatica[percorre+2].token,"+") == 0) ||
		(strcmp(sintatica[percorre+2].token,"-") == 0)) && ((strcmp(sintatica[percorre+3].tipo,"ID") == 0) || (strcmp(sintatica[percorre+3].tipo,"NUM") == 0) ||
		(strcmp(sintatica[percorre+3].token,"falso") == 0) || (strcmp(sintatica[percorre+3].token,"verdadeiro") == 0))&& (strcmp(sintatica[percorre+4].token,")") == 0))
		{
			imprime+=1;
			percorre+=1;
			if(strcmp(sintatica[percorre].token,"(") == 0)
			{
				imprime+=1;
				percorre+=1;

				if(strcmp(sintatica[percorre].token,"+") == 0 || strcmp(sintatica[percorre].token,"-") == 0)
				{
					imprime+=1;
					percorre+=1;

					if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
					|| strcmp(sintatica[percorre].token,"verdadeiro") == 0 || strcmp(sintatica[percorre].token,"falso") == 0
					)
					{
						imprime+=1;
						percorre+=1;
						if(strcmp(sintatica[percorre].token,")") == 0)
						{
							imprime+=1;
							percorre+=1;

							if(strcmp(sintatica[percorre].token,"faca") == 0)
							{
								imprime+=1;
								percorre+=1;

								if(strcmp(sintatica[percorre].token,"#") == 0)
								{
									indicador=1;
									goto erro_sintatico;
								}
								if(strcmp(sintatica[percorre].token,"fim") == 0)
								{
									indicador=1;
									goto erro_sintatico;
								}
								if(strcmp(sintatica[percorre].token,"se") == 0 || strcmp(sintatica[percorre].token,"enquanto") == 0
								|| strcmp(sintatica[percorre].token,"leia") == 0 || strcmp(sintatica[percorre].token,"escreva") == 0
								|| strcmp(sintatica[percorre].token,"retorne") == 0 || strcmp(sintatica[percorre].tipo,"ID") == 0)
								{
									goto comeco;
								}
							}
							else
							{
								indicador=1;
								goto erro_sintatico;
							}
						}
						else
						{
							indicador=1;
							goto erro_sintatico;
						}
					}
					else
					{
						indicador=1;
						goto erro_sintatico;
					}
				}
				else
				{
					indicador=1;
					goto erro_sintatico;
				}
			}
			else
			{
				indicador=1;
				goto erro_sintatico;
			}

		}

		if((strcmp(sintatica[percorre].token,"enquanto") == 0) && (strcmp(sintatica[percorre+1].token,"(") == 0) && ((strcmp(sintatica[percorre+2].tipo,"ID") == 0) ||
		(strcmp(sintatica[percorre+2].tipo,"NUM") == 0) || (strcmp(sintatica[percorre+2].token,"verdadeiro") == 0 ) || (strcmp(sintatica[percorre+2].token,"falso") == 0)
		)&& (strcmp(sintatica[percorre+3].tipo,"ORL") == 0 ) && ((strcmp(sintatica[percorre+4].tipo,"ID") == 0) || (strcmp(sintatica[percorre+4].tipo,"NUM") == 0) ||
		(strcmp(sintatica[percorre+4].token,"verdadeiro") == 0 ) || (strcmp(sintatica[percorre+4].token,"falso") == 0))&& (strcmp(sintatica[percorre+5].token,")") == 0))
		{
			imprime+=1;
			percorre+=1;


			if(strcmp(sintatica[percorre].token,"(") == 0)
			{
				imprime+=1;
				percorre+=1;

				if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
				|| strcmp(sintatica[percorre].token,"verdadeiro") == 0 || strcmp(sintatica[percorre].token,"falso") == 0
				)
				{
					imprime+=1;
					percorre+=1;

					if(strcmp(sintatica[percorre].tipo,"ORL") == 0)
					{
						imprime+=1;
						percorre+=1;

						if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
						|| strcmp(sintatica[percorre].token,"verdadeiro") == 0 || strcmp(sintatica[percorre].token,"falso") == 0
						)
						{
							imprime+=1;
							percorre+=1;
							if(strcmp(sintatica[percorre].token,")") == 0)
							{
								imprime+=1;
								percorre+=1;

								if(strcmp(sintatica[percorre].token,"faca") == 0)
								{
									imprime+=1;
									percorre+=1;

									if(strcmp(sintatica[percorre].token,"#") == 0)
									{
										indicador=1;
										goto erro_sintatico;
									}

									if(strcmp(sintatica[percorre].token,"fim") == 0)
									{
										indicador=1;
										goto erro_sintatico;
									}
									if(strcmp(sintatica[percorre].token,"se") == 0 || strcmp(sintatica[percorre].token,"enquanto") == 0
									|| strcmp(sintatica[percorre].token,"leia") == 0 || strcmp(sintatica[percorre].token,"escreva") == 0
									|| strcmp(sintatica[percorre].token,"retorne") == 0 || strcmp(sintatica[percorre].tipo,"ID") == 0)
									{
										goto comeco;
									}
								}
								else
								{
									indicador=1;
									goto erro_sintatico;
								}
							}
							else
							{
								indicador=1;
								goto erro_sintatico;
							}
						}
						else
						{
							indicador=1;
							goto erro_sintatico;
						}
					}
					else
					{
						indicador=1;
						goto erro_sintatico;
					}
				}
				else
				{
					indicador=1;
					goto erro_sintatico;
				}
			}
			else
			{
				indicador=1;
				goto erro_sintatico;
			}

		}
		if((strcmp(sintatica[percorre].token,"enquanto") == 0) && (strcmp(sintatica[percorre+1].token,"(") == 0) && ((strcmp(sintatica[percorre+2].token,"+") == 0)
		|| (strcmp(sintatica[percorre+2].token,"-") == 0))&& ((strcmp(sintatica[percorre+3].tipo,"ID") == 0) || (strcmp(sintatica[percorre+3].tipo,"NUM") == 0) ||
		(strcmp(sintatica[percorre+3].token,"verdadeiro") == 0) || (strcmp(sintatica[percorre+3].token,"falso") == 0))&& (strcmp(sintatica[percorre+4].tipo,"ORL") == 0)
		&& ((strcmp(sintatica[percorre+5].token,"+") == 0) || (strcmp(sintatica[percorre+5].token,"-") == 0))&& ((strcmp(sintatica[percorre+6].tipo,"ID") == 0) ||
		(strcmp(sintatica[percorre+6].tipo,"NUM") == 0) || (strcmp(sintatica[percorre+6].token,"verdadeiro") == 0) || (strcmp(sintatica[percorre+6].token,"falso") == 0))
		&& (strcmp(sintatica[percorre+7].token,")") == 0) )
		{
			imprime+=1;
			percorre+=1;

			if(strcmp(sintatica[percorre].token,"(") == 0)
			{
				imprime+=1;
				percorre+=1;

				if(strcmp(sintatica[percorre].token,"+") == 0 || strcmp(sintatica[percorre].token,"-") == 0)
				{
					imprime+=1;
					percorre+=1;
					if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
					|| strcmp(sintatica[percorre].token,"verdadeiro") == 0 || strcmp(sintatica[percorre].token,"falso") == 0
					)
					{
						imprime+=1;
						percorre+=1;

						if(strcmp(sintatica[percorre].tipo,"ORL") == 0)
						{
							imprime+=1;
							percorre+=1;

							if(strcmp(sintatica[percorre].token,"+") == 0 || strcmp(sintatica[percorre].token,"-") == 0)
							{
								imprime+=1;
								percorre+=1;

								if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
								|| strcmp(sintatica[percorre].token,"verdadeiro") == 0 || strcmp(sintatica[percorre].token,"falso") == 0
								)
								{
									imprime+=1;
									percorre+=1;

									if(strcmp(sintatica[percorre].token,")") == 0)
									{
										imprime+=1;
										percorre+1;

										if(strcmp(sintatica[percorre].token,"faca") == 0)
										{
											imprime+=1;
											percorre+1;
											if(strcmp(sintatica[percorre].token,"#") == 0)
											{
												indicador=1;
												goto erro_sintatico;
											}
											if(strcmp(sintatica[percorre].token,"fim") == 0)
											{
												indicador=1;
												goto erro_sintatico;
											}
											if(strcmp(sintatica[percorre].token,"se") == 0 || strcmp(sintatica[percorre].token,"enquanto") == 0
											|| strcmp(sintatica[percorre].token,"leia") == 0 || strcmp(sintatica[percorre].token,"escreva") == 0
											|| strcmp(sintatica[percorre].token,"retorne") == 0 || strcmp(sintatica[percorre].tipo,"ID") == 0)
											{
												goto comeco;
											}

										}
										else
										{
											indicador=1;
											goto erro_sintatico;
										}
									}
									else
									{
										indicador=1;
										goto erro_sintatico;
									}
								}
								else
								{
									indicador=1;
									goto erro_sintatico;
								}
							}
							else
							{
								indicador=1;
								goto erro_sintatico;
							}
						}
						else
						{
							indicador=1;
							goto erro_sintatico;
						}

					}
					else
					{
						indicador=1;
						goto erro_sintatico;
					}
				}
				else
				{
					indicador=1;
					goto erro_sintatico;
				}
			}
			else
			{
				indicador=1;
				goto erro_sintatico;
			}
		}
		if((strcmp(sintatica[percorre].token,"enquanto") == 0) && (strcmp(sintatica[percorre+1].token,"(") == 0) && ((strcmp(sintatica[percorre+2].token,"+") == 0)
		|| (strcmp(sintatica[percorre+2].token,"-") == 0)) && ((strcmp(sintatica[percorre+3].tipo,"ID") == 0) || (strcmp(sintatica[percorre+3].tipo,"NUM") == 0) ||
		(strcmp(sintatica[percorre+3].token,"verdadeiro") == 0) || (strcmp(sintatica[percorre+3].token,"falso") == 0))&& (strcmp(sintatica[percorre+4].tipo,"ORL") == 0)
		&&  ((strcmp(sintatica[percorre+5].tipo,"ID") == 0) || (strcmp(sintatica[percorre+5].tipo,"NUM") == 0) || (strcmp(sintatica[percorre+5].token,"verdadeiro") == 0)
		|| (strcmp(sintatica[percorre+5].token,"falso") == 0))&& (strcmp(sintatica[percorre+6].token,")") == 0) )
		{

			imprime+=1;
			percorre+=1;

			if(strcmp(sintatica[percorre].token,"(") == 0)
			{
				imprime+=1;
				percorre+=1;

				if(strcmp(sintatica[percorre].token,"+") == 0 || strcmp(sintatica[percorre].token,"-") == 0)
				{
					imprime+=1;
					percorre+=1;
					if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
					|| strcmp(sintatica[percorre].token,"verdadeiro") == 0 || strcmp(sintatica[percorre].token,"falso") == 0
					)
					{
						imprime+=1;
						percorre+=1;

						if(strcmp(sintatica[percorre].tipo,"ORL") == 0)
						{
							imprime+=1;
							percorre+=1;

							if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
							|| strcmp(sintatica[percorre].token,"verdadeiro") == 0 || strcmp(sintatica[percorre].token,"falso") == 0
							)
							{
								imprime+=1;
								percorre+=1;

								if(strcmp(sintatica[percorre].token,")") == 0)
								{
									imprime+=1;
									percorre+=1;

									if(strcmp(sintatica[percorre].token,"faca") == 0)
									{
										imprime+=1;
										percorre+=1;

										if(strcmp(sintatica[percorre].token,"#") == 0)
										{
											indicador=1;
											goto erro_sintatico;
										}
										if(strcmp(sintatica[percorre].token,"fim") == 0)
										{
											indicador=1;
											goto erro_sintatico;
										}
										if(strcmp(sintatica[percorre].token,"se") == 0 || strcmp(sintatica[percorre].token,"enquanto") == 0
										|| strcmp(sintatica[percorre].token,"leia") == 0 || strcmp(sintatica[percorre].token,"escreva") == 0
										|| strcmp(sintatica[percorre].token,"retorne") == 0 || strcmp(sintatica[percorre].tipo,"ID") == 0)
										{
											goto comeco;
										}
									}
									else
									{
										indicador=1;
										goto erro_sintatico;
									}
								}
								else
								{
									indicador=1;
									goto erro_sintatico;
								}
							}
							else
							{
								indicador=1;
								goto erro_sintatico;
							}
						}
						else
						{
							indicador=1;
							goto erro_sintatico;
						}
					}
					else
					{
						indicador=1;
						goto erro_sintatico;
					}

				}
				else
				{
					indicador=1;
					goto erro_sintatico;
				}
			}
			else
			{
				indicador=1;
				goto erro_sintatico;
			}

		}
		if((strcmp(sintatica[percorre].token,"enquanto") == 0) && (strcmp(sintatica[percorre+1].token,"(") == 0) && ((strcmp(sintatica[percorre+2].tipo,"ID") == 0) ||
		(strcmp(sintatica[percorre+2].tipo,"NUM") == 0) ||(strcmp(sintatica[percorre+2].token,"verdadeiro") == 0) || (strcmp(sintatica[percorre+2].token,"falso") == 0))
		&& (strcmp(sintatica[percorre+3].tipo,"ORL") == 0) && ((strcmp(sintatica[percorre+4].token,"+") == 0) || (strcmp(sintatica[percorre+4].token,"-") == 0) )&&
		((strcmp(sintatica[percorre+5].tipo,"ID") == 0) || (strcmp(sintatica[percorre+5].tipo,"NUM") == 0) || (strcmp(sintatica[percorre+5].token,"verdadeiro") == 0)
		|| (strcmp(sintatica[percorre+5].token,"falso") == 0) )&& (strcmp(sintatica[percorre+6].token,")") == 0) )
		{
			imprime+=1;
			percorre+=1;


			if(strcmp(sintatica[percorre].token,"(") == 0)
			{
				imprime+=1;
				percorre+=1;

				if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
				|| strcmp(sintatica[percorre].token,"verdadeiro") == 0 ||strcmp(sintatica[percorre].token,"falso") == 0
				)
				{
					imprime+=1;
					percorre+=1;

					if(strcmp(sintatica[percorre].tipo,"ORL") == 0)
					{
						imprime+=1;
						percorre+1;

						if(strcmp(sintatica[percorre].token,"+") == 0 || strcmp(sintatica[percorre].token,"-") == 0)
						{
							imprime+=1;
							percorre+=1;

							if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
							|| strcmp(sintatica[percorre].token,"verdadeiro") == 0 || strcmp(sintatica[percorre].token,"falso") == 0
							)
							{
								imprime+=1;
								percorre+=1;

								if(strcmp(sintatica[percorre].token,")") == 0)
								{
									imprime+=1;
									percorre+=1;

									if(strcmp(sintatica[percorre].token,"faca") == 0)
									{
										imprime+=1;
										percorre+=1;



										if(strcmp(sintatica[percorre].token,"#") == 0)
										{
											indicador=1;
											goto erro_sintatico;
										}
										if(strcmp(sintatica[percorre].token,"fim") == 0)
										{
											indicador=1;
											goto erro_sintatico;
										}
										if(strcmp(sintatica[percorre].token,"se") == 0 || strcmp(sintatica[percorre].token,"enquanto") == 0
										|| strcmp(sintatica[percorre].token,"leia") == 0 || strcmp(sintatica[percorre].token,"escreva") == 0
										|| strcmp(sintatica[percorre].token,"retorne") == 0 || strcmp(sintatica[percorre].tipo,"ID") == 0)
										{
											goto comeco;
										}
									}
									else
									{
										indicador=1;
										goto erro_sintatico;
									}
								}
								else
								{
									indicador=1;
									goto erro_sintatico;
								}

							}
							else
							{
								indicador=1;
								goto erro_sintatico;
							}
						}
						else
						{
							indicador=1;
							goto erro_sintatico;
						}
					}
					else
					{
						indicador=1;
						goto erro_sintatico;
					}
				}
				else
				{
					indicador=1;
					goto erro_sintatico;
				}
			}
			else
			{
				indicador=1;
				goto erro_sintatico;
			}

		}



		/*
			Comando Se
		*/
		if(strcmp(sintatica[percorre].token,"se") == 0 && (strcmp(sintatica[percorre+1].token,"(") == 0) && ((strcmp(sintatica[percorre+2].tipo,"ID") == 0)
		|| (strcmp(sintatica[percorre+2].tipo,"NUM") == 0) || (strcmp(sintatica[percorre+2].token,"falso") == 0) || (strcmp(sintatica[percorre+2].token,"verdadeiro") == 0))
		&& (strcmp(sintatica[percorre+3].token,")") == 0))
		{
			//printf("ENTROU1");
			imprime+=1;
			percorre+=1;

			if(strcmp(sintatica[percorre].token,"(") == 0)
			{
				imprime+=1;
				percorre+=1;

				if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
				|| strcmp(sintatica[percorre].token,"falso") == 0 || strcmp(sintatica[percorre].token,"verdadeiro") == 0
				)
				{
					imprime+=1;
					percorre+=1;

					if(strcmp(sintatica[percorre].token,")") == 0)
					{
						imprime+=1;
						percorre+=1;

						if(strcmp(sintatica[percorre].token,"entao") == 0 || strcmp(sintatica[percorre].token,"ent�o") == 0)
						{
							imprime+=1;
							percorre+=1;

							if(strcmp(sintatica[percorre].token,"#") == 0)
							{
								indicador=1;
								goto erro_sintatico;
							}
							if(strcmp(sintatica[percorre].token,"fim") == 0)
							{
								indicador=1;
								goto erro_sintatico;
							}
							if(strcmp(sintatica[percorre].token,"se") == 0 || strcmp(sintatica[percorre].token,"enquanto") == 0
							|| strcmp(sintatica[percorre].token,"leia") == 0 || strcmp(sintatica[percorre].token,"escreva") == 0
							|| strcmp(sintatica[percorre].token,"retorne") == 0 || strcmp(sintatica[percorre].tipo,"ID") == 0)
							{
								goto comeco;
							}
						}
						else
						{
							indicador=1;
							printf("AQUI 5\n\n");
							goto erro_sintatico;

						}
					}
					else
					{
						indicador=1;
						printf("ENTROU1");
						goto erro_sintatico;
					}
				}
				else
				{
					indicador=1;
					printf("ENTROU1");
					goto erro_sintatico;
				}
			}
			else
			{
				indicador=1;
				printf("ENTROU1");
				goto erro_sintatico;
			}
		}
		if(strcmp(sintatica[percorre].token,"se") == 0 && (strcmp(sintatica[percorre+1].token,"(") == 0) && ((strcmp(sintatica[percorre+2].token,"+") == 0) ||
		(strcmp(sintatica[percorre+2].token,"-") == 0)) && ((strcmp(sintatica[percorre+3].tipo,"ID") == 0) || (strcmp(sintatica[percorre+3].tipo,"NUM") == 0) ||
		(strcmp(sintatica[percorre+3].token,"falso") == 0) || (strcmp(sintatica[percorre+3].token,"verdadeiro") == 0))&& (strcmp(sintatica[percorre+4].token,")") == 0))
		{
			//	printf("ENTROU2");
			imprime+=1;
			percorre+=1;
			if(strcmp(sintatica[percorre].token,"(") == 0)
			{
				imprime+=1;
				percorre+=1;

				if(strcmp(sintatica[percorre].token,"+") == 0 || strcmp(sintatica[percorre].token,"-") == 0)
				{
					imprime+=1;
					percorre+=1;

					if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
					|| strcmp(sintatica[percorre].token,"verdadeiro") == 0 || strcmp(sintatica[percorre].token,"falso") == 0
					)
					{
						imprime+=1;
						percorre+=1;
						if(strcmp(sintatica[percorre].token,")") == 0)
						{
							imprime+=1;
							percorre+=1;

							if(strcmp(sintatica[percorre].token,"entao") == 0 || strcmp(sintatica[percorre].token,"ent�o") == 0)
							{
								imprime+=1;
								percorre+=1;

								if(strcmp(sintatica[percorre].token,"#") == 0)
								{
									indicador=1;
									goto erro_sintatico;
								}
								if(strcmp(sintatica[percorre].token,"fim") == 0)
								{
									indicador=1;
									goto erro_sintatico;
								}
								if(strcmp(sintatica[percorre].token,"se") == 0 || strcmp(sintatica[percorre].token,"enquanto") == 0
								|| strcmp(sintatica[percorre].token,"leia") == 0 || strcmp(sintatica[percorre].token,"escreva") == 0
								|| strcmp(sintatica[percorre].token,"retorne") == 0 || strcmp(sintatica[percorre].tipo,"ID") == 0)
								{
									goto comeco;
								}
							}
							else
							{
								indicador=1;
								printf("AQUI 4\n\n");
								goto erro_sintatico;
							}
						}
						else
						{
							indicador=1;
							printf("ENTROU2");
							goto erro_sintatico;
						}
					}
					else
					{
						indicador=1;
						printf("ENTROU2");
						goto erro_sintatico;
					}
				}
				else
				{
					indicador=1;
					printf("ENTROU2");
					goto erro_sintatico;
				}
			}
			else
			{
				indicador=1;
				printf("ENTROU2");
				goto erro_sintatico;
			}

		}

		if(strcmp(sintatica[percorre].token,"se") == 0 && strcmp(sintatica[percorre+1].token,"(") == 0 && (strcmp(sintatica[percorre+2].tipo,"ID") == 0
		||strcmp(sintatica[percorre+2].tipo,"NUM") == 0 || strcmp(sintatica[percorre+2].token,"verdadeiro") == 0  || strcmp(sintatica[percorre+2].token,"falso") == 0
		)&& strcmp(sintatica[percorre+3].tipo,"ORL") == 0  && (strcmp(sintatica[percorre+4].tipo,"ID") == 0 || strcmp(sintatica[percorre+4].tipo,"NUM") == 0
		|| strcmp(sintatica[percorre+4].token,"verdadeiro") == 0  || strcmp(sintatica[percorre+4].token,"falso") == 0 )&& strcmp(sintatica[percorre+5].token,")") == 0)
		{
			//printf("ENTROU\n");
			imprime+=1;
			percorre+=1;

			if(strcmp(sintatica[percorre].token,"(") == 0)
			{
				imprime+=1;
				percorre+=1;

				if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
				|| strcmp(sintatica[percorre].token,"verdadeiro") == 0 || strcmp(sintatica[percorre].token,"falso") == 0
				)
				{
					imprime+=1;
					percorre+=1;

					if(strcmp(sintatica[percorre].tipo,"ORL") == 0)
					{
						imprime+=1;
						percorre+=1;

						if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
						|| strcmp(sintatica[percorre].token,"verdadeiro") == 0 || strcmp(sintatica[percorre].token,"falso") == 0
						)
						{
							imprime+=1;
							percorre+=1;
							if(strcmp(sintatica[percorre].token,")") == 0)
							{
								imprime+=1;
								percorre+=1;

								if(strcmp(sintatica[percorre].token,"entao") == 0 || strcmp(sintatica[percorre].token,"ent�o") == 0)
								{
									imprime+=1;
									percorre+=1;

									if(strcmp(sintatica[percorre].token,"#") == 0)
									{
										indicador=1;
										goto erro_sintatico;
									}

									if(strcmp(sintatica[percorre].token,"fim") == 0)
									{
										indicador=1;
										goto erro_sintatico;
									}
									if(strcmp(sintatica[percorre].token,"se") == 0 || strcmp(sintatica[percorre].token,"enquanto") == 0
									|| strcmp(sintatica[percorre].token,"leia") == 0 || strcmp(sintatica[percorre].token,"escreva") == 0
									|| strcmp(sintatica[percorre].token,"retorne") == 0 || strcmp(sintatica[percorre].tipo,"ID") == 0)
									{
										goto comeco;
									}
								}
								else
								{
									indicador=1;
									printf("AQUI\n\n");
									goto erro_sintatico;
								}
							}
							else
							{
								indicador=1;
								printf("AQUII\n\n");
								goto erro_sintatico;
							}
						}
						else
						{
							indicador=1;
							printf("AQUIII\n\n");
							goto erro_sintatico;
						}
					}
					else
					{
						indicador=1;
						printf("AQUIIII\n\n");
						goto erro_sintatico;
					}
				}
				else
				{
					indicador=1;
					printf("AQUIIIII\n\n");
					goto erro_sintatico;
				}
			}
			else
			{
				indicador=1;
				printf("AQUIIIIII\n\n");
				goto erro_sintatico;
			}
		}
		if((strcmp(sintatica[percorre].token,"se") == 0) && (strcmp(sintatica[percorre+1].token,"(") == 0) && ((strcmp(sintatica[percorre+2].token,"+") == 0)
		|| (strcmp(sintatica[percorre+2].token,"-") == 0))&& ((strcmp(sintatica[percorre+3].tipo,"ID") == 0) || (strcmp(sintatica[percorre+3].tipo,"NUM") == 0) ||
		(strcmp(sintatica[percorre+3].token,"verdadeiro") == 0) || (strcmp(sintatica[percorre+3].token,"falso") == 0))&& (strcmp(sintatica[percorre+4].tipo,"ORL") == 0)
		&& ((strcmp(sintatica[percorre+5].token,"+") == 0) || (strcmp(sintatica[percorre+5].token,"-") == 0))&& ((strcmp(sintatica[percorre+6].tipo,"ID") == 0) ||
		(strcmp(sintatica[percorre+6].tipo,"NUM") == 0) || (strcmp(sintatica[percorre+6].token,"verdadeiro") == 0) || (strcmp(sintatica[percorre+6].token,"falso") == 0) )
		&& (strcmp(sintatica[percorre+7].token,")") == 0) )
		{
			//printf("ENTROU6\n");
			imprime+=1;
			percorre+=1;

			if(strcmp(sintatica[percorre].token,"(") == 0)
			{
				imprime+=1;
				percorre+=1;

				if(strcmp(sintatica[percorre].token,"+") == 0 || strcmp(sintatica[percorre].token,"-") == 0)
				{
					imprime+=1;
					percorre+=1;
					if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
					|| strcmp(sintatica[percorre].token,"verdadeiro") == 0 || strcmp(sintatica[percorre].token,"falso") == 0
					)
					{
						imprime+=1;
						percorre+=1;

						if(strcmp(sintatica[percorre].tipo,"ORL") == 0)
						{
							imprime+=1;
							percorre+=1;

							if(strcmp(sintatica[percorre].token,"+") == 0 || strcmp(sintatica[percorre].token,"-") == 0)
							{
								imprime+=1;
								percorre+=1;

								if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
								|| strcmp(sintatica[percorre].token,"verdadeiro") == 0 || strcmp(sintatica[percorre].token,"falso") == 0
								)
								{
									imprime+=1;
									percorre+=1;

									if(strcmp(sintatica[percorre].token,")") == 0)
									{
										imprime+=1;
										percorre+1;

										if(strcmp(sintatica[percorre].token,"entao") == 0 || strcmp(sintatica[percorre].token,"ent�o") == 0)
										{
											if(strcmp(sintatica[percorre].token,"#") == 0)
											{
												indicador=1;
												goto erro_sintatico;
											}
											if(strcmp(sintatica[percorre].token,"fim") == 0)
											{
												indicador=1;
												goto erro_sintatico;
											}
											if(strcmp(sintatica[percorre].token,"se") == 0 || strcmp(sintatica[percorre].token,"enquanto") == 0
											|| strcmp(sintatica[percorre].token,"leia") == 0 || strcmp(sintatica[percorre].token,"escreva") == 0
											|| strcmp(sintatica[percorre].token,"retorne") == 0 || strcmp(sintatica[percorre].tipo,"ID") == 0)
											{
												goto comeco;
											}

										}
										else
										{
											indicador=1;
											printf("AQUI 1\n\n");
											goto erro_sintatico;
										}
									}
									else
									{
										indicador=1;
										printf("ENTROU6\n");
										goto erro_sintatico;
									}
								}
								else
								{
									indicador=1;
									printf("ENTROU6\n");
									goto erro_sintatico;
								}
							}
							else
							{
								indicador=1;
								printf("ENTROU6\n");
								goto erro_sintatico;
							}
						}
						else
						{
							indicador=1;
							printf("ENTROU6\n");
							goto erro_sintatico;
						}

					}
					else
					{
						indicador=1;
						printf("ENTROU6\n");
						goto erro_sintatico;
					}
				}
				else
				{
					indicador=1;
					printf("ENTROU6\n");
					goto erro_sintatico;
				}
			}
			else
			{
				indicador=1;
				printf("ENTROU6\n");
				goto erro_sintatico;
			}
		}
		if((strcmp(sintatica[percorre].token,"se") == 0) && (strcmp(sintatica[percorre+1].token,"(") == 0) && ((strcmp(sintatica[percorre+2].token,"+") == 0)
		|| (strcmp(sintatica[percorre+2].token,"-") == 0) )&&((strcmp(sintatica[percorre+3].tipo,"ID") == 0) || (strcmp(sintatica[percorre+3].tipo,"NUM") == 0) ||
		(strcmp(sintatica[percorre+3].token,"verdadeiro") == 0) || (strcmp(sintatica[percorre+3].token,"falso") == 0)) && (strcmp(sintatica[percorre+4].tipo,"ORL") == 0)
		&& ((strcmp(sintatica[percorre+5].tipo,"ID") == 0) || (strcmp(sintatica[percorre+5].tipo,"NUM") == 0) || (strcmp(sintatica[percorre+5].token,"verdadeiro") == 0)
		|| (strcmp(sintatica[percorre+5].token,"falso") == 0))&& (strcmp(sintatica[percorre+6].token,")") == 0) )
		{
			//printf("ENTROU7\n");
			imprime+=1;
			percorre+=1;

			if(strcmp(sintatica[percorre].token,"(") == 0)
			{
				imprime+=1;
				percorre+=1;

				if(strcmp(sintatica[percorre].token,"+") == 0 || strcmp(sintatica[percorre].token,"-") == 0)
				{
					imprime+=1;
					percorre+=1;
					if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
					|| strcmp(sintatica[percorre].token,"verdadeiro") == 0 || strcmp(sintatica[percorre].token,"falso") == 0
					)
					{
						imprime+=1;
						percorre+=1;

						if(strcmp(sintatica[percorre].tipo,"ORL") == 0)
						{
							imprime+=1;
							percorre+=1;

							if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
							|| strcmp(sintatica[percorre].token,"verdadeiro") == 0 || strcmp(sintatica[percorre].token,"falso") == 0
							)
							{
								imprime+=1;
								percorre+=1;

								if(strcmp(sintatica[percorre].token,")") == 0)
								{
									imprime+=1;
									percorre+=1;

									if(strcmp(sintatica[percorre].token,"entao") == 0 || strcmp(sintatica[percorre].token,"ent�o") == 0)
									{
										imprime+=1;
										percorre+=1;

										if(strcmp(sintatica[percorre].token,"#") == 0)
										{
											indicador=1;
											goto erro_sintatico;
										}
										if(strcmp(sintatica[percorre].token,"fim") == 0)
										{
											indicador=1;
											goto erro_sintatico;
										}
										if(strcmp(sintatica[percorre].token,"se") == 0 || strcmp(sintatica[percorre].token,"enquanto") == 0
										|| strcmp(sintatica[percorre].token,"leia") == 0 || strcmp(sintatica[percorre].token,"escreva") == 0
										|| strcmp(sintatica[percorre].token,"retorne") == 0 || strcmp(sintatica[percorre].tipo,"ID") == 0)
										{
											goto comeco;
										}
									}
									else
									{
										indicador=1;
										printf("AQUI 2\n\n");
										goto erro_sintatico;
									}
								}
								else
								{
									indicador=1;
									printf("ENTROU7\n");
									goto erro_sintatico;
								}
							}
							else
							{
								indicador=1;
								printf("ENTROU7\n");
								goto erro_sintatico;
							}
						}
						else
						{
							indicador=1;
								printf("ENTROU7\n");
							goto erro_sintatico;
						}
					}
					else
					{
						indicador=1;
							printf("ENTROU7\n");
						goto erro_sintatico;
					}

				}
				else
				{
					indicador=1;
						printf("ENTROU7\n");
					goto erro_sintatico;
				}
			}
			else
			{
				indicador=1;
					printf("ENTROU7\n");
				goto erro_sintatico;
			}
		}
		if((strcmp(sintatica[percorre].token,"se") == 0) && (strcmp(sintatica[percorre+1].token,"(") == 0) &&( (strcmp(sintatica[percorre+2].tipo,"ID") == 0) ||
		(strcmp(sintatica[percorre+2].tipo,"NUM") == 0) ||(strcmp(sintatica[percorre+2].token,"verdadeiro") == 0) || (strcmp(sintatica[percorre+2].token,"falso") == 0))
		&& (strcmp(sintatica[percorre+3].tipo,"ORL") == 0) && ((strcmp(sintatica[percorre+4].token,"+") == 0) || (strcmp(sintatica[percorre+4].token,"-") == 0) )&&
		((strcmp(sintatica[percorre+5].tipo,"ID") == 0) || (strcmp(sintatica[percorre+5].tipo,"NUM") == 0) || (strcmp(sintatica[percorre+5].token,"verdadeiro") == 0)
		|| (strcmp(sintatica[percorre+5].token,"falso") == 0))&& (strcmp(sintatica[percorre+6].token,")") == 0) )
		{
				//printf("ENTROU8\n");
			imprime+=1;
			percorre+=1;


			if(strcmp(sintatica[percorre].token,"(") == 0)
			{
				imprime+=1;
				percorre+=1;

				if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
				|| strcmp(sintatica[percorre].token,"verdadeiro") == 0 ||strcmp(sintatica[percorre].token,"falso") == 0
				)
				{
					imprime+=1;
					percorre+=1;

					if(strcmp(sintatica[percorre].tipo,"ORL") == 0)
					{
						imprime+=1;
						percorre+1;

						if(strcmp(sintatica[percorre].token,"+") == 0 || strcmp(sintatica[percorre].token,"-") == 0)
						{
							imprime+=1;
							percorre+=1;

							if(strcmp(sintatica[percorre].tipo,"ID") == 0 || strcmp(sintatica[percorre].tipo,"NUM") == 0
							|| strcmp(sintatica[percorre].token,"verdadeiro") == 0 || strcmp(sintatica[percorre].token,"falso") == 0
							)
							{
								imprime+=1;
								percorre+=1;

								if(strcmp(sintatica[percorre].token,")") == 0)
								{
									imprime+=1;
									percorre+=1;

									if(strcmp(sintatica[percorre].token,"entao") == 0 || strcmp(sintatica[percorre].token,"ent�o") == 0)
									{
										imprime+=1;
										percorre+=1;



										if(strcmp(sintatica[percorre].token,"#") == 0)
										{
											indicador=1;
											goto erro_sintatico;
										}
										if(strcmp(sintatica[percorre].token,"fim") == 0)
										{
											indicador=1;
											goto erro_sintatico;
										}
										if(strcmp(sintatica[percorre].token,"se") == 0 || strcmp(sintatica[percorre].token,"enquanto") == 0
										|| strcmp(sintatica[percorre].token,"leia") == 0 || strcmp(sintatica[percorre].token,"escreva") == 0
										|| strcmp(sintatica[percorre].token,"retorne") == 0 || strcmp(sintatica[percorre].tipo,"ID") == 0)
										{
											goto comeco;
										}
									}
									else
									{
										indicador=1;
										printf("AQUI 3\n\n");
										goto erro_sintatico;
									}
								}
								else
								{
									indicador=1;
									printf("ENTROU8\n");
									goto erro_sintatico;
								}

							}
							else
							{
								indicador=1;
								printf("ENTROU8\n");
								goto erro_sintatico;
							}
						}
						else
						{
							indicador=1;
							printf("ENTROU8\n");
							goto erro_sintatico;
						}
					}
					else
					{
						indicador=1;
						printf("ENTROU8\n");
						goto erro_sintatico;
					}
				}
				else
				{
					indicador=1;
					printf("ENTROU8\n");
					goto erro_sintatico;
				}
			}
			else
			{
				indicador=1;
				printf("ENTROU8\n");
				goto erro_sintatico;
			}

		}




		/*
			Comando Sen�o
		*/
		if(strcmp(sintatica[percorre].token,"senao") == 0 || strcmp(sintatica[percorre].token,"sen�o") == 0)
		{
			//printf("Yuri");
			imprime+=1;
			percorre+=1;


			if(strcmp(sintatica[percorre].token,"#") == 0)
			{
				indicador=1;
				printf("entrou");
				goto erro_sintatico;
			}
			if(strcmp(sintatica[percorre].token,"fim") == 0)
			{
				indicador=1;
				printf("entrou1");
				goto erro_sintatico;
			}

			if(strcmp(sintatica[percorre].token,"se") == 0 || strcmp(sintatica[percorre].token,"enquanto") == 0
			|| strcmp(sintatica[percorre].token,"leia") == 0 || strcmp(sintatica[percorre].token,"escreva") == 0
			|| strcmp(sintatica[percorre].token,"retorne") == 0 || strcmp(sintatica[percorre].tipo,"ID") == 0)
			{
				goto comeco;
			}
		}



	}
	else
	{
		indicador=1;
		printf("OI\n\n");
		goto erro_sintatico;
	}
	/*
		Caso nessa parte tenha o # ele imprime as posi��es restantes junto com o fim.
		Caso tenha alguma estrutura do bloco ele redireciona para l� o processo � reiniciado novamente.
	*/
	fim:
	if(strcmp(sintatica[percorre].token,"fim") == 0)
	{
		imprime+=1;
		percorre+=1;
		if(strcmp(sintatica[percorre].token,"var") == 0 || strcmp(sintatica[percorre].token,"funcao") == 0 ||strcmp(sintatica[percorre].token,"fun��o") == 0 || strcmp(sintatica[percorre].token,"procedimento") == 0)
		{
			for(k=auximprime;k<imprime;k++)
        	{
                printf("%s ",sintatica[k].token);
            }
            printf(" -  OK\n");
            auximprime = imprime;
            goto bloco;
		}
		if(strcmp(sintatica[percorre].token,"inicio") == 0)
		{
			for(k=auximprime;k<imprime;k++)
        	{
                printf("%s ",sintatica[k].token);
            }
            printf(" -  OK\n");
            auximprime = imprime;
            goto comando;
		}
		if(strcmp(sintatica[percorre].token,"#") == 0)
		{
			for(k=auximprime;k<imprime;k++)
        	{
                printf("%s ",sintatica[k].token);
            }
            printf(" -  OK\n");
            auximprime = imprime;
            sentinela=1;
			goto analisa;
		}
	}



	/*
		Aqui � verificado que caso a flag seja diferente de 0 n�o teve nenhum erro sint�tico, caso
		contr�rio teve e exibir� a linha do erro.
	*/

	analisa:
    if(sentinela == 0)
    {
    	indicador=1;
    	erro_sintatico:
        printf("\n\nERRO SINTATICO - LINHA:%s\n",sintatica[percorre].linha);
    }
    else
        printf("\n\nSEM NENHUM ERRO SINTATICO\n");



	printf("------------------------------------------------------\n\n");

	fclose(saida);
	return indicador;

}




/*
	PLP - Etapa 02 - Analisador L�xico

	GRUPO

	Erik Volpert
	Gustavo Santarsieri
	Rogerio Bordignon
	Yuri Serrano



  Observa��o: Caso a pontua��o apare�a estranha, � por uma incompatibilidade da IDE com a pontua��o, ent�o existe um arquivo a parte com os mesmos dizeres.
  Para n�o ocorrer um bug ,utilizamos a vers�o 5.11 do orwell Dev C++.
  Caso use o Bloshedev 4.9.2 ir� bugar.

  Observa��o 1: Devido a uma diferen�a nas produ��es e nos exemplos do c�digo que tinham em uns tinha acentua��o e em outros n�o, nosso c�digo identifica dos
  dois modos com ou sem acentua��o.

  Observa��o 2: Fiz adapta��es para palavras com acentos.



  Conjunto de Testes

  Na pasta teste a testes adicionais que fiz para comprovar o funcionamento mediante a erros l�xicos , coment�rios e outros
  c�digos completos, para testar basta pegar o arquivo entrada que encontrase nas pastas.


  Exemplo:fun��o - funcao





  Documenta��o - Yuri Serrano




  Nessa segunda etapa estamos utilizando o conceito de buffering, em que todos os caracteres lidos s�o armazenados em um vetor de char alocados
  dinamicamente com um tamanho de 2000 caracteres podendo esse espa�o ser expandido ou n�o.
  Para cumprir com os requisitos da Etapa 02 , os estados do nosso aut�matos s�o representados pelos r�tulos do goto , em que caracter por caracter
  � analisado e ap�s a identifica��o (ou n�o) do lexema um token referente ao mesmo � gerado , bem com  o n�mero da linha que o token foi encontrado
  no nosso arquivo texto denominado output que encontra-se no  seguinte formato:

  TOKEN			  TIPO				LINHA


  Para a terceira etapa adotando como dica da professora Daniela, vamos retirar essa primeira linha  e remover o identificador de linhas para facilitar
  no processo da an�lise sint�tica.

  Com base na linguagem SIM o analisador l�xico reconhece os seguintes tokens:

  Palavras Reservadas - PR

  enquanto
  entao
  e
  escreva
  ou
  booleano
  retorne
  leia
  se
  senao
  programa
  procedimento
  inicio
  inteiro
  var
  verdadeiro
  faca
  funcao
  fim
  falso

  Todas as palavras reservadas s�o em letra min�scula obrigatoriamente, pois n�o inferimos  que a linguagem em quest�o � case sensitive.

  ________________________________________________________________________________________________________________________________________________


  Classe dos identificadores (L  (D|L|_) )  - ID

  O identificador seguindo a regra  da linguagem SIM obrigatoriamente tem que come�ar com uma letra, ap�s isso ele pode ser constitu�do de letras ,
  d�gitos ou '_'.Como n�o foi especificado o tamanho m�ximo do identificador deixamos o tamanho livre, por n�o ser uma aplica��o que ser� usada
  inicialmente por diversos usu�rios.

  Caso o usu�rio insista em come�ar com d�gitos ou '_' ser� printado na tela "ERRO L�XICO" e a linha onde ocorreu o erro.

  Exemplo:

  yuri - ID

  _yuri ou 1yuri - ERRO L�XICO


  ________________________________________________________________________________________________________________________________________________

  Classe dos Operadores Relacionais L�gicos ( < >  <> <= >= e ou ) - ORL


  Sobre esta classe n�o temos muitos coment�rios a respeito,� que decidimos incluir e/ou nesta classe por se tratarem de ORL mesmo estando escritos
  em portugu�s.

  ________________________________________________________________________________________________________________________________________________


  Classe dos pontos ( , ;  ) - PT

  Sobre esta classe n�o temos muitos coment�rios a respeito, pois a mesma � intuitiva

  ________________________________________________________________________________________________________________________________________________

  Classe dos delimitadores ( ( ) { }  ) - DEL

  Sobre esta classe os delimitadores { } n�o s�o colocados no arquivo pois eles s�o utilizados para delimitar os coment�rios e tudo o que est�
  entre eles e incluindo eles � removido do arquivo.

  ________________________________________________________________________________________________________________________________________________
  Atribui��o - ATRIB

  Operador de atribui��o.

  ________________________________________________________________________________________________________________________________________________



  Classe dos Literais ( "texto") - LIT

  Sobre esta classe ela � delimitada pelos delimitadores  ( ) em que dentro deles � verificado o come�o do " e o t�rmino que significa a identifica-
  ��o do literal.
  Obrigatoriamente � preciso incluir " " para representar o literal, caso contr�rio ir� aparecer erro l�xico.
  Se o delimitador ) n�o aparecer tamb�m ir� aparecer erro l�xico.

   ________________________________________________________________________________________________________________________________________________

    Classe dos Coment�rios

    Esta classe possui como delimitadores  { } em que dentro deles o usu�rio pode colocar qualquer coisa, caso n�o seja colocado o delimitador }
    ser� apresentado erro l�xico.
    O coment�rio n�o � colocado no output do arquivo,bem como os seus delimitadores.
   ________________________________________________________________________________________________________________________________________________

  	Classe dos Operadores Matem�ticos

    Esta classe possui somente os operadores + e -.
   ________________________________________________________________________________________________________________________________________________

Processo de identifica��o dos lexemas e gera��o dos tokens

Para a identifica��o dos lexemas os goto simulam um aut�mato h�brido, em que o processo de identifica��o � feito em cascata,em que ao t�rmino de uma
identifica��o ele volta ao �nicio para continuar dando prosseguimento ao reconhecimento dos outros tokens.

As palavras reservadas fizemos aut�matos pr�prios iguais ao nosso modelo da etapa 1 que reconhecem todas as palavras reservadas, em que � analisado a primeira
letra de cada palavra reservada e caso a palavra seja reconhecida ela � colocada no arquivo output, caso a palavra tenha qualquer outro caracter que
a modifique ela � encaminhada para o estado identificador e a partir da� � tratada como tal no nosso output.
Para os n�meros enquanto existirem digitos ele vai entrando no estado de d�gitos at� que seja encontrado o espa�o vazio ou algo diferente de um d�gito.
E para as demais classes elas adotam o procedimento realizado com a classe de n�meros.

________________________________________________________________________________________________________________________________________________


Elimina��o de Espa�os Vazios

Foi colocado um la�o que elimina espa�os vazios em demasia deixando somente um caso a pessoa escreva utilizando espa�os.


________________________________________________________________________________________________________________________________________________




Creio eu que todas os pontos que a ETAPA 02 requisitou, conseguimos implementar e fazer funcionar corretamente.


Ao longo do c�digo algumas partes ser�o comentadas demonstrando a funcionalidade, outras n�o pois utilizamos basicamente a mesma estrutura
mudando o r�tulo do aut�mato.


OBS:

Material utilizado nesta etapa:

http://web.cs.mun.ca/~michael/c/ascii-table.html
http://www.tutorialspoint.com/c_standard_library/ctype_h.htm
http://linguagemc.com.br/ctype-h-toupper-tolower-isalpha-isdigit-em-c/




ATTE Yuri Serrano


*/



int analise_lexica(FILE *abrir,FILE *saida)
{
	int indicador=0;
	char *entrada;
	char num;
	char resposta[100]  ={};
	char operador[100] ={};
	char numero[100] = {};
	char delimitador[100] = {};
	char identificador[100] = {};
	char operador_relacional[100] = {};
	char aux[100] = {};
	char literal[100] = {};
	int i=0,contador,linha=1,j=0,k=0;
	char caracter,c;
	abrir = fopen("entrada.txt","r");
	saida = fopen("saida.txt","w");
	int flag =0;




	/*
		* Verifica se o arquivo foi aberto com sucesso ou n�o.
		* Caso n�o consiga � emitida uma mensagem informando que n�o � poss�vel
	*/

	if(abrir == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");

	if(saida == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");




	/*
		* Realiza a aloca��o din�mica do vetor de chars entrada com 2000 elementos, podendo
		* este espa�o ser aumentado.
	*/
	entrada = malloc(sizeof(char)*2000);

	/*
		* L� todo o arquivo caracter por caracter at� chegar no EOF.
		* Cada caracter vai sendo armazenado no vetor de chars entrada.
	*/
	while((caracter=fgetc(abrir))!=EOF)
	{
		entrada[i]=caracter;
		i++;
	}

	//printf("Tamanho Entrada:%d\n",strlen(entrada));
	/*
		 Foi utilizado para testar se os caracteres estava sendo pegos
	while(k<strlen(entrada))
	{
		printf("K:%d\n",k);
		printf(" C:%c,[%d]:%d\n ",entrada[k],k,entrada[k]);
		k=k+1;
	}

	*/



	/*
		* Ao final do vetor de chars entrada � colocado o s�mbolo '\0' == 0
		* para que se possa ter uma refer�ncia parao t�rmino da leitura do
		* vetor de chars.

	*/
	entrada[i]='\0';

	while(j<strlen(entrada))
	{



		inicio:
		/*
			* A fun��o memset serve para zerar o vetor de chars que esta armazenando
			* a string que foi colocada no arquivo output.
			* Assim que a mesma � gravada quando o processo volta ao estado inicio
			* ele zera os vetores de chars que possam ter sido utilizados.
		*/
		memset(&resposta[0], 0, sizeof(resposta));
		memset(&delimitador[0], 0, sizeof(delimitador));
		memset(&literal[0], 0, sizeof(literal));
		memset(&identificador[0], 0, sizeof(identificador));
		memset(&operador_relacional[0], 0, sizeof(operador_relacional));
		memset(&operador[0], 0, sizeof(operador));
		memset(&aux[0], 0, sizeof(aux));
		c=entrada[j];


		//printf("%c\n",c);
		// Verifica-se se tem um espa�o vazio
		if(c == 32)
		{

			/*
				* Este la�o vai eliminando os espa�os vazios em demasia que se encontram no
				* arquivo deixando somente um, que � tratado pelos nossos aut�matos caso
				*ocorra.
			*/
			while(entrada[j] == 32 && entrada[j+1] == 32)
			{

					j=j+1;
					c=entrada[j];
					if(entrada[j+2] == 10)
					{

						linha = linha+1;
						j=j+3;


					}
			}
		}

		/*
			* Como processo da elimina��o de espa�os o �nico que sobrar � eliminado
			* Como esse espa�o � eliminado sobrar� o o elemento a ser identificado  ou \n == 10
			* ou o final do vetor de chars que � '\0' == 0
		*/
		if(entrada[j] == 32)
		{
			j=j+1;
			goto inicio;
		}

		/*
			* Se a entrada for um \n ele soma1 a vari�vel linha e anda uma posi��o passando para
			* a vari�vel c que ser� avaliada nos casos a seguir.

		*/
		if(entrada[j] == 10)
		{
			j=j+1;
			linha=linha+1;
			goto inicio;
		}
		if(entrada[j] == 9)
		{
			j=j+1;
			goto inicio;
		}

		/*
			* Se o valor for 0 ('\0') o la�o � interrompido, indicando que a leitura
			* terminou
		*/
		if(entrada[j] == 0)
			break;



		/*
			* Identifica o delimitador (.
		*/
		if(c == '(')
		{
			sprintf(delimitador, "%c", c);
			strcat(resposta,delimitador);
			fprintf(saida,"%s\t\t\t\t\tDEL\t\t\t\t\t\t%d\n",resposta,linha);
			j=j+1;
			goto inicio;
		}

		//Aqui verifica se � "
		if(c == 34 )
		{
			sprintf(literal, "%c", c);
			strcat(resposta,literal);


				// Enquanto n�o chegar na outra " o la�o vai continuando e o conte�do sendo gravado no vetor  resposta
			while(entrada[j+1] != 34 )
			{
				//Se ele chegar ao terminador '\0' quer dizer que n�o achou o outro terminador



				if(entrada[j+1] == 0)
					goto errolexico;
				sprintf(literal, "%c", entrada[j+1]);
				strcat(resposta,literal);
				j=j+1;
			}
				//Assim que " � encontrado a string no vetor resposta � gravada no output
			if(entrada[j+1] == 34)
			{

					sprintf(literal, "%c", entrada[j+1]);
					strcat(resposta,literal);

					if(strlen(resposta) <=15)
						fprintf(saida,"%s\t\t\t\tLIT\t\t\t\t\t\t%d\n",resposta,linha);
					else
						fprintf(saida,"%s\t\t\tLIT\t\t\t\t\t\t%d\n",resposta,linha);
					j=j+2;
					goto inicio;
			}
			if(entrada[j+1] == 0)
					goto errolexico;
		}
		if(c == -109 )
		{
			sprintf(literal, "%c", c);
			strcat(resposta,literal);


				// Enquanto n�o chegar na outra " o la�o vai continuando e o conte�do sendo gravado no vetor  resposta
			while(entrada[j+1] != -108 )
			{
				//Se ele chegar ao terminador '\0' quer dizer que n�o achou o outro terminador



				if(entrada[j+1] == 0)
					goto errolexico;
				sprintf(literal, "%c", entrada[j+1]);
				strcat(resposta,literal);
				j=j+1;
			}
				//Assim que " � encontrado a string no vetor resposta � gravada no output
			if(entrada[j+1] == -108)
			{

					sprintf(literal, "%c", entrada[j+1]);
					strcat(resposta,literal);
					if(strlen(resposta) <=15)
						fprintf(saida,"%s\t\t\t\tLIT\t\t\t\t\t\t%d\n",resposta,linha);
					else
						fprintf(saida,"%s\t\t\tLIT\t\t\t\t\t\t%d\n",resposta,linha);
					j=j+2;
					goto inicio;
			}
			if(entrada[j+1] == 0)
					goto errolexico;
		}
		//Aqui caso seja encontrado ) � gravado no output
		if(c == ')')
		{
			    sprintf(delimitador, "%c", c);
				strcat(resposta,delimitador);
				fprintf(saida,"%s\t\t\t\t\tDEL\t\t\t\t\t\t%d\n",resposta,linha);
				j=j+1;
				goto inicio;
		}


		//Aqui verifica se uma pontua��o foi achada e caso seja � gravada no arquivo output
		if(c == ',' || c== ':' || c == ';')
		{
			sprintf(delimitador, "%c", c);
			strcat(resposta,delimitador);
			if(c == ':' && entrada[j+1] == '=')
			{
				sprintf(delimitador, "%c", entrada[j+1]);
				strcat(resposta,delimitador);
				fprintf(saida,"%s\t\t\t\t\tATRIB\t\t\t\t\t\t%d\n",resposta,linha);
				j=j+2;
				goto inicio;
			}
			fprintf(saida,"%s\t\t\t\t\tPT\t\t\t\t\t\t%d\n",resposta,linha);
			j=j+1;
			goto inicio;

		}


		/*
			* Aqui inicia-se o reconhecimento dos coment�rios e sua elimina��o
			* do arquivo
		*/
		if(c == '{' && c == 123)
		{
			comentario:
			/*
				* Ap�s a identifica��o do do primeiro delimitador ele vai passando toda posi��o
				* que for diferente do outro delimitador.
			*/

			if(entrada[j+1] !=  '}')
			{
				if(entrada[j+1] == 0)
					goto errolexico;
				j=j+1;
				goto comentario;
			}




			// Aqui verifica se chegou ao \n se sim volta ao inicio
			if(entrada[j+1] == '}' && entrada[j+2] == 10)
			{
				linha=linha+1;
				j=j+3;
				goto inicio;
			}

			// Aqui verifica se achou um espa�o, se sim volta ao inicio
			if(entrada[j+1] == '}' && entrada[j+2] == 32)
			{

				j=j+3;
				goto inicio;
			}
			// Aqui verifica se achou o final do vetor de entradas se sim o la�o � interrompido
			if(entrada[j+1] == '}' && entrada[j+2] == 0)
			{
				j=j+3;
				printf("Comentario");
				break;
			}
			// Aqui verifica se existe elementos como letras, d�gitos ou '_' depois do coment�rio se sim volta para o inicio
			if(entrada[j+1] == '}' && isdigit(entrada[j+2] ) || isalpha(entrada[j+2]) || entrada[j+2] == '_' )
			{
				j=j+2;
				goto inicio;

			}
		}


		/*
			* Aqui � feito o processo de indentifica��o dos n�meros.
		*/
		if(isdigit(c))
		{

			sprintf(numero, "%c", c);
			strcat(resposta,numero);

			numero:
			memset(&numero[0], 0, sizeof(numero));


			/*
				* Aqui � como se tivesse um pr�prio referenciamento a este estado, enquanto tiver d�gitos ele vai percorrendo
				* Caso ele encontre letras n�o vai para o estado de errolexico ,pois a pessoa pode ter escrito sem espa�os.
			*/
			if(isdigit(entrada[j+1]))
			{
				sprintf(numero, "%c", num);
				strcat(resposta,numero);
				j=j+1;
				goto numero;

			}
			//printf("NUM:%d\n",num);
			if(isalpha(entrada[j+1]) || entrada[j+1] == '_')
			{
				j=j+1;
				goto errolexico;
				flag=1;
			}
			if(entrada[j+1] == 0  )
			{
				fprintf(saida,"%s\t\t\t\t\tNUM \t\t\t\t\t\t%d\n",resposta,linha);
				break;

			}
			if(entrada[j+1] == 10)
			{
				fprintf(saida,"%s\t\t\t\t\tNUM \t\t\t\t\t\t%d\n",resposta,linha);
				linha=linha+1;
				j=j+2;
				goto inicio;
			}
			if(entrada[j+1] == 32)
			{
				fprintf(saida,"%s\t\t\t\t\tNUM \t\t\t\t\t\t%d\n",resposta,linha);
				j=j+2;
				goto inicio;

			}
			if(entrada[j+1] == ')' )
	 		{
	 			fprintf(saida,"%s\t\t\t\t\tNUM \t\t\t\t\t\t%d\n",resposta,linha);
				j=j+1;
				goto inicio;
	 		}
	 		if(entrada[j+1] == ';' )
	 		{
	 			fprintf(saida,"%s\t\t\t\t\tNUM \t\t\t\t\t\t%d\n",resposta,linha);
				j=j+1;
				goto inicio;
	 		}
		}
		/*
			* Aqui inicia-se o processo da identifica��o das palavras reservadas que come�am com e
			* e do operador relacional e.
		*/
		if(isalpha(c) && c == 'e' && c == 101)
		{
			    strcat(resposta,"e");

			if(isspace(entrada[j+1]) || entrada[j+1] ==  32 || entrada[j+1] == 10 || entrada[j+1] == '\0' ||  entrada[j+1] == 9)
			{

				//printf("%s",resposta);
				fprintf(saida,"%s\t\t\t\t\tORL\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+1] == 10)
					linha=linha+1;
				j=j+1;
				goto inicio;

			}
			if(( entrada[j+1] != 's' && entrada[j+1] != 'n') || isdigit(entrada[j+1]) || entrada[j+1] == '_')
			{

					goto identificador;
			}

			if(isalpha(entrada[j+1]) && entrada[j+1] == 's' && entrada[j+1] == 115)
			{
				if((entrada[j+2] != 'c') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"s");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"s");
				j=j+1;
				goto escreva;

			}

			if(isalpha(entrada[j+1]) && entrada[j+1] == 'n' && entrada[j+1] == 110)
			{
				if((entrada[j+2] != 't' && entrada[j+2] != 'q') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}

				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"n");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"n");
				j=j+1;
				if(entrada[j+1] == 'q')
					goto enq;
				if(entrada[j+1] == 't')
					goto prox;


			}
			if(isalpha(entrada[j+1])  || isdigit(entrada[j+1]) || entrada[j+1] == '_')
			{

                    goto identificador;
            }
			prox:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 't' && entrada[j+1] == 116)
			{
				if((entrada[j+2] != 'a' && entrada[j+2] != -29) || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"t");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"t");
				j=j+1;
				goto entao;
			}
			enq:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'q' && entrada[j+1] == 113)
			{
				if((entrada[j+2] != 'u') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"q");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"q");
				j=j+1;
				goto enquanto;
			}

			entao:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'a' && entrada[j+1] == 97)
			{
				if((entrada[j+2] != 'o') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"a");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"a");
				j=j+1;
				goto entao1;
			}
			if(entrada[j+1] == -29)
			{
				if((entrada[j+2] != 'o') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"�");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"�");
				j=j+1;
				goto funcao3;
		}
			entao1:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'o' && entrada[j+1] == 111)
			{
				if(isalpha(entrada[j+2]) || isdigit(entrada[j+2]) )
				{
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"o");
				fprintf(saida,"%s\t\t\t\t\tPR\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					if(entrada[j+2] == 10)
						linha=linha+1;
					j = j+2;
					goto inicio;

				}
				j=j+2;
				goto inicio;

			}
			enquanto:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'u' && entrada[j+1] == 117)
			{
				if((entrada[j+2] != 'a') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"u");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"u");
				j=j+1;
				goto enquanto1;
			}
			enquanto1:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'a' && entrada[j+1] == 97)
			{
				if((entrada[j+2] != 'n') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"a");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"a");
				j=j+1;
				goto enquanto2;
			}
			enquanto2:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'n' && entrada[j+1] == 110)
			{
				if((entrada[j+2] != 't') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"n");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"n");
				j=j+1;
				goto enquanto3;
			}
			enquanto3:
				printf("%c - %d\n",entrada[j+1],entrada[j+1]);
			if(isalpha(entrada[j+1]) && entrada[j+1] == 't' && entrada[j+1] == 116)
			{
				if((entrada[j+2] != 'o') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"t");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"t");
				j=j+1;
				goto enquanto4;
			}
			enquanto4:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'o' && entrada[j+1] == 111)
			{
				if(isalpha(entrada[j+2]) || isdigit(entrada[j+2]) )
				{
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"o");
				fprintf(saida,"%s\t\t\t\tPR\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					if(entrada[j+2] == 10)
						linha=linha+1;
					j = j+2;
					goto inicio;

				}

				j=j+2;
				goto inicio;

			}
			escreva:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'c' && entrada[j+1] == 99)
			{
				if((entrada[j+2] != 'r') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"c");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"c");
				j=j+1;
				goto escreva1;

			}
			escreva1:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'r' && entrada[j+1] == 114)
			{
				if((entrada[j+2] != 'e') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"r");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"r");
				j=j+1;
				goto escreva2;

			}
			escreva2:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'e' && entrada[j+1] == 101)
			{
				if((entrada[j+2] != 'v') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"e");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"e");
				j=j+1;
				goto escreva3;

			}
			escreva3:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'v' && entrada[j+1] == 118)
			{
				if(( entrada[j+2] != 'a') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"v");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"v");
				j=j+1;
				goto escreva4;

			}
			escreva4:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'a' && entrada[j+1] == 97)
			{
				if(isalpha(entrada[j+2]) || isdigit(entrada[j+2]) )
				{
					strcat(resposta,"a");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"a");
				fprintf(saida,"%s\t\t\t\t\tPR\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					if(entrada[j+2] == 10)
						linha=linha+1;
					j = j+3;
					goto inicio;

				}

			    if(entrada[j+2] == '(' )
	 		    {

					j=j+2;
					goto inicio;
	 			}
	 			if(entrada[j+2] == ';')
				{

					j = j+2;
					goto inicio;

				}
				j=j+2;
				goto inicio;

			}


		}
		/*
			* Aqui inicia-se o processo do operador relacional ou
		*/
		if(isalpha(c) && c == 'o' && c == 111)
		{
				strcat(resposta,"o");


				if((entrada[j+1] != 'u') || isdigit(entrada[j+1]) || entrada[j+1] == '_')
				{
					goto identificador;
				}
				if(isalpha(entrada[j+1])  && entrada[j+1] == 'u' && entrada[j+1] == 117)
				{
					strcat(resposta,"u");
					if(isalpha(entrada[j+2]) || isdigit(entrada[j+2]) || entrada[j+2] == '_' )
					{

						j = j+1;
						goto identificador;
					}

					fprintf(saida,"%s\t\t\t\t\tORL\t\t\t\t\t\t%d\n",resposta,linha);
					if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
					{
						if(entrada[j+2] == 10)
							linha=linha+1;
						j = j+2;
						goto inicio;

					}
					j=j+2;
					goto inicio;

				}

		}

		if(isalpha(c) && c == 'l' && c == 108)
		{
			if((entrada[j+1] != 'e') || isdigit(entrada[j+1]) || entrada[j+1] == '_')
			{
					goto identificador;
			}
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'e' && entrada[j+1] == 101)
			{
				strcat(resposta,"l");
				if((entrada[j+2] != 'i') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"e");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"e");
				j=j+1;
				goto leia;

			}
			leia:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'i' && entrada[j+1] == 105)
			{
				if((entrada[j+2] != 'a') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"i");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"i");
				j=j+1;
				goto leia1;

			}
			leia1:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'a' && entrada[j+1] == 97)
			{
				strcat(resposta,"a");
				if(isalpha(entrada[j+2]) || isdigit(entrada[j+2]) )
				{
					j = j+1;
					goto identificador;
				}

				fprintf(saida,"%s\t\t\t\t\tPR\t\t\t\t\t\t%d\n",resposta,linha);


				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					if(entrada[j+2] == 10)
						linha=linha+1;
					j = j+3;
					goto inicio;

				}
				if(entrada[j+2] == ';')
				{

					j = j+2;
					goto inicio;

				}

				j=j+2;
				goto inicio;
			}


		}
		/*
			* Aqui inicia-se o processo da identifica��o das palavras reservadas que come�am com b
		*/
		if(isalpha(c) && c == 'b' && c == 98)
		{
			if((entrada[j+1] != 'o') || isdigit(entrada[j+1]) || entrada[j+1] == '_')
			{
					goto identificador;
			}
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'o' && entrada[j+1] == 111)
			{
				strcat(resposta,"b");
				if((entrada[j+2] != 'o') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"o");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"o");
				j=j+1;
				goto booleano;

			}
			booleano:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'o' && entrada[j+1] == 111)
			{

				if((entrada[j+2] != 'l') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"o");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"o");
				j=j+1;
				goto booleano1;

			}
			booleano1:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'l' && entrada[j+1] == 108)
			{
				if((entrada[j+2] != 'e') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{

					strcat(resposta,"l");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"l");
				j=j+1;
				goto booleano2;
			}
			booleano2:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'e' && entrada[j+1] == 101)
			{
				if((entrada[j+2] != 'a') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"e");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"e");
				j=j+1;
				goto booleano3;
			}
			booleano3:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'a' && entrada[j+1] == 97)
			{
				if((entrada[j+2] != 'n') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"a");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"a");
				j=j+1;
				goto booleano4;
			}
			booleano4:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'n' && entrada[j+1] == 110)
			{
				if((entrada[j+2] != 'o') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"n");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"n");
				j=j+1;
				goto booleano5;
			}
			booleano5:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'o' && entrada[j+1] == 111)
			{
				strcat(resposta,"o");
				if(isalpha(entrada[j+2]) || isdigit(entrada[j+2]) )
				{
					j = j+1;
					goto identificador;
				}

				fprintf(saida,"%s\t\t\t\tPR\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					if(entrada[j+2] == 10)
						linha=linha+1;
					j = j+3;
					goto inicio;

				}
				if(entrada[j+2] == ';')
				{

					j = j+2;
					goto inicio;

				}

				j=j+2;
				goto inicio;
			}

		}

		/*
			* Aqui inicia-se o processo da identifica��o das palavras reservadas que come�am com r
		*/
		if(isalpha(c) && c == 'r' && c == 114)
		{
			if((entrada[j+1] != 'e') || isdigit(entrada[j+1]) || entrada[j+1] == '_')
			{
					goto identificador;
			}
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'e' && entrada[j+1] == 101)
			{
				strcat(resposta,"r");
				if((entrada[j+2] != 't') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"e");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"e");
				j=j+1;
				goto retorne;

			}
			retorne:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 't' && entrada[j+1] == 116)
			{
				if((entrada[j+2] != 'o') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"t");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"t");
				j=j+1;
				goto retorne1;

			}
			retorne1:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'o' && entrada[j+1] == 111)
			{
				if((entrada[j+2] != 'r') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"o");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"o");
				j=j+1;
				goto retorne2;

			}
			retorne2:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'r' && entrada[j+1] == 114)
			{
				if(( entrada[j+2] != 'n') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"r");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"r");
				j=j+1;
				goto retorne3;

			}
			retorne3:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'n' && entrada[j+1] == 110)
			{
				if(( entrada[j+2] != 'e') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"n");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"n");
				j=j+1;
				goto retorne4;

			}
			retorne4:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'e' && entrada[j+1] == 101)
			{
				strcat(resposta,"e");
				if(isalpha(entrada[j+2]) || isdigit(entrada[j+2]) )
				{
					j = j+1;
					goto identificador;
				}

				fprintf(saida,"%s\t\t\t\t\tPR\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					if(entrada[j+2] == 10)
						linha=linha+1;
					j = j+3;
					goto inicio;

				}
				if(entrada[j+2] == ';')
				{

					j = j+2;
					goto inicio;

				}
				j=j+2;
				goto inicio;
			}
		}
		/*
			* Aqui inicia-se o processo da identifica��o das palavras reservadas que come�am com s
		*/
		if(isalpha(c) && c == 's' && c == 115)
		{
			strcat(resposta,"s");
			if((entrada[j+1] != 'e') || isdigit(entrada[j+1]) || entrada[j+1] == '_')
			{
					goto identificador;
			}
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'e' && entrada[j+1] == 101)
			{
				strcat(resposta,"e");
				if(entrada[j+2] == 'n')
				{
					j=j+1;
					goto senao;
				}
				if(isalpha(entrada[j+2])  || isdigit(entrada[j+2]) )
				{
					j = j+1;
					goto identificador;
				}
				fprintf(saida,"%s\t\t\t\t\tPR\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					if(entrada[j+2] == 10)
						linha=linha+1;
					j = j+3;
					goto inicio;

				}
				j=j+2;
				goto inicio;


			}
			senao:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'n' && entrada[j+1] == 110)
			{
				if((entrada[j+2] != 'a' && entrada[j+2] != -29) || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"n");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"n");
				j=j+1;
				goto senao1;
			}

			senao1:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'a' && entrada[j+1] == 97)
			{
				if((entrada[j+2] != 'o') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"a");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"a");
				j=j+1;
				goto senao2;
			}
			if(entrada[j+1] == -29)
			{
				if(( entrada[j+2] != 'o') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"�");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"�");
				j=j+1;
				goto senao2;
			}
			senao2:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'o' && entrada[j+1] == 111)
			{
				strcat(resposta,"o");
				if(isalpha(entrada[j+2]) || isdigit(entrada[j+2]) )
				{
					j = j+1;
					goto identificador;
				}

				fprintf(saida,"%s\t\t\t\t\tPR\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					if(entrada[j+2] == 10)
						linha=linha+1;
					j = j+3;
					goto inicio;

				}
				j=j+2;
				goto inicio;
			}


		}
		/*
			* Aqui inicia-se o processo da identifica��o das palavras reservadas que come�am com p
		*/
		if(isalpha(c) && c == 'p' && c == 112)
		{
			strcat(resposta,"p");
			if((entrada[j+1] != 'r') || isdigit(entrada[j+1]) || entrada[j+1] == '_')
			{
				goto identificador;
			}
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'r' && entrada[j+1] == 114)
			{
				if((entrada[j+2] != 'o') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"r");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"r");
				j=j+1;

			}
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'o' && entrada[j+1] == 111)
			{
				if((entrada[j+2] != 'g' && entrada[j+2] !='c')|| isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"o");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"o");
				j=j+1;
				if(entrada[j+1] == 'g')
					goto programa;
				if(entrada[j+1] == 'c')
					goto procedimento;

			}

			programa:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'g' && entrada[j+1] == 103)
			{
				if((entrada[j+2] != 'r') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"g");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"g");
				j=j+1;
				goto programa1;
			}
			programa1:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'r' && entrada[j+1] == 114)
			{
				if((entrada[j+2] != 'a') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"r");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"r");
				j=j+1;
				goto programa2;
			}
			programa2:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'a' && entrada[j+1] == 97)
			{
				if(( entrada[j+2] != 'm') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"a");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"a");
				j=j+1;
				goto programa3;
			}
			programa3:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'm' && entrada[j+1] == 109)
			{
				if((entrada[j+2] != 'a') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"m");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"m");
				j=j+1;
				goto programa4;
			}
			programa4:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'a' && entrada[j+1] == 97)
			{
				strcat(resposta,"a");
				if(isalpha(entrada[j+2]) || isdigit(entrada[j+2]) )
				{
					j = j+1;
					goto identificador;
				}

				fprintf(saida,"%s\t\t\t\tPR\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					if(entrada[j+2] == 10)
						linha=linha+1;
					j = j+3;
					goto inicio;

				}
				j=j+2;
				goto inicio;
			}
			procedimento:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'c' && entrada[j+1] == 99)
			{


				if(( entrada[j+2] != 'e') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{

					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"c");
					j = j+1;
					goto identificador;
				}


				strcat(resposta,"c");
				j=j+1;
				goto procedimento1;
			}
			procedimento1:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'e' && entrada[j+1] == 101)
			{
				if((entrada[j+2] != 'd') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"e");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"e");
				j=j+1;
				goto procedimento2;
			}
			procedimento2:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'd' && entrada[j+1] == 100)
			{
				if(entrada[j+2] != 'i' || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"d");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"d");
				j=j+1;
				goto procedimento3;
			}
			procedimento3:
			if(entrada[j+1] == 'i' && entrada[j+1] == 105)
			{
				if(entrada[j+2] != 'm' || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"i");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"i");
				j=j+1;
				goto procedimento4;
			}
			procedimento4:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'm' && entrada[j+1] == 109)
			{
				if(entrada[j+2] != 'e' || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"m");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"m");
				j=j+1;
				goto procedimento5;
			}
			procedimento5:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'e' && entrada[j+1] == 101)
			{
				if(entrada[j+2] != 'n' || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"e");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"e");
				j=j+1;
				goto procedimento6;
			}
			procedimento6:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'n' && entrada[j+1] == 110)
			{
				if( entrada[j+2] != 't' || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"n");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"n");
				j=j+1;
				goto procedimento7;
			}
			procedimento7:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 't' && entrada[j+1] == 116)
			{
				if( entrada[j+2] != 'o' || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"t");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"t");
				j=j+1;
				goto procedimento8;
			}
			procedimento8:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'o' && entrada[j+1] == 111)
			{
				strcat(resposta,"o");
				if(isalpha(entrada[j+2]) || isdigit(entrada[j+2]) )
				{
					j = j+1;
					goto identificador;
				}

				fprintf(saida,"%s\t\t\t\tPR\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					if(entrada[j+2] == 10)
						linha=linha+1;
					j = j+3;
					goto inicio;

				}
				j=j+2;
				goto inicio;
			}

		}

		/*
			* Aqui inicia-se o processo da identifica��o das palavras reservadas que come�am com i
		*/
		if(isalpha(c) && c == 'i' && c == 105)
		{
			if(entrada[j+1] != 'n' || isdigit(entrada[j+1]) || entrada[j+1] == '_')
			{
					goto identificador;
			}
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'n' && entrada[j+1] == 110)
			{
				strcat(resposta,"i");
				if( entrada[j+2] != 't' && entrada[j+2] != 'i' || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"n");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"n");
				j=j+1;
				if(entrada[j+1] == 'i')
					goto ini;
				if(entrada[j+1] == 't')
					goto inteiro;


			}

			ini:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'i' && entrada[j+1] == 105)
			{
				if(entrada[j+2] != 'c' || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"i");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"i");
				j=j+1;
				goto ini1;
			}
			ini1:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'c' && entrada[j+1] == 99)
			{
				if((entrada[j+2] != 'i') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"c");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"c");
				j=j+1;
				goto ini2;
			}
			ini2:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'i' && entrada[j+1] == 105)
			{
				if(entrada[j+2] != 'o' || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"i");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"i");
				j=j+1;
				goto ini3;
			}
			ini3:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'o' && entrada[j+1] == 111)
			{
				strcat(resposta,"o");
				if(isalpha(entrada[j+2]) || isdigit(entrada[j+2]) )
				{
					j = j+1;
					goto identificador;
				}

				fprintf(saida,"%s\t\t\t\t\tPR\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+2] == 10 || entrada[j+2] == 32 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					if(entrada[j+2] == 10)
						linha=linha+1;
					j = j+3;
					goto inicio;

				}
				j=j+2;
				goto inicio;


			}
			inteiro:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 't' && entrada[j+1] == 116)
			{
				if(entrada[j+2] != 'e' || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"t");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"t");
				j=j+1;
				goto inteiro1;
			}
			inteiro1:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'e' && entrada[j+1] == 101)
			{
				if( entrada[j+2] != 'i' || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"e");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"e");
				j=j+1;
				goto inteiro2;
			}
			inteiro2:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'i' && entrada[j+1] == 105)
			{
				if(entrada[j+2] != 'r' || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"i");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"i");
				j=j+1;
				goto inteiro3;
			}
			inteiro3:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'r' && entrada[j+1] == 114)
			{
				if(entrada[j+2] != 'o' || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"r");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"r");
				j=j+1;
				goto inteiro4;
			}
			inteiro4:
			if(isalpha(entrada[j+1]) && entrada[j+1] == 'o' && entrada[j+1] == 111 )
			{
				strcat(resposta,"o");
				if(isalpha(entrada[j+2]) || isdigit(entrada[j+2]) )
				{
					j = j+1;
					goto identificador;
				}

				fprintf(saida,"%s\t\t\t\t\tPR\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+2] == 10 || entrada[j+2] == 32 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					if(entrada[j+2] == 10)
						linha=linha+1;
					j = j+3;
					goto inicio;

				}
				if(entrada[j+2] == ';')
				{

					j = j+2;
					goto inicio;

				}
				j=j+2;
				goto inicio;
			}


	}
	/*
			* Aqui inicia-se o processo da identifica��o das palavras reservadas que come�am com f
	*/
	if(isalpha(c) && c == 'f' && c == 102)
	{
		if((entrada[j+1] != 'a' && entrada[j+1] != 'i' && entrada[j+1] != 'u') || isdigit(entrada[j+1]) || entrada[j+1] == '_')
		{
					goto identificador;
		}
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'a' && entrada[j+1] == 97)
		{
				if( (entrada[j+2] != 'l' && entrada[j+2] != 'c') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				strcat(resposta,"f");
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"a");
					j = j+1;
					goto identificador;
				}

				strcat(resposta,"a");
				j=j+1;
				if(entrada[j+1] == 'c')
					goto faca;
				if(entrada[j+1] == 'l')
					goto falso;
		}
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'i' && entrada[j+1] == 105)
		{
				strcat(resposta,"f");
				if(entrada[j+2] != 'm' || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"i");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"i");
				j=j+1;
				if(entrada[j+1] == 'm')
					goto fim;


		}
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'u' && entrada[j+1] == 117)
		{
				strcat(resposta,"f");
				if((entrada[j+2] != 'n') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"u");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"u");
				j=j+1;
				if(entrada[j+1] == 'n')
					goto funcao;


		}
		faca:
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'c' && entrada[j+1] == 99)
		{
			if((entrada[j+2] != 'a') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"c");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"c");
				j=j+1;
				goto faca1;
		}
		if(entrada[j+1] == -25)
		{
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"�");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"�");
				j=j+1;
				goto faca1;
		}
		faca1:
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'a' && entrada[j+1] == 97)
		{
				if((entrada[j+2] != 'o') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				strcat(resposta,"a");
				if(isalpha(entrada[j+2]) || isdigit(entrada[j+2]) )
				{
					j = j+1;
					goto identificador;
				}

				fprintf(saida,"%s\t\t\t\t\tPR\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					if(entrada[j+2] == 10)
						linha=linha+1;
					j = j+3;
					goto inicio;

				}
				j=j+2;
				goto inicio;
		}
		falso:
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'l' && entrada[j+1] == 108)
		{
				if((entrada[j+2] != 's') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"l");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"l");
				j=j+1;
				goto falso1;
		}
		falso1:
		if(isalpha(entrada[j+1]) && entrada[j+1] == 's' && entrada[j+1] == 115)
		{
				if(( entrada[j+2] != 'o') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"s");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"s");
				j=j+1;
				goto falso2;
		}
		falso2:
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'o' && entrada[j+1] == 111)
		{
				strcat(resposta,"o");
				if(isalpha(entrada[j+2]) || isdigit(entrada[j+2]) )
				{
					j = j+1;
					goto identificador;
				}

				fprintf(saida,"%s\t\t\t\t\tPR\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					if(entrada[j+2] == 10)
						linha=linha+1;
					j = j+3;
					goto inicio;

				}
				if(entrada[j+2] == ';')
				{

					j = j+2;
					goto inicio;

				}
				j=j+2;
				goto inicio;
		}
		fim:
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'm' && entrada[j+1] == 109)
		{
				strcat(resposta,"m");
				if(isalpha(entrada[j+2]) || isdigit(entrada[j+2]) )
				{
					j = j+1;
					goto identificador;
				}

				fprintf(saida,"%s\t\t\t\t\tPR\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					if(entrada[j+2] == 10)
						linha=linha+1;
					j = j+3;
					goto inicio;

				}
				j=j+2;
				goto inicio;
		}
		funcao:
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'n' && entrada[j+1] == 110)
		{
				if((entrada[j+2] != 'c' && entrada[j+2] != -25) || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"n");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"n");
				j=j+1;
				goto funcao1;
		}
		funcao1:
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'c' && entrada[j+1] == 99)
		{
				if(( entrada[j+2] != 'a' && entrada[j+2] != -29) || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"c");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"c");
				j=j+1;
				goto funcao2;
		}
		if(entrada[j+1] == -25)
		{
				if(( entrada[j+2] != 'a' && entrada[j+2] != -29) || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"�");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"�");
				j=j+1;
				goto funcao2;
		}
		funcao2:
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'a' && entrada[j+1] == 97)
		{
				if((entrada[j+2] != 'o') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"a");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"a");
				j=j+1;
				goto funcao3;
		}
		funcao21:
		if(entrada[j+1] == -29)
		{
				if((entrada[j+2] != 'o') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"�");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"�");
				j=j+1;
				goto funcao3;
		}
		funcao3:
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'o' && entrada[j+1] == 111)
		{
				strcat(resposta,"o");
				if(isalpha(entrada[j+2]) || isdigit(entrada[j+2]) )
				{
					j = j+1;
					goto identificador;
				}

				fprintf(saida,"%s\t\t\t\t\tPR\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					if(entrada[j+2] == 10)
						linha=linha+1;
					j = j+2;
					goto inicio;

				}
				j=j+2;
				goto inicio;
		}

	}
	/*
			* Aqui inicia-se o processo da identifica��o das palavras reservadas que come�am com v
	*/
	if(isalpha(c) && c == 'v' && c == 118)
	{
		if((entrada[j+1] != 'a' && entrada[j+1] != 'e') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
		{

					goto identificador;
		}
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'a' && entrada[j+1] == 97)
		{
				strcat(resposta,"v");
				if((entrada[j+2] != 'r' ) || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"a");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"a");
				j=j+1;
				if(entrada[j+1] == 'r')
					goto var;

		}
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'e' && entrada[j+1] == 101)
		{
				strcat(resposta,"v");
				if(( entrada[j+2] != 'r') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"e");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"e");
				j=j+1;
				goto verdadeiro;
		}
		verdadeiro:
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'r' && entrada[j+1] == 114)
		{
				if((entrada[j+2] != 'd') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"r");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"r");
				j=j+1;
				goto verdadeiro1;
		}
		verdadeiro1:
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'd' && entrada[j+1] == 100)
		{
				if((entrada[j+2] != 'a') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"d");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"d");
				j=j+1;
				goto verdadeiro2;
		}
		verdadeiro2:
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'a' && entrada[j+1] == 97)
		{
				if((entrada[j+2] != 'd') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"a");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"a");
				j=j+1;
				goto verdadeiro3;
		}
		verdadeiro3:
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'd' && entrada[j+1] == 100)
		{
				if((entrada[j+2] != 'e') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"d");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"d");
				j=j+1;
				goto verdadeiro4;
		}
		verdadeiro4:
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'e' && entrada[j+1] == 101)
		{
				if((entrada[j+2] != 'i') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"e");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"e");
				j=j+1;
				goto verdadeiro5;
		}
		verdadeiro5:
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'i' && entrada[j+1] == 105)
		{
				if((entrada[j+2] != 'r') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"i");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"i");
				j=j+1;
				goto verdadeiro6;
		}
		verdadeiro6:
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'r' && entrada[j+1] == 114)
		{
				if((entrada[j+2] != 'o') || isdigit(entrada[j+2]) || entrada[j+2] == '_')
				{
					goto identificador;
				}
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					strcat(resposta,"r");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"r");
				j=j+1;
				goto verdadeiro7;
		}
		verdadeiro7:
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'o' && entrada[j+1] == 111)
		{
				strcat(resposta,"o");
				if(isalpha(entrada[j+2]) || isdigit(entrada[j+2]) )
				{
					j = j+1;
					goto identificador;
				}

				fprintf(saida,"%s\t\t\t\tPR\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					if(entrada[j+2] == 10)
						linha=linha+1;
					j = j+3;
					goto inicio;

				}
				if(entrada[j+2] == ';')
				{

					j = j+2;
					goto inicio;

				}
				j=j+2;
				goto inicio;
		}

		var:
		if(isalpha(entrada[j+1]) && entrada[j+1] == 'r' && entrada[j+1] == 114)
		{
				strcat(resposta,"r");
				if(isalpha(entrada[j+2]) || isdigit(entrada[j+2]) )
				{
					j = j+1;
					goto identificador;
				}

				fprintf(saida,"%s\t\t\t\t\tPR\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
				{
					if(entrada[j+2] == 10)
						linha=linha+1;
					j = j+3;
					goto inicio;

				}
			fprintf(saida,"%s\t\t\t\t\tPR\t\t\t\t\t\t%d\n",resposta,linha);
			j=j+2;
			goto inicio;
		}
	}
	/*
			* Aqui inicia-se o processo da identifica��o dos operadores relacionais < , <= e <>
	*/

	if(c == '<' && c == 60)
	{
		sprintf(operador_relacional, "%c", c);
		strcat(resposta,operador_relacional);
		if(isspace(entrada[j+1]) || entrada[j+1] ==  32 || entrada[j+1] == 10 || entrada[j+1] == '\0' ||  entrada[j+1] == 9)
		{

			fprintf(saida,"%s\t\t\t\tORL\t\t\t\t%d\n",resposta,linha);
			if(entrada[j+1] == 10)
				linha=linha+1;
			j=j+2;
			goto inicio;
		}
		memset(&operador_relacional[0], 0, sizeof(operador_relacional));
		if(entrada[j+1] == '=' && entrada[j+1] == 61)
		{
			sprintf(operador_relacional, "%c", entrada[j+1]);
			strcat(resposta,operador_relacional);
			if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
			{

				fprintf(saida,"%s\t\t\t\t\tORL\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+2] == 10)
					linha=linha+1;
				j = j+3;
				goto inicio;

			}
			fprintf(saida,"%s\t\t\t\tORL\t\t\t\t\t\t%d\n",resposta,linha);
			j=j+2;
			goto inicio;

		}

		if(entrada[j+1] == '>' && entrada[j+1] == 62)
		{
			sprintf(operador_relacional, "%c", entrada[j+1]);
			strcat(resposta,operador_relacional);
			if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
			{

				fprintf(saida,"%s\t\t\t\t\tORL\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+2] == 10)
					linha=linha+1;
				j = j+3;
				goto inicio;

			}
			fprintf(saida,"%s\t\t\t\t\tORL\t\t\t\t\t%d\n",resposta,linha);
			j=j+2;
			goto inicio;

		}
	}
	/*
			* Aqui inicia-se o processo da identifica��o dos operadores relacionais >, >=
	*/

	if(c == '>' && c == 62)
	{

		sprintf(operador_relacional, "%c", c);
		strcat(resposta,operador_relacional);
		if(isspace(entrada[j+1]) || entrada[j+1] ==  32 || entrada[j+1] == 10 || entrada[j+1] == '\0' ||  entrada[j+1] == 9)
		{

			fprintf(saida,"%s\t\t\t\t\tORL\t\t\t\t\t\t%d\n",resposta,linha);
			if(entrada[j+1] == 10)
				linha=linha+1;
			j=j+2;
			goto inicio;
		}

		memset(&operador_relacional[0], 0, sizeof(operador_relacional));
		if(entrada[j+1] == '=' && entrada[j+1] == 61)
		{
			sprintf(operador_relacional, "%c", entrada[j+1]);
			strcat(resposta,operador_relacional);
			if(entrada[j+2] == 32 || entrada[j+2] == 10 || entrada[j+2] == '\0' || entrada[j+2] == 9)
			{

				fprintf(saida,"%s\t\t\t\t\tORL\t\t\t\t\t\t%d\n",resposta,linha);
				if(entrada[j+2] == 10)
					linha=linha+1;
				j = j+3;
				goto inicio;

			}


		}
	}

	/*
			* Aqui inicia-se o processo do operador relacional =
	*/
	if(c == '=' && c == 61)
	{
         if(isspace(entrada[j+1]) || entrada[j+1] ==  32 || entrada[j+1] == 10 || entrada[j+1] == '\0' ||  entrada[j+1] == 9)
		{
			sprintf(operador_relacional, "%c", c);
			strcat(resposta,operador_relacional);
			fprintf(saida,"%s\t\t\t\t\tORL\t\t\t\t\t\t%d\n",resposta,linha);
			if(entrada[j+1] == 10)
				linha=linha+1;
			j=j+2;
			goto inicio;
		}

		if(isalpha(entrada[j+1]) || isdigit(entrada[j+1]))
		{
			sprintf(operador_relacional, "%c", c);
			strcat(resposta,operador_relacional);
			fprintf(saida,"%s\t\t\t\tORL\t\t\t\t%d\n",resposta,linha);
			j=j+2;
			goto inicio;
		}
		j=j+1;
		goto inicio;
    }

    /*
			* Aqui inicia-se o processo da identifica��o dos operadores matem�ticos +  e -
	*/
    if(c == '+' && c == 43)
	{
		sprintf(operador, "%c", c);
		strcat(resposta,operador);
         if(isspace(entrada[j+1]) || entrada[j+1] ==  32 || entrada[j+1] == 10 || entrada[j+1] == '\0' ||  entrada[j+1] == 9)
		{

			fprintf(saida,"%s\t\t\t\t\tOM\t\t\t\t\t\t%d\n",resposta,linha);
			if(entrada[j+1] == 10)
				linha=linha+1;
			j=j+2;
			goto inicio;
		}

		if(isalpha(entrada[j+1]) || isdigit(entrada[j+1]))
		{
			fprintf(saida,"%s\t\t\t\t\tOM\t\t\t\t\t\t%d\n",resposta,linha);
			j=j+1;
			goto inicio;
		}
		fprintf(saida,"%s\t\t\t\t\tOM\t\t\t\t\t\t%d\n",resposta,linha);
		j=j+1;
		goto inicio;
    }

	if(c == '-' && c == 45)
	{
		sprintf(operador, "%c", c);
		strcat(resposta,operador);
         if(isspace(entrada[j+1]) || entrada[j+1] ==  32 || entrada[j+1] == 10 || entrada[j+1] == '\0' ||  entrada[j+1] == 9)
		{

			fprintf(saida,"%s\t\t\t\t\tOM\t\t\t\t\t\t%d\n",resposta,linha);
			if(entrada[j+1] == 10)
				linha=linha+1;
			j=j+2;
			goto inicio;
		}
		if(isalpha(entrada[j+1]) || isdigit(entrada[j+1]))
		{

			fprintf(saida,"%s\t\t\t\t\tOM\t\t\t\t\t\t%d\n",resposta,linha);
			j=j+1;
			goto inicio;
		}
		fprintf(saida,"%s\t\t\t\t\tOM\t\t\t\t\t\t%d\n",resposta,linha);
		j=j+1;
		goto inicio;
    }


	/*
			* Aqui inicia-se o processo da identifica��o dos identificadores
	*/
	if(isalpha(c))
	{
		   sprintf(identificador, "%c", c);
		   strcat(resposta,identificador);
           identificador:
           memset(&identificador[0], 0, sizeof(identificador));
           if(isdigit(entrada[j+1]) || isalpha(entrada[j+1]) || entrada[j+1] == '_')
           {

               sprintf(identificador, "%c", entrada[j+1]);
		       strcat(resposta,identificador);
			   j=j+1;
               goto identificador;
           }


            if(entrada[j+1] == 10 || entrada[j+1] == 32 || entrada[j+1] == 0)
			{
						/*
							* Aqui eu fa�o uma verifica��o do tamanho da string somente
							* para a impress�o sair certa no arquivo output
						*/
						if(strlen(resposta) >=7)
							fprintf(saida,"%s\t\t\t\tID\t\t\t\t\t\t%d\n",resposta,linha);
						else
							fprintf(saida,"%s\t\t\t\t\tID\t\t\t\t\t\t%d\n",resposta,linha);

					   if(entrada[j+1] == 10)
						  linha=linha+1;
					   j = j+1;
					   goto inicio;

	 		}
	 		if(entrada[j+1] == '.' || entrada[j+1] == ',' || entrada[j+1] == ';')
	 		{
	 			if(strlen(resposta) >=7)
							fprintf(saida,"%s\t\t\t\tID\t\t\t\t\t\t%d\n",resposta,linha);
				else
							fprintf(saida,"%s\t\t\t\t\tID\t\t\t\t\t\t%d\n",resposta,linha);
	 			j=j+1;
	 			goto inicio;

			}
			if(entrada[j+1] == ')' )
	 		{
	 			if(strlen(resposta) >=7)
							fprintf(saida,"%s\t\t\t\tID\t\t\t\t\t\t%d\n",resposta,linha);
				else
							fprintf(saida,"%s\t\t\t\t\tID\t\t\t\t\t\t%d\n",resposta,linha);
	 			j=j+1;
	 			goto inicio;

			}


        }

		/*
			* Todas as pontua�ões n�o reconhecidas da linguagem levam ao estado de erro l�xico
		*/

		if(ispunct(c)  && c != '{' && c != '"' && c != ':'  && c != ';' && c != ',' && c != '+' && c != '-' && c != '=' && c != '<' && c != '>' && c != '}' && c != '(' && c != ')')
		{
			goto errolexico;
		}

		if(c == '_'  || c == '.')
			goto errolexico;
		if(entrada[j+1] == '\0')
		{

			break;
		}




}



		/*
			* Caso ocorra algum erro l�xico ao longo da an�lise se a flag for setada ele � printado
			* ou caso ele j� seja mandado tamb�m � printado.
		*/
	if(flag==1)
	{

		errolexico:
				printf("ERRO LEXICO - LINHA %d\n",linha);
		indicador=1;
	}


	fclose(abrir);
	fclose(saida);
	free(entrada);
	return indicador;
}
