
- 수많은 기능들이 backend 디렉토리에 들어있는 것에 비해 main.ts가 생각보다 간단해보였다. 직접 정의한 객체는 단 하나만 사용하고 나머지는 다 외부 모듈을 import했길래 처음에는 뭔가 싶었는데, 아니나다를까 그 직접 정의한 객체에 backend의 모든 기능이 다 포함되어 있었다.
    - 그렇지만 역시 focal point는 main이다. 확실히 전체적인 실행 흐름은 main에 있고 나머지는 상대적으로 부수적인 요소(backend의 모든 기능이 다 포함되어 있는 객체도 마찬가지)이다.
    - 직접 해보니 focal point를 잡고 생소한 코드를 읽어나가는 것에 대한 의의를 알 수 있었다.

- 남이 작성한 그것도 생소한 언어로 작성된 코드를, 설명 없이 혼자서 읽어만 본 경험은 많지 않아서 과연 코드를 이해할 수 있을지 걱정했지만 변수, 함수, 파일명들이 처음 보는 사람도 알아보기 쉽게 잘 명명되어 있어서 전체 흐름을 간단히 이해하는 정도는 생각외로 쉬웠다. (당연히 정확하게는 이해못함...아주 간단하게만 이해했음.)

- 이 과정에서 IDE를 사용하니 무척 편했다.
    - 이번 타입스크립트(자바스크립트)와 같이 익숙하지 않은 언어의 코드에서 괄호를 기준으로 열었다 닫았다할 수 있어서 코드를 단위별로 chunk하고 구조화하여 이해하기가 편했다.
    - 정보를 얻고 싶은 특정 객체나 함수에 대해 타고 들어가서(마치 웹에서 link로 이동하는 것과 같음) 정확히 어떻게 구현이 되어있는지 definition을 바로 찾아볼 수 있었던 점도 편했다.
    앞으로도 IDE를 사용해 이렇게 생소한 코드를 읽을 의향이 있다!