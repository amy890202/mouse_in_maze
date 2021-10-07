//---------------------------------------------------------------------------

#ifndef mouseinmazeH
#define mouseinmazeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Imaging.jpeg.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *Button2;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *Edit1;
	TEdit *Edit2;
	TGroupBox *GroupBox1;
	TButton *Button3;
	TButton *Button4;
	TOpenDialog *OpenDialog1;
	TSaveDialog *SaveDialog1;
	TButton *Button5;
	TButton *Button6;
	TEdit *Edit3;
	TLabel *Label3;
	TButton *Button7;
	TCheckBox *CheckBox1;
	TTrackBar *TrackBar1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TMemo *Memo1;
	TTabSheet *TabSheet2;
	TStringGrid *StringGrid1;
	TTabSheet *TabSheet3;
	TStringGrid *StringGrid2;
	TTabSheet *TabSheet4;
	TStringGrid *StringGrid3;
	TTabSheet *TabSheet5;
	TStringGrid *StringGrid4;
	TTabSheet *TabSheet6;
	TStringGrid *StringGrid5;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall StringGrid2DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State);
	void __fastcall StringGrid2Click(TObject *Sender);
	void __fastcall StringGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State);
	void __fastcall StringGrid3DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State);
	void __fastcall StringGrid4DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State);
	void __fastcall StringGrid5DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
