//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <Jpeg.hpp>

#include "mouseinmaze.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int maze1 [20][20];
int **maze;
//int mark[20][20]={0};
int m,n;
int debug=0;
int button=0;
//int repeat=0;
#define maxsize 500;
//enum directions {N,NE,E,SE,S,SW,W,NW};
enum directions {E,S,SE,NE,SW,W,N,NW};      //
//enum directions {E,S,W,N,SE,NE,SW,NW};
//enum directions {E,S,W,N,SE,SW,NE,NW};
int choose=0;
typedef struct
{
	int x;
	int y;
	//int dir;
	directions dir;

}position;
position pt(int,int,directions);
position stack[350]={(0,0,N)};
int top=-1;
#define possible_direction 8

struct offset
{
	int dx;
	int dy;
};
 offset move[possible_direction];


int ** generatemaze(int ** maze, int x, int y)
{
	int direction;

	 maze[x][y] =0; // 標示此格已設定

	// Form1->Memo2->Lines->Add("(x,y,dir)="+IntToStr(x)+","+IntToStr(y)+","+IntToStr(direction));
   //	if(y-2<0 || x-2<0)
	 //	ShowMessage("y-2<0 || x-2<0 "+IntToStr(m)+"  *  "+IntToStr(n));
   //	ShowMessage("x="+IntToStr(x));
	if(x>m || y>n)
		ShowMessage("x>m || y>n "+IntToStr(m)+"  *  "+IntToStr(n));
	//ShowMessage("x="+IntToStr(x));


	while (maze[x][y+2]==1 || maze[x+2][y]==1 || maze[x][y-2]==1 || maze[x-2][y]==1) // 如果不是外牆
	{

		   //	ShowMessage("y="+IntToStr(y));
			direction = rand()%4+1; // 決定下一個位置

			if (direction==1 && maze[x][y+2]==1) // 向右走
			{
				maze[x][y+1] =0; // 拆掉右牆
				maze = generatemaze(maze, x,y+2);
				y=y+2;

			}
			else if (direction==2 && maze[x-2][y]==1) // 向上走
			{
				maze[x-1][y] =0; // 拆掉上牆
				if(x-2<0)
				{
				   //	ShowMessage("break");
					break;
				}
				maze = generatemaze(maze, x-2,y);
				x=x-2;
			}
			else if (direction==3 && maze[x][y-2]==1) // 向左走
			{
				maze[x][y-1] =0; // 拆掉右牆
				maze = generatemaze(maze, x,y-2);
				y=y-2;
			}
			else if (direction==4 && maze[x+2][y]==1) // 向下走
			{
				maze[x+1][y] =0; // 拆掉上牆
				maze = generatemaze(maze, x+2,y);
			 x=x+2;

			}

		  // 	ShowMessage("x="+IntToStr(x));
//		if(x-2<0 || y-2<0)
//		{
//			ShowMessage("break;");
//			break;
//
//	//	ShowMessage("break;");
//
//		}

	}

	 // ShowMessage("breakdown;");
	return maze;
	//ShowMessage("breakdown;drg");

}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Form1 -> Memo1->Lines->Clear();   //開始先清空
}
void push(position pt/*int element*/)
{

		//  ShowMessage("push start"+IntToStr(m)+"  *  "+IntToStr(n));
		if(top == 299)
		{
		  // ShowMessage("push return"+IntToStr(m)+"  *  "+IntToStr(n));
			return ;//StackFull();
		}
		else
		{	//stack[++top]=element;
		  // ShowMessage("push ingstart"+IntToStr(m)+"  *  "+IntToStr(n));
				stack[++top]=pt;
		   //	ShowMessage("push ing"+IntToStr(m)+"  *  "+IntToStr(n));
		}
	  //	ShowMessage("push end"+IntToStr(m)+"  *  "+IntToStr(n));



}
Boolean StackEmpty()
{
	if(top==-1)
		return true;
	else
        return false;

}
position pop()
{
	if(top==-1)
	{
		StackEmpty();
		//return stack[0];
	}
	return stack [top--];
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)  // load map
{
	Form1 -> Memo1->Lines->Clear();   //開始先清空
	FILE *fp;     // Define fp as a pointer pointing to some file (with data type FILE) in HD

	String out;

	//int m, n, i, j;
	int i, j;

	AnsiString infile;   // Use builder's string (AnsiString) to ease the conversion (into const char *)

	if (OpenDialog1->Execute())
	{
		infile = OpenDialog1->FileName;

		fp = fopen(infile.c_str(), "r+");

			  //c_str函数的傳回值是 const char *, 即把AnsiString轉成const char *給fopen使用

		fscanf(fp, "%d %d", &m, &n);    // Read in two integers m & n

		Memo1->Lines->Add("(m, n)="+IntToStr(m)+", "+IntToStr(n));

		for (i=0; i<=m; i++)    // Reda in m*n 0/1/2's into maze[][]

			for (j=0; j<=n; j++)

				fscanf(fp, "%d", &maze1[i][j]);

		fclose(fp);

		for (i=0; i<m; i++)      // Print out maze[][] in Memo1
		{
			out = "";
			for (j=0; j<n; j++) out += "  "+IntToStr(maze1[i][j]);

			Memo1->Lines->Add(out);
		}

		// Print out maze[][] in StringGrid1

		StringGrid1->RowCount = m+1;

		StringGrid1->ColCount = n+1;

		for (i=1; i<=m; i++)

			for (j=1; j<=n; j++)

				StringGrid1->Cells[j][i] = maze1[i][j];

  }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	int g_Heigh,g_Width;
	 g_Heigh = m;
	 g_Width = n;
	 int g_maze[50][50];
	 for(int i=1;i<=m;i++)
		for(int j=1 ;j<=n ;j++)
			g_maze[i][j]=maze[i][j];


	if (SaveDialog1->Execute())     //確認SaveDialog1讀取檔案成功
	{   // 取SaveDialog1所開啟的檔案名稱, 將檔案名稱轉為char格式後用fopen開啟此檔案

		AnsiString file_name = SaveDialog1->FileName;
		FILE *fp = fopen(file_name.c_str(),"w");    // "w" 表示開以寫檔的方式開啟

		//利用fprintf將g_matrix中的元素寫入fp, 當需要換行時使用putc將'\n'加入fp中

		if (fp)
		{   fprintf(fp, "%d %d", g_Heigh, g_Width);

			putc('\n', fp);

			for(int i=1 ; i<=g_Heigh ; i++)
			{
				for (int j=1 ; j<=g_Width ; j++)
				{
					fprintf(fp, "%d ", g_maze[i][j]);
				}

				putc('\n', fp);
			}

        fclose(fp);   // 寫完檔後請關檔

		}
        Memo1->Lines->Add("save the map");

	}
	else
	{
		m=1;
		n=1;

	}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
     Memo1->Lines->Add(" ");
	choose=1;
	//repeat=0;
	if (maze&&button!=1) // delete the previous maze
	{
		for (int i=0; i<m+3; i++)
			delete(maze[i]);
//		if(maze[m])
//			delete(maze[m]);
//		if(maze[m+1])
//			delete(maze[m+1]);

		delete(maze);

	}
    button=0;

	FILE *fp;

	AnsiString out, fname;
	String outt;

	int i, j;

	if (OpenDialog1->Execute())
	{     fname = OpenDialog1->FileName;

			fp = fopen(fname.c_str(), "r+");

			fscanf(fp, "%d %d", &m, &n);    // Reda integers m & n

			int m_height=m;
			  int m_width=n;
			//  m = m_height;

			  //n = m_width;

			  maze = new int * [m+3];

			  for (i=0; i<m+3; i++)  maze[i] = new int [n+3];

			  Memo1->Lines->Add("m="+IntToStr(m_height));

              Memo1->Lines->Add("n="+IntToStr(m_width));

			  for (i=0; i<m_height; i++)

					 for (j=0; j<m_width; j++)

							fscanf(fp, "%d", &maze[i+1][j+1]);

			for (i=0; i<=m_height; i++)
			{

				maze[i][0] = 2;
				maze[i][m_width+1] = 2;
			}
			for (j=0; j<=m_width; j++)
			{
					maze[0][j] = 2;
				maze[m_height+1][j] = 2;
			   //	StringGrid1->Cells[j][0] = 2;
			   //	StringGrid1->Cells[j][m_height+1] = 2;
			}
			maze[m_height+1][m_width+1] = 2;
			maze[1][0]=0;
			maze[m][n+1]=0;

			   for (i=0; i<=m_height+1; i++)      // Print maze[][] in Memo1

				{      out = "";

						for (j=0; j<=m_width+1; j++)  out += "  "+IntToStr(maze[i][j]);

						Memo1->Lines->Add(out);

				}

				fclose(fp);
//			for (i=0; i<m_height; i++)      // Print out maze[][] in Memo1
//			{
//				outt = "";
//				for (j=0; j<m_width; j++) outt += "  "+IntToStr(maze[i][j]);
//
//				Memo1->Lines->Add(outt);
//			}

		// Print out maze[][] in StringGrid1

			StringGrid1->RowCount = m_height+2;

			StringGrid1->ColCount = m_width+2;

			for (i=0; i<=m_height+1; i++)

				for (j=0; j<=m_width+1; j++)

					StringGrid1->Cells[j][i] = maze[i][j];
					/*
			for (i=0; i<=m_height; i++)
			{

				StringGrid1->Cells[0][i] = 2;
				StringGrid1->Cells[m_width+1][i] = 2;
			}
			for (j=0; j<=m_width; j++)
			{
				StringGrid1->Cells[j][0] = 2;
				StringGrid1->Cells[j][m_height+1] = 2;
			}
			StringGrid2->Cells[m_width+1][m_height+1] = 2;
			*/
		 }

		 else
		 {  Memo1->Lines->Add("Nothing happens.");
			m=1;
            n=1;
			maze = new int * [m+3];
			  for (i=0; i<m+3; i++)  maze[i] = new int [n+3];
		 }
        // ShowMessage("load in"+IntToStr(m)+"  *  "+IntToStr(n));

//		 for (i=0; i<m+2; i++)    // Release memory of **maze
//		{
//			delete maze[i];
//		}
//
//		delete maze;
    	if(maze)
	{
		int i, j;

		int grid_size = Edit3->Text.ToInt();

			if(choose==1)
			{
				for (i=0; i<=m; i++)
				{

					maze[i][0] = 2;
					maze[i][n+1] = 2;
				}
				for (j=0; j<=n; j++)
				{
					maze[0][j] = 2;
					maze[m+1][j] = 2;
				//	StringGrid1->Cells[j][0] = 2;
				//	StringGrid1->Cells[j][m_height+1] = 2;
				}
				maze[m+1][n+1] = 2;
			}
			StringGrid1->RowCount = m+2;

			StringGrid1->ColCount = n+2;

			for (i=0; i<=m+1; i++)

				for (j=0; j<=n+1; j++)

					StringGrid1->Cells[j][i] = maze[i][j];
		   if(choose==1)
		   {	for (i=0; i<=m; i++)
				{
					StringGrid2->Cells[0][i] = 2;
					StringGrid2->Cells[n+1][i] = 2;
//					StringGrid3->Cells[0][i] = 2;
//					StringGrid3->Cells[n+1][i] = 2;
//					StringGrid4->Cells[0][i] = 2;
//					StringGrid4->Cells[n+1][i] = 2;
//					StringGrid5->Cells[0][i] = 2;
//					StringGrid5->Cells[n+1][i] = 2;

				}
				for (j=0; j<=n; j++)
				{
					StringGrid2->Cells[j][0] = 2;
					StringGrid2->Cells[j][m+1] = 2;
//					StringGrid3->Cells[j][0] = 2;
//			  		StringGrid3->Cells[j][m+1] = 2;
//					StringGrid4->Cells[0][i] = 2;
//					StringGrid4->Cells[n+1][i] = 2;
//					StringGrid5->Cells[0][i] = 2;
//					StringGrid5->Cells[n+1][i] = 2;
				}
				StringGrid2->Cells[n+1][m+1] = 2;
				StringGrid2->Cells[0][1]=0;
				StringGrid2->Cells[n+1][m]=0;
			}

		StringGrid2->RowCount = m+2;   StringGrid2->ColCount = n+2;
		StringGrid3->RowCount = m+2;   StringGrid3->ColCount = n+2;
		StringGrid4->RowCount = m+2;   StringGrid4->ColCount = n+2;
		StringGrid5->RowCount = m+2;   StringGrid5->ColCount = n+2;

		StringGrid2->FixedCols = 0;   StringGrid2->FixedRows = 0;

		for (i=0; i<=m; i++) StringGrid2->RowHeights[i] = grid_size;

		for (i=0; i<=n; i++) StringGrid2->ColWidths[i] = grid_size;

		for (i=0; i<=m+2; i++)
			for (j=0; j<=n+2; j++)
			{
				StringGrid2->Cells[j][i] = StringGrid1->Cells[j][i];
				StringGrid3->Cells[j][i] = StringGrid1->Cells[j][i];
				StringGrid4->Cells[j][i] = StringGrid1->Cells[j][i];
				StringGrid5->Cells[j][i] = StringGrid1->Cells[j][i];


			}
   //	StringGrid3->RowCount = m;   StringGrid3->ColCount = n;

		StringGrid3->FixedCols=0;     StringGrid3->FixedRows=0;

		for (i=0; i<m+2; i++) StringGrid3->RowHeights[i] = grid_size;

		for (i=0; i<n+2; i++) StringGrid3->ColWidths[i] = grid_size;

  //	StringGrid4->RowCount = m;   StringGrid4->ColCount = n;

		StringGrid4->FixedCols=0;      StringGrid4->FixedRows=0;

		for (i=0; i<m+2; i++) StringGrid4->RowHeights[i] = grid_size;

		for (i=0; i<n+2; i++) StringGrid4->ColWidths[i] = grid_size;

   //	StringGrid5->RowCount = m;  StringGrid5->ColCount = n;

		StringGrid5->FixedCols=0; StringGrid5->FixedRows=0;

		StringGrid5->GridLineWidth = 0;

		for (i=0; i<m+2; i++) StringGrid5->RowHeights[i] = grid_size;

		for (i=0; i<n+2; i++) StringGrid5->ColWidths[i] = grid_size;

		StringGrid2->Refresh();

		StringGrid3->Refresh();

		StringGrid4->Refresh();

		StringGrid5->Refresh();
//	if(choose==2)
//	{	m=m+2;
//		n=n+2;
//	}
		choose=0;


	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
	if(maze)
	{
		int i, j;

		int grid_size = Edit3->Text.ToInt();

			if(choose==1)
			{
				for (i=0; i<=m; i++)
				{

					maze[i][0] = 2;
					maze[i][n+1] = 2;
				}
				for (j=0; j<=n; j++)
				{
					maze[0][j] = 2;
					maze[m+1][j] = 2;
				//	StringGrid1->Cells[j][0] = 2;
				//	StringGrid1->Cells[j][m_height+1] = 2;
				}
				maze[m+1][n+1] = 2;
			}
			StringGrid1->RowCount = m+2;

			StringGrid1->ColCount = n+2;

			for (i=0; i<=m+1; i++)

				for (j=0; j<=n+1; j++)

					StringGrid1->Cells[j][i] = maze[i][j];
		   if(choose==1)
		   {	for (i=0; i<=m; i++)
				{
					StringGrid2->Cells[0][i] = 2;
					StringGrid2->Cells[n+1][i] = 2;
//					StringGrid3->Cells[0][i] = 2;
//					StringGrid3->Cells[n+1][i] = 2;
//					StringGrid4->Cells[0][i] = 2;
//					StringGrid4->Cells[n+1][i] = 2;
//					StringGrid5->Cells[0][i] = 2;
//					StringGrid5->Cells[n+1][i] = 2;

				}
				for (j=0; j<=n; j++)
				{
					StringGrid2->Cells[j][0] = 2;
					StringGrid2->Cells[j][m+1] = 2;
//					StringGrid3->Cells[j][0] = 2;
//			  		StringGrid3->Cells[j][m+1] = 2;
//					StringGrid4->Cells[0][i] = 2;
//					StringGrid4->Cells[n+1][i] = 2;
//					StringGrid5->Cells[0][i] = 2;
//					StringGrid5->Cells[n+1][i] = 2;
				}
				StringGrid2->Cells[n+1][m+1] = 2;
				StringGrid2->Cells[0][1]=0;
				StringGrid2->Cells[n+1][m]=0;
			}

		StringGrid2->RowCount = m+2;   StringGrid2->ColCount = n+2;
		StringGrid3->RowCount = m+2;   StringGrid3->ColCount = n+2;
		StringGrid4->RowCount = m+2;   StringGrid4->ColCount = n+2;
		StringGrid5->RowCount = m+2;   StringGrid5->ColCount = n+2;

		StringGrid2->FixedCols = 0;   StringGrid2->FixedRows = 0;

		for (i=0; i<=m; i++) StringGrid2->RowHeights[i] = grid_size;

		for (i=0; i<=n; i++) StringGrid2->ColWidths[i] = grid_size;

		for (i=0; i<=m+2; i++)
			for (j=0; j<=n+2; j++)
			{
				StringGrid2->Cells[j][i] = StringGrid1->Cells[j][i];
				StringGrid3->Cells[j][i] = StringGrid1->Cells[j][i];
				StringGrid4->Cells[j][i] = StringGrid1->Cells[j][i];
				StringGrid5->Cells[j][i] = StringGrid1->Cells[j][i];


			}
   //	StringGrid3->RowCount = m;   StringGrid3->ColCount = n;

		StringGrid3->FixedCols=0;     StringGrid3->FixedRows=0;

		for (i=0; i<m+2; i++) StringGrid3->RowHeights[i] = grid_size;

		for (i=0; i<n+2; i++) StringGrid3->ColWidths[i] = grid_size;

  //	StringGrid4->RowCount = m;   StringGrid4->ColCount = n;

		StringGrid4->FixedCols=0;      StringGrid4->FixedRows=0;

		for (i=0; i<m+2; i++) StringGrid4->RowHeights[i] = grid_size;

		for (i=0; i<n+2; i++) StringGrid4->ColWidths[i] = grid_size;

   //	StringGrid5->RowCount = m;  StringGrid5->ColCount = n;

		StringGrid5->FixedCols=0; StringGrid5->FixedRows=0;

		StringGrid5->GridLineWidth = 0;

		for (i=0; i<m+2; i++) StringGrid5->RowHeights[i] = grid_size;

		for (i=0; i<n+2; i++) StringGrid5->ColWidths[i] = grid_size;

		StringGrid2->Refresh();

		StringGrid3->Refresh();

		StringGrid4->Refresh();

		StringGrid5->Refresh();
//	if(choose==2)
//	{	m=m+2;
//		n=n+2;
//	}
		choose=0;


	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid2DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{
	StringGrid2->Canvas->Brush->Color = clWhite;

    StringGrid2->Canvas->Font->Color = clBlue;

    StringGrid2->Canvas->FillRect(Rect);

	AnsiString text = StringGrid2->Cells[ACol][ARow];

	StringGrid2->Canvas->TextRect(Rect, Rect.Left+8, Rect.Top+8, text);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid2Click(TObject *Sender)
{
    TRect Recto = StringGrid1->CellRect(StringGrid1->Col, StringGrid1->Row);

     int width = Recto.Width();    int height = Recto.Height();

     Label1->Caption = "Cell: ["+IntToStr(StringGrid2->Col)+", "+IntToStr(StringGrid2->Row)+"] = "+StringGrid2->Cells[StringGrid2->Col][StringGrid2->Row];;

     Label2->Caption = "Size: "+IntToStr(width)+"X"+IntToStr(height);

     Label3->Caption = StringGrid1->Cells[StringGrid2->Col][StringGrid2->Row];

}
//---------------------------------------------------------------------------


void __fastcall TForm1::StringGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{
      AnsiString text = StringGrid1->Cells[ACol][ARow];

	if (text == "0")
		 StringGrid1->Canvas->Brush->Color = static_cast<TColor>(RGB(250, 245, 135));
	else if (text == "1")
		 StringGrid1->Canvas->Brush->Color = static_cast<TColor>(RGB(200, 205, 155));
	else if (text == "2")
		 StringGrid1->Canvas->Brush->Color = static_cast<TColor>(RGB(100, 295, 15));
	else if (text == "3")
		 StringGrid1->Canvas->Brush->Color = static_cast<TColor>(RGB(20, 295, 105));
	else if (text == "4")
		 StringGrid1->Canvas->Brush->Color = static_cast<TColor>(RGB(100, 65, 25));
	else

		 StringGrid1->Canvas->Brush->Color = clWhite;

	StringGrid1->Canvas->FillRect(Rect);

	StringGrid1->Canvas->TextRect(Rect, Rect.Left+6, Rect.Top+8, text);

}
//---------------------------------------------------------------------------


void __fastcall TForm1::StringGrid3DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{

	 String text = StringGrid3->Cells[ACol][ARow];

	 if (text == "0") StringGrid3->Canvas->Brush->Color = static_cast<TColor>(RGB(250, 245, 135));

	else if (text == "1") StringGrid3->Canvas->Brush->Color = static_cast<TColor>(RGB(176, 36, 132));

	else if (text == "2") StringGrid3->Canvas->Brush->Color = static_cast<TColor>(RGB(180, 180, 80));

	else if (text == "4") StringGrid3->Canvas->Brush->Color = static_cast<TColor>(RGB(100, 80, 200));

	else StringGrid3->Canvas->Brush->Color = static_cast<TColor>(RGB(50, 50, 50));

	StringGrid3->Canvas->FillRect(Rect);

	StringGrid3->Canvas->TextRect(Rect, Rect.Left+8, Rect.Top+8, text);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid4DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{


	 TJPEGImage * img = new TJPEGImage; //TJPEGImage * img = new TJPEGImage;      // 必須 #include <Jpeg.hpp> 切記 !  貼 JPG 必須include ==> #include <Jpeg.hpp>
//
	////img->LoadFromFile("mise.jpg");
   //	Graphics::TBitmap * bmp = new Graphics::TBitmap;

	//bmp->LoadFromFile("mise.bmp");
	String text = StringGrid4->Cells[ACol][ARow];

	 if (text == "0") StringGrid4->Canvas->Brush->Color = static_cast<TColor>(RGB(250, 245, 135));

	else if (text == "1") StringGrid4->Canvas->Brush->Color = static_cast<TColor>(RGB(176, 36, 132));

	else if (text == "2") StringGrid4->Canvas->Brush->Color = static_cast<TColor>(RGB(180, 180, 80));

	else if (text == "4") StringGrid4->Canvas->Brush->Color = static_cast<TColor>(RGB(100, 80, 200));

	else StringGrid4->Canvas->Brush->Color = static_cast<TColor>(RGB(50, 50, 50));


	StringGrid4->Canvas->FillRect(Rect);
	////if (text == "3") StringGrid4->Canvas->Draw(Rect.Left, Rect.Top, img);
   //      StringGrid4->Canvas->StretchDraw(Rect, bmp);
	//StringGrid4->Canvas->FillRect(Rect);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid5DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{
//	AnsiString text = StringGrid2->Cells[ACol][ARow];
//
//    if (text == "0")
//
//		  StringGrid5->Canvas->Brush->Color = RGB(200, 205, 155) ;
//
//	else StringGrid5->Canvas->Brush->Color = RGB(80, 80, 80);
//
//    StringGrid5->Canvas->FillRect(Rect);
	Graphics::TBitmap * bmp = new Graphics::TBitmap;

	bmp->LoadFromFile("mise.bmp");
	String text = StringGrid5->Cells[ACol][ARow];

	 if (text == "0") StringGrid5->Canvas->Brush->Color = static_cast<TColor>(RGB(250, 245, 135));

	else if (text == "1") StringGrid5->Canvas->Brush->Color = static_cast<TColor>(RGB(176, 36, 132));

	else if (text == "2") StringGrid5->Canvas->Brush->Color = static_cast<TColor>(RGB(180, 180, 80));

	else if (text == "4") StringGrid5->Canvas->Brush->Color = static_cast<TColor>(RGB(100, 80, 200));

	else StringGrid5->Canvas->Brush->Color = static_cast<TColor>(RGB(50, 50, 50));

	StringGrid5->Canvas->FillRect(Rect);
  	if (text == "3") StringGrid5->Canvas->StretchDraw(Rect, bmp);

}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button4Click(TObject *Sender)
{
		int first=0;
	if(maze)
	{	int ansx[350]={0};//top--;
		int ansy[350]={0};
		int no=0;
		for(int i=0;i<350;i++)
			stack[i]={(0,0,E)};
		int mark[100][100]={0};
		int gotoend=0,showonetime=0;
		position step;
		int i=1,j=0,u,v;
		directions d ,d1,d2;
		top=-1;
		if (CheckBox1)
			DoubleBuffered = true;
		else
			DoubleBuffered = false;

	// 畫面重新繪製時，會出現閃爍的狀況；在Panel或Form上設置DoubleBuffered的屬性為true即可
		step.x = 1;//1
		step.y = 0;//1
		step.dir=E;//E
	//step=pt(1,1,E);//step=path(1,1,E);
	  //	ShowMessage("find the tour start"+IntToStr(m)+"  *  "+IntToStr(n));
		push(step);
	// ShowMessage("find the tour second"+IntToStr(m)+"  *  "+IntToStr(n));

		while(top>-1)
		{
		//int mark[20][20]={0};


			step = pop();
		   //	Memo1->Lines->Add("pop()"+IntToStr(step.x)+" "+IntToStr(step.y));
		//if(mark[step.x][step.y]==1)//如果是走過的路徑被pop出來的話
		  //	mark[step.x][step.y]=2; //mark要設回可走直到找到另一條可走的路
//		 if(top>-1)
//		 {	position tempstep = pop();
//			mark[tempstep.x][tempstep.y]=2;//0
//		 	push(tempstep);
//		 }

			d = step.dir;
			d1=step.dir;
			i=step.x;
            j= step.y;

	   //	d2 = E;
	   // ShowMessage("step:"+IntToStr(step.x)+","+IntToStr(step.y)+"\n top="+top);
			while(d <= 7 && d1<=7)
			{
		   //	ShowMessage(d);
				if(d==N)
				{

					move[d].dx=-1;
					move[d].dy=0;
				}
				else if(d==NE)
				{
					move[d].dx=-1;
					move[d].dy=1;
				}
				else if(d==E)
				{
					move[d].dx=0;
					move[d].dy=1;
				}
				else if (d==SE)
				{
					move[d].dx=1;
					move[d].dy=1;

				}
				else if(d==S)
				{
					move[d].dx=1;
					move[d].dy=0;
				}
				else if(d==SW)
				{
					move[d].dx=1;
					move[d].dy=-1;
				}
				else if (d==W)
				{
					move[d].dx=0;
					move[d].dy=-1;
				}
				else if (d==NW)
				{
					move[d].dx=-1;
					move[d].dy=-1;

				}

				 //	ShowMessage(IntToStr(move[d].dx)+","+IntToStr(move[d].dy));
				u=i+move[d].dx;
				v=j+move[d].dy; //i,j是現在座標 x,y是direction的兩個分量
		   //	ShowMessage(IntToStr(move[d].dx)+" "+IntToStr(move[d].dy));

				 // ShowMessage(IntToStr(u)+","+IntToStr(v)+" "+IntToStr(maze[u][v]));
			   if(u>=0 && v>=0 && u<m+2 && v<n+2)
			   {    //if(maze[u][v]==0)
					  //	Memo1->Lines->Add("!"+IntToStr(u)+","+IntToStr(v)+"d:"+d);
					if(((maze[u][v]==0)||(maze[u][v]==3)) && (mark[u][v]!=1))//(u,v)可以走且不曾走過maze[u][v]==0
					{   /*
						dir = 下個可能嘗試的方向
					push ((i,j,dir));

				*/
					//ShowMessage(IntToStr(u)+" "+IntToStr(v));
					//ShowMessage(maze[u][v]);
						//mark[step.x][step.y]=1;
						step.x=i;
						step.y=j;
						//step.dir = d+1;
						step.dir = (directions)(d+1);
						push (step);  //先把下一步丟進stack裡
						//Memo1->Lines->Add(IntToStr(u)+","+IntToStr(v)+"top:"+top);
					   //	maze[u][v]=4;
						StringGrid3->Cells[v][u] = 4;
						StringGrid2->Cells[v][u] = 4;
						StringGrid1->Cells[v][u] = 4;
						StringGrid4->Cells[v][u] = 4;
						StringGrid5->Cells[v][u] = 4;
						Sleep(TrackBar1->Position);
						Sleep(TrackBar1->Position);
						StringGrid1->Refresh();
						StringGrid2->Refresh();
						StringGrid3->Refresh();
						StringGrid4->Refresh();
					   //	StringGrid5->Refresh();
						if((u==m)&& (v==n))
						{
						//成功找到出口 輸出路徑 可以停止
						//將stack內所有元素pop出
						//pop出的所有(i,j)=3;
							gotoend=1;
							while(top>-1)
							{

								position temp;
							//int a,b;
							//directions c;
								temp = pop();
								maze[temp.x][temp.y]=3;
//							for (i=0; i<=m+1; i++)
//
//								for (j=0; j<=n+1; j++)
//							{
//								StringGrid1->Cells[j][i] = maze[i][j];
//								StringGrid3->Cells[j][i] = maze[i][j];
//							}
					   //	Memo1->Lines->Add("ans = "+IntToStr(temp.x)+","+IntToStr(temp.y));

								ansx[no]= temp.x;
								ansy[no]=temp.y;
								no++;



//						StringGrid1->Refresh();
//						StringGrid3->Refresh();

							}
							for(int t=1;t<=n;t++)
								for( int s=1;s<=m ;s++)
									if(maze[t][s]!=3 && mark[t][s]!=0)
										maze[t][s]=4;
							int number=no-1;
							String text="";
							while(number>=0)
							{
								text=text+("("+IntToStr(ansx[number])+" , "+IntToStr(ansy[number])+")→");
								if(number==0)
									text=text+"the end!";
							//Memo1->Lines->Add("ans = "+IntToStr(ansx[number])+","+IntToStr(ansy[number]));

								StringGrid3->Cells[ansy[number]][ansx[number]] = maze[ansx[number]][ansy[number]];
								StringGrid2->Cells[ansy[number]][ansx[number]] = maze[ansx[number]][ansy[number]];
								StringGrid1->Cells[ansy[number]][ansx[number]] = maze[ansx[number]][ansy[number]];
								StringGrid4->Cells[ansy[number]][ansx[number]] = maze[ansx[number]][ansy[number]];
								StringGrid5->Cells[ansy[number]][ansx[number]] = maze[ansx[number]][ansy[number]];
								Sleep(TrackBar1->Position);
								Sleep(TrackBar1->Position);
								StringGrid1->Refresh();
								StringGrid2->Refresh();
								StringGrid3->Refresh();
								StringGrid4->Refresh();
							   //	StringGrid5->Refresh();

								number--;
							}
							Memo1->Lines->Add(text);
							maze[m][n]=3;
							maze[m][n+1]=3;
							for (i=0; i<=m+1; i++)
								for (j=0; j<=n+1; j++)
								{
									StringGrid1->Cells[j][i] = maze[i][j];
									StringGrid3->Cells[j][i] = maze[i][j];
									StringGrid2->Cells[j][i] = maze[i][j];
									StringGrid4->Cells[j][i] = maze[i][j];
									StringGrid5->Cells[j][i] = maze[i][j];
								}
							Memo1->Lines->Add("ans = "+IntToStr(m)+","+IntToStr(n));
							Sleep(TrackBar1->Position);
							StringGrid1->Refresh();
							StringGrid2->Refresh();
							StringGrid3->Refresh();
							StringGrid4->Refresh();
							StringGrid5->Refresh();
							break;
						}
						mark[u][v]=1;
						i=u;
						j=v;
						d=E;//dir=N;
					}
					else  //換個方向
					{
						d=(directions)(d+1);//d=d+1;
						//Memo1->Lines->Add("d++="+d);
					   //	Memo1->Lines->Add(d);
						if(d==8 && first==0)
						{	d=(directions)0;
							first=1;
						 //	Memo1->Lines->Add("d++="+d);
						}


					}


				//d=E;
				//d1=E;//d=d+1;
				}
				else  //換個方向
					d1=(directions)(d1+1);//d=d+1;

			}
			first=0;
	   //	ShowMessage("place:"+IntToStr(u)+","+IntToStr(v)+"\n top="+top);


		}
		if(gotoend==0&& showonetime==0)
		{
			showonetime++;
			Memo1->Lines->Add("can't find the exit for this maze.");
		}
   //	ShowMessage("find the tour last"+IntToStr(m)+"  *  "+IntToStr(n));

	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	int delete1=0;

	if (maze) // delete the previous maze
	{
		for (int i=0; i<m+3; i++)
			delete(maze[i]);
//		if(maze[m])
//			delete(maze[m]);
//		if(maze[m+1])
//			delete(maze[m+1]);

		delete(maze);
		delete1=1;

	}

        if(delete1==1)
		{
			delete maze;
		   // ShowMessage("delete");

		}
		ShowMessage("close");

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{  /*
		int delete1=0;
		for(int i=0; i<m+2; i++)
			for(int j=0; j<n+2; j++)
			{
				if(maze[i][j]>=0)
					delete1=1;
			}
		for (int i=0; i<m+2; i++)    // Release memory of **maze
		{
			if(delete1==1)
			{
				delete maze[i];

			}
		}

        if(delete1==1)
		{
			delete maze;
            ShowMessage("delete");

		}
		ShowMessage("close");    */

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{

   //	repeat=0;
    if (maze) // delete the previous maze
	{
		for (int i=0; i<m+3; i++)
			delete(maze[i]);
		delete(maze);
		button=1;

	}
	m=0;
    n=0;
	StringGrid1->RowCount = 0;
	StringGrid1->ColCount = 0;
	StringGrid2->RowCount = 0;
	StringGrid2->ColCount = 0;
	StringGrid3->RowCount = 0;
	StringGrid3->ColCount = 0;
	StringGrid4->RowCount = 0;
	StringGrid4->ColCount = 0;
	StringGrid5->RowCount = 0;
	StringGrid5->ColCount = 0;

    Form1 -> Memo1->Lines->Clear();   //開始先清空
}




/*	int m, n, i, j, k;

    PageControl1->ActivePage = TabSheet1;

    m = Edit1->Text.ToInt();

    n = Edit2->Text.ToInt();

	if (CheckBox1) DoubleBuffered = true;

    else DoubleBuffered = false;

    // 畫面重新繪製時，會出現閃爍的狀況；在Panel或Form上設置DoubleBuffered的屬性為true即可

    //Form1->DoubleBuffered = true;

    for (i=0; i<m; i++)

    { for (j=0; j<n; j++)

        { Sleep(TrackBar1->Position);

			k = StringGrid3->Cells[j][i].ToInt();

			StringGrid3->Cells[j][i] = 3;

			StringGrid3->Refresh();

			StringGrid3->Cells[j][i] = k;

        }

	} */

//}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{

	Memo1->Lines->Add(" ");
	AnsiString out ;
   // int startj,starti,endj,endi;
//	if(repeat==1)
//	{
//		m=m+2;
//		n=n+2;
//		repeat=0;
//	}


	choose=2;
	int i, j;

	if (maze) // delete the previous maze
	{
	   //	if(choose==1)
		//{
		for (int i=0; i<m+2; i++)
			delete(maze[i]);
		delete(maze);

	}
	m=0;
	n=0;


	m = Edit1->Text.ToInt();

	n = Edit2->Text.ToInt();
	if(m<=2 ||n<=2)
	{

		if(m<=2)
			m=13;
		if(n<=2)
			n=13;
		ShowMessage("the maze is too small, generate"+IntToStr(m)+"*"+IntToStr(n)+"maze");

	}

	maze = new int * [m+3];

	for (int i=0; i<m+3; i++)
	{
		maze[i] = new int [n+3];

	}
//	for (int c=0; c<m+3; c++)
//	{
//		for (int b=0; b<n+3; b++)
//		{
//			maze[c][b] = 0; // 初始化
//
//		}
//
//	}
//	ShowMessage(maze[m][n]);

	int starti=1;
	int startj=1;
	int endi=m-2;
	int endj=n-2;
   // ShowMessage(endi);

	int x, y;

	// srand(time(NULL));

	for (x=0; x<m; x++)
	{
		for (y=0; y<n; y++)
		{
			if (x==0 || y==0 || x==m-1 || y==n-1 ) maze[x][y] = 2; // 設定外牆

			else maze[x][y] = 1; // 初始迷宮內部

		}

	}

	//ShowMessage("generate start"+IntToStr(endi)+" "+IntToStr(endj));
	maze = generatemaze(maze, endi, endj); // 產生迷宮
     //ShowMessage("generate end");

	maze[starti][startj-1] =0; // 拆掉入口左牆

	maze[endi][endj+1] =0; // 拆掉出口右牆

	StringGrid1->RowCount = m;

	StringGrid1->ColCount = n;

	for (i=0; i<m; i++)

		for (j=0; j<n; j++)

			StringGrid1->Cells[j][i] = maze[i][j];

	for (i=0; i<m; i++)      // Print maze[][] in Memo1
	{
		out = "";

		for (j=0; j<n; j++)  out += "  "+IntToStr(maze[i][j]);

		Memo1->Lines->Add(out);

	}

	//if (choose==2) {
		m=m-2;
		n=n-2;

		//repeat=1;

	if(maze)
	{
		int i, j;

		int grid_size = Edit3->Text.ToInt();

			if(choose==1)
			{
				for (i=0; i<=m; i++)
				{

					maze[i][0] = 2;
					maze[i][n+1] = 2;
				}
				for (j=0; j<=n; j++)
				{
					maze[0][j] = 2;
					maze[m+1][j] = 2;
				//	StringGrid1->Cells[j][0] = 2;
				//	StringGrid1->Cells[j][m_height+1] = 2;
				}
				maze[m+1][n+1] = 2;
			}
			StringGrid1->RowCount = m+2;

			StringGrid1->ColCount = n+2;

			for (i=0; i<=m+1; i++)

				for (j=0; j<=n+1; j++)

					StringGrid1->Cells[j][i] = maze[i][j];
		   if(choose==1)
		   {	for (i=0; i<=m; i++)
				{
					StringGrid2->Cells[0][i] = 2;
					StringGrid2->Cells[n+1][i] = 2;
//					StringGrid3->Cells[0][i] = 2;
//					StringGrid3->Cells[n+1][i] = 2;
//					StringGrid4->Cells[0][i] = 2;
//					StringGrid4->Cells[n+1][i] = 2;
//					StringGrid5->Cells[0][i] = 2;
//					StringGrid5->Cells[n+1][i] = 2;

				}
				for (j=0; j<=n; j++)
				{
					StringGrid2->Cells[j][0] = 2;
					StringGrid2->Cells[j][m+1] = 2;
//					StringGrid3->Cells[j][0] = 2;
//			  		StringGrid3->Cells[j][m+1] = 2;
//					StringGrid4->Cells[0][i] = 2;
//					StringGrid4->Cells[n+1][i] = 2;
//					StringGrid5->Cells[0][i] = 2;
//					StringGrid5->Cells[n+1][i] = 2;
				}
				StringGrid2->Cells[n+1][m+1] = 2;
				StringGrid2->Cells[0][1]=0;
				StringGrid2->Cells[n+1][m]=0;
			}

		StringGrid2->RowCount = m+2;   StringGrid2->ColCount = n+2;
		StringGrid3->RowCount = m+2;   StringGrid3->ColCount = n+2;
		StringGrid4->RowCount = m+2;   StringGrid4->ColCount = n+2;
		StringGrid5->RowCount = m+2;   StringGrid5->ColCount = n+2;

		StringGrid2->FixedCols = 0;   StringGrid2->FixedRows = 0;

		for (i=0; i<=m; i++) StringGrid2->RowHeights[i] = grid_size;

		for (i=0; i<=n; i++) StringGrid2->ColWidths[i] = grid_size;

		for (i=0; i<=m+2; i++)
			for (j=0; j<=n+2; j++)
			{
				StringGrid2->Cells[j][i] = StringGrid1->Cells[j][i];
				StringGrid3->Cells[j][i] = StringGrid1->Cells[j][i];
				StringGrid4->Cells[j][i] = StringGrid1->Cells[j][i];
				StringGrid5->Cells[j][i] = StringGrid1->Cells[j][i];


			}
   //	StringGrid3->RowCount = m;   StringGrid3->ColCount = n;

		StringGrid3->FixedCols=0;     StringGrid3->FixedRows=0;

		for (i=0; i<m+2; i++) StringGrid3->RowHeights[i] = grid_size;

		for (i=0; i<n+2; i++) StringGrid3->ColWidths[i] = grid_size;

  //	StringGrid4->RowCount = m;   StringGrid4->ColCount = n;

		StringGrid4->FixedCols=0;      StringGrid4->FixedRows=0;

		for (i=0; i<m+2; i++) StringGrid4->RowHeights[i] = grid_size;

		for (i=0; i<n+2; i++) StringGrid4->ColWidths[i] = grid_size;

   //	StringGrid5->RowCount = m;  StringGrid5->ColCount = n;

		StringGrid5->FixedCols=0; StringGrid5->FixedRows=0;

		StringGrid5->GridLineWidth = 0;

		for (i=0; i<m+2; i++) StringGrid5->RowHeights[i] = grid_size;

		for (i=0; i<n+2; i++) StringGrid5->ColWidths[i] = grid_size;

		StringGrid2->Refresh();

		StringGrid3->Refresh();

		StringGrid4->Refresh();

		StringGrid5->Refresh();
//	if(choose==2)
//	{	m=m+2;
//		n=n+2;
//	}
		choose=0;


	}
	Memo1->Lines->Add("");

	//}
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

