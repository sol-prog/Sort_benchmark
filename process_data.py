# Average the data sets and calculate the standard deviation for each set
# In order to run the script you will need Python 3, Numpy and Matplotlib

from pylab import *

def gen_plot(prefix, nr_tests, descr):	
	tmp = []

	for i in range(nr_tests):
		fname = "data/" + prefix + "_" + "data_" + str(i) + ".txt"
		tmp.append(np.loadtxt(fname))

	data = np.mean(tmp, 0)
	std = np.std(tmp, 0)

	figure(1)
	plot(data[:,0],data[:,1], color="blue", linewidth=2.5, label = "unsorted")
	plot(data[:,0],data[:,2], color="red", linewidth=2.5, label = "sorted, increasing")
	plot(data[:,0],data[:,3], color="green", linewidth=2.5, label = "sorted, decreasing")
	plot(data[:,0],data[:,4], color="black", linewidth=2.5, label = "identity")

	xlabel('Number of elements')
	ylabel('Time [ms]')
	title(descr)
	legend(loc='upper left')

	errorbar(data[:,0],data[:,1], std[:,1], color="blue")
	errorbar(data[:,0],data[:,2], std[:,2], color="red")	
	errorbar(data[:,0],data[:,3], std[:,3], color="green")	
	errorbar(data[:,0],data[:,4], std[:,4], color="black")

	savefig(prefix + "_" + "sort_all.png", dpi=72)

	close()

	figure(2)
	plot(data[:,0],data[:,2], color="red", linewidth=2.5, label = "sorted, increasing")
	plot(data[:,0],data[:,3], color="green", linewidth=2.5, label = "sorted, decreasing")
	plot(data[:,0],data[:,4], color="black", linewidth=2.5, label = "identity")

	xlabel('Number of elements')
	ylabel('Time [ms]')
	title(descr)
	legend(loc='upper left')

	errorbar(data[:,0],data[:,2], std[:,2], color="red")
	errorbar(data[:,0],data[:,3], std[:,3], color="green")	
	errorbar(data[:,0],data[:,4], std[:,4], color="black")

	savefig(prefix +  "_" + "sort_sorted.png", dpi=72)

	close()

nr_tests = 100
gen_plot("clang", nr_tests, "Clang 3.2svn")
gen_plot("gcc", nr_tests, "Gcc-4.7.2")
gen_plot("vs", nr_tests, "Visual Studio 2012")

