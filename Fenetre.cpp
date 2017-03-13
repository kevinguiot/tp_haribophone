//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Fenetre.h"
#include "C_VideoCapture.h"
#include "C_ImageCouleur.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
C_VideoCapture MaCamera;

C_ImageCouleur MonImage(640,480,320,10);
C_ImageCouleur MonTableau(640,480,8,170);

bool TabNotes[4][8]; //Classe attribut (HariboPhone)
int compteurMusique = 0;
int compteurPhoto   = 0;




//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TForm1::B_ConnexionCameraClick(TObject *Sender)
{
/*
String NomCamera = "";
String EtatCamera = "";

//Recherche des périphériques
MaCamera.RechercherPeripherique();

//On récupère le nom de la caméra
NomCamera = MaCamera.GetNomDesPerif(0);

if(MaCamera.ConnecterPeripherique(0) == true) {
        MaCamera.CreerFenetre(this->Handle, 0,0, 300, 480);
        EtatCamera = "OK";
} else {
        EtatCamera = "Problème";
}

//On affiche les informations
Label1->Caption = NomCamera + " | " + EtatCamera;*/

	MaCamera.RechercherPeripherique();
	MaCamera.CreerFenetre(this->Handle, 1000,1000,320,640);
	Label1->Caption = MaCamera.GetNomDesPerif(0);


   

}
//---------------------------------------------------------------------------
void __fastcall TForm1::B_PrendrePhotoClick(TObject *Sender)
{

// prise de la photo, mise à jour du fichier frame.bmp
MaCamera.CapturerFrame();

// affichage en utilisant la classe C_Image
MonImage.LoadFromBmp("images/frames/frame.bmp");

MonImage.Afficher(Canvas);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender) {

        //Déclarations de variables
        int TabColCases[12];
        int TabLigCases[4];

        //On remets à jour les images
        MonTableau.LoadFromBmp("images/tableau.bmp");
	MonImage.LoadFromBmp("images/frames/frame.bmp");

        //On initialise le tableau des notes
        compteurMusique = 0;
        for(int c = 0; c < 8; c++) {
                for(int l = 0; l < 4; l++) {
                        TabNotes[l][c] = false;
                }
        }

        //Réglages
        int seuillage = Edit1->Text.ToInt();
        bool afficherTousMarqueurs = CheckBox1->Checked;

        //On effectue un seillage
	for(int c = 0; c < MonImage.GetHauteur(); c++) {
		for(int l = 0; l < MonImage.GetLargeur(); l++) {

			//Différentes couches de seuilage
				if(MonImage.GetPixelRVB(c,l) < seuillage) {
					MonImage.PutPixel(c,l, 1);
				} else {
                                        MonImage.PutPixelR(c,l, 255);
					MonImage.PutPixelV(c,l, 255);
					MonImage.PutPixelB(c,l, 255);
                                }
                                                //Délimination
		}
	}



        MonImage.Afficher(Canvas);



        //On regarde si la grille existez
        int ligne = 240;

        //c1 & c2 : colonne gauche
        int c1 = 0;
        int c2 = 0; //c1 + 5


        //c3 & c4 : colonne droite
        int c3 = 0;
        int c4 = 0; //c3 + 5

        int l1 = 0; //Ligne haut c1
        int l2 = 0; //Ligne bas c1

        // recherche de la grille
	for(int c = 0; c < MonImage.GetLargeur(); c++) {
               //Si on capte un pixel noir (début de la grille)
                if(MonImage.GetPixelRVB(ligne, c) == 0) {
                           c1 = c;
                           c2 = c1;

                           break;
                }
	}



        for(int c = MonImage.GetLargeur(); c > 0; c--) {
               //Si on capte un pixel noir (début de la grille)
                if(MonImage.GetPixelRVB(ligne, c) == 0) {
                           c3 = c;
                           c4 = c3;

                           break;
                }
	}



        /* ON CAPTE LES LIGNES */

        // on remonte dans le trait noir jusqu'au coin en haut à gauche
        // attention il faut que le trait soit épais d'au moins 10 pixels
        int l = (MonImage.GetHauteur()) / 2;
        bool jAiRetrouveLeBord = true;
        while ( jAiRetrouveLeBord == true )
        {
                int c = 0;
                while(MonImage.GetPixelRVB(l, c) == 255 && c<MonImage.GetLargeur() )
                        c++;
                if (c1-5 <c && c<c1+5)
                        jAiRetrouveLeBord = true;
                else   jAiRetrouveLeBord = false;
                l--;
        }
        l1 = l;


        // on remonte dans le trait noir jusqu'au coin en bas à gauche
        // attention il faut que le trait soit épais d'au moins 10 pixels
        l = (MonImage.GetHauteur()) / 2;
        jAiRetrouveLeBord = true;
        while ( jAiRetrouveLeBord == true )
        {
                int c = 0;
                while(MonImage.GetPixelRVB(l, c) == 255 && c<MonImage.GetLargeur() )
                        c++;
                if (c1-5 <c && c<c1+5)
                        jAiRetrouveLeBord = true;
                else   jAiRetrouveLeBord = false;
                l++;
        }
        l2 = l;


        /* ON CAPTE LES COLONNES */


        


          /*

         //On va à la fin de la première ligne
        // on avance à droite dans le trait noir jusqu'au coin ern haut à droite
        for(int c = 320; c < MonImage.GetLargeur(); c++) {
                if(MonImage.GetPixelRVB(l1, c) == 255) {
                         c3 = c;
                         c4 = c3 + 3;

                         break;
                }
        }     */


        /*
        for(int l = 240; l > 0; l--) {
                if(MonImage.GetPixelRVB(l, c2) == 255) {
                        l1 = l;
                        break;
                }
        }
          */



        //On définit les lignes
        int PasAPas = (l2 - l1) / 8;

        int k = 0;
        int j = 0;
        int m = 0; //Nombre de colonne

        for(int l = l1; l < l2; l++) {
                if(k > PasAPas) {
                        if(j == 0) {
                               MonImage.MarquerLigne(l, Canvas, clBlue);
                                TabLigCases[m] = l;

                                j = 1;
                                m++;
                        } else {
                                if(afficherTousMarqueurs == true) {
                                        MonImage.MarquerLigne(l, Canvas, clAqua);
                                }
                                j = 0;
                        }
                        k = 0;
                }

                k++;
        }







        //Définitions des colonnes
        //int CPasAPas = (c4 - c2) / 24; //21
        int CPasAPas = 20;

        int j2 = 0;
        int k2 = 0;
        int m2 = 0;

        for(int c = c2; c < c4; c++) {
                if(k2 > CPasAPas) {
                        k2 = 0;

                        if(j2 == 0) {

                                //Pour ne pas avoir 12 cases mais 8
                                if(m2 < 9) MonImage.MarquerColonne(c, Canvas, clBlue);
                                else MonImage.MarquerColonne(c, Canvas, clBlack);

                                TabColCases[m2] = c;

                                m2++;
                                j2 = 1;
                        } else {
                                if(j2 == 1) {
                                        if(afficherTousMarqueurs == true) {
                                                MonImage.MarquerColonne(c, Canvas, clMaroon);
                                        }
                                        j2 = 0;
                                }
                        }

                }

                k2++;
        }

        if(afficherTousMarqueurs == true) {
                //Marqueur verticaux
                MonImage.MarquerColonne(c1, Canvas, clGreen);
                MonImage.MarquerColonne(c4, Canvas, clGreen);

                //Marqueur horizontaux
                MonImage.MarquerLigne(l1, Canvas, clRed);
                MonImage.MarquerLigne(l2, Canvas, clRed);
        }


        //On parcourt les points
        for(int c = 0; c < 8 /*12 auparavant*/; c++) {
                for(int l = 0; l < 4; l++) {

                        int pixelC = TabColCases[c];
                        int pixelL = TabLigCases[l];

                        //On regarde les alentours
                        if(
                                MonImage.GetPixelRVB(pixelL, pixelC) == 0 &&
                                MonImage.GetPixelRVB(pixelL - 1, pixelC) == 0 &&
                                MonImage.GetPixelRVB(pixelL, pixelC + 1) == 0 &&
                                MonImage.GetPixelRVB(pixelL - 1, pixelC) == 0 &&
                                MonImage.GetPixelRVB(pixelL, pixelC - 1) == 0
                        ) {
                                TColor color = clLime;

                                for(int i = 0; i < 4; i++) {
                                       if(i == 0) {
                                                MonImage.MarquerPoint(pixelC, pixelL, Canvas, clLime);
                                       } else {

                                                MonImage.MarquerPoint(pixelC, pixelL - i, Canvas, color);
                                                MonImage.MarquerPoint(pixelC + i, pixelL, Canvas, color);
                                                MonImage.MarquerPoint(pixelC, pixelL + i, Canvas, color);
                                                MonImage.MarquerPoint(pixelC - i, pixelL, Canvas, color);
                                        }
                                }

                                //On place à true;
                                TabNotes[l][c] = true;
                        } else {
                                TColor color = clRed;

                                for(int i = 0; i < 4; i++) {
                                       if(i == 0) {
                                                MonImage.MarquerPoint(pixelC, pixelL, Canvas, clLime);
                                       } else {

                                                MonImage.MarquerPoint(pixelC, pixelL - i, Canvas, color);
                                                MonImage.MarquerPoint(pixelC + i, pixelL, Canvas, color);
                                                MonImage.MarquerPoint(pixelC, pixelL + i, Canvas, color);
                                                MonImage.MarquerPoint(pixelC - i, pixelL, Canvas, color);
                                        }
                                }
                        }
                }

        }


        //On rempli le tableau virtuel
	int traitsV = 0;
	int traitsH = 0;
        int c = 0;
        int i = 0;

	bool dansLeNoir = false;

        int casesVerticales[8];

        casesVerticales[0] = 5;
        casesVerticales[1] = 41;
        casesVerticales[2] = 78;
        casesVerticales[3] = 115;
        casesVerticales[4] = 152;
        casesVerticales[5] = 189;
        casesVerticales[6] = 226;
        casesVerticales[7] = 263;


        

	       for(l = 5; l < MonTableau.GetHauteur() - 5; l++) {

               for(i = 0; i < 8; i++) {






                        c = casesVerticales[i];
                        traitsV = i;


				if(MonTableau.GetPixel(l, c) != 0) {
					if(dansLeNoir == true) {
						dansLeNoir = false;
                                                traitsH++;
					}

					if(TabNotes[traitsH][traitsV] == true) {


                                                for(int k = c; k < c + 32; k++) {
                                           	        MonTableau.PutPixelR(l, k, 0);
						        MonTableau.PutPixelV(l, k, 255);
						        MonTableau.PutPixelB(l, k, 0);
                                                }
					}
				} else {
					dansLeNoir = true;
				}

               }



		}



                        /*
                        if(MonTableau.GetPixel(l, c) != 0) {
                        if(dansLeNoir == true) {
                                dansLeNoir = false;
                                traitsV++;
                        }

                        if(TabNotes[0][traitsV] == true) {
                                MonTableau.PutPixelR(l, c, 255);
                                MonTableau.PutPixelV(l, c, 0);
                                MonTableau.PutPixelB(l, c, 0);
                        }
                        } else {
                        dansLeNoir = true;
                        } */


                
        









          /*
               for(int l = 5; l < MonTableau.GetHauteur() - 5; l++) {

                        if(MonTableau.GetPixel(l, c) != 0) {
                               MonTableau.PutPixelR(l, c, 255);
                               MonTableau.PutPixelV(l, c, 0);
                               MonTableau.PutPixelB(l, c, 0);
                       }
                }
                */


        MonTableau.Afficher(Canvas);
        Button2->Enabled = true;

        





}

//---------------------------------------------------------------------------

void __fastcall TForm1::TimerJouerTimer(TObject *Sender)
{


        if(compteurMusique > 7) {
                compteurMusique = 0;
        }

        int PositionImage = 0;
        PositionImage = Image1->Left;

        if(compteurMusique == 0) {
               Image1->Left = 23;
        } else {
                Image1->Left = PositionImage + 37;
        }


        if(TabNotes[0][compteurMusique] == true) {
                MediaPlayer4->Play();
        }

        if(TabNotes[1][compteurMusique] == true) {
                MediaPlayer3->Play();
        }

        if(TabNotes[2][compteurMusique] == true) {
                MediaPlayer2->Play();
        }

        if(TabNotes[3][compteurMusique] == true) {
                MediaPlayer1->Play();
        }



        compteurMusique++;
}
//---------------------------------------------------------------------------




void __fastcall TForm1::TimerAcqTimer(TObject *Sender)
{

// prise de la photo, mise à jour du fichier frame.bmp
MaCamera.CapturerFrame();



// affichage en utilisant la classe C_Image
MonImage.LoadFromBmp("images/frames/frame.bmp");
MonImage.Afficher(Canvas);
  
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        MonTableau.LoadFromBmp("images/tableau.bmp");
        MonTableau.Afficher(Canvas);

	MonImage.LoadFromBmp("images/frames/frame.bmp");
        MonImage.Afficher(Canvas);

        Button4->Enabled = true;
        GroupBox1->Visible = true;        
}
//---------------------------------------------------------------------------



//Gestion du son
void __fastcall TForm1::Button2Click(TObject *Sender)
{
        //Si le timer n'est pas encore lancé
        if(TimerJouer->Enabled == false) {
                TimerJouer->Enabled = true;
                Image1->Visible = true;
                Button2->Caption = "Arrêter le son";
        } else {
                TimerJouer->Enabled = false;
                Button2->Caption = "Jouer le son";
        }
}
//---------------------------------------------------------------------------


