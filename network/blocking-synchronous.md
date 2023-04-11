# Blocking, Synchronous I/O

## Blocking / Non-Blocking I/O 란?

- 호출되는 함수가 바로 리턴하느냐 마느냐가 관심사다.
- 쉽게 말하면:
    - Blocking은 작업이 완료될 때까지 다른 작업을 수행하지 않는 것을 의미한다.
    - Non-blocking은 작업이 완료되지 않아도 다른 작업을 수행할 수 있는 것을 의미한다.
- 명확하게 말하면:
    - Blocking은 호출된 함수가 자신의 작업을 모두 마칠 때까지 호출한 함수에게 `제어권`을 넘겨주지 않고 대기하게 만든다.
    - Non-Blocking은 호출된 함수가 바로 리턴해서 호출한 함수에게 `제어권`을 넘겨주고 호출한 함수가 다른 일을 할 수 있게 한다.
- 예를 들어,
    - Blocking I/O는 데이터가 도착하기 전까지 응용 프로그램이 멈추고 대기해야 한다.
    - Non-blocking I/O는 데이터가 도착하기를 기다리지 않고 계속 실행된다.
- 유저 프로그램에서 요청한 I/O 작업이 완료될 때까지
    - CPU를 안 놓는다(Blocking). Waiting, Sleeping 상태로 들어간다.
    - CPU를 놓는다(Non-Blocking).
- 이 차이는 파일 입출력 응용 프로그램을 만들면 명확하게 알 수 있다.
    - 비동기 호출을 했지만 Blocking 입출력을 할 경우 응용 프로그램이 멈춘다.
- 마찬가지로 웹 애플리케이션에서 비동기 호출을 했지만 DB에서 데이터 조회 시 Blocking I/O를 수행할 경우 해당 트랜잭션에서 계속 대기한다.
    - 따라서 DB에서 데이터 조회 시 Non-blocking I/O가 필요한 경우가 있다.

## Synchrounous / Asynchronous 란?

- 호출되는 함수의 작업 완료 여부를 누가 신경쓰느냐가 관심사다.
- 쉽게 말하면:
    - Synchronous는 호출된 함수가 결과를 반환할 때까지 호출하는 함수가 대기해야 하는 것을 의미한다.
    - Asynchronous는 호출된 함수가 결과를 반환하기를 기다리지 않고 호출하는 함수가 다른 작업을 수행할 수 있는 것을 의미한다.
- 명확하게 말하면:
    - Synchronous는 호출하는 함수가 호출되는 함수의 작업 완료 후 리턴을 기다리거나,
      또는 호출되는 함수로부터 바로 리턴 받더라도 작업 완료 여부를 호출하는 함수 스스로 계속 확인하며 신경쓴다.
    - Asynchronous는 호출되는 함수에게 callback을 전달해서 호출되는 함수의 작업이 완료되면
      호출되는 함수가 전달받은 callback을 실행하고, 호출하는 함수는 작업 완료 여부를 신경쓰지 않는다.
- 예를 들어,
    - Synchronous 함수는 호출자가 함수가 반환할 때까지 기다려야 한다.
    - Asynchronous 함수는 호출자가 반환하기를 기다리지 않고 다른 작업을 수행할 수 있다.
- 유저 프로그램에서 요청한 I/O 작업이 완료될 때까지
    - 같은 흐름에서 처리한다(Synchronous).
    - 같은 흐름에서 처리하지 않는다(Asynchronous).
        - 비동기 처리 예시: 개별 Thread 활용, Callback 함수 활용(시그널 핸들러, 이벤트 핸들러 등)

## I/O Multiplexing

하나의 프로세스에서 여러 파일 디스크립터를 관리하고 방법이다.
I/O Multiplexing 기법은 `select`, `poll`, `epoll`과 같은 시스템 콜을 사용한다.
이러한 시스템 콜은 파일 디스크립터의 상태 변화를 감지하고,
상태 변화가 발생한 파일 디스크립터에 대해서만 블로킹되지 않고 바로 작업을 처리할 수 있도록 한다.
이를 통해 다수의 I/O 작업을 블로킹되지 않고 비동기적으로 처리할 수 있게 된다.

`select`, `poll`, `epoll`은 모두 I/O 멀티플렉싱을 위한 시스템 콜이다.
이들은 모두 여러 개의 파일 디스크립터를 모니터링하면서 입출력 가능한 이벤트가 발생하면
해당 이벤트를 처리하기 위해 호출한 프로세스에 알려준다.
이들 시스템 콜의 차이점은 다음과 같다.

- `select`와 `poll`은 파일 디스크립터를 매번 시스템 콜에 전달해야 한다.
  이에 반해 `epoll`은 `epoll` 인스턴스라는 객체를 생성하고,
  이를 통해 관심있는 파일 디스크립터를 등록하여 사용한다.
- `select`는 파일 디스크립터의 수가 커지면 성능이 떨어지는 단점이 있다.
  이에 비해 `poll`은 이를 보완하고자 등장했지만, 여전히 비효율적이다.
  `epoll`은 등록된 파일 디스크립터에 대해 이벤트 발생 시 해당 이벤트를
  바로 알려주기 때문에 대규모 네트워크 프로그래밍에서 더욱 성능이 우수하다.
- `select`와 `poll`은 블로킹 호출 방식을 사용한다.
  이에 반해 `epoll`은 논블로킹 호출 방식을 사용한다.

따라서 대부분의 경우에는 `epoll`을 사용하는 것이 가장 적합하다.
다만, 운영체제의 종류나 네트워크 환경에 따라서는 `select`나 `poll`을 사용해야 하는 경우가 있을 수 있다.

## 참조

- [Blocking-NonBlocking-Synchronous-Asynchronous](https://homoefficio.github.io/2017/02/19/Blocking-NonBlocking-Synchronous-Asynchronous/) -
  HomoEfficio
- [Boost application performance using asynchronous I/O](https://developer.ibm.com/articles/l-async/) - IBM Developer
- 리눅스 시스템 핵심 (Non-Blocking I/O와 select 이해와 실습) - 리얼 리눅스
- [I/O Multiplexing 톺아보기 (1부)](https://incredible-larva.tistory.com/entry/IO-Multiplexing-%ED%86%BA%EC%95%84%EB%B3%B4%EA%B8%B0-1%EB%B6%80)
- [I/O Multiplexing 톺아보기 (2부)](https://incredible-larva.tistory.com/entry/IO-Multiplexing-%ED%86%BA%EC%95%84%EB%B3%B4%EA%B8%B0-2%EB%B6%80)
- [python example](https://github.com/xpdojo/python/blob/cc0f32fa7fc60e0c76a04d18d717971bdf2bcc6c/lang/async/blocking_asynchronous.py)
