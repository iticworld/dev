# [OpenCV] 간단한 이미지 출력 프로그램

이 프로그램은 GCC를 사용하셔서 컴파일 하시면 됩니다.

```shell
g++ -o display display.cpp -I<opencv include path> -L<opencv lib path> -lopencv_imgcodecs -lopencv_highgui -lopencv_core
```

아래는 `/usr/local` 에 설치한 OpenCV 라이브러리와 헤더 파일을 포함시켜서 프로그램을 빌드한 것입니다.

```shell
g++ -o display display.cpp -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_imgcodecs -lopencv_highgui -lopencv_core
```
