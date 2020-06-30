#include "lib/libraries.h"



int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_EVERYTHING);

  int tamanhoTela = 672;
  SDL_Window *screen = SDL_CreateWindow("Pacman COVID-19", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, tamanhoTela, tamanhoTela, SDL_WINDOW_OPENGL);     
  SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

  SDL_Texture *mensagemFinal;

  ///Gameloop
  bool running = true;

  criaMapa();
  carregaTexturas(renderer);
  criaPacman(renderer);
  criaFantasmas();

  while(running) {
    SDL_RenderClear(renderer);

    ///Logica
    // movimentaFantasma();
    //Detecção de Evento
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
      switch(event.type)  {
        case SDL_KEYDOWN:       
          switch (event.key.keysym.sym) {
            case SDLK_UP:
              movimentaPacman('u');       
              break;
            case SDLK_DOWN:
              movimentaPacman('d');          
              break;
            case SDLK_LEFT:
              movimentaPacman('l');             
              break;
            case SDLK_RIGHT:
              movimentaPacman('r');
            break;
          }
          break;
        case SDL_QUIT: //Caso saia
          running = false;
        break;
      }
    }

    //Atualizações gerais devem vir aqui
    exibeMapa(renderer);
    movimentaFantasma(renderer);
    mostraFantasmas(renderer);
    exibePacman(renderer);
    mostraPlacar(renderer);

    ///Rendering vai vir aqui
    SDL_RenderPresent(renderer);

    if (verificaFimJogo() == 'w') {
      mensagemFinal = carregaImagem("assets/win.bmp", renderer);
      running = false;
    } else if (verificaFimJogo() == 'l') {
      mensagemFinal = carregaImagem("assets/lost.bmp", renderer);
      running = false;
    }
    SDL_Delay(10); //Isso causa algo como 60 quadros por segundo.
  }
  
  SDL_Rect tamanhoMensagemFinal;
  tamanhoMensagemFinal.x = 0;
  tamanhoMensagemFinal.h = 0;
  tamanhoMensagemFinal.w = 0;

  SDL_QueryTexture(mensagemFinal, nullptr, nullptr, &tamanhoMensagemFinal.w, &tamanhoMensagemFinal.h);

  tamanhoMensagemFinal.y = (tamanhoTela-tamanhoMensagemFinal.h)/2;
  tamanhoMensagemFinal.x = (tamanhoTela-tamanhoMensagemFinal.w)/2;

  SDL_RenderCopy(renderer, mensagemFinal, NULL, &tamanhoMensagemFinal);
  SDL_RenderPresent(renderer);

  SDL_Delay(10000);
  
  SDL_DestroyWindow(screen);
  SDL_Quit();

  return 0;
}