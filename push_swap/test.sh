rm -rf testi
for i in {1..100}; do
	echo $i >> testi
	for VAR in {1..20};do
		ARG=`ruby -e "puts (1..$i).to_a.shuffle.join(' ')"`; ./push_swap $ARG  | ./checker $ARG >> testi
	done
done
