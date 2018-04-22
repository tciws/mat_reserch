**1.void statement(void);**<br>
- 構文解析用メイン関数
- **tok.attr**の値によって処理が変化
- ピリオドを読むと強制終了

<br>
**2.void rwo_func(void);**<br>
- **var**を読むと**teigi**に飛ぶようになっている

<br>
**3.void num_func(void);**<br>
<br>
**4.void sym_func(void);**<br>
<br>
**5.void ope_func(void);**<br>
<br>
**6.void ident(void);**<br>
- tmpは１つめのアドレスを格納するための変数
- tmp2は２つめのアドレスを格納するための変数
- :=が存在したとき**getsym()**をして、次のトークンを読む。トークンによって処理が変わる。
  - 変数の場合
    - 1.変数が記号表の中にあるか探索
    - 2.アドレスから変数の中身をロード
    - 3.

  - 数字の場合

<br>
**7.void teigi(void);**<br>
- 変数記号表作成用関数
- **ide[hoge].ptr**には変数文字列を入れる
- **ide[hoge].adr**には変数のアドレス
- 最後に**getsym()**をして、次のトークンがカンマだった場合は自身の関数を呼び出す

<br>
**8.int search(void);**
- グローバル変数**tok.charvalue**に格納されている文字列を変数表から探す関数
- 戻り値は変数が存在する場合はアドレスを返し、ない場合は0を返す。
