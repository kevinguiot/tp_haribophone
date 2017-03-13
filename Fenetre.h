//---------------------------------------------------------------------------

#ifndef FenetreH
#define FenetreH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <MPlayer.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// Composants gérés par l'EDI
  TButton *B_ConnexionCamera;
  TLabel *Label1;
        TButton *B_PrendrePhoto;
        TButton *Button4;
        TTimer *TimerAcq;
        TTimer *TimerJouer;
        TMediaPlayer *MediaPlayer2;
        TMediaPlayer *MediaPlayer3;
        TMediaPlayer *MediaPlayer4;
        TMediaPlayer *MediaPlayer1;
        TButton *Button1;
        TGroupBox *GroupBox1;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *Edit1;
        TCheckBox *CheckBox1;
        TButton *Button2;
        TImage *Image1;
  void __fastcall B_ConnexionCameraClick(TObject *Sender);
  void __fastcall B_PrendrePhotoClick(TObject *Sender);
  void __fastcall Button4Click(TObject *Sender);
        void __fastcall TimerJouerTimer(TObject *Sender);
        void __fastcall TimerAcqTimer(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
  __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
