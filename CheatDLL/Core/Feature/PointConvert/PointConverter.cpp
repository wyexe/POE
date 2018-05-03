#include "PointConverter.h"
#include <Core/Feature/Searcher/ObjectSearcher.h>
#include <Core/Feature/GameMemory/GameMemory.h>
#include <LogLib/Log.h>

#define _SELF L"PointConverter.cpp"
Point CPointConverter::GetCursorClientPos()
{
	DWORD dwInGameState = CObjectSearcher::GetGameEnv();
	return Point(ReadDWORD(dwInGameState + 当前屏幕坐标X偏移), ReadDWORD(dwInGameState + 当前屏幕坐标Y偏移));
}

Point CPointConverter::GetCursorGamePos()
{
	DWORD dwInGameState = CObjectSearcher::GetGameEnv();
	return Point(static_cast<DWORD>(ReadFloat(dwInGameState + 当前鼠标游戏坐标X) * ReadFloat(游戏坐标比例基址)), static_cast<DWORD>(ReadFloat(dwInGameState + 当前鼠标游戏坐标Y) * ReadFloat(游戏坐标比例基址)));
}

Point CPointConverter::ConvertClientPosToGamePos(_In_ CONST Point& ClientPos)
{
	DWORD dwInGameState = CObjectSearcher::GetGameEnv();

	/*
		00B44970 | 55                       | push ebp                                |
		00B44971 | 8B EC                    | mov ebp,esp                             |
		00B44973 | 83 E4 F8                 | and esp,FFFFFFF8                        |
		00B44976 | 83 EC 5C                 | sub esp,5C                              |
		00B44979 | 56                       | push esi                                |
		00B4497A | 8B F1                    | mov esi,ecx                             | nop
		00B4497C | 8D 44 24 20              | lea eax,dword ptr ss:[esp+20]           |
		00B44980 | 50                       | push eax                                |
		00B44981 | 8D 4E 10                 | lea ecx,dword ptr ds:[esi+10]           | nop
		00B44984 | E8 C7 53 99 FF           | call pathofexile.4D9D50                 |
		00B44989 | 8B 86 40 02 00 00        | mov eax,dword ptr ds:[esi+240]          | 0
		00B4498F | F3 0F 10 44 24 58        | movss xmm0,dword ptr ss:[esp+58]        | xmm0=Buffer[10]=-1013
		00B44995 | F3 0F 11 44 24 10        | movss dword ptr ss:[esp+10],xmm0        | [ESP+10]=xmm0=-1013
		00B4499B | 66 0F 6E 4D 0C           | movd xmm1,dword ptr ss:[ebp+C]          | xmm1=Pos.X
		00B449A0 | 66 0F 6E C0              | movd xmm0,eax                           | xmm0=[esi+240]
		00B449A4 | F3 0F E6 C0              | cvtdq2pd xmm0,xmm0                      | nop
		00B449A8 | C1 E8 1F                 | shr eax,1F                              | 0
		00B449AB | 8B 55 08                 | mov edx,dword ptr ss:[ebp+8]            | ResultBuffer
		00B449AE | 0F 5B C9                 | cvtdq2ps xmm1,xmm1                      | nop
		00B449B1 | F2 0F 58 04 C5 F0 EC 2F  | addsd xmm0,qword ptr ds:[eax*8+12FECF0] | 0
		00B449BA | F3 0F 10 64 24 30        | movss xmm4,dword ptr ss:[esp+30]        | xmm4 = Buffer[4]=0.588662
		00B449C0 | F3 0F 10 54 24 34        | movss xmm2,dword ptr ss:[esp+34]        | xmm2=Buffer[5]=0.588662
		00B449C6 | F3 0F 10 7C 24 50        | movss xmm7,dword ptr ss:[esp+50]        | xmm7=Buffer[12]=7318.65
		00B449CC | F3 0F 10 74 24 54        | movss xmm6,dword ptr ss:[esp+54]        | xmm6=Buffer[13]=11307.8
		00B449D2 | 66 0F 5A C0              | cvtpd2ps xmm0,xmm0                      | nop
		00B449D6 | 0F 14 FE                 | unpcklps xmm7,xmm6                      | xmm7[1]=11307.8 xmm7[2]=7318.65
		00B449D9 | F3 0F 5C C8              | subss xmm1,xmm0                         | xmm1=846-0=846
		00B449DD | F3 0F 5E 8E 38 02 00 00  | divss xmm1,dword ptr ds:[esi+238]       | xmm1=846/1=846
		00B449E5 | F3 0F 2C C1              | cvttss2si eax,xmm1                      | eax=(DWORD)846
		00B449E9 | F3 0F 10 4C 24 38        | movss xmm1,dword ptr ss:[esp+38]        | xmm1=Buffer[6]=-0.554035
		00B449EF | 03 C0                    | add eax,eax                             | eax=846*2=1692
		00B449F1 | 66 0F 6E E8              | movd xmm5,eax                           | xmm5=1692
		00B449F5 | 8B 46 04                 | mov eax,dword ptr ds:[esi+4]            | eax=游戏分辨率X
		00B449F8 | 0F 5B ED                 | cvtdq2ps xmm5,xmm5                      | nop
		00B449FB | 66 0F 6E C0              | movd xmm0,eax                           | xmm0=游戏分辨率X
		00B449FF | F3 0F E6 C0              | cvtdq2pd xmm0,xmm0                      |
		00B44A03 | C1 E8 1F                 | shr eax,1F                              |
		00B44A06 | F2 0F 58 04 C5 F0 EC 2F  | addsd xmm0,qword ptr ds:[eax*8+12FECF0] | 0
		00B44A0F | 8B 45 10                 | mov eax,dword ptr ss:[ebp+10]           | eax=Pos.Y=369
		00B44A12 | 03 C0                    | add eax,eax                             | eax=369*2=738
		00B44A14 | 66 0F 5A C0              | cvtpd2ps xmm0,xmm0                      | nop
		00B44A18 | 66 0F 6E D8              | movd xmm3,eax                           | xmm3=738
		00B44A1C | 8B 46 08                 | mov eax,dword ptr ds:[esi+8]            | eax=游戏分辨率Y=768
		00B44A1F | F3 0F 5E E8              | divss xmm5,xmm0                         | xmm5=1692/1280=1.32187
		00B44A23 | 66 0F 6E C0              | movd xmm0,eax                           | xmm0=eax=768
		00B44A27 | F3 0F E6 C0              | cvtdq2pd xmm0,xmm0                      | nop
		00B44A2B | C1 E8 1F                 | shr eax,1F                              | 0
		00B44A2E | 0F 5B DB                 | cvtdq2ps xmm3,xmm3                      | mop
		00B44A31 | F2 0F 58 04 C5 F0 EC 2F  | addsd xmm0,qword ptr ds:[eax*8+12FECF0] | 0
		00B44A3A | F3 0F 5C 2D C8 7D 2F 01  | subss xmm5,dword ptr ds:[12F7DC8]       | xmm5=1.32187-1=0.32187
		00B44A42 | 8B 44 24 10              | mov eax,dword ptr ss:[esp+10]           | eax=-1013
		00B44A46 | 66 0F 5A C0              | cvtpd2ps xmm0,xmm0                      | nop
		00B44A4A | F3 0F 5E 6E 50           | divss xmm5,dword ptr ds:[esi+50]        | xmm5=0.321875/1.44853=0.222208
		00B44A4F | F3 0F 5E D8              | divss xmm3,xmm0                         | xmm3=738/768=0.960938
		00B44A53 | F3 0F 10 44 24 20        | movss xmm0,dword ptr ss:[esp+20]        | xmm0=0.707107
		00B44A59 | F3 0F 5C 1D C8 7D 2F 01  | subss xmm3,dword ptr ds:[12F7DC8]       | xmm3=0.969375-1=-0.030625
		00B44A61 | F3 0F 59 C5              | mulss xmm0,xmm5                         | xmm0=0.707107*0.222208=0.157125
		00B44A65 | F3 0F 5E 5E 64           | divss xmm3,dword ptr ds:[esi+64]        | xmm3=-0.390625/2.41421=0.1618024
		00B44A6A | 5E                       | pop esi                                 |
		00B44A6B | 66 0F D6 3A              | movq qword ptr ds:[edx],xmm7            | ResultBuffer[0]=7318.65,11307.8
		00B44A6F | 0F 57 1D E0 ED 2F 01     | xorps xmm3,xmmword ptr ds:[12FEDE0]     | xmm3=-0.0161802 ^ -0.0 = 0.0161802
		00B44A76 | F3 0F 59 E3              | mulss xmm4,xmm3                         | xmm4=0.161802*0.588662=0.0952468
		00B44A7A | 89 42 08                 | mov dword ptr ds:[edx+8],eax            | ResultBuffer[2]=-1013
		00B44A7D | 8B C2                    | mov eax,edx                             | nop
		00B44A7F | F3 0F 59 D3              | mulss xmm2,xmm3                         | xmm2=0.588662*0.01061802=0.00952468
		00B44A83 | F3 0F 58 E0              | addss xmm4,xmm0                         | xmm4=0.00952468+0.157125=0.16665
		00B44A87 | F3 0F 59 CB              | mulss xmm1,xmm3                         | xmm1=-0.554035*0.0161802=-0.0089644
		00B44A8B | F3 0F 10 44 24 20        | movss xmm0,dword ptr ss:[esp+20]        | xmm0=Buffer[1]=-0.707107
		00B44A91 | F3 0F 59 C5              | mulss xmm0,xmm5                         | xmm0=-0.707107*0.222208=0.157125
		00B44A95 | F3 0F 58 64 24 3C        | addss xmm4,dword ptr ss:[esp+3C]        | xmm4=0.16665+Buffer[8]=0.16665+0.391762=0.558411
		00B44A9B | F3 0F 58 D0              | addss xmm2,xmm0                         | xmm2=0.00952468+(-0.157125)=-0.1476
		00B44A9F | F3 0F 10 44 24 24        | movss xmm0,dword ptr ss:[esp+24]        | xmm0=Buffer[2]=0.0
		00B44AA5 | F3 0F 59 C5              | mulss xmm0,xmm5                         | 0*Any=0
		00B44AA9 | F3 0F 58 54 24 40        | addss xmm2,dword ptr ss:[esp+40]        | xmm2=-0.1476+Buffer[9]=-0.1476+0.391762=0.244162
		00B44AAF | F3 0F 58 C8              | addss xmm1,xmm0                         | xmm1=-0.0089644+0
		00B44AB3 | 0F 14 E2                 | unpcklps xmm4,xmm2                      |
		00B44AB6 | F3 0F 58 4C 24 44        | addss xmm1,dword ptr ss:[esp+44]        | xmm1=-0.0089644+Buffer[10]=-0.0089644+0.832494=0.8235296
		00B44ABC | 66 0F D6 62 0C           | movq qword ptr ds:[edx+C],xmm4          | ResultBuffer[3]=0.558411 ,  ResultBuffer[4]=0.244161
		00B44AC1 | F3 0F 11 4C 24 18        | movss dword ptr ss:[esp+18],xmm1        | nop
		00B44AC7 | 8B 4C 24 18              | mov ecx,dword ptr ss:[esp+18]           | nop
		00B44ACB | 89 4A 14                 | mov dword ptr ds:[edx+14],ecx           | ResultBuffer[5]=xmm1=0.823529
		00B44ACE | 8B E5                    | mov esp,ebp                             |
		00B44AD0 | 5D                       | pop ebp                                 |
		00B44AD1 | C2 0C 00                 | ret C                                   |
	*/


	// 矩阵
	float CalcBuffer[16] = 
	{
		ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x0), ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x10), 0.0f, 0.0f,
		ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x4), ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x14),ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x24), 0.0f,
		ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x8), ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x18), ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x28), -0.0f,  // => 0x80000000
		ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 游戏坐标转换偏移3 + 0x0), ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 游戏坐标转换偏移3 + 0x4), ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 游戏坐标转换偏移3 + 0x8), 1.0f,
	};


	// 游戏分辨率
	DWORD ResolutionX = ReadDWORD(dwInGameState + 游戏坐标转换偏移1 + 0x4), ResolutionY = ReadDWORD(dwInGameState + 游戏坐标转换偏移1 + 0x8);

	// 计算投影矩阵……
	float fxmm5 = static_cast<float>(ClientPos.X * 2) / ResolutionX;
	fxmm5 -= ReadFloat(坐标转换基址2);
	fxmm5 /= ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 游戏坐标转换偏移5);


	float fxmm3 = static_cast<float>(ClientPos.Y * 2) / ResolutionY;
	fxmm3 -= ReadFloat(坐标转换基址2);
	fxmm3 /= ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 游戏坐标转换偏移4);
	fxmm3 = fabs(fxmm3); // xmm3(xmm3 < 0) xor -0.0f =>  fabs(xmm3)



	float fxmm2 = fxmm3 * CalcBuffer[4] + fxmm5 * CalcBuffer[0] + CalcBuffer[8];
	float fxmm4 = fxmm3 * CalcBuffer[4] + fxmm5 * CalcBuffer[1] + CalcBuffer[9];
	float fxmm1 = fxmm3 * CalcBuffer[6] + CalcBuffer[10];
	float fxmm0 = fabs(CalcBuffer[14]) - fabs(ReadFloat(dwInGameState + 游戏坐标转换偏移2));
	

	fxmm0 /= fxmm1;


	/*
		007E6E19 | 51                       | push ecx                                |
		007E6E1A | 8B C8                    | mov ecx,eax                             |
		007E6E1C | E8 3F 1B 14 00           | call pathofexile.928960                 |
		007E6E21 | F3 0F 10 44 24 14        | movss xmm0,dword ptr ss:[esp+14]        | xmm0=1013
		007E6E27 | F3 0F 11 44 24 14        | movss dword ptr ss:[esp+14],xmm0        |
		007E6E2D | D8 6C 24 14              | fsubr dword ptr ss:[esp+14]             | xmm0=abs([EBX+194c]) = 1013-abs[EBX+1924]=981.75
		007E6E31 | F3 0F 10 4F 08           | movss xmm1,dword ptr ds:[edi+8]         | xmm1=0.822932 = [EBX+1958] = Result[5]
		007E6E36 | D8 B3 58 19 00 00        | fdiv dword ptr ds:[ebx+1958]            | xmm0 / 0.822932
		007E6E3C | F3 0F 10 17              | movss xmm2,dword ptr ds:[edi]           | xmm2=0.428617=[EBX+1950]
		007E6E40 | F3 0F 10 67 04           | movss xmm4,dword ptr ds:[edi+4]         | xmm4=0.375225=[ebx+1954]
		007E6E45 | F3 0F 10 1D E8 80 2F 01  | movss xmm3,dword ptr ds:[12F80E8]       | xmm3=100.0f=[12F80E8]
		007E6E4D | D9 5C 24 14              | fstp dword ptr ss:[esp+14]              | [ESP+14] = xmm0 = 1192.99
		007E6E51 | F3 0F 10 44 24 14        | movss xmm0,dword ptr ss:[esp+14]        | xmm0 = [ESP+14] = 1192.99
		007E6E57 | F3 0F 59 C8              | mulss xmm1,xmm0                         | 1192.99*0.822932=981.75
		007E6E5B | F3 0F 59 D0              | mulss xmm2,xmm0                         | 0.428617*1192.99=511.337
		007E6E5F | F3 0F 58 8B 4C 19 00 00  | addss xmm1,dword ptr ds:[ebx+194C]      | 981.75-1013=-31.25
		007E6E67 | F3 0F 59 E0              | mulss xmm4,xmm0                         | 0.375225*1192.99=447.639
		007E6E6B | F3 0F 58 93 44 19 00 00  | addss xmm2,dword ptr ds:[ebx+1944]      | 511.337+7329.52=7840.857
		007E6E73 | F3 0F 58 A3 48 19 00 00  | addss xmm4,dword ptr ds:[ebx+1948]      | 447.64+11242.6=11690.24
		007E6E7B | 0F 28 C1                 | movaps xmm0,xmm1                        | xmm0=-31.25
		007E6E7E | F3 0F 5C 0D 24 83 2F 01  | subss xmm1,dword ptr ds:[12F8324]       | -31.25-400.0=-431.25
		007E6E86 | F3 0F 58 C3              | addss xmm0,xmm3                         | -31.25+100=68.75
		007E6E8A | F3 0F 11 93 3C 19 00 00  | movss dword ptr ds:[ebx+193C],xmm2      | 7840.86
		007E6E92 | F3 0F 11 54 24 4C        | movss dword ptr ss:[esp+4C],xmm2        |
		007E6E98 | F3 0F 11 A3 40 19 00 00  | movss dword ptr ds:[ebx+1940],xmm4      | 11690.2
		007E6EA0 | 33 DB                    | xor ebx,ebx                             |
		007E6EA2 | 33 C9                    | xor ecx,ecx                             |
	*/

	// X 
	fxmm2 *= fxmm0;
	fxmm2 += ReadFloat(dwInGameState + 游戏坐标X转换偏移);
	fxmm2 *= ReadFloat(游戏坐标比例基址);


	// Y
	fxmm4 *= fxmm0;
	fxmm4 += ReadFloat(dwInGameState + 游戏坐标Y转换偏移);
	fxmm4 *= ReadFloat(游戏坐标比例基址);

	return Point(static_cast<DWORD>(fxmm2), static_cast<DWORD>(fxmm4));
}

BOOL CPointConverter::ConvertGamePosToClientPos(_In_ CONST Point& GamePos, _Out_ Point& ClientPos)
{
	DWORD dwInGameState = CObjectSearcher::GetGameEnv();

	float fPosX = static_cast<float>(GamePos.X) / ReadFloat(游戏坐标比例基址);
	float fPosY = static_cast<float>(GamePos.Y) / ReadFloat(游戏坐标比例基址);

	fPosX -= ReadFloat(dwInGameState + 游戏坐标X转换偏移);
	fPosY -= ReadFloat(dwInGameState + 游戏坐标Y转换偏移);

	float fxmm0 = fabs(ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 游戏坐标转换偏移3 + 0x8)) - fabs(ReadFloat(dwInGameState + 游戏坐标转换偏移2));
	fPosX /= fxmm0;
	fPosY /= fxmm0;


	// 解二元一次方程……
	// fxmm5 = (Pos.X - Pos.Y) * (fxmm3 * CalcBuffer[6] + CalcBuffer[10]) / (CalcBuffer[0] - CalcBuffer[1]) 
	// (Pos.X - Pos.Y) / (CalcBuffer[0] - CalcBuffer[1])  => A
	float A = (fPosX - fPosY) / (ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x0) - ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x10));

	// fxmm5 = A * (fxmm3 * CalcBuffer[6] + CalcBuffer[10])
	// fxmm5 = A * fxmm3 * CalcBuffer[6] + A * CalcBuffer[10]

	//A * CalcBuffer[6] => B
	//A * CalcBuffer[10] = > C

	float B = A * ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x24);
	float C = A * ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x28);

	// fxmm5 = B * fxmm3 + C

	/*
		fxmm2 = fxmm5 * CalcBuffer[0] + fxmm3 * CalcBuffer[4] + CalcBuffer[8]
		fxmm4 = fxmm3 * CalcBuffer[4] + fxmm5 * CalcBuffer[1] + CalcBuffer[9]
		fxmm1 = fxmm3 * CalcBuffer[6] + CalcBuffer[10]

		Pos.X * xmm1 = fxmm5 * CalcBuffer[0] + fxmm3 * CalcBuffer[4] + CalcBuffer[8]
		Pos.Y * xmm1 = fxmm5 * CalcBuffer[1] + fxmm3 + CalcBuffer[4] + CalcBuffer[9]

		Pos.X * xmm1 = (B * fxmm3 + C) * CalcBuffer[0] + fxmm3 * CalcBuffer[4] + CalcBuffer[8]
		Pos.X * xmm1 = B * fxmm3 * CalcBuffer[0] + C * CalcBuffer[0] + fxmm3 * CalcBuffer[4] + CalcBuffer[8]

		B * CalcBuffer[0] => D
		C * CalcBuffer[0] => E

		Pos.X * xmm1 = D * xmm3 + E + fxmm3 * CalcBuffer[4] + CalcBuffer[8]
		Pos.X * xmm1 = xmm3 * (D + CalcBuffer[4]) + E + CalcBuffer[8]

		D + CalcBuffer[4] => F
		E + CalcBuffer[8] => G

		Pos.X * xmm1 = xmm3 * F + G

		Pos.X * (fxmm3 * CalcBuffer[6] + CalcBuffer[10]) = xmm3 * F + G
		Pos.X * CalcBuffer[6] * xmm3  + Pos.X * CalcBuffer[10] = xmm3 * F + G

		Pos.X * CalcBuffer[6] => H
		Pos.X * CalcBuffer[10] => I

		H * xmm3 + I = xmm3 * F + G
		I - G = xmm3 * F - H * xmm3
		I - G = xmm3 * (F - H)
		xmm3 = (I - G) / (F - H)
	*/

	float D = B * ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x0);
	float E = C * ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x0);
	float F = D + ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x4);
	float G = E + ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x8);
	float H = fPosX * ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x24);
	float I = fPosX * ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x28);
	float fxmm3 = (I - G) / (F - H);


	float fScreenY = fxmm3 * -1;
	fScreenY *= ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 游戏坐标转换偏移4);
	fScreenY += ReadFloat(坐标转换基址2);
	fScreenY *= static_cast<float>(ReadDWORD(dwInGameState + 游戏坐标转换偏移1 + 0x8));
	fScreenY /= 2;
	if (fScreenY >= ReadDWORD(dwInGameState + 游戏坐标转换偏移1 + 0x8))
	{
		// LOG_C_D(L"Y轴已经超出屏幕坐标了!");
		return FALSE;
	}

	// fxmm5 = B * fxmm3 + C
	float fxmm5 = B * fxmm3 + C;
	float fScreenX = fxmm5 * ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 游戏坐标转换偏移5);
	fScreenX += ReadFloat(坐标转换基址2);
	fScreenX *= static_cast<float>(ReadDWORD(dwInGameState + 游戏坐标转换偏移1 + 0x4));
	fScreenX /= 2;
	if (fScreenX >= static_cast<float>(ReadDWORD(dwInGameState + 游戏坐标转换偏移1 + 0x4)))
	{
		//LOG_C_D(L"X轴已经超出屏幕坐标了!");
		return FALSE;
	}

	
	ClientPos.X = static_cast<DWORD>(fScreenX);
	ClientPos.Y = static_cast<DWORD>(fScreenY);
	return TRUE;
}

/*
float StaticBuffer[] = { 1.0f,1.0f,1.0f,1.0f };
__declspec(naked) void WINAPI CalcScreenToClientBuffer(LPVOID)
{
	__asm
	{
		PUSH EBP;
		MOV EBP, ESP;
		MOV EAX, dword ptr[ESP + 0x8];
		AND ESP, 0xFFFFFFF0;
		SUB ESP, 0x130;

		movss   xmm2, dword ptr[ecx + 3Ch]
			movss   xmm0, dword ptr[ecx + 34h]
			movss   xmm1, dword ptr[ecx + 2Ch]
			movss   xmm7, dword ptr[ecx + 18h]
			movss   xmm3, dword ptr[ecx + 8]
			movss   xmm5, dword ptr[ecx + 24h]
			movss   xmm6, dword ptr[ecx + 1Ch]
			movss   xmm4, dword ptr[ecx + 14h]
			movss   dword ptr[esp + 0A4h], xmm2
			movss   dword ptr[esp + 0ACh], xmm2
			movss   dword ptr[esp + 24h], xmm2
			movss   dword ptr[esp + 30h], xmm3
			movss   dword ptr[esp + 34h], xmm3
			movss   xmm3, dword ptr[ecx]
			movss   dword ptr[esp + 38h], xmm7
			movss   dword ptr[esp + 3Ch], xmm7
			movups  xmm2, [esp + 30h]
			movss   xmm7, dword ptr[ecx + 8]
			movss   dword ptr[esp + 4], xmm0
			movss   dword ptr[esp + 0Ch], xmm0
			movss   dword ptr[esp + 2Ch], xmm0
			movss   dword ptr[esp + 0A0h], xmm1
			movss   dword ptr[esp + 0A8h], xmm1
			movups  xmm0, xmmword ptr[esp + 0A0h]
			movss   dword ptr[esp + 80h], xmm3
			mulps   xmm2, xmm0
			movss   dword ptr[esp + 84h], xmm3
			movss   xmm3, dword ptr[ecx + 10h]
			movss   dword ptr[esp + 88h], xmm3
			movss   dword ptr[esp + 8Ch], xmm3
			movss   xmm3, dword ptr[ecx]
			movups  xmmword ptr[esp + 0C0h], xmm2
			movups  xmm2, xmmword ptr[esp + 80h]
			movss   dword ptr[esp], xmm5
			movss   dword ptr[esp + 8], xmm5
			movups  xmm0, xmmword ptr[esp]
			movss   dword ptr[esp + 10h], xmm7
			movss   xmm7, dword ptr[ecx + 28h]
			movss   dword ptr[esp + 18h], xmm3
			movss   xmm3, dword ptr[ecx + 20h]
			mulps   xmm2, xmm0
			movss   dword ptr[esp + 20h], xmm6
			movss   dword ptr[esp + 14h], xmm7
			movss   dword ptr[esp + 1Ch], xmm3
			movups  xmm7, xmmword ptr[esp + 10h]
			movss   dword ptr[esp + 28h], xmm4
			movups  xmm0, xmmword ptr[esp + 20h]
			movss   dword ptr[esp + 18h], xmm6
			movss   dword ptr[esp + 1Ch], xmm6
			movss   xmm6, dword ptr[ecx + 30h]
			movups  xmmword ptr[esp + 0A0h], xmm2
			movss   xmm2, dword ptr[ecx + 28h]
			mulps   xmm7, xmm0
			movss   xmm0, dword ptr[ecx + 38h]
			movss   dword ptr[esp + 4], xmm6
			movss   dword ptr[esp + 0Ch], xmm6
			movss   xmm6, dword ptr[ecx + 18h]
			movss   dword ptr[esp + 20h], xmm2
			movss   dword ptr[esp + 24h], xmm0
			movss   dword ptr[esp + 28h], xmm2
			movss   xmm2, dword ptr[ecx + 0Ch]
			movss   dword ptr[esp + 2Ch], xmm0
			movss   dword ptr[esp], xmm3
			movss   dword ptr[esp + 8], xmm3
			movss   xmm3, dword ptr[ecx + 4]
			movss   dword ptr[esp + 80h], xmm6
			movss   xmm6, dword ptr[ecx + 10h]
			movss   dword ptr[esp + 84h], xmm0
			movss   xmm0, dword ptr[ecx + 30h]
			movss   dword ptr[esp + 10h], xmm2
			movss   dword ptr[esp + 14h], xmm2
			movss   dword ptr[esp + 30h], xmm3
			movss   dword ptr[esp + 34h], xmm3
			movss   dword ptr[esp + 38h], xmm4
			movss   dword ptr[esp + 3Ch], xmm4
			movss   dword ptr[esp + 88h], xmm6
			movss   dword ptr[esp + 8Ch], xmm0
			movss   dword ptr[esp + 40h], xmm2
			movss   dword ptr[esp + 44h], xmm1
			movss   dword ptr[esp + 48h], xmm3
			movss   dword ptr[esp + 4Ch], xmm5
			movups  xmm0, xmmword ptr[esp + 10h]
			movups  xmm3, xmmword ptr[esp + 20h]
			movups  xmm2, xmmword ptr[esp]
			movups  xmm1, xmmword ptr[esp + 80h]
			mulps   xmm3, xmm0
			movups  xmm0, xmmword ptr[esp + 30h]
			movss   dword ptr[esp + 18h], xmm6
			mulps   xmm2, xmm0
			movups  xmm0, xmmword ptr[esp + 40h]
			movss   xmm6, dword ptr[ecx + 1Ch]
			mulps   xmm1, xmm0
			movups  xmm0, xmmword ptr[esp + 0C0h]
			movss   dword ptr[esp + 30h], xmm6
			subps   xmm0, xmm3
			movss   dword ptr[esp + 3Ch], xmm6
			movss   xmm6, dword ptr[ecx + 28h]
			subps   xmm7, xmm1
			movss   xmm3, dword ptr[ecx + 20h]
			movss   dword ptr[esp + 44h], xmm5
			movss   dword ptr[esp + 70h], xmm6
			movss   xmm6, dword ptr[ecx + 8]
			movups  xmmword ptr[esp + 0C0h], xmm0
			movups  xmm0, xmmword ptr[esp + 0A0h]
			movups  xmm1, xmmword ptr[esp + 0C0h]
			subps   xmm0, xmm2
			movss   dword ptr[esp + 74h], xmm6
			movss   xmm6, dword ptr[ecx + 18h]
			movaps  xmm2, xmm1
			movups  xmmword ptr[esp + 0D0h], xmm7
			movaps  xmm5, xmm1
			shufps  xmm2, xmm1, 55h
			movups  xmmword ptr[esp + 0A0h], xmm0
			movss   xmm0, dword ptr[ecx + 4]
			movss   dword ptr[esp + 48h], xmm0
			movaps  xmm0, xmm7
			shufps  xmm0, xmm7, 55h
			movaps  xmm7, xmm1
			movaps  xmmword ptr[esp + 0F0h], xmm0
			movss   dword ptr[esp + 20h], xmm0
			shufps  xmm5, xmm1, 0FFh
			movss   dword ptr[esp + 4], xmm0
			movss   xmm0, dword ptr[ecx + 2Ch]
			shufps  xmm7, xmm1, 0AAh
			movss   dword ptr[esp + 2Ch], xmm1
			movups  xmm1, xmmword ptr[esp + 0D0h]
			movss   dword ptr[esp + 34h], xmm0
			movss   xmm0, dword ptr[ecx + 0Ch]
			movss   dword ptr[esp + 10h], xmm3
			movss   xmm3, dword ptr[ecx]
			movss   dword ptr[esp + 40h], xmm4
			movss   dword ptr[esp + 4Ch], xmm4
			movups  xmm4, xmmword ptr[esp + 0A0h]
			movss   dword ptr[esp + 38h], xmm0
			movaps  xmm0, xmm1
			shufps  xmm0, xmm1, 0FFh
			movaps  xmm1, xmm4
			movss   dword ptr[esp + 78h], xmm6
			movss   xmm6, dword ptr[ecx + 8]
			movss   dword ptr[esp + 14h], xmm3
			movss   dword ptr[esp + 1Ch], xmm3
			movaps  xmm3, xmm4
			shufps  xmm3, xmm4, 0FFh
			movss   dword ptr[esp + 7Ch], xmm6
			movaps  xmm6, xmm4
			shufps  xmm1, xmm4, 55h
			movss   dword ptr[esp + 24h], xmm2
			movaps  xmmword ptr[esp + 100h], xmm5
			movss   dword ptr[esp + 28h], xmm5
			movss   dword ptr[esp], xmm5
			movss   dword ptr[esp + 8], xmm2
			movss   dword ptr[esp + 0Ch], xmm7
			movaps  xmmword ptr[esp + 110h], xmm0
			movss   dword ptr[esp + 50h], xmm0
			movss   dword ptr[esp + 54h], xmm1
			movaps  xmmword ptr[esp + 120h], xmm3
			movss   dword ptr[esp + 58h], xmm3
			movss   dword ptr[esp + 5Ch], xmm4
			movss   dword ptr[esp + 60h], xmm3
			movss   dword ptr[esp + 64h], xmm0
			movss   dword ptr[esp + 68h], xmm1
			shufps  xmm6, xmm4, 0AAh
			movups  xmm0, xmmword ptr[esp + 20h]
			movups  xmm4, xmmword ptr[esp + 40h]
			movss   dword ptr[esp + 6Ch], xmm6
			mulps   xmm4, xmm0
			movups  xmm0, xmmword ptr[esp]
			movss   dword ptr[esp + 44h], xmm2
			movups  xmmword ptr[esp + 0B0h], xmm4
			movups  xmm4, xmmword ptr[esp + 10h]
			movss   dword ptr[esp + 10h], xmm3
			mulps   xmm4, xmm0
			movups  xmm0, xmmword ptr[esp + 50h]
			movss   xmm3, dword ptr[ecx + 28h]
			movups  xmmword ptr[esp + 80h], xmm4
			movups  xmm4, xmmword ptr[esp + 30h]
			movss   dword ptr[esp + 94h], xmm3
			mulps   xmm4, xmm0
			movups  xmm0, xmmword ptr[esp + 70h]
			movss   dword ptr[esp + 40h], xmm7
			movups  xmmword ptr[esp + 0E0h], xmm4
			movups  xmm4, xmmword ptr[esp + 60h]
			movss   dword ptr[esp + 60h], xmm5
			movss   xmm5, dword ptr[ecx + 30h]
			mulps   xmm4, xmm0
			movss   xmm0, dword ptr[ecx + 34h]
			movss   dword ptr[esp + 74h], xmm0
			movss   xmm0, dword ptr[ecx + 14h]
			movss   dword ptr[esp + 78h], xmm0
			movups  xmm0, xmmword ptr[esp + 0C0h]
			movss   dword ptr[esp + 50h], xmm5
			movss   xmm5, dword ptr[ecx + 20h]
			movss   dword ptr[esp + 64h], xmm0
			movss   dword ptr[esp + 4Ch], xmm0
			movss   xmm0, dword ptr[ecx + 3Ch]
			movss   dword ptr[esp + 24h], xmm0
			movss   xmm0, dword ptr[ecx + 1Ch]
			movups  xmmword ptr[esp + 30h], xmm4
			movss   xmm4, dword ptr[ecx + 24h]
			movss   dword ptr[esp + 54h], xmm5
			movss   xmm5, dword ptr[ecx + 30h]
			movss   dword ptr[esp + 28h], xmm0
			movups  xmm0, xmmword ptr[esp + 0A0h]
			movss   dword ptr[esp + 70h], xmm4
			movss   dword ptr[esp + 7Ch], xmm4
			movups  xmm4, xmmword ptr[esp + 0D0h]
			movss   dword ptr[esp + 58h], xmm5
			movss   xmm5, dword ptr[ecx + 10h]
			movss   dword ptr[esp + 0Ch], xmm0
			movss   dword ptr[esp + 68h], xmm2
			movss   xmm2, dword ptr[ecx + 2Ch]
			movss   dword ptr[esp + 5Ch], xmm5
			movaps  xmm5, xmm4
			movups  xmm3, xmmword ptr[esp + 50h]
			movss   dword ptr[esp + 14h], xmm0
			shufps  xmm5, xmm4, 0AAh
			movss   dword ptr[esp + 6Ch], xmm4
			movups  xmm0, xmmword ptr[esp + 60h]
			movss   dword ptr[esp + 48h], xmm4
			movups  xmm4, xmmword ptr[esp + 70h]
			movss   dword ptr[esp + 20h], xmm2
			movss   dword ptr[esp + 2Ch], xmm2
			movss   xmm2, dword ptr[ecx + 38h]
			mulps   xmm4, xmm0
			movups  xmm0, xmmword ptr[esp + 40h]
			movss   dword ptr[esp + 90h], xmm2
			movss   dword ptr[esp + 98h], xmm2
			movss   xmm2, dword ptr[ecx + 18h]
			mulps   xmm3, xmm0
			movss   dword ptr[esp + 18h], xmm1
			movss   dword ptr[esp + 9Ch], xmm2
			movups  xmm2, xmmword ptr[esp + 20h]
			movss   dword ptr[esp + 1Ch], xmm5
			movups  xmm0, xmmword ptr[esp + 10h]
			movss   dword ptr[esp + 4], xmm1
			mulps   xmm2, xmm0
			movups  xmm0, xmmword ptr[esp + 90h]
			movss   dword ptr[esp], xmm6
			movss   dword ptr[esp + 8], xmm5
			movups  xmm1, [esp]
			mulps   xmm1, xmm0
			movups  xmm0, xmmword ptr[esp + 0B0h]
			subps   xmm0, xmm4
			movups  xmmword ptr[esp + 0B0h], xmm0
			movups  xmm0, xmmword ptr[esp + 80h]
			movups  xmm4, xmmword ptr[esp + 0E0h]
			subps   xmm0, xmm3
			movss   dword ptr[esp + 20h], xmm6
			movss   xmm3, dword ptr[ecx]
			subps   xmm4, xmm2
			movss   xmm2, dword ptr[ecx + 10h]
			movss   dword ptr[esp + 60h], xmm2
			movss   xmm2, dword ptr[ecx + 30h]
			movups  xmmword ptr[esp + 80h], xmm0
			movups  xmm0, xmmword ptr[esp + 30h]
			movss   dword ptr[esp + 2Ch], xmm6
			subps   xmm0, xmm1
			movss   dword ptr[esp + 70h], xmm7
			movss   xmm1, dword ptr[ecx + 4]
			movss   dword ptr[esp + 94h], xmm1
			movss   dword ptr[esp + 9Ch], xmm1
			movups  xmm1, xmmword ptr[esp + 0D0h]
			movups  xmmword ptr[esp + 30h], xmm0
			movss   xmm0, dword ptr[ecx + 34h]
			movss   dword ptr[esp + 90h], xmm0
			movss   dword ptr[esp + 98h], xmm0
			movaps  xmm0, xmmword ptr[esp + 0F0h]
			movss   dword ptr[esp + 74h], xmm0
			movss   dword ptr[esp + 50h], xmm0
			movups  xmm0, xmmword ptr[esp + 0C0h]
			movups  xmm6, xmmword ptr[esp + 90h]
			movss   dword ptr[esp + 54h], xmm0
			movaps  xmm0, xmmword ptr[esp + 100h]
			movss   dword ptr[esp + 58h], xmm0
			movss   xmm0, dword ptr[ecx + 3Ch]
			movss   dword ptr[esp + 40h], xmm0
			movss   dword ptr[esp + 48h], xmm0
			movaps  xmm0, xmmword ptr[esp + 110h]
			movss   dword ptr[esp + 78h], xmm1
			movss   dword ptr[esp + 5Ch], xmm1
			movss   xmm1, dword ptr[ecx + 0Ch]
			movss   dword ptr[esp + 10h], xmm0
			movss   dword ptr[esp + 24h], xmm0
			movups  xmm0, xmmword ptr[esp + 0A0h]
			movss   dword ptr[esp + 44h], xmm1
			movss   dword ptr[esp + 4Ch], xmm1
			movss   xmm1, dword ptr[ecx + 18h]
			movss   dword ptr[esp + 14h], xmm0
			movaps  xmm0, xmmword ptr[esp + 120h]
			movss   dword ptr[esp], xmm1
			movss   xmm1, dword ptr[ecx + 38h]
			movss   dword ptr[esp + 18h], xmm0
			movss   dword ptr[esp + 4], xmm1
			movss   xmm1, dword ptr[ecx + 8]
			movss   dword ptr[esp + 7Ch], xmm7
			movups  xmm0, xmmword ptr[esp + 70h]
			movss   dword ptr[esp + 64h], xmm2
			movss   xmm2, dword ptr[ecx + 20h]
			mulps   xmm6, xmm0
			movups  xmm0, xmmword ptr[esp + 50h]
			movss   dword ptr[esp + 8], xmm1
			movss   xmm1, dword ptr[ecx + 28h]
			movss   dword ptr[esp + 68h], xmm3
			movss   dword ptr[esp + 6Ch], xmm2
			movss   dword ptr[esp + 0Ch], xmm1
			movups  xmm1, xmmword ptr[esp + 60h]
			movss   dword ptr[esp + 28h], xmm5
			mulps   xmm1, xmm0
			movups  xmm0, xmmword ptr[esp + 20h]
			movss   dword ptr[esp + 1Ch], xmm5
			movups  xmm5, xmmword ptr[esp + 40h]
			movups  xmm2, xmmword ptr[esp + 10h]
			mulps   xmm5, xmm0
			movaps  xmm3, xmm1
			movups  xmm0, [esp]
			mulps   xmm2, xmm0
			movups  xmm0, xmmword ptr[esp + 0B0h]
			movaps  xmm7, xmm0
			subps   xmm7, xmm6
			addps   xmm6, xmm0
			movups  xmm0, xmmword ptr[esp + 80h]
			addps   xmm3, xmm0
			movups  xmmword ptr[esp + 0B0h], xmm6
			subps   xmm0, xmm1
			movups  xmmword ptr[esp + 80h], xmm0

			movups  xmm0, xmmword ptr[esp + 30h]
			movaps  xmm1, xmm4
			movss   dword ptr[esp + 50h], xmm6
			subps   xmm1, xmm5
			movaps  xmm6, xmm7
			addps   xmm5, xmm4
			shufps  xmm6, xmm7, 55h
			movaps  xmm4, xmm2
			movss   dword ptr[esp + 54h], xmm6
			addps   xmm4, xmm0
			mulss   xmm6, dword ptr[ecx + 10h]
			subps   xmm0, xmm2
			shufps  xmm7, xmm7, 0FFh
			movss   dword ptr[esp + 5Ch], xmm7
			mulss   xmm7, dword ptr[ecx + 30h]
			movss   dword ptr[esp + 70h], xmm5
			movups  xmmword ptr[esp + 30h], xmm0
			movups  xmm0, xmmword ptr[esp + 0B0h]
			shufps  xmm5, xmm5, 0AAh
			movaps  xmm2, xmm0
			movss   dword ptr[esp + 78h], xmm5
			shufps  xmm2, xmm0, 0AAh
			movups  xmm0, xmmword ptr[esp + 80h]
			movss   dword ptr[esp + 58h], xmm2
			movss   dword ptr[esp + 60h], xmm0
			movaps  xmm0, xmm3
			shufps  xmm0, xmm3, 55h
			mulss   xmm2, dword ptr[ecx + 20h]
			movss   dword ptr[esp + 64h], xmm0
			movss   xmm0, dword ptr[esp + 88h]
			movss   dword ptr[esp + 68h], xmm0
			movaps  xmm0, xmm1
			shufps  xmm0, xmm1, 55h
			movss   dword ptr[esp + 74h], xmm0
			movaps  xmm0, xmm4
			shufps  xmm0, xmm4, 55h
			movss   dword ptr[esp + 94h], xmm0
			movups  xmm0, xmmword ptr[esp + 0B0h]
			shufps  xmm3, xmm3, 0FFh
			mulss   xmm0, dword ptr[ecx]
			movss   dword ptr[esp + 6Ch], xmm3
			shufps  xmm1, xmm1, 0FFh
			addss   xmm6, xmm0
			movss   dword ptr[esp + 7Ch], xmm1
			movups  xmm1, xmmword ptr[esp + 30h]
			shufps  xmm4, xmm4, 0FFh
			movss   dword ptr[esp + 90h], xmm1
			addss   xmm6, xmm2
			shufps  xmm1, xmm1, 0AAh
			movups  xmm2, xmmword ptr[esp + 70h]
			movss   dword ptr[esp + 98h], xmm1
			movups  xmm1, xmmword ptr[esp + 60h]
			addss   xmm6, xmm7
			movss   dword ptr[esp + 9Ch], xmm4
			movups  xmm4, xmmword ptr[esp + 90h]
			shufps  xmm6, xmm6, 0
			rcpps   xmm3, xmm6
			movaps  xmm0, xmm3
			mulps   xmm0, xmm3
			addps   xmm3, xmm3
			mulps   xmm0, xmm6
			subps   xmm3, xmm0
			movups  xmm0, xmmword ptr[esp + 50h]
			mulps   xmm3, StaticBuffer
			mulps   xmm4, xmm3
			mulps   xmm2, xmm3
			mulps   xmm1, xmm3
			mulps   xmm0, xmm3
			movups  xmmword ptr[eax + 20h], xmm2
			movups  xmmword ptr[eax + 10h], xmm1
			movups  xmmword ptr[eax], xmm0
			movups  xmmword ptr[eax + 30h], xmm4;

		MOV ESP, EBP;
		POP EBP;
		RETN 4;
	}
}
*/


/*
float Buffer[] =
{
	0.707107f, 0.588662f, 0.391762f, 0.0f,
	-0.707107f, 0.588662f, 0.391762f, 0.0f,
	0.0f	   ,-0.554035f, 0.832494f, 0.0f,
	2863.113f  ,-11513.11f , -6445.292f, 1.000000f
};

float CalcBuffer[16] = { 0 };

float f12FECF0[] =
{
	0.0f, 0.0f, 0.0f, 30.0f,
	30.0f, 30.0f,30.0f, 30.0f,
	0.0f, 0.0f, 0.0f, 40.0f,
	0.0f, 0.0f, 0.0f, 50.0f,
	0.0f, 50.0f, 0.0f, 50.0f,
	0.0f, 64.0f, 0.0f, 69.0f,
	0.0f, 77.0f, 0.0f, 69.0f,
	148.0f, 57.0f, 337.0f, 97.0f,
	255.0f,255.0f,255.0f,255.0f,
	-100000.0f,-100000.0f,100000.0f,100000.0f,
	100000.0f,100000.0f,100000.0f,100000.0f,
};

DWORD fZeroBuffer[] =
{
	0x80000000,
	0x80000000,
	0x80000000,
	0x80000000,
};


float Result[6] = { 0 };

DWORD dwCalcScreenToClientBufferAddr = (DWORD)memcpy;
DWORD ScreenX = 0x3FB;
DWORD ScreenY = 0x298;
float f238 = 1.0f;
float f64 = 2.414213f;
float f50 = 1.44853f;
float f12F7DC8[] =
{
	1.0f,1.001000f,1.035000f,0.0f
};
__declspec(naked) void GetScreenToClientBuffer()
{
	__asm
	{
		PUSH EBP;
		MOV EBP, ESP;
		AND ESP, 0xFFFFFFF8;
		SUB ESP, 0x5C;
		PUSH ESI;

		LEA ECX, Buffer;

		PUSH 16 * 4;
		LEA EAX, CalcBuffer;
		PUSH EAX;
		LEA EAX, [ESP + 0x20];
		PUSH EAX;
		CALL dwCalcScreenToClientBufferAddr;
		ADD ESP, 0xC;

		MOV EAX, 0x0; // [InGameState+1950+240]
		movss xmm0, dword ptr[ESP + 0x58];
		movss   dword ptr[esp + 10h], xmm0;
		movd    xmm1, ScreenX;
		movd    xmm0, eax;
		cvtdq2pd xmm0, xmm0;
		shr     eax, 1Fh;
		lea     edx, Result;
		cvtdq2ps xmm1, xmm1;
		addsd   xmm0, qword ptr[eax * 8 + f12FECF0];
		movss   xmm4, dword ptr[esp + 30h];
		movss   xmm2, dword ptr[esp + 34h];
		movss   xmm7, dword ptr[esp + 50h];
		movss   xmm6, dword ptr[esp + 54h];
		cvtpd2ps xmm0, xmm0;
		unpcklps xmm7, xmm6;
		subss   xmm1, xmm0;
		divss   xmm1, f238;
		cvttss2si eax, xmm1;
		movss   xmm1, dword ptr[esp + 38h];
		add     eax, eax;
		movd    xmm5, eax;
		mov eax, 0x500;    // 游戏分辨率X
		cvtdq2ps xmm5, xmm5;
		movd    xmm0, eax;
		cvtdq2pd xmm0, xmm0;
		shr     eax, 1Fh;
		addsd   xmm0, qword ptr[eax * 8 + f12FECF0];
		mov     eax, ScreenY;
		add     eax, eax;
		cvtpd2ps xmm0, xmm0;
		movd    xmm3, eax;
		mov eax, 0x300;  // 游戏分辨率Y
		divss   xmm5, xmm0;
		movd    xmm0, eax;
		cvtdq2pd xmm0, xmm0;
		shr     eax, 1Fh;
		cvtdq2ps xmm3, xmm3;
		addsd   xmm0, qword ptr[eax * 8 + f12FECF0];
		subss   xmm5, f12F7DC8;
		mov     eax, [esp + 10h];
		cvtpd2ps xmm0, xmm0;
		divss   xmm5, f50;
		divss   xmm3, xmm0;
		movss   xmm0, dword ptr[esp + 20h];
		subss   xmm3, f12F7DC8;
		mulss   xmm0, xmm5;
		divss   xmm3, f64;
		POP     ESI; // 还原堆栈后对下面的 ESP + XX 是有影响的
		movq    qword ptr[edx], xmm7;


		xorps   xmm3, fZeroBuffer;
		mulss   xmm4, xmm3;
		mov[edx + 8], eax;
		mov     eax, edx;
		mulss   xmm2, xmm3;
		addss   xmm4, xmm0;
		mulss   xmm1, xmm3;
		movss   xmm0, dword ptr[esp + 20h];
		mulss   xmm0, xmm5;
		addss   xmm4, dword ptr[esp + 3Ch];
		addss   xmm2, xmm0;
		movss   xmm0, dword ptr[esp + 24h];
		mulss   xmm0, xmm5;
		addss   xmm2, dword ptr[esp + 40h];
		addss   xmm1, xmm0;
		unpcklps xmm4, xmm2;
		addss   xmm1, dword ptr[esp + 44h];
		movq    qword ptr[edx + 0Ch], xmm4;
		movss   dword ptr[esp + 18h], xmm1;
		mov     ecx, [esp + 18h];
		mov[edx + 14h], ecx;


		MOV ESP, EBP;
		POP EBP;
		RETN;
	}
}
*/


/*
	DWORD dwInGameState = CObjectSearcher::GetGameEnv();


	POINT Pos;
	RECT GameRect;
	if (!::GetWindowRect(CGameMemory::GetInstance().GetGameWnd(), &GameRect))
	{
		LOG_MSG_CF(L"GetWindowRect Faild!");
		return;
	}
	
	::GetCursorPos(&Pos);
	
	
	//ScreenX = Pos.x - GameRect.left - 8;
	//ScreenY = Pos.y - GameRect.top - 31;
	ScreenX = 853;
	ScreenY = 331;
	
	for (int i = 0; i < _countof(Buffer); ++i)
	{
		Buffer[i] = ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + i * 4);
	}
	
	CalcBuffer[0] = ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x0);
	CalcBuffer[1] = ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x10);
	CalcBuffer[2] = 0.0f;
	CalcBuffer[3] = 0.0f;
	CalcBuffer[4] = ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x4);
	CalcBuffer[5] = ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x14);
	CalcBuffer[6] = ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x24);
	CalcBuffer[7] = 0.0f;
	CalcBuffer[8] = ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x8);
	CalcBuffer[9] = ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x18);
	CalcBuffer[10] = ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x28);
	CalcBuffer[11] = -0.0f; // => 0x80000000
	CalcBuffer[12] = ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 游戏坐标转换偏移3 + 0x0);
	CalcBuffer[13] = ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 游戏坐标转换偏移3 + 0x4);
	CalcBuffer[14] = ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 游戏坐标转换偏移3 + 0x8);
	CalcBuffer[15] = 1.0f;

	Result[0] = CalcBuffer[12];
	Result[1] = CalcBuffer[13];
	Result[2] = CalcBuffer[14];

	// 游戏分辨率
	float ResolutionX = ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x4), ResolutionY = ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x8);

	//--------------------------------------
	float fxmm5 = static_cast<float>(ScreenX * 2) / ResolutionX;
	fxmm5 -= ReadFloat(坐标转换基址2);
	fxmm5 /= ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 游戏坐标转换偏移5);
	fxmm5 *= CalcBuffer[0]; // 0.157125


	float fxmm3 = static_cast<float>(ScreenY * 2) / ResolutionY;
	fxmm3 -= ReadFloat(坐标转换基址2);
	fxmm3 /= ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 游戏坐标转换偏移4);
	fxmm3 = fabs(fxmm3); // xmm3(xmm3 < 0) xor -0.0f =>  fabs(xmm3)
	fxmm3 *= CalcBuffer[4];
	Result[3] = fxmm3 + fxmm5 + CalcBuffer[8];

	//--------------------------------------------
	fxmm5 = static_cast<float>(ScreenX * 2) / ResolutionX;
	fxmm5 -= ReadFloat(坐标转换基址2);
	fxmm5 /= ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 游戏坐标转换偏移5); //
	fxmm5 *= CalcBuffer[1];


	fxmm3 = static_cast<float>(ScreenY * 2) / ResolutionX;
	fxmm3 -= ReadFloat(坐标转换基址2);
	fxmm3 /= ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 游戏坐标转换偏移4);
	fxmm3 = fabs(fxmm3); // xmm3(xmm3 < 0) xor -0.0f =>  fabs(xmm3)
	fxmm3 *= CalcBuffer[4];
	Result[4] = fxmm3 + fxmm5 + CalcBuffer[9];

	//-------------------------------------------------
	fxmm3 = static_cast<float>(ScreenY * 2) / ResolutionY;
	fxmm3 -= ReadFloat(坐标转换基址2);
	fxmm3 /= ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 游戏坐标转换偏移4);
	fxmm3 = fabs(fxmm3); // xmm3(xmm3 < 0) xor -0.0f =>  fabs(xmm3)
	fxmm3 *= CalcBuffer[6];
	fxmm3 += CalcBuffer[10];
	Result[5] = fxmm3;


	float fxmm0 = fabs(Result[2]) - fabs(ReadFloat(dwInGameState + 游戏坐标转换偏移2));
	float fxmm1 = Result[5];
	float fxmm2 = Result[3];
	float fxmm4 = Result[4];



	fxmm0 /= fxmm1;
	fxmm2 *= fxmm0;
	fxmm2 += ReadFloat(dwInGameState + 游戏坐标X转换偏移);
	fxmm2 *= ReadFloat(游戏坐标比例基址); // CurorPos.X


	fxmm4 *= fxmm0;
	fxmm4 += ReadFloat(dwInGameState + 游戏坐标Y转换偏移);
	fxmm4 *= ReadFloat(游戏坐标比例基址); // CurorPos.Y
	LOG_C_D(L"CurorPos=[%.2f,%.2f]", fxmm2, fxmm4);

*/

/*

VOID GamePointToScreen()
{
DWORD dwInGameState = CObjectSearcher::GetGameEnv();
//float fPosX = ReadFloat(dwInGameState + 0x193C), fPosY = ReadFloat(dwInGameState + 0x1940);
float fPosX = 734.0f / ReadFloat(游戏坐标比例基址);
float fPosY = 1065.0f / ReadFloat(游戏坐标比例基址);

fPosX -= ReadFloat(dwInGameState + 游戏坐标X转换偏移);
fPosY -= ReadFloat(dwInGameState + 游戏坐标Y转换偏移);

float fxmm0 = fabs(ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 游戏坐标转换偏移3 + 0x8)) - fabs(ReadFloat(dwInGameState + 游戏坐标转换偏移2));
fPosX /= fxmm0;
fPosY /= fxmm0;

// fxmm5 = (Pos.X - Pos.Y) * (fxmm3 * CalcBuffer[6] + CalcBuffer[10]) / (CalcBuffer[0] - CalcBuffer[1])
// (Pos.X - Pos.Y) / (CalcBuffer[0] - CalcBuffer[1])  => A
float A = (fPosX - fPosY) / (ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x0) - ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x10));

// fxmm5 = A * (fxmm3 * CalcBuffer[6] + CalcBuffer[10])
// fxmm5 = A * fxmm3 * CalcBuffer[6] + A * CalcBuffer[10]

//A * CalcBuffer[6] => B
//A * CalcBuffer[10] = > C

float B = A * ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x24);
float C = A * ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x28);

// fxmm5 = B * fxmm3 + C


//// 
fxmm2 = fxmm5 * CalcBuffer[0] + fxmm3 * CalcBuffer[4] + CalcBuffer[8]
fxmm4 = fxmm3 * CalcBuffer[4] + fxmm5 * CalcBuffer[1] + CalcBuffer[9]
fxmm1 = fxmm3 * CalcBuffer[6] + CalcBuffer[10]

Pos.X * xmm1 = fxmm5 * CalcBuffer[0] + fxmm3 * CalcBuffer[4] + CalcBuffer[8]
Pos.Y * xmm1 = fxmm5 * CalcBuffer[1] + fxmm3 + CalcBuffer[4] + CalcBuffer[9]

Pos.X * xmm1 = (B * fxmm3 + C) * CalcBuffer[0] + fxmm3 * CalcBuffer[4] + CalcBuffer[8]
Pos.X * xmm1 = B * fxmm3 * CalcBuffer[0] + C * CalcBuffer[0] + fxmm3 * CalcBuffer[4] + CalcBuffer[8]

B * CalcBuffer[0] => D
C * CalcBuffer[0] => E

Pos.X * xmm1 = D * xmm3 + E + fxmm3 * CalcBuffer[4] + CalcBuffer[8]
Pos.X * xmm1 = xmm3 * (D + CalcBuffer[4]) + E + CalcBuffer[8]

D + CalcBuffer[4] => F
E + CalcBuffer[8] => G

Pos.X * xmm1 = xmm3 * F + G

Pos.X * (fxmm3 * CalcBuffer[6] + CalcBuffer[10]) = xmm3 * F + G
Pos.X * CalcBuffer[6] * xmm3  + Pos.X * CalcBuffer[10] = xmm3 * F + G

Pos.X * CalcBuffer[6] => H
Pos.X * CalcBuffer[10] => I

H * xmm3 + I = xmm3 * F + G
I - G = xmm3 * F - H * xmm3
I - G = xmm3 * (F - H)
xmm3 = (I - G) / (F - H)

float D = B * ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x0);
float E = C * ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x0);
float F = D + ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x4);
float G = E + ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x8);
float H = fPosX * ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x24);
float I = fPosX * ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 0x10 + 0x28);
float fxmm3 = (I - G) / (F - H);

LOG_C_D(L"fxmm3=%.6f", fxmm3);
float fScreenY = fxmm3 * -1;
LOG_C_D(L"fScreenY=%.6f", fScreenY);
fScreenY *= ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 游戏坐标转换偏移4);
LOG_C_D(L"fScreenY=%.6f", fScreenY);
fScreenY += ReadFloat(坐标转换基址2);
LOG_C_D(L"fScreenY=%.6f", fScreenY);
fScreenY *= static_cast<float>(ReadDWORD(dwInGameState + 游戏坐标转换偏移1 + 0x8));
LOG_C_D(L"fScreenY=%.6f", fScreenY);
fScreenY /= 2;
LOG_C_D(L"ScreenY=%.2f", fScreenY);
if (fScreenY >= ReadDWORD(dwInGameState + 游戏坐标转换偏移1 + 0x8))
{
	LOG_C_D(L"Y轴已经超出屏幕坐标了!");
}

// fxmm5 = B * fxmm3 + C
float fxmm5 = B * fxmm3 + C;
float fScreenX = fxmm5 * ReadFloat(dwInGameState + 游戏坐标转换偏移1 + 游戏坐标转换偏移5);
fScreenX += ReadFloat(坐标转换基址2);
fScreenX *= static_cast<float>(ReadDWORD(dwInGameState + 游戏坐标转换偏移1 + 0x4));
fScreenX /= 2;
LOG_C_D(L"ScreenX=%.2f", fScreenX);
if (fScreenX >= static_cast<float>(ReadDWORD(dwInGameState + 游戏坐标转换偏移1 + 0x4)))
{
	LOG_C_D(L"X轴已经超出屏幕坐标了!");
}

LOG_C_D(L"Cursor=[%d,%d]", ReadDWORD(dwInGameState + 当前屏幕坐标X偏移), ReadDWORD(dwInGameState + 当前屏幕坐标Y偏移));
}
*/