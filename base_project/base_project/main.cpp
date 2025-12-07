#include<DxLib.h>
#include"Geometry.h"
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	Circle c(50.0f, Position2(320.0f, 240.0f));
	Capsule cap(30.0f, Position2(100.0f, 100.0f), Position2(200.0f, 300.0f));
	Rect rc(Position2(500.0f, 400.0f), 100, 150);
	Arrow arrow(Position2(400.0f, 100.0f), Position2(600.0f, 300.0f));
	DashedArrow dashedArrow(Position2(100.0f, 400.0f), Position2(300.0f, 200.0f));
	dashedArrow.lineThickness = 5.0f;
	dashedArrow.headSize = 50.0f;
	dashedArrow.headType = ArrowHeadType::V;

	while (ProcessMessage() !=-1 ){
		ClearDrawScreen();

		c.Draw(0xffaa00, false);
		cap.Draw(0x00ff00, false);
		rc.Draw(0x00ffff, false);
		arrow.Draw(0xffff00);
		dashedArrow.Draw(0xff00ff);

		ScreenFlip();
	}
	DxLib_End();
	return 0;
}