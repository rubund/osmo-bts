#!/bin/sh

PID=$$
echo "-1000" > /proc/$PID/oom_score_adj


while [ -f $1 ]; do
	(echo "0" > /proc/self/oom_score_adj && exec nice -n -20 $*) &
	LAST_PID=$!
	wait $LAST_PID
done
