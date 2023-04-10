# Blocking, Synchronous I/O

## Blocking / Non-Blocking I/O 란?

- 유저 프로그램에서 요청한 I/O 작업이 완료될 때까지
  - CPU를 놓는다(Non-Blocking).
  - CPU를 안 놓는다(Blocking). Waiting, Sleeping 상태로 들어간다.

## Synchrounous / Asynchronous 란?

- 유저 프로그램에서 요청한 I/O 작업이 완료될 때까지
  - 같은 흐름에서 처리한다(Synchronous).
  - 같은 흐름에서 처리하지 않는다(Asynchronous).
    - 비동기 처리 예시: 개별 Thread 활용, Callback 함수 활용(시그널 핸들러, 이벤트 핸들러 등)

## I/O Multiplexing

하나의 프로세스에서 여러 파일 디스크립터를 관리하고 방법.

`select()`

## 참조

- [Blocking-NonBlocking-Synchronous-Asynchronous](https://homoefficio.github.io/2017/02/19/Blocking-NonBlocking-Synchronous-Asynchronous/) - HomoEfficio
- [Boost application performance using asynchronous I/O](https://developer.ibm.com/articles/l-async/) - IBM Developer
- 리눅스 시스템 핵심 (Non-Blocking I/O와 select 이해와 실습) - 리얼 리눅스
- [I/O Multiplexing 톺아보기 (1부)](https://incredible-larva.tistory.com/entry/IO-Multiplexing-%ED%86%BA%EC%95%84%EB%B3%B4%EA%B8%B0-1%EB%B6%80)
- [I/O Multiplexing 톺아보기 (2부)](https://incredible-larva.tistory.com/entry/IO-Multiplexing-%ED%86%BA%EC%95%84%EB%B3%B4%EA%B8%B0-2%EB%B6%80)
- https://github.com/xpdojo/python/blob/cc0f32fa7fc60e0c76a04d18d717971bdf2bcc6c/lang/async/blocking_asynchronous.py
