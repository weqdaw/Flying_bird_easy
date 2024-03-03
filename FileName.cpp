#include <stdio.h>
#include <windows.h>    //*没有这个函数库貌似按钮信息读不出来*？//
#include <easyx.h>//easyx库//
#include <time.h>//计时器//
#include <conio.h> //按钮//
#include<graphics.h>//包含图形库头文件
#include<mmsystem.h>//包含多媒体设备接口头文件
#pragma comment(lib,"winmm.lib")
#define width 288
#define high 512
IMAGE bk;//背景//
IMAGE bird[2];//鸟//
IMAGE up[2];//上面管子//
IMAGE down[2];//下面管子//
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
	int vx;//速度//
};
struct bird fb = { (288 - 48) / 2,(512 - 48) / 2,10 };// x,y分别计算//  //5ms换一下//

struct tipe
{
	int x;
	int y;
	int height;
};
struct tipe pillar[3];
//*分函数*//
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

void tipepating(int i) //***// // 管子的绘制//
{
	putimage(pillar[i].x, 0, 52, pillar[i].height, up + 0, 0, 320 - pillar[i].height, SRCAND);
	putimage(pillar[i].x, 0, 52, pillar[i].height, up + 1, 0, 320 - pillar[i].height, SRCERASE);
	putimage(pillar[i].x, 512 - (320 - pillar[i].height), 52, 320 - pillar[i].height, down+0, 0, 0,SRCAND);
	putimage(pillar[i].x, 512 - (320 - pillar[i].height), 52, 320 - pillar[i].height, down+1, 0, 0,SRCERASE);

}

void birdpating()//绘制小鸟函数//   //透明贴图//
{
	putimage(fb.x, fb.y, bird + 0, SRCAND);//掩码图//
	putimage(fb.x, fb.y, bird + 1, SRCPAINT);//背景图//
}

int timerecord(int count, int m)  //时间记录//
{
	static int start[100];
	int end = clock();
	if (end - start[m] > count) //触发m号计时器//
	{
		start[m] = end; //初始化//
		return 1; //启动计时器//
	}
	return 0;
}

int overvideo()//结束动画//
{
	int x = 50;
	int y = 608;
	while (y >= 240)
	{
		putimage(0, 0, &bk);
		putimage(x, y, end+0, SRCAND);
		putimage(x, y, end+1, SRCERASE);
		if (timerecord(100, 2))// 计时器//
		{
			y -= 50;
		}
		FlushBatchDraw();
	}
	return 0;
}

void sucai()//加载函数//
{
	loadimage(&bk,"background.jpg");
	loadimage(bird + 0, "bird0.png");//掩码图//  //鸟//
	loadimage(bird + 1, "bird1.png");//背景图// 
	loadimage(down + 0, "down0.jpg");//上管子// //掩码图//
	loadimage(down + 1, "down1.jpg");       //背景图// 
	loadimage(up + 0, "up0.jpg");//下馆子//  //掩码图//
	loadimage(up + 1, "up1.jpg");       //背景图//
	loadimage(end+0, "end2.jpg");
	loadimage(end+1, "end1.jpg");
}

void tipeloder(int i)
{
	pillar[i].x = 288;//外部生成//
	pillar[i].y = 0;
	pillar[i].height = rand()%100;//高度随机//
}

int hitf()//全局碰撞检测函数//
{
		if (fb.x + 48> 512 || fb.x<=0)//碰撞检测范围//
		{
			return 1;
		}
	return 0;
}

int hitxxx()//x方向碰撞检测函数//
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

int hitp()//y方向碰撞检测//
{
	int p = hitxxx();
	printf("%d\n", p);
	if ((p != -1 && fb.y < pillar[p].height) || (p != -1 && 320 - fb.y < pillar[p].height))
	{
		return 1;
	}
	return 0;
}
//*主函数*//
int main()
{
	srand((int)time(NULL)); //柱子的随机函数//
	sucai();  //引入素材库//
	initgraph(width,high,1);
	for (int i = 0; i < 3; i++)
	{
		tipeloder(i);
		pillar[i].x = 288 + i * 200;  // 间隔150生成柱子//
	}
	BeginBatchDraw(); //开始绘画//
    mciSendString("play 卡通弹跳.wav repeat", 0, 0, 0);
	while (1)
	{
		putimage(0, 0, &bk);
		birdpating();
		
		for (int i = 0; i < 3; i++)
		{
			tipepating(i);
			if (pillar[i].x < -52 - 155)  //边界后初始化/ /
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
			fb.y += fb.vx;//鸟速度计算//
		}
		if (_kbhit()) //按键识别//
		{
			control();
		}
		if (hitf() || hitp() ) 
		{
			break;
			overvideo();
		}
		FlushBatchDraw();
		//Sleep(50);//暂空50ms//
	}

	overvideo();
	system("pause");
	EndBatchDraw();  //结束绘画//
	closegraph();
	return 0;
}


//  * 上下碰撞间距问题 * //