first = int(raw_input("Enter a number to start the sequence at: "))
x = 1
max = 0
counter = 0

while x == 1:
	if (first % 2) == 0:
		first /= 2
		counter += 1
		if first > max:
			max = first
		if first <= 1: break

	if (first % 2) != 0:
		first = ((first * 3) + 1)
		counter += 1
		if first > max:
			max = first
		if first <= 1: break

print "Number of iterations: ",
print counter
print "Highest number in sequence: ",
print max
