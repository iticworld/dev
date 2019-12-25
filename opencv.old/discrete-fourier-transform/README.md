## FOURIER TRANSFORM

푸리에 변환은 신호처리, 음성, 통신 분야에서 뿐만 아니라 영상처리에서도 매우 중요한 개념으로 다양한 응용을 가지고 있습니다.
영상을 주파수 성분으로 변환하여 다양한 분석 및 처리를 할 수 있고, 임의의 필터링 연산을 Fast Fourier Transform 을 이용하여 고속으로 구현할 수도 있습니다. 푸리에 변환은 임의의 입력 신호를 다양한 주파수를 갖는 주기함수들의 합으로 분해하여 표현하는 것입니다. 푸리에 변환에서 사용하는 주기함수는 sin, cos 삼각함수이며 푸리에 변환은 고주파부터 저주파까지 다양한 주파수 대역의 sin, cos 함수들로 원본 신호를 분해하는 것입니다.

아래 그림에서 맨 앞의 붉은 색 신호는 입력 신호이고 뒤의 파란색 신호들은 푸리에 변환(Fourier Transform)을 통해 얻어진 주기함수의 성분들이다. 즉, 원본 신호를 구성하는 신호들이다. 각각의 주기함수 성분들은 고유의 주파수(frequency)와 강도(amplitude)를 가지고 있으며 이들을 모두 합치면 원본 붉은색 신호가 된다.

![그림. 푸리에 변환](/assets/images/9967FA3359B63D8122.png)

여기서 입력 신호는 전파, 음성신호 등과 같이 시간축(time) 에 대해 정의된 신호일 수도 있고 이미지등과 같이 공간축에 대해 정의된 신호일 수도 있다. 통신 분야에서는 푸리에 변환을 Time domain 에서 Frequency domain 으로의 변환이라고 하고, 컴퓨터 비전이나 영상처리 쪽에서는 Spatial domain 에서 Frequency domain 으로의 변환이라고 부른다. 핵심은 입력 신호를 sin, cos 의 주기성분으로 분해하는 것이다.

푸리에 변환의 대단한 점은 입력 신호가 어떤 신호이든 관계없이 임의의 입력 신호를 sin, cos 주기함수들의 합으로 분해할 수 있다는 것이다. 그리고 그 과정을 수식으로 표현한 것이 푸리에 변환식이다.

푸리에 변환은 프랑스 수학자 Joseph Fourier 가 제안한 방법으로 수학사(해석학)의 역사가 새로 씌여질 정도로 대단한 발견이었다고 합니다.

<math xmlns="http://www.w3.org/1998/Math/MathML" display="block">
 <semantics>
  <mrow>
   <mi>f</mi>
   <mrow>
    <mrow>
     <mo fence="true" stretchy="false">(</mo>
     <mrow>
      <mi>x</mi>
     </mrow>
     <mo fence="true" stretchy="false">)</mo>
    </mrow>
    <mo stretchy="false">=</mo>
    <mrow>
     <munderover>
      <mo stretchy="false">∫</mo>
      <mrow>
       <mo stretchy="false">−</mo>
       <mi mathvariant="normal">∞</mi>
      </mrow>
      <mi mathvariant="normal">∞</mi>
     </munderover>
     <mrow>
      <mi>F</mi>
      <mrow>
       <mo fence="true" stretchy="false">(</mo>
       <mrow>
        <mi>u</mi>
       </mrow>
       <mo fence="true" stretchy="false">)</mo>
      </mrow>
      <msup>
       <mi>e</mi>
       <mrow>
        <mi>j</mi>
        <mn>2</mn>
        <mi>π</mi>
        <mi mathvariant="italic">ux</mi>
       </mrow>
      </msup>
      <mi mathvariant="italic">du</mi>
     </mrow>
    </mrow>
   </mrow>
  </mrow>
  <annotation encoding="StarMath 5.0">f( x ) = int from{ -%infinite } to{ %infinite } { F(u) e^{j2 %pi ux} du }</annotation>
 </semantics>
</math>

```
sudo apt install libcanberra-gtk-module libcanberra-gtk3-module
```
