/* ゲーム管理クラスの定義 */

#pragma once

#include "CoreMinimal.h"					// UEで広く利用する基本的な方や機能
#include "GameFramework/Actor.h"			// AActorクラスの定義
#include "TutorialGameManager.generated.h"	// UEが自動生成する、このクラス用の補助コード

UCLASS() // クラスをUEのリフレクションシステムに認識させるマクロ
class FIRSTUNREALPROJECT_API ATutorialGameManager : public AActor
{
	// UEのオブジェクトシステムに必要な宣言をクラスへ組み込むマクロ
	GENERATED_BODY()

public:
	ATutorialGameManager();

	// コインを取得した際に呼ばれる
	void CollectCoin();

	/*
	 * UFUNCTION() ... C++の関数をUEのリフレクションシステムへ登録するためのマクロ
	 *				   C++から呼び出せるが、実際の処理内容はBlueprint側で定義する
	 */
	// コインの取得枚数が変化したことをBlueprintに通知する
	UFUNCTION(BlueprintImplementableEvent, Category = "Coin Game")
	void OnCoinCountChanged(int32 CurrentCoins, int32 TotalCoins);

protected:
	// ゲーム開始時に一度だけ実行される
	virtual void BeginPlay() override;

	// クリアに必要なコイン数
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Coin Game",
			  meta = (ClampMin = "1"))
	int32 RequiredCoins = 3;

	// 現在取得したコイン数
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin Game")
	int32 CollectedCoins = 0;

private:
	// クリア処理の重複実行を防ぐ
	bool bGameCleared = false;
};


/* 
アクセス指定子	自分のクラス	   派生クラス    外部クラス
  public	     利用可能	    利用可能		利用可能
 protected		 利用可能		利用可能		原則不可
  private	     利用可能		原則不可		原則不可
*/

/*
 * UPROPERTY() ... C++のメンバ変数をUEのプロパティシステムへ公開・登録するマクロ
 */

/*
接頭辞	代表例
A		AActor, APawn, ACharacter
U		UObject, USceneComponent
F		FString, FVector, FRotator
E		ECollisionEnabled などの列挙型
T		TArray, TObjectPtr などのテンプレート型
b		bCollected, bGameCleared などのbool変数

参考：https://qiita.com/waigoma/items/05c972add9607f969d13
 */
