#ifndef __0910_library_pacman
#define __0910_library_pacman

    #include <iostream>
    #include "SDL2/SDL.h"
    #include <SDL2/SDL_ttf.h>
    #include <unistd.h>
    #include <list>

    using namespace std;

    SDL_Texture *carregaImagem(const char *imagem, SDL_Renderer *renderizador);

    const float tamanhoBlocos = 32;
    const int tamanhoMapa = 21;
    const int qtdFantasmas = 5;

    // Velocidade contada em quadros, quanto menos quadros, mais rápido
    const int velocidadeFantasma = 20, velocidadePacman = 5; 
    const int duracaoPoder = 800;

    struct Bloco {
        int sizeX = tamanhoBlocos, sizeY = tamanhoBlocos;
        int posX, posY;    
        int tipo = 0; // 1 = parede 2 = pontos 3 = area de risco 4 = Alcool
    };

    struct Fantasma {
        int posX, posY, posAnteriorX, posAnteriorY;
        char direcao = 'u';
        SDL_Texture *textura;
    };

    struct Pacman {
        int posX = 10, posY = 13;
        char direcao = 'r';
        int vidas = 3;
        bool poder = false;
        int pontos = 0;
        SDL_Texture *textura;
    };

    void criaMapa();
    void exibeMapa(SDL_Renderer *renderer);
    void exibePacman(SDL_Renderer *renderer);
    bool validaPosicao(int linha, int coluna);
    void criaCasaFantasma();
    void criaObstaculos();
    void distribuiAlcool(int quantidade);
    void distribuiPontos();
    char verificaFimJogo();
    void movimentaPacman(char direcao);
    void mostraFantasmas(SDL_Renderer *renderer);
    void criaFantasmas();
    void criaPacman(SDL_Renderer *renderer);
    void movimentaFantasma(SDL_Renderer *renderer);
    void colisaoPacman(int idFantasma);
    void carregaTexturas(SDL_Renderer *renderer);
    void mostraPlacar(SDL_Renderer *renderer);
#endif