#include <cstdlib>
#include <iostream>
#include <fstream>


using namespace std;

typedef int tImagem[1000][1000];

string erro;

//tons é o brilho máximo;


int carregaPGM(string nome, tImagem img, int *lin, int *col, int *tons){

    string tipo;
    ifstream arquivo(nome);
    if (!arquivo.is_open()){
        erro = "Erro: Arquivo não encontrado."; 
        return 1;
    }

    arquivo >> tipo;
    if (tipo != "P2"){
        erro = "Erro: Arquivo não tem formato P2."; 
        return 2;
    }
     
    arquivo >> *col >> *lin >> *tons;
    for (int i = 0; i < *lin; i++){
        for (int j = 0; j < *col; j++){
            arquivo >> img[i][j];
        }
    }
    arquivo.close();    
    return 0;
}

int salvaPGM(string nome, tImagem img, int lin, int col, int tons){
    ofstream arquivo(nome);
    if (!arquivo.is_open()){
        erro = "Erro: Arquivo não encontrado."; 
        return 1;
    }

    arquivo << "P2" << endl << col << " " << lin << endl << tons << endl;
    for (int i = 0; i < lin; i++){
        for (int j = 0; j < col; j++){
            arquivo << img[i][j] << " ";
        }
        arquivo << endl;
    }
    
    arquivo.close();
    return 0;
}

void direita(tImagem img_saida, tImagem img_entrada, int linhas, int colunas){
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++)
            img_saida[j][linhas - i - 1] = img_entrada[i][j];
    }
}

void esquerda(tImagem img_saida, tImagem img_entrada, int linhas, int colunas){
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++)
            img_saida[j][i] = img_entrada[i][j];          
    }
}

void binarizar(tImagem img_saida, tImagem img_entrada, int linhas, int colunas, int maior){
  for(int i = 0; i < linhas; i++){
    for(int j = 0; j < colunas; j++){
      if(maior >= img_entrada[i][j]){
        img_saida[i][j] = 255;
      }
      else{
        img_saida[i][j] = 0;
      }
    }  
  }
}

// Supondo que tImagem seja um tipo para representar uma matriz de inteiros
// e que img_saida e img_entrada sejam matrizes válidas de tamanho linhas x colunas
void iconizar(tImagem img_saida, tImagem img_entrada, int linhas, int colunas) {
    int n = 0, m = 0; //novas variáveis que recebem o valor na saída
    int newLin = linhas / 64; 
    int newCol = colunas / 64;

    for (int i = 0, n = 0; i < linhas; i += newLin, n++) {
        for (int j = 0, m = 0; j < colunas; j += newCol, m++) {
            img_saida[n][m] = img_entrada[i][j];
        }
    }
}

// fator - o usuário escolhe um valor para aumentar ou diminuir o brilho da imagem
void brilho(tImagem img_entrada, tImagem img_saida, int linhas, int colunas, int fator) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            int novovalor;
            if (fator > 1) {
                // Clarear a imagem: multiplicar o valor do pixel pelo fator
                novovalor = img_entrada[i][j] * fator;
            } else {
                // Escurecer a imagem: multiplicar o valor do pixel pelo fator e arredondar para baixo
                novovalor = img_entrada[i][j] * fator;
            }

            // garantir que o valor esteja dentro do intervalo [0, 255]
            if (novovalor < 0) {
                novovalor = 0;
            } else if (novovalor > 255) {
                novovalor = 255;
            }

            // Atribuir o novo valor de intensidade ao pixel
            img_saida[i][j] = novovalor;
        }
    }
}

void passabaixa(tImagem img_saida, tImagem img_entrada, int linhas, int colunas, int soma){
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            if(i > 0 && j > 0){
                //continuar...
            }
        }
    }
}

/*
 * Leitura e Escrita de arquivos no formato PGM com funções.
 */
int main(int argc, char** argv) {
    tImagem img_entrada, img_saida;
    int colunas, linhas, tons, opcao, maior;
    string arquivo_entrada, arquivo_saida;
  
    // Leitura do arquivo de entrada da imagem.
    cout << " Entre com o nome da imagem de entrada: ";
    cin >> arquivo_entrada;
    arquivo_entrada = arquivo_entrada + ".pgm";
    if (carregaPGM(arquivo_entrada, img_entrada, &linhas, &colunas, &tons) != 0){
        cout << "\n" + erro + "\n";
        return 1;
    }
    
    cout << "Como deseja alterar a imagem?" << endl;
    cout << "[1] Girar para Direita\n"
         << "[2] Girar para Esquerda\n"
         << "[3] Binarizar\n"
         << "[4] Iconizar\n"
         << "[5] Alterar o Brilho\n"
         << "Opção: ";
    cin >> opcao;
    
   /* if(opcao < 1 || opcao > 6)
        cout << "Opção inválida, digite uma opção apresentada acima!" << endl;*/
    
    if(opcao == 1){
        direita(img_saida, img_entrada, linhas, colunas);
        cout << "Entre com o nome da imagem de saída: ";
        cin >> arquivo_saida;
        arquivo_saida = arquivo_saida + ".pgm";
        if (salvaPGM(arquivo_saida, img_saida, linhas, colunas, tons) != 0){
            cout << "\n" + erro + "\n";
            return 1;
        }
    }    
        
    else if(opcao == 2){
        esquerda(img_saida, img_entrada, linhas, colunas);
        cout << "Entre com o nome da imagem de saída: ";
        cin >> arquivo_saida;
        arquivo_saida = arquivo_saida + ".pgm";
        if (salvaPGM(arquivo_saida, img_saida, linhas, colunas, tons) != 0){
            cout << "\n" + erro + "\n";
            return 1;
        }
    }    
    else if(opcao == 3){
        cout << "Qual será o maior valor dos pixels?" << endl;
        cin >> maior;
        binarizar(img_saida, img_entrada, linhas, colunas, maior);
        cout << "Entre com o nome da imagem de saída: ";
        cin >> arquivo_saida;
        arquivo_saida = arquivo_saida + ".pgm";
        if (salvaPGM(arquivo_saida, img_saida, linhas, colunas, tons) != 0){
            cout << "\n" + erro + "\n";
            return 1;
        }
    }   
    else if(opcao == 4){
        iconizar(img_saida, img_entrada, linhas, colunas);
        cout << "Entre com o nome da imagem de saída: ";
        cin >> arquivo_saida;
        arquivo_saida = arquivo_saida + ".pgm";
        if (salvaPGM(arquivo_saida, img_saida, 64, 64, tons) != 0){
            cout << "\n" + erro + "\n";
            return 1;
        }
    }
    else if(opcao == 5){
        int fator;
        cout << "Dige um fator maior que 1 para clarear ou menor que 0 para escurecer a imagem: "<< endl;
        cin >> fator;
        brilho(img_entrada, img_saida, linhas, colunas, fator);
        cout << "Entre com o nome da imagem de saída: ";
        cin >> arquivo_saida;
        arquivo_saida = arquivo_saida + ".pgm";
        if (salvaPGM(arquivo_saida, img_saida, 64, 64, tons) != 0){
            cout << "\n" + erro + "\n";
            return 1;
        }
    }
    return 0;
}

