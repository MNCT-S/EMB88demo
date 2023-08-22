# EMB88demo
組み込み開発のための実践的プログラミング  
EMB-88 のデモソリューション

## Requirement
~~Atmel Studio 7.0~~  
VScode に移行

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
無効にすると45度ずつ動きます  
電源ON時に，PB1が'L'で2相励磁，PB2が'L'で1-2相励磁，何もつなげなければ1相励磁に切り替えできます  
Author : Kenichi Magara / NIT, Maizuru College (KOSEN)

- MAIZURU  
MAIZURUの文字をマトリックスLEDに表示  
Author : Kenichi Magara / NIT, Maizuru College (KOSEN)

- Mario  
国民的ゲームの音を鳴らします．  
SW1 で始まりの音  
SW2 で終わりの音  
Author : Kenichi Magara / NIT, Maizuru College (KOSEN)
