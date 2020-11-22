import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

fig = plt.figure()
graph = fig.add_subplot(111)
x = []
y = []

for i in range(0, 100):
	r1 = open("results/output" + str(i).zfill(3) + ".txt", "r")
	r2 = open("true_results/output" + str(i).zfill(3) + ".txt", "r")
            
	input_argv1 = r1.read().splitlines()
	input_argv2 = r2.read().split()
	argv_arr1=input_argv1[2].split()

	array1 = argv_arr1
	array2 = input_argv2

	if(len(array2) != len(array1)):
		exit("Len error in file "+str(i).zfill(3))

	for j in range(0,len(argv_arr1)):
		array1[j]=int(array1[j])
		array2[j]=int(array2[j])

	for j in range(0, len(argv_arr1)):
		if(array2[j] != array1[j]):
			exit("Sort error in file " +str(i).zfill(3))

	x.append(int(input_argv1[1]))
	y.append(int(input_argv1[0]))
	r1.close()
	r2.close()

	print(i)

print("YOU ARE AWESOME!!!")

name = input("Enter filename ")

graph.plot(x,y)
graph.grid(which='major',color = 'k')
graph.minorticks_on()
graph.grid(which='minor',color = 'gray',linestyle = ':')
graph.set_xlabel('number of elements')
graph.set_ylabel('microseconds')
fig.savefig(name + '.png')
