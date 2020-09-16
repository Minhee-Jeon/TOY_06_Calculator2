# TOY_06_Calculator2 (사칙연산 계산기2)

네 자리(. 포함) 수와 사칙연산자를 입력해서 계산하는 계산기를 만듭니다.
입력한 순서대로 바로 계산되어 `+`, `-` 연산이 `*`, `/` 연산보다 일찍 와도 `+`, `-` 연산부터 실행됩니다.   
  
계산기에는 **0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ., C, +, -, * , /** 16개의 문자를 입력할 수 있습니다.  
   
## :heavy_check_mark: 케이스 정리   
* `1.1.1.1.1.1` -> `1.11`로 입력. 네 자리 수만 입력 가능하므로 연산자 제외 더 입력해도 피연산자는 계속 1.11로 저장됩니다.   
* **C**를 입력하기 전까지는 이전 연산 결과가 남아있습니다. 
  - `5+2-1=*2-10=` -> `2` 그 결과로 다시 연산할 수 있습니다.   
  - `5+2-1=2-10` -> `-8` 연산 결과가 남아 있어도 숫자 입력 시 예전 연산 결과는 사라지고 숫자로 새 계산이 시작됩니다.   
* `6-1=====` -> `1` **=** 을 연달아 누르면 **마지막 연산자 + 마지막 피연산자**로 연이어 계산됩니다.   
* 첫 입력이나 연산자 | 등호 입력 바로 다음 **.** 입력 시 자동으로 **0.** 으로 변환됩니다.    
   
## :warning: 주의사항
* 계산 결과가 9999를 넘으면 **E 출력** (overflow)   
* 계산 결과가 0.01보다 작으면 **0 출력** (underflow)   
* 0으로 나누는 경우 **E 출력** (arithmetic exception)    
* 계산 결과가 네 자리 수보다 작은데 -부호가 붙어있다면 출력은 아래와 같이 합니다.   
  ex. -6 표시 -> -' '' '' '6 (부호로부터 세 칸을 띄워서 출력)   
* `3.111*4.111=` -> `12.789321`입니다. 이 때 **유효 범위만 출력**합니다. 반올림할지 버림할지는 선택해서 구현하세요.   
