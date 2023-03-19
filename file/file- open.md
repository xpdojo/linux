# File 열기

## task_struct

- fd table[]
  - 0번은 표준 입력(stdin)
  - 1번은 표준 출력(stdout)
  - 2번은 표준 에러(stderr)
  - 3번째 인덱스에는 프로세스가 열어놓은 첫 번째 파일, 소켓, 파이프 등의 file descriptor가 할당된다.
    이 값은 3 이상의 정수값으로, 프로세스가 실행되는 동안 열린 각 파일, 소켓, 파이프 등은 고유한 file descriptor 값을 갖게 된다.

## redirect(`>`)

```bash
uftrace record -la bash -c "echo 'hello' > hello.txt"
```

`hello.txt` 파일을 생성하는 과정에서 리다이렉트(`>`) 사용시
`stdout`으로 사용중인 파일 디스크립터 `1`을 `hello.txt` 파일 디스크립터로 변경한다.

```bash
  61.179 us [  3871] | open("hello.txt", O_TRUNC|O_CREAT|O_WRONLY) = 4;  
...
   3.073 us [  3871] | dup2(4, 1) = 1;
```

4번은 task_struct `dup2(4, 1)`는 "fd 변경: 4 -> 1"을 의미한다.

## pipe(`|`)

```bash
uftrace record -la bash -c "cat hello.txt | wc -l"
```

`cat` 프로그램은 `hello.txt`를 열고 read 후 write를 통해서 `stdout(1)` 에 출력한다.
`wc` 프로그램은 터미널 tty 파일 디스크립터를 `stdin(0)` 으로 변경한다.

```bash
 193.598 us [  3942] | open("/dev/tty", O_NONBLOCK|O_RDWR) = 4;
   6.704 us [  3942] | open("hello.txt", O_RDONLY) = 5;
...
   2.506 us [  3942] | read(5, 0x7f85afbfb000, 0x20000) = 6;
   2.003 us [  3942] | write(1, 0x7f85afbfb000, 6) = 6;
   3.073 us [  3943] | dup2(4, 0) = 0;
```

`dup2(4, 0)`는 "fd 변경: 4 -> 0”을 의미한다.
결과적으로  `wc` 프로그램은 파일 디스크립터 `0`으로 read 하면 `hello.txt` 내용을 읽게 된다.
