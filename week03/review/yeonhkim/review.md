
내가 minishell을 했을 때 맡았던 부분들 중 가장 기억에 남았던 실행부 쪽을 보았다. (마침 내가 맡은 리뷰 대상자인 dahkang님께서도 실행부 쪽을 맡으시기도 하였다.)

우선 프로젝트 디렉토리를 전체적으로 둘러보았을 때, 쉘에 필요한 각 기능들이 라이브러리(lib)로 나눠져있어서 그 점이 신기했다. 나는 실행부를 보기로 마음 먹었으므로, 내가 주로 본 곳은 ./modules/libexec 디렉토리였다.
궁금한 사용자 정의 데이터 타입 혹은 함수가 있을 경우 같은 디렉토리 내부를 살펴보면 대부분 전부 있었기에 무척 보기가 좋았다. (선언이나 정의부를 바로 타고 들어가서 볼 수 있는 IDE의 편리한 기능이 있긴 하지만, 여전히 필요로 하는 부분을 빠르게 찾을 수 있도록 구조화하는 건 중요하다.)

코드에 대한 코멘트는 이미 소스 내 주석으로 여럿 달아두었기에 여기서는 짧게 요약만 해보겠다.

<아쉬웠던 점>
- 함수와 변수 명명에 있어 일관적이지 않은 부분이 있다.
- 함수의 파라미터가 적절히 설정되어 있지 않다. 그래서 생기는 문제는 두 가지 있다.
	1. 전달받은 인자(주로 구조체)내부를 탐색해서 원하는 멤버에 접근하거나 혹은 필요한 값만을 별도로 구해주는 작업이 피호출함수 내부에서 이루어진다.
	2. 함수의 원형(prototype)만을 볼 때 어떤 기능을 하고, 또 전달된 인자가 내부적으로 어떻게 사용되는지 알기가 어렵다.
- 구조체 내부에 불필요한 멤버가 있다.
- 중복되는 코드가 존재한다. (대표적으로 에러 메세지 출력)
- 반복용 변수 i 그리고 인덱스의 시작값이 -1이다.

<좋았던 점>
- 에러 처리가 꼼꼼하게 잘 되어있다.
- 프로젝트 디렉토리 구조가 전체적으로 필요한 부분만을 탐색하기 좋게 되어있다.
- 반복용 변수 i 그리고 인덱스의 시작값이 -1인 점이 코드 내내 일관적이다(?)

분명 필요한 기능을 훌륭히 수행하고 있는 코드인데 자잘한 부분들(사실 그리 자잘하지 않을지도 모른다)때문에 가독성이 저하되는 것 같아서 코드의 작성자도 아닌 내가 괜히 더 아쉬웠다.
개인적으로는 시간이 없어 실행부 외에 다른 코드를 더 못 본 것이 아쉽다. 정말 솔직하게 코멘트를 달아서 dahkang님이 상처를 받지는 않으실지 조금 걱정되기도 하는데...내 코드도 이렇게 발가벗겨질 것이기 때문에 용서해주실 것이라 믿는다. 훌륭한 코드 잘 봤습니다 dahkang님!!!