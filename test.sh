#!/bin/bash

make \
&& ./minishell < test_subjects > HOME.log \
&& bash        < test_subjects > BASH.log \
&& diff BASH.log HOME.log \
;
