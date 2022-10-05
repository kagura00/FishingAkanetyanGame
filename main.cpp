#include "DxLib.h"

int Key[256]; // キーボード入力

typedef struct
{
    int x, y;       // 座標格納用変数
    char name[128]; // 項目名格納用変数
} menuXYName_t;

int gpUpdateKey()
{
    char tmpKey[256]; // 現在のキーの入力状態を格納する
    GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
    for (int i = 0; i < 256; i++)
    {
        if (tmpKey[i] != 0)  // i番のキーコードに対応するキーが押されていたら
            Key[i]++;       // 加算する
        else                // 押されていなければ
            Key[i] = 0;     // 0にする
    }
    return 0;
}

// ここからmain
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

    // DxLib初期設定
    ChangeWindowMode(TRUE); // ウィンドウモードに設定
    SetDrawScreen(DX_SCREEN_BACK);
    if (DxLib_Init() == -1)		// DxLib初期化処理
    {
        return -1;			// エラーが起きたら直ちに終了
    }
    // DxLib初期設定終わり

    // 変数初期設定
    int scene = 0;  //シーン 0:初期設定,1:タイトル,2:ゲーム,
    int i = 0;
    int akane, aoi, ebihurai, haikei;
    int selectNum = 0;
    menuXYName_t startMenu[5] = {
        {  80, 100, "げーむをはじめる" },
        { 100, 150, "あそびかた" },
        { 100, 200, "おんりょうせってい" },
        { 100, 250, "くれじっと" },
        { 100, 300, "げーむをしゅうりょうする"}
    };
    menuXYName_t gameMenu[5] = {
        {  80, 100, "げーむをさいかいする" },
        { 100, 150, "たいとるにもどる" },
        { 100, 200, "おんりょうせってい" },
        { 100, 250, "あそびかた" },
        { 100, 300, "げーむをしゅうりょうする"}
    };
        // 変数初期設定終わり

        //ゲーム本体
        while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0)
        {
            // ゲームメニュー呼び出し
            if (Key[KEY_INPUT_ESCAPE] == 1 && scene == 1)
            {
                selectNum = 0;
                i = 0;
                while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0)
                {
                    if (Key[KEY_INPUT_ESCAPE] == 1) //もう一度ESCAPEキーが押されたらメニューを閉じる         
                        break;
                    else if (Key[KEY_INPUT_DOWN] == 1)       // 下キーが押された瞬間だけ処理
                        selectNum = (selectNum + 1) % 5;  // 現在の選択項目を一つ下にずらす
                    else if (Key[KEY_INPUT_UP] == 1)     // 上キーが押された瞬間だけ処理
                        selectNum = (selectNum + 4) % 5;  // 現在の選択項目を一つ上にずらす(逆ループする)

                    for (i = 0; i < 5; i++)       // メニュー項目数である5個ループ処理
                    {
                        if (i == selectNum)        // 今処理しているのが、選択番号と同じ要素なら
                            gameMenu[i].x = 80;     // 座標を80にする
                        else                        // 今処理しているのが、選択番号以外なら
                            gameMenu[i].x = 100;    // 座標を100にする 
                    }

                    for (i = 0; i < 5; i++) // メニュー項目を描画
                        DrawFormatString(gameMenu[i].x, gameMenu[i].y, GetColor(255, 255, 255), gameMenu[i].name);

                    if (Key[KEY_INPUT_SPACE] == 1)
                        switch (selectNum)
                        {
                        case 0:
                            break;
                        case 1:
                            scene = 0;
                            break;
                        case 2:

                            break;
                        case 3:

                            break;
                        case 4:
                            DxLib_End();
                            return 0;
                        }
                }

            }
            // ゲームメニュー終わり

            switch (scene) //ゲームの各シーン選択
            {
            case 0: // 初期設定
                selectNum = 0;
                i = 0;
                scene = 1;
                break;

            case 1: // タイトル
                if (Key[KEY_INPUT_DOWN] == 1)            // 下キーが押された瞬間だけ処理
                    selectNum = (selectNum + 1) % 5;  // 現在の選択項目を一つ下にずらす
                else if (Key[KEY_INPUT_UP] == 1)     // 上キーが押された瞬間だけ処理
                    selectNum = (selectNum + 4) % 5;  // 現在の選択項目を一つ上にずらす(逆ループする)

                for (i = 0; i < 5; i++)       // メニュー項目数である5個ループ処理
                {
                    if (i == selectNum)        // 今処理しているのが、選択番号と同じ要素なら
                        startMenu[i].x = 80;     // 座標を80にする
                    else                        // 今処理しているのが、選択番号以外なら
                        startMenu[i].x = 100;    // 座標を100にする 
                }

                for (i = 0; i < 5; i++) // メニュー項目を描画
                    DrawFormatString(startMenu[i].x, startMenu[i].y, GetColor(255, 255, 255), startMenu[i].name);

                if (Key[KEY_INPUT_SPACE] == 1) // 決定ボタン(スペースキー)が押されたら
                    switch (selectNum)
                    {
                    case 0:
                        scene = 2;
                        break;
                    case 1:

                        break;
                    case 2:

                        break;
                    case 3:

                        break;
                    case 4:
                        DxLib_End();
                        return 0;
                    }

                break;
            case 2: // ゲーム

                break;
            default:
                scene = 0;
                break;
            }
        }
    //ゲーム本体終わり

    DxLib_End();			// DxLibの終了処理
    return 0;				// ソフトの終了 
}