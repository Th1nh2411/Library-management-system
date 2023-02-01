#pragma once
#include "Ngay_Thang.h"
#include "DauSach.h"
//data cua node muon tra (C)
struct MuonTra{
	string MASACH;
	NGAY_THANG ngaymuon;
	NGAY_THANG ngaytra;
	uint trangthai = 0;
};
typedef struct MuonTra MUON_TRA;
// node muon tra (C)
struct NodeMuonTra{
	MUON_TRA data;
	struct NodeMuonTra *pNext;
};
typedef struct NodeMuonTra NODE_MT;
//list node muon tra dslk don (C)
struct ListMT{
	// so phan tu de doc tu file
	int n;
	NODE_MT *pHead;

};
typedef struct ListMT LIST_MT;

// ..... khoi tao........
void initList_MT(LIST_MT &l);

// kiem tra rong (C)
bool ListMTIsEmpty(LIST_DMS l);

// khoi tao node muon tra dua tren data (C)
NODE_MT* GetNode_MT(MUON_TRA DATA);
// them vao dau dslk don muon tra (C)
void AddHeadList_MT(LIST_MT &l, MUON_TRA data);
// xoa het cai list mt
void ClearAll_ListMT(LIST_MT &l);
// kiem tra sach co ten co ton tai? (C)
bool SearchTenSach_MT(LIST_MT lMT, string tensach);
// so sach dang muon kieu nhu n trong list muon tra (C)
int SoSachDangMuon(LIST_MT lMT);

// ham kiem tra doc gia co lam mat sach hay khong? (C)
int MatSach(LIST_MT lMT);
// so ngay muon nhieu nhat trong nhung quyen sach da muon (C)
int SoNgayMuon_Max(LIST_MT lMT);
// so ngay da qua dua tren so ngay muon max (C)
int SoNgayQuaHan(LIST_MT lMT);

void Output_MT(NODE_MT * p, int i,LIST_DAUSACH lds);

void XoaDisplay_MT(int i);

void OutputList_MT(LIST_MT lMT,LIST_DAUSACH lds);

void EffectiveMenu_MT(LIST_MT lMT, int pos, int flag, LIST_DAUSACH lds);

int chonItem_MT(LIST_MT lMT,LIST_DAUSACH lds);

//------------------------------------------prototype--------------------------------------------------

void initList_MT(LIST_MT &l)
{
	l.pHead =  NULL;
	l.n = 0;
}

bool ListMTIsEmpty(LIST_DMS l){
	return l.pHead == NULL;
}

NODE_MT* GetNode_MT(MUON_TRA DATA){
	NODE_MT *p = new NODE_MT;
	if (p == NULL) {
		return NULL;
	}
	p->data = DATA;
	p->pNext = NULL;
	return (p);
}

void AddHeadList_MT(LIST_MT &l, MUON_TRA data){
	// tao Node
//	NODE_MT *p = GetNode_MT(data);
	NODE_MT *p = new NODE_MT;
	p->data = data;
	p->pNext = NULL;
	if (l.pHead == NULL) {
		l.pHead =  p;
	}
	else{
		p->pNext = l.pHead;
		l.pHead = p;
	}
	++l.n;
}

void ClearAll_ListMT(LIST_MT &l){
	NODE_MT * p;
	while (l.pHead != NULL){
		p = l.pHead;
		l.pHead = l.pHead->pNext;
		delete p;
	}
	l.pHead = NULL;
}

//bool SearchTenSach_MT(LIST_MT lMT, string tensach){
//	for (NODE_MT * p = lMT.pHead; p != NULL; p = p->pNext)
//		if ((p->data.tensach == tensach && p->data.trangthai == 0) || (p->data.tensach == tensach && p->data.trangthai == 2))
//			return true;
//	return false;
//}
// kiem tra masach list mt co bang masach khong (C)

bool SearchMaSach_MT(LIST_MT lMT, string MaSach){
    for(NODE_MT* p = lMT.pHead; p!= NULL;p=p->pNext)
        if((checkMASACH(p->data.MASACH,MaSach) && p->data.trangthai == 0)
        || (checkMASACH(p->data.MASACH,MaSach) && p->data.trangthai == 2)) return true;
    return false;
}

int SoSachDangMuon(LIST_MT lMT){
	int i = 0;
	for (NODE_MT * p = lMT.pHead; p != NULL; p = p->pNext)
		if (p->data.trangthai == 0 || p->data.trangthai == 2)
			i++;
	return i;
}

// ham kiem tra doc gia co lam mat sach hay khong? .Co thi tra lai 1, khong thi tra lai 0 (C)
int MatSach(LIST_MT lMT){
	for (NODE_MT * p = lMT.pHead; p != NULL; p = p->pNext)
		if ( p->data.trangthai == 2)
			return 1;
	return 0;
}
// tra ve so ngay muon lau nhat cua 1 doc gia (C)
int SoNgayMuon_Max(LIST_MT lMT){
	int max = 0;
	int nngay;
	for (NODE_MT * p = lMT.pHead; p != NULL; p = p->pNext)
		if ((p->data.trangthai == 0) || (p->data.trangthai == 2)){
			nngay = KhoangCachNgay(p->data.ngaymuon);
			if (max < nngay) max = nngay;
		}
	return max;
}
// muon hon 7 ngay ham se tra ve 1 so > 0 <-> TRUE (C)
int SoNgayQuaHan(LIST_MT lMT){
	int nNgayMuonMax = SoNgayMuon_Max(lMT);
	return nNgayMuonMax - 7;
}

void Output_MT(NODE_MT *p, int i,LIST_DAUSACH lds)
{
	gotoxy(XDisplayMT[0] + 2, 21 + i);
	cout << SearchTen_DSDuaTrenMaDMS(lds,p->data.MASACH);
	gotoxy(XDisplayMT[1] + 2, 21 + i);
	cout << p->data.MASACH;

	xuatNGAY_THANG(p->data.ngaymuon, XDisplayMT[2] + 2, 21 + i);

	xuatNGAY_THANG(p->data.ngaytra, XDisplayMT[3] + 3, 21 + i);

	gotoxy(XDisplayMT[4] + 9, 21 + i);
	cout << KhoangCachNgay(p->data.ngaymuon);
	gotoxy(XDisplayMT[5] + 6, 21 + i);
	cout << Search_DMS1(SearchMASACH_DS(lds,p->data.MASACH),p->data.MASACH)->data.viTri;

	gotoxy(XDisplayMT[6] + 2, 21 + i);
	if (p->data.trangthai == 2)
		cout << " Lam Mat Sach";
	else if (KhoangCachNgay(p->data.ngaymuon) > 7)
		cout << " M. Qua 7 ngay";
	else if (p->data.trangthai == 0)
		cout << " Dang Muon";
	else if (p->data.trangthai == 1)
		cout << " Da Tra";
}

void XoaDisplay_MT(int i)
{
	gotoxy(XDisplayMT[0] + 1, 21 + i);
	cout << setw(XDisplayMT[1] - XDisplayMT[0] - 1) << setfill(' ') << " "; 
	gotoxy(XDisplayMT[1] + 1, 21 + i);
	cout << setw(XDisplayMT[2] - XDisplayMT[1] - 1) << setfill(' ') << " ";
	gotoxy(XDisplayMT[2] + 1, 21 + i);
	cout << setw(XDisplayMT[3] - XDisplayMT[2] - 1) << setfill(' ') << " ";
	gotoxy(XDisplayMT[3] + 1, 21 + i);
	cout << setw(XDisplayMT[4] - XDisplayMT[3] - 1) << setfill(' ') << " ";
	gotoxy(XDisplayMT[4] + 1, 21 + i);
	cout << setw(XDisplayMT[5] - XDisplayMT[4] - 1) << setfill(' ') << " ";
	gotoxy(XDisplayMT[5] + 1, 21 + i);
	cout << setw(XDisplayMT[6] - XDisplayMT[5] - 1) << setfill(' ') << " ";
	gotoxy(XDisplayMT[6] + 1, 21 + i);
	cout << setw(XDisplayMT[7] - XDisplayMT[6] - 1) << setfill(' ') << " ";
}

void OutputList_MT(LIST_MT lMT,LIST_DAUSACH lds)
{
	int i = 0;

	// xoa display dau sach
	for (int j = 0; j < 3; j++)
	{
		XoaDisplay_MT(j);
	}

	// thuc hien ouput
	for (NODE_MT * p = lMT.pHead; p != NULL; p = p->pNext)
	{
		if ( p->data.trangthai == 0 || p->data.trangthai == 2)
		{
			Output_MT(p, i,lds);
			i++;
		}
	}
}

void EffectiveMenu_MT(LIST_MT lMT, int pos, int flag,LIST_DAUSACH lds)
{
	int i = 0;
	ShowCur(false);

	// get so sach dang muon trong danh sach.
	int n = SoSachDangMuon(lMT);

	//down
	if (flag == 1)
	{
		for (NODE_MT * p = lMT.pHead; p != NULL; p = p->pNext)
		{
			if (p->data.trangthai == 0 || p->data.trangthai == 2)
			{
				if (i == pos)
				{
					SetBGColor(GREEN);
					SetColor(BLACK);
					Output_MT(p, i,lds);
					normalBGColor();
				}
				if (i == (pos + n - 1) % n)
				{
					
					SetColor(WHITE);
					Output_MT(p, i,lds);
				}
				i++;
			}
		}
	}
	else if (flag == 2) {

		//up
		for (NODE_MT * p = lMT.pHead; p != NULL; p = p->pNext)
		{
			if (p->data.trangthai == 0 || p->data.trangthai == 2)
			{
				if (i == pos)
				{
					SetBGColor(GREEN);
					SetColor(BLACK);
					Output_MT(p, i,lds);
					normalBGColor();
				}
				if (i == (pos + 1) % n)
				{
					SetColor(WHITE);
					Output_MT(p, i,lds);
				}
				i++;
			}
		}
	}
}




int chonItem_MT(LIST_MT lMT,LIST_DAUSACH lds)
{
	int currpos = 0;
	ShowCur(false);

	// get so sach dang muon trong danh sach.
	int n = SoSachDangMuon(lMT);
	
	/*gotoxy(XDisplayMT[0] + 2, 21 + i);
	cout << SearchTen_DSDuaTrenMaDMS(lds,p->data.MASACH);*/

	if (n == 0)
		return -1;

	// high light muc dau.
	int i = 0;
	for (NODE_MT * p = lMT.pHead; p != NULL, i != 1; p = p->pNext)
	{
		if (p->data.trangthai == 0 || p->data.trangthai == 2)
		{
			if (i == 0)
			{
				SetBGColor(GREEN);
				SetColor(BLACK);
				Output_MT(p, i,lds);
				normalBGColor();
				i++;
				
			}
		}
	}
	// xu ly.
	int kb_hit;
	while (true)
	{
		if (_kbhit())
		{
			kb_hit = _getch();
			if (kb_hit == 224 || kb_hit == 0)
			{
				kb_hit = _getch();
			}
			switch (kb_hit)
			{
			case KEY_UP:
				if (currpos > 0)
				{
					currpos = currpos - 1;
				}
				else {

					currpos = n - 1;  // vi tri hien tai bang so so sach muon.
				}
				EffectiveMenu_MT(lMT, currpos, 2,lds);
				break;

			case KEY_DOWN: 
				if (currpos <  n - 1)
				{
					currpos = currpos + 1;
				}
				else {
					currpos = 0;
				}
				EffectiveMenu_MT(lMT, currpos, 1,lds);
				break;

			case ENTER: //enter
				return currpos;
				break;
			case ESC:
				return -2;
			}
		}
	}
}

