# mbed_usbps4

ほぼ自分用ライブラリ、
Arduino GIGA R1 (Mbed OS) などの環境で、PlayStation 4 コントローラー (DualShock 4) をUSBホスト機能経由で直接制御するためのライブラリです。  
Arduino GIGA R1でUSB Host shield 2.0無しでps4コントローラー使用できるlibraryであり、また
`USBHostShield2.0` の `PS4.h` と高い互換性を持つAPIを提供しており、過去のコードからの移行が容易です。  
ですが挙動は完全に同じわけではなく、、少し違ったりするためちゅいが必要です。  
例えば、「Click」を例に出すと、Clickが実行されるまでClickした情報がバッファで保存され、実行してから、正常に終了するまで待機します。

## 特徴
- Mbed OS の `Arduino_USBHostMbed5` をバックエンドに使用(そのため`Arduino_USBHostMbed5`を先に導入をしておいてください)
- USBHostShield 2.0 互換の API 命名規則 (`getButtonPress`, `getButtonClick`, `getAnalogHat` など)
- 押しっぱなし (Press) と 押した瞬間 (Click) の両方のイベント検出に対応
- ※ロボコンで使用することを想定した設計になるため、LEDや振動系は完全に抜いています。
- 十字キー、各種ボタン、アナログスティック、L2/R2アナログ値の取得に対応

- 実戦で使用できるレベルのスケッチ例を付属しています。（それを見れば使い方が一瞬でわかるはずです）
  
## 対応ボード
- Arduino GIGA R1 WiFi
- その他 Mbed OS 5 ベースの USB Host 対応 Arduino ボード
- ※もちろんusb host shield 2.0とは互換性がありません。（互換性があるのはコードのみです）

## インストール方法
1. このリポジトリのリリースから ZIP ファイルをダウンロードします。
2. Arduino IDE を開き、`スケッチ` > `ライブラリをインクルード` > `.ZIP形式のライブラリをインストール...` を選択します。
3. ダウンロードした ZIP ファイルを選択してインストールを完了させてください。
- <img width="712" height="361" alt="Image" src="https://github.com/user-attachments/assets/16fed481-7f32-46b5-ac18-06a537f9724a" />
- <img width="952" height="521" alt="Image" src="https://github.com/user-attachments/assets/0ba12112-457b-4fa8-af18-ac78b39c9383" />
## スケッチ例
付属しているスケッチ例はすでに実践的に使用可能なレベルのものです。
スケッチ例を呼び出す方法については以下です。
1. `ファイル` > `スケッチ例` > `カスタムライブラリのスケッチ例`から、`mbed_usbps4` > `PS4USB_GIGA_R1_base`
2. あとは好きにコードを書くのじゃ
- <img width="661" height="707" alt="Image" src="https://github.com/user-attachments/assets/19bcd3f1-6881-4428-a195-2b22a16a1bbb" />
