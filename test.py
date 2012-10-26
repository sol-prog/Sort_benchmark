import subprocess
import platform

def run_tests(prefix, nr_tests):
	for i in range(nr_tests):
		fname = prefix + "_" + "data_" + str(i) + ".txt"
		if platform.system() == "Windows":
			program = prefix + "_test"
		else:
			program = "./" + prefix + "_test"
		status = subprocess.call(program + " > " + fname, shell = True)
		print("process " + str(i) + " finished")

nr_tests = 100
if platform.system() == "Linux":
	#compilers = ["clang", "gcc"]
	#compilers = ["clang"]
	compilers = ["gcc"]
elif platform.system() == "Windows":
	compilers = ["vs"]

for prefix in compilers:
	run_tests(prefix, nr_tests)

print("Finish")
