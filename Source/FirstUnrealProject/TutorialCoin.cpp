/* コインの回転、接触検知、取得処理 */

#include "TutorialCoin.h"                   // Coinクラス自身の定義

#include "TutorialGameManager.h"            // GameManagerの関数を呼び出す

#include "Components/SphereComponent.h"     // 球体の当たり判定
#include "Components/StaticMeshComponent.h" // 3Dモデル表示
#include "GameFramework/Pawn.h"             // APawn型を使用
#include "Kismet/GameplayStatics.h"         // レベル内のActorを検索

ATutorialCoin::ATutorialCoin()
{
    // 毎フレームのTickを有効化
    PrimaryActorTick.bCanEverTick = true;

    // 接触判定用の球体を作成
    /* Unityだと、AddComponent<T> */
    CollectionSphere = CreateDefaultSubobject<USphereComponent>(
        TEXT("CollectionSphere")
    );

    // メンバ関数を使って、RootComponentを設定
    SetRootComponent(CollectionSphere);
    
    // 当たり判定の半径
    CollectionSphere->InitSphereRadius(80.0f);

    /*
     * SetCollisionEnabled() ... ComponentのCollision（衝突判定）の利用方法を設定する関数
     * ECollisionEnabled ... 衝突判定の有効状態を表す列挙型
                             設定	            意味
                             NoCollision	    衝突判定を無効化
                             QueryOnly	    クエリによる判定のみ利用し、物理シミュレーションには使用しない
                             PhysicsOnly	    物理シミュレーション用に使用
                             QueryAndPhysics	両方で使用
     */
    // 物理的には押し返さず、接触判定のみ行う
    CollectionSphere->SetCollisionEnabled(
        ECollisionEnabled::QueryOnly
    );

    /*
     * SetCollisionObjectType() ... Componentにおける自身のCollisionの種類を動的に変更する関数
                                    ECC_WorldStatic     静的なワールドオブジェクト
                                    ECC_WorldDynamic    動的なワールドオブジェクト
                                    ECC_Pawn            Pawnに対応するカテゴリ
     */
    CollectionSphere->SetCollisionObjectType(
        ECC_WorldDynamic
    );

    /*
     * SetCollisionResponseToAllChannels() ... すべてのCollision Channelに対する反応を一括で設定する関数
                                               設定	        意味
                                               ECR_Ignore	無視する
                                               ECR_Overlap	重なりを検知する
                                               ECR_Block	衝突をブロックする
     */
    CollectionSphere->SetCollisionResponseToAllChannels(
        ECR_Ignore
    );

    /*
     * SetCollisionResponseToChannel() ... 特定のCollision Channelに対する反応を動的に変更する
                                           設定	        意味
                                           ECR_Ignore	無視する
                                           ECR_Overlap	重なりを検知する
                                           ECR_Block	衝突をブロックする
     */
    // Pawnとの接触を検知する
    CollectionSphere->SetCollisionResponseToChannel(
        ECC_Pawn,
        ECR_Overlap
    );

    // Overlapイベントを有効化
    CollectionSphere->SetGenerateOverlapEvents(true);

    // 見た目となるStatic Mesh Component
    // Static Mesh Componentを作成
    CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(
        TEXT("CoinMesh")
    );

    // CoinMeshをCollectionSphereの子Componentとして配置
    CoinMesh->SetupAttachment(CollectionSphere);

    // 見た目のメッシュ自体には衝突判定を持たせない
    CoinMesh->SetCollisionEnabled(
        ECollisionEnabled::NoCollision
    );

    // 接触開始イベントとC++関数を関連付ける
    /* Unityだと、OnTriggerEnter() */
    CollectionSphere->OnComponentBeginOverlap.AddDynamic(
        this,
        &ATutorialCoin::OnCoinOverlap
    );
}

void ATutorialCoin::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 1フレームで回転する角度を計算
    const float RotationAmount = RotationSpeed * DeltaTime;

    // ワールドのZ軸を中心に回転する
    /* 左手系で、ピッチ（Y軸まわり） → ヨー（Z軸まわり） → ロール（X軸まわり）の順に指定 */
    AddActorWorldRotation(
        FRotator(0.0f, RotationAmount, 0.0f)
    );
}

// コインを取得する処理
void ATutorialCoin::OnCoinOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    // 取得済みなら何もしない
    if (bCollected)
    {
        return;
    }

    /*
     * Cast<APawn>() ... UEのUObject系オブジェクトが指定した型として扱えるかを確認し、可能ならその型のポインタを返す
     */
    // 接触相手がプレイヤー操作中のPawnか確認（接触したActorをAPawnとして扱えるか確認）
    APawn* Pawn = Cast<APawn>(OtherActor);

    if (!Pawn || !Pawn->IsPlayerControlled())
    {
        return;
    }

    // レベル内に配置されたGameManagerを探す
    ATutorialGameManager* Manager =
        Cast<ATutorialGameManager>( // 指定したワールド内から、指定したクラスのActorを検索する関数
            UGameplayStatics::GetActorOfClass(
                GetWorld(),                         // 現在のActorが属するワールドを取得
                ATutorialGameManager::StaticClass() // ATutorialGameManager のクラス情報を表す UClass* を取得する関数
            )
        );

    // GameManagerが見つからない場合
    if (!Manager)
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT("TutorialGameManager not found!")
        );

        return;
    }

    // 二重取得を防止
    bCollected = true;

    // GameManagerに取得を通知
    Manager->CollectCoin();

    // コインを削除
    Destroy();
}
