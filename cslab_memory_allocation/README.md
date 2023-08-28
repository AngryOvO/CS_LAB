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

실행시간에 변수나 객체의 타입을 검사하는 것

Python이 실험 했던 C와 Java와 다른 대표적인 특징 중 하나이다.
리스트에서 타입에 해당하는 


### And coding style tests

Explain what these tests test and why

```
Give an example
```

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
