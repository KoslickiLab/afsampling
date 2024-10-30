from matplotlib import pyplot as plt
import pandas as pd
import sys

filename = sys.argv[1]

# Read the data from the CSV file
data = pd.read_csv(filename, sep='\t', header=None)
data.columns = ['size_a', 'size_b', 'jaccard_true', 'jaccard_aff', 'jaccard_fmh']

# plot jaccards against true
plt.scatter(data['jaccard_true'], data['jaccard_fmh'], label='FMH Jaccard', alpha=0.5)
plt.scatter(data['jaccard_true'], data['jaccard_aff'], label='AFF Jaccard', alpha=0.5)

plt.xlabel('True Jaccard')
plt.ylabel('Estimated Jaccard')

# plot the true line
plt.plot(data['jaccard_true'], data['jaccard_true'], alpha=0.8)

plt.legend()

plt.savefig(f'{filename}.svg')