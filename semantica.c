


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


/*
	Esta é a struct que é utilizada na análise sintática e semântica.
	Ela possui três campos que são o token, o tipo e a linha ,podendo guardar esses três elementosem sua estrutura
	que serão utilizados posteriormente no processo de backtracking.
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
	Protótipo das Funções
	- Análise Léxica
	- Análise Sintática
	- Análise Semantica
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
	ETAPA 04 - Análise Semântica
	
	
	Nesta etapa é realizada a checagem de tipos das váriáveis e comandos que utilizam expressões booleanas ou inteiras
	como é o caso dos comandos se,atribuição e enquanto.
	
	
	No caso da atribuição ela só trata somente as atribuições básicas não aceitando expressões, pois na minha visão
	não lhe caberia por não ter uma função ternária, mas este processo de checagem de expressões é feito no comando se
	e enquanto.
	
	Caso seja necessário também para a atribuição ele pode ser facilmente implementado.
	
	Como procedimentos não tem retorno eles não são aceitos nos comandos provocando erro semântico.
	
	
	Como técnica criei duas estruturas que armazenam todas as variáveis e seus tipos e conforme a árvore é analisada
	ela checa se a variável ou função já foram declaradas e caso seja afirmativo ela verifica a outra parte analisando se
	ambas são do mesmo tipo, caso sejam a linha com a claúsula é impressa, caso contrário é impresso a linha com o erro 
	semântico.
	
	
	A única exceção é que quando eu tenho uma atribuição, caso uma função seja usada como ID recebendo algo, ele dá erro
	semântico pois uma função não pode receber valores, só váriáveis.
	
	
	Existe uma pasta com todos os testes e erros feitos no corpo do arquivo, demonstrando a funcionalidade do mesmo.
	
	As três partes funcionam em conjunto tanto é que para uma executar a anterior tem que ter sido bem-sucedida, então caso
	teste algo que é capturado pela análise sintática o erro aparecerá e a análise semântica não será executada.
	
	
	Projeto de Compiladores Concluído por Yuri Serrano
	
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
		Técnica de buffering ,a mesma que foi utilizada na análise léxica.
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
			Aqui a última posição do vetor de structs contém o "#"
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
		Vai percorrendo e excluindo qualquer token que não seja var,funcao,se e enquanto e que não seja do tipo ID
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
		Aqui são armazenadas as variáveis na estrutura destinada as mesmas
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
		Aqui são armazenadas as funções na estrutura destinada as mesmas
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
		Aqui inicia-se a checagem das atribuições.
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
		Aqui inicia-se o processo de análise dos comandos se e enquanto
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

	PLP - ETAPA 03  - Análise Sintática


	Aqui verificamos se todos os tokens foram colocados nas posições corretamente pelo usuário.
	Com relação a etapa anterior eu não modifiquei o token do ID, pois nesta etapanão faria sentido
	visto que não iremos tratar o escopo e a duplicação de variáveis, mas na análise semântica será
	feito para a verificação de tipos.
	Como haviam algumas incongruências na gramática eu editei de modo a parecer com o exemplo que encontra-se
	no doc do projeto, a mesma editada encontra-selogo abaixo:

	Estrutura Análise Sintática


	programa ID ;



	bloco


	laço (Essa parte pode ocorrer mais de uma vez)

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

	O comando var do bloco só pode ser usado uma vez por inicio - fim, pois sua produção coloca isso, mas
	ele pode ter dentro dele varias declarações.

	Caso após o fim eu tenha alguma estrutura do bloco ele leva para lá e o processo ocorre novamente.
	A estrutura do se e do enquanto são praticamente iguais mudando os comandos auxiliares que no enquanto é o faca
	e no se o então e o senão.

	Será impresso as lnhas que estão OK sintaticamente e caso apareça algum erro surgirá a mensagem "ERRO SINTÁTICO"
	juntamente com o número da linha que esse problema ocorreu, parando a execução do problema.

	Observação: Os problemas relacionados a sintaxe do programa já foram tratados na análise léxica,então caso seja
	testado ele será acusado como erro léxico parando a execução do programa, não indo fazer a análise sintática.
	A mesma só é possível caso não haja nenhum erro léxico.



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
		Técnica de buffering ,a mesma que foi utilizada na análise léxica.
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
			Aqui a última posição do vetor de structs contém o "#"
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
                if(strcmp(sintatica[percorre].token,"var") == 0 || strcmp(sintatica[percorre].token,"funcao") == 0  || strcmp(sintatica[percorre].token,"função") == 0|| strcmp(sintatica[percorre].token,"procedimento") == 0)
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
				if(strcmp(sintatica[percorre].token,"var") == 0 || strcmp(sintatica[percorre].token,"funcao") == 0   || strcmp(sintatica[percorre].token,"função") == 0 || strcmp(sintatica[percorre].token,"procedimento") ==0 )
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
		Funcao ou Função - OK
	*/
  printf("FUNCAO\n");
	if(strcmp(sintatica[percorre].token,"funcao") == 0 || strcmp(sintatica[percorre].token,"função") == 0 )
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
							if(strcmp(sintatica[percorre].token,"var") == 0 || strcmp(sintatica[percorre].token,"funcao") == 0  ||  strcmp(sintatica[percorre].token,"função") == 0 || strcmp(sintatica[percorre].token,"procedimento") ==0 )
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
							if(strcmp(sintatica[percorre].token,"funcao") == 0  ||  strcmp(sintatica[percorre].token,"função") == 0 || strcmp(sintatica[percorre].token,"procedimento") ==0 )
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
									if(strcmp(sintatica[percorre].token,"var") == 0 || strcmp(sintatica[percorre].token,"funcao") == 0  ||  strcmp(sintatica[percorre].token,"função") == 0 || strcmp(sintatica[percorre].token,"procedimento") ==0 )
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
							if(strcmp(sintatica[percorre].token,"senao") == 0 || strcmp(sintatica[percorre].token,"senão") == 0 )
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
							if((strcmp(sintatica[percorre].token,"senao") == 0 || strcmp(sintatica[percorre].token,"senão") == 0 ))
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
					if(strcmp(sintatica[percorre].token,"senao") == 0 || strcmp(sintatica[percorre].token,"senão") == 0 )
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
					if(strcmp(sintatica[percorre].token,"senao") == 0 || strcmp(sintatica[percorre].token,"senão") == 0 )
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
			Comando Atribuição
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

						if(strcmp(sintatica[percorre].token,"entao") == 0 || strcmp(sintatica[percorre].token,"então") == 0)
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

							if(strcmp(sintatica[percorre].token,"entao") == 0 || strcmp(sintatica[percorre].token,"então") == 0)
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

								if(strcmp(sintatica[percorre].token,"entao") == 0 || strcmp(sintatica[percorre].token,"então") == 0)
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

										if(strcmp(sintatica[percorre].token,"entao") == 0 || strcmp(sintatica[percorre].token,"então") == 0)
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

									if(strcmp(sintatica[percorre].token,"entao") == 0 || strcmp(sintatica[percorre].token,"então") == 0)
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

									if(strcmp(sintatica[percorre].token,"entao") == 0 || strcmp(sintatica[percorre].token,"então") == 0)
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
			Comando Senão
		*/
		if(strcmp(sintatica[percorre].token,"senao") == 0 || strcmp(sintatica[percorre].token,"senão") == 0)
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
		Caso nessa parte tenha o # ele imprime as posições restantes junto com o fim.
		Caso tenha alguma estrutura do bloco ele redireciona para lá o processo é reiniciado novamente.
	*/
	fim:
	if(strcmp(sintatica[percorre].token,"fim") == 0)
	{
		imprime+=1;
		percorre+=1;
		if(strcmp(sintatica[percorre].token,"var") == 0 || strcmp(sintatica[percorre].token,"funcao") == 0 ||strcmp(sintatica[percorre].token,"função") == 0 || strcmp(sintatica[percorre].token,"procedimento") == 0)
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
		Aqui é verificado que caso a flag seja diferente de 0 não teve nenhum erro sintático, caso
		contrário teve e exibirá a linha do erro.
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
	PLP - Etapa 02 - Analisador Léxico

	GRUPO

	Erik Volpert
	Gustavo Santarsieri
	Rogerio Bordignon
	Yuri Serrano



  Observação: Caso a pontuação apareça estranha, é por uma incompatibilidade da IDE com a pontuação, então existe um arquivo a parte com os mesmos dizeres.
  Para não ocorrer um bug ,utilizamos a versão 5.11 do orwell Dev C++.
  Caso use o Bloshedev 4.9.2 irá bugar.

  Observação 1: Devido a uma diferença nas produções e nos exemplos do código que tinham em uns tinha acentuação e em outros não, nosso código identifica dos
  dois modos com ou sem acentuação.

  Observação 2: Fiz adaptações para palavras com acentos.



  Conjunto de Testes

  Na pasta teste a testes adicionais que fiz para comprovar o funcionamento mediante a erros léxicos , comentários e outros
  códigos completos, para testar basta pegar o arquivo entrada que encontrase nas pastas.


  Exemplo:função - funcao





  Documentação - Yuri Serrano




  Nessa segunda etapa estamos utilizando o conceito de buffering, em que todos os caracteres lidos são armazenados em um vetor de char alocados
  dinamicamente com um tamanho de 2000 caracteres podendo esse espaço ser expandido ou não.
  Para cumprir com os requisitos da Etapa 02 , os estados do nosso autômatos são representados pelos rótulos do goto , em que caracter por caracter
  é analisado e após a identificação (ou não) do lexema um token referente ao mesmo é gerado , bem com  o número da linha que o token foi encontrado
  no nosso arquivo texto denominado output que encontra-se no  seguinte formato:

  TOKEN			  TIPO				LINHA


  Para a terceira etapa adotando como dica da professora Daniela, vamos retirar essa primeira linha  e remover o identificador de linhas para facilitar
  no processo da análise sintática.

  Com base na linguagem SIM o analisador léxico reconhece os seguintes tokens:

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

  Todas as palavras reservadas são em letra minúscula obrigatoriamente, pois não inferimos  que a linguagem em questão é case sensitive.

  ________________________________________________________________________________________________________________________________________________


  Classe dos identificadores (L  (D|L|_) )  - ID

  O identificador seguindo a regra  da linguagem SIM obrigatoriamente tem que começar com uma letra, após isso ele pode ser constituído de letras ,
  dígitos ou '_'.Como não foi especificado o tamanho máximo do identificador deixamos o tamanho livre, por não ser uma aplicação que será usada
  inicialmente por diversos usuários.

  Caso o usuário insista em começar com dígitos ou '_' será printado na tela "ERRO LÉXICO" e a linha onde ocorreu o erro.

  Exemplo:

  yuri - ID

  _yuri ou 1yuri - ERRO LÉXICO


  ________________________________________________________________________________________________________________________________________________

  Classe dos Operadores Relacionais Lógicos ( < >  <> <= >= e ou ) - ORL


  Sobre esta classe não temos muitos comentários a respeito,é que decidimos incluir e/ou nesta classe por se tratarem de ORL mesmo estando escritos
  em português.

  ________________________________________________________________________________________________________________________________________________


  Classe dos pontos ( , ;  ) - PT

  Sobre esta classe não temos muitos comentários a respeito, pois a mesma é intuitiva

  ________________________________________________________________________________________________________________________________________________

  Classe dos delimitadores ( ( ) { }  ) - DEL

  Sobre esta classe os delimitadores { } não são colocados no arquivo pois eles são utilizados para delimitar os comentários e tudo o que está
  entre eles e incluindo eles é removido do arquivo.

  ________________________________________________________________________________________________________________________________________________
  Atribuição - ATRIB

  Operador de atribuição.

  ________________________________________________________________________________________________________________________________________________



  Classe dos Literais ( "texto") - LIT

  Sobre esta classe ela é delimitada pelos delimitadores  ( ) em que dentro deles é verificado o começo do " e o término que significa a identifica-
  ção do literal.
  Obrigatoriamente é preciso incluir " " para representar o literal, caso contrário irá aparecer erro léxico.
  Se o delimitador ) não aparecer também irá aparecer erro léxico.

   ________________________________________________________________________________________________________________________________________________

    Classe dos Comentários

    Esta classe possui como delimitadores  { } em que dentro deles o usuário pode colocar qualquer coisa, caso não seja colocado o delimitador }
    será apresentado erro léxico.
    O comentário não é colocado no output do arquivo,bem como os seus delimitadores.
   ________________________________________________________________________________________________________________________________________________

  	Classe dos Operadores Matemáticos

    Esta classe possui somente os operadores + e -.
   ________________________________________________________________________________________________________________________________________________

Processo de identificação dos lexemas e geração dos tokens

Para a identificação dos lexemas os goto simulam um autômato híbrido, em que o processo de identificação é feito em cascata,em que ao término de uma
identificação ele volta ao ínicio para continuar dando prosseguimento ao reconhecimento dos outros tokens.

As palavras reservadas fizemos autômatos próprios iguais ao nosso modelo da etapa 1 que reconhecem todas as palavras reservadas, em que é analisado a primeira
letra de cada palavra reservada e caso a palavra seja reconhecida ela é colocada no arquivo output, caso a palavra tenha qualquer outro caracter que
a modifique ela é encaminhada para o estado identificador e a partir daí é tratada como tal no nosso output.
Para os números enquanto existirem digitos ele vai entrando no estado de dígitos até que seja encontrado o espaço vazio ou algo diferente de um dígito.
E para as demais classes elas adotam o procedimento realizado com a classe de números.

________________________________________________________________________________________________________________________________________________


Eliminação de Espaços Vazios

Foi colocado um laço que elimina espaços vazios em demasia deixando somente um caso a pessoa escreva utilizando espaços.


________________________________________________________________________________________________________________________________________________




Creio eu que todas os pontos que a ETAPA 02 requisitou, conseguimos implementar e fazer funcionar corretamente.


Ao longo do código algumas partes serão comentadas demonstrando a funcionalidade, outras não pois utilizamos basicamente a mesma estrutura
mudando o rótulo do autômato.


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
		* Verifica se o arquivo foi aberto com sucesso ou não.
		* Caso não consiga é emitida uma mensagem informando que não é possível
	*/

	if(abrir == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");

	if(saida == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");




	/*
		* Realiza a alocação dinâmica do vetor de chars entrada com 2000 elementos, podendo
		* este espaço ser aumentado.
	*/
	entrada = malloc(sizeof(char)*2000);

	/*
		* Lê todo o arquivo caracter por caracter até chegar no EOF.
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
		* Ao final do vetor de chars entrada é colocado o símbolo '\0' == 0
		* para que se possa ter uma referência parao término da leitura do
		* vetor de chars.

	*/
	entrada[i]='\0';

	while(j<strlen(entrada))
	{



		inicio:
		/*
			* A função memset serve para zerar o vetor de chars que esta armazenando
			* a string que foi colocada no arquivo output.
			* Assim que a mesma é gravada quando o processo volta ao estado inicio
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
		// Verifica-se se tem um espaço vazio
		if(c == 32)
		{

			/*
				* Este laço vai eliminando os espaços vazios em demasia que se encontram no
				* arquivo deixando somente um, que é tratado pelos nossos autômatos caso
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
			* Como processo da eliminação de espaços o único que sobrar é eliminado
			* Como esse espaço é eliminado sobrará o o elemento a ser identificado  ou \n == 10
			* ou o final do vetor de chars que é '\0' == 0
		*/
		if(entrada[j] == 32)
		{
			j=j+1;
			goto inicio;
		}

		/*
			* Se a entrada for um \n ele soma1 a variável linha e anda uma posição passando para
			* a variável c que será avaliada nos casos a seguir.

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
			* Se o valor for 0 ('\0') o laço é interrompido, indicando que a leitura
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

		//Aqui verifica se é "
		if(c == 34 )
		{
			sprintf(literal, "%c", c);
			strcat(resposta,literal);


				// Enquanto não chegar na outra " o laço vai continuando e o conteúdo sendo gravado no vetor  resposta
			while(entrada[j+1] != 34 )
			{
				//Se ele chegar ao terminador '\0' quer dizer que não achou o outro terminador



				if(entrada[j+1] == 0)
					goto errolexico;
				sprintf(literal, "%c", entrada[j+1]);
				strcat(resposta,literal);
				j=j+1;
			}
				//Assim que " é encontrado a string no vetor resposta é gravada no output
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


				// Enquanto não chegar na outra " o laço vai continuando e o conteúdo sendo gravado no vetor  resposta
			while(entrada[j+1] != -108 )
			{
				//Se ele chegar ao terminador '\0' quer dizer que não achou o outro terminador



				if(entrada[j+1] == 0)
					goto errolexico;
				sprintf(literal, "%c", entrada[j+1]);
				strcat(resposta,literal);
				j=j+1;
			}
				//Assim que " é encontrado a string no vetor resposta é gravada no output
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
		//Aqui caso seja encontrado ) é gravado no output
		if(c == ')')
		{
			    sprintf(delimitador, "%c", c);
				strcat(resposta,delimitador);
				fprintf(saida,"%s\t\t\t\t\tDEL\t\t\t\t\t\t%d\n",resposta,linha);
				j=j+1;
				goto inicio;
		}


		//Aqui verifica se uma pontuação foi achada e caso seja é gravada no arquivo output
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
			* Aqui inicia-se o reconhecimento dos comentários e sua eliminação
			* do arquivo
		*/
		if(c == '{' && c == 123)
		{
			comentario:
			/*
				* Após a identificação do do primeiro delimitador ele vai passando toda posição
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

			// Aqui verifica se achou um espaço, se sim volta ao inicio
			if(entrada[j+1] == '}' && entrada[j+2] == 32)
			{

				j=j+3;
				goto inicio;
			}
			// Aqui verifica se achou o final do vetor de entradas se sim o laço é interrompido
			if(entrada[j+1] == '}' && entrada[j+2] == 0)
			{
				j=j+3;
				printf("Comentario");
				break;
			}
			// Aqui verifica se existe elementos como letras, dígitos ou '_' depois do comentário se sim volta para o inicio
			if(entrada[j+1] == '}' && isdigit(entrada[j+2] ) || isalpha(entrada[j+2]) || entrada[j+2] == '_' )
			{
				j=j+2;
				goto inicio;

			}
		}


		/*
			* Aqui é feito o processo de indentificação dos números.
		*/
		if(isdigit(c))
		{

			sprintf(numero, "%c", c);
			strcat(resposta,numero);

			numero:
			memset(&numero[0], 0, sizeof(numero));


			/*
				* Aqui é como se tivesse um próprio referenciamento a este estado, enquanto tiver dígitos ele vai percorrendo
				* Caso ele encontre letras não vai para o estado de errolexico ,pois a pessoa pode ter escrito sem espaços.
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
			* Aqui inicia-se o processo da identificação das palavras reservadas que começam com e
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
					strcat(resposta,"ã");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"ã");
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
			* Aqui inicia-se o processo da identificação das palavras reservadas que começam com b
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
			* Aqui inicia-se o processo da identificação das palavras reservadas que começam com r
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
			* Aqui inicia-se o processo da identificação das palavras reservadas que começam com s
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
					strcat(resposta,"ã");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"ã");
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
			* Aqui inicia-se o processo da identificação das palavras reservadas que começam com p
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
			* Aqui inicia-se o processo da identificação das palavras reservadas que começam com i
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
			* Aqui inicia-se o processo da identificação das palavras reservadas que começam com f
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
					strcat(resposta,"ç");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"ç");
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
					strcat(resposta,"ç");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"ç");
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
					strcat(resposta,"ã");
					j = j+1;
					goto identificador;
				}
				strcat(resposta,"ã");
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
			* Aqui inicia-se o processo da identificação das palavras reservadas que começam com v
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
			* Aqui inicia-se o processo da identificação dos operadores relacionais < , <= e <>
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
			* Aqui inicia-se o processo da identificação dos operadores relacionais >, >=
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
			* Aqui inicia-se o processo da identificação dos operadores matemáticos +  e -
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
			* Aqui inicia-se o processo da identificação dos identificadores
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
							* Aqui eu faço uma verificação do tamanho da string somente
							* para a impressão sair certa no arquivo output
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
			* Todas as pontuaçÃµes não reconhecidas da linguagem levam ao estado de erro léxico
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
			* Caso ocorra algum erro léxico ao longo da análise se a flag for setada ele é printado
			* ou caso ele já seja mandado também é printado.
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
