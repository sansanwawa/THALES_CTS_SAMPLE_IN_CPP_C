# THALES_CTS_SAMPLE_IN_CPP_C


Tested on my MAC OS in Apple M1 - 14.1.1 (23B81) by using CLion IDE (https://www.jetbrains.com/clion/download)

Before test, please make sure below library are installed.

1. jsoncpp
2. curl

You may install by using `brew install jsoncpp` or `brew install curl`.
- https://formulae.brew.sh/formula/jsoncpp
- https://formulae.brew.sh/formula/curl

Below is the result when we are doing a token/detoken.

> # Token

```
index = [0] token = [D8Rz Oj 3a WHK6g 5U2U Rxx4 Vs TOqud s] 
index = [1] token = [duhA Gb 8G l5dun T53T qD9s tg hBh8A F] 
index = [2] token = [7bF7 9s qm q20cI D7Ut MTyq Ei k84ff x] 
index = [3] token = [squo eg KT 1btyT 5div gFwr Sv wjGuk T] 
index = [4] token = [zp3Y VZ od suyLr MGPr HzSl CN BIpE4 b] 
```

> # DeToken
```
index = [0] data = [This is ** ***** **** **** ** ****n 0] 
index = [1] data = [This is ** ***** **** **** ** ****n 1] 
index = [2] data = [This is ** ***** **** **** ** ****n 2] 
index = [3] data = [This is ** ***** **** **** ** ****n 3] 
index = [4] data = [This is ** ***** **** **** ** ****n 4] 
```

