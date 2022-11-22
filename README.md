# HighScoreAttack
cocos2dゲームリポジトリ  

# 開発環境
* Editor Visual Studio 2017
* [python](https://www.python.org/downloads/)  
cocos2dのインストールに必要　
* [cocos2d-x-3.15.1  
Cocos Console 2.3](https://cocos2d-x.org/download)  
新規にcocos2dプロジェクトを立ち上げる場合はコマンドから  
```bash
cocos new プロジェクト名 -p 識別子任意の名前 -l cpp -d 作成ディレクトリのパス
```  

* windows用リリースデプロイをする際は
```bash
 cocos deploy -s path -p win32 -m release  
```  
pathはcocosプロジェクトのカレントディレクトリ  
終了後に
```bash
 ./bin/release/win32  
```  
内にビルド結果が作成されるのでその中の  
```bash
 プロジェクト名.exe  
```  
ファイルを実行でゲームを起動させることができる  

* マニュアル
```bash
 ./Manual/index.html  
```  
にマニュアルを用意していますのでそちらを参照してください
