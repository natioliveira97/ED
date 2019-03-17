/** 
	\file calculadora.c
	\author Natalia Oliveira Borges - 16/0015863
	\date 04/17
	\name Resolução de Expressōes e Calculadora
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pilha.h" /* Biblioteca de funçōes para tipo pilha. */
#include "calculadora.h" /* Biblioteca de funçōes para calculadora */

/** Define tamanho máximo da entrada do modo resolução de expressōes.*/
#define ENTRADA1 1000

/** Define tamanho máximo da entrada do modo calculadora.*/
#define ENTRADA2 20


// Implementação das funçōes:

double transforma_em_numero(char *numero, int tamanho){
	double resultado = 0; // Resultado da transformação do vetor de char em um ponto flutuante.
	int potencia     = -1; // Indica qual a potencia de 10 cada algarismo deve ser multiplicado. 
	int i;

	for(i = 0; numero[i] != ',' && i < tamanho; ++i){
		++potencia;
	} //end for
	for(i = 0; i < tamanho; ++i){
		if(numero[i]>='0' && numero[i]<='9'){
			resultado += (numero[i]-'0')*pow(10, potencia);
			--potencia;
		}//end if
	} //end for

	return resultado;
}

void imprime_numero(double numero){
	int i;
	int auxnumero = numero;

	// Se o número for inteiro, imprime o valor inteiro. 
	if(auxnumero == numero){
		printf("%d\n",auxnumero);
	}
	// Se o número tiver parte decimal
	else{
		char string_numero[500]; // String auxiliar para mudar o ponto pela virgula no ponto flutuante.
		sprintf(string_numero, "%lf",numero);
		for(i = 0; i < 500 && string_numero[i] != '\0'; ++i){
			if(string_numero[i] == '.'){
				string_numero[i] = ',';
			}
		}
		printf("%s\n", string_numero);
	}
}

int caractere_valido(char c){
	if((c>='0' && c<='9') || 
	    c=='+' || 
	    c=='-' || 
	    c=='*' || 
	    c=='/' || 
	    c=='(' || 
	    c==')' || 
	    c=='[' || 
	    c==']' || 
	    c=='{' || 
	    c=='}' || 
	    c==' ' || 
	    c==','){
		return 1;
	}// end if

	return 0;
}

int validacao_de_equacao(char *expressao, int tamanho){
	int i;
	int valida = 0; // É acrescentado quando lê um operando e decrementado quando lê um operador, percebe se a expressão estiver errada sintaticamente.
	int ponto = 0; // Verifica se o número passado tem parte decimal.

	for (i = 0; i < tamanho && expressao[i] != '\0'; ++i){
		if(caractere_valido(expressao[i])){
			// Se a expressao[i] for um número:
			if((expressao[i] >= '0' && expressao[i] <= '9') || expressao[i] == ','){
				++valida;
				// Percorre o número até o final.
				while(i < tamanho && ((expressao[i] >= '0' && expressao[i] <= '9') || expressao[i] == ',')){
					// Se houver um '.' no número é preciso verificar se antes e depois dele há um caractere numérico e se há apenas um '.'.
					if(expressao[i] == '.'){
						if(i == 0 || i == tamanho-1 || (expressao[i-1] < '0' || expressao[i-1] > '9') || (expressao[i+1] < '0' || expressao[i+1] > '9')){
							return 0;
						}
						else{
							++ponto;
							if(ponto > 1){
								return 0;
							}
						}
					} //end if
					++i;
				} //end while
				ponto = 0;
			} //end if

			// Se a expressao[i] for um sinal de + ou -:
			if(expressao[i] == '+' || expressao[i] == '-'){
				// É preciso um cuidado especial com esses sinais pois eles podem não indicar uma operação, mas sim o sinal do número que vem em seguida.
				// Se o sinal for o primeiro elemento da expressāo ou se logo antes do sinal estiver um caractere de abertura de escopo, esse sinal indica se o numero é positivo ou negativo, não é operador.
				if(i == 0 || (expressao[i-1] == '(' || expressao[i-1] == '[' || expressao[i-1] == '{')){
					valida = valida;
				}
				// Em outros casos, o sinal pode ser considerado operador.
				else{
					--valida;
				}
			} //end if

			// Se a expressao[i] for um sinal de * ou /:
			if(expressao[i] == '*' || expressao[i] == '/'){
				--valida;
			}

			// Deve-se checar se não há número seguido de número ou operador seguido de operador, nesses casos, a expressão não é válida. 
			if(valida != 0 && valida != 1){
				return 0;
			}
		} //end if

		// Se o caractere não for válido.
		else{
			return 0;	
		}
	}
	// Como toda expressão deve terminar com um número, a variável valida deve ser 1 no final.
	if (valida != 1){
		return 0;
	}
	return 1;
}

int validacao_de_escopo(char *expressao, int tamanho){
	int i;
	t_pilha *delimitatores_de_equacao = get_pilha(); //Pilha de ponto flutuante utilizada para armazenar os valores inteiros dos caracteres correspondentes.

	for(i = 0; i < tamanho && expressao[i] != '\0'; ++i){
		// Se a expressao[i] for um símbolo de abertura de escopo:
		if(expressao[i] == '(' || expressao[i] == '[' || expressao[i] == '{'){
			// Empilha o símbolo.
			inserir_elemento(delimitatores_de_equacao, (int) expressao[i]);
		}

		// Se a expressao[i] for um símbolo de fechamento de escopo:
		if(expressao[i] == ')' || expressao[i] == ']' || expressao[i] == '}'){
			// Se a pilha estiver vazia, um escopo que não foi aberto está sendo fechado, a expressão é inválida.
			if (pilha_vazia(delimitatores_de_equacao)){
				libera_pilha(delimitatores_de_equacao);
				return 0;
			}
			// Se o topo da pilha possuir um delimitador de abertura correspondente ao de fechamento, retira-se o topo da pilha, caso contrario, a expressão é inválida.
			switch(expressao[i]){
				case ')':
					if (delimitatores_de_equacao->topo->dado == '('){
						retirar_elemento(delimitatores_de_equacao);
					}
					else{
						libera_pilha(delimitatores_de_equacao);
						return 0;
					}
					break;
				case ']':
					if (delimitatores_de_equacao->topo->dado == '['){
						retirar_elemento(delimitatores_de_equacao);
					}
					else{
						libera_pilha(delimitatores_de_equacao);
						return 0;
					}
					break;
				case '}':
					if (delimitatores_de_equacao->topo->dado == '{'){
						retirar_elemento(delimitatores_de_equacao);
					}
					else{
						libera_pilha(delimitatores_de_equacao);
						return 0;
					}
					break;
			} //end switch
		} //end if	
	} //end for

	// Se ao final a pilha estiver vazia, a expressão é válida.
	if(pilha_vazia(delimitatores_de_equacao)){
		libera_pilha(delimitatores_de_equacao);
		return 1;
	}

	libera_pilha(delimitatores_de_equacao);
	return 0;
}

int validacao_de_entrada(char *expressao, int tamanho){
	if(validacao_de_equacao(expressao, tamanho)==1 && validacao_de_escopo(expressao,tamanho)==1){
		return 1;
	}
	return 0;
}

char* forma_posfixa(char *expressao, int tamanho){
	int i = 0, j = 0;
	char *expressao_posfixa = (char *) malloc(sizeof(char) * tamanho * 2); // A expressão_posfixa pode ser maior que a infixa, pois serão colocados espaços entre os elementos.
	t_pilha *operadores     = get_pilha(); // Pilha que determina a ordem de operaçōes na expressão posfixa. Serão empilhados os valores inteiros dos caracteres na pilha de ponto flutuante.

	for(i = 0; i < tamanho && expressao[i] != '\0'; ++i){
		// Se expressao[i] for um número:
		if((expressao[i] >= '0' && expressao[i] <= '9') || expressao[i] == ','){
			// Copia o número na expressão posfixa.
			expressao_posfixa[j] = expressao[i]; ++j;
			// Quando chega ao final do número, um espaço é colocado.
			if(i+1 < tamanho){
				if((expressao[i+1] < '0' || expressao[i+1] > '9') && expressao[i+1] != ','){
					expressao_posfixa[j]=' ';++j;
				}
			}
		} //end if

		// Se expressao[i] for um sinal de + ou -:
		else if(expressao[i] == '+' || expressao[i] == '-'){
			// Se for um sinal que indica de o número é positivo ou negativo, copia o sinal na expressão posfixa.
			if(i == 0 || (expressao[i-1] == '(' || expressao[i-1] == '[' || expressao[i-1] == '{')){
				expressao_posfixa[j] = expressao[i]; ++j;
			}
			// Se o sinal for um operador:
			else {
				// Enquanto a pilha não estiver vazia, e seu topo for um operador de prioridade maior ou igual ao encontrado, copia o topo na a expressão posfixa e retira o topo.
				while(!pilha_vazia(operadores) && (operadores->topo->dado=='*' || operadores->topo->dado=='/' ||operadores->topo->dado=='+' || operadores->topo->dado=='-')){
					expressao_posfixa[j] = operadores->topo->dado; ++j;
					expressao_posfixa[j] = ' '; ++j;
					retirar_elemento(operadores);
				}
				// Empilha o operador.
				inserir_elemento(operadores, (int) expressao[i]);
			}
		} // end else if

		// Se expressao[i] for um sinal de * ou /:
		else if(expressao[i] == '*' || expressao[i] == '/'){
			// Enquanto a pilha não estiver vazia, e seu topo for um operador de prioridade maior ou igual ao encontrado, copia o topo na expressão posfixa e retira o topo.
			while(!pilha_vazia(operadores) && (operadores->topo->dado == '*' || operadores->topo->dado == '/')){
					expressao_posfixa[j] = operadores->topo->dado; ++j;
					expressao_posfixa[j] = ' '; ++j;
					retirar_elemento(operadores);
			}
			// Empilha o operador.
			inserir_elemento(operadores, (int) expressao[i]);
		} // end else if

		// Se expressao[i] for um sinal de abertura de escopo:
		else if(expressao[i] == '(' || expressao[i] == '[' || expressao[i] == '{'){
			// Empilha o sinal.
			inserir_elemento(operadores, (int) expressao[i]);
		} // end else if

		// Se expressao[i] for um sinal de fechamento de escopo:
		else if(expressao[i] == ')' || expressao[i] == ']' || expressao[i] == '}'){
			// Enquanto não encontrar o seu sinal de abertura correspondente, copia o topo da pilha para a expressão posfixa e retira o topo.
			if (expressao[i] == ')'){
				while(operadores->topo->dado != '('){
					expressao_posfixa[j] = operadores->topo->dado; ++j;
					expressao_posfixa[j] = ' '; ++j;
					retirar_elemento(operadores);
				}
				retirar_elemento(operadores);
			}
			if (expressao[i] == ']'){
				while(operadores->topo->dado != '['){
					expressao_posfixa[j] = operadores->topo->dado; ++j;
					expressao_posfixa[j] = ' '; ++j;
					retirar_elemento(operadores);
				}
				retirar_elemento(operadores);
			}
			if (expressao[i] == '}'){
				while(operadores->topo->dado!='{'){
					expressao_posfixa[j]=operadores->topo->dado; ++j;
					expressao_posfixa[j]=' ';++j;
					retirar_elemento(operadores);
				}
				retirar_elemento(operadores);
			}
		}
	}

	// Enquanto a pilha não estiver vazia, copia o topo para a expressão posfixa e retira o topo.
	while(!pilha_vazia(operadores)){
		expressao_posfixa[j] = operadores->topo->dado; ++j;
		expressao_posfixa[j] = ' '; ++j;
		retirar_elemento(operadores);
	}
	// Um '\0' é colocado para indicar o final da expressão posfixa.
	expressao_posfixa[j]='\0';
	printf("%s\n",expressao_posfixa);

	libera_pilha(operadores);

	return expressao_posfixa;
}

double avalia_expressao(char *expressao, int tamanho){
	int i;
	int inicio; // Armazena a posição do primeiro algarismo de um número.
	int tamanho_numero; //Armazena quantas posiçōes o número ocupa.
	int sinal = 1; // Indica se o número é positivo ou negativo.
	double numero; // Número resultado da transformação de um vetor de caracteres numéricos.
	double n1,n2,n3; // Auxiliares.
	t_pilha *resultado = get_pilha(); // Pilha que realiza a resolução da expressão.

	for(i = 0; i < tamanho && expressao[i] != '\0'; ++i){
		// Se expressao[i] for um número.
		if(expressao[i] >= '0' && expressao[i] <= '9'){
			tamanho_numero = 0;
			inicio = i; // Guarda a posição de inicio.
			// Percorre todo o número, e acrescenta a variável tamanho_numero.
			while((expressao[i] >= '0' && expressao[i] <= '9')||expressao[i] == ','){
				++tamanho_numero;
				++i;
			}
			// Transforma o vetor de caracteres numéricos em número passando o endereço do primeiro algarismo e o tamanho do vetor para a função transforma_em_numero().
			numero = transforma_em_numero(&expressao[inicio], tamanho_numero);
			// Verifica se o número é negativo.
			if(sinal == -1){
				numero = -numero;
				sinal = 1;
			}
			// Empilha o número.
			inserir_elemento(resultado, numero);
		} //end if

		// Se a expressao[i] for um sinal de + ou -:
		if(expressao[i]=='+' || expressao[i]=='-'){
			/* Se na posição seguinte tiver um algarismo, significa que esse sinal indica se o número é positivo ou negativo.
			   Podemos fazer isso porque, na função que tranforma em posfixa, após os operadores foram colocados espaços. */
			if(expressao[i+1] != ' '){
				if(expressao[i] == '-'){
					sinal *= -1; 
				}
			}
			// Se o sinal for operador, desempilha os dois últimos números e realiza a operação, empilha o resultado a operação.
			else{
				n1 = resultado->topo->dado;
				n2 = resultado->topo->anterior->dado;
				if(expressao[i] == '+'){
					n3 = n2+n1;
				}
				if(expressao[i] == '-'){
					n3 = n2-n1;
				}
				retirar_elemento(resultado);
				retirar_elemento(resultado);
				inserir_elemento(resultado, n3);
			}
		} //end if

		// Se a expressao[i] for um sinal de * ou /:
		if(expressao[i]=='*' || expressao[i]=='/'){
			// Desempilha os dois últimos números e realiza a operação, empilha o resultado a operação.
			n1 = resultado->topo->dado;
			n2 = resultado->topo->anterior->dado;
			if(expressao[i] == '*'){
				n3 = n2*n1;
			}
			if(expressao[i] == '/'){
				n3 = n2/n1;
			}
			retirar_elemento(resultado);
			retirar_elemento(resultado);
			inserir_elemento(resultado, n3);
		} //end if
	} //end for

	n3 = resultado->topo->dado;
	libera_pilha(resultado);
	return n3;
}

int atualiza_calculadora(t_pilha *calculadora, char *entrada){
	int i,j;
	int inicio; // Armazena a posição do primeiro algarismo de um número.
	int tamanho; //Armazena quantas posiçōes o número ocupa.
	int sinal = 0; // Indica se o número é positivo ou negativo.
	int auxn1; // Necesário para saber se o número de copias da operação 'c' é inteiro.
	int ponto; // Valida o  uso de ponto flutuante.
	double numero; // Número resultado da transformação de um vetor de caracteres numéricos.
	double n1,n2,n3; // Auxiliares.

	for(i = 0; i < ENTRADA2 || entrada[i] != '\0'; ++i){
		// Se a entrada for um dos caracteres de saida da função.
		if(entrada[i] == 'x'|| entrada[i] == 'X'){
			return 0;
		} //end if

		// Se a entrada for número:
		else if(entrada[i] >= '0' && entrada[i] <= '9'){
			ponto = 0;
			tamanho = 0;
			inicio = i; // Guarda a posição de inicio.
			// Percorre todo o número, e acrescenta a variável tamanho.
			while((entrada[i] >= '0' && entrada[i] <= '9') || entrada[i] == ','){
				++tamanho;
				++i;
				if(entrada[i] == ','){
					++ponto;
					if(ponto>1){
						return 3;
					}
				}
			}
			// Se o final do número coincidir com o final da entrada:
			if(entrada[i] == '\0'){
				// Transforma o vetor de caracteres numéricos em número.
				numero = transforma_em_numero(&entrada[inicio], tamanho);
				if(sinal == 1){
					numero = -numero;
				}
				// Empilha o número.
				inserir_elemento(calculadora, numero);
				return 1;
			}
			// Se após o número houver algo a mais na entrada, a entrada é inválida.
			else{
				return 3;
			}
		} //end else if

		// Se a entrada for um sinal de +, -, * ou /:
		else if(entrada[0] == '+' || entrada[0] == '-' || entrada[0] == '*' || entrada[0] == '/'){
			// Se a entrada for apenas o sinal, desempilha o dois últimos números e realiza a operação entre eles.
			if(entrada[1]=='\0'){
				// Se não houver pelo menos dois elementos na pilha, o numero de operandos é insuficiente.
				if(tamanho_pilha(calculadora) < 2){
					return 2;
				}
				else{
					n1 = calculadora->topo->dado;
					n2 = calculadora->topo->anterior->dado;
					if(entrada[0] == '+'){
						n3 = n2+n1;
					}
					if(entrada[0] == '-'){
						n3 = n2-n1;
					}
					if(entrada[0] == '*'){
						n3 = n2*n1;
					}
					if(entrada[0] == '/'){
						n3 = n2/n1;
					}
					retirar_elemento(calculadora);
					retirar_elemento(calculadora);
					inserir_elemento(calculadora, n3);
					return 1;
				}
			} //end if

			// Se após os sinais houver um sinal !, realiza-se a operação em toda a pilha.
			else if(entrada[1] == '!' && entrada[2] == '\0'){
				// Se não houver pelo menos dois elementos na pilha, o numero de operandos é insuficiente.
				if(tamanho_pilha(calculadora) < 2){
					return 2;
				}
				else {
					while(tamanho_pilha(calculadora) > 1){
						n1 = calculadora->topo->dado;
						n2 = calculadora->topo->anterior->dado;
						if(entrada[0]=='+'){
							n3 = n2+n1;
						}
						if(entrada[0]=='-'){
							n3 = n2-n1;
						}
						if(entrada[0]=='*'){
							n3 = n2*n1;
						}
						if(entrada[0]=='/'){
							n3 = n2/n1;
						}
						retirar_elemento(calculadora);
						retirar_elemento(calculadora);
						inserir_elemento(calculadora, n3);
					}
					return 1;
				}
			} //end else if

			// Se houver um algarismo após os sinais de + ou -, esse sinal indica se o número é positivo ou negativo.
			else if((entrada[0] == '+' || entrada[0] == '-') && (entrada[1] >= '0' && entrada[1] <= '9')){
				if(entrada[0] == '-'){
					sinal = 1;
				}
			} //end else if

			// Se após o sinal houver algo diferente dos casos anteriore na entrada, a entrada é inválida.
			else{
				return 3;
			} //end else
		} //end else if

		// Se a entrada for apenas o caractere 'c'.
		else if(entrada[0]=='c' && entrada[1]=='\0'){
			// Se não houver pelo menos dois elementos na pilha, o número de operandos é insuficiente.
			if(tamanho_pilha(calculadora)<2){
				return 2;
			}
			else{
				n1 = calculadora->topo->dado;
				auxn1 = n1;
				// Se o número do topo da pilha for inteiro não negativo, a operação de cópia de elementos pode ser concluida.
				if(auxn1 == n1 && auxn1 >= 0){
					retirar_elemento(calculadora);
					n2 = calculadora->topo->dado;
					retirar_elemento(calculadora);
					for(j = 1; j<=auxn1; ++j){
						inserir_elemento(calculadora, n2);	
					}
					return 1;						
				}
				// Se o número do topo da pilha não for inteiro ou for negativo, a operação de cópia de elemento não pode ser concluida.
				else{
					return 4;
				}
			}
		} //end else if

		// Se a entrada for qualquer uma não mencionada anteriormente, a entrada é inválida.
		else{
			return 3;
		}
	} //end for

	return 3;
}

void resolucao_de_expressao(){
	char *expressao = (char *) malloc(sizeof(char)*ENTRADA1);
	char *expressao_posfixa;
	double resultado; // Resultado da expressão.
	int i;

	for(i = 0; i < ENTRADA1; ++i){
		expressao[i] = '\0';
	}

	system("clear");

	printf("MODO RESOLUÇÃO DE EXPRESSŌES\n\n");

	printf("Digite a expressão:\n");
	scanf("%[^\n]", expressao);
	while(getchar()!='\n');

	// Se a expressão for válida.
	if(validacao_de_entrada(expressao, ENTRADA1) == 1){
		printf("\nA expressão %s é válida.\n", expressao);
		printf("\nTransformando essa expressão para posfixa:\n");

		expressao_posfixa = forma_posfixa(expressao, ENTRADA1);
		resultado = avalia_expressao(expressao_posfixa, ENTRADA1*2);

		printf("\nO resultado dessa expressão é:\n");
		imprime_numero(resultado);

	} //end if

	// Se a expressão não for válida.
	else{
		printf("A expressão %s não é válida.\n",expressao);
	} //end else

	printf("\nPressione 'Enter' para voltar ao menu.\n");
	while(getchar()!='\n');

	free(expressao);
	free(expressao_posfixa);
}

void calculadora(){
	t_pilha *calculadora = get_pilha();
	char *entrada        = (char *) malloc(sizeof(char)*ENTRADA2);
	int opcao            = 1;
	int i;
	
	while(opcao!=0){
		for(i = 0; i < ENTRADA2; ++i){
			entrada[i] = '\0';
		}
		system("clear");
		printf("Para sair, digite: 'X'.\n\n");
		printf("MODO CALCULADORA\n\n");

		if(opcao==2){
			printf("Não há elementos suficientes na pilha.\n\n");
		}
		if(opcao==3){
			printf("Entrada Inválida.\n\n");
		}
		if(opcao==4){
			printf("Para usar o comando 'c' o topo da pilha precisa ser inteiro não negativo.\n\n");
		}

		imprime_pilha(calculadora);
		printf("->");
		scanf("%[^\n]",entrada);
		while(getchar()!='\n');
		opcao = atualiza_calculadora(calculadora, entrada);
	}
	libera_pilha(calculadora);	
	free(entrada);
}