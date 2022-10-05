#include "DxLib.h"

int Key[256]; // �L�[�{�[�h����

typedef struct
{
    int x, y;       // ���W�i�[�p�ϐ�
    char name[128]; // ���ږ��i�[�p�ϐ�
} menuXYName_t;

int gpUpdateKey()
{
    char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
    GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
    for (int i = 0; i < 256; i++)
    {
        if (tmpKey[i] != 0)  // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
            Key[i]++;       // ���Z����
        else                // ������Ă��Ȃ����
            Key[i] = 0;     // 0�ɂ���
    }
    return 0;
}

// ��������main
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

    // DxLib�����ݒ�
    ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
    SetDrawScreen(DX_SCREEN_BACK);
    if (DxLib_Init() == -1)		// DxLib����������
    {
        return -1;			// �G���[���N�����璼���ɏI��
    }
    // DxLib�����ݒ�I���

    // �ϐ������ݒ�
    int scene = 0;  //�V�[�� 0:�����ݒ�,1:�^�C�g��,2:�Q�[��,
    int i = 0;
    int akane, aoi, ebihurai, haikei;
    int selectNum = 0;
    menuXYName_t startMenu[5] = {
        {  80, 100, "���[�ނ��͂��߂�" },
        { 100, 150, "�����т���" },
        { 100, 200, "�����傤�����Ă�" },
        { 100, 250, "���ꂶ����" },
        { 100, 300, "���[�ނ����イ��傤����"}
    };
    menuXYName_t gameMenu[5] = {
        {  80, 100, "���[�ނ�������������" },
        { 100, 150, "�����Ƃ�ɂ��ǂ�" },
        { 100, 200, "�����傤�����Ă�" },
        { 100, 250, "�����т���" },
        { 100, 300, "���[�ނ����イ��傤����"}
    };
        // �ϐ������ݒ�I���

        //�Q�[���{��
        while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0)
        {
            // �Q�[�����j���[�Ăяo��
            if (Key[KEY_INPUT_ESCAPE] == 1 && scene == 1)
            {
                selectNum = 0;
                i = 0;
                while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0)
                {
                    if (Key[KEY_INPUT_ESCAPE] == 1) //������xESCAPE�L�[�������ꂽ�烁�j���[�����         
                        break;
                    else if (Key[KEY_INPUT_DOWN] == 1)       // ���L�[�������ꂽ�u�Ԃ�������
                        selectNum = (selectNum + 1) % 5;  // ���݂̑I�����ڂ�����ɂ��炷
                    else if (Key[KEY_INPUT_UP] == 1)     // ��L�[�������ꂽ�u�Ԃ�������
                        selectNum = (selectNum + 4) % 5;  // ���݂̑I�����ڂ����ɂ��炷(�t���[�v����)

                    for (i = 0; i < 5; i++)       // ���j���[���ڐ��ł���5���[�v����
                    {
                        if (i == selectNum)        // ���������Ă���̂��A�I��ԍ��Ɠ����v�f�Ȃ�
                            gameMenu[i].x = 80;     // ���W��80�ɂ���
                        else                        // ���������Ă���̂��A�I��ԍ��ȊO�Ȃ�
                            gameMenu[i].x = 100;    // ���W��100�ɂ��� 
                    }

                    for (i = 0; i < 5; i++) // ���j���[���ڂ�`��
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
            // �Q�[�����j���[�I���

            switch (scene) //�Q�[���̊e�V�[���I��
            {
            case 0: // �����ݒ�
                selectNum = 0;
                i = 0;
                scene = 1;
                break;

            case 1: // �^�C�g��
                if (Key[KEY_INPUT_DOWN] == 1)            // ���L�[�������ꂽ�u�Ԃ�������
                    selectNum = (selectNum + 1) % 5;  // ���݂̑I�����ڂ�����ɂ��炷
                else if (Key[KEY_INPUT_UP] == 1)     // ��L�[�������ꂽ�u�Ԃ�������
                    selectNum = (selectNum + 4) % 5;  // ���݂̑I�����ڂ����ɂ��炷(�t���[�v����)

                for (i = 0; i < 5; i++)       // ���j���[���ڐ��ł���5���[�v����
                {
                    if (i == selectNum)        // ���������Ă���̂��A�I��ԍ��Ɠ����v�f�Ȃ�
                        startMenu[i].x = 80;     // ���W��80�ɂ���
                    else                        // ���������Ă���̂��A�I��ԍ��ȊO�Ȃ�
                        startMenu[i].x = 100;    // ���W��100�ɂ��� 
                }

                for (i = 0; i < 5; i++) // ���j���[���ڂ�`��
                    DrawFormatString(startMenu[i].x, startMenu[i].y, GetColor(255, 255, 255), startMenu[i].name);

                if (Key[KEY_INPUT_SPACE] == 1) // ����{�^��(�X�y�[�X�L�[)�������ꂽ��
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
            case 2: // �Q�[��

                break;
            default:
                scene = 0;
                break;
            }
        }
    //�Q�[���{�̏I���

    DxLib_End();			// DxLib�̏I������
    return 0;				// �\�t�g�̏I�� 
}