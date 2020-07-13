import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sys

def csv_to_graphic(folder_path, csv_path):
	results_table = pd.read_csv(csv_path, sep=',')
	vet_iter = results_table['ITER'].values
	vet_set_size = results_table['TEACHING SET SIZE'].values
	max_iter = np.max(vet_set_size)
	new_lines = []
	for i in range(1,len(vet_iter)):
		results_table.at[results_table.index[i], 'ITER'] = results_table.at[results_table.index[i], 'TEACHING SET SIZE']
	    
		for j in range(vet_set_size[i-1]+1, vet_set_size[i]):
			new_lines.append([j] + [x for x in results_table.iloc[i-1].values[1:] ])
			new_lines[-1][-3] = j
			new_lines[-1][-4] = 1

		if vet_iter[i]== 0 or i==(len(vet_iter)-1):
			if i==(len(vet_iter)-1): i+=1
			for j in range(vet_iter[i-1]+1, max_iter+1):
	            
				new_lines.append([j] + [x for x in results_table.iloc[i-1].values[1:] ])
				new_lines[-1][-3] = j
				new_lines[-1][-4] = 1

	cols = results_table.columns
	new_lines = pd.DataFrame(data=new_lines, columns=cols)
	results_table = pd.concat([results_table, new_lines], ignore_index=True)

	results_table = results_table.groupby(by=['ITER', 'TEACHER', 'LEARNER', 'HYPOTHESES GENERATOR']).mean()
	results_table.sort_values(['TEACHER', 'ITER'], inplace=True)
	results_table.drop(columns=['TEACHER SEED', 'LEARNER SEED', 'HYP_GENERATOR SEED'], inplace=True)

	X, Y, labels = [],[],[]
	c = 0
	for row in results_table.iterrows():
	    if row[0][0] == 0:
	        X.append([])
	        Y.append([])
	        labels.append(row[0][1]+'_'+row[0][2])
	    
	    X[c].append(row[0][0])
	    Y[c].append(row[1][3])
	    
	    if row[0][0] == max_iter:
	        c+=1

	plt.figure(figsize=(11, 5))
	for i in range(len(X)):
		plt.plot(range(len(Y[i])), Y[i], label=labels[i])

	    #plt.scatter(range(len(Y[i])), Y[i], label=labels[i])	    
	    #plt.plot(range(len(Y[i])), Y[i])#, label=labels[i])
	    #plt.xticks(X[i])
	plt.legend()
	plt.xlabel('Teaching Set Size')
	plt.ylabel('Accuracy')
	#plt.show()
	plt.savefig(folder_path+'/graphic.png')

if __name__ == '__main__':
	folder_path = sys.argv[1]
	csv_path = sys.argv[2]
	csv_to_graphic(folder_path, csv_path)
