import os
import sys



script = sys.argv[1]
file_list = sys.argv[2]


out_dir = "/pnfs/sbnd/resilient/users/aantonak/"

count = 0
with open(file_list, 'r') as f:
	for line in f:
		#print(line.strip())
		os.system("python "+script+ " "+line.strip()+" "+ out_dir+"eta_tpcnocosmic_truth_"+str(count)+".root")
		count += 1



print("Finished Processing!!!")



