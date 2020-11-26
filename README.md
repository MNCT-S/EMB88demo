# EMB88demo
組み込み開発のための実践的プログラミング  
EMB-88 のデモソリューション

## Requirement
Atmel Studio 7.0

***
## 各プロジェクトの説明 
書き込み時は［スタートアッププロジェクトに設定］を忘れずに．

- ExBoard  
オリジナル拡張ボードでアクチュエータ（モータとサーボ）の動作デモ  
SW1で正回転，SW2で逆回転します  
Author : Kenichi Magara / NIT, Maizuru College (KOSEN)

- ExBoardSTM  
オリジナル拡張ボードでステッピングモータの動作デモ  
SW1で正回転，SW2で逆回転します  
プログラム内の SLOW_MODE を有効にすると，人間の目にもわかるくらいのスピードで動きます  
1相励磁・1-2相励磁・2相励磁の切り替えは，mode 変数を変えてください  
（動的に変えたかったがEMB-88の制約であきらめた）  
Author : Kenichi Magara / NIT, Maizuru College (KOSEN)

- MAIZURU  
MAIZURUの文字をマトリックスLEDに表示  
Author : Kenichi Magara / NIT, Maizuru College (KOSEN)
