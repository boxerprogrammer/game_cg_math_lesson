#include<DxLib.h>
#include<cmath>
#include"Geometry.h"
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	Circle circle(150.0f, Position2(320.0f, 240.0f));
	Circle point(5.0f, Position2(0.0f, 0.0f));
	Arrow xarrow(Position2(0.0f, 240.0f), Position2(640.0f,240.0f));
	xarrow.headSize = 20.0f;
	Arrow yarrow(Position2(320.0f, 480.0f), Position2(320.0f,0.0f));
	yarrow.headSize = 20.0f;

	float angle = 0.0f;
	while (ProcessMessage() !=-1 ){
		ClearDrawScreen();
		xarrow.Draw();
		yarrow.Draw();
		circle.Draw(0xffaaaa, false);
		float radian = DegToRad(angle);
		point.pos.x = circle.pos.x + circle.radius*std::cos(radian);
		point.pos.y = circle.pos.y - circle.radius*std::sin(radian);
		point.Draw(0x00ffff, true);
		angle = fmod(angle+1.0f,360.0f);
		//DrawFormatString(10, 10, 0xffffff, L"ìxêîñ@ : %.2f deg", angle);
		DrawFormatString(10, 10, 0xffffff, L"É∆ = %.2f rad", radian);
		DrawFormatString(10, 90, 0xffaaaa, L"cos(É∆) : %.2f", cos(radian));
		DrawFormatString(10, 70, 0xaaffaa, L"sin(É∆) : %.2f", sin(radian));
		auto iangle = ((int)angle % 180);
		if ( std::abs(iangle-90)>=5 ){
			DrawFormatString(10, 110, 0xaaaaff, L"tan(É∆) : %.2f", tan(radian));
		}else{
			DrawFormatString(10, 110, 0xaaaaff, L"tan(É∆) : inf");
		}
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}