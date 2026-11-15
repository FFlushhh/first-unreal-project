# FirstUnrealProject

Unreal Engine 5とC++を用いたゲーム開発を学習するための個人プロジェクトです。

## 開発環境

- **ゲームエンジン：** Unreal Engine 5.8.4
- **プログラミング言語：** C++
- **ビジュアルスクリプティング：** Blueprint
- **IDE：** JetBrains Rider
- **OS：** Windows
- **バージョン管理：** Git / GitHub

## プロジェクト概要

Unreal Engine 5のThird Person（三人称視点）テンプレートをベースにした学習用プロジェクトです。

キャラクター操作などの既存機能を活用しながら、C++によるゲームロジックの実装やBlueprintとの連携など、Unreal Engine特有の開発手法の習得を目指しています。

## 開発状況

現在、Third Personテンプレートによるプロジェクトを作成し、開発環境とバージョン管理の整備を進めています。

今後は、C++によるゲーム機能を段階的に実装する予定です。

## 実行方法

1. Unreal Engine 5.8.4をインストールします。
2. 本リポジトリをローカル環境にクローンします。
3. `FirstUnrealProject.uproject`を開きます。
4. C++のビルドが必要な場合は、対応する開発環境でEditorターゲットをビルドします。
5. Unreal Editor上でレベルを開き、Playボタンから実行します。

C++のビルドには、Unreal Engine 5.8.4に対応するMSVCツールチェーンとWindows SDKが必要です。

## ディレクトリ構成

- `Config/`：ゲームやエンジンの設定ファイル
- `Content/`：レベル、Blueprint、マテリアルなどのゲームアセット
- `Source/`：C++のソースコード
- `FirstUnrealProject.uproject`：Unreal Engineプロジェクトファイル

## コントリビューション

開発・変更に関する方針は、[CONTRIBUTING.md](CONTRIBUTING.md)を参照してください。