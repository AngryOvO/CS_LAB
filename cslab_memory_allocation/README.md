# Python Memory Allocation 시간 분석

파이썬 언어에서 메모리 할당량이 높아질수록 프로세스 실행시간이 급격하게 느려지는 현상 관측 및 대안 분석

## 실험 환경

Rocky-Linux 9.2 SSH 서버
CPU : Intel Core i7 - 4790 3.60GHz
RAM : 7.5Gi

### 언어별 동일한 크기의 메모리 할당 시간 비교

1. Python의 메모리 할당 시간 체크

```
y = []
    for i in range(300000000):
     y.append(i)
```
현재 실험 환경에서 append()를 최대 3억번 까지 호출 가능하다는 것을 확인
위 내용을 기준으로 리스트에 3억개의 값을 할당하는 시간을 체크

실행 결과


<img width="365" alt="PYTHON_1" src="https://github.com/AngryOvO/linux_kernel/assets/101005580/c2020d9b-e965-4af6-9374-bcc07c923381">




2. C의 메모리 할당 시간 체크
파이썬의 리스트와 C의 배열이 완전히 동일한 구조가 아니기 때문에 파이썬에서 메모리에 할당한 리스트의 크기를 계산해 그 크기에 근사한 양을 C에서 배열로 할당
대략 인덱스가 6억정도의 정수형 배열을 만들 수 있으며 그에 해당하는 프로세스 실행시간을 체크

실행 결과 (컴파일러의 최적화 옵션을 끈 상태로 실험을 진행)


<img width="259" alt="C_1" src="https://github.com/AngryOvO/linux_kernel/assets/101005580/5df11d6c-ced2-44e9-9896-36b40aa5420a">



3. JAVA의 메모리 할당 시간 체크
JAVA 또한 마찬가지로 진행

실행 결과


<img width="437" alt="JAVA_1" src="https://github.com/AngryOvO/linux_kernel/assets/101005580/7016ab03-4ec3-4f9d-a3dd-48b7a4eb70a6">




### Python의 메모리 할당량 별 실행시간 변화

A step by step series of examples that tell you how to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Python의 실행시간 분석

다른 언어에 비해 파이썬으로 작성한 코드의 실행시간이 현저하게 느린 이유에 대한 몇가지 원인들을 찾아보았다.

대표적으로 아래 세 가지를 꼽을 수 있었다.
1. 동적 타입 검사
2. GC (가비지 컬렉션)
3. 인터프리터

각 원인이 파이썬 실행시간에 어떠한 차이를 주는지에 대한 실험을 진행했다.


### 동적 타입 검사 Dynamic type checking

실행시간에 변수나 객체의 타입을 검사하는 기능이다.

Python이 C와 Java와 다른 대표적인 특징 중 하나이다.

파이썬은 명시적으로 타입을 선언하지 않기 때문에 실행 시간에 동적으로 타입을 판단한다.
당연하게도 실행시간에 모든 데이터타입을 검사하는 과정이 포함되므로 오버헤드가 발생한다.
파이썬에서 타입 힌트와 정적 검사 도구를 제공하지만 실제로 동적 타입 검사를 실행하지 않는 방법은 존재하지 않는다.

실제로 타입 힌트와 명시적으로 데이터타입을 표기하더라도 실행시간에 큰 차이가 없다는 것을 다음 실행 결과를 통해 알 수 있다.

실행 결과 (명시적으로 리스트에 들어올 데이터의 타입을 정한 경우)




<img width="688" alt="PYTHON_static_typing" src="https://github.com/AngryOvO/linux_kernel/assets/101005580/a56c1919-f303-4583-8c95-8253d7715838">



동적 타입검사가 실행시간에 큰 영향을 주지 않아 보이지만, 후에 설명할 인터프리터에서 실행시간과의 영향에 대해 다시 알아볼 것이다.

### GC 가비지 컬렉션 

할당을 해제한 메모리들을 수집해 관리하는 기능이다.

지금까지의 테스트 코드는 이번 실험 환경의 메모리의 약 70퍼센트를 할당하고 해제하는 과정을 반복한다.
그 과정에서 가비지 컬렉션도 마찬가지로 메모리를 수집하고 정리를 반복한다.
가비지 컬렉션의 활동에 대한 오버헤드가 프로세스 실행시간에 얼마나 큰 영향을 미치는지를 알아보자.

기존 테스트 코드에서 메모리를 할당하는 시점부터 종료되는 시점까지 가비지 컬렉션을 비활성화 했을 때의 시간 차이를 보면 아래와 같다

실행 결과



<img width="657" alt="PYTHON_gc_disable" src="https://github.com/AngryOvO/linux_kernel/assets/101005580/cc0f4bd6-369e-4a33-bbba-9c70153f27d5">




## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Billie Thompson** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone whose code was used
* Inspiration
* etc
