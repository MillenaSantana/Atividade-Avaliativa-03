#include <stdio.h>

#define MAX 1000

// ==================================================
// PESSOA 1 - CRIACAO E LEITURA DE ARQUIVOS
// ==================================================

void criarArquivo() {
    FILE *arquivo = fopen("dados.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao criar dados.txt!\n");
        return;
    }

    int valores[] = {64, 34, 25, 12, 11, 90};
    int n = (int)(sizeof(valores) / sizeof(valores[0]));

    for (int i = 0; i < n; i++) {
        fprintf(arquivo, "%d\n", valores[i]);
    }

    if (fclose(arquivo) != 0) {
        printf("Erro ao fechar dados.txt!\n");
        return;
    }

    printf("Arquivo dados.txt criado com sucesso!\n");
}

int lerArquivo(int vetor[]) {
    FILE *arquivo = fopen("dados.txt", "r");
    int n = 0;
    int resultado;

    if (arquivo == NULL) {
        printf("Erro ao abrir dados.txt!\n");
        return -1;
    }

    while (n < MAX && (resultado = fscanf(arquivo, "%d", &vetor[n])) == 1) {
        n++;
    }

    if (!feof(arquivo) && n == MAX) {
        printf("Aviso: limite de %d numeros atingido.\n", MAX);
    } else if (!feof(arquivo) && resultado != EOF) {
        printf("Erro: dados.txt contem um valor invalido.\n");
        fclose(arquivo);
        return -1;
    }

    if (ferror(arquivo)) {
        printf("Erro durante a leitura de dados.txt!\n");
        fclose(arquivo);
        return -1;
    }

    fclose(arquivo);
    return n;
}

// ==================================================
// PESSOA 2 - ALGORITMOS DE ORDENACAO
// ==================================================

void bubbleSort(int vetor[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                int aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

void insertionSort(int vetor[], int n) {
    for (int i = 1; i < n; i++) {
        int valor = vetor[i];
        int j = i - 1;

        while (j >= 0 && vetor[j] > valor) {
            vetor[j + 1] = vetor[j];
            j--;
        }

        vetor[j + 1] = valor;
    }
}

void selectionSort(int vetor[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int menorPosicao = i;

        for (int j = i + 1; j < n; j++) {
            if (vetor[j] < vetor[menorPosicao]) {
                menorPosicao = j;
            }
        }

        int aux = vetor[i];
        vetor[i] = vetor[menorPosicao];
        vetor[menorPosicao] = aux;
    }
}

void merge(int vetor[], int temp[], int esquerda, int meio, int direita) {
    int i = esquerda;
    int j = meio + 1;
    int k = esquerda;

    while (i <= meio && j <= direita) {
        if (vetor[i] <= vetor[j]) {
            temp[k++] = vetor[i++];
        } else {
            temp[k++] = vetor[j++];
        }
    }

    while (i <= meio) {
        temp[k++] = vetor[i++];
    }

    while (j <= direita) {
        temp[k++] = vetor[j++];
    }

    for (i = esquerda; i <= direita; i++) {
        vetor[i] = temp[i];
    }
}

void mergeRec(int vetor[], int temp[], int esquerda, int direita) {
    if (esquerda >= direita) {
        return;
    }

    int meio = esquerda + (direita - esquerda) / 2;

    mergeRec(vetor, temp, esquerda, meio);
    mergeRec(vetor, temp, meio + 1, direita);
    merge(vetor, temp, esquerda, meio, direita);
}

void mergeSort(int vetor[], int n) {
    int temp[MAX];

    if (n > 1) {
        mergeRec(vetor, temp, 0, n - 1);
    }
}

void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(int vetor[], int baixo, int alto) {
    int pivo = vetor[alto];
    int i = baixo - 1;

    for (int j = baixo; j < alto; j++) {
        if (vetor[j] <= pivo) {
            i++;
            troca(&vetor[i], &vetor[j]);
        }
    }

    troca(&vetor[i + 1], &vetor[alto]);
    return i + 1;
}

void quickSort(int vetor[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionar(vetor, baixo, alto);
        quickSort(vetor, baixo, pi - 1);
        quickSort(vetor, pi + 1, alto);
    }
}

// ==================================================
// PESSOA 3 - EXIBICAO E GRAVACAO DO RESULTADO
// ==================================================

void imprimirVetor(int vetor[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int salvarOrdenado(int vetor[], int n) {
    FILE *arquivo = fopen("ordenado.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao criar ordenado.txt!\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (fprintf(arquivo, "%d\n", vetor[i]) < 0) {
            printf("Erro ao gravar ordenado.txt!\n");
            fclose(arquivo);
            return 0;
        }
    }

    if (fclose(arquivo) != 0) {
        printf("Erro ao fechar ordenado.txt!\n");
        return 0;
    }

    printf("Resultado salvo em ordenado.txt!\n");
    return 1;
}

void menuOrdenacao(int vetor[], int n) {
    int opcao;

    if (n <= 0) {
        printf("Nao existem numeros para ordenar.\n");
        return;
    }

    printf("\n===== MENU DE ORDENACAO =====\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Insertion Sort\n");
    printf("3 - Selection Sort\n");
    printf("4 - Merge Sort\n");
    printf("5 - Quick Sort\n");
    printf("Escolha o algoritmo: ");

    if (scanf("%d", &opcao) != 1) {
        printf("Entrada invalida!\n");
        return;
    }

    switch (opcao) {
        case 1:
            bubbleSort(vetor, n);
            break;
        case 2:
            insertionSort(vetor, n);
            break;
        case 3:
            selectionSort(vetor, n);
            break;
        case 4:
            mergeSort(vetor, n);
            break;
        case 5:
            quickSort(vetor, 0, n - 1);
            break;
        default:
            printf("Opcao invalida!\n");
            return;
    }

    printf("\nNumeros ordenados:\n");
    imprimirVetor(vetor, n);
    salvarOrdenado(vetor, n);
}

// ==================================================
// PESSOA 4 - ALTERACAO DE VALORES E TESTES
// ==================================================

void alterarValor() {
    int vetor[MAX];
    int n = lerArquivo(vetor);

    if (n <= 0) {
        printf("Nao foi possivel ler os dados. Verifique dados.txt.\n");
        return;
    }

    printf("\n===== NUMEROS ATUAIS =====\n");
    for (int i = 0; i < n; i++) {
        printf("Posicao %d: %d\n", i + 1, vetor[i]);
    }

    int posicao;
    printf("\nDigite a posicao que deseja alterar (1 a %d): ", n);

    if (scanf("%d", &posicao) != 1) {
        printf("Entrada invalida!\n");
        return;
    }

    if (posicao < 1 || posicao > n) {
        printf("Posicao invalida! Nenhuma alteracao foi feita.\n");
        return;
    }

    int novoValor;
    printf("Digite o novo valor: ");

    if (scanf("%d", &novoValor) != 1) {
        printf("Entrada invalida!\n");
        return;
    }

    vetor[posicao - 1] = novoValor;

    FILE *arquivo = fopen("dados.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao atualizar dados.txt!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        if (fprintf(arquivo, "%d\n", vetor[i]) < 0) {
            printf("Erro ao gravar dados.txt!\n");
            fclose(arquivo);
            return;
        }
    }

    if (fclose(arquivo) != 0) {
        printf("Erro ao fechar dados.txt!\n");
        return;
    }

    printf("\nValor alterado com sucesso!\n");
    printf("Dados atualizados:\n");
    imprimirVetor(vetor, n);

    // Ler novamente o arquivo para confirmar a alteracao.
    int confirmacao[MAX];
    int quantidade = lerArquivo(confirmacao);

    if (quantidade < 0) {
        printf("Nao foi possivel confirmar os dados atualizados.\n");
        return;
    }

    printf("Conteudo atual de dados.txt:\n");
    imprimirVetor(confirmacao, quantidade);
}

// ==================================================
// MENU PRINCIPAL - INTEGRACAO DO PROGRAMA
// ==================================================

void limparEntrada() {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
        /* descarta o restante da entrada invalida */
    }
}

int lerOpcao() {
    int opcao;

    if (scanf("%d", &opcao) != 1) {
        limparEntrada();
        return -999;
    }

    return opcao;
}

int main() {
    int opcao;

    do {
        printf("\n========== MENU PRINCIPAL ==========\n");
        printf("1 - Criar/recriar dados.txt\n");
        printf("2 - Exibir dados atuais\n");
        printf("3 - Alterar um numero\n");
        printf("4 - Ordenar numeros\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        opcao = lerOpcao();

        switch (opcao) {
            case 1:
                criarArquivo();
                break;

            case 2: {
                int vetor[MAX];
                int n = lerArquivo(vetor);

                if (n >= 0) {
                    printf("\nNumeros em dados.txt:\n");
                    imprimirVetor(vetor, n);
                }
                break;
            }

            case 3:
                alterarValor();
                break;

            case 4: {
                int vetor[MAX];
                int n = lerArquivo(vetor);

                if (n > 0) {
                    menuOrdenacao(vetor, n);
                } else if (n == 0) {
                    printf("O arquivo nao possui numeros.\n");
                }
                break;
            }

            case 0:
                printf("Programa encerrado!\n");
                break;

            case -999:
                printf("Entrada invalida! Digite um numero do menu.\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
