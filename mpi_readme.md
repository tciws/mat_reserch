# MPIプログラミング
## MPI雑感
- rank0はプログラム実行と同時に作成される
- rank1以降はMPI_INITをcallする時点で作成される.
- rank同士は基本思い思いに動作する.
- MPI_SEND,MPI_Recvはデッドロックが発生する可能性がある
- MPI_BCASTは放送
- MPI_
## 構文集
-
