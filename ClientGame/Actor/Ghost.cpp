#include "Actor/Ghost.h"
#include "Core/ImageManager.h"
#include "Core/Engine.h"
#include "Level/Level.h"
#include "Level/GameLevel.h"
#include "Settings/ObjectDefines.h"
#include "Utils/Utils.h"
Ghost::Ghost(int x, int y) : Actor(std::string("../Assets/Images/Ghost.txt"), Vector2(x, y), ImageManager::Get().GetImage("../Assets/Images/Ghost.txt"), ImageManager::Get().GetColor("../Assets/Colors/GhostColors.txt"), ImageManager::Get().GetColor("../Assets/Colors/GhostColors.txt")) {
	//SetPosition(Vector2(x, y));
	xTemp = (float)x;
	yTemp = (float)y;
	SetSortingOrder(15);
}

void Ghost::Tick(float deltaTime) {
	super::Tick(deltaTime);

	GameLevel* mygl = dynamic_cast<GameLevel*>(GetOwner());
	if (!mygl)
		return;

	Vector2 playerLeftTop = mygl->GetPlayerPosition();
	Vector2 playerCenter = Vector2(playerLeftTop.x + (PLAYER_WIDTH / 2), playerLeftTop.y + (PLAYER_HEIGHT / 2));
	Vector2 ghostCenter = Vector2(position.x + (GHOST_WIDTH / 2), position.y + (GHOST_HEIGHT / 2));
	if (playerCenter.x > ghostCenter.x)
		isRight = true;
	else
		isRight = false;

	//공격 사거리
	int xRange = BLOCKSIZE_WIDTH / 3;
	int yRange = BLOCKSIZE_HEIGHT / 3;

	if (xRange >= abs(ghostCenter.x - playerCenter.x) && yRange >= abs(ghostCenter.y - playerCenter.y))
		Attack();
	else {
		// 이동 속도
		//float moveSpeed = 2.5f; // 속도는 상황에 맞게 조절

		// 유령 중심 기준으로 방향 계산 (정규화된 벡터)
		float dx = (float)(playerCenter.x - ghostCenter.x);
		float dy = (float)(playerCenter.y - ghostCenter.y);
		float length = sqrtf(dx * dx + dy * dy);
		if (length != 0.0f)
		{
			dx /= length;
			dy /= length;
		}

		// 누적 좌표 업데이트 (float)
		xTemp += dx * moveSpeed;
		yTemp += dy * moveSpeed;

	//	// 정수 좌표로 변환 → 이동
		int newX = (int)xTemp;
		int newY = (int)yTemp;
		int deltaX = newX - position.x;
		int deltaY = newY - position.y;

		if (deltaX != 0 || deltaY != 0)
		{
			Vector2 oldPos = position;
			Move(Vector2(deltaX, deltaY));

			// 이동 실패 → 롤백
			if (position == oldPos)
			{
				xTemp = (float)position.x;
				yTemp = (float)position.y;
			}
		}
	}

}
void Ghost::Render() {
	Vector2 actorPos = { position.x - Engine::Get().cameraPos.x, position.y - Engine::Get().cameraPos.y };

	if (asciiImages.empty() || asciiImages[0].empty())
		return;

	//플레이어 렌더
	int direction = isRight ? 0 : 15;
	int animationLevel = 0;

	int startRow = direction + animationLevel;

	// 이미지와 색상에서 필요한 부분만 자름
	auto sliceImage = Utils::Slice2DVector(asciiImages, startRow, 0, GHOST_HEIGHT, (int)asciiImages[0].size());
	auto sliceFg = Utils::Slice2DVector(fgs, startRow, 0, GHOST_HEIGHT, (int)fgs[0].size());
	auto sliceBg = Utils::Slice2DVector(bgs, startRow, 0, GHOST_HEIGHT, (int)bgs[0].size());
	Engine::Get().WriteToBuffer(actorPos, sliceImage, sliceFg, sliceBg);

}
void Ghost::Move(Vector2 delta) {
	position = position + delta;
}

void Ghost::Attack() {

}