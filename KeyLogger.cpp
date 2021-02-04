//--------------------------------------------------------------------------------------
// File: KeyLogger.cpp
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "DXUT.h"
#include "resource.h"
IDirect3DTexture9* g_Texture;
ID3DXSprite* g_Sprite;
D3DXIMAGE_INFO g_Info;
D3DXCOLOR g_Color = 0xffffffff;
LPD3DXFONT fonts[105];
D3DXVECTOR2 fontpos[105];
RECT fontrct[105];
time_t g_Time;
tm* g_Localtime;

int P[103] = { 0, };
int W[256] = { 0, };
int a = 0;
int result = 0;

FILE* fp;
int inputdata; // for fileinput
#define SCW 1236
#define SCH 369
HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
    fp = fopen("KeyLogger.txt", "r");
    if (fp)
    {
        int num = 0;
        while (fscanf(fp, "%d", &inputdata) != EOF)
        {
            P[num] = inputdata;
            num++;
        }
        fclose(fp);
    }
    else
    {
        for (int i = 0; i < 103; i++)
            P[i] = 0;
    }
    g_Time = time(0);
    g_Localtime = localtime(&g_Time);
    D3DXCreateSprite(pd3dDevice, &g_Sprite);
    D3DXCreateTextureFromFileEx(DXUTGetD3D9Device(), L"keyboard.png", -2, -2, 1, 0, D3DFORMAT::D3DFMT_A8B8G8R8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, &g_Info, nullptr, (LPDIRECT3DTEXTURE9*)&g_Texture);
    for (int i = 0; i < 105; i++)
    {
        fontpos[i] = { 0,0 };
        D3DXCreateFont(DXUTGetD3D9Device(), 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &fonts[i]);
    }
    fontpos[103] = { 0,0 };
    D3DXCreateFont(DXUTGetD3D9Device(), 17, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &fonts[103]);
    fontpos[104] = { 0,0 };
    D3DXCreateFont(DXUTGetD3D9Device(), 17, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &fonts[104]);
    /// first line
    fontpos[0] = { 26,26 };
    fontpos[1] = { 135,26 };
    fontpos[2] = { 189,26 };
    fontpos[3] = { 243,26 };
    fontpos[4] = { 297,26 };
    fontpos[5] = { 380,26 };
    fontpos[6] = { 434,26 };
    fontpos[7] = { 488,26 };
    fontpos[8] = { 542,26 };
    fontpos[9] = { 623,26 };
    fontpos[10] = { 677,26 };
    fontpos[11] = { 731,26 };
    fontpos[12] = { 785,26 };
    fontpos[13] = { 852,26 };
    fontpos[14] = { 906,26 };
    fontpos[15] = { 960,26 };
    ///
    /// second line
    for (int i = 0; i < 14; i++)
        fontpos[16 + i] = { 26 + float(i * 54), 107 };
    for (int i = 0; i < 3; i++)
        fontpos[30 + i] = { 851 + float(i * 54), 107 };
    for (int i = 0; i < 4; i++)
        fontpos[33 + i] = { 1025 + float(i * 54), 107 };
    /// 
    /// third line
        fontpos[37] = { 26, 161 };
    for (int i = 0; i < 13; i++)
        fontpos[38 + i] = { 108 + float(i * 54), 161 };
    for (int i = 0; i < 3; i++)
        fontpos[51 + i] = { 851 + float(i * 54), 161 };
    for (int i = 0; i < 4; i++)
        fontpos[54 + i] = { 1025 + float(i * 54), 161 };
    ///
    /// fourth line
    fontpos[58] = { 26, 215 };
    for (int i = 0; i < 12; i++)
        fontpos[59 + i] = { 121 + float(i * 54), 215 };
    for (int i = 0; i < 3; i++)
        fontpos[71 + i] = { 1025 + float(i * 54), 215 };
    ///
    /// fifth line
    fontpos[74] = { 26, 269 };
    for (int i = 0; i < 11; i++)
        fontpos[75 + i] = { 147 + float(i * 54), 269 };
    fontpos[86] = { 906,269 };
    for (int i = 0; i < 3; i++)
        fontpos[87 + i] = { 1025 + float(i * 54), 269 };
    ///
    ///sixth line
    fontpos[90] = { 26, 323 };
    fontpos[91] = { 93, 323 };
    fontpos[92] = { 164, 323 };
    fontpos[93] = { 380, 323 };
    fontpos[94] = { 566, 323 };     
    fontpos[95] = { 633, 323 };
    fontpos[96] = { 702, 323 };
    fontpos[97] = { 768, 323 };
    for (int i = 0; i < 3; i++)
        fontpos[98 + i] = { 851 + float(i * 54), 323 };
    fontpos[101] = { 1025, 323 };
    fontpos[102] = { 1133, 323 };
    ///
    fontpos[103] = { 900, 70 };
    fontpos[104] = { 700, 70 };

    return S_OK;
}

void CALLBACK OnFrameMove(double fTime, float fElapsedTime, void* pUserContext)
{
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(DXUTGetHWND(), &p);

    for (int i = 0; i < 256; i++)
    {
        if ((GetAsyncKeyState(i) & 0x8000) && W[i] == 0)
        {
            cout << i << endl;
            W[i] = 1;
            if (i == 109 && a == 0) // 처음에 킬때 - 이게 왜 눌리는지 모르겠는데 무튼 이거 예외처리해줌
            {
                a++;
                break;
            }
            switch (i)
            {
            case VK_ESCAPE:
                P[0]++;
                break;
            case VK_F1:
                P[1]++;
                break;
            case VK_F2:
                P[2]++;
                break;
            case VK_F3:
                P[3]++;
                break;
            case VK_F4:
                P[4]++;
                break;
            case VK_F5:
                P[5]++;
                break;
            case VK_F6:
                P[6]++;
                break;
            case VK_F7:
                P[7]++;
                break;
            case VK_F8:
                P[8]++;
                break;
            case VK_F9:
                P[9]++;
                break;
            case VK_F10:
                P[10]++;
                break;
            case VK_F11:
                P[11]++;
                break;
            case VK_F12:
                P[12]++;
                break;
            case 255:
                P[13]++;
                break;
            case VK_SCROLL:
                P[14]++;
                break;
            case VK_PAUSE:
                P[15]++;
                break;
            case 192:
                P[16]++;
                break;
            case '1':
                P[17]++;
                break;
            case '2':
                P[18]++;
                break;
            case '3':
                P[19]++;
                break;
            case '4':
                P[20]++;
                break;
            case '5':
                P[21]++;
                break;
            case '6':
                P[22]++;
                break;
            case '7':
                P[23]++;
                break;
            case '8':
                P[24]++;
                break;
            case '9':
                P[25]++;
                break;
            case '0':
                P[26]++;
                break;
            case 189:
                P[27]++;
                break;
            case 187:
                P[28]++;
                break;
            case VK_BACK:
                P[29]++;
                break;
            case VK_INSERT:
                P[30]++;
                break;
            case VK_HOME:
                P[31]++;
                break;
            case 33:
                P[32]++;
                break;
            case VK_NUMLOCK:
                P[33]++;
                break;
            case 111:
                P[34]++;
                break;
            case 106:
                P[35]++;
                break;
            case 109:
                P[36]++;
                break;
            case VK_TAB:
                P[37]++;
                break;
            case 'Q':
                P[38]++;
                break;
            case 'W':
                P[39]++;
                break;
            case 'E':
                P[40]++;
                break;
            case 'R':
                P[41]++;
                break;
            case 'T':
                P[42]++;
                break;
            case 'Y':
                P[43]++;
                break;
            case 'U':
                P[44]++;
                break;
            case 'I':
                P[45]++;
                break;
            case 'O':
                P[46]++;
                break;
            case 'P':
                P[47]++;
                break;
            case 219:
                P[48]++;
                break;
            case 221:
                P[49]++;
                break;
            case VK_RETURN:
                P[50]++;
                break;
            case VK_DELETE:
                P[51]++;
                break;
            case VK_END:
                P[52]++;
                break;
            case 34:
                P[53]++;
                break;
            case VK_NUMPAD7:
                P[54]++;
                break;
            case VK_NUMPAD8:
                P[55]++;
                break;
            case VK_NUMPAD9:
                P[56]++;
                break;
            case 107:
                P[57]++;
                break;
            case VK_CAPITAL:
                P[58]++;
                break;
            case 'A':
                P[59]++;
                break;
            case 'S':
                P[60]++;
                break;
            case 'D':
                P[61]++;
                break;
            case 'F':
                P[62]++;
                break;
            case 'G':
                P[63]++;
                break;
            case 'H':
                P[64]++;
                break;
            case 'J':
                P[65]++;
                break;
            case 'K':
                P[66]++;
                break;
            case 'L':
                P[67]++;
                break;
            case 186:
                P[68]++;
                break;
            case 222:
                P[69]++;
                break;
            case 220:
                P[70]++;
                break;
            case VK_NUMPAD4:
                P[71]++;
                break;
            case VK_NUMPAD5:
                P[72]++;
                break;
            case VK_NUMPAD6:
                P[73]++;
                break;
            case VK_SHIFT:
                P[74]++;
                break;
            case 'Z':
                P[75]++;
                break;
            case 'X':
                P[76]++;
                break;
            case 'C':
                P[77]++;
                break;
            case 'V':
                P[78]++;
                break;
            case 'B':
                P[79]++;
                break;
            case 'N':
                P[80]++;
                break;
            case 'M':
                P[81]++;
                break;
            case 188:
                P[82]++;
                break;
            case 190:
                P[83]++;
                break;
            case 191:
                P[84]++;
                break;
            case VK_RSHIFT:
                P[85]++;
                break;
            case VK_UP:
                P[86]++;
                break;
            case VK_NUMPAD1:
                P[87]++;
                break;
            case VK_NUMPAD2:
                P[88]++;
                break;
            case VK_NUMPAD3:
                P[89]++;
                break;
            case VK_LCONTROL:
                P[90]++;
                break;
            case 91:
                P[91]++;
                break;
            case 164:
                P[92]++;
                break;
            case VK_SPACE:
                P[93]++;
                break;
            case 21:
                P[94]++;
                break;
            case 92:
                P[95]++;
                break;
            case 93:
                P[96]++;
                break;
            case 25:
                P[97]++;
                break;
            case VK_LEFT:
                P[98]++;
                break;
            case VK_DOWN:
                P[99]++;
                break;
            case VK_RIGHT:
                P[100]++;
                break;
            case VK_NUMPAD0:
                P[101]++;
                break;
            case 110:
                P[102]++;
                break;
            }
            fp = fopen("KeyLogger.txt", "w");
            for (int i = 0; i < 103; i++)
                fprintf(fp, "%d\n", P[i]);
            fclose(fp);
        }
        else if ((GetAsyncKeyState(i) == 0))
        {
            W[i] = 0;
        }
    
    }

}

void CALLBACK OnLostDevice(void* pUserContext)
{
    g_Sprite->OnLostDevice();
    for (int i = 0; i < 105; ++i)
        fonts[i]->OnLostDevice();
}

HRESULT CALLBACK OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
    g_Sprite->OnResetDevice();
    for (int i = 0; i < 105; ++i)
        fonts[i]->OnResetDevice();
    return S_OK;
}

void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    HRESULT hr;

    V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 234, 234, 234), 1.0f, 0 ) );

    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
        D3DXMATRIX m;
        D3DXMatrixTransformation2D(&m, nullptr, 0, &D3DXVECTOR2(1, 1), nullptr, 0, &D3DXVECTOR2(SCW / 2, SCH / 2));
        g_Sprite->SetTransform(&m);
        g_Sprite->Begin(D3DXSPRITE_ALPHABLEND);
        D3DXVECTOR3 center = { 0.5f * g_Info.Width, 0.5f * g_Info.Height, 0 };
        g_Sprite->Draw(g_Texture, NULL, &center, NULL, g_Color);
        g_Sprite->End();
        result = 0;
        for (int i = 0; i < 103; i++)
            result += P[i];
        float average = (float)result / 103;
        for (int i = 0; i < 103; i++)
        {
            D3DXCOLOR col(0, 0, 0, 1);
            float compare = P[i];
            if (average / 5 > compare)
                col = { 0,0,0,1 };
            else if (average / 4 > compare)
                col = { 0.05,0,0,1 };
            else if (average / 3  > compare)
                col = { 0.1,0,0,1 };
            else if (average / 2 > compare)
                col = { 0.15,0,0,1 };
            else if ((average * 10) < compare)
                col = { 1,0,0,1 };
            else if ((average * 9) < compare)
                col = { 0.9,0,0,1 };
            else if ((average * 8) < compare)
                col = { 0.8,0,0,1 };
            else if ((average * 7) < compare)
                col = { 0.7,0,0,1 };
            else if ((average * 6) < compare)
                col = { 0.6,0,0,1 };
            else if ((average * 5) < compare)
                col = { 0.5,0,0,1 };
            else if ((average * 4) < compare)
                col = { 0.4,0,0,1 };
            else if ((average * 3) < compare)
                col = { 0.35,0,0,1 };
            else if ((average * 2) < compare)
                col = { 0.3,0,0,1 };
            else if (average < compare)
                col = { 0.25,0,0,1 };
            wstring val = to_wstring(P[i]);
            SetRect(&fontrct[i], fontpos[i].x, fontpos[i].y, 0, 0);
            fonts[i]->DrawTextW(nullptr, val.c_str(), -1, &fontrct[i], DT_NOCLIP, col);
        }
        char buff[MAX_SIZE_SECURITY_ID];
        sprintf(buff, "Total Keyboard pressed : %d", result);
        string a = buff;
        wstring aa;
        aa.assign(a.begin(), a.end());
        SetRect(&fontrct[103], fontpos[103].x, fontpos[103].y, 0, 0);
        fonts[103]->DrawTextW(nullptr, aa.c_str(), -1, &fontrct[103], DT_NOCLIP, D3DXCOLOR(0, 0, 0, 1));
        sprintf(buff, "Started At %d(day) - %d:%d:%d", g_Localtime->tm_mday, g_Localtime->tm_hour, g_Localtime->tm_min, g_Localtime->tm_sec);
        a = buff;
        aa.assign(a.begin(), a.end());
        SetRect(&fontrct[104], fontpos[104].x, fontpos[104].y, 0, 0);
        fonts[103]->DrawTextW(nullptr, aa.c_str(), -1, &fontrct[104], DT_NOCLIP, D3DXCOLOR(0, 0, 0, 1));

        V( pd3dDevice->EndScene() );
    }
}

void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
    exit(1);
}


INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
//int main(void)
{
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackFrameMove( OnFrameMove );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );
    DXUTSetCallbackD3D9DeviceReset( OnResetDevice );
    DXUTSetCallbackD3D9DeviceLost( OnLostDevice );

    DXUTInit( true, true ); 
    DXUTSetHotkeyHandling( true, false, true );
    DXUTSetCursorSettings( true, true );
    DXUTCreateWindow( L"KeyLogger" );
    DXUTCreateDevice( true, 1236, 369 );

    DXUTMainLoop();

    return DXUTGetExitCode();
}


