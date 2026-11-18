/* コインの取得枚数管理とクリア判定 */

#include "TutorialGameManager.h"		// 自分自身のクラス定義

#include "Components/SceneComponent.h"	// USceneComponentを使用する
#include "Engine/Engine.h"				// GEngineやエンジンの機能を使用する

// コンストラクタ
ATutorialGameManager::ATutorialGameManager()
{
	// このActorは毎フレーム処理する必要がない
	PrimaryActorTick.bCanEverTick = false;

	// Actorの位置の基準となるComponent
	/* Unityだと、AddComponent<T> */
	RootComponent = CreateDefaultSubobject<USceneComponent>(
		TEXT("SceneRoot")
	);
}

// ゲームプレイ開始時に呼ばれる
void ATutorialGameManager::BeginPlay()
{
	/*
	 * Super ... 基底クラスを参照するための別名
	 * AActor::BeginPlay() と概ね同じ
	 */
	// 親クラスのBeingPlay()を実行
	Super::BeginPlay();

	CollectedCoins = 0;
	bGameCleared = false;
}

// Coinから呼び出される、ゲームの進行管理の中心となる処理
void ATutorialGameManager::CollectCoin()
{
	// すでにクリアしていたら処理しない
	if (bGameCleared)
	{
		return;
	}

	// 取得枚数を1増やす
	++CollectedCoins;

	// 変更された取得枚数をBlueprintへ通知
	OnCoinCountChanged(CollectedCoins, RequiredCoins);

	// クリア条件を判定
	if (CollectedCoins >= RequiredCoins)
	{
		bGameCleared = true;

		/*
		 * GEngine ... UEのエンジンオブジェクトを参照するグローバルポインタ
		 *			   画面上のデバッグメッセージ表示などに利用
		 */
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				10002,
				15.0f,
				FColor::Green,
				TEXT("GAME CLEAR! All coins collected!")
			);
			
			/* 
			定義
			void UEngine::AddOnScreenDebugMessage(int32 Key, float TimeToDisplay, FColor DisplayColor, const FString& DebugMessage, bool bNewerOnTop, const FVector2D& TextScale)
			{
				AddOnScreenDebugMessage((uint64)Key, TimeToDisplay, DisplayColor, DebugMessage, bNewerOnTop, TextScale);
			}
			*/
		}

		UE_LOG(LogTemp, Log, TEXT("Game Clear!"));
	}
}

/*
 * Super ... 基底クラスを参照するための別名
 * AActor::BeginPlay() と概ね同じ
 */

/*
コイン取得時の処理の一連の流れ
	現在の取得状況

	1 / 3 枚

	2枚目のコインに接触したとき
	1. Overlapイベント発生
	   CollectionSphere がPawnとの接触を検知
	   
	2. OnCoinOverlap() を実行
	   取得済みか、相手がプレイヤーか確認
	   
	3. GameManagerを取得
	   GetActorOfClass() で検索
	   
	4. Manager->CollectCoin() を実行
	   CollectedCoins が1から2に変化
	   
	5. ShowProgress() で表示更新
	   Coins: 2 / 3 を表示
	   
	6. クリア判定
	   2 >= 3 はfalseなので、まだクリアしない
	   
	7. Destroy() を実行
	   取得した2枚目のコインを削除
 */

