#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100

typedef struct {
    char itens[MAX][14];  // Armazenar números binários de 13 bits como strings + \0
    int topo;
} Pilha;

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int estaCheia(Pilha *p) {
    return p->topo == MAX - 1;
}

int estaVazia(Pilha *p) {
    return p->topo == -1;
}

// Empilha um número binário (string)
void empilhar(Pilha *p, char binario[14]) {
    if (estaCheia(p)) {
        printf("Pilha cheia!\n");
        return;
    }
    strcpy(p->itens[++(p->topo)], binario);
    printf("Empilhou %s na pilha\n", binario);
}

// Desempilha um número binário (string)
void desempilhar(Pilha *p, char binario[14]) {
    if (estaVazia(p)) {
        printf("Pilha vazia!\n");
        strcpy(binario, "");  // Retorna uma string vazia
        return;
    }
    strcpy(binario, p->itens[(p->topo)--]);
    printf("Desempilhou %s da pilha\n", binario);
}

void mostrarPilha(Pilha *p) {
    printf("Estado da pilha: ");
    for (int i = 0; i <= p->topo; i++) {
        printf("%s ", p->itens[i]);
    }
    printf("\n");
}

int obterSinal(char binario[14]) {
    return (binario[0] - '0'); // Retorna 0 ou 1 pelo sinal do número
}

void zerarString(char str[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        str[i] = '0';  // Preenche com '0'
    }
    str[tamanho - 1] = '\0';  
}

// Função para somar bits binários com carry
int somarBits(char bit1, char bit2, int vaiUmEntrada , int *vaiUmSaida) {
    int soma = (bit1 - '0') + (bit2 - '0') + vaiUmEntrada ;
    *vaiUmSaida = soma / 2;  // Define o novo carry(valor que está sendo transportado para operação atual)
    return soma % 2;        // Retorna o bit resultante
}

// Função auxiliar para subtrair dois dígitos binários e o borrow (valor que está sendo emprestado para a operação atual)
int subtrairBits(char bit1, char bit2, int emprestaEntrada, int *emprestaSaida) {
    int sub = (bit1 - '0') - (bit2 - '0') - emprestaEntrada;
    if (sub < 0) {
        sub += 2;
        *emprestaSaida = 1;
    } else {
        *emprestaSaida = 0;
    }
    return sub;
}

// Função para subtrair dois números binários (com parte inteira e decimal)
void subtrairNumerosBinarios(char bin1[14], char bin2[14], char resultado[14]) {
    int borrow = 0; 
    for (int i = 12; i >= 1; i--) {
        int bit_subtraido = subtrairBits(bin1[i], bin2[i], borrow, &borrow);
        resultado[i] = bit_subtraido + '0';  // Armazena o bit resultante
    }
    resultado[13] = '\0';  // Finaliza a string
}

// Função para somar dois números binários (com parte inteira e decimal)
void somarNumerosBinarios(char bin1[14], char bin2[14], char resultado[14]) {
    int carry = 0;
    for (int i = 12; i >= 1; i--) {
        int bit_somado = somarBits(bin1[i], bin2[i], carry, &carry);
        resultado[i] = bit_somado + '0';  // Armazena o bit resultante
    }
    resultado[13] = '\0';  // Finaliza a string
}

void multiplicarNumerosBinarios(char bin1[14], char bin2[14], char resultado[14]) {
    zerarString(resultado, 14);

    // Obter sinais dos números
    int sinal1 = obterSinal(bin1);
    int sinal2 = obterSinal(bin2);

    // Se o resultado for negativo, define o sinal
    if (sinal1 != sinal2) {
        resultado[0] = '1'; // Sinal negativo
    } else {
        resultado[0] = '0'; // Sinal positivo
    }

    // Converte as partes inteiras e fracionárias para decimal
    int parteInteira1 = 0, parteInteira2 = 0;
    double parteFracao1 = 0.0, parteFracao2 = 0.0;

    // Converte a parte inteira (bits 1 a 8)
    for (int i = 1; i <= 8; i++) {
        parteInteira1 = parteInteira1 * 2 + (bin1[i] - '0');
        parteInteira2 = parteInteira2 * 2 + (bin2[i] - '0');
    }

    // Converte a parte fracionária (bits 9 a 12)
    double fator = 0.5;
    for (int i = 9; i <= 12; i++) {
        parteFracao1 += (bin1[i] - '0') * fator;
        parteFracao2 += (bin2[i] - '0') * fator;
        fator /= 2;
    }

    // Calcula o número total em decimal (parte inteira + fracionária)
    double num1 = parteInteira1 + parteFracao1;
    double num2 = parteInteira2 + parteFracao2;

    // Realiza a multiplicação
    double produto = num1 * num2;

    // Separa a parte inteira e fracionária do resultado
    int parteInteiraResultado = (int)produto;
    double parteFracaoResultado = produto - parteInteiraResultado;

    // Converte a parte inteira de volta para binário (8 bits)
    for (int i = 8; i >= 1; i--) {
        resultado[i] = (parteInteiraResultado % 2) + '0';
        parteInteiraResultado /= 2;
    }

    // Converte a parte fracionária de volta para binário (4 bits)
    fator = 0.5;
    for (int i = 9; i <= 12; i++) {
        if (parteFracaoResultado >= fator) {
            resultado[i] = '1';
            parteFracaoResultado -= fator;
        } else {
            resultado[i] = '0';
        }
        fator /= 2;
    }

    resultado[13] = '\0';  // Finaliza a string
}


// Função para dividir dois números binários
void dividirNumerosBinarios(char bin1[14], char bin2[14], char resultado[14]) {
    zerarString(resultado, 14);

    int sinal1 = obterSinal(bin1);
    int sinal2 = obterSinal(bin2);

    // Se o resultado for negativo, define o sinal
    if (sinal1 != sinal2) {
        resultado[0] = '1'; // Sinal negativo
    } else {
        resultado[0] = '0'; // Sinal positivo
    }

    // Converte as partes inteiras e fracionárias para decimal
    int parteInteira1 = 0, parteInteira2 = 0;
    double parteFracao1 = 0.0, parteFracao2 = 0.0;

    // Converte a parte inteira (bits 1 a 8)
    for (int i = 1; i <= 8; i++) {
        parteInteira1 = parteInteira1 * 2 + (bin1[i] - '0');
        parteInteira2 = parteInteira2 * 2 + (bin2[i] - '0');
    }

    // Converte a parte fracionária (bits 9 a 12)
    double fator = 0.5;
    for (int i = 9; i <= 12; i++) {
        parteFracao1 += (bin1[i] - '0') * fator;
        parteFracao2 += (bin2[i] - '0') * fator;
        fator /= 2;
    }

    // Calcula o número total em decimal (parte inteira + fracionária)
    double num1 = parteInteira1 + parteFracao1;
    double num2 = parteInteira2 + parteFracao2;

    // Verifica divisão por zero
    if (num2 == 0.0) {
        printf("Erro: Divisão por zero!\n");
        return;
    }

    // Realiza a divisão
    double quociente = num1 / num2;

    // Separa a parte inteira e fracionária do resultado
    int parteInteiraResultado = (int)quociente;
    double parteFracaoResultado = quociente - parteInteiraResultado;

    // Converte a parte inteira de volta para binário (8 bits)
    for (int i = 8; i >= 1; i--) {
        resultado[i] = (parteInteiraResultado % 2) + '0';
        parteInteiraResultado /= 2;
    }

    // Converte a parte fracionária de volta para binário (4 bits)
    fator = 0.5;
    for (int i = 9; i <= 12; i++) {
        if (parteFracaoResultado >= fator) {
            resultado[i] = '1';
            parteFracaoResultado -= fator;
        } else {
            resultado[i] = '0';
        }
        fator /= 2;
    }

    resultado[13] = '\0';  // Finaliza a string
}

// Função para exponenciar dois números binários (considerando apenas a parte inteira)
void exponenciarNumerosBinarios(char base[14], char expoente[14], char resultado[14]) {
    zerarString(resultado, 14);

    // Converte as partes inteiras para decimal
    int baseDecimal = 0, expoenteDecimal = 0;
    for (int i = 1; i <= 8; i++) {
        baseDecimal = baseDecimal * 2 + (base[i] - '0');
        expoenteDecimal = expoenteDecimal * 2 + (expoente[i] - '0');
    }

    // Calcula a exponenciação (base ^ expoente) em decimal
    int potencia = pow(baseDecimal, expoenteDecimal);

    // Converte o resultado de volta para binário
    for (int i = 8; i >= 1; i--) {
        resultado[i] = (potencia % 2) + '0';
        potencia /= 2;
    }

    // Converte a parte fracionária para binário (assumindo zero)
    for (int i = 9; i <= 12; i++) {
        resultado[i] = '0';
    }
    resultado[13] = '\0';
}

// Realiza operações com a pilha
void realizarOperacao(Pilha *p, char op) {
    if (p->topo < 1) {
        printf("Não há operandos suficientes na pilha!\n");
        return;
    }

    char bin2[14], bin1[14];
    desempilhar(p, bin2);  // Retira o de cima da pilha
    desempilhar(p, bin1);  // Retira o de baixo da pilha

    char resultado[14];
    zerarString(resultado, 14);

    switch (op) {
        case '+':
            somarNumerosBinarios(bin1, bin2, resultado);
            break;
        case '-':
            subtrairNumerosBinarios(bin1, bin2, resultado);
            break;
        case '*':
            multiplicarNumerosBinarios(bin1, bin2, resultado);
            break;
        case '/':
            dividirNumerosBinarios(bin1, bin2, resultado);
            break;
        case '^':
            exponenciarNumerosBinarios(bin1, bin2, resultado);
            break;
        default:
            printf("Operação inválida!\n");
            return;
    }

    empilhar(p, resultado);
    printf("Resultado da operação %c: %s\n", op, resultado);
}

int main() {
    Pilha pilha;
    inicializarPilha(&pilha);

    char binario[14];
    char operacao;
    int opcao;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Inserir número binário na pilha\n");
        printf("2. Somar (+)\n");
        printf("3. Subtrair (-)\n");
        printf("4. Multiplicar (*)\n");
        printf("5. Dividir (/)\n");
        printf("6. Exponenciar (^)\n");  
        printf("7. Mostrar pilha\n");
        printf("8. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o número binário de 13 dígitos (sinal + 8 inteiros + 4 decimais): ");
                scanf("%s", binario);
                empilhar(&pilha, binario);
                break;
            case 2:
                realizarOperacao(&pilha, '+');
                break;
            case 3:
                realizarOperacao(&pilha, '-');
                break;
            case 4:
                realizarOperacao(&pilha, '*');
                break;
            case 5:
                realizarOperacao(&pilha, '/');
                break;
            case 6:
                realizarOperacao(&pilha, '^');
                break;
            case 7:
                mostrarPilha(&pilha);
                break;
            case 8:
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opção inválida!\n");
        }
    }

 return 0;
}