/* コインの取得枚数管理とクリア判定 */

#include "TutorialGameManager.h"		// 自分自身のクラス定義
#include "Components/SceneComponent.h"	// USceneComponentを使用する
#include "kismet/GameplayStatics.h"

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

		// Blueprintにゲームクリアを通知
		OnGameCleared();

		UE_LOG(LogTemp, Log, TEXT("Game Clear!"));
	}
}

void ATutorialGameManager::RestartGame()
{
	// ゲームクリア前のリスタート防止
	if (!bGameCleared)
	{
		return;
	}
	
	// 現在プレイしているレベルの名前を取得
	const FString CurrentLevelName =
		UGameplayStatics::GetCurrentLevelName(this, true);
	/*
		型			主な用途					特徴
		FString		文字列の生成・編集			文字列操作に適している
		FName		名前・識別子				名前の比較や識別に適している
		FText		プレイヤー向けの表示文字	ローカライズに対応
	 */
	
	// レベル名を取得できなかった場合は処理を中断
	if (CurrentLevelName.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to get current level name."));
		return;
	}
	
	// リスタートするレベル名をログに出力
	UE_LOG(
		LogTemp,
		Log,
		TEXT("Restarting level: %s"),
		*CurrentLevelName
	);
	
	// 現在のレベルを再読み込みする
	UGameplayStatics::OpenLevel(
		this,
		FName(*CurrentLevelName) // FStringをFNameにキャスト
	);
	/*
	OpenLevel() ... 指定したレベルへ遷移する関数
	static void OpenLevel(
		const UObject* WorldContextObject,
		FName LevelName,
		bool bAbsolute = true,
		FString Options = FString(TEXT(""))
	);
	引数					役割										今回の値
	WorldContextObject	対象ワールドを特定する						this
	LevelName			開くレベルの名前							現在のレベル名
	bAbsolute			現在のレベルのURLオプションを引き継ぐかどうか	true（デフォルト）
	Options				レベル遷移時の追加オプション				空文字列（デフォルト）
	*/
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

