/*--------------------------------------------------------
  TP Imagerie       BTS Iris Lorgues      Septembre 2007
Classe permettant d'acquerir une image depuis un peripherique
video (camera USB, appareil photo, scanner, camera video avec
carte d'acquisition video, ...)
C_VideoCapture.h      Environnement : WinXP, C++ Builder 6
Auteur : Philippe Dupuy, R�mi Breysse
---------------------------------------------------------*/

#ifndef C_VideoCaptureH
#define C_VideoCaptureH
//---------------------------------------------------------------------------

#include <vcl.h>
#include <vfw.h>

//---------------------------------------------------------------------------
class C_VideoCapture
{
    private:
        HWND hFenCapt;
        int nID;
        char szDeviceName[80];
        char szDeviceVersion[80];
        AnsiString nomDesPerif[10];
        CAPDRIVERCAPS CapDrvCaps;
        CAPSTATUS *CapStatus;

   public:

        AnsiString strFileNameFrame,strFileNameVideo;
        C_VideoCapture()
        {
                strFileNameFrame="frame.bmp";
                strFileNameVideo="video.avi";
        };
        void RechercherPeripherique();
        void CreerFenetre(HWND arg);
        //arg: handle sur la fen�tre parente
        void CreerFenetre(HWND arg, short posX, short posY,
              short largeur, short hauteur);

        AnsiString GetNomDesPerif(short num)
        {
                if(nomDesPerif[num]=="")
                  return "" ;
                else
                  return nomDesPerif[num];
        };
        //num :num�ro du p�riph�rique(0 � 9 d�finit par rechercherPeripherique())
        //retourne le nom du p�riph�rique ou ""

        bool ConnecterPeripherique(short NumeroDuPeripherique);
        //arg:num�ro du p�riph�rique(0 � 9 d�finit par rechercherPeripherique())

        void AppelerFenetre_CameraEtResolution()
        {
                capDlgVideoFormat( hFenCapt );
                capDlgVideoSource( hFenCapt );
                capDlgVideoDisplay(hFenCapt);
        };
        void AppelerFenetre_Compression()
        {
                capDlgVideoCompression(hFenCapt);
        };
        void SetNomFichierFrame()
        { InputQuery("","",strFileNameFrame);
        };
        void SetNomFichierVideo()
        { InputQuery("","",strFileNameVideo);
        };
        void CapturerVideo();
        bool CapturerFrame();
        void HeightWidth(unsigned int *h,unsigned int *w);
        HWND GetHandleCaptureWindow(void);
};


#endif
