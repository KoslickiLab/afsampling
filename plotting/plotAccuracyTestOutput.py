from matplotlib import pyplot as plt
import pandas as pd
import sys

filename = sys.argv[1]

# Read the data from the CSV file
data = pd.read_csv(filename, sep='\t')

# plot jaccards against true
plt.scatter(data['true_jaccard'], data['fmh_jaccard'], label='FMH Jaccard', alpha=0.5)
plt.scatter(data['true_jaccard'], data['aff_jaccard'], label='AFF Jaccard', alpha=0.5)

plt.xlabel('True Jaccard')
plt.ylabel('Estimated Jaccard')

# plot the true line
plt.plot(data['true_jaccard'], data['true_jaccard'], alpha=0.8)

plt.legend()

plt.savefig(f'{filename}.svg')


plt.clf()

plt.scatter(data['size_b'], (data['fmh_jaccard']-data['true_jaccard'])/data['true_jaccard'], label='FMH relative error', alpha=0.5)
plt.scatter(data['size_b'], (data['aff_jaccard']-data['true_jaccard'])/data['true_jaccard'], label='AFF relative error', alpha=0.5)

# plot the true line
plt.plot(data['size_b'], [0]*len(data), alpha=0.8)

plt.xlabel('Size of set B')
plt.ylabel('Relative error')
plt.legend()
plt.savefig(f'{filename}_relative_error.svg')

# compute the rms relative error for each method
print('FMH RMS relative error:', ((data['fmh_jaccard']-data['true_jaccard'])/data['true_jaccard']).pow(2).mean()**0.5)
print('AFF RMS relative error:', ((data['aff_jaccard']-data['true_jaccard'])/data['true_jaccard']).pow(2).mean()**0.5)


plt.clf()

plt.scatter(data['size_b'], data['fmh_sketch_size_b'], label='FMH sketch sizes', alpha=0.5)
plt.scatter(data['size_b'], data['aff_sketch_size_b'], label='AFF sketch sizes', alpha=0.5)

plt.xlabel('Size of set B')
plt.ylabel('Size of sketch of B')
plt.legend()
plt.savefig(f'{filename}_sketch_sizes.svg')

