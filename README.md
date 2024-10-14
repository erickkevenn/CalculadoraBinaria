# **Calculadora de Binários - Estrutura de Dados**

Este repositório contém o projeto de uma calculadora de números binários, desenvolvida como parte da disciplina **Estrutura de Dados** na Universidade Federal de Alagoas (UFAL). O objetivo principal do projeto foi explorar a manipulação de números binários utilizando uma estrutura de pilha para realizar operações aritméticas.

## **Funcionalidades**

A calculadora permite realizar as seguintes operações com números binários de 13 bits, onde:

- **1 bit** é reservado para o **sinal**: `0` para **números positivos** e `1` para **números negativos**.
- **8 bits** representam a parte inteira do número.
- **4 bits** representam a parte fracionária do número.

As operações disponíveis são:

- **Soma (`+`)**
- **Subtração (`-`)**
- **Multiplicação (`*`)**
- **Divisão (`/`)**
- **Exponenciação (`^`)**

Além disso, a calculadora oferece as seguintes funcionalidades adicionais:

- Empilhamento de números binários
- Desempilhamento para realizar operações
- Exibição do estado atual da pilha

## **Como Utilizar**

1. Clone o repositório:

    ```bash
    git clone https://github.com/seu_usuario/calculadora-binarios.git
    ```

2. Compile o código:

    ```bash
    gcc calculadora.c -o calcbin -lm
    ```

3. Execute o programa:

    ```bash
    ./calcbin
    ```

4. No menu interativo, empilhe **dois números binários** antes de realizar qualquer operação. Após empilhar, você poderá selecionar as operações desejadas.

   - Cada número binário deve ter 13 dígitos no total: o primeiro dígito indica o sinal (`0` para positivo e `1` para negativo), seguido por 8 bits da parte inteira e 4 bits da parte fracionária.

## **Exemplo de Uso**

```bash
Menu:
1. Inserir número binário na pilha
2. Somar (+)
3. Subtrair (-)
4. Multiplicar (*)
5. Dividir (/)
6. Exponenciar (^)
7. Mostrar pilha
8. Sair
Escolha uma opção: 1
Digite o número binário de 13 dígitos (sinal + 8 inteiros + 4 decimais): 0000001100000
Empilhou 0000001100000 na pilha
Escolha uma opção: 1
Digite o número binário de 13 dígitos (sinal + 8 inteiros + 4 decimais): 0000001010000
Empilhou 0000001010000 na pilha
Escolha uma opção: 2
Resultado da operação +: 0000010110000

```

## **Contribuidores**

Este projeto foi desenvolvido por:

- **Efraim Lopes**
- **Erick Keven**
- **Luís Felipe**
- **Rodrigo Moreira**
