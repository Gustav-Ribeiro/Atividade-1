#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAM 100

typedef struct students {
    char nome[50];
    char numero[50];
    char curso[50];
    char nota1[50];
    char nota2[50];
} students;

int abrirArquivos(FILE **arquivoEntrada, FILE **arquivoSaida);
void processarDados(FILE *arquivoEntrada, FILE *arquivoSaida);
const char *calcularSituacao(float media);

int main() {
    FILE *arquivoEntrada, *arquivoSaida;

    if (abrirArquivos(&arquivoEntrada, &arquivoSaida) != 0) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    processarDados(arquivoEntrada, arquivoSaida);

    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    printf("DEU BOM FAMILIA. olhe o  arquivo SituacaoFinal.csv.\n");

    return 0;
}

int abrirArquivos(FILE **arquivoEntrada, FILE **arquivoSaida) {
    *arquivoEntrada = fopen("DadosEntrada.csv", "r");
    *arquivoSaida = fopen("SituacaoFinal.csv", "w");
    
    if (*arquivoEntrada == NULL || *arquivoSaida == NULL) {
        return 1; 
    }

    return 0; 
}

void processarDados(FILE *arquivoEntrada, FILE *arquivoSaida) {
    char tamanho[MAX_TAM];
    students line;

    fgets(tamanho, sizeof(tamanho), arquivoEntrada);

    fprintf(arquivoSaida, "Nome,Media,Situacao\n");

    while (fgets(tamanho, sizeof(tamanho), arquivoEntrada)) {
        char *token = strtok(tamanho, ",");
        strcpy(line.nome, token);
        token = strtok(NULL, ",");
        strcpy(line.numero, token);
        token = strtok(NULL, ",");
        strcpy(line.curso, token);
        token = strtok(NULL, ",");
        strcpy(line.nota1, token);
        token = strtok(NULL, ",");
        strcpy(line.nota2, token);

        double nota1 = atof(line.nota1);
        double nota2 = atof(line.nota2);

        float media = (nota1 + nota2) / 2.0;

        const char *situacao = calcularSituacao(media);

        fprintf(arquivoSaida, "%s,%.2f,%s\n", line.nome, media, situacao);
    }
}

const char *calcularSituacao(float media) {
    if (media >= 7.0) {
        return "Aprovado";
    } else {
        return "Reprovado";
    }
}

