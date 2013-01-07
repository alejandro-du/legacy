// Editor de mapas V.2.0 (APOCALIPSIS)
// DPA SOFTWARE.
// Programador: Jairo Alejandro Duarte Avenda¤o.
// Fecha de inicio de edici¢n: 9 de Diciembre de 1999.
// Terminado: 2000.

#include <stdio.h>
#include <string.h>
#include "allegro.h"

#define ERR_ARCHIVO 2
#define ERR_MEMORIA 3
#define ERR_MOUSE   4
#define ERR_VIDEO   5


#define TB_PARED
#define TB_PARED_A
#define TB_SUELO
#define TB_SUELO_A
#define TB_TRAMPA



#define MOUSE_X (mouse_x - mouse->w/2)
#define MOUSE_Y (mouse_y - mouse->h/2)

void rut_err(char cod, char mensaje[80]);
void pintar_mapa(BITMAP *buffer);
void cargar_blk(void);
void abrir(char blk, char map, char pal);
void cargar_map(void);
void cargar_pal(void);
void pintar_mapa_bloques(BITMAP *buffer);
int obtener_blk(int x, int y);
int obtener_pos(int x, int y);
void ayuda(void);
void ir(void);
void rellenar(int bl);
void ajustar(void);
void guardar(void);
void guardar_como(void);
void cambiar_blk(int bl);
void cambiar_ids(void);
void guardar_blk(void);
void cambiar_color(void);
void cambiar_color_rejilla(void);
void info(void);
void ajustar_presentacion(void);


typedef unsigned char BYTE;

typedef struct MAPA { // estructura para el manejo de los mapas
  int x, y; // posici¢n de inicio de dibujado del mapa
  int ancho, alto; // tama¤o del mapa
  int *mapa; // memoria usada para guardar el mapa
  int bl_v, bl_h; // n£mero de bloques que se deben dibujar en pantalla
  int bl_max; // n£mero de bloques usados
  int bl_ancho, bl_alto; // tama¤o de cada bloque
  unsigned char *blk_a; // atributos de cada bloque
  BITMAP **blk; // array de punteros a bitmaps con los bloques
} MAPA;


MAPA mapa;
PALLETE paleta;

int pos_mapa_blk, // posici¢n del mapa de bloques
    sel; // bloque seleccionado
char modificado = ' ';
BYTE color, color_rejilla;
char ids[17]; // cadena de identificaci¢n definida por el usuario
char mapa_bloques; // BOOL
char rejilla; // BOOL

char ARCHIVO_BLK[80];
char ARCHIVO_MAP[80];
char ARCHIVO_PAL[80];

main(void)
{
  BITMAP *mouse, *buffer;
  long int cont,
           pos;
  int mouse_blk, // bloque que est  debajo del mouse
      off,
      x, y;
  char barra_estado; // BOOL
  allegro_init();
  install_timer();
  install_mouse();
  install_keyboard();
  text_mode(-1); // transparente

  if(set_gfx_mode(GFX_VESA1, 640, 480, 0, 0) != 0) { // inicializar modo gr fico VGA
    rut_err(ERR_VIDEO, "640 * 480 * 256");
  }
  mouse = load_pcx("mouse.pcx", (RGB*)paleta);
  if(!mouse) rut_err(ERR_ARCHIVO, "MOUSE.PCX");

  buffer = create_bitmap(SCREEN_W, SCREEN_H);
  clear(buffer);
  clear_keybuf();

  // iniclializar variables
  mapa.x = 0;
  mapa.y = 0;
  mapa.ancho = 100;
  mapa.alto = 100;
  mapa.bl_max = 50;
  mapa.bl_ancho = 32;
  mapa.bl_alto = 32;
  mapa.bl_h = SCREEN_W / mapa.bl_ancho;
  mapa.bl_v = SCREEN_H / mapa.bl_alto;
  mapa_bloques = 1; // mostrar mapa de bloques
  barra_estado = 1;
  rejilla = 0; // no mostrar rejilla
  pos_mapa_blk = 0;
  sel = 0;
  color = 25;
  color_rejilla = 0;
  strcpy(ids, "DPA SOFTWARE    ");
  strcpy(ARCHIVO_BLK, "em.blk");
  strcpy(ARCHIVO_MAP, "em.map");
  strcpy(ARCHIVO_PAL, "em.pal");

  // preparar memoria
  mapa.mapa = (int*)malloc((mapa.ancho)*(mapa.alto)*sizeof(int));
  if(!mapa.mapa) rut_err(ERR_MEMORIA, "para cargar el mapa");
  for(cont = 0; cont < (mapa.ancho)*(mapa.alto); cont++) mapa.mapa[cont] = 0;

  mapa.blk = (BITMAP**)calloc(mapa.bl_max, sizeof(BITMAP));
  mapa.blk_a = (unsigned char*)malloc(mapa.bl_max);

  for(cont = 0; cont < mapa.bl_max; cont++) {
    mapa.blk[cont] = create_bitmap(mapa.bl_ancho, mapa.bl_alto);
    clear(mapa.blk[cont]);
  }
  for(cont = 0; cont < mapa.bl_max; cont++) mapa.blk_a[cont] = 0;


  // bucle principal
  for(;!key[KEY_ESC];) {
    // obtener accion del usuario
    if(key[KEY_SPACE]) {
      mapa_bloques = !mapa_bloques;
      clear_keybuf();
    }
    else if(key[KEY_TAB]) {
      barra_estado = !barra_estado;
      clear_keybuf();
    }
    else if(key[KEY_F1]) ayuda();
    else if(key[KEY_F2]) guardar();
    else if(key[KEY_F4]) guardar_como();
    else if(key[KEY_F5]) abrir(TRUE, FALSE, FALSE); // BLK
    else if(key[KEY_F6]) abrir(FALSE, TRUE, FALSE); // MAP
    else if(key[KEY_F7]) abrir(FALSE, FALSE, TRUE); // PAL
    else if(key[KEY_F8]) abrir(TRUE, TRUE, TRUE); // todos
    else if(key[KEY_F11]) {
      rejilla = !rejilla;
      clear_keybuf();
    }
    else if(key[KEY_F12]) {
      set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
      clrscr();
      clear_keybuf();
      remove_keyboard();
      printf("\n %s", ids);
      printf("\n DPA Software\n");
      rest(66);
      clrscr();
      if(set_gfx_mode(GFX_VESA1, 640, 400, 0, 0) != 0) // inicializar modo gr fico VGA
        rut_err(ERR_VIDEO, "640 * 480 * 256");
      set_pallete((RGB*)paleta);
      install_keyboard();
      clear_keybuf();
    }
    else if(key[KEY_CONTROL] && key[KEY_C]) cambiar_color();
    else if(key[KEY_CONTROL] && key[KEY_G]) cambiar_color_rejilla();
    else if(key[KEY_CONTROL] && key[KEY_B]) guardar_blk();
    else if(key[KEY_CONTROL] && key[KEY_R]) cargar_map();
    else if(key[KEY_CONTROL] && key[KEY_I]) ir();
    else if(key[KEY_CONTROL] && key[KEY_D]) ajustar();
    else if(key[KEY_CONTROL] && key[KEY_P]) ajustar_presentacion();
    else if(key[KEY_CONTROL] && key[KEY_S]) cambiar_ids();
    else if(key[KEY_CONTROL] && key[KEY_E]) info();
    else if(key[KEY_CONTROL] && key[KEY_LSHIFT] && key[KEY_F9] && key[KEY_F10]) {
      strcpy(ARCHIVO_BLK, "piedra.blk");
      strcpy(ARCHIVO_MAP, "m1.map");
      strcpy(ARCHIVO_PAL, "pal1.pal");
      cargar_blk();
      cargar_map();
      cargar_pal();
    }

    else if(key[KEY_CONTROL] && key[KEY_L] && mouse_blk != -1) rellenar(sel);
    else if((key[KEY_RSHIFT] || (mouse_b & 2)) && mouse_blk != -1) {
      sel = mouse_blk;
      if(sel < pos_mapa_blk) pos_mapa_blk = sel;
      if(sel >= pos_mapa_blk + SCREEN_W/mapa.bl_ancho) pos_mapa_blk = sel - SCREEN_W/mapa.bl_ancho + 1;
    }
    else if(key[KEY_ENTER] || (mouse_b & 1) && mouse_blk != -1) {
      mapa.mapa[pos] = sel;
      modificado = '*';
    }
/*    else if(key[KEY_ALT] && key[KEY_1]) {
      mapa.blk_a[sel] ^= 1;
      clear_keybuf();
    }
    else if(key[KEY_ALT] && key[KEY_2]) {
      mapa.blk_a[sel] ^= 2;
      clear_keybuf();
    }*/
    else if(key[KEY_ALT] && key[KEY_1]) {
      mapa.blk_a[sel] ^= 1;
      clear_keybuf();
    }
    else if(key[KEY_ALT] && key[KEY_2]) {
      mapa.blk_a[sel] ^= 2;
      clear_keybuf();
    }
    else if(key[KEY_ALT] && key[KEY_3]) {
      mapa.blk_a[sel] ^= 4;
      clear_keybuf();
    }
    else if(key[KEY_ALT] && key[KEY_4]) {
      mapa.blk_a[sel] ^= 8;
      clear_keybuf();
    }
    else if(key[KEY_ALT] && key[KEY_5]) {
      mapa.blk_a[sel] ^= 16;
      clear_keybuf();
    }
    else if(key[KEY_ALT] && key[KEY_6]) {
      mapa.blk_a[sel] ^= 32;
      clear_keybuf();
    }
    else if(key[KEY_ALT] && key[KEY_7]) {
      mapa.blk_a[sel] ^= 64;
      clear_keybuf();
    }
    else if(key[KEY_ALT] && key[KEY_8]) {
      mapa.blk_a[sel] ^= 128;
      clear_keybuf();
    }

    // scroll de pantalla
    else if(key[KEY_UP]) {
      mapa.y -= mapa.bl_v;
      clear_keybuf();
    }
    else if(key[KEY_DOWN]) {
      mapa.y += mapa.bl_v;
      clear_keybuf();
    }
    else if(key[KEY_LEFT]) {
      mapa.x -= mapa.bl_h;
      clear_keybuf();
    }
    else if(key[KEY_RIGHT]) {
      mapa.x += mapa.bl_h;
      clear_keybuf();
    }

    // scroll de bloque
    if(key[KEY_LSHIFT] && mouse_x > (mapa.bl_ancho * mapa.bl_h) - 10) mapa.x++;
    else if(key[KEY_LSHIFT] && mouse_x < 10) mapa.x--;
    if(key[KEY_LSHIFT] && mouse_y > (mapa.bl_alto * mapa.bl_v) - 10) mapa.y++;
    else if(key[KEY_LSHIFT] && mouse_y < 10) mapa.y--;

    if(mapa.y < 0) mapa.y = 0;
    else if(mapa.y > (mapa.alto - mapa.bl_v)) mapa.y = mapa.alto - mapa.bl_v ;
    if(mapa.x < 0) mapa.x = 0;
    else if(mapa.x > (mapa.ancho - mapa.bl_h)) mapa.x = mapa.ancho - mapa.bl_h;

    if(mouse_x > mapa.bl_ancho * mapa.bl_h || mouse_y > mapa.bl_alto * mapa.bl_v) {
      pos = -1;
      mouse_blk = -1;
      off = -1;
      x = y = -1;
    }
    else {
      pos = obtener_pos(mouse_x, mouse_y);
      mouse_blk = mapa.mapa[pos];
      off = (mouse_y/mapa.bl_ancho)+((mouse_x/mapa.bl_ancho)*mapa.bl_v);
      x = mouse_x / mapa.bl_ancho + mapa.x;
      y = mouse_y / mapa.bl_alto + mapa.y;
    }

    pintar_mapa(buffer);

    if(mapa_bloques) { // presentar mapa de bloques e informaci¢n
      rectfill(buffer, 0, SCREEN_H - (mapa.bl_alto * 2) - 15, SCREEN_W, SCREEN_H, 0);
      rect(buffer, SCREEN_W-(mapa.bl_ancho*2)-11, SCREEN_H - (mapa.bl_alto*2)-4, SCREEN_W-mapa.bl_ancho-10, SCREEN_H - mapa.bl_alto-3, color);
      rect(buffer, SCREEN_W-(mapa.bl_ancho)-2, SCREEN_H - (mapa.bl_alto*2)-4, SCREEN_W-1, SCREEN_H - mapa.bl_alto-3, color);
      pintar_mapa_bloques(buffer);
      rect(buffer, (sel-pos_mapa_blk)*(mapa.bl_ancho), SCREEN_H - mapa.bl_alto, (sel-pos_mapa_blk)*(mapa.bl_ancho) + mapa.bl_ancho, SCREEN_H -1, color);
      if(mouse_y >= SCREEN_H - (mapa.bl_alto * 2) - 15) { // si esta en el cuadro
        // fuera de rango del mapa
        pos = -1;
        mouse_blk = -1;
        off = -1;
        x = y = -1;
        if(mouse_y >= SCREEN_H - mapa. bl_alto) { // si el mouse esta en el mapa de bloques
          // obtener el bloque que est  debajo del mouse
          mouse_blk = ((mouse_x / mapa.bl_ancho) + pos_mapa_blk);
          if(key[KEY_CONTROL] && (mouse_b & 1)) cambiar_blk(mouse_blk);
          if(!key[KEY_LSHIFT]) { // si no esta haciendo scroll
            if(mouse_x > 635) {
              if(key[KEY_CONTROL]) pos_mapa_blk+=4; // avanzar r pidamente
              pos_mapa_blk++;
            }
            else if(mouse_x < 5) {
              if(key[KEY_CONTROL]) pos_mapa_blk-=3;
              pos_mapa_blk--;
            }
          }
        }
      }
      textprintf(buffer, font, 0, SCREEN_H-mapa.bl_ancho*2 - 14, color, "[%c] X%d Y%d (X%d Y%d) BLK %d SEL %d H%d V%d POS %d OFF %d", modificado, x, y, mouse_x, mouse_y, mouse_blk, sel, mapa.ancho, mapa.alto, pos, off);
//      textprintf(buffer, font, 0, SCREEN_H-mapa.bl_ancho - 11, color, "IDS: \"%s\"  ATR %d %d %d", ids, ((mapa.blk_a[sel] & 1)?1:0), ((mapa.blk_a[sel] & 2)?1:0), mapa.blk_a[sel]);
      textprintf(buffer, font, 0, SCREEN_H-mapa.bl_ancho - 11, color, "IDS: \"%s\"  ATR %d %d %d %d %d %d %d %d", ids,
                                                                                                                  ((mapa.blk_a[sel] & 1)?1:0),
                                                                                                                  ((mapa.blk_a[sel] & 2)?1:0),
                                                                                                                  ((mapa.blk_a[sel] & 4)?1:0),
                                                                                                                  ((mapa.blk_a[sel] & 8)?1:0),
                                                                                                                  ((mapa.blk_a[sel] & 16)?1:0),
                                                                                                                  ((mapa.blk_a[sel] & 32)?1:0),
                                                                                                                  ((mapa.blk_a[sel] & 64)?1:0),
                                                                                                                  ((mapa.blk_a[sel] & 128)?1:0));

      if(mouse_blk != -1) draw_sprite(buffer, mapa.blk[mouse_blk], SCREEN_W-(mapa.bl_ancho*2)-10, SCREEN_H - (mapa.bl_alto*2)-3);
      draw_sprite(buffer, mapa.blk[sel], SCREEN_W-(mapa.bl_ancho)-1, SCREEN_H - (mapa.bl_alto*2)-3);
    }
    else if(barra_estado) textprintf(buffer, font, 0, SCREEN_H-8, color, "[%c] X%d Y%d (X%d Y%d) BLK %d SEL %d H%d V%d POS %d OFF %d", modificado, x, y, mouse_x, mouse_y, mouse_blk, sel, mapa.ancho, mapa.alto, pos, off);
    draw_sprite(buffer, mouse, MOUSE_X, MOUSE_Y); // pintar puntero del mouse
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); // volcado
    clear(buffer);
  }

  free(mapa.mapa);
  cfree(mapa.blk);
  remove_keyboard();
  remove_mouse();
  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0); // volver al modo de texto
  allegro_exit();

  printf("\nDPA SOFTWARE 1999.\nAutor: Jairo Alejandro Duarte Avenda¤o.\njaal81@yahoo.com\n");

  return(0);
}



void pintar_mapa(BITMAP *buffer)
{
  int x, y, num = 0;

  num += mapa.alto * mapa.x + mapa.y; // avanzar a la posicion actual
  // pintar el mapa
  for(x = 0; x < mapa.bl_h; x++) {
    for(y = 0; y < mapa.bl_v; y++) {
      blit(mapa.blk[mapa.mapa[num]], buffer, 0, 0, (x * mapa.bl_ancho), (y * mapa.bl_alto), mapa.bl_ancho, mapa.bl_alto);
      if(rejilla) rect(buffer, x * mapa.bl_ancho, y * mapa.bl_alto, (x * mapa.bl_ancho) + mapa.bl_ancho, (y * mapa.bl_alto)+mapa.bl_alto, color_rejilla);
      num++;
    }
    num += mapa.alto - mapa.bl_v;
  }
}



void pintar_mapa_bloques(BITMAP *buffer)
{
  int x;
  if(pos_mapa_blk < 0) pos_mapa_blk = 0;
  if(pos_mapa_blk > mapa.bl_max - SCREEN_W/mapa.bl_ancho) pos_mapa_blk = mapa.bl_max - SCREEN_W/mapa.bl_ancho;
  for(x = pos_mapa_blk; x < pos_mapa_blk + SCREEN_W/mapa.bl_ancho; x++) {
    blit(mapa.blk[x], buffer, 0, 0, ((x-pos_mapa_blk) * mapa.bl_ancho), SCREEN_H-mapa.bl_alto, mapa.bl_ancho, mapa.bl_alto);
  }
}




int obtener_blk(int x, int y)
{
  int x_s, y_s, num = 0;

  x_s = (x / mapa.bl_ancho);
  y_s = (y / mapa.bl_alto);

  num += (mapa.alto) * (mapa.x) + (mapa.y); /* punto inicial en pantalla */

  return *mapa.mapa + num;
}



void rellenar(int bl)
{
  long int x, y, num = 0;
  int max_y = 0;

  if(mapa_bloques) max_y = (mapa.bl_alto*3+15)/mapa.bl_alto;

  num += mapa.alto * mapa.x + mapa.y; // avanzar a la posicion actual
  for(x = 0; x < mapa.bl_h; x++) {
    for(y = 0; y < mapa.bl_v - max_y; y++) {
      mapa.mapa[num] = sel;
      num++;
    }
    num += mapa.alto - mapa.bl_v + max_y;
  }
  modificado = '*';
}




void ir(void)
{
  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
  clear_keybuf();
  remove_keyboard();
  clrscr();

  printf("\n Posici¢n actual: %d, %d\n\n", mapa.x, mapa.y);

  printf("X: ");
  scanf("%d", &mapa.x);
  printf("Y: ");
  scanf("%d", &mapa.y);

  if(set_gfx_mode(GFX_VESA1, 640, 480, 0, 0) != 0) { // inicializar modo gr fico VGA
    rut_err(ERR_VIDEO, "640 * 480 * 256");
  }
  set_pallete(paleta);
  install_keyboard();
}



int obtener_pos(int x, int y)
{
  int x_s, y_s, num = 0;

  x_s = (x / mapa.bl_ancho);
  y_s = (y / mapa.bl_alto);

  num += (mapa.alto) * (mapa.x) + (mapa.y); /* punto inicial en pantalla */
  num += (mapa.alto) * x_s + y_s; /* desplazamiento */

  return num;
}




void ajustar(void)
{
  long int cont, num;
  int *temp;
  int an, al, x, y, inc;

  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
  clrscr();
  clear_keybuf();
  remove_keyboard();

  an = mapa.ancho;
  al = mapa.alto;

  // reservar la memoria necesaria para el mapa temporal
  temp = (int*)malloc((long)(mapa.ancho) * (mapa.alto)*sizeof(int));
  if(temp == NULL) rut_err(ERR_MEMORIA, "para cargar el mapa temporal");

  for(cont = 0; cont < (mapa.ancho) * (mapa.alto); cont++) temp[cont] = mapa.mapa[cont];

  printf("\n Tama¤o actual: H=%d V=%d\n", mapa.ancho, mapa.alto);
  printf("\n N£mero de bloques horizontales = ");
  scanf("%d", &mapa.ancho);
  printf("\n N£mero de bloques verticales = ");
  scanf("%d", &mapa.alto);

  if(mapa.ancho < mapa.bl_h) {
    mapa.ancho = mapa.bl_h;
  }
  if(mapa.alto < mapa.bl_v) {
    mapa.alto = mapa.bl_v;
  }

  //reservar la memoria necesaria para el nuevo mapa
  free(mapa.mapa);
  mapa.mapa = (int*)malloc((mapa.ancho)*(mapa.alto)*sizeof(int));
  if(!mapa.mapa) rut_err(ERR_MEMORIA, "para crear el nuevo mapa");

  for(cont = 0; cont < (mapa.ancho)*(mapa.alto); cont++) mapa.mapa[cont] = sel;

  if(mapa.ancho < an) { // reducir mapa
    an = mapa.ancho;
  }
  if(mapa.alto < al) {
    inc = al - mapa.alto;
    al = mapa.alto;
  }
  else inc = 0;

  cont = 0;
  num = 0;
  for(x = 0; x < an; x++) {
    for(y = 0; y < al; y++) {
      mapa.mapa[num] = temp[cont];
      cont++;
      num++;
    }
    cont+= inc;
    num += mapa.alto - al;
  }

  free(temp);

  if(set_gfx_mode(GFX_VESA1, 640, 480, 0, 0) != 0) { // inicializar modo gr fico VGA
    rut_err(ERR_VIDEO, "640 * 480 * 256");
  }
  install_keyboard();
  set_pallete(paleta);
  modificado = '*';
}




void ajustar_presentacion(void)
{
  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
  clrscr();
  clear_keybuf();
  clear_keybuf();
  remove_keyboard();

  printf("\nTama¤o actual: %d*%d", mapa.bl_h, mapa.bl_v);
  printf("\nBloques horizontales: ");
  scanf("%d", &mapa.bl_h);
  printf("\nBloques verticales: ");
  scanf("%d", &mapa.bl_v);

  if(mapa.bl_h > 640/mapa.bl_ancho) mapa.bl_h = 640/mapa.bl_ancho;
  if(mapa.bl_v > 480/mapa.bl_alto) mapa.bl_v = 480/mapa.bl_alto;
  if(mapa.bl_h < 1) mapa.bl_h = 1;
  if(mapa.bl_v < 1) mapa.bl_v = 1;

  if(set_gfx_mode(GFX_VESA1, 640, 480, 0, 0) != 0) { // inicializar modo gr fico VGA
    rut_err(ERR_VIDEO, "640 * 480 * 256");
  }
  install_keyboard();
  set_pallete((RGB*)paleta);
}





void cambiar_blk(int bl)
{
  long int num;
  BITMAP *temp;

  temp = create_bitmap(mapa.bl_ancho, mapa.bl_alto);
  clear(temp);

  draw_sprite(temp, mapa.blk[sel], 0, 0);
  clear(mapa.blk[sel]);
  draw_sprite(mapa.blk[sel], mapa.blk[bl], 0, 0);
  clear(mapa.blk[bl]);
  draw_sprite(mapa.blk[bl], temp, 0, 0);

  // verificar en el mapa para hacer la correcci¢n
  for(num = 0; num < (mapa.ancho * mapa.alto); num++) {
    if(mapa.mapa[num] == sel) mapa.mapa[num] = bl;
    else if(mapa.mapa[num] == bl) mapa.mapa[num] = sel;
  }
  modificado = '*';
}





void cargar_blk(void) // carga el archivo BLK
{
  FILE *archivo;
  int num; // bloque actual
  char DPABLK[6], version;
  BYTE x, y;

  if((archivo = fopen(ARCHIVO_BLK, "rb")) == NULL) // abrir el archivo en modo binario
    return; // volver si hay error

  // leer cabecera BLK
  if(fread(DPABLK, 1, 6, archivo) != 6)
    rut_err(ERR_ARCHIVO, ARCHIVO_BLK);
  DPABLK[6] = NULL;
  ids[16] = NULL;
  if(strcmp(DPABLK, "DPABLK") != 0) rut_err(ERR_ARCHIVO, ".\nCabecera BLK incorrecta");
  if(fread(&version, 1, 1, archivo) != 1) // versi¢n
    rut_err(ERR_ARCHIVO, ARCHIVO_BLK);
  if(fread(ids, 16, 1, archivo) != 1) // ids
    rut_err(ERR_ARCHIVO, ARCHIVO_BLK);
  if(fread(&mapa.bl_max, 2, 1, archivo) != 1) // n£mero de bloques
    rut_err(ERR_ARCHIVO, ARCHIVO_BLK);
  if(fread(&mapa.bl_ancho, 2, 1, archivo) != 1) // ancho de bloque
    rut_err(ERR_ARCHIVO, ARCHIVO_BLK);
  if(fread(&mapa.bl_alto, 2, 1, archivo) != 1) // alto de bloque
    rut_err(ERR_ARCHIVO, ARCHIVO_BLK);

  // preparar memoria
  cfree(mapa.blk);
  free(mapa.blk_a);
  mapa.blk = (BITMAP**)calloc(mapa.bl_max, sizeof(BITMAP));
  mapa.blk_a = (unsigned char*)malloc(mapa.bl_max);
  if(!mapa.blk) rut_err(ERR_MEMORIA, "para cargar el archivo BLK");
  for(num = 0; num < mapa.bl_max; num++)
    mapa.blk[num] = create_bitmap(mapa.bl_ancho, mapa.bl_alto);

  // cargar los bloques
  x = 0; y = 0;
  for(num = 0; num < mapa.bl_max;) {
    mapa.blk[num]->line[y][x] = getc(archivo); // leer byte
    if(ferror(archivo)) rut_err(ERR_ARCHIVO, ARCHIVO_BLK);
    x++;
    if(x >= mapa.bl_ancho) {
      x = 0;
      y++;
    }
    if(y >= mapa.bl_alto) {
      num++;
      y = 0;
    }
  }
  for(num = 0; num < mapa.bl_max; num++) {
    mapa.blk_a[num] = getc(archivo); // byte de atributo
    if(ferror(archivo)) rut_err(ERR_ARCHIVO, ARCHIVO_BLK);
  }
  fclose(archivo);
  mapa.bl_h = 640 / mapa.bl_ancho;
  mapa.bl_v = 480 / mapa.bl_alto;
}




void cargar_map(void)
{
  FILE *archivo; // manejador del archivo
  long int contador;
  char DPAMAP[7], version;

  // abrir el archivo
  if((archivo = fopen(ARCHIVO_MAP, "rb")) == NULL) return;

  // leer la cabecera
  if(fread(DPAMAP, 1, 6, archivo) != 6)
    rut_err(ERR_ARCHIVO, ARCHIVO_MAP);
  DPAMAP[6] = NULL;
  if(strcmp(DPAMAP, "DPAMAP") != 0) rut_err(ERR_ARCHIVO, ".\nCabecera MAP incorrecta");
  if(fread(&version, 1, 1, archivo) != 1) // versi¢n
  ids[16] = NULL;
  if(fread(ids, 16, 1, archivo) != 1) // ids
    rut_err(ERR_ARCHIVO, ARCHIVO_MAP);
  if(fread(&mapa.ancho, 2, 1, archivo) != 1) // ancho
    rut_err(ERR_ARCHIVO, ARCHIVO_MAP);
  if(fread(&mapa.alto, 2, 1, archivo) != 1) // alto del mapa
    rut_err(ERR_ARCHIVO, ARCHIVO_MAP);
  //reservar la memoria necesaria
  free(mapa.mapa);
  mapa.mapa = (int*)malloc((mapa.ancho)*(mapa.alto)*sizeof(int));
  if(!mapa.mapa) rut_err(ERR_MEMORIA, "para cargar el mapa");
//  for(cont = 0; cont < (mapa.ancho)*(mapa.alto); cont++) mapa.mapa[cont] = 0;


  // cargar el mapa
  for(contador = 0; contador < (mapa.ancho * mapa.alto); contador++) {
    if(fread(&mapa.mapa[contador], 4, 1, archivo) != 1) // leer de a cuatro bytes (int)
      rut_err(ERR_ARCHIVO, ARCHIVO_MAP);
    if(mapa.mapa[contador] > (mapa.bl_max)) rut_err(33, "Mapa con valores blk muy altos");
  }
  fclose(archivo);
  mapa.x = 0;
  mapa.y = 0;
  modificado = ' ';
}



void cargar_pal(void)
{
  FILE *archivo;
  int contador;

  if((archivo = fopen(ARCHIVO_PAL, "rb")) == NULL) return;

  for(contador = 0; contador < 256; contador++) {
    paleta[contador].r = getc(archivo);
    paleta[contador].g = getc(archivo);
    paleta[contador].b = getc(archivo);
    if(ferror(archivo)) rut_err(ERR_ARCHIVO, ARCHIVO_PAL);
  }
  set_pallete((RGB*)paleta);
}



void abrir(char blk, char map, char pal)
{
  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
  clrscr();
  clear_keybuf();
  remove_keyboard();


  printf("\n Archivos en uso:");
  printf(" BLK: %s\n MAP: %s\n PAL: %s\n", ARCHIVO_BLK, ARCHIVO_MAP, ARCHIVO_PAL);

  if(blk) {
    printf("\n Archivo BLK: ");
    scanf("%s", ARCHIVO_BLK);
    cargar_blk();
  }
  if(map) {
    printf("\n Archivo MAP: ");
    scanf("%s", ARCHIVO_MAP);
    cargar_map();
  }
  if(pal) {
    printf("\n Archivo PAL: ");
    scanf("%s", ARCHIVO_PAL);
    cargar_pal();
  }
  if(set_gfx_mode(GFX_VESA1, 640, 480, 0, 0) != 0) { // inicializar modo gr fico VGA
    rut_err(ERR_VIDEO, "640 * 480 * 256");
  }
  set_pallete((RGB*)paleta);
  install_keyboard();
}



void guardar(void)
{
  FILE *archivo; // manejador del archivo
  long int cont;

  // abrir el archivo
  if((archivo = fopen(ARCHIVO_MAP, "wb")) == NULL)
    rut_err(ERR_ARCHIVO, ARCHIVO_MAP);

  // escribir cabecera
  fprintf(archivo, "DPAMAP"); // ID
  fprintf(archivo, "%c", 1); // Versi¢n
  fwrite(&ids, 16, 1, archivo); // IDS
  fwrite(&mapa.ancho, 2, 1, archivo);
  fwrite(&mapa.alto, 2, 1, archivo);

  for(cont = 0; cont < (mapa.ancho) * (mapa.alto); cont++) {
    if(fwrite(mapa.mapa+cont, 4, 1, archivo) != 1)
      rut_err(ERR_ARCHIVO, ARCHIVO_MAP);
  }
  fclose(archivo);
  modificado = ' ';
}




void guardar_como(void)
{
  FILE *archivo; // manejador del archivo
  long int cont;

  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
  clrscr();
  clear_keybuf();
  remove_keyboard();

  printf("\n Archivo MAP: ");
  scanf("%s", ARCHIVO_MAP);
  guardar();

  if(set_gfx_mode(GFX_VESA1, 640, 480, 0, 0) != 0) { // inicializar modo gr fico VGA
    rut_err(ERR_VIDEO, "640 * 480 * 256");
  }
  install_keyboard();
  set_pallete((RGB*)paleta);
}



void cambiar_ids(void)
{
  int cont;

  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
  clrscr();
  clear_keybuf();
  remove_keyboard();

  for(cont = 0; cont < 17; cont++) ids[cont] = ' ';
  printf("\nIDS (max. 16 caracteres): ");
  scanf("%s", ids);
  ids[strlen(ids)] = ' ';

  if(set_gfx_mode(GFX_VESA1, 640, 480, 0, 0) != 0) { // inicializar modo gr fico VGA
    rut_err(ERR_VIDEO, "640 * 480 * 256");
  }
  install_keyboard();
  set_pallete((RGB*)paleta);
}



void cambiar_color(void)
{
  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
  clrscr();
  clear_keybuf();
  remove_keyboard();

  printf("\nColor actual: %d", color);
  printf("\nColor(0-256): ");
  scanf("%d", &color);

  if(set_gfx_mode(GFX_VESA1, 640, 480, 0, 0) != 0) { // inicializar modo gr fico VGA
    rut_err(ERR_VIDEO, "640 * 480 * 256");
  }
  install_keyboard();
  set_pallete((RGB*)paleta);
}



void cambiar_color_rejilla(void)
{
  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
  clrscr();
  clear_keybuf();
  remove_keyboard();

  printf("\nColor actual de la rejilla: %d", color_rejilla);
  printf("\nColor(0-256): ");
  scanf("%d", &color_rejilla);

  if(set_gfx_mode(GFX_VESA1, 640, 480, 0, 0) != 0) { // inicializar modo gr fico VGA
    rut_err(ERR_VIDEO, "640 * 480 * 256");
  }
  install_keyboard();
  set_pallete((RGB*)paleta);
}




void guardar_blk(void)
{
  FILE *archivo;
  long int num; // byte dentro de el bloque
  BYTE x, y;


  if((archivo = fopen(ARCHIVO_BLK, "wb")) == NULL) // abrir el archivo en modo binario
    rut_err(ERR_ARCHIVO, ARCHIVO_BLK);

  // escribir cabecera BLK
  fprintf(archivo, "DPABLK"); // ID
  fprintf(archivo, "%c", 1); // Versi¢n
  fwrite(&ids, 16, 1, archivo); // IDS
  fwrite(&mapa.bl_max, 2, 1, archivo);
  fwrite(&mapa.bl_ancho, 2, 1, archivo);
  fwrite(&mapa.bl_alto, 2, 1, archivo);

  x = 0; y = 0;
  for(num = 0; num < mapa.bl_max;) {
    putc(mapa.blk[num]->line[y][x], archivo); // escribir byte
    if(ferror(archivo)) rut_err(ERR_ARCHIVO, ARCHIVO_BLK); // verificar
    x++;
    if(x >= mapa.bl_ancho) {
      x = 0;
      y++;
    }
    if(y >= mapa.bl_alto) {
      num++;
      y = 0;
    }
  }
  for(num = 0; num < mapa.bl_max; num++) {
    putc(mapa.blk_a[num], archivo); // byte de atributo
    if(ferror(archivo)) rut_err(ERR_ARCHIVO, ARCHIVO_BLK);
  }
  fclose(archivo);
}




void info(void)
{
  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
  clrscr();

  printf("
 ---------------------------------------------
 EDITOR DE MAPAS V. 2.0
 Versi¢n para APOCALIPSIS.
 DPA Software. 1999.
 Autor: Jairo Alejandro Duarte Avenda¤o.
        jaal81@yahoo.com
 ---------------------------------------------
  ");
  printf("\n Archivo BLK: %s", ARCHIVO_BLK);
  printf("\n  Longitud: %d bloques", mapa.bl_max);
  printf("\n  Dimenciones de bloque: H=%d V=%d", mapa.bl_ancho, mapa.bl_alto);
  printf("\n  Memoria requerida: %ld bytes", mapa.bl_ancho*mapa.bl_alto*mapa.bl_max);
  printf("\n\n Archivo MAP: %s", ARCHIVO_MAP);
  printf("\n  Dimenciones: H=%d V=%d (%d * %d)", mapa.ancho, mapa.alto, mapa.bl_h, mapa.bl_v);
  printf("\n  Memoria requerida: %ld bytes", mapa.ancho*mapa.alto*sizeof(int) + 4);
  printf("\n  Cadena identificador: \"%s\"", ids);
  printf("\n\n Memoria total requerida: %ld bytes", mapa.bl_ancho*mapa.bl_alto*mapa.bl_max + mapa.ancho*mapa.alto*sizeof(int) + 4);
  printf("\n\n\n            Presione una tecla para continuar...");
  printf("\n");


  clear_keybuf();
  readkey();
  if(set_gfx_mode(GFX_VESA1, 640, 480, 0, 0) != 0) { // inicializar modo gr fico VGA
    rut_err(ERR_VIDEO, "640 * 480 * 256");
  }
  set_pallete(paleta);
}






void ayuda(void)
{
  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
  clrscr();

  clear_keybuf();

  printf("
          Editor de mapas Versi¢n 2.0.

          F2           Guardar
          F4           Guardar como
          CONTROL + B  Guardar el archivo BLK
          F5           Abrir BLK
          F6           Abrir MAP
          F7           Abrir PAL
          F8           Abrir BLK MAP PAL
          F11          Ver rejilla
          F12          Repintar pantalla
          ESPACIO      Ver/ocultar mapa de bloques
          TAB          Ver/ocultar barra de estado en pantalla completa
          CONTROL + R  Re-abrir el archivo MAP
          CONTROL + L  Llenar la pantalla con el bloque seleccionado
          CONTROL + I  Ir a una posici¢n exacta del mapa
          CONTROL + D  Ajustar las dimenciones del mapa
          CONTROL + P  Ajustar el tama¤o de presentaci¢n del mapa
          ESC          Salir del programa
          ENTER        Pintar el bloque seleccionado en el mapa
          RSHIFT       Seleccionar bloque

                  Presione una tecla para continuar.
          ");
  delay(200);
  readkey();
  printf("
          FLECHAS      Scroll de pantalla
          LSHIFT  +    mouse, scroll de bloque)
          CONTROL +    boton izquierdo del mouse, cambiar bloque
          CONTROL + S  Cambiar la cadena de identificaci¢n
          CONTROL + E  Informaci¢n y especificaciones
          CONTROL + C  Establecer el color de la barra de estado
          CONTROL + G  Cambiar el color de la rejilla
          ALT          + bit, propiedad del bloque. Para Apocalipsis:
                       1: 0 = suelo, 1 = pared
                       2: 0 = normal, 1 = mapa adicional

                  Presione una tecla para continuar...
          ");
  delay(400);

  readkey();
  if(set_gfx_mode(GFX_VESA1, 640, 480, 0, 0) != 0) { // inicializar modo gr fico VGA
    rut_err(ERR_VIDEO, "640 * 480 * 256");
  }
  set_pallete(paleta);
}




void rut_err(char cod, char mensaje[80])
{
  remove_keyboard();
  remove_mouse();
  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0); // volver al modo de texto

  switch(cod) {
    case ERR_ARCHIVO: // posiblemente el archivo no existe o se a alterado su contenido
       printf("Error al leer el archivo");
    break;

    case ERR_VIDEO: // error al intentar colocar un modo gr fico
       printf("No se puede inicializar el modo gr fico");
    break;

    case ERR_MEMORIA: // No se logro obtener la memoria con calloc()
       printf("Memoria insuficiente");
    break;

    case ERR_MOUSE:
       printf("No se encontr¢ el controlador del mouse");
    break;

    default: // error personalizado
      printf("Error de ejecuci¢n #%d", cod);
    break;
  }

  printf(" %s.\n", mensaje); // imprimir mensaje adicional

  exit(cod);
}
