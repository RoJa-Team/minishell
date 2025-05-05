#!/bin/bash

cat << EOF1 | cat << EOF2 >> $1
ola
EOF
adeus
EOF

echo $?

echo $DoesntExist

export NowExistsValueNumeric=1
echo $NowExistsValueNumeric
export NowExistsValueNumeric=1113745243058239740598274352743576174850234750823143
echo $NowExistsValueNumeric
unset NowExistsValueNumeric

export NowExistsValueAlpha=a
echo $NowExistsValueAlpha
export NowExistsValueAlpha=aasdfsachabsdfhasojdadsjncashebfhasjknda
echo $NowExistsValueAlpha
unset NowExistsValueAlpha

export NowExistsValueAlphaNumeric=a1
echo $NowExistsValueAlpha
export NowExistsValueAlphaNumeric=1a
echo $NowExistsValueAlpha
export NowExistsValueAlphaNumeric=168t2g7ydg18276gy8h1276
echo $NowExistsValueAlpha
export NowExistsValueAlphaNumeric=t2g7ydg18276gy8h1276
echo $NowExistsValueAlpha
unset NowExistsValueAlphaNumeric

export NowExistsValueRandom=/
echo $NowExistsValueRandom
export NowExistsValueRandom=129jeP/n\nLQ9D-90O]LQD0=DP.;.FOK3IKQ8jd123
echo $NowExistsValueRandom
unset NowExistsValueRandom

echo $1StartsWithNumberAndDoesntExist
