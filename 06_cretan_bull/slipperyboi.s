.name "Slippery Boi"
.comment "I'm one slippery boi"
	
entry:
	fork %:live2
	sti r1, %:live, %1
	and r1, %0, r1

live:
	live %1
	zjmp %:live

live2:
	live %1
	zjmp %-10
