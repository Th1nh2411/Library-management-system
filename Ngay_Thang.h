#pragma once
#include <time.h>
#include <iostream>
#include "mylib.h"
#include "Mark.h"
using std::cout;

// 1800 <  NAM < 9999
const int MAX_NAM = 9999;
const int MIN_NAM = 1800;
// struct ngay thang 
struct NGAY_THANG{
	uint ngay;
	uint thang;
	uint nam;
};
typedef struct NGAY_THANG NGAY_THANG;

// kiem tra nam nhuan
bool namNhuan(int year);

//xuat ngay thang
void xuatNGAY_THANG(NGAY_THANG dt, int x, int y);
// kiem tra ngay HOPLE 
int ngayHopLe(NGAY_THANG nt);

//  lay ngay gio he thong 
void LayNgayGioHT(NGAY_THANG &d);

// lay nam tu he thong 
int LayNamHT();
// so sanh khoang cach ngay x ngay y
int SoSanhNgay(NGAY_THANG x,NGAY_THANG y);
// so sanh nt1 voi ngay h hien tai
int KhoangCachNgay(NGAY_THANG nt1);

void xuatNGAY_THANG(NGAY_THANG dt, int x, int y){
	gotoxy(x, y);
	cout << dt.ngay << " /";
	gotoxy(x + 4, y);
	cout << dt.thang << " /";
	gotoxy(x + 8, y);
	cout << dt.nam;
}

int ngayHopLe(NGAY_THANG nt){
	// return 0 chi ngay sai, 1 chi thang sai , 2 chi nam sai va 3 chi ngay gio dung format
	
	if (nt.nam > MAX_NAM || nt.nam < MIN_NAM)
		return 2;
	if (nt.thang < 1 || nt.thang > 12)
		return 1;
	if (nt.ngay < 1 || nt.ngay > 31)
		return 0;

	// xu ly thang 2 voi nam  nhuan
	if (nt.thang == 2)
	{
		if (namNhuan(nt.nam))
		{
			if (nt.ngay > 29)
				return 0;
		}
		else
		{
			if (nt.ngay > 28)
			{
				return 0;
			}
		}
	}
	if ((nt.thang == 4 || nt.thang == 6 || nt.thang == 9 || nt.thang == 11) && (nt.ngay > 30))
	{
		return 0;
	}
	return 3;
}


void LayNgayGioHT(NGAY_THANG &d){
	// int ngay,thang,nam ;
	tm* today;
	time_t ltime;
	time(&ltime);
	today = localtime( &ltime );
	//localtime_s(&today, &ltime);
	d.ngay = today->tm_mday;
	d.thang = today->tm_mon + 1;
	d.nam = today->tm_year + 1900;
}

int LayNamHT(){
	tm* today;
	time_t ltime;
	time(&ltime);
	today = localtime( &ltime );
	return (today->tm_year + 1900);
}

bool namNhuan(int nam){
	if(nam % 400 == 0 || (nam % 100 != 0 && nam % 4 == 0)) return true;
	return false;
}

int soNgayConLaiTrongThang(uint ngay, uint thang, uint nam){
	switch(thang){
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31-ngay;
		case 4:
		case 6:
		case 9:
		case 11:
			return 30-ngay;
		case 2:
			if(namNhuan(nam)) return 29-ngay;
			else return 28-ngay;
	}
}

int soNgayConLaiTrongNam(uint ngay, uint thang, uint nam){
	int temp=soNgayConLaiTrongThang(ngay,thang,nam);
	for(int i=thang+1;i<=12;i++){
		temp+=soNgayConLaiTrongThang(0,i,nam);
	}
	return temp;
}

int soNgayDaQuaTrongNam(uint ngay,uint thang,uint nam){
	if(namNhuan(nam)) return 366-soNgayConLaiTrongNam(ngay,thang,nam);
	return 365-soNgayConLaiTrongNam(ngay,thang,nam);
}

int khoangCachGiua2Nam(NGAY_THANG x,NGAY_THANG y){
	int temp=soNgayConLaiTrongNam(x.ngay,x.thang,x.nam);
	for(int i=x.nam+1;i<y.nam;i++) temp+=soNgayConLaiTrongNam(0,1,i);
	temp+=soNgayDaQuaTrongNam(y.ngay,y.thang,y.nam);
	return temp;
}

int SoSanhNgay(NGAY_THANG x,NGAY_THANG y){
	if(x.nam == y.nam)
		if(x.thang > y.thang) return soNgayDaQuaTrongNam(x.ngay,x.thang,x.nam) - soNgayDaQuaTrongNam(y.ngay,y.thang,y.nam);
			else return -soNgayDaQuaTrongNam(x.ngay,x.thang,x.nam) + soNgayDaQuaTrongNam(y.ngay,y.thang,y.nam);
	else if(x.nam > y.nam) return khoangCachGiua2Nam(y,x);
	return khoangCachGiua2Nam(x,y);
}

int KhoangCachNgay(NGAY_THANG nt1){
	NGAY_THANG nt2;
	LayNgayGioHT(nt2);
	return SoSanhNgay(nt1,nt2);
}

