./manger &

sleep 15

# while [[  $(killall -11 lampon; killall -11 ruins; killall -11 -- -bash; killall -11 yes; killall -11 manger; rm -f *.poo; pkill -11 'poo';) ]]
# do
# 	:;
# done

kill -s KILL $(pgrep crap lampon ruins xanthos yes)
kill -s KILL $(top -l 1 | grep manger | awk '{print $1}')
rm -f *.poo
