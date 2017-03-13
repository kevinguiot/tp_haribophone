/*--------------------------------------------------------
  TP Imagerie       BTS Iris Lorgues      Septembre 2007
Classe permettant d'acquerir une image depuis un peripherique
video (camera USB, appareil photo, scanner, camera video avec
carte d'acquisition video, ...)
C_VideoCapture.cpp    Environnement : WinXP, C++ Builder 6
Auteur : Philippe Dupuy, R�mi Breysse
---------------------------------------------------------*/

#include <vcl.h>
#pragma hdrstop
#pragma package(smart_init)

#include "C_VideoCapture.h"
//---------------------------------------------------------------------------
void C_VideoCapture::RechercherPeripherique()
{
//================================================
//Recherche de p�riph�riques
        for (short DevIndex = 0; DevIndex < 10; DevIndex++)
        {

            if (capGetDriverDescription (DevIndex, szDeviceName,
                sizeof (szDeviceName), szDeviceVersion,
                sizeof (szDeviceVersion)))
            {
                //incription des noms de p�riph�riques
                nomDesPerif[DevIndex]=szDeviceName;
            }else nomDesPerif[DevIndex]="";
        }
}
//================================================
void C_VideoCapture::CreerFenetre(HWND fenetreParent)
{
        hFenCapt = capCreateCaptureWindow (
            "My Capture Window",    // nom de la fen�tre
            WS_CHILD | WS_VISIBLE,  // style de la fen�tre (winuser.h - L:2291)
            150, 24, 352, 288,         // position et dimensions de la fen�tre
            fenetreParent,          // handle sur la fen�tre parente
            nID );                  // identificateur de la fen�tre
}
//================================================
void C_VideoCapture::CreerFenetre(HWND fenetreParent,short posX, short posY,
    short largeur, short hauteur)
{
        hFenCapt = capCreateCaptureWindow (
            "My Capture Window",    // nom de la fen�tre
            WS_CHILD | WS_VISIBLE,  // style de la fen�tre (winuser.h - L:2291)
            posX, posY, largeur, hauteur,  // position et dimensions de la fen�tre
            fenetreParent,          // handle sur la fen�tre parente
            nID );                  // identificateur de la fen�tre
}
//================================================
bool C_VideoCapture::ConnecterPeripherique(short NumeroDuPeripherique)
{
        bool test=capDriverConnect(hFenCapt,NumeroDuPeripherique);
        //configuration de la vitesse de visualisation
        capPreviewRate(hFenCapt,30);
        //demarrage de la pr�visualisation
        capPreview(hFenCapt,true);
        return test;
}
//================================================
void C_VideoCapture::CapturerVideo()
{
        capCaptureSequence(hFenCapt);
        capFileSaveAs(hFenCapt, strFileNameVideo.c_str());
}
//================================================
bool C_VideoCapture::CapturerFrame()
{
        return capFileSaveDIB(hFenCapt,strFileNameFrame.c_str());
}
//================================================
void C_VideoCapture::HeightWidth(unsigned int *h,unsigned int *w)
{
CAPSTATUS CapStatus;
        capGetStatus(hFenCapt,&CapStatus,sizeof(CAPSTATUS));
        *h = CapStatus.uiImageHeight;
        *w = CapStatus.uiImageWidth;
}
//================================================
HWND C_VideoCapture::GetHandleCaptureWindow(void)
{
return hFenCapt;
}
//================================================
