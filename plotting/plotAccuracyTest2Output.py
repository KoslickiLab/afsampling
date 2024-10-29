from matplotlib import pyplot as plt
import pandas as pd

# Read the data from the CSV file
data = pd.read_csv('accuracyTest2Output', sep='\t', header=None)
data.columns = ['size_a', 'size_b', 'jaccard_true', 'jaccard_aff_k_300', 'jaccard_aff_k_400', 'jaccard_aff_k_500', 'jaccard_aff_k_600', 'jaccard_aff_k_700', 'jaccard_fmh']

# plot jaccards against true
plt.scatter(data['jaccard_true'], data['jaccard_fmh'], label='FMH Jaccard', alpha=0.5)
plt.scatter(data['jaccard_true'], data['jaccard_aff_k_300'], label='AFF Jaccard (k = 300)', alpha=0.5)
plt.scatter(data['jaccard_true'], data['jaccard_aff_k_400'], label='AFF Jaccard (k = 400)', alpha=0.4)
plt.scatter(data['jaccard_true'], data['jaccard_aff_k_500'], label='AFF Jaccard (k = 500)', alpha=0.3)
plt.scatter(data['jaccard_true'], data['jaccard_aff_k_600'], label='AFF Jaccard (k = 600)', alpha=0.2)
plt.scatter(data['jaccard_true'], data['jaccard_aff_k_700'], label='AFF Jaccard (k = 700)', alpha=0.15)

plt.xlabel('True Jaccard')
plt.ylabel('Estimated Jaccard')

# plot the true line
plt.plot(data['jaccard_true'], data['jaccard_true'], alpha=0.8, color='black') 

plt.legend()

plt.savefig('plotAccuracyTest2Output.svg')