#pragma once
#include <iostream>
#include "Muon_Tra.h"
#include <string>
#include "GlobalVariable.h"
#include "Check_Nhap.h"
#include "Ve_Hinh.h"
#include "mylib.h"

using namespace std;
// data docgia (C)
struct DocGia{
	uint MADG;
	string ho;
	string ten;
	
	uint gioitinh;
	uint trangthaithe;
	
};
typedef struct DocGia DOC_GIA;
// node doc gia (C)
struct NodeDG{
	DOC_GIA DG;
	struct NodeDG *pLeft;
	struct NodeDG *pRight;
	LIST_MT mt;
};
typedef struct NodeDG NODE_DG;
typedef NODE_DG* TREE_DG;//cay

//................................
// struct de quan ly danh sach qua han (C)
struct QuaHan{
	uint MADG;
	int songayquahan;
};

struct TenHo{
	string hoten;
	uint MADG;
};
typedef struct TenHo TEN_HO;

//................................

// khoi tao (C)
void initTREE_DG(TREE_DG &t);

// kiem tra rong (C)
bool IsEmpty(TREE_DG t);

// khoi tao node dua tren data (C)
NODE_DG* khoiTaoNodeDG(DOC_GIA dg);

//  them node vao tree DG (C)
void insertDGtoTree(TREE_DG &t, DOC_GIA dg);

// dem so luong doc gia (C)
int countDG(TREE_DG tree);

// kiem tra MSDG co ton tai hay khong (C)
bool Check_MADG(TREE_DG  t, uint MADG);

// tra ve 1 so nguyen duong ngau nhien tu dong(C)
uint Random();

// Ham tra ve  MSDG la so nguyen duong ngau nhien tu dong va khong trung.(C)
uint Random_MADG(TREE_DG t);

// find Min
//NODE_DG* FindMin(TREE_DG t);

// tim doc gia bang ma doc gia, co tra ve dia chi , khong tra ve NULL (C)
NODE_DG* Find_DG(TREE_DG t, uint MADG);
// xoa node th co 2 con (C)
void Delete2Child_DG(TREE_DG &t,NODE_DG* &c); 

// neu xoa dc, thuc hien xoa roi tra ve true , khong tra ve false (C)
bool IsDeleted_DG(TREE_DG &t, DOC_GIA dg);

//xoa  Output mot doc gia.
void Xoa_OutDG_1line(int locate);

// xoa Output 29 doc gia
void Xoa_OutDg_29lines();

// xuat thong tin cua mot DG ra man hinh console
void Output_DG(NODE_DG* dg);

// lay ten va ho phuc vu cho viec sap xep dsdg theo ten+ho(C)
string Get_TenHO(DOC_GIA dg);

//tao mang tu cay theo thu tu LNR -> thu tu tang theo maDG (C)
void Create_ArrMADG(TREE_DG t, uint* arr);
//tao mang theo ten ho theo LNR (C)
void Create_ArrTenHo(TREE_DG t, TEN_HO* arr);
// tao mang tam arr qua han (C)
void Create_ArrQuaHan(TREE_DG t, QuaHan* arr);
// doi cho 2 ptu trong mang tenho (C)
void Swap_TenHo(TEN_HO &a, TEN_HO &b);
// sort mang ten ho (C)
void QuicKsort_ARRTenHo(TEN_HO *th, int left, int right);

// ham cap nhat thong tin DG
void Update_DG(TREE_DG &t, DOC_GIA &dg, bool isEdited);

// xuat dsdg theo ten tang dan tren 1 trang
void OutputDG_PerPage1(TREE_DG t, TEN_HO *arr, int index);

//  ham xuat ds DG theo thu tu ten maDG tang dan tren 1 trang
void OutputDG_PerPage2(TREE_DG t, uint* arr, int index);
// ham xuat dsDG theo thu tu ten tang dan
void Output_ListDG1(TREE_DG t, TEN_HO *arr);

// ham xuat danh sach DG theo thu tu MADG tang dan
void Output_ListDG2(TREE_DG t, uint *arr);

// xuat danh sach cap nhat
void Menu_DocGia(TREE_DG &t);
// xuat danh sach doc gia
void InDocGia(TREE_DG t);

// quick sort mang theo thu tu keyword giam dan
void Sort_QuaHan(QuaHan *ArrQuaHan, int q, int r);

//lay danh sach qua han xu ly va xuat ra ds qua han
void DanhSachQuaHan(TREE_DG t);

//chon doc gia
int ChooseItemsb(TREE_DG &t, uint* arr, int tttrang, int tongtrang);

//tra ve ma doc gia theo pos
string traVeMaDGb(TREE_DG t,int pos, uint* arr, int trang);
void initTREE_DG(TREE_DG &t){
	nDG = 0;
	t = NULL;
}

bool IsEmpty(TREE_DG t){
	return t == NULL;
}

NODE_DG* khoiTaoNodeDG(DOC_GIA dg){
	NODE_DG *p = new NODE_DG;
	if (p == NULL) {
		return NULL;
	}
	// khoi tao danh muc sach trong node doc gia
	initList_MT(p->mt);
	p->DG = dg;
	p->pLeft = p->pRight = NULL;
	return (p);
}

void insertDGtoTree(TREE_DG &t, DOC_GIA dg){
	/// tang doc gia len 1
	if (t == NULL) {
		t = khoiTaoNodeDG(dg);
		++nDG;
	}
	else if (t->DG.MADG > dg.MADG) insertDGtoTree(t->pLeft, dg);
		else if (t->DG.MADG < dg.MADG) insertDGtoTree(t->pRight, dg);
}

int countDG(TREE_DG tree){
	int c = 1;             // ban than node duoc dem la 1;
	if (tree == NULL) return 0;
	else {
		c += countDG(tree->pLeft);
		c += countDG(tree->pRight);
		return c;
	}
}

bool Check_MADG(TREE_DG  t, uint MADG){
	if (t == NULL) return false;
	else if (t->DG.MADG == MADG) return true;
		else if (MADG < t->DG.MADG) return Check_MADG(t->pLeft, MADG);
			else return Check_MADG(t->pRight, MADG);
}

uint Random(){
	srand((uint)time(0));
	int x;
	// bo ham rand() vao vong lap moi khong bi loi tang dan, hay giam dan.
	for (int i = 0; i < 500; i++) 
		x = rand();
	return x;
}

uint Random_MADG(TREE_DG t){
	uint temp;
	do{
		temp = Random();
	} while (Check_MADG(t, temp));  // check trung , neu trung thi random lai
	return temp;
}

//NODE_DG* FindMin(TREE_DG t){
//	while (t->pLeft != NULL) t = t->pLeft;
//	return t;
//}

NODE_DG* Find_DG(TREE_DG t, uint MADG){
	while (t != NULL && t->DG.MADG != MADG)
		if (MADG < t->DG.MADG)	t = t->pLeft;
			else t = t->pRight;
	return t;
}

void Delete2Child_DG(TREE_DG &t,NODE_DG* &c){
	if(c->pLeft!=NULL) Delete2Child_DG(t,c->pLeft);
		else {
			t->DG = c->DG;
			t = c;
			c = c->pRight;
		}
}

bool IsDeleted_DG(TREE_DG &t, DOC_GIA dg){
	if (t == NULL)	return false;
	else if (dg.MADG > t->DG.MADG) return IsDeleted_DG(t->pRight, dg);
			else if (dg.MADG < t->DG.MADG) return IsDeleted_DG(t->pLeft, dg);
				else {
					NODE_DG* temp = t;
				 	if (t->pLeft == NULL) t = t->pRight;
				 		else if (t->pRight == NULL)	t = t->pLeft;
				 			else Delete2Child_DG(temp,t->pRight);
				 	ClearAll_ListMT(temp->mt);
					delete temp;
					--nDG;
					return true;
				}
}

void Xoa_OutDG_1line(int locate)
{
	gotoxy(xDisplayDG[0] + 1, yDisplay + 3 + locate);
	cout << setw(xDisplayDG[1] - xDisplayDG[0] - 1) << setfill(' ') << ' ';
	gotoxy(xDisplayDG[1] + 1, yDisplay + 3 + locate);
	cout << setw(xDisplayDG[2] - xDisplayDG[1] - 1) << setfill(' ') << ' ';
	gotoxy(xDisplayDG[2] + 4, yDisplay + 3 + locate);
	cout << setw(xDisplayDG[3] - xDisplayDG[2] - 5) << setfill(' ') << ' ';
	gotoxy(xDisplayDG[3] + 3, yDisplay + 3 + locate);
	cout << setw(xDisplayDG[4] - xDisplayDG[3] - 3) << setfill(' ') << ' ';
	gotoxy(xDisplayDG[4] + 3, yDisplay + 3 + locate);
	cout << setw(xDisplayDG[5] - xDisplayDG[4] - 3) << setfill(' ') << ' ';
}

void Xoa_OutDg_29lines()
{
	for (int i = 0; i <NUMBER_LINES; i++)
	{
		Xoa_OutDG_1line(i);
	}
}

void Output_DG(NODE_DG* dg)
{
	Xoa_OutDG_1line(locate);
	gotoxy(xDisplayDG[0] + 3, yDisplay + 3 + locate);
	cout << dg->DG.MADG;
	gotoxy(xDisplayDG[1] + 1, yDisplay + 3 + locate);
	cout << dg->DG.ho;
	gotoxy(xDisplayDG[2] + 4, yDisplay + 3 + locate);
	cout << dg->DG.ten;
	gotoxy(xDisplayDG[3] + 3, yDisplay + 3 + locate);
	(dg->DG.gioitinh == 0) ? cout << "NAM" : cout << "NU";

	gotoxy(xDisplayDG[4] + 3, yDisplay + 3 + locate);
	(dg->DG.trangthaithe == 0) ? cout << "KHOA" : cout << "HOAT DONG";
	locate++;
}

string Get_TenHO(DOC_GIA dg){
	int i = 0;
	string token;
	token = dg.ten;
    for(i;i<dg.ho.length();i++) token+= dg.ho[i];
	return token;
}

void Create_ArrMADG(TREE_DG t, uint* arr){
	if (t == NULL)	return;
	Create_ArrMADG(t->pLeft, arr); 
	arr[index++] = t->DG.MADG;
	Create_ArrMADG(t->pRight, arr);
}

void Create_ArrMADGb(TREE_DG t, uint* &arr){
	arr = (uint*)realloc(arr,countDG(t)*sizeof(uint));
	if (t == NULL)	return;
	Create_ArrMADG(t->pLeft, arr); 
	arr[index++] = t->DG.MADG;
	Create_ArrMADG(t->pRight, arr);
}

void Create_ArrTenHo(TREE_DG t, TEN_HO* arr){
	if (t == NULL)	return;
	Create_ArrTenHo(t->pLeft, arr); 
	arr[index].hoten = Get_TenHO(t->DG);
	arr[index++].MADG = t->DG.MADG;
	Create_ArrTenHo(t->pRight, arr);
}

void Create_ArrQuaHan(TREE_DG t, QuaHan* arr){
	if(t == NULL) return;
	Create_ArrQuaHan(t->pLeft,arr);
	arr[index].MADG = t->DG.MADG;
	arr[index++].songayquahan = SoNgayQuaHan(t->mt);
	Create_ArrQuaHan(t->pRight,arr);
}

void Swap_TenHo(TEN_HO &a, TEN_HO &b){
	TEN_HO temp;
	temp = a;
	a = b;
	b = temp;
}

void QuicKsort_ARRTenHo(TEN_HO *th, int left, int right){
	TEN_HO key = th[(left + right) / 2];
	int i = left, j = right;
	do {
		while (th[i].hoten < key.hoten)
			i++;
		while (th[j].hoten > key.hoten)
			j--;
		if (i <= j) {
			if (i < j) Swap_TenHo(th[i], th[j]);
			i++;
			j--;
		}
	} while (i <= j);
	if (left < j) QuicKsort_ARRTenHo(th, left, j);
	if (right > i) QuicKsort_ARRTenHo(th, i, right);
}

void Update_DG(TREE_DG &t, DOC_GIA &dg, bool isEdited){
	// hien con tro nhap
	ShowCur(true);
	normalBGColor();
	

	// cac flag dieu khien qua trinh cap nhat
	int ordinal = 0;
	bool isSave = false;
	bool isEscape = false;

	// chieu dai bang nhap
	int nngang = (int)keyBangNhapDG[0].length();

	// cac bien luu tru tam thoi
	string ho = "";
	string ten = "";
	uint phai = 3, ttthe = 3;
	uint MADG;
	/*SetBGColor(WHITE);
	SetColor(GREEN);*/
	CreateBox(X_NOTIFY, Y_NOTIFY, "THONG BAO:  ", 59);
	BangNhap(xDisplayDG[5] + 7, yDisplay, nngang, keyBangNhapDG, 12);
	BangGuides(xDisplayDG[5] + 7, yDisplay + 20, nngang, keyGuide1, 6);

	if (isEdited)
	{
		ho = dg.ho;
		ten = dg.ten;
		phai = dg.gioitinh;
		ttthe = dg.trangthaithe;
		MADG = dg.MADG;
		gotoxy((xDisplayDG[5] + 7 + nngang / 2), yDisplay + 3);
		cout << MADG;
		gotoxy((xDisplayDG[5] + 7 + nngang / 2), yDisplay + 5);
		cout << ho;
		gotoxy((xDisplayDG[5] + 7 + nngang / 2), yDisplay + 7);
		cout << ten;
		gotoxy((xDisplayDG[5] + 7 + nngang / 2), yDisplay + 9);
		(phai == 0) ? cout << phai << ":  NAM" : cout << phai << ":  NU";
		gotoxy((xDisplayDG[5] + 7 + nngang / 2), yDisplay + 11);
		(ttthe == 0) ? cout << ttthe << ":  KHOA" : cout << ttthe << ":  HOAT DONG";
	}
	if (!isEdited)
	{
		gotoxy((xDisplayDG[5] + 7 + nngang / 2), yDisplay + 3);
		MADG = Random_MADG(t);
		cout << MADG;
	}

	while (true) {

		switch (ordinal)
		{
		case 0:
			gotoxy((xDisplayDG[5] + 7 + nngang / 2), yDisplay + 5);
			NhapHo(ho, ordinal, isSave, isEscape);
			break;
		case 1:
			gotoxy((xDisplayDG[5] + 7 + nngang / 2), yDisplay + 7);
			NhapTen(ten, ordinal, isSave, isEscape);
			break;
		case 2:
			gotoxy((xDisplayDG[5] + 7 + nngang / 2), yDisplay + 9);
			Nhap(phai, NHAP_PHAI, ordinal, isSave, isEscape);
			break;
		case 3:
			gotoxy((xDisplayDG[5] + 7 + nngang / 2), yDisplay + 11);
			Nhap(ttthe, NHAP_TRANG_THAI, ordinal, isSave, isEscape);
			break;
		}
		// check Save
		if (isSave)
		{
			// cap nhat lai flag
			isSave = false;

			// check rong;
			if (ho.length() == 0)
			{
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "CAC TRUONG DU LIEU KHONG DUOC DE TRONG !!! ";
				normalBGColor();

				// quay lai va dien vao truong du lieu do
				ordinal = 0;
				continue;
			}
			else if (ten.length() == 0)
			{
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "CAC TRUONG DU LIEU KHONG DUOC DE TRONG !!! ";
				normalBGColor();

				// quay lai va dien vao truong du lieu do
				ordinal = 1;
				continue;
			}
			else if (phai == 3)
			{
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "CAC TRUONG DU LIEU KHONG DUOC DE TRONG !!! ";
				normalBGColor();
				// quay lai va dien vao truong du lieu do
				ordinal = 2;
				continue;
			}
			else if (ttthe == 3)
			{
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "CAC TRUONG DU LIEU KHONG DUOC DE TRONG !!! ";
				normalBGColor();
				ordinal = 3;
				continue;
			}
			
			dg.MADG = MADG;
			dg.ho = ChuanHoaString(ho);
			dg.ten = ChuanHoaString(ten);
			dg.gioitinh = phai;
			dg.trangthaithe = ttthe;

			if (isEdited)
			{	
				NODE_DG* p;

				// ma doc gia khong doi
				p = Find_DG(t, MADG);
				p->DG = dg;	
			}
			else
			{
				insertDGtoTree(t, dg);
			}

			// In dong thong bao .
			for (int i = 0; i < 5; i++)
			{
					SetColor(BLUE);
					gotoxy(X_NOTIFY + 15, Y_NOTIFY);
					Sleep(100);
					cout << "           SUCCESSFULLY !!! ";
			}
			normalBGColor();
			XoaMotVung(xDisplayDG[5] + 7, yDisplay, 30, 60);
			return;
		}

		if (isEscape)
		{
			XoaMotVung(xDisplayDG[5] + 7, yDisplay, 30, 60);
			return;
		}
	}
	ShowCur(false);
}

void OutputDG_PerPage1(TREE_DG t, TEN_HO *arr, int index){
	Xoa_OutDg_29lines();
	locate = 0;
	index--;
	NODE_DG* temp = NULL;
	if (t == NULL)
		return;
	else{
		for (int i =  NUMBER_LINES * index; i < NUMBER_LINES*( 1 +  index) && i < nDG; i++){
			temp = Find_DG(t, arr[i].MADG);
			Output_DG(temp);
		}
	}
	
}

void Output_ListDG1(TREE_DG t, TEN_HO *arr){
	ShowCur(false);
	nDG = countDG(t);

	// thu tu trang
	int tttrang, tongtrang;
	tttrang = 1;
	tongtrang = (nDG / NUMBER_LINES) + 1;
	OutputDG_PerPage1(t, arr, tttrang);

	int kb_hit;
	do
	{
		if (_kbhit())
		{
			kb_hit = _getch();
			if (kb_hit == 224 || kb_hit == 0)
				kb_hit = _getch();
			switch (kb_hit)
			{
			case PAGE_UP:
				(tttrang > 1) ? tttrang-- : tttrang = tongtrang;
				OutputDG_PerPage1(t, arr, tttrang);
				break;
			case PAGE_DOWN:

				(tttrang < tongtrang) ? tttrang++ : tttrang = 1;
				OutputDG_PerPage1(t, arr, tttrang);
				break;

			case ESC:
				return;
			}
		}
		gotoxy(3, 35);
		cout << "HotKey: PgUp, PgDn, ESC, KEYUP, KEYDOWN ";
		gotoxy(55, 35);
		cout << "Trang " << tttrang << " / " << tongtrang;
	} while (true);
}

void OutputDG_PerPage2(TREE_DG t, uint* arr, int index){
	Xoa_OutDg_29lines();
	locate = 0;
	NODE_DG* temp = NULL;
	index--;
	for (int i = 0 + NUMBER_LINES * index; i < (NUMBER_LINES + NUMBER_LINES * index) && i < nDG; i++)
	{
		temp = Find_DG(t, arr[i]);
		Output_DG(temp);
	}
}

void Output_ListDG2(TREE_DG t, uint *arr){
	ShowCur(false);
	nDG = countDG(t);
	// thu tu trang
	int tttrang, tongtrang;
	tttrang = 1;
	tongtrang = (nDG / NUMBER_LINES) + 1;
	OutputDG_PerPage2(t, arr, tttrang);

	int kb_hit;
	do
	{
		if (_kbhit())
		{
			kb_hit = _getch();
			if (kb_hit == 224 || kb_hit == 0)
				kb_hit = _getch();
			switch (kb_hit)
			{

			case PAGE_UP:
				(tttrang > 1) ? tttrang-- : tttrang = tongtrang;
				OutputDG_PerPage2(t, arr, tttrang);
				break;

			case PAGE_DOWN:
				(tttrang < tongtrang) ? tttrang++ : tttrang = 1;
				OutputDG_PerPage2(t, arr, tttrang);
				break;

			case  ESC:
				return;
			}
		}
		gotoxy(3, 35);
		cout << "HotKey: PgUp, PgDn, ESC, KEYUP, KEYDOWN ";
		gotoxy(55, 35);
		cout << "Trang " << tttrang << " / " << tongtrang;
	} while (true);
}

void OutputDG_PerPageb(TREE_DG t, uint* arr, int index){
    Xoa_OutDg_29lines();
	SetColor(WHITE);
	locate = 0;
	NODE_DG* temp = NULL;
	index--;
	for (int i = NUMBER_LINES * index; i < NUMBER_LINES * (index + 1) && i <nDG ; i++)
	{
		temp = Find_DG(t, arr[i]);
		Output_DG(temp);
	}
}

//string traVeMaDG(int pos, LIST_TEMPLIST l, int trang){
//	NODE_TEMPLIST* temp = NULL;
//	trang--;
//	pos=pos+ 29*trang;
//	if(pos>=nDG){
//		return "     ";
//	}
//	else{
//		temp = BinarySearch_TEMPLIST(l, pos);
//		return to_string(temp->tl.MADG);
//	}
//
//}

string traVeMaDGb(TREE_DG t,int pos, uint* arr, int trang){
    NODE_DG* temp = NULL;
    trang--;
    pos = pos+29*trang;
    if(pos>=nDG){
	return "     ";
	}
	else {
	    temp = Find_DG(t,arr[pos]);
	    return to_string(temp->DG.MADG);
	}
}

int ChooseItemsb(TREE_DG &t, uint* arr, int tttrang, int tongtrang){
    int pos = 0;
	int kb_hit;
	pos = 0;
	SetColor(LIGHT_GREEN);
	string keydg = "";
	SetBGColor(BLUE);
	keydg=traVeMaDGb(t , pos, arr, tttrang);
	gotoxy(xDisplayDG[0] + 3, yDisplay + 3 + pos);
	cout << keydg;
	normalBGColor();
	while (true)
	{
		if (_kbhit())
		{
			kb_hit = _getch();
			if (kb_hit == 224 || kb_hit == 0)
				kb_hit = _getch();

			switch (kb_hit)
			{
			case KEY_UP:
				keydg=traVeMaDGb(t, pos, arr, tttrang);
	            gotoxy(xDisplayDG[0] + 3, yDisplay + 3 + pos);
	            cout << keydg;

				(pos > 0) ? pos-- : pos = 28;

				// to mau muc moi
			    SetColor(LIGHT_GREEN);
			    SetBGColor(BLUE);
				keydg=traVeMaDGb(t, pos, arr, tttrang);
	            gotoxy(xDisplayDG[0] + 3, yDisplay + 3 + pos);
	            cout << keydg;
	            normalBGColor();
				break;

			case KEY_DOWN:
				// xoa muc truoc
				keydg=traVeMaDGb(t, pos, arr, tttrang);
	            gotoxy(xDisplayDG[0] + 3, yDisplay + 3 + pos);
	            cout << keydg;

				(pos < NUMBER_LINES - 1) ? pos++ : pos = 0;

				// to mau muc moi
				SetColor(LIGHT_GREEN);
			    SetBGColor(BLUE);
				keydg=traVeMaDGb(t, pos, arr, tttrang);
	            gotoxy(xDisplayDG[0] + 3, yDisplay + 3 + pos);
	            cout << keydg;
	            normalBGColor();
				break;

			case PAGE_UP:
				if (tttrang > 1)
				{
					tttrang--;
				}
				else
				{
					tttrang = tongtrang;
				}
				OutputDG_PerPageb(t, arr, tttrang);

				// high light hang dau.
				pos = 0;
				SetColor(LIGHT_GREEN);
			    SetBGColor(BLUE);
				keydg=traVeMaDGb(t, pos, arr, tttrang);
	            gotoxy(xDisplayDG[0] + 3, yDisplay + 3 + pos);
	            cout << keydg;
	            normalBGColor();
				break;

			case PAGE_DOWN:
				if (tttrang <  tongtrang)
				{
					tttrang++;
				}
				else
				{
					tttrang = 1;

				}
				
				OutputDG_PerPageb(t, arr, tttrang);

				// high light hang dau.
				pos = 0;
				SetColor(LIGHT_GREEN);
			    SetBGColor(BLUE);
				keydg=traVeMaDGb(t, pos, arr, tttrang);
	            gotoxy(xDisplayDG[0] + 3, yDisplay + 3 + pos);
	            cout << keydg;
	            normalBGColor();
				break;

			case ENTER:

				// tra ve vi tri pos.
				return (pos == 0 && tttrang == 1) ? pos : pos + (tttrang - 1)* NUMBER_LINES;
				break;
			case ESC:
				 return -1;
			}
		}
		ShowCur(false);
		SetColor(WHITE);
		gotoxy(30, 36);
		cout << "Trang " << tttrang << " / " << tongtrang;
		normalBGColor();
	}
}

void deleteARR(uint* arr){
    delete []arr;
}

//int Output_ListDG(TREE_DG &t, LIST_TEMPLIST &l, DOC_GIA &dg,  int &tttrang)
//{
//	NODE_TEMPLIST * temp1 = NULL;
//	NODE_DG* temp2 = NULL;
//	int choose;
//	bool check;
//
//	// nDG la so DG hien co trong cay
//	nDG = countDG(t);
//
//	// thu tu trang
//	int  tongtrang;
//	tongtrang = (nDG / NUMBER_LINES) + 1;
//	OutputDG_PerPage(t, l, tttrang);
//
//	int kb_hit;
//	//menudsdg :
//		
//	do
//	{
//		if (_kbhit())
//		{
//			kb_hit = _getch();
//			if (kb_hit == 224 || kb_hit == 0)
//				kb_hit = _getch();
//			switch (kb_hit)
//			{
//			case PAGE_UP:
//
//				(tttrang > 1) ? tttrang-- : tttrang = tongtrang;
//				OutputDG_PerPage(t, l, tttrang);
//				break;
//
//			case PAGE_DOWN:
//				(tttrang <  tongtrang) ? tttrang++ : tttrang = 1;
//				OutputDG_PerPage(t, l, tttrang);
//				break;
//
//			// them
//			case KEY_F2:
//				//Beep(600, 100);
//				Update_DG(t, dg, false);
//				ClearAll_TEMPLIST(l);
//				return 1;
//
//			// hieu chinh
//			case  KEY_F3:
//				//Beep(600, 100);
//				choose = ChooseItems(t, l, tttrang, tongtrang);
//				if(choose==-1) return 1;
//				temp1 = BinarySearch_TEMPLIST(l, choose);
//				
//				// check cac truong hop.
//				if (temp1 == NULL)
//				{
//					return 1;
//				}
//				else
//				{
//					temp2 = Find_DG(t, temp1->tl.MADG);
//					Update_DG(t, temp2->DG, true);
//					ClearAll_TEMPLIST(l);
//					return 1;
//				}
//				
//			// xoa
//			case KEY_F4:
//				//Beep(600, 100);
//				choose = ChooseItems(t, l, tttrang, tongtrang);
//				temp1 = BinarySearch_TEMPLIST(l, choose);
//
//				// truong hop khong chon doc gia nao.
//				if(choose==-1) return 1;
//				if (temp1 == NULL)
//				{
//					return 1;
//				}
//				else
//				{
//					temp2 = Find_DG(t, temp1->tl.MADG);
//					if (SoSachDangMuon(temp2->mt) > 0)
//					{
//						gotoxy(75, 20);
//						cout << "Doc Gia da muon sach nen khong duoc phep xoa !";
//						_getch();
//						gotoxy(75, 20);
//						cout << "                                                      ";
//						return 1;
//					}
//					else
//					{
//						// ch? bi?n check này d? thông báo là check thành công.....
//						check = IsDeleted_DG(t, temp2->DG);
//						ClearAll_TEMPLIST(l);
//						return 1;
//					}
//				}
//
//			case ESC:
//				//Beep(600, 100);
//				ClearAll_TEMPLIST(l);
//				return 0;
//			}
//		}
//		ShowCur(false);
//		gotoxy(30, 36);
//		cout << "Trang " << tttrang << " / " << tongtrang;
//	} while (true);
//}

int Output_ListDGb(TREE_DG &t, uint* arr, DOC_GIA &dg,  int &tttrang){
	NODE_DG* temp = NULL;
	int choose;
	bool check;

	// nDG la so DG hien co trong cay
	nDG = countDG(t);

	// thu tu trang
	int  tongtrang;
	tongtrang = (nDG / NUMBER_LINES) + 1;
	OutputDG_PerPageb(t, arr, tttrang);

	int kb_hit;
	//menudsdg :
		
	do
	{
		if (_kbhit())
		{
			kb_hit = _getch();
			if (kb_hit == 224 || kb_hit == 0)
				kb_hit = _getch();
			switch (kb_hit)
			{
			case PAGE_UP:

				(tttrang > 1) ? tttrang-- : tttrang = tongtrang;
				OutputDG_PerPageb(t, arr, tttrang);
				break;

			case PAGE_DOWN:
				(tttrang <  tongtrang) ? tttrang++ : tttrang = 1;
				OutputDG_PerPageb(t, arr, tttrang);
				break;

			// them
			case KEY_F2:
				Update_DG(t, dg, false);
				return 1;

			// hieu chinh
			case  KEY_F3:
				choose = ChooseItemsb(t, arr, tttrang, tongtrang);
				if(choose==-1) return 1;
				temp = Find_DG(t,arr[choose]);
				
				// check cac truong hop.
				if (temp == NULL)
				{
					return 1;
				}
				else
				{
					Update_DG(t, temp->DG, true);
					return 1;
				}
				
			// xoa
			case KEY_F4:
				//Beep(600, 100);
				choose = ChooseItemsb(t, arr, tttrang, tongtrang);
				temp = Find_DG(t,arr[choose]);

				// truong hop khong chon doc gia nao.
				if(choose==-1) return 1;
				if (temp == NULL)
				{
					return 1;
				}
				else
				{
					if (SoSachDangMuon(temp->mt) > 0)
					{
						gotoxy(75, 20);
						cout << "Doc Gia da muon sach nen khong duoc phep xoa !";
						_getch();
						gotoxy(75, 20);
						cout << "                                                      ";
						return 1;
					}
					else
					{
						gotoxy(92,20);
						cout<<"BAN CHAC CHAN?";
						int kb_hit1 = _getch();
						if (kb_hit1 == ENTER){
						check = IsDeleted_DG(t, temp->DG);
						}
						return 1;
					}
//					else
//					{
//						// ch? bi?n check này d? thông báo là check thành công.....
//						check = IsDeleted_DG(t, temp->DG);
//						return 1;
//					}
				}

			case ESC:
				return 0;
			}
		}
		ShowCur(false);
		gotoxy(30, 36);
		cout << "Trang " << tttrang << " / " << tongtrang;
	} while (true);
}

void Menu_DocGia(TREE_DG &t)
{
	clrscr();
	normalBGColor();
	int tttrang = 1;
	int esc = 1;
	do
	{
		clrscr();
		gotoxy(26, 1);
		cout << "   CAP NHAT DOC GIA    ";

		gotoxy(3, yHotkey );
		SetColor(WHITE);
		cout << "ESC-Thoat, F2 - Them, F3 - Sua, F4 - Xoa, F10 - Luu, PgUP, PgDn";

		normalBGColor();
		DOC_GIA dg;
		index = 0;
        uint* arrMADG = NULL;
		Create_ArrMADGb(t,arrMADG);
		DisplayDG(keyDisplayDG, 5, xDisplayDG);
		esc = Output_ListDGb(t, arrMADG, dg, tttrang);
		free(arrMADG);
	} while (esc);
}

void InDocGia(TREE_DG t)
{
	clrscr();
	normalBGColor();
	ShowCur(false);

	int c = 0;
	int chosen = 0;
	while (c != ESC)
	{
		clrscr();
		SetColor(BRIGHT_WHITE);
		gotoxy(xINDOCGIA, yINDOCGIA);
		cout << " THEO THU TU TEN_HO TANG DAN ";
		gotoxy(xINDOCGIA, yINDOCGIA + 2);
		cout << " THEO THU TU MA_DG TANG DAN  ";
		while (c != ENTER)
		{
			SetColor(LIGHT_GREEN);
			gotoxy(xINDOCGIA - 3, yINDOCGIA + chosen);
			cout << "->";
			gotoxy(xINDOCGIA + 30, yINDOCGIA + chosen);
			cout << "<-";
			c = _getch();

			if (c == KEY_UP || c == KEY_DOWN)
			{
				gotoxy(xINDOCGIA - 3, yINDOCGIA + chosen);
				cout << "   ";
				gotoxy(xINDOCGIA + 30, yINDOCGIA + chosen);
				cout << "   ";

				if (chosen == 0)
				{
					chosen = 2;
				}
				else if (chosen == 2)
				{
					chosen = 0;
				}
			}
			else if (c == ESC)
			{
				return;
			}
		}
		if (chosen == 0)
		{
			index = 0;
			TEN_HO* ArrTenHo = new TEN_HO[nDG];
			Create_ArrTenHo(t, ArrTenHo);
			DisplayDG(keyDisplayDG, 5, xDisplayDG);
			QuicKsort_ARRTenHo(ArrTenHo, 0, nDG - 1);
			Output_ListDG1(t, ArrTenHo);

			// xoa vung nho
			delete[] ArrTenHo;
		}
		else if (chosen == 2)
		{
			index = 0;

			// su dung cap phat dong.
			uint* arrMADG = new uint[nDG];
			DisplayDG(keyDisplayDG, 5, xDisplayDG);
			Create_ArrMADG(t, arrMADG);
			Output_ListDG2(t, arrMADG);

			// xoa vung nho
			delete[]arrMADG;
		}
		c = 0;
		chosen = 0;
	}
}

void Sort_QuaHan(QuaHan *ArrQuaHan, int l, int r){
	QuaHan temp;
	int i = l;
	int j = r;
	int x = ArrQuaHan[(l + r) / 2].songayquahan;
	do
	{  
		while (ArrQuaHan[i].songayquahan > x)
			i++; 
		while (ArrQuaHan[j].songayquahan < x)
			j--;  

		if (i <= j) 
		{
			temp = ArrQuaHan[i];
			ArrQuaHan[i] = ArrQuaHan[j];
			ArrQuaHan[j] = temp;
			i++;
			j--;
		}
	} while (i <= j);

	if (l<j) 
		Sort_QuaHan(ArrQuaHan, l, j);
	if (i < r)   
		Sort_QuaHan(ArrQuaHan, i, r);
}

void DanhSachQuaHan(TREE_DG t){
	//system("color 3E");
	normalBGColor();
	clrscr();
	int nDG_MAX = countDG(t);
	index = 0;
	// tao mang phu de xu ly.
	QuaHan *ArrQuaHan = new QuaHan[nDG_MAX];
	Create_ArrQuaHan(t,ArrQuaHan);

	// quicksort ArrQuaHan theo thu tu giam dan.
	Sort_QuaHan(ArrQuaHan, 0, index - 1);

	// in thong tin ra ngoai man hinh.
	string text = "DANH SACH DOC GIA MUON QUA HAN ";
	CreateBox(48, 2, text, (int)text.length());
	SetBGColor(GREEN);
	
	gotoxy(47, 2);
	cout << "DANH SACH DOC GIA MUON QUA HAN ";
	gotoxy(3, 5);
	cout << "STT";
	gotoxy(10, 5);
	cout << "MA DOC GIA";
	gotoxy(25, 5);
	cout << "HO DOC GIA";
	gotoxy(48, 5);
	cout << "TEN DOC GIA";
	gotoxy(65, 5);
	cout << "GIOI TINH";
	gotoxy(80, 5);
	cout << "TRANG THAI THE";
	gotoxy(100, 5);
	cout << "SO NGAY QUA HAN";
	normalBGColor();
	SetColor(WHITE);

	// in danh sach doc gia muon qua han theo thoi gian giam dan.
	int j = 0;
	for (int i = 0; i < index; i++)
	{
		if (ArrQuaHan[i].songayquahan > 0)
		{
			NODE_DG* p = Find_DG(t, ArrQuaHan[i].MADG);
			gotoxy(12, 6 + j);
			cout << p->DG.MADG;
			gotoxy(25, 6 + j);
			cout << p->DG.ho;
			gotoxy(50, 6 + j);
			cout << p->DG.ten;
			gotoxy(67, 6 + j);
			(p->DG.gioitinh == 0) ? cout << "NAM" : cout << "NU";
			gotoxy(82, 6 + j);
			(p->DG.trangthaithe == 0) ? cout << "KHOA" : cout << "HOAT DONG";
			gotoxy(108, 6 + j);
			cout << SoNgayQuaHan(p->mt);
			gotoxy(4, 6 + j);
			j++;
			cout << j;
		}
	}
	_getch();
	delete[] ArrQuaHan;
}
