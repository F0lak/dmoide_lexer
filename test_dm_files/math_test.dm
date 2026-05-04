proc/math_test()
	var/a = 10
	a += 5
	a /= 2
	if(a == 7.5 && a != 10)
		return 1