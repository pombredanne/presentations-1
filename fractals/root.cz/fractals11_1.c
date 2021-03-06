//-----------------------------------------------------------------------------
// Fraktaly v pocitacove grafice
// Ukazkovy priklad cislo 11.1
// Autor: Pavel Tisnovsky
//
// Vykresleni Juliovy mnoziny.
// Pixmapu s vykreslenym fraktalem je mozne ulozit do souboru ve formatu TGA
// pomoci klavesove zkratky [S].
// Ukonceni aplikace se provede klavesou [Esc] nebo klavesou [Q].
//-----------------------------------------------------------------------------

#ifdef __BORLANDC__
#include <windows.h>
#endif

#include <GL/glut.h>                            // hlavickovy soubor funkci GLUTu a OpenGL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WINDOW_TITLE    "Fraktaly 11.1"         // titulek okna
#define WINDOW_WIDTH    512                     // pocatecni velikost okna
#define WINDOW_HEIGHT   384
#define FILE_NAME       "fraktaly111.tga"       // jmeno souboru pro ulozeni pixmapy

#define PIXMAP_WIDTH    512                     // sirka pixmapy
#define PIXMAP_HEIGHT   384                     // vyska pixmapy

typedef struct {                                // struktura popisujici pixmapu
    unsigned int width;
    unsigned int height;
    unsigned char *pixels;
} pixmap;

pixmap *pix;

int    maxiter=150;                             // maximalni pocet iteraci

// parametry Juliovy mnoziny
#define CX     -0.771
#define CY      0.115

// hranice obrazce v komplexni rovine
#define MINX   -2.0
#define MAXX    2.0
#define MINY   -1.5
#define MAXY    1.5



//-----------------------------------------------------------------------------
// Funkce pro vytvoreni pixmapy o zadane velikosti
//-----------------------------------------------------------------------------
pixmap * createPixmap(const unsigned int width, const unsigned int height)
{
    pixmap *p=(pixmap *)malloc(sizeof(pixmap)); // alokace struktury pixmapy
    if (!p) return NULL;
    p->width=width;                             // naplneni struktury
    p->height=height;
    p->pixels=(unsigned char *)malloc(3*width*height);
    if (!p->pixels) {                           // alokace pole pro pixely
        free(p);                                // alokace se nepovedla
        return NULL;
    }
    else {
        memset(p->pixels, 0, 3*width*height);   // smazani pixmapy
    }
    return p;
}



//-----------------------------------------------------------------------------
// Funkce pro zruseni pixmapy
//-----------------------------------------------------------------------------
void destroyPixmap(pixmap *p)
{
    if (p->pixels) free(p->pixels);             // uvolnit vlastni pixmapu
    if (p) free(p);                             // i okolni strukturu
}



//-----------------------------------------------------------------------------
// Vymazani pixmapy
//-----------------------------------------------------------------------------
void clearPixmap(const pixmap *p)
{
    if (!p) return;
    if (!p->pixels) return;
    memset(p->pixels, 0, 3*p->width*p->height);
}



//-----------------------------------------------------------------------------
// Funkce pro vykresleni pixmapy do barvoveho bufferu
//-----------------------------------------------------------------------------
void drawPixmap(const pixmap *p)
{
    if (!p || !p->pixels) return;
    glDrawPixels(                               // vykresleni pixmapy
            p->width, p->height,                // sirka a vyska pixmapy
            GL_RGB,                             // format dat pixelu
            GL_UNSIGNED_BYTE,                   // datovy typ kazde barevne slozky
            p->pixels);                         // ukazatel na pamet s barvami pixelu
}



//-----------------------------------------------------------------------------
// Ulozeni pixmapy do externiho souboru
//-----------------------------------------------------------------------------
void savePixmap(const pixmap *p, const char *fileName)
{
    FILE *fout;
    unsigned int i, j, k;
    unsigned char tgaHeader[18]={               // hlavicka formatu typu TGA
                        0x00,                   // typ hlavicky TGA
                        0x00,                   // nepouzivame paletu
                        0x02,                   // typ obrazku je RGB TrueColor
                        0x00, 0x00,             // delka palety je nulova
                        0x00, 0x00, 0x00,       // pozice v palete nas nezajima
                        0x00, 0x00, 0x00, 0x00, // obrazek je umisteny na pozici [0, 0]
                        0x00, 0x00, 0x00, 0x00, // sirka a vyska obrazku (dva byty na polozku)
                        0x18,                   // format je 24 bitu na pixel
                        0x20                    // orientace bitmapy v obrazku
    };
    if (!p || !p->pixels) return;
    memcpy(tgaHeader+12, &(p->width), 2);       // do hlavicky TGA zapsat velikost obrazku
    memcpy(tgaHeader+14, &(p->height), 2);
    fout=fopen(fileName, "wb");
    if (fout) {
        fwrite(tgaHeader, 18, 1, fout);         // zapsat hlavicku TGA do souboru
        for (j=p->height; j; j--) {             // radky zapisovat v opacnem poradi
            unsigned int yoff=(j-1)*3*p->width; // y-ovy offset v poli
            unsigned int xoff=0;                // x-ovy offset v poli
            for (i=0; i<p->width; i++) {        // pro kazdy pixel na radku
                for (k=0; k<3; k++) {           // prohodit barvy RGB na BGR
                    fputc(p->pixels[xoff+yoff+2-k], fout); // a zapsat do souboru
                }
                xoff+=3;                        // posun na dalsi pixel
            }
        }
        fclose(fout);
    }
}



//-----------------------------------------------------------------------------
// Zmena barvy pixelu na zadanych souradnicich
//-----------------------------------------------------------------------------
void putpixel(pixmap *p,
              const unsigned int x,             // pozice pixelu v pixmape
              const unsigned int y,
              const unsigned char r,            // barva pixelu
              const unsigned char g,
              const unsigned char b)
{
    int pos;
    // zde se vyuziva zkraceneho vyhodnoceni vyrazu - pokud plati !p, nic se dale netestuje
    if (!p || !p->pixels || x>=p->width || y>=p->height) return;
    pos=3*(x+y*p->width);
    p->pixels[pos++]=r;                         // nastaveni barvy pixelu
    p->pixels[pos++]=g;
    p->pixels[pos]=b;
}



//-----------------------------------------------------------------------------
// Uprava svetlosti pixelu v pixmape do celeho spektra
//-----------------------------------------------------------------------------
void filterPixmap(pixmap *pix)
{
    int i;
    unsigned char maxr=0;
    unsigned char maxg=0;
    unsigned char maxb=0;
    unsigned char *p=pix->pixels;
    float         gainr;
    float         gaing;
    float         gainb;

    // projit vsechny pixely a zjistit maximalni intenzity
    for (i=0; i<(pix->width)*(pix->height); i++) {
        if (*p>maxr) maxr=*p;
        p++;
        if (*p>maxg) maxg=*p;
        p++;
        if (*p>maxb) maxb=*p;
        p++;
    }
    
    // vypocitat zesileni pro jednotlive barvove slozky
    gainr=maxr ? 255.0/(float)maxr : 0;
    gaing=maxr ? 255.0/(float)maxg : 0;
    gainb=maxr ? 255.0/(float)maxb : 0;

    // projit vsechny pixely a aplikovat zesileni
    p=pix->pixels;
    for (i=0; i<(pix->width)*(pix->height); i++) {
        *p=(unsigned char)((float)*p*gainr); p++;
        *p=(unsigned char)((float)*p*gaing); p++;
        *p=(unsigned char)((float)*p*gainb); p++;
    }
}



//-----------------------------------------------------------------------------
// Prekresleni Juliovy mnoziny
//-----------------------------------------------------------------------------
void recalcJulia( pixmap *pix,                  // pixmapa pro vykreslovani
                  int    maxiter)               // maximalni pocet iteraci
{
    double zx, zy, zx2, zy2;                    // slozky komplexni promenne Z a Z^2
    double zx0, zy0;
    double cx=CX, cy=CY;                        // slozky komplexni konstanty C
    int    x, y;                                // pocitadla sloupcu a radku v pixmape
    int    iter;                                // pocitadlo iteraci

    zy0=MINY;
    for (y=0; y<pix->height; y++) {             // pro vsechny radky v pixmape
        zx0=MINX;
        for (x=0; x<pix->width; x++) {          // pro vsechny pixely na radku
            zx=zx0;                             // nastavit pocatecni hodnotu Z(0)
            zy=zy0;
            for (iter=0; iter<maxiter; iter++) {// iteracni smycka
                zx2=zx*zx;                      // zkraceny vypocet druhe mocniny slozek Z
                zy2=zy*zy;
                if (zx2+zy2>4.0) break;         // kontrola prekroceni meze divergence
                zy=2.0*zx*zy+cy;                // vypocet Z(n+1)
                zx=zx2-zy2+cx;
            }
            putpixel(pix, x, y, iter, iter, iter); // vykresleni pixelu
            zx0+=(MAXX-MINX)/pix->width;        // posun na dalsi bod na radku
        }
        zy0+=(MAXY-MINY)/pix->height;           // posun na dalsi radek
    }
}



//-----------------------------------------------------------------------------
// Vykresleni retezce na obrazovku
//-----------------------------------------------------------------------------
void drawString(const int x, const int y,                    // umisteni retezce
                const float r, const float g, const float b, // barva pisma
                char *str)                                   // ukazatel na retezec
{
    char *c;
    glColor3f(r, g, b);
    glRasterPos2i(x, y);
    for (c=str; *c!=0; c++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }
}



//-----------------------------------------------------------------------------
// Vypis informaci o vykreslovanem fraktalu
//-----------------------------------------------------------------------------
void drawInfo(int maxiter)
{
    char str[100];
    sprintf(str, "[<][>]  maxiter = %d", maxiter);
    drawString(10, 48, 0.6, 1.0, 0.8, str);
}



//-----------------------------------------------------------------------------
// Funkce volana pro inicializaci vykreslovani
//-----------------------------------------------------------------------------
void onInit(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);       // barva pozadi
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);      // mod ulozeni pixelu

    pix=createPixmap(PIXMAP_WIDTH, PIXMAP_HEIGHT);
}



//-----------------------------------------------------------------------------
// Nastaveni souradneho systemu v zavislosti na velikosti okna
//-----------------------------------------------------------------------------
void onResize(int w, int h)                     // argumenty w a h reprezentuji novou velikost okna
{
    glViewport(0, 0, w, h);                     // viditelna oblast pres cele okno
    glMatrixMode(GL_PROJECTION);                // zacatek modifikace projekcni matice
    glLoadIdentity();                           // vymazani projekcni matice (=identita)
    glOrtho(0, w, 0, h, -1, 1);                 // mapovani abstraktnich souradnic do souradnic okna
}



//-----------------------------------------------------------------------------
// Tato callback funkce je zavolana pri kazdem prekresleni okna
//-----------------------------------------------------------------------------
void onDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);               // vymazani vsech bitovych rovin barvoveho bufferu
    glDrawBuffer(GL_BACK);                      // pixmapa se bude kreslit do zadniho barvoveho bufferu
    glRasterPos2i(0, 0);                        // nastaveni souradnic leveho spodniho rohu pixmapy
    clearPixmap(pix);                           // vymazani pracovni pixmapy (nastaveni pixelu na cernou barvu)
    recalcJulia(pix, maxiter);                  // prepocet fraktalu
    filterPixmap(pix);                          // uprava pixmapy
    drawPixmap(pix);                            // vykresleni pixmapy
    drawInfo(maxiter);
    glFlush();                                  // provedeni a vykresleni vsech zmen
    glutSwapBuffers();
}



//-----------------------------------------------------------------------------
// Tato callback funkce je zavolana pri stlaceni ASCII klavesy
//-----------------------------------------------------------------------------
#ifdef __BORLANDC__
#pragma option -w-par
#endif
void onKeyboard(unsigned char key, int x, int y)
{
    key=(key>='A' && key<='Z') ? key-'A'+'a': key;
    switch (key) {
        case 27:                                                              // pokud byla stlacena klavesa ESC, konec programu
        case 'q': exit(0);                                             break; // totez co klavesa ESC
        case 's': savePixmap(pix, FILE_NAME);                          break; // ulozeni pixmapy
        case '<': if (maxiter>10)   maxiter-=10; glutPostRedisplay();  break; 
        case ',': if (maxiter>1)    maxiter--;   glutPostRedisplay();  break; // zmena poctu iteraci
        case '>': if (maxiter<246)  maxiter+=10; glutPostRedisplay();  break; 
        case '.': if (maxiter<255)  maxiter++;   glutPostRedisplay();  break; 
        default:                                                       break; 
    }
}
#ifdef __BORLANDC__
#pragma option -w+par
#endif



//-----------------------------------------------------------------------------
// Tato callback funkce je zavolana pri stlaceni non-ASCII klavesy
//-----------------------------------------------------------------------------
#ifdef __BORLANDC__
#pragma option -w-par
#endif
void onSpecial(int key, int x, int y)
{
    // posun fraktalu a zmena meritka
    switch (key) {
        default:                                                break;
    }
}
#ifdef __BORLANDC__
#pragma option -w+par
#endif



//-----------------------------------------------------------------------------
// Hlavni funkce konzolove aplikace
//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
    glutInit(&argc, argv);                      // inicializace knihovny GLUT
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow(WINDOW_TITLE);             // vytvoreni okna pro kresleni
    glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);// zmena velikosti okna
    glutPositionWindow(100, 100);               // pozice leveho horniho rohu okna
    glutDisplayFunc(onDisplay);                 // registrace funkce volane pri prekreslovani okna
    glutReshapeFunc(onResize);                  // registrace funkce volane pri zmene velikosti okna
    glutKeyboardFunc(onKeyboard);               // registrace funkce volane pri stlaceni klavesy
    glutSpecialFunc(onSpecial);                 // registrace funkce volane pri stlaceni specialni klavesy
    onInit();                                   // inicializace vykreslovani
    glutMainLoop();                             // nekonecna smycka, kde se volaji zaregistrovane funkce
    return 0;                                   // navratova hodnota vracena operacnimu systemu
}



//-----------------------------------------------------------------------------
// finito
//-----------------------------------------------------------------------------

