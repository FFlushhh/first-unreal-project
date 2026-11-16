/* コインクラスの定義 */
/* コインを回転させ、プレイヤーとの接触を検知し、GameManagerへ取得を通知する */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutorialCoin.generated.h"

/*
 * 前方宣言 ... クラスや構造体の完全な定義を提供せずに、コンパイラに「その名前の型や関数が存在する」ことを伝えて、
 *			   その名前を他のクラスや関数で使用できるようにする宣言
 *			   ヘッダファイルで前方宣言しておき、ソースファイルでincludeする
 */
class USphereComponent;
class UStaticMeshComponent;
class UPrimitiveComponent;

UCLASS()
class FIRSTUNREALPROJECT_API ATutorialCoin : public AActor
{
	GENERATED_BODY()

public:
	ATutorialCoin();

	// 毎フレーム呼ばれる
	virtual void Tick(float DeltaTime) override;

protected:
	
	/* 
	 * TObjectPtr ... Unreal EngineのUObject系インスタンスへの参照を保持するための型
	 *				  UPROPERTY() を付けたメンバーとして使用する場合、UEのガベージコレクションに追跡される強い参照として機能する
	 */
	
	/*
	 * USphereComponent ... 球体の当たり判定を持つComponent
	 *						UnityのSphereColliderに近い
	 * UStaticMeshComponent ... Statick MEshを表示するためのComponent
	 *							UnityのMeshFilterとMeshRendererに近い機能をまとめて持つ
	 */
	// コイン取得の当たり判定
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	TObjectPtr<USphereComponent> CollectionSphere;

	// コインの3Dモデル
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	TObjectPtr<UStaticMeshComponent> CoinMesh;

	// 1秒あたりの回転速度（度）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	float RotationSpeed = 120.0f;

	/*
	 * UFUNCTION() ... C++の関数をUEのリフレクションシステムへ登録するためのマクロ
	 */
	// SphereのOverlap開始時に呼ばれる
	UFUNCTION()
	void OnCoinOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	/*
	  引数					意味
	  OverlappedComponent	接触イベントを受け取ったComponent
	  OtherActor			接触した相手のActor
	  OtherComp				接触した相手側のComponent
	  OtherBodyIndex		相手のボディ識別用インデックス
	  bFromSweep			移動によるSweep判定に伴う接触かどうか
	  SweepResult			Sweepに関する接触情報
	 */

private:
	// 同じコインの二重取得を防ぐ
	bool bCollected = false;
};
