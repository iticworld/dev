# NOVEMBERIZING CORE LIB

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/8ab41f3d3be74d4b8fa1dbc9bc210913)](https://www.codacy.com/project/iticworld/core/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=novemberizing/core&amp;utm_campaign=Badge_Grade_Dashboard)

여러 운영체제에 독립적으로 동작할 수 있는 코어 라이브러리를 만드는 것이 목적입니다.

## INSTALL GUIDE

아래의 예제는 리눅스 기반으로 빌드하는 예제입니다. 설치하시면 기본적으로 /usr/local/include 에 헤더 파일이, /usr/local/lib 에 정적 라이브러리 파일이 설치 됩니다.

```
git clone https://github.com/novemberizing/core.git
mkdir core/build/install -p
cd core/build/install
cmake -G "CodeBlocks - Unix Makefiles" ../..
sudo cmake --build ./ --target install -- -j 2
```

## CONTENTS

- [novemberizing core timestamp](document/novemberizing.core.timestamp.md)
- [novemberizing core string](document/novemberizing.core.string.md)

## SEE

- [uml](document/novemberizing.uml)
