int out_file_func(int signal[5]){
  switch(signal[0]){
    case 1:
    //load命令
      switch(signal[4]){
        case 0:
        //addr
        fprintf(outfile, "load  R%d,%d\n", signal[1],signal[3]);
        break;
        case 1:
        //label
        fprintf(outfile, "load  R%d,E%d\n", signal[1],signal[3]);
        break;
        case 2:
        //resister
        fprintf(outfile, "loadr  R%d,R%d\n", signal[1],signal[2]);
        break;
        case 3:
        //immediate
        fprintf(outfile, "loadi  R%d,%d\n", signal[1],signal[3]);
        break;
        case 4:
        fprintf(outfile, "load  R%d,%d(BR)\n", signal[1],signal[3]);
        break;
      }
    break;
    case 2:
    //store命令
      switch(signal[4]){
        case 0:
        //addr
        fprintf(outfile, "store  R%d,%d\n", signal[1],signal[3]);
        break;
        case 1:
        //label
        fprintf(outfile, "store  R%d,E%d\n", signal[1],signal[3]);
        break;
        case 2:
        fprintf(outfile, "store  R%d,%d(BR)\n", signal[1],signal[3]);
        break;
      }
    break;
    case 3:
    //add命令
      switch(signal[4]){
        case 0:
        //addr
        fprintf(outfile, "add  R%d,%d\n", signal[1],signal[3]);
        break;
        case 1:
        //label
        fprintf(outfile, "add  R%d,E%d\n", signal[1],signal[3]);
        break;
        case 2:
        //register
        fprintf(outfile, "addr  R%d,R%d\n", signal[1],signal[2]);
        break;
        case 3:
        //immediate
        fprintf(outfile, "addi  R%d,%d\n", signal[1],signal[3]);
        break;
        case 4:
        fprintf(outfile, "add  R%d,%d(BR)\n", signal[1],signal[3]);
        break;
      }
    break;
    case 4:
    //subtract命令
      switch(signal[4]){
        case 0:
        //addr
        fprintf(outfile, "sub  R%d,%d\n", signal[1],signal[3]);
        break;
        case 1:
        //label
        fprintf(outfile, "sub  R%d,E%d\n", signal[1],signal[3]);
        break;
        case 2:
        //register
        fprintf(outfile, "subr  R%d,R%d\n", signal[1],signal[2]);
        break;
        case 3:
        //immediate
        fprintf(outfile, "subi  R%d,%d\n", signal[1],signal[3]);
        break;
        case 4:
        fprintf(outfile, "sub  R%d,%d(BR)\n", signal[1],signal[3]);
        break;
      }
    break;
    case 5:
    //multiply命令
    switch(signal[4]){
        case 0:
        //addr
        fprintf(outfile, "mul  R%d,%d\n", signal[1],signal[3]);
        break;
        case 1:
        //label
        fprintf(outfile, "mul  R%d,E%d\n", signal[1],signal[3]);
        break;
        case 2:
        //register
        fprintf(outfile, "mulr  R%d,R%d\n", signal[1],signal[2]);
        break;
        case 3:
        //immediate
        fprintf(outfile, "muli  R%d,%d\n", signal[1],signal[3]);
        break;
        case 4:
        fprintf(outfile, "mul  R%d,%d(BR)\n", signal[1],signal[3]);
        break;
      }
    break;
    case 6:
    //divide命令
    switch(signal[4]){
        case 0:
        //addr
        fprintf(outfile, "div  R%d,%d\n", signal[1],signal[3]);
        break;
        case 1:
        //label
        fprintf(outfile, "div  R%d,E%d\n", signal[1],signal[3]);
        break;
        case 2:
        //register
        fprintf(outfile, "divr  R%d,R%d\n", signal[1],signal[2]);
        break;
        case 3:
        //immediate
        fprintf(outfile, "divi  R%d,%d\n", signal[1],signal[3]);
        break;
        case 4:
        fprintf(outfile, "div  R%d,%d(BR)\n", signal[1],signal[3]);
        break;
      }
    break;
    case 7:
    //compare命令
    switch(signal[4]){
        case 0:
        //addr
        fprintf(outfile, "cmp  R%d,%d\n", signal[1],signal[3]);
        break;
        case 1:
        //label
        fprintf(outfile, "cmp  R%d,E%d\n", signal[1],signal[3]);
        break;
        case 2:
        //register
        fprintf(outfile, "cmpr  R%d,R%d\n", signal[1],signal[2]);
        break;
        case 3:
        //immediate
        fprintf(outfile, "cmpi  R%d,%d\n", signal[1],signal[3]);
        break;
        case 4:
        fprintf(outfile, "cmp  R%d,%d(BR)\n", signal[1],signal[3]);
        break;
      }
    break;
    case 8:
    //jump命令
    switch(signal[1]){
      case 0:
      //if
      {
        switch(signal[4]){
            case 0:
            //強制ジャンプ
            fprintf(outfile, "jmp  L%d\n",signal[3]);
            break;
            case 1:
            //non0のときジャンプ
            fprintf(outfile, "jnz  L%d\n",signal[3]);
            break;
            case 2:
            //eql0のときジャンプ
            fprintf(outfile, "jz  L%d\n",signal[3]);
            break;
            case 3:
            //>0のときジャンプ
            fprintf(outfile, "jgt  L%d\n",signal[3]);
            break;
            case 4:
            //>=0のときジャンプ
            fprintf(outfile, "jge  L%d\n",signal[3]);
            break;
            case 5:
            //<0のときジャンプ
            fprintf(outfile, "jlt  L%d\n",signal[3]);
            break;
            case 6:
            //<=0のときジャンプ
            fprintf(outfile, "jle  L%d\n",signal[3]);
            break;
        }
      }
      break;
      case 1:
      //while
      {
        switch(signal[4]){
            case 0:
            //強制ジャンプ
            fprintf(outfile, "jmp  W%d\n",signal[3]);
            break;
            case 1:
            //non0のときジャンプ
            fprintf(outfile, "jnz  W%d\n",signal[3]);
            break;
            case 2:
            //eql0のときジャンプ
            fprintf(outfile, "jz  W%d\n",signal[3]);
            break;
            case 3:
            //>0のときジャンプ
            fprintf(outfile, "jgt  W%d\n",signal[3]);
            break;
            case 4:
            //>=0のときジャンプ
            fprintf(outfile, "jge  W%d\n",signal[3]);
            break;
            case 5:
            //<0のときジャンプ
            fprintf(outfile, "jlt  W%d\n",signal[3]);
            break;
            case 6:
            //<=0のときジャンプ
            fprintf(outfile, "jle  W%d\n",signal[3]);
            break;
        }
      }
    }
    break;
    case 9:
    switch(signal[4]){
      case 0:
      //文字列
      fprintf(outfile, "writec  R%d\n",signal[1]);
      break;
      case 1:
      //数字
      fprintf(outfile, "writed  R%d\n",signal[1]);
      break;
      case 3:
      //文字列
      fprintf(outfile,"loadi  R0,10\n");
      fprintf(outfile, "writec  R0\n");
      break;
      case 4:
      //文字列
      fprintf(outfile,"loadi  R0,9\n");
      fprintf(outfile, "writec  R0\n");
      break;
    }
    break;
    case 10:
    fprintf(outfile, "L%d:\n",signal[3]);
    break;
    case 11:
    //サイズの大きな値を格納用
    fprintf(outfile, "E%d:data %d\n",signal[3],signal[4]);
    break;
    case 12:
    fprintf(outfile, "halt\n");
    break;
    case 13:
    fprintf(outfile, "push  R%d\n",signal[1]);
    break;
    case 14:
    fprintf(outfile, "pop  R%d\n",signal[1]);
    break;
    case 15:
    fprintf(outfile, "call  L%d\n",signal[3]);
    break;
    case 16:
    fprintf(outfile, "return\n");
    break;
    case 17:
    fprintf(outfile, "main:\n");
    break;
    case 18:
    fprintf(outfile, "jmp main\n");
    break;
    case 19:
    fprintf(outfile, "call  proc\n");
    break;
    case 20:
    fprintf(outfile, "proc:\n");
    break;
  }
