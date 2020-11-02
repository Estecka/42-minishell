#!/bin/bash

cd $(dirname $BASH_SOURCE);

if [ "$#" != "0" ];
then
	TEST_LISTS=$@
else
	TEST_LISTS=(
		echo
		export
		cd
		pipe
	);
fi



make minishell -C ../ || exit $?;

for t in ${TEST_LISTS[@]};
do
	echo "	$t :"
	../minishell <${t} >${t}.out.42sh.log 2>${t}.err.42sh.log;
	bash         <${t} >${t}.out.bash.log 2>${t}.err.bash.log;
	diff ${t}.out.42sh.log ${t}.out.bash.log;
done;
