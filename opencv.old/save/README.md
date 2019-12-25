# [OpenCV] 간단한 이미지 저장 프로그램

이 프로그램은 GCC 를 사용하셔서 빌드하시면 됩니다. 헤더 파일과 라이브러리 폴더의 경우 OpenCV 를 설치한 경로에 따라 다르게 설정하셔야 합니다. 기본적으로는 `/usr/local` 에 설치됩니다.

```shell
g++ -o save save.cpp -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_core
```

실행하시려면 `./save <original image path>` 를 실행시키시면 됩니다.
