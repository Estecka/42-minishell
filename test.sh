#!/bin/bash

make \
&& ./minishell < test_subjects > HOME.log 2>/dev/null \
&& bash        < test_subjects > BASH.log 2>/dev/null \
;

echo "# diff :";
diff BASH.log HOME.log ;
