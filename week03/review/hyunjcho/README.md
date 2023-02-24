# TheProgrammersBrain_2302

## built_in

#### @ `cd.c`

`ft_strjoin_left_free` && `ft_strjoin_no_free`
- 유사 함수를 기능에 따라 구분하였고, 이름에서 어떤 함수를 써야 하는지 한 눈에 알 수 있음

#### @ `echo.c`

`is_option`
- 해당 함수의 경우 문자열에서 '-n'옵션을 찾아 bool을 반환하는 형태인데, <br>
'is_option'보다는 'has_option'이 좀 더 맞지 않나 하는 생각이 듦

`bool print_newline`
- n옵션에 대한 정확한 지식이 없어도 파악이 가능하게 하는 변수명과 자료형이라고 생각함

#### @ `exit.c`

`command_has_alpha`
- 파싱부를 정확히 파악하지 못해서 잘못 생각하는 것일 수 있지만, <br>
숫자가 아닌 모든 경우에 해당하는 것이기 때문에 조금 포괄적이지 못하지 않나 싶음 

#### @ `unset.c`

`ft_delete_env`
- ft를 붙인 이유가 뭐지?!

---

## data_structure

#### @ `binary_tree_function_2.c`

`inorder_traverse_bool`
- 파싱부에 대한 이해도가 떨어져서 해당 함수가 정확히 어떤 것에 대한 true/false를 판별하는지 <br>
함수 이름으로는 파악하기가 조금 어렵다 <br>
노드의 존재 여부?!

#### @ `linked_list_function_1.c`

`swap_node`
- 전체 파일에서 'cur'과 'cursor'의 혼재

---

## expansion

#### @ `concat_content.c`

`concatenate_expanded_content`
- 확장과 연결..?

`int meet_before_dollar_len`
- 그냥 len이 아니라 정확히 어떤 길이를 재는 것인지 명시해주는 점이 흥미롭고 <br>
함수 이해에 큰 도움이 될 듯

---

## parser

#### @ `parser.c`

`hang_from_tree`
- 재밌는 함수 이름 ㅎㅎ

#### @ `tokenize_utils.c`

`ft_charjoin` && `ft_chardup`
- 함수 이름만으로는 조금 헷갈릴 수 있었을텐데, <br>
주석이 함께 있어서 보다 쉽게 이해할 수 있었음

---

## utils

#### @ `free1.c`

`free_list_node_content`
- node의 content만 free하는 것처럼 느껴진다<br>
그냥 free_list라고 해도 되지 않았을까?<br>
`free_list_only_node`에 'only_node'라는 조건을 달았으니 굳이 더 부연설명을 할 필요가 없을 것 같다. <br>
우리가 일반적으로 알고있는 list free의 형태여서..?

---

1. 전반적으로 함수 이름이 굉장히 상세하고, 변수명도 'command'등으로 축약어가 아닌 풀네임이 적혀있어서 <br>
해당 함수와 변수가 어떤 기능을 하는지 쉽게 알아볼 수 있었다 <br>

2. 유사 함수들을 기능에 따라 정확히 함수명을 새로 명명하여(ex. ft_strlen_no_space) <br>
함수의 정확한 기능을 파악할 수 있음
