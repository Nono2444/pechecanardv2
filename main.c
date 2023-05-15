
#include <allegro.h>
#include <time.h>
#include <stdio.h>

typedef struct canard{
    BITMAP* file;  //sprite
    int x, y;  //coordonnées du coin supérieur gauche
    int depx, depy;  //deplacement
    int posprex, posprey ;  //position précedente
    int tx, ty;  //taille de l'acteur
    int grab;

}t_canard;



int contact(t_canard *canard, BITMAP *bmp, int couleur)
{
  int ncontact;
  int xb, yb;
  ncontact=0;
  for (yb=0; yb<canard->ty;yb++){
      if (getpixel(bmp, canard->x, canard->y+yb)== couleur)
          ncontact++;
      if (getpixel(bmp, canard->x+canard->tx, canard->y+yb)== couleur)
          ncontact++;
  }
    for (xb=0; xb<canard->tx;xb++){
        if (getpixel(bmp, canard->x+xb, canard->y)== couleur)
            ncontact++;
        if (getpixel(bmp, canard->x+xb, canard->y+canard->ty)== couleur)
            ncontact++;
    }
    return ncontact;
}


void initialisation_allegro();


int main() {

    t_canard canard[10];
    BITMAP *page;
    BITMAP *decor;
    BITMAP *murs;
    int compteur=0;
   // int temps=30;



    initialisation_allegro();

    show_mouse(screen);





    page = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(page);
    decor = load_bitmap("pechecanard.bmp", NULL);
    murs = load_bitmap("collisioncanard.bmp", NULL);

  for (int i =0; i<10; i++)
  { // initialisation de tous les canards
      canard[i].x=200+50*i;
      canard[i].y=20+50*i;
      canard[i].tx=69;
      canard[i].ty=75;
      canard[i].grab=0;
      canard[i].file = load_bitmap("spritecanard.bmp", NULL);
  }

    canard->depx = 0; canard->depy = 0;


for (int i=0; i<10;i++)
    {
     canard[i].posprex= canard[i].x;  // test
     canard[i].posprey= canard[i].y;
    }

    int pris=0;

    while (!key[KEY_ESC] ) {


        textprintf_ex(decor, font,30, 30, makecol(0, 0, 0), -1, "Score %d",compteur);

        blit(decor, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        for (int i=0; i<10;i++){
            if(canard[i].grab!=2) {
                // le for
                masked_blit(canard[i].file, page, 0, 0, canard[i].x, canard[i].y, canard->tx, canard->ty); // page


                // SI ON UTILISE LA SOURIS
                if ((mouse_b & 1)&&(pris==0))
                {
                    printf("pris :%d, i: %d (dans le test souris)\n ", pris, i);

                    if (((mouse_x >= canard[i].x) && (mouse_x < (canard[i].x + canard[i].tx))) &&
                         ((mouse_y >= canard[i].y) &&
                         (mouse_y < (canard[i].y + canard[i].ty))))
                    {
                        canard[i].grab = 1;
                         pris = 1;
                         printf(" pris : %d, i : %d (dans le test de coordonnees) \n", pris, i);
                         printf(" mouse x : %d, mouse y : %d,can x:  %d,can y : %d", mouse_x, mouse_y, canard[i].x,canard[i].y);
                    }
                    else
                    {
                        canard[i].grab = 0;
                    }
                }
                    if (canard[i].grab)
                    {
                        canard[i].x = mouse_x - canard->file->w / 2;
                        canard[i].y = mouse_y - canard->file->h / 2; // on centre le canard sur la souris
                    }


                    if (contact(canard, murs, makecol(255, 0, 0))) // rouge = collision
                    {

                        // canard[i].x -= 20;
                        //canard[i].y -= canard[i].posprey;


                           //canard[i].x -= canx_diff; // test
                           // canard[i].y -= cany_diff;*/
                    }



                    canard[i].posprex = canard[i].x;  //  a tester sur mvt aléatoire
                    canard[i].posprey = canard[i].y;
                }


                if ((canard[i].grab==1)&&contact(&(canard[i]), murs, makecol(255, 255, 0))) // jaune
                {

                    compteur++;
                    canard[i].grab=2;
                    pris=0;

                }

        } // le for

        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }

    destroy_bitmap(canard->file);
    destroy_bitmap(decor);
    destroy_bitmap(murs);
    destroy_bitmap(page);
    allegro_exit();

    return 0;
}
END_OF_MAIN();


void initialisation_allegro()
{
    allegro_init(); // appel obligatoire (var.globales, recup. infos syst�me ...)
    install_keyboard(); //pour utiliser le clavier
    install_mouse(); //pour utiliser la souris
    //pour choisir la profondeur de couleurs (8,16,24 ou 32 bits)
    set_color_depth(desktop_color_depth()); //ici�: identique � celle du bureau

    //s�lection du mode graphique
    // avec choix d'un driver+mode+r�solution de l'�cran
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    show_mouse(screen);
}