#include <stdio.h>
#include <windows.h>    //*û�����������ò�ư�ť��Ϣ��������*��//
#include <easyx.h>//easyx��//
#include <time.h>//��ʱ��//
#include <conio.h> //��ť//
#include<graphics.h>//����ͼ�ο�ͷ�ļ�
#include<mmsystem.h>//������ý���豸�ӿ�ͷ�ļ�
#pragma comment(lib,"winmm.lib")
#define width 288
#define high 512
IMAGE bk;//����//
IMAGE bird[2];//��//
IMAGE up[2];//�������//
IMAGE down[2];//�������//
IMAGE end[2];
void control();
void tipepating(int i);
void birdpating();
int timerecord(int count, int m);
int overvideo();
void sucai();
void tipeloder();
int hitf();
int hitxxx();
int hitxxx();

struct bird {
	int x;
	int y;
	int vx;//�ٶ�//
};
struct bird fb = { (288 - 48) / 2,(512 - 48) / 2,10 };// x,y�ֱ����//  //5ms��һ��//

struct tipe
{
	int x;
	int y;
	int height;
};
struct tipe pillar[3];
//*�ֺ���*//
void control()
{
	char key = _getch();
	switch (key)
	{
	case ' ' :
		fb.y -= 5 * fb.vx;
		break;
	default:
		break;
	}
}

void tipepating(int i) //***// // ���ӵĻ���//
{
	putimage(pillar[i].x, 0, 52, pillar[i].height, up + 0, 0, 320 - pillar[i].height, SRCAND);
	putimage(pillar[i].x, 0, 52, pillar[i].height, up + 1, 0, 320 - pillar[i].height, SRCERASE);
	putimage(pillar[i].x, 512 - (320 - pillar[i].height), 52, 320 - pillar[i].height, down+0, 0, 0,SRCAND);
	putimage(pillar[i].x, 512 - (320 - pillar[i].height), 52, 320 - pillar[i].height, down+1, 0, 0,SRCERASE);

}

void birdpating()//����С����//   //͸����ͼ//
{
	putimage(fb.x, fb.y, bird + 0, SRCAND);//����ͼ//
	putimage(fb.x, fb.y, bird + 1, SRCPAINT);//����ͼ//
}

int timerecord(int count, int m)  //ʱ���¼//
{
	static int start[100];
	int end = clock();
	if (end - start[m] > count) //����m�ż�ʱ��//
	{
		start[m] = end; //��ʼ��//
		return 1; //������ʱ��//
	}
	return 0;
}

int overvideo()//��������//
{
	int x = 50;
	int y = 608;
	while (y >= 240)
	{
		putimage(0, 0, &bk);
		putimage(x, y, end+0, SRCAND);
		putimage(x, y, end+1, SRCERASE);
		if (timerecord(100, 2))// ��ʱ��//
		{
			y -= 50;
		}
		FlushBatchDraw();
	}
	return 0;
}

void sucai()//���غ���//
{
	loadimage(&bk,"background.jpg");
	loadimage(bird + 0, "bird0.png");//����ͼ//  //��//
	loadimage(bird + 1, "bird1.png");//����ͼ// 
	loadimage(down + 0, "down0.jpg");//�Ϲ���// //����ͼ//
	loadimage(down + 1, "down1.jpg");       //����ͼ// 
	loadimage(up + 0, "up0.jpg");//�¹���//  //����ͼ//
	loadimage(up + 1, "up1.jpg");       //����ͼ//
	loadimage(end+0, "end2.jpg");
	loadimage(end+1, "end1.jpg");
}

void tipeloder(int i)
{
	pillar[i].x = 288;//�ⲿ����//
	pillar[i].y = 0;
	pillar[i].height = rand()%100;//�߶����//
}

int hitf()//ȫ����ײ��⺯��//
{
		if (fb.x + 48> 512 || fb.x<=0)//��ײ��ⷶΧ//
		{
			return 1;
		}
	return 0;
}

int hitxxx()//x������ײ��⺯��//
{
	for (int i = 0; i < 3; i++)
	{
		if (fb.x + 48 < pillar[i].x + 52 || fb.x + 48 > pillar[i].x)
		{
			return i;
		}
	}
	return 0;
}

int hitp()//y������ײ���//
{
	int p = hitxxx();
	printf("%d\n", p);
	if ((p != -1 && fb.y < pillar[p].height) || (p != -1 && 320 - fb.y < pillar[p].height))
	{
		return 1;
	}
	return 0;
}
//*������*//
int main()
{
	srand((int)time(NULL)); //���ӵ��������//
	sucai();  //�����زĿ�//
	initgraph(width,high,1);
	for (int i = 0; i < 3; i++)
	{
		tipeloder(i);
		pillar[i].x = 288 + i * 200;  // ���150��������//
	}
	BeginBatchDraw(); //��ʼ�滭//
    mciSendString("play ��ͨ����.wav repeat", 0, 0, 0);
	while (1)
	{
		putimage(0, 0, &bk);
		birdpating();
		
		for (int i = 0; i < 3; i++)
		{
			tipepating(i);
			if (pillar[i].x < -52 - 155)  //�߽���ʼ��/ /
			{
				tipeloder(i);
			}

		}
		if (timerecord(50, 1))
		{
			for (int i = 0; i < 3; i++)
			{
				pillar[i].x -= 10;
			}
		}
		if (timerecord(200, 0))
		{
			fb.y += fb.vx;//���ٶȼ���//
		}
		if (_kbhit()) //����ʶ��//
		{
			control();
		}
		if (hitf() || hitp() ) 
		{
			break;
			overvideo();
		}
		FlushBatchDraw();
		//Sleep(50);//�ݿ�50ms//
	}

	overvideo();
	system("pause");
	EndBatchDraw();  //�����滭//
	closegraph();
	return 0;
}


//  * ������ײ������� * //