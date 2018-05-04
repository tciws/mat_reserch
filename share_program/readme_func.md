## 大域変数
- TOKEN tok;  
  getsymのトークン管理用変数
- FILE *infile;  
  ファイル処理
- FILE *outfile;  
  ファイル処理
- int spt;  
  ??
- hensu ide[H];  
  変数表
- int sym,num;  
  ??
- int add;  
  変数アドレス格納用x:=数式;  
  の場合のxのアドレス保持用
- int typesel;  
  使ってない？要検証
- int lv;  
  ラベル管理用、使ってない？
- int sig[SIG_MAX];  
  最終出力制御用配列
- int rx[6];  
  レジスタの空き状況を示配列
- int label;  
  ラベル付に使ってる？
- int osin;
  ??
- int st;  
  ??
- int cal_times;  
  expression関数の再帰の階数を表したもの
- int num_add;
