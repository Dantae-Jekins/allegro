#ifndef VARIABLES
#define VARIABLES

// variáveis gerais
#define height 720
#define width 1080
#define tileSiz 50
#define gravidade 2
#define fps 60.0

// constantes de posições do chat
// útil para pre-processamento
#define comment_x0 (width / 10 + 120)
#define comment_y0 (height - 180)
#define comment_x1 (width - (width / 10 + 120))
#define comment_y1 (height - 60)

// constantes de tamanho das box
#define typ0x 20
#define typ0y 20

#define typ1x 20
#define typ1y 40

#define typ2x 20
#define typ2y 40

#define typ3x 30
#define typ3y 40

#define typ4x 250
#define typ4y 150

#define typ5x 100
#define typ5y 10

#define typ9x 150
#define typ9y 75

#define speed 5

// variáveis de tamanho do jogador
#define ply_x 25
#define ply_y 40

#define AZULBOLD al_map_rgb(80, 80, 160)
#define AZULLITE al_map_rgba(80, 80, 160, 80)

#define CIANBOLD al_map_rgb(120, 200, 240)
#define CIANLITE al_map_rgba(120, 200, 240, 80)

#define BRANCO al_map_rgb(255, 255, 255)

// Bitmap

bool seta;
int tile;
int back;
int obst;

#define bitmap_count 30
ALLEGRO_BITMAP *bitmap[bitmap_count]; // Vetor de ponteiros para bitmaps, cada elemento desse vetor é um ponteiro
                          // Não da pra saber o tamanho do bitmap, por isso cria um ponteiro
#define font_count 2
ALLEGRO_FONT *FONTES[font_count];

ALLEGRO_DISPLAY *display;

#endif