.name 		"le monstre du lock-bits"
.comment	"ta mere elle fait du rodeo sur les kfar"

ld %1, r8
ld %2, r9
ld %4, r10
ld %410, r11
ld %400, r12
ld %2, r14
ld %410, r15
ld %400, r16
sti r1, %:attack, %1

ok:
	ld %0, r3
	zjmp  %:attack

attack:
	live %1
	live %2
	ld %57672961, r2
	ld %57672705, r6
	ld %57672961, r4
	ld %57672705, r5
	sti r5, r11, r10
	sti r4, r12, r10
	sti r2, r10, r11
	sti r6, r10, r12
	sti r5, r10, r11
	sti r4, r10, r12
	sti r2, r10, r11
	sti r6, r10, r12
	sti r2, r10, r11
	sti r6, r10, r12
	sti r2, r10, r11
	sti r6, r10, r12
	add r10, r11, r11
	add r10, r12, r12
	fork %4
	ld 	%0, r3
	fork %1
	ld %0, r3
	zjmp %350
	ld %0, r3
	ld %0, r3
	zjmp %-200
	xor r1, r1, r1
	zjmp %350
	fork 		%1
	ld %0, r3
	ld %0, r3
	st r3, 60
	zjmp %-50
