import subprocess
from subprocess import PIPE

def script():
	name = input("Enter file name of the file you want to test ")
	compilation = subprocess.run("gcc -o " + name + ".exe " + name +".c")
	if(compilation.returncode != 0):
		print("C++/C compilation error")
		return 0
	
	for i in range(0, 100):
		cmd = subprocess.Popen(name + ".exe " + "input/input" + str(i).zfill(3) + ".txt", stdout=PIPE)
		cmd_out, cmd_err = cmd.communicate()
		
		if(cmd_err != None):
			error = cmd_err.decode("utf-8")
			print("The program exited with a nonzero code. Exite code: " + error + "; File error" + str(i).zfill(3))
			return 0

		to_file = cmd_out.decode("utf-8")
		
		output_txt = open("results/output" + str(i).zfill(3) + ".txt", "w")

		output_txt.write(to_file)
		
		output_txt.close()

	print("Test completed successfully")

script();