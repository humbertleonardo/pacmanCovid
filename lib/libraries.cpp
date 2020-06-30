#include <iostream>
#include "libraries.h"

using namespace std;

SDL_Texture *parede, *remedio, *alcool, *fantasmaTexture, *pacmanTexture, *coracaoLogo, *textoVidas, *textoPontos, *numeros;

Bloco mapa[tamanhoMapa][tamanhoMapa];
Fantasma fanstasmas[qtdFantasmas];
Pacman pacman;

char direcaoPacman = pacman.direcao;

int qtdPilulasRestantes = 0;
int ultimoQuadroFantasma = 0, ultimoQuadroPacman = 0, ultimoQuadroPoder = 0, quadroAtual = 0;

SDL_Texture *carregaImagem(const char *imagem, SDL_Renderer *renderizador) {
  
  SDL_Surface *surface = SDL_LoadBMP(imagem); 
  SDL_Texture *textura = SDL_CreateTextureFromSurface(renderizador, surface);
  SDL_FreeSurface(surface);

  return textura;
}
void carregaTexturas(SDL_Renderer *renderer) {
  parede = carregaImagem("assets/texture.bmp", renderer);
  remedio = carregaImagem("assets/remedio.bmp", renderer);
  alcool = carregaImagem("assets/alcool.bmp", renderer);
  fantasmaTexture = carregaImagem("assets/covid.bmp", renderer);
  pacmanTexture = carregaImagem("assets/ambulance.bmp", renderer);
  coracaoLogo = carregaImagem("assets/life.bmp", renderer);
  textoVidas = carregaImagem("assets/vidas_font.bmp", renderer);
  textoPontos = carregaImagem("assets/pontos_font.bmp", renderer);
  numeros = carregaImagem("assets/numeros_font.bmp", renderer);
}
void criaMapa() {
  // Define todas bordas como paredes
  for (int linha = 0; linha < tamanhoMapa; linha++) {
    for (int coluna = 0; coluna < tamanhoMapa; coluna++) {
      mapa[linha][coluna].posX = tamanhoBlocos*coluna;
      mapa[linha][coluna].posY = tamanhoBlocos*linha;
      
      if (linha == 0 || linha == tamanhoMapa-1 || coluna == 0 || coluna == tamanhoMapa-1) {
        mapa[linha][coluna].tipo = 1;
      }
    }
  }
    
    

    criaCasaFantasma();
    criaObstaculos();
    distribuiAlcool(4);
    distribuiPontos();   
  
  // Cria o portal
    mapa[9][0].tipo = 0;
    mapa[9][20].tipo = 0;

  
}
void criaObstaculos() {
    // Obstaculos
    mapa[2][2].tipo = 1;
    mapa[2][3].tipo = 1;
    mapa[2][4].tipo = 1;

    mapa[4][2].tipo = 1;
    mapa[4][3].tipo = 1;
    mapa[4][4].tipo = 1;

    mapa[2][6].tipo = 1;
    mapa[2][7].tipo = 1;
    mapa[2][8].tipo = 1;

    mapa[1][10].tipo = 1;
    mapa[2][10].tipo = 1;

    mapa[2][12].tipo = 1;
    mapa[2][13].tipo = 1;
    mapa[2][14].tipo = 1;

    mapa[2][16].tipo = 1;
    mapa[2][17].tipo = 1;
    mapa[2][18].tipo = 1;

    mapa[4][6].tipo = 1;
    mapa[5][6].tipo = 1;
    mapa[6][6].tipo = 1;
    mapa[6][7].tipo = 1;
    mapa[6][8].tipo = 1;

    mapa[4][14].tipo = 1;
    mapa[5][14].tipo = 1;
    mapa[6][14].tipo = 1;
    mapa[6][13].tipo = 1;
    mapa[6][12].tipo = 1;

    mapa[4][16].tipo = 1;
    mapa[4][17].tipo = 1;
    mapa[4][18].tipo = 1;

    mapa[4][8].tipo = 1;
    mapa[4][9].tipo = 1;
    mapa[4][10].tipo = 1;
    mapa[4][11].tipo = 1;
    mapa[4][12].tipo = 1;
    mapa[5][10].tipo = 1;
    mapa[6][10].tipo = 1;

    mapa[18][2].tipo = 1;
    mapa[18][3].tipo = 1;
    mapa[18][4].tipo = 1;

    mapa[18][6].tipo = 1;
    mapa[18][7].tipo = 1;
    mapa[18][8].tipo = 1;

    mapa[16][2].tipo = 1;
    mapa[16][3].tipo = 1;
    mapa[16][4].tipo = 1;

    mapa[16][6].tipo = 1;
    mapa[15][6].tipo = 1;
    mapa[14][6].tipo = 1;
    mapa[14][7].tipo = 1;
    mapa[14][8].tipo = 1;

    mapa[16][14].tipo = 1;
    mapa[15][14].tipo = 1;
    mapa[14][14].tipo = 1;
    mapa[14][13].tipo = 1;
    mapa[14][12].tipo = 1;

    mapa[16][8].tipo = 1;
    mapa[16][9].tipo = 1;
    mapa[16][10].tipo = 1;
    mapa[16][11].tipo = 1;
    mapa[16][12].tipo = 1;
    mapa[15][10].tipo = 1;
    mapa[14][10].tipo = 1;

    mapa[18][18].tipo = 1;
    mapa[18][17].tipo = 1;
    mapa[18][16].tipo = 1;

    mapa[18][14].tipo = 1;
    mapa[18][13].tipo = 1;
    mapa[18][12].tipo = 1;

    mapa[16][18].tipo = 1;
    mapa[16][17].tipo = 1;
    mapa[16][16].tipo = 1;

    mapa[19][10].tipo = 1;
    mapa[18][10].tipo = 1;

    mapa[12][6].tipo = 1;
    mapa[12][7].tipo = 1;
    mapa[12][8].tipo = 1;
    mapa[12][9].tipo = 1;
    mapa[12][10].tipo = 1;
    mapa[12][11].tipo = 1;
    mapa[12][12].tipo = 1;
    mapa[12][13].tipo = 1;
    mapa[12][14].tipo = 1;

    mapa[8][1].tipo = 1;
    mapa[10][1].tipo = 1;
    mapa[8][2].tipo = 1;
    mapa[10][2].tipo = 1;

    mapa[6][2].tipo = 1;
    mapa[6][3].tipo = 1;
    mapa[6][4].tipo = 1;
    mapa[7][4].tipo = 1;
    mapa[8][4].tipo = 1; 
    mapa[8][5].tipo = 1; 

    mapa[6][18].tipo = 1;
    mapa[6][17].tipo = 1;
    mapa[6][16].tipo = 1;
    mapa[7][16].tipo = 1;
    mapa[8][16].tipo = 1; 
    mapa[8][15].tipo = 1;

    mapa[12][2].tipo = 1;
    mapa[13][2].tipo = 1;
    mapa[14][2].tipo = 1; 

    mapa[10][5].tipo = 1;
    mapa[10][4].tipo = 1;
    mapa[11][4].tipo = 1;
    mapa[12][4].tipo = 1;
    mapa[13][4].tipo = 1;
    mapa[14][4].tipo = 1; 

    mapa[10][15].tipo = 1;
    mapa[10][16].tipo = 1;
    mapa[11][16].tipo = 1;
    mapa[12][16].tipo = 1;
    mapa[13][16].tipo = 1;
    mapa[14][16].tipo = 1; 

    mapa[12][18].tipo = 1;
    mapa[13][18].tipo = 1;
    mapa[14][18].tipo = 1; 

    mapa[8][18].tipo = 1;
    mapa[10][18].tipo = 1;
    mapa[8][19].tipo = 1;
    mapa[10][19].tipo = 1;
}
void criaCasaFantasma() {
    // Casa onde nasce os montros
    mapa[8][10].tipo = 3;
    mapa[8][7].tipo = 1;
    mapa[8][8].tipo = 1;
    mapa[8][9].tipo = 1;
    mapa[8][11].tipo = 1;
    mapa[8][12].tipo = 1;
    mapa[8][13].tipo = 1;

    mapa[9][7].tipo = 1;
    mapa[9][8].tipo = 3;
    mapa[9][9].tipo = 3;
    mapa[9][10].tipo = 3;
    mapa[9][11].tipo = 3;
    mapa[9][12].tipo = 3;
    mapa[9][13].tipo = 1;

    mapa[10][7].tipo = 1;
    mapa[10][8].tipo = 1;
    mapa[10][9].tipo = 1;
    mapa[10][10].tipo = 1;
    mapa[10][11].tipo = 1;
    mapa[10][12].tipo = 1;
    mapa[10][13].tipo = 1;
}
void distribuiAlcool(int quantidade) {
  srand (time(NULL));

  int distribuidos = 0;
  for (int i = 0; i < quantidade; i++) {
    int linhaRandom = 0, colunaRandom = 0;
    bool invalido = true;

    while (invalido) {
      linhaRandom = rand() % (tamanhoMapa-3)+1;
      colunaRandom = rand() % (tamanhoMapa-3)+1;

      if (validaPosicao(linhaRandom, colunaRandom)) {
        invalido = false;
      }
      
    }
    
    mapa[linhaRandom][colunaRandom].tipo = 4;
    distribuidos++;  
  }

}
void distribuiPontos() {
  for (int linha = 0; linha < tamanhoMapa; linha++) {
    for (int coluna = 0; coluna < tamanhoMapa; coluna++) {
      if (mapa[linha][coluna].tipo == 0) {
        mapa[linha][coluna].tipo = 2;
        qtdPilulasRestantes++;
      }  
    }
  }
}
void exibeMapa(SDL_Renderer *renderer) {

  SDL_Rect tamanhoParede;
      tamanhoParede.h = tamanhoBlocos;
      tamanhoParede.w = tamanhoBlocos;
      tamanhoParede.x = 0;
      tamanhoParede.y = 0;

  for (int linha = 0; linha < tamanhoMapa; linha++) {
    for (int coluna = 0; coluna < tamanhoMapa; coluna++) {
            
      SDL_Rect textureRemedio;
      textureRemedio.w = tamanhoBlocos/2;
      textureRemedio.h = tamanhoBlocos/2;
      textureRemedio.x = mapa[linha][coluna].posX + textureRemedio.w/2;
      textureRemedio.y = mapa[linha][coluna].posY + textureRemedio.h/2;
     

      SDL_Rect textureParede;
      textureParede.x = mapa[linha][coluna].posX;
      textureParede.y = mapa[linha][coluna].posY;
      textureParede.w = mapa[linha][coluna].sizeX;
      textureParede.h = mapa[linha][coluna].sizeY;

      if (mapa[linha][coluna].tipo == 1) {        
        SDL_RenderCopy(renderer, parede, &tamanhoParede, &textureParede);
      } else if (mapa[linha][coluna].tipo == 2) {
        SDL_RenderCopy(renderer, remedio, NULL, &textureRemedio);
      } else if (mapa[linha][coluna].tipo == 4) {
        SDL_RenderCopy(renderer, alcool, NULL, &textureParede);
      }
    }
  }
}

void exibePacman(SDL_Renderer *renderer) {
    
    SDL_Rect textura;
    textura.h = 64;
    textura.w = 64;
    textura.x = 128;
    textura.y = 0;

    switch (direcaoPacman) {
    case 'u': 
      textura.x = 0;
      break;
    case 'd':
      textura.x = 64;
      break;
    case 'r':
      textura.x = 128;
      break;
    case 'l':
      textura.x = 192;
      break;
    }
  
    SDL_Rect bloco;
    bloco.x = tamanhoBlocos*pacman.posX;
    bloco.y = tamanhoBlocos*pacman.posY;
    bloco.w = tamanhoBlocos;
    bloco.h = tamanhoBlocos;
      
    SDL_RenderCopy(renderer, pacman.textura, &textura, &bloco);  
}

bool validaPosicao(int linha, int coluna) {
  if (mapa[linha][coluna].tipo == 1 || mapa[linha][coluna].tipo == 3) {
    return false;
  } else {
    return true;
  }
  
}

char verificaFimJogo() {
  // Verifica se todos os pontos já foram coletados
  if (qtdPilulasRestantes == 0) {
    // Winner
    return 'w';
  } else if (pacman.vidas <= 0) {
    // Lost
    return 'l';
  }
}

void movimentaPacman(char direcao) {
  
  if (quadroAtual-ultimoQuadroPacman >= velocidadePacman) {
    int novaLinhaPacman = pacman.posY;
    int novaColunaPacman = pacman.posX;

    switch (direcao) {
      case 'u':
        novaLinhaPacman--;
        break;
      case 'd':
        novaLinhaPacman++;
        break;
      case 'l':
        novaColunaPacman--;
        break;
      case 'r':
        novaColunaPacman++;
        break;
    }

    direcaoPacman = direcao;

    // Verifica se o Pacman saiu para fora do mapa e retorna ele ao outro extremo
    if (novaColunaPacman == -1) {
      novaColunaPacman = 20;
    } else if (novaColunaPacman == 21) {
      novaColunaPacman = 0;
    }
    
    if(validaPosicao(novaLinhaPacman, novaColunaPacman)) {
      pacman.posY = novaLinhaPacman;
      pacman.posX = novaColunaPacman;
      
      ultimoQuadroPacman = quadroAtual;
    }

    // Verifica se há algum ponto para ser coletado na nova posição    
    if (mapa[pacman.posY][pacman.posX].tipo == 2) {
      mapa[pacman.posY][pacman.posX].tipo = 0;
      qtdPilulasRestantes--;
      pacman.pontos++;
    } else if (mapa[pacman.posY][pacman.posX].tipo == 4 && pacman.poder == false) {
      mapa[pacman.posY][pacman.posX].tipo = 0;
      ultimoQuadroPoder = quadroAtual;
      pacman.poder = true;
      pacman.pontos = pacman.pontos + 5;
    }
  }
}

void criaFantasmas() {
  for (int i = 0; i < qtdFantasmas; i++) {
    fanstasmas[i].posX = i+8;
    fanstasmas[i].posY = 9;
    fanstasmas[i].textura = fantasmaTexture; 
  }
}

void criaPacman(SDL_Renderer *renderer) {
  pacman.textura = pacmanTexture;
}

void movimentaFantasma(SDL_Renderer *renderer) {
  quadroAtual++;
  
  if (quadroAtual-ultimoQuadroPoder >= duracaoPoder) {
    pacman.poder = false;
  }
  
  if (quadroAtual-ultimoQuadroFantasma >= velocidadeFantasma) {
      
      for (int fantasma = 0; fantasma < qtdFantasmas; fantasma++) {
        int linhaFantasma = fanstasmas[fantasma].posY;
        int colunaFantasma = fanstasmas[fantasma].posX;
        char direcaoFantasma = fanstasmas[fantasma].direcao;

        // Movimenta fantasmas para fora de suas casas SE o Pacman não tiver com o poder ativado
        if (mapa[linhaFantasma][colunaFantasma].tipo == 3 && pacman.poder == false) {
            if (colunaFantasma < 10) {
              colunaFantasma++;
            } else if (colunaFantasma > 10) {
              colunaFantasma--;
            } else {
              linhaFantasma--;
            }
        } else if (mapa[linhaFantasma][colunaFantasma].tipo != 3) {
          int linhaTmp, colunaTmp;
          linhaTmp = linhaFantasma;
          colunaTmp = colunaFantasma;
          
          // switch (fantasma) {
          //   case 0:
              switch (direcaoFantasma) {                
                case 'r':
                  colunaTmp++;
                  break;
                case 'l':
                  colunaTmp--;
                  break;
                case 'd':
                  linhaTmp++;
                  break;
                case 'u':
                  linhaTmp--;
                  break;
              }
              
              if (colunaTmp == -1) {
                colunaTmp = 20;
              } else if (colunaTmp == 21) {
                colunaTmp = 0;
              }
              
              while (!validaPosicao(linhaTmp, colunaTmp) || (linhaTmp == fanstasmas[fantasma].posAnteriorY && colunaTmp == fanstasmas[fantasma].posAnteriorX)) {
                linhaTmp = linhaFantasma;
                colunaTmp = colunaFantasma;
                int direcaoRand = rand() % 4;

                switch (direcaoRand) {
                  case 0:
                    colunaTmp++;
                    direcaoFantasma = 'r';
                    break;
                  case 1:
                    colunaTmp--;
                    direcaoFantasma = 'l';
                    break;
                  case 2:
                    linhaTmp++;
                    direcaoFantasma = 'd';
                    break;
                  case 3:
                    linhaTmp--;
                    direcaoFantasma = 'u';
                    break;
                }
              }          
                            
              linhaFantasma = linhaTmp;
              colunaFantasma = colunaTmp;
            // break;
          // }
        }
        
        fanstasmas[fantasma].direcao = direcaoFantasma;
        fanstasmas[fantasma].posAnteriorX = fanstasmas[fantasma].posX;
        fanstasmas[fantasma].posAnteriorY = fanstasmas[fantasma].posY;
        fanstasmas[fantasma].posX = colunaFantasma;
        fanstasmas[fantasma].posY = linhaFantasma;
        colisaoPacman(fantasma);
      }
      ultimoQuadroFantasma = quadroAtual;
  }
    
  // Primeiro pacman move-se aleatóriamente pelo mapa
      
}
void colisaoPacman(int idFantasma) {
  // Verifica se o Pacman e o Fanstasma estão ou passaram pelo mesmo bloco

  if ((fanstasmas[idFantasma].posX == pacman.posX && fanstasmas[idFantasma].posY == pacman.posY) || (fanstasmas[idFantasma].posAnteriorX == pacman.posX && fanstasmas[idFantasma].posAnteriorY == pacman.posY)) {
    // Verifica se o pacman tem poder
    if (pacman.poder) {
      srand(time(0));
      fanstasmas[idFantasma].posX = idFantasma+8;
      fanstasmas[idFantasma].posY = 9;
      pacman.pontos = pacman.pontos + 50;
    } else {
      pacman.vidas--;
      pacman.posX = 10;
      pacman.posY = 13;
    }
    
  }
  
}
void mostraFantasmas(SDL_Renderer *renderer) {
     
    SDL_Rect virus;
    virus.h = 54;
    virus.w = 54;   
    virus.y = 10;

    // Verifica se o Pacman tem poder para definir a cor do fantasma
    if (pacman.poder) {
      virus.x = 84;
    } else {
      virus.x = 10;
    } 

    SDL_Rect texture;
    texture.h = tamanhoBlocos;
    texture.w = tamanhoBlocos;
    for (int fantasma = 0; fantasma < qtdFantasmas; fantasma++) {
      texture.x = fanstasmas[fantasma].posX * tamanhoBlocos;
      texture.y = fanstasmas[fantasma].posY * tamanhoBlocos;

      SDL_Texture *textura =  fanstasmas[0].textura;
      SDL_RenderCopy(renderer, textura, &virus, &texture);
    }
    

}
void mostraPlacar(SDL_Renderer *renderer) {
  // Mostra as Vidas
  SDL_Rect texture;
  texture.h = tamanhoBlocos-5;
  texture.w = tamanhoBlocos-5;
  texture.y = 2.5;

  // Mostra os corações
  for (int i = 0; i < pacman.vidas; i++) {
    texture.x = tamanhoBlocos*tamanhoMapa-tamanhoBlocos-i*(tamanhoBlocos-5);
    SDL_RenderCopy(renderer, coracaoLogo, NULL, &texture);
  }

  // Mostra o texto Vidas
  texture.w = 100;
  texture.x = texture.x-100;
  SDL_RenderCopy(renderer, textoVidas, NULL, &texture);

  // Mostra o texto Pontos
  texture.x = 0;
  SDL_RenderCopy(renderer, textoPontos, NULL, &texture);

  int placar[4];
  placar[0] = pacman.pontos/1000;
  placar[1] = pacman.pontos%1000/100;
  placar[2] = pacman.pontos%100/10;
  placar[3] = pacman.pontos%10;
  
  texture.x = 100;
  texture.w = 22;

  SDL_Rect tamanho_numero;
  tamanho_numero.h = 22;
  tamanho_numero.w = 18;
  tamanho_numero.y = 0;
  tamanho_numero.x = 0;
  
  for (int i = 0; i < sizeof(placar)/sizeof(int); i++) {
    tamanho_numero.x = placar[i]*18;
    texture.x = 100 + i*21;
    SDL_RenderCopy(renderer, numeros, &tamanho_numero, &texture);
  } 
}