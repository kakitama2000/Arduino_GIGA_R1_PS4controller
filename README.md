# mbed_usbps4

ほぼ自分用ライブラリ
Arduino GIGA R1 (Mbed OS) などの環境で、PlayStation 4 コントローラー (DualShock 4) をUSBホスト機能経由で直接制御するためのライブラリです。
Arduino GIGA R1でUSB Host shield 2.0無しでps4コントローラー使用できるlibraryであり、また
`USBHostShield2.0` の `PS4.h` と高い互換性を持つAPIを提供しており、過去のコードからの移行が容易です。

## 特徴
- Mbed OS の `Arduino_USBHostMbed5` をバックエンドに使用
- USBHostShield 2.0 互換の API 命名規則 (`getButtonPress`, `getButtonClick`, `getAnalogHat` など)
- 押しっぱなし (Press) と 押した瞬間 (Click) の両方のイベント検出に対応
- ※ロボコンで使用することを想定した設計になるため、LEDや振動系は完全に抜いています。
- 十字キー、各種ボタン、アナログスティック、L2/R2アナログ値の取得に対応
- 実戦で使用できるレベルのスケッチ例を付属しています。
  
## 対応ボード
- Arduino GIGA R1 WiFi
- その他 Mbed OS 5 ベースの USB Host 対応 Arduino ボード
- ※もちろんusb host shield 2.0とは互換性がありません。（互換性があるのはコードのみです）

## インストール方法
1. このリポジトリのリリースから ZIP ファイルをダウンロードします。
2. Arduino IDE を開き、`スケッチ` > `ライブラリをインクルード` > `.ZIP形式のライブラリをインストール...` を選択します。
3. ダウンロードした ZIP ファイルを選択してインストールを完了させてください。
